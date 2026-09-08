#pragma once

#include <vector>
#include <string>

#include "Token.h"

namespace Lexer {
    std::vector<Token> Tokenizar(const std::string& expresion);
}