#ifndef MOCK_HEADER
#define MOCK_HEADER

#include <map>
#include <vector>

#include <Models.h>
#include <iDatabaseSource.h>

namespace Mocks{

    class UserMock{
        private:
            std::map<int,Models::User> users;
            int idcounter = 0;

            int getNextID();

        public:
            int getCurrentID();

            UserMock();
            bool add(const std::pair<int,Models::User> & );
            Models::User at(const int & id);
            std::vector<Models::User> getAllUsers();
    };

    class DatabaseMock : iDatabaseSource {
        private:
            UserMock users;
        public:
            Models::User getUserByID(const int & id);
            std::vector<Models::User> getAllUsers();
    };

}
#endif