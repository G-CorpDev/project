#include <pistache/router.h>

#include <RouteHandler.h>

RouteHandler::RouteHandler(Net::Rest::Router &router)
{
    Net::Rest::Routes::Post(router, "/login", Net::Rest::Routes::bind(&RouteHandler::doLogin, this));
    Net::Rest::Routes::Post(router, "/register", Net::Rest::Routes::bind(&RouteHandler::doRegister, this));

    Net::Rest::Routes::Get(router, "/", Net::Rest::Routes::bind(&RouteHandler::serveIndex, this));
    Net::Rest::Routes::Get(router, "/dist/scripts/main.js", Net::Rest::Routes::bind(&RouteHandler::serveApp, this));
    Net::Rest::Routes::Get(router, "/src/img/*", Net::Rest::Routes::bind(&RouteHandler::serveImage, this));
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
    std::cout<<"Served image: "<< filename;
    Net::Http::serveFile(response, filename.c_str()).then([](ssize_t bytes) {
        ;
        std::cout << " ,sent " << bytes << " bytes" << std::endl;
    },
                                                               Async::NoExcept);
}

void RouteHandler::doLogin(const Net::Rest::Request &request, Net::Http::ResponseWriter response)
{
    auto headers = request.headers();
    auto ct = headers.get<Net::Http::Header::Host>();
    std::cout << "login from " << ct->host() << ":" << ct->port() << " - " << request.body() << std::endl;
    response.send(Net::Http::Code::Ok, "Piss off, CUNT!\n");
}

void RouteHandler::doRegister(const Net::Rest::Request &request, Net::Http::ResponseWriter response)
{
    std::cout << "register from " << request.body() << std::endl;
    response.send(Net::Http::Code::Ok, "Piss off, CUNT!\n");
}