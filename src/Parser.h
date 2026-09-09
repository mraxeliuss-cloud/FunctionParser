#pragma once

#include <string>
#include <vector>
#include <memory>
#include <variant>

#include "Token.h"

class Parser
{
    private:

    public:
    Parser();
    ~Parser() = default;


    std::vector<std::variant<int, float, char, std::string>> parsear(const std::vector<Token>&);
    // No se que voy a devolver
    /*
        Shunting yard
        Construir el AST durante el propio parseing
        2 vectores pila.
    */
    void parsear(std::vector<Token>& AST) const;

};