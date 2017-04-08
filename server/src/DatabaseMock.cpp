#include <Mocks.h>

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
    return Models::Worksheet(name, "Desc", "10 hours", "Balls to the Wall");
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

bool Mocks::DatabaseMock::selectWorksheetByWorksheetName(const int &userID, const std::string &worksheetName)
{
    //TODO:
}

bool Mocks::DatabaseMock::saveExercise(const int &userID, const int &week, const int &day, const Models::Workout::TimeOfDay &timeOfDay, const Models::Exercise &exercise)
{
    //TODO:
}
