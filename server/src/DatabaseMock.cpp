#include <Mocks.h>

Models::User Mocks::DatabaseMock::getUserByID(const int & id){
    return users[id];
}