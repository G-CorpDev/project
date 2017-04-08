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
    Net::Rest::Routes::Post(router, "/users/:id/SelectWorksheet", Net::Rest::Routes::bind(&RouteHandler::selectWorksheet, this));
    Net::Rest::Routes::Post(router, "/worksheets", Net::Rest::Routes::bind(&RouteHandler::getWorksheets, this));

    Net::Rest::Routes::Post(router, "/users/:id/finishWorkout", Net::Rest::Routes::bind(&RouteHandler::finishWorkout, this));

    Net::Rest::Routes::Get(router, "/test", Net::Rest::Routes::bind(&RouteHandler::testHandler, this));
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
        response.send(Net::Http::Code::Unauthorized);
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
        response.send(Net::Http::Code::Unauthorized);
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
        response.send(Net::Http::Code::Not_Acceptable);
        return;
    }

    //Validation
    if (
        username.length() < 3 || username.length() > 254 || password.length() < 3 || password.length() > 254 ||
        displayName.length() < 3 || displayName.length() > 254)
    {
        std::cerr << "Invalid registration data." << std::endl;
        response.send(Net::Http::Code::Not_Acceptable);
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
        response.send(Net::Http::Code::Forbidden);
        return;
    }
    Net::Http::Cookie cookie = cookies.get("JWTtoken");
    std::string token = cookie.value;
    int userID = request.param(":id").as<int>();
    Models::User user(auth.authenticateUser(token));
    if (userID != user.getID() || !user.isValid())
    {
        response.send(Net::Http::Code::Forbidden);
        return;
    }
    response.send(Net::Http::Code::Ok, database.getUsersWorksheetByUserID(userID).toJSON());
}
void RouteHandler::getWorksheets(const Net::Rest::Request &request, Net::Http::ResponseWriter response)
{
    auto cookies = request.cookies();
    if (!cookies.has("JWTtoken"))
    {
        response.send(Net::Http::Code::Forbidden);
        return;
    }

    Net::Http::Cookie cookie = cookies.get("JWTtoken");
    std::string token = cookie.value;
    Models::User user(auth.authenticateUser(token));
    if (!user.isValid())
    {
        response.send(Net::Http::Code::Forbidden);
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
        response.send(Net::Http::Code::Not_Acceptable);
        return;
    }
    Sort sortArgument;
    if ("None" == sortBy)
    {
        sortArgument=Sort::None;
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
        response.send(Net::Http::Code::Forbidden);
        return;
    }
    Net::Http::Cookie cookie = cookies.get("JWTtoken");
    std::string token = cookie.value;
    int userID = request.param(":id").as<int>();
    Models::User user(auth.authenticateUser(token));
    if (userID != user.getID() || !user.isValid())
    {
        response.send(Net::Http::Code::Forbidden);
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
        response.send(Net::Http::Code::Not_Acceptable);
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
        response.send(Net::Http::Code::Not_Found);
        return;
    }
    response.send(Net::Http::Code::Internal_Server_Error);
}

void RouteHandler::testHandler(const Net::Rest::Request &request, Net::Http::ResponseWriter response)
{
    Models::Worksheet sheet("Test sheet", "Work please.", "1 egg", "Like shitting bricks.");
    Models::Week week1;
    Models::Week week2;
    Models::Day monday1(Models::Day::Days::Monday);
    Models::Day tuesday1(Models::Day::Days::Tuesday);
    Models::Day wednesday1(Models::Day::Days::Wednesday);
    Models::Day monday2(Models::Day::Days::Monday);
    Models::Workout overwritten("SHOULD NOT APPEAR", "get out of here", Models::Workout::TimeOfDay::Day, true);
    Models::Workout workout1("Lunch", "Have lunch, fatass", Models::Workout::TimeOfDay::Day, false);
    Models::Workout workout2("Swim", "So sharks can eat you", Models::Workout::TimeOfDay::Morning, true);
    Models::Exercise ex("pushup", "", Models::Exercise::Type::RepsOnly, "10", "0", false);
    Models::Exercise ex2("SOUPSUP", "fatass", Models::Exercise::Type::JustDone, "", "", true);
    Models::Exercise ex3("lose weight", "FATASS!", Models::Exercise::Type::JustDone, "", "", false);
    Models::Exercise ex4("lift bro", "DYEL!", Models::Exercise::Type::RepsAndWeight, "5x5", "50 moons", false);

    workout1.addExercise(ex);
    workout1.addExercise(ex3);
    workout1.addExercise(ex2);
    workout1.addExercise(ex4);
    monday1.addWorkout(overwritten);
    monday1.addWorkout(workout1);
    monday1.addWorkout(workout2);
    week1.addDay(monday1);
    week1.addDay(tuesday1);
    week1.addDay(wednesday1);
    week2.addDay(monday2);
    sheet.addWeek(week1);
    sheet.addWeek(week2);
    response.send(Net::Http::Code::Ok, sheet.toJSON());
}

void RouteHandler::finishWorkout(const Net::Rest::Request &request, Net::Http::ResponseWriter response)
{
    //TODO:
    //TODO: database error handling;
    response.send(Net::Http::Code::Not_Implemented);
}