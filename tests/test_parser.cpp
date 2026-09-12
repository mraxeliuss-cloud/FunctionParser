#include <catch2/catch_test_macros.hpp>
#include <numbers>

#include "Lexer/Lexer.h"
#include "Parser/Parser.h"

TEST_CASE("Prueba de los paréntesis")
{
    Parser parser;
    auto tokens = Lexer::Tokenizar("pi + (e - 1)");
    auto nodo = parser.ShuntingYard(tokens);
    CHECK(nodo->token.tipo == TokenType::ADD);
    CHECK(nodo->hijos[0]->token.getValorNumerico() == std::numbers::pi);
    CHECK(nodo->hijos[1]->token.tipo == TokenType::SUB);
    CHECK(nodo->hijos[1]->hijos[0]->token.getValorNumerico() == std::numbers::e);
    CHECK(nodo->hijos[1]->hijos[1]->token.getValorNumerico() == 1);
}

TEST_CASE("Precedencia sin paréntesis")
{
    Parser parser;
    auto tokens = Lexer::Tokenizar("3 + 4 * 2");
    auto nodo = parser.ShuntingYard(tokens);
    CHECK(nodo->token.tipo == TokenType::ADD);
    CHECK(nodo->hijos[0]->token.getValorNumerico() == 3);
    CHECK(nodo->hijos[1]->token.tipo == TokenType::MULT);
    CHECK(nodo->hijos[1]->hijos[0]->token.getValorNumerico() == 4);
    CHECK(nodo->hijos[1]->hijos[1]->token.getValorNumerico() == 2);
}