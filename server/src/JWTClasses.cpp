#include <JWT.h>

#include <iostream>

JWT::SecretHandler::SecretHandler(const std::string &secret) : secret(secret)
{
    this->secret_raw = new unsigned char[this->secret.length()];
    int i = 0;
    for (char c : this->secret)
    {
        this->secret_raw[i] = (unsigned char)c;
        ++i;
    }
}

JWT::SecretHandler::~SecretHandler()
{
    if (this->secret_raw != 0)
    {
        delete this->secret_raw;
    }
}

const std::string JWT::Generator::generateJWT(const std::map<std::string, std::string> &payload)
{
    std::string token("Error generating JWT.");
    int err = 0;
    jwt_t *generator;
    err = jwt_new(&generator);
    err = jwt_set_alg(generator, JWT_ALG_HS256, this->secret_raw, this->secret.length());
    for (auto grant : payload)
    {
        err = jwt_add_grant(generator, grant.first.c_str(), grant.second.c_str());
        if(err!=0){return "Error adding grant: "+grant.first+":"+grant.second;}
    }

    char * token_tmp = jwt_encode_str(generator);
    token = std::string(token_tmp); 
    delete token_tmp;

    jwt_free(generator);

    return token;
}

const std::string &JWT::SecretHandler::getSecret() const
{
    return this->secret;
}

JWT::Generator::Generator(const std::string &secret) : SecretHandler(secret) {}

JWT::Verifier::Verifier(const std::string &secret) : SecretHandler(secret) {}

const std::map<std::string, std::string> JWT::Verifier::verifyJWT(const std::string &token)
{
    std::map<std::string, std::string> grants;
    int err = 0;
    jwt_t *verifier;

    err = jwt_decode(&verifier, token.c_str(), this->secret_raw, this->secret.length());
    if(err!=0){return grants;}
    char * decoded_tmp = jwt_dump_str(verifier, 0);

    if(decoded_tmp==0){std::cout<<decoded_tmp<<std::endl;}
    std::string decoded = std::string(decoded_tmp);
    delete decoded_tmp;
    std::string delimiter("}.{"); 
    decoded = decoded.substr(decoded.find(delimiter)+2);

    json_t *jsonParser;
    json_error_t jsonError;

    jsonParser = json_loads(decoded.c_str(), 0, &jsonError);

    if (!json_is_object(jsonParser))
    {
        json_decref(jsonParser);
        return grants;
    }

    const char * key;
    json_t *value;
    json_object_foreach(jsonParser,key,value){
        grants.insert({key,json_string_value(value)});
    }

    json_decref(jsonParser);
    jwt_free(verifier);
    return grants;
}