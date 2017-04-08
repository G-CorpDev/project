#ifndef INTERFACE_DATABASE_SOURCE
#define INTERFACE_DATABASE_SOURCE

#include <Models.h>
#include <Results.h>
#include <Sort.h>

class iDatabaseSource
{
  public:
    /*Returns an User model with the appropriate data, if the user is identified by the ID.
      Retruns an User(false) otherwise.*/
    virtual Models::User getUserByID(const int & id) = 0;

    /*Returns an User model with the appropriate data, if the credentials identify an User.
      Retruns an User(false) otherwise.*/
    virtual Models::User getUserByCredentials(const std::string &username,const std::string & password) = 0;

    /*Returns all Users in the database, sorted ascending by their id.*/
    virtual std::vector<Models::User> getAllUsers() = 0;

    /*Saves the new User into the database.
      Returns the appropriate Results::Database message (i.e. Results::Database::Ok on success).*/
    virtual Results::Database saveUser(const std::string & displayName,const std::string & username,const std::string & password) = 0;

    /*Returns the designated User's current Worksheet filled out with the Users perosnal records.*/
    virtual Models::Worksheet getUsersWorksheetByUserID(const int & id) = 0;

    /*Returns all Worksheet descriptions in the database, without actual data or details (i.e. the Weeks vector is empty), sorted according to the argument.*/
    virtual std::vector<Models::Worksheet> getAllWorksheets(const Sort & sortBy) = 0;

    /*Sets the User's current worksheet to the worksheet designated by the worksheet name. The User is designated by userID
      Returns the appropriate Results::Database message (i.e. Results::Database::Ok on success).*/
    virtual Results::Database selectWorksheetByWorksheetName(const int & userID,const std::string & worksheetName) = 0;

    /*Saves the Exercise record for the User identified by userID.
      Returns the appropriate Results::Database message (i.e. Results::Database::Ok on success).*/
    virtual Results::Database saveExercise(const int & userID,const int & week,const int & day,const Models::Workout::TimeOfDay & timeOfDay,const Models::Exercise & exercise) = 0;
};

#endif