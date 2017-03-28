#include <iostream>
#include <pistache/endpoint.h>
#include <pistache/router.h>
#include <pistache/http.h>

#include <Models.h>
#include <RouteHandler.h>

#include <Mocks.h>

#include <JWT.h>
#include <Authenticator.h>

#include <ctime>
#include <sstream>

Mocks::DatabaseMock db;

int main (int argc , char ** argv){
    Net::Address acceptFromAddress(Net::Ipv4::any(),Net::Port(3000));
    auto options = Net::Http::Endpoint::options().threads(2);
    Net::Rest::Router router;
    RouteHandler handler(router);
    Net::Http::Endpoint server(acceptFromAddress);
    server.init(options);
    server.setHandler(router.handler());
    server.serveThreaded();

    std::cout<<std::endl<<"JWT generation test:"<<std::endl;
    std::map<std::string,std::string> payload;
    std::stringstream ss;
    ss << std::time(0);
    std::string expiration(ss.str());
    payload.insert({"exp",expiration});
  
    Authenticator auth;
    for(int i = 1;i<12;++i){
    std::string token = auth.generateToken(db.getUserByID(i)); 
    auth.authenticateUser(token);
    }

    std::cout<<std::endl<<"Serving on port 3000"<<std::endl;
    std::cin.get();
}