#pragma once

#include <string>
#include <vector>
#include <memory>
#include <variant>
#include <stack>

#include "Token.h"
#include "Nodo.h"

namespace Parser
{
    std::unique_ptr<Nodo> ShuntingYard(const std::vector<Token> &tokens);
};