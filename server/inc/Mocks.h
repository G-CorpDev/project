#ifndef MOCK_HEADER
#define MOCK_HEADER

#include <map>

#include <Models.h>
#include <iDatabaseSource.h>

namespace Mocks{

    class UserMock{
        private:
            std::map<int,Models::User> users;

        public:
            UserMock();
            bool add(const std::pair<int,Models::User> & );
            Models::User operator[](const int & id);
    };

    class DatabaseMock : iDatabaseSource {
        private:
            UserMock users;
        public:
            Models::User getUserByID(const int & id);
    };

}
#endif