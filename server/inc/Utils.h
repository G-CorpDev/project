#ifndef UTILS_HEADER
#define UTILS_HEADER

#include <jansson.h>
#include <Models.h>

#include <map>
/*! A namespace containing utility functions.*/
namespace Utils{
    /*!\param json A JSON object's string representation.
        \return A map with key-value pairs.
        
        Parses a JSON string into a map. The JSON may only be one level, and may only contain integers, booleans and strings.
        Booleans and integers will be converted to a string representation.*/ 
    std::map<std::string,std::string> decodeSimpleJSON(const std::string & json);

    /*!\param data A map with key-value pairs.
        \return A string representation of a JSON

        Takes the key-value pairs of the **data** parameter and emplaces them in a JSON object.*/
    std::string makeSimpleJSON(const std::map<std::string,std::string> & data);
};
#endif