#include "Parser.h"

#include <string>
#include <vector>
#include <memory>
#include <variant>
#include <stack>

#include "Token.h"
#include "Nodo.h"

void Parser::ShuntingYard(std::vector<Token> &tokens)
{
    std::stack<Token> pilaOperadores;
    std::stack<std::unique_ptr<Nodo>> pilaOperandos;
    for (const auto &elemento : tokens)
    {
        // Esto son los operadores
        if (elemento.tipo >= TokenType::ADD && elemento.tipo <= TokenType::DIVIDE)
        {
            while (!pilaOperadores.empty() && prioridad(pilaOperadores.top()) >= prioridad(elemento))
            {
                auto sacado = pilaOperadores.top();
                pilaOperadores.pop();
                auto hijoD = std::move(pilaOperandos.top());
                pilaOperandos.pop();
                auto hijoI = std::move(pilaOperandos.top());
                pilaOperandos.pop();
                auto nodo = std::make_unique<Nodo>(sacado, std::move(hijoI), std::move(hijoD));
                pilaOperandos.push(std::move(nodo));
            }
            pilaOperadores.push(elemento);
        }
        else // De momento asumimos que solo son operadores báscos o números
        {
            auto nodo = std::make_unique<Nodo>(elemento, nullptr, nullptr);
            pilaOperandos.push(std::move(nodo));
        }
    }
}

int Parser::prioridad(const Token &token) const
{
    switch (token.tipo)
    {
    case TokenType::ADD: // +
        return 1;
    case TokenType::SUB: // -
        return 1;
    case TokenType::MULT: // *
        return 2;
    case TokenType::DIVIDE: // /
        return 2;
    }
}