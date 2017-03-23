#include <iostream>
#include <pistache/endpoint.h>
#include <pistache/router.h>
#include <pistache/http.h>

#include <Models.h>
#include <RouteHandler.h>

#include <Mocks.h>

int main (int argc , char ** argv){
    Net::Address acceptFromAddress(Net::Ipv4::any(),Net::Port(3000));
    auto options = Net::Http::Endpoint::options().threads(2);
    Net::Rest::Router router;
    RouteHandler handler(router);
    Net::Http::Endpoint server(acceptFromAddress);
    server.init(options);
    server.setHandler(router.handler());
    server.serveThreaded();

    std::cout<<"Database Mock test:"<<std::endl;
    Mocks::DatabaseMock db;
    auto users = db.getAllUsers();
    for(auto it = users.cbegin();it!=users.cend();++it){
        std::cout<<(*it).getName()<<std::endl;
    }

    std::cout<<std::endl<<"Serving on port 3000"<<std::endl;
    std::cin.get();
}