#ifndef MODELS_HEADER
#define MODELS_HEADER

#include <string>

namespace Models{
    class User{
        private:
            std::string displayName;
            int age;
            float weight;
            float height;
            int sex;
            unsigned int id;
        public:
            const std::string & getDisplayName() const;
            unsigned int getID() const;
            User (const std::string & displayName,const int & age,const float & weight,const float & height,const int & sex,const unsigned int & id);
    };
}
#endif