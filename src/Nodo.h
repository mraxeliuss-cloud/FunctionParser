#pragma once

#include <memory>
#include <optional>
#include <vector>

#include "Token.h"

struct Nodo
{
    std::unique_ptr<Nodo> hijoI;
    std::unique_ptr<Nodo> hijoD;
    Token token;

    Nodo(Token token, std::unique_ptr<Nodo> hijoI, std::unique_ptr<Nodo> hijoD) 
        : token(token), hijoI(std::move(hijoI)), hijoD(std::move(hijoD)) {}
    // Usas move semantics porque no se pueden copiar los unique_ptr
    Token getToken() { return token; }
};
