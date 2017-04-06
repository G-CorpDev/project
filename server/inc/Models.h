#ifndef MODELS_HEADER
#define MODELS_HEADER

#include <string>

namespace Models{
    class User{
        private:
            std::string displayName;
            unsigned int id;

            const bool verified;

        public:
            const std::string & getDisplayName() const;
            unsigned int getID() const;
            bool isValid() const;
            User (const std::string & displayName,const unsigned int & id);
            User (bool verified);
    };
}
#endif