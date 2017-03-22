#include <iostream>
#include <pistache/endpoint.h>
#include <pistache/router.h>
#include <pistache/http.h>

#include <Models.h>

class RouteHandler {
    public:
        RouteHandler(Net::Rest::Router & router){
            Net::Rest::Routes::Get(router,"/users/:id",Net::Rest::Routes::bind(&RouteHandler::testHandler,this));
        }
        void testHandler(const Net::Rest::Request& request, Net::Http::ResponseWriter response){
            auto id = request.param(":id").as<int>();
            std::cout<<"Querying User " << id <<std::endl;
            auto bytesSent = response.send(Net::Http::Code::Ok,"Piss off cunt!\n");
        }
};

int main (int argc , char ** argv){
    Net::Address acceptFromAddress(Net::Ipv4::any(),Net::Port(3000));
    auto options = Net::Http::Endpoint::options().threads(2);
    Net::Rest::Router router;
    RouteHandler handler(router);
    Net::Http::Endpoint server(acceptFromAddress);
    server.init(options);
    server.setHandler(router.handler());
    server.serveThreaded();
    std::cout<<"Model test:"<<std::endl;
    Models::User user("FUCK");
    std::cout<<"User: "<<user.getName()<<std::endl;
    std::cout<<"Serving on port 3000"<<std::endl;
    std::cin.get();
}