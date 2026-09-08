// Namespace anónimo y oculto, solo como helper
#include "Token.h"

#include <cstddef>
#include <charconv>
#include <vector>
#include <unordered_map>
#include <string_view>
#include <algorithm>

namespace
{
    Token tokenNumero(const std::string &expresion, size_t &pos)
    {
        size_t start = pos;
        bool hayPunto = false;
        if (!(expresion[start] >= '0' && expresion[start] <= '9'))
        {
            // Error, no hay dígitos
        }
        while (pos < expresion.size() && ((expresion[pos] >= '0' && expresion[pos] <= '9') || expresion[pos] == '.'))
        {
            if (expresion[pos] == '.')
            {
                if (hayPunto)
                {
                    // Error, más de 1 punto
                }
                hayPunto = true;
            }
            pos++;
        }

        double numero;
        auto resultado = std::from_chars(expresion.data() + start, expresion.data() + pos, numero);
        if (resultado.ec != std::errc())
        {
            // Error de evaluación
        }
        return Token(numero);
    }
    //
    Token tokenSimbolo(const char caracter)
    {
        switch (caracter)
        {
        case '+':
            return Token(TokenType::ADD);
        case '-':
            return Token(TokenType::SUB);
        case '*':
            return Token(TokenType::MULT);
        case '/':
            return Token(TokenType::DIVIDE);
        default:
            // return Error no es operador
        }
    }
    Token tokenCaracterEspecial(const char caracter)
    {
        switch (caracter)
        {
        case ',':
            return Token(TokenType::COMA);
        case ';':
            return Token(TokenType::FIN_SECUENCIA);
        case '(':
            return Token(TokenType::ABRE_PARENTESIS);
        case ')':
            return Token(TokenType::CIERRA_PARENTESIS);
        case '=':
            return Token(TokenType::IGUALDAD);
        default:
            // return Error no es caracter especial
        }
    }

    // Mapeo de funciones
    static const std::unordered_map<std::string_view, TokenType> funcionMap = {
        // first es la string
        // second es el tokentype
        {"sin", TokenType::SIN},
        {"cos", TokenType::COS},
        {"tan", TokenType::TAN},
        {"exp", TokenType::EXP},
        {"log", TokenType::LOG},
        {"pow", TokenType::POW},
        {"nrt", TokenType::NRT}};

    Token tokenIdentificador(const std::string &expresion, size_t &posicion)
    {
        size_t start = posicion;

        // Delimitar la palabra
        while (posicion < expresion.size() && (expresion[posicion] >= 'a' && expresion[posicion] <= 'z'))
        {
            posicion++;
        }

        std::string_view palabra(expresion.data() + start, posicion - start);

        // it recibe valor si palabra está en el mapa
        auto it = funcionMap.find(palabra);
        // Está en el mapa
        if (it != funcionMap.end())
        {
            // Second es el TokenType
            return Token(it->second);
        }
        if (palabra == "x" || palabra == "y" || palabra == "z")
        {
            return Token(palabra[0]);
        }
        // throw error si no es ninguna
    }
    std::string &limpiarEspacios(std::string &expresion)
    {
        expresion.erase(std::remove_if(expresion.begin(), expresion.end(), ::isspace), expresion.end());
        return expresion;
    }
}
namespace Lexer
{

    std::vector<Token> Tokenizar(std::string &expresionInput)
    {
        std::string expresion = expresionInput;
        size_t i = 0;
        std::vector<Token> tokens;
        tokens.reserve(expresion.size() / 3);
        expresion = limpiarEspacios(expresion);
        while (i < expresion.size())
        {
            char c = expresion[i];
            if (std::isdigit(static_cast<unsigned char>(c)))
            {
                tokens.push_back(tokenNumero(expresion, i));
            }
            else if (std::isalpha(static_cast<unsigned char>(c)))
            {
                tokens.push_back(tokenIdentificador(expresion, i));
            }
            else if (c == '+' || c == '-' || c == '*' || c == '/')
            {
                tokens.push_back(tokenSimbolo(c));
                ++i;
            }
            else if (c == '(' || c == ')' || c == ',' || c == '=' || c == ';')
            {
                tokens.push_back(tokenCaracterEspecial(c));
                ++i;
            }
            else
            {
                // throw evaluation_error("Carácter inesperado en la expresión");
            }
        }
        return tokens;
    }
}
