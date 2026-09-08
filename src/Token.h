#pragma once

#include <utility>
#include <variant>
#include <string>

enum class TokenType
{
    // OPERADORES
    IGUALDAD = 0,
    ADD,
    SUB,
    MULT,
    DIVIDE,
    POW,
    NRT,
    SIN,
    COS,
    TAN,
    EXP,
    LOG,
    // FIN OPERADORES

    ABRE_PARENTESIS,
    CIERRA_PARENTESIS,
    COMA,
    VARIABLE,
    NUMERO,
    FIN_SECUENCIA
    // En el readme, hay que acabar con ';'
};

struct Token
{
    TokenType tipo;
    std::variant<double, char> valor;

    // Constructor para números
    Token(double num) : tipo(TokenType::NUMERO), valor(num) {}
    // Constructor para variables
    Token(char var) : tipo(TokenType::VARIABLE), valor(var) {}
    // Constructor para tokens sin valor
    Token(TokenType t) : tipo(t), valor(0.0) {}
};
