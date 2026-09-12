#include <catch2/catch_test_macros.hpp>
#include <numbers>

#include "Lexer/Lexer.h"
#include "Parser/Parser.h"

TEST_CASE("Prueba de los paréntesis")
{
    Parser parser;
    auto tokens = Lexer::Tokenizar("pi + (e - 1)");
    auto nodo = parser.ShuntingYard(tokens);
    REQUIRE(tokens.size() == 7);
    REQUIRE(nodo->getToken().tipo == TokenType::ADD);
    REQUIRE(nodo->hijoI->getToken().valor == std::numbers::pi);
    REQUIRE(nodo->hijoD->getToken().tipo == TokenType::SUB);
    REQUIRE(nodo->hijoD->hijoI->getToken().valor == std::numbers::e);
    REQUIRE(nodo->hijoD->hijoD->getToken().valor == 1);
}