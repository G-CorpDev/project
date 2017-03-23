#include<pistache/router.h>

#include <RouteHandler.h>

RouteHandler::RouteHandler(Net::Rest::Router &router)
{
    Net::Rest::Routes::Get(router, "/users/:id", Net::Rest::Routes::bind(&RouteHandler::testHandler, this));
}

void RouteHandler::testHandler(const Net::Rest::Request &request, Net::Http::ResponseWriter response)
{
    auto id = request.param(":id").as<int>();
    std::cout << "Querying User " << id << std::endl;
    auto bytesSent = response.send(Net::Http::Code::Ok, "Piss off cunt!\n");
}