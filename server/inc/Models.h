#ifndef MODELS_HEADER
#define MODELS_HEADER

#include <string>

namespace Models{
    class User{
        private:
            std::string name;
            int id;
        public:
            const std::string & getName() const;
            int getID() const;
            User (const std::string & name,const int & id);
    };
}
#endif