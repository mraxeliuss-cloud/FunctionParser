#pragma once

#include <string>
#include <vector>
#include <memory>
#include <variant>
#include <stack>

#include "Token.h"
#include "Nodo.h"

class Parser
{
private:
public:
    Parser();
    ~Parser() = default;

    std::vector<std::variant<int, float, char, std::string>> parsear(const std::vector<Token> &);

    void ShuntingYard(std::vector<Token> &tokens);

    int prioridad(const Token &token) const;
};