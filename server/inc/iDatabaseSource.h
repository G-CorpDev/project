#ifndef INTERFACE_DATABASE_SOURCE
#define INTERFACE_DATABASE_SOURCE

#include <Models.h>

class iDatabaseSource
{
  public:
    virtual Models::User getUserByID(const int & id) = 0;
    virtual std::vector<Models::User> getAllUsers() = 0;
};

#endif