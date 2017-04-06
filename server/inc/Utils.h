#include <jansson.h>
#include <Models.h>

#include <map>

namespace Utils{
    std::map<std::string,std::string> decodeSimpleJSON(const std::string & json);
    std::string makeSimpleJSON(const std::map<std::string,std::string> & data);
};