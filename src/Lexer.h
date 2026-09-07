#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <cstddef>
#include <charconv>

#include "Token.h"

namespace Lexer
{

    std::string &limpiarEspacios(std::string &expresion)
    {
        expresion.erase(std::remove_if(expresion.begin(), expresion.end(), ::isspace), expresion.end());
        return expresion;
    }
    std::vector<Token> Tokenizar(std::string &expresion)
    {
        std::vector<Token> listaTokens;
        listaTokens.reserve(expresion.size() / 3);
        expresion = limpiarEspacios(expresion);
        static const std::unordered_map<std::string_view, TokenType> funcionMap = {
            {"sin", TokenType::SIN},
            {"cos", TokenType::COS},
            {"tan", TokenType::TAN},
            {"exp", TokenType::EXP},
            {"log", TokenType::LOG},
            {"pow", TokenType::POW},
            {"nrt", TokenType::NRT} // Raíz enésima: nrt(base, indice)
        };

        for (size_t i = 0; i < expresion.size(); i++)
        {
            // Buscar el ';'
            if (expresion[i] >= '0' && expresion[i] <= '9')
            {
                int j = i;
                bool hayPunto = false;
                while (j < expresion.size() && ((expresion[j] >= '0' && expresion[j] <= '9') || expresion[j] == '.'))
                {
                    if (expresion[j] == '.')
                    {
                        if (hayPunto)
                        {
                            // Error por puntos decimales
                        }
                        hayPunto = true;
                    }
                    j++;
                }
                double numero;
                auto resultado = std::from_chars(expresion.data() + i, expresion.data() + j, numero);
                if (resultado.ec != std::errc())
                {
                    // Error de evaluación
                }
                listaTokens.push_back(Token(numero));
                i = j - 1;
            }
        }
    }
}