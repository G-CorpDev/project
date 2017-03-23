#include <pistache/router.h>

#include <RouteHandler.h>

RouteHandler::RouteHandler(Net::Rest::Router &router)
{
    Net::Rest::Routes::Get(router, "/users/:id", Net::Rest::Routes::bind(&RouteHandler::testHandler, this));
    Net::Rest::Routes::Post(router, "/login", Net::Rest::Routes::bind(&RouteHandler::doLogin, this));
    Net::Rest::Routes::Post(router, "/register", Net::Rest::Routes::bind(&RouteHandler::doRegister, this));
}

void RouteHandler::testHandler(const Net::Rest::Request &request, Net::Http::ResponseWriter response)
{
    auto id = request.param(":id").as<int>();
    std::cout << "Querying User " << id << std::endl;
    auto bytesSent = response.send(Net::Http::Code::Ok, "Piss off cunt!\n");
}

void RouteHandler::doLogin(const Net::Rest::Request &request, Net::Http::ResponseWriter response)
{   
    std::cout<<"login from "<<request.body()<<std::endl;
    response.send(Net::Http::Code::Forbidden,"Piss off, CUNT!\n");
}

void RouteHandler::doRegister(const Net::Rest::Request &request, Net::Http::ResponseWriter response)
{   
    std::cout<<"register from "<<request.body()<<std::endl;
    response.send(Net::Http::Code::Forbidden,"Piss off, CUNT!\n");
}