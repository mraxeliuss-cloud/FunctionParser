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
    // Por el momento 1-4
    POW,
    NRT,
    SIN,
    COS,
    TAN,
    EXP,
    LOG, // 11
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
    size_t posicion;

    // Constructor para números
    Token(double num, size_t pos) : tipo(TokenType::NUMERO), valor(num), posicion(pos) {}
    // Constructor para variables
    Token(char var, size_t pos) : tipo(TokenType::VARIABLE), valor(var), posicion(pos) {}
    // Constructor para tokens sin valor
    Token(TokenType t, size_t pos) : tipo(t), valor(0.0), posicion(pos) {}
};
