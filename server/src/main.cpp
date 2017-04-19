#include <iostream>
#include <pistache/endpoint.h>
#include <pistache/router.h>
#include <pistache/http.h>

#include <RouteHandler.h>

#include <Mocks.h>
#include <Models.h>

#include <JWT.h>
#include <Authenticator.h>

//NOTE: POSTs in Chrome are unreliable for some reason. Use Firefox.

//BUG: CLient: cant write note for the first exercise
//BUG: Client: if note is empty , server gets it as "note", if not its "Note" as an additional field

int main(int argc, char **argv)
{
    Net::Address acceptFromAddress(Net::Ipv4::any(), Net::Port(3000));
    auto options = Net::Http::Endpoint::options().threads(10).flags(Net::Tcp::Options::InstallSignalHandler);
    Net::Rest::Router router;
    Mocks::DatabaseMock database;
    RouteHandler handler(router, database);
    Net::Http::Endpoint server(acceptFromAddress);
    server.init(options);
    server.setHandler(router.handler());
    server.serveThreaded();
    /*
    std::cout<<std::endl<<"JWT generation test:"<<std::endl;
    Authenticator auth;
    std::string token = auth.generateToken(database.getUserByID(1)); 
    for(int i = 1;i<12;++i){
        token= auth.generateToken(database.getUserByID(i)); 
        Models::User user = auth.authenticateUser(token);
        std::cout<<"user "<<user.getID()<<" - "<< user.getDisplayName()<<", aged "<<user.getAge()<<std::endl;
    }

    Models::User user = auth.authenticateUser("u2i3hnez23czwiemhiar23zrhq8.sdu2mh7382f38sm98dtg2.3rh2f8rh2f3");
    std::cout<<"user "<<user.getID()<<" - "<< user.getDisplayName()<<std::endl;

    auto invalidUser = database.getUserByCredentials("sajt","fuck");
    auto validUser = database.getUserByCredentials("jófej","fuck");
    std::cout<<"Valid is"<<validUser.isValid()<<std::endl;
    std::cout<<"inValid is"<<invalidUser.isValid()<<std::endl;
*/

    std::cout << std::endl
              << "Serving on port 3000" << std::endl;
    std::cin.get();
    server.shutdown();
}