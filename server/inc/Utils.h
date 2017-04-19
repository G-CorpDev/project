#ifndef UTILS_HEADER
#define UTILS_HEADER

#include <jansson.h>

#include <algorithm>
#include <map>

#include <Models.h>

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

    /*!\param length the length of the random string
    \return a random string

    Generates a random string with the desired length*/
    std::string random_string(size_t length);

};
#endif