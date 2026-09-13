#include "Parser.h"

#include <string>
#include <vector>
#include <memory>
#include <variant>
#include <stack>

#include "Token.h"
#include "Nodo.h"
#include "Excepciones.h"
namespace
{
    void desapilarOperador(std::stack<Token> &pilaOperadores,
                           std::stack<std::unique_ptr<Nodo>> &pilaOperandos)
    {
        auto sacado = pilaOperadores.top();
        pilaOperadores.pop();
        if (pilaOperandos.empty())
        {
            throw ErrorLexico("Error en el formato de la expresion", sacado.posicion);
        }
        auto hijoD = std::move(pilaOperandos.top());
        pilaOperandos.pop();
        if (pilaOperandos.empty())
        {
            throw ErrorLexico("Error en el formato de la expresion", sacado.posicion);
        }

        auto hijoI = std::move(pilaOperandos.top());
        pilaOperandos.pop();

        auto nodo = std::make_unique<Nodo>(sacado, std::move(hijoI), std::move(hijoD));
        pilaOperandos.push(std::move(nodo));
    }
    int prioridad(const Token &token)
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
        default:
            throw ErrorDeFormato("Hay un problema con la expresión", token.posicion);
        }
    }
    int aridad(const Token &token)
    {
        switch (token.tipo)
        {
        case TokenType::POW:
        case TokenType::NRT:
        case TokenType::LOG:
            return 2;

        case TokenType::SIN:
        case TokenType::COS:
        case TokenType::TAN:
        case TokenType::EXP:
            return 1;
        default:
            throw ErrorDeFormato("El token no es una funcion", token.posicion);
        }
    }
}
namespace Parser
{

    std::unique_ptr<Nodo> ShuntingYard(const std::vector<Token> &tokens)
    {
        std::stack<Token> pilaOperadores;
        std::stack<std::unique_ptr<Nodo>> pilaOperandos;

        for (const auto &elemento : tokens)
        {
            if (elemento.tipo == TokenType::ABRE_PARENTESIS)
            {
                pilaOperadores.push(elemento);
            }
            else if (elemento.tipo == TokenType::CIERRA_PARENTESIS)
            {
                while (!pilaOperadores.empty() && pilaOperadores.top().tipo != TokenType::ABRE_PARENTESIS)
                {
                    desapilarOperador(pilaOperadores, pilaOperandos);
                }
                // Eliminar el paréntesis de apertura
                if (pilaOperadores.empty())
                    throw ErrorParentesis("Hay un desbalance en los paréntesis de apertura", elemento.posicion);
                pilaOperadores.pop();
            }
            else if (elemento.tipo >= TokenType::POW && elemento.tipo <= TokenType::LOG)
            {
                throw ErrorEnDesarrollo("Las funciones aún no están implementadas");
            }
            else if (elemento.tipo >= TokenType::ADD && elemento.tipo <= TokenType::DIVIDE) // Esto son los operadores
            {
                while (!pilaOperadores.empty() && pilaOperadores.top().tipo != TokenType::ABRE_PARENTESIS && prioridad(pilaOperadores.top()) >= prioridad(elemento))
                {
                    desapilarOperador(pilaOperadores, pilaOperandos);
                }
                pilaOperadores.push(elemento);
            }
            else
            {
                auto nodo = std::make_unique<Nodo>(elemento, nullptr, nullptr);
                pilaOperandos.push(std::move(nodo));
            }
        }
        while (!pilaOperadores.empty())
        {
            if (pilaOperadores.top().tipo == TokenType::ABRE_PARENTESIS)
                throw ErrorParentesis("Hay un paréntesis sin cerrar", pilaOperadores.top().posicion);
            desapilarOperador(pilaOperadores, pilaOperandos);
        }
        if (pilaOperandos.empty())
        {
            throw ErrorDeNodos("Hay operandos incorrectos");
        }
        auto ultimoElemento = std::move(pilaOperandos.top());
        pilaOperandos.pop();
        if (!pilaOperandos.empty())
        {
            throw ErrorDeNodos("Hay operandos incorrectos");
        }
        return ultimoElemento;
    }
}