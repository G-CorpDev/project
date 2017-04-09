#include <RouteHandler.h>

RouteHandler::RouteHandler(Net::Rest::Router &router, iDatabaseSource &database) : database(database)
{
    Net::Rest::Routes::Post(router, "/login", Net::Rest::Routes::bind(&RouteHandler::doLogin, this));
    Net::Rest::Routes::Get(router, "/logout", Net::Rest::Routes::bind(&RouteHandler::doLogout, this));
    Net::Rest::Routes::Post(router, "/register", Net::Rest::Routes::bind(&RouteHandler::doRegister, this));

    Net::Rest::Routes::Get(router, "/", Net::Rest::Routes::bind(&RouteHandler::serveIndex, this));
    Net::Rest::Routes::Get(router, "/dist/scripts/main.js", Net::Rest::Routes::bind(&RouteHandler::serveApp, this));
    Net::Rest::Routes::Get(router, "/src/img/*", Net::Rest::Routes::bind(&RouteHandler::serveImage, this));

    Net::Rest::Routes::Get(router, "/users/:id/worksheet", Net::Rest::Routes::bind(&RouteHandler::getWorksheet, this));
    Net::Rest::Routes::Post(router, "/users/:id/selectWorksheet", Net::Rest::Routes::bind(&RouteHandler::selectWorksheet, this));
    Net::Rest::Routes::Post(router, "/worksheets", Net::Rest::Routes::bind(&RouteHandler::getWorksheets, this));

    Net::Rest::Routes::Post(router, "/users/:id/finishWorkout", Net::Rest::Routes::bind(&RouteHandler::finishWorkout, this));
}

void RouteHandler::serveApp(const Net::Rest::Request &request, Net::Http::ResponseWriter response)
{
    Net::Http::serveFile(response, "./client/dist/scripts/main.js").then([](ssize_t bytes) {
        ;
        std::cout << "Served the JS bundle, sent " << bytes << " bytes." << std::endl;
    },
                                                                         Async::NoExcept);
}

void RouteHandler::serveIndex(const Net::Rest::Request &request, Net::Http::ResponseWriter response)
{
    std::cout << "Served index, ";

    Net::Http::serveFile(response, "./client/index.html").then([](ssize_t bytes) {
        ;
        std::cout << "sent " << bytes << " bytes" << std::endl;
    },
                                                               Async::NoExcept);
}

void RouteHandler::serveImage(const Net::Rest::Request &request, Net::Http::ResponseWriter response)
{
    std::string filename("./client/src/img/");
    filename.append(request.splatAt(0).as<std::string>());
    std::cout << "Served image: " << filename;
    Net::Http::serveFile(response, filename.c_str()).then([](ssize_t bytes) {
        ;
        std::cout << " ,sent " << bytes << " bytes" << std::endl;
    },
                                                          Async::NoExcept);
}

void RouteHandler::doLogin(const Net::Rest::Request &request, Net::Http::ResponseWriter response)
{
    auto ct = request.headers().get<Net::Http::Header::Host>();

    auto json = Utils::decodeSimpleJSON(request.body());

    std::string username;
    std::string password;
    try
    {
        username = json.at("username");
        password = json.at("password");
    }
    catch (std::exception e)
    {
        std::cerr << e.what() << " Error in credentials" << std::endl;
        response.send(Net::Http::Code::Not_Acceptable,"Credentials are malformed.");
        return;
    }
    Models::User user = database.getUserByCredentials(username, password);
    if (user.isValid())
    {
        std::map<std::string, std::string> userData;
        userData.insert({"displayName", user.getDisplayName()});
        userData.insert({"id", std::to_string(user.getID())});

        std::cout << "login from " << ct->host() << ":" << ct->port() << " - " << request.body() << std::endl;
        std::string token = auth.generateToken(user);
        std::string payload("JWTtoken=");
        payload.append(token);
        payload.append("; path=/ ");
        payload.append("; domain=localhost ");
        payload.append("; Max-Age=3600");
        Net::Http::Cookie cookie = Net::Http::Cookie::fromString(payload);
        cookie.httpOnly = true;
        response.cookies().add(cookie);
        response.send(Net::Http::Code::Ok, Utils::makeSimpleJSON(userData));
        return;
    }
    else
    {
        std::cout << "INVALID login from " << ct->host() << ":" << ct->port() << " - " << request.body() << std::endl;
        response.send(Net::Http::Code::Unauthorized,"Invalid credentials.");
        return;
    }
    response.send(Net::Http::Code::Internal_Server_Error);
}

void RouteHandler::doLogout(const Net::Rest::Request &request, Net::Http::ResponseWriter response)
{
    auto cookieJar = request.cookies();
    if (cookieJar.has("JWTtoken"))
    {
        auto cookie = request.cookies().get("JWTtoken");
        cookie = Net::Http::Cookie::fromString("JWTtoken=Logged Out.; path=/ ; domain=localhost ; max-age=2");
        cookie.httpOnly = true;
        response.cookies().add(cookie);
    }
    response.send(Net::Http::Code::Ok);
}

void RouteHandler::doRegister(const Net::Rest::Request &request, Net::Http::ResponseWriter response)
{
    auto json = Utils::decodeSimpleJSON(request.body());
    std::string username;
    std::string password;
    std::string displayName;

    try
    {
        username = json.at("username");
        password = json.at("password");
        displayName = json.at("nickname");
    }
    catch (std::exception e)
    {
        std::cerr << e.what() << " Error in registration data." << std::endl;
        response.send(Net::Http::Code::Not_Acceptable,"Registration data malformed");
        return;
    }

    //Validation
    if (
        username.length() < 3 || username.length() > 254 || password.length() < 3 || password.length() > 254 ||
        displayName.length() < 3 || displayName.length() > 254)
    {
        std::cerr << "Invalid registration data." << std::endl;
        response.send(Net::Http::Code::Not_Acceptable,"Invalid registration data.");
        return;
    }

    Results::Database err = database.saveUser(displayName, username, password);
    if (err == Results::Database::Ok)
    {
        Models::User user = database.getUserByCredentials(username, password);
        if (user.isValid())
        {
            std::map<std::string, std::string> userData;
            userData.insert({"displayName", user.getDisplayName()});
            userData.insert({"id", std::to_string(user.getID())});
            std::string token = auth.generateToken(user);
            std::string payload("JWTtoken=");
            payload.append(token);
            payload.append("; path=/ ");
            payload.append("; domain=localhost ");
            payload.append("; Max-Age=3600");
            Net::Http::Cookie cookie = Net::Http::Cookie::fromString(payload);
            cookie.httpOnly = true;
            response.cookies().add(cookie);
            std::cout << "Registered " << user.getDisplayName() << std::endl;
            response.send(Net::Http::Code::Ok, Utils::makeSimpleJSON(userData));
            return;
        }
    }
    else
    {
        //TODO:database error handling
    }
    response.send(Net::Http::Code::Internal_Server_Error);
}

void RouteHandler::getWorksheet(const Net::Rest::Request &request, Net::Http::ResponseWriter response)
{
    auto cookies = request.cookies();
    if (!cookies.has("JWTtoken"))
    {
        response.send(Net::Http::Code::Forbidden,"No authorization present.");
        return;
    }
    Net::Http::Cookie cookie = cookies.get("JWTtoken");
    std::string token = cookie.value;
    int userID = request.param(":id").as<int>();
    Models::User user(auth.authenticateUser(token));
    if (userID != user.getID() || !user.isValid())
    {
        response.send(Net::Http::Code::Forbidden,"Invalid authrization.");
        return;
    }
    std::cout<<"Getting worksheet"<<std::endl;
    Models::Worksheet sheet = database.getUsersWorksheetByUserID(userID);
    std::cout<<"Got worksheet"<<std::endl;
    response.send(Net::Http::Code::Ok, sheet.toJSON());
}
void RouteHandler::getWorksheets(const Net::Rest::Request &request, Net::Http::ResponseWriter response)
{
    auto cookies = request.cookies();
    if (!cookies.has("JWTtoken"))
    {
        response.send(Net::Http::Code::Forbidden,"No authorization present.");
        return;
    }

    Net::Http::Cookie cookie = cookies.get("JWTtoken");
    std::string token = cookie.value;
    Models::User user(auth.authenticateUser(token));
    if (!user.isValid())
    {
        response.send(Net::Http::Code::Forbidden,"Invalid authrization.");
        return;
    }

    auto json = Utils::decodeSimpleJSON(request.body());
    std::string sortBy;
    std::string descendingString;

    try
    {
        sortBy = json.at("sortBy");
        descendingString = json.at("descending");
    }
    catch (std::exception e)
    {
        std::cerr << e.what() << " Error in sorting parameters." << std::endl;
        response.send(Net::Http::Code::Not_Acceptable,"Sorting parameters malformed.");
        return;
    }
    Sort sortArgument;
    if ("None" == sortBy)
    {
        sortArgument = Sort::None;
    }
    else
    {
        bool descending;
        if ("false" == descendingString)
        {
            descending = false;
        }
        if ("true" == descendingString)
        {
            descending = true;
        }
        switch (descending)
        {
        case (false):
            if ("Name" == sortBy)
            {
                sortArgument = Sort::Name;
                break;
            }
            if ("Length" == sortBy)
            {
                sortArgument = Sort::Length;
                break;
            }
            if ("AvgWorkoutTime" == sortBy)
            {
                sortArgument = Sort::AvgWorkoutTime;
                break;
            }
            if ("Difficulty" == sortBy)
            {
                sortArgument = Sort::Difficulty;
                break;
            }
        case (true):
            if ("Name_Descending" == sortBy)
            {
                sortArgument = Sort::Name_Descending;
                break;
            }
            if ("Length_Descending" == sortBy)
            {
                sortArgument = Sort::Length_Descending;
                break;
            }
            if ("AvgWorkoutTime_Descending" == sortBy)
            {
                sortArgument = Sort::AvgWorkoutTime_Descending;
                break;
            }
            if ("Difficulty_Descending" == sortBy)
            {
                sortArgument = Sort::Difficulty_Descending;
                break;
            }
        }
    }
    std::vector<Models::Worksheet> sheets = database.getAllWorksheets(sortArgument);

    std::string res("{\"sheets\":[");
    bool first = true;

    for (auto &sheet : sheets)
    {
        if (!first)
        {
            res.append(",");
        }
        res.append(sheet.toJSON());
        first = false;
    }
    res.append("]}");

    response.send(Net::Http::Code::Ok, res);
}

void RouteHandler::selectWorksheet(const Net::Rest::Request &request, Net::Http::ResponseWriter response)
{
    auto cookies = request.cookies();
    if (!cookies.has("JWTtoken"))
    {
        response.send(Net::Http::Code::Forbidden,"No authorization present.");
        return;
    }
    Net::Http::Cookie cookie = cookies.get("JWTtoken");
    std::string token = cookie.value;
    int userID = request.param(":id").as<int>();
    Models::User user(auth.authenticateUser(token));
    if (userID != user.getID() || !user.isValid())
    {
        response.send(Net::Http::Code::Forbidden,"Invalid authorization.");
        return;
    }

    auto json = Utils::decodeSimpleJSON(request.body());
    std::string worksheetName;

    try
    {
        worksheetName = json.at("worksheet");
    }
    catch (std::exception e)
    {
        std::cerr << e.what() << " Error in worksheet name." << std::endl;
        response.send(Net::Http::Code::Not_Acceptable,"Worksheet data malformed.");
        return;
    }

    Results::Database err = database.selectWorksheetByWorksheetName(userID, worksheetName);
    if (err != Results::Database::Ok)
    {
        response.send(Net::Http::Code::Ok);
        return;
    }
    if (err == Results::Database::NotFound)
    {
        response.send(Net::Http::Code::Not_Found,"Worksheet not found in database.");
        return;
    }
    response.send(Net::Http::Code::Internal_Server_Error);
}

void RouteHandler::finishWorkout(const Net::Rest::Request &request, Net::Http::ResponseWriter response)
{
    //TODO:
    //tmp
    int userID = 0;
    /*auto cookies = request.cookies();
    if (!cookies.has("JWTtoken"))
    {
        response.send(Net::Http::Code::Forbidden,"No authorization found.");
        return;
    }
    Net::Http::Cookie cookie = cookies.get("JWTtoken");
    std::string token = cookie.value;
    int userID = request.param(":id").as<int>();
    Models::User user(auth.authenticateUser(token));
    if (userID != user.getID() || !user.isValid())
    {
        response.send(Net::Http::Code::Forbidden,"Invalid authorization.");
        return;
    }*/
    json_error_t err;
    json_t *json = json_loads(request.body().c_str(), 0, &err);
    if (!json_is_object(json))
    {
        response.send(Net::Http::Code::Not_Acceptable);
        std::cout << "JSON malformed" << std::endl;
        json_decref(json);
        return;
    }
    int week = json_integer_value(json_object_get(json, "week"));
    //TODO: change string day to MODELS::DAY::DAYS
    std::string day(json_string_value(json_object_get(json, "day")));
    std::string time(json_string_value(json_object_get(json, "time")));

    json_t *exercises = json_object_get(json, "exercises");
    if (!json_is_array(exercises))
    {
        response.send(Net::Http::Code::Not_Acceptable);
        std::cout << "Exercises not an array." << std::endl;
        json_decref(json);
        return;
    }

    json_t *exercise;
    size_t index;
    json_array_foreach(exercises, index, exercise)
    {
        json_t *nameObject = json_object_get(exercise, "name");
        std::string name;
        if (json_is_string(nameObject))
        {
            name = json_string_value(nameObject);
        }
        else
        {
            response.send(Net::Http::Code::Not_Acceptable, "Name malformed in exercise " + std::to_string(index + 1) + ".");
            return;
        }
        json_t *noteObject = json_object_get(exercise, "note");
        std::string note;
        if (json_is_string(noteObject))
        {
            name = json_string_value(noteObject);
        }
        else
        {
            response.send(Net::Http::Code::Not_Acceptable, "Note malformed in exercise " + std::to_string(index + 1) + ".");
            return;
        }
        json_t *doneObject = json_object_get(exercise, "done");
        bool done = false;
        bool doneDefined = false;
        if (json_is_boolean(doneObject))
        {
            done = json_boolean_value(doneObject);
            doneDefined = true;
        }
        json_t *repsObject = json_object_get(exercise, "R");
        std::string reps;
        if (json_is_string(repsObject))
        {
            reps = json_string_value(repsObject);
        }
        json_t *weightObject = json_object_get(exercise, "W");
        std::string weight;
        if (json_is_string(weightObject))
        {
            weight = json_string_value(weightObject);
        }//TODO: day -> int conv.

        Models::Exercise::Type type;
        if (!doneDefined && reps == "" && weight == "")
        {
            response.send(Net::Http::Code::Not_Acceptable, "No discernable type in exercise " + std::to_string(index + 1) + ".");
            return;
        }
        if (doneDefined && reps == "" && weight == "")
        {
            type = Models::Exercise::Type::JustDone;
        }
        if (!doneDefined && reps != "" && weight != "")
        {
            type = Models::Exercise::Type::RepsAndWeight;
        }
        if (!doneDefined && reps == "" && weight != "")
        {
            type = Models::Exercise::Type::WeightOnly;
        }
        if (!doneDefined && reps != "" && weight == "")
        {
            type = Models::Exercise::Type::RepsOnly;
        }

        Results::Database result;
        switch (type)
        {
        case Models::Exercise::Type::RepsOnly:
            std::cout << "reps only" << std::endl;
            //result = database.saveExercise(userID,week,)
            break;
        case Models::Exercise::Type::JustDone:
            std::cout << "JustDone" << std::endl;
            break;
        case Models::Exercise::Type::WeightOnly:
            std::cout << "WeightOnly" << std::endl;
            break;
        case Models::Exercise::Type::RepsAndWeight:
            std::cout << "BOTH" << std::endl;
            break;
        }
    }

    //TODO: expand this verification
    //if json_has_?
    if (week < 1 || "" == day || "" == time)
    {
        response.send(Net::Http::Code::Not_Acceptable);
        std::cout << "Too little data" << std::endl;
        json_decref(json);
        return;
    }

    std::cout << "Week " << week << ", " << day << " " << time << std::endl;

    //TODO: database error handling;
    response.send(Net::Http::Code::Internal_Server_Error);
    json_decref(json);
}

//TODO: put error messages in responses.