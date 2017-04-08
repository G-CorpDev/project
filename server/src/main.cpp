#include <iostream>
#include <pistache/endpoint.h>
#include <pistache/router.h>
#include <pistache/http.h>

#include <RouteHandler.h>

#include <Mocks.h>
#include <Models.h>

#include <JWT.h>
#include <Authenticator.h>

#include <Sort.h>

//NOTE: POSTs in Chrome are unreliable for some reason. Use Firefox.

int main (int argc , char ** argv){
    Net::Address acceptFromAddress(Net::Ipv4::any(),Net::Port(3000));
    auto options = Net::Http::Endpoint::options().threads(10);
    Net::Rest::Router router;
    Mocks::DatabaseMock database;
    RouteHandler handler(router,database);
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
/*  
    Models::Worksheet sheet("Test sheet","Work please.","1 egg","Like shitting bricks.");
    Models::Week week1;
    Models::Week week2;
    Models::Day monday1(Models::Day::Days::Monday);
    Models::Day tuesday1(Models::Day::Days::Tuesday);
    Models::Day wednesday1(Models::Day::Days::Wednesday);
    Models::Day monday2(Models::Day::Days::Monday);
    Models::Workout overwritten("SHOULD NOT APPEAR","get out of here",Models::Workout::TimeOfDay::Day,true);
    Models::Workout workout1("Lunch","Have lunch, fatass",Models::Workout::TimeOfDay::Day,false);
    Models::Workout workout2("Swim","So sharks can eat you",Models::Workout::TimeOfDay::Morning,true);
    Models::Exercise ex("pushup","",Models::Exercise::Type::RepsOnly,"10","0",false);
    Models::Exercise ex2("SOUPSUP","fatass",Models::Exercise::Type::JustDone,"","",true);
    Models::Exercise ex3("lose weight","FATASS!",Models::Exercise::Type::JustDone,"","",false);
    Models::Exercise ex4("lift bro","DYEL!",Models::Exercise::Type::RepsAndWeight,"5x5","50 moons",false);
    
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
    std::cout<<sheet.toJSON()<<std::endl;
*/
    std::cout<<std::endl<<"Serving on port 3000"<<std::endl;
    std::cin.get();
    server.shutdown();
}