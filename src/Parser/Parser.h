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

    std::vector<std::variant<int, float, char, std::string>> parsear(const std::vector<Token> &);

    std::unique_ptr<Nodo> ShuntingYard(const std::vector<Token> &tokens);

    [[nodiscard]] int prioridad(const Token &token) const;
    [[nodiscard]] int aridad(const Token &token) const;
};