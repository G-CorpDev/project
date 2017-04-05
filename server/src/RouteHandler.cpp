#include <RouteHandler.h>

RouteHandler::RouteHandler(Net::Rest::Router &router, iDatabaseSource &database) : database(database)
{
    Net::Rest::Routes::Post(router, "/login", Net::Rest::Routes::bind(&RouteHandler::doLogin, this));
    Net::Rest::Routes::Get(router, "/logout", Net::Rest::Routes::bind(&RouteHandler::doLogout, this));
    Net::Rest::Routes::Post(router, "/register", Net::Rest::Routes::bind(&RouteHandler::doRegister, this));

    Net::Rest::Routes::Get(router, "/", Net::Rest::Routes::bind(&RouteHandler::serveIndex, this));
    Net::Rest::Routes::Get(router, "/dist/scripts/main.js", Net::Rest::Routes::bind(&RouteHandler::serveApp, this));
    Net::Rest::Routes::Get(router, "/src/img/*", Net::Rest::Routes::bind(&RouteHandler::serveImage, this));

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

    auto json = Utils::decodeJSON(request.body());

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
        std::map<std::string,std::string> userData;
        userData.insert({"displayName", user.getDisplayName()});
        userData.insert({"id", std::to_string(user.getID())});
        userData.insert({"age", std::to_string(user.getAge())});
        userData.insert({"sex", std::to_string(user.getSex())});
        userData.insert({"height", std::to_string(user.getHeight())});
        userData.insert({"weight", std::to_string(user.getWeight())});
        
        std::cout << "login from " << ct->host() << ":" << ct->port() << " - " << request.body() << std::endl;
        std::string token = auth.generateToken(user);
        Net::Http::Cookie cookie("token", token);
        cookie.httpOnly = true;
        response.cookies().add(cookie);
        response.send(Net::Http::Code::Ok,Utils::makeJSON(userData));
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
    if(cookieJar.has("token")){
        auto cookie = request.cookies().get("token");
        cookie.value = "";
        response.cookies().add(cookie);
    }
    response.send(Net::Http::Code::Ok);
}

void RouteHandler::doRegister(const Net::Rest::Request &request, Net::Http::ResponseWriter response)
{
    std::cout << "register from " << request.body() << std::endl;
    response.send(Net::Http::Code::Ok, "Piss off, CUNT!\n");
}

void RouteHandler::testHandler(const Net::Rest::Request &request, Net::Http::ResponseWriter response)
{
    std::cout << "test - " << request.body() << std::endl;
    Net::Http::Cookie cookie("test", "fuck");
    cookie.httpOnly = true;
    response.cookies()
        .add(cookie);
    response.send(Net::Http::Code::Ok, "BITCH\n");
}

//std::string token = request.cookies().get("auth").value;