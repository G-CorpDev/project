#ifndef INTERFACE_DATABASE_SOURCE
#define INTERFACE_DATABASE_SOURCE

#include <Models.h>
#include <Results.h>
#include <Sort.h>

/*! An interface defining the necessary functionality of the database.*/
class iDatabaseSource
{
  public:
    /*!
    \return the User identified by the ID
    
      Returns an User model with the appropriate data, if the user is identified by the ID.
      Retruns an User(false) otherwise.*/
    virtual Models::User getUserByID(const int & id) = 0;

    /*!
    \return the User identified by the credentials

      Returns an User model with the appropriate data, if the credentials identify an User.
      Retruns an User(false) otherwise.*/
    virtual Models::User getUserByCredentials(const std::string &username,const std::string & password) = 0;

    /*!
    \return vector of Models::User

    Returns all Users in the database, **sorted** ascending by their id.*/
    virtual std::vector<Models::User> getAllUsers() = 0;

    /*!
      \param displayName the chosen nickname of the new User
      \param username the login name of the new User
      \param password the password of the new User
      \return the appropriate Results::Database

      Saves the new User into the database.*/
    virtual Results::Database saveUser(const std::string & displayName,const std::string & username,const std::string & password) = 0;

    /*!
    \param id the User's ID
    \return the filled Models::Worksheet

    Returns the designated User's current Worksheet filled out with the Users perosnal records.*/
    virtual Models::Worksheet getUsersWorksheetByUserID(const int & id) = 0;

    /*!
    \param sortBy the property by which to sort the return value
    \return vector of Models::Worksheet
    
    Returns all Worksheet descriptions in the database, without actual data or details (i.e. the Weeks vector is empty), sorted according to the argument.*/
    virtual std::vector<Models::Worksheet> getAllWorksheets(const Sort & sortBy) = 0;

    /*!
      \param userID the Models::User's ID
      \param worksheetName the Models::Worksheet's name
      \return the appropriate Results::Database

      Sets the **User**'s current worksheet to the worksheet designated by the **worksheet name**.*/
    virtual Results::Database selectWorksheetByWorksheetName(const int & userID,const std::string & worksheetName) = 0;

    /*!
      \param userID the Models::User's ID
      \param week Which week
      \param day which day
      \param timeOfDay which time of the day
      \param exercise the Models::Exercise to save
      \return the appropriate Results::Database
    
      Saves the Exercise record for the **User** identified by **userID**.*/
    virtual Results::Database saveExercise(const int & userID,const int & week,const Models::Day::Days & day,const Models::Workout::TimeOfDay & timeOfDay,const Models::Exercise & exercise) = 0;
};

#endif