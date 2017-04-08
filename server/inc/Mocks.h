#ifndef MOCK_HEADER
#define MOCK_HEADER

#include <map>
#include <vector>
#include <atomic>

#include <Models.h>
#include <iDatabaseSource.h>
#include <Results.h>
#include <Sort.h>

namespace Mocks{

    class UserMock{
        private:
            std::map<std::pair<std::string,std::string>,Models::User> users;
            std::atomic<int> idcounter;

        public:
            int getNextID();
            UserMock();
            bool add(const std::pair<std::pair<std::string,std::string>,Models::User> & );
            Models::User getUserByCredentials(const std::pair<std::string,std::string> & credentials);
            Models::User getUserByID(const int & id);
            std::vector<Models::User> getAllUsers();
    };

    class DatabaseMock : public iDatabaseSource {
        private:
            UserMock users;
        public:
            Models::User getUserByID(const int & id);
            Models::User getUserByCredentials(const std::string & username,const std::string & password);
            std::vector<Models::User> getAllUsers();
            Results::Database saveUser(const std::string & user,const std::string & username,const std::string & password);
            Models::Worksheet getUsersWorksheetByUserID(const int & id);
            std::vector<Models::Worksheet> getAllWorksheets(const Sort & sortBy);
            bool selectWorksheetByWorksheetName(const int & userID,const std::string & worksheetName);
            bool saveExercise(const int & userID,const int & week,const int & day,const Models::Workout::TimeOfDay & timeOfDay,const Models::Exercise & exercise);

    };

}
#endif