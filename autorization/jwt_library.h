#ifndef __JWT_LIBRARY__
#define __JWT_LIBRARY__

#include <boost/json.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <list>

#include <jwt-cpp/jwt.h>

namespace json = boost::json;

// secret key: the_holy_grail
// issuer : 
// game id:

std::string create_jwt( string user_id, string game_id )
{
    auto token_ = jwt::create()
    .set_type("JWS")
    .set_issuer(user_id)
    .set_payload_claim("game_id", jwt::claim(game_id))
    .sign(jwt::algorithm::hs256{"the_holy_grail"});

    return token_;
}

void verify_jwt( string user_id, string game_id , string msg )
{
    auto verifier = jwt::verify()
    .with_issuer(user_id)
    .with_claim("game_id", jwt::claim(game_id))
    .allow_algorithm(jwt::algorithm::hs256{"the_holy_grail"});
 
    verifier.verify(jwt::decode(msg));//<<std::endl;
}

void decode_jwt(std::string const token)
{
    auto decoded = jwt::decode(token);

    for(auto& e : decoded.get_payload_json())
        std::cout << e.first << " = " << e.second << '\n';
}


#endif