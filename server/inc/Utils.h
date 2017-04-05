#include <jansson.h>
#include <Models.h>

#include <map>

namespace Utils{
    std::map<std::string,std::string> decodeJSON(const std::string & json);
    std::string makeJSON(const std::map<std::string,std::string> & data);
};