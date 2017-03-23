#ifndef MODELS_HEADER
#define MODELS_HEADER

#include <string>

namespace Models{
    class User{
        private:
            std::string name;
        public:
            std::string getName();
            User (std::string name);
    };
}
#endif