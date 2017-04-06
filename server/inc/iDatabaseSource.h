#ifndef INTERFACE_DATABASE_SOURCE
#define INTERFACE_DATABASE_SOURCE

#include <Models.h>
#include <Results.h>

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

    /*Updates the data of the appropriate User in the database.
      Returns the appropriate Results::Database message (i.e. Results::Database::Ok on success).*/
    virtual Results::Database saveUser(const Models::User & user) = 0;

    /*Saves the new User into the database.
      Returns the appropriate Results::Database message (i.e. Results::Database::Ok on success).*/
    virtual Results::Database saveUser(const std::string & displayName,const std::string & username,const std::string & password) = 0;
};

#endif