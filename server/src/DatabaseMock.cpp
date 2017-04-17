#include <Mocks.h>

#include <iostream>

Models::User Mocks::DatabaseMock::getUserByID(const int &id)
{
    return users.getUserByID(id);
}

std::vector<Models::User> Mocks::DatabaseMock::getAllUsers()
{
    return users.getAllUsers();
}

Models::User Mocks::DatabaseMock::getUserByCredentials(const std::string &username, const std::string &password)
{
    return users.getUserByCredentials(std::make_pair(username, password));
}

Results::Database Mocks::DatabaseMock::saveUser(const std::string &displayName, const std::string &username, const std::string &password)
{
    users.add(std::make_pair(std::make_pair(username, password), Models::User(displayName, users.getNextID())));
    return Results::Database::Ok;
}

Models::Worksheet Mocks::DatabaseMock::getUsersWorksheetByUserID(const int &id)
{
    Models::User user = getUserByID(id);
    std::string name(user.getDisplayName());
    name.append("'s worksheet");
    Models::Worksheet sheet(name,"Work please.","1 egg","Like shitting bricks.");
    Models::Week week1;
    Models::Week week2;

    Models::Day monday1(Models::Day::Days::Monday);
    Models::Day tuesday1(Models::Day::Days::Tuesday);
    Models::Day wednesday1(Models::Day::Days::Wednesday);
    Models::Day thursday1(Models::Day::Days::Thursday);
    Models::Day friday1(Models::Day::Days::Friday);
    Models::Day monday2(Models::Day::Days::Monday);
    Models::Day tuesday2(Models::Day::Days::Tuesday);
    Models::Day wednesday2(Models::Day::Days::Wednesday);
    Models::Day thursday2(Models::Day::Days::Thursday);

    Models::Workout overwritten("SHOULD NOT APPEAR","get out of here",Models::Workout::TimeOfDay::Day,true,false);
    Models::Workout workout1("Lunch","Have lunch, fatass",Models::Workout::TimeOfDay::Day,true,false);
    Models::Workout workout2("Swim","So sharks can eat you",Models::Workout::TimeOfDay::Morning,true,true);
    Models::Workout workout3("Lift.","CRATESANDCRATESANDCRATESANDCRATES and smooth jazz",Models::Workout::TimeOfDay::Evening,false,false);
    Models::Exercise ex("pushup","",Models::Exercise::Type::RepsOnly,"10","0",false);
    Models::Exercise ex2("SOUPSUP","fatass",Models::Exercise::Type::JustDone,"","",true);
    Models::Exercise ex3("lose weight","FATASS!",Models::Exercise::Type::JustDone,"","",false);
    Models::Exercise ex4("lift bro","DYEL!",Models::Exercise::Type::RepsAndWeight,"5x5","50 moons",false);
    Models::Exercise ex5("lift bro","",Models::Exercise::Type::WeightOnly,"","",false);
    Models::Exercise ex6("lift bro","",Models::Exercise::Type::RepsOnly,"","",false);
    Models::Exercise ex7("leg day","",Models::Exercise::Type::JustDone,"","",false);
    
    workout1.addExercise(ex);
    workout1.addExercise(ex3);
    workout1.addExercise(ex2);
    workout1.addExercise(ex4);
    workout3.addExercise(ex5);
    workout3.addExercise(ex6);
    workout3.addExercise(ex7);
    monday1.addWorkout(overwritten);
    monday1.addWorkout(workout1);
    monday1.addWorkout(workout2);
    monday1.addWorkout(workout3);
    wednesday1.addWorkout(workout3);
    week1.addDay(monday1);
    week1.addDay(tuesday1);
    week1.addDay(wednesday1);
    week1.addDay(thursday1);
    week1.addDay(friday1);
    week2.addDay(monday1);
    week2.addDay(tuesday1);
    week2.addDay(wednesday1);
    week2.addDay(thursday1);
    sheet.addWeek(week1);
    sheet.addWeek(week2);
    return Models::Worksheet(sheet);
}

std::vector<Models::Worksheet> Mocks::DatabaseMock::getAllWorksheets(const Sort &sortBy)
{
    std::vector<Models::Worksheet> sheets;
    sheets.push_back(Models::Worksheet("Sheet1", "First sheet.", "20 mins", "Hard"));
    sheets.push_back(Models::Worksheet("Sheet2", "Second sheet.", "20 mins", "Easy"));
    sheets.push_back(Models::Worksheet("Sheet3", "Third sheet.", "10 mins", "Extreme"));
    sheets.push_back(Models::Worksheet("Sheet4", "Fourth sheet.", "40 mins", "JUST"));
    sheets.push_back(Models::Worksheet("Sheet7", "Seventh sheet.", "20 mins", "Hard"));
    sheets.push_back(Models::Worksheet("Sheet5", "Fifth sheet.", "60 mins", "Extreme"));
    sheets.push_back(Models::Worksheet("Sheet6", "Sixth sheet.", "20 mins", "Hard"));
    return sheets;
}

Results::Database Mocks::DatabaseMock::selectWorksheetByWorksheetName(const int &userID, const std::string &worksheetName)
{   //DEBUG:
    std::cout<<"User "<<userID<<" changed worksheet to "<<worksheetName<<std::endl;
    return Results::Database::Ok;
}

Results::Database Mocks::DatabaseMock::saveExercise(const int &userID, const int &week, const Models::Day::Days &day, const Models::Workout::TimeOfDay &timeOfDay, const Models::Exercise &exercise)
{
    return Results::Database::Ok;   
}
