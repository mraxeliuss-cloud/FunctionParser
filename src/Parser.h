#pragma once

#include <string>
#include <vector>
#include <memory>
#include <variant>

#include "Nodo.h"
#include "Token.h"

class Parser
{
    private:

    public:
    Parser();
    ~Parser() = default;


    std::vector<std::variant<int, float, char, std::string>> parsear(const std::vector<Token>&);
    // No se que voy a devolver
    void evaluar(std::vector<std::unique_ptr<Nodo>>& AST) const;

};