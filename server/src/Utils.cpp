#include <Utils.h>

std::map<std::string, std::string> Utils::decodeSimpleJSON(const std::string &json)
{
    std::map<std::string, std::string> grants;
    json_t *jsonParser;
    json_error_t jsonError;

    jsonParser = json_loads(json.c_str(), 0, &jsonError);

    if (!json_is_object(jsonParser))
    {
        json_decref(jsonParser);
        return grants;
    }

    const char *key;
    json_t *value;
    json_object_foreach(jsonParser, key, value)
    {
        if (json_is_string(value))
        {
            grants.insert({key, json_string_value(value)});
            continue;
        }
        if (json_is_boolean(value))
        {
            if (json_is_false(value))
            {
                grants.insert({key, "false"});
            }
            else
            {
                grants.insert({key, "true"});
            }
            continue;
        }
        if (json_is_integer(value))
        {
            grants.insert({key, std::to_string(json_integer_value(value))});
        }
    }

    json_decref(jsonParser);
    return grants;
}

std::string Utils::makeSimpleJSON(const std::map<std::string, std::string> &data)
{
    json_t *root = json_object();

    for (auto &entry : data)
    {
        json_object_set_new(root, entry.first.c_str(), json_string(entry.second.c_str()));
    }

    char *raw = json_dumps(root, 0);
    std::string json(raw);
    delete raw;

    json_decref(root);
    return json;
}