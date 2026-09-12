#include <catch2/catch_test_macros.hpp>
#include "Lexer/Lexer.h"

TEST_CASE("el lexer produce tres tokens para 2+3") {
    auto tokens = Lexer::Tokenizar("2+3");
    REQUIRE(tokens.size() == 3);
    REQUIRE(tokens[0].tipo == TokenType::NUMERO);
    REQUIRE(tokens[1].tipo == TokenType::ADD);
    REQUIRE(tokens[2].tipo == TokenType::NUMERO);
}

