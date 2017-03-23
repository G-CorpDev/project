#include <Mocks.h>

Mocks::UserMock::UserMock()
{
    this->add(std::pair<int,Models::User>(1,"Jani"));
}

bool Mocks::UserMock::add(const std::pair<int, Models::User> & user){
    users.insert(user);
}
