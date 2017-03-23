#include <Models.h>

class iDatabaseSource
{
  public:
    virtual Models::User getUserByID(const int & id) = 0;
};