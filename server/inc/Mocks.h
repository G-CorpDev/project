#ifndef MOCK_HEADER
#define MOCK_HEADER

#include <map>
#include <vector>

#include <Models.h>
#include <iDatabaseSource.h>
#include <Results.h>

namespace Mocks{

    class UserMock{
        private:
            std::map<int,Models::User> users;
            int idcounter = 0;


        public:
            int getNextID();
            int getCurrentID();

            UserMock();
            bool add(const std::pair<int,Models::User> & );
            Models::User at(const int & id);
            std::vector<Models::User> getAllUsers();
    };

    class DatabaseMock : public iDatabaseSource {
        private:
            UserMock users;
        public:
            Models::User getUserByID(const int & id);
            Models::User getUserByCredentials(const std::string & username,const std::string & password);
            std::vector<Models::User> getAllUsers();
            Results::Database saveUser(const Models::User & user);
            Results::Database saveUser(const std::string & user,const std::string & username,const std::string & password);

    };

}
#endif