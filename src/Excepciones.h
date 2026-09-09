#pragma once

#include <stdexcept>

struct ErrorLexico : std::runtime_error
{
    size_t posicion;
    ErrorLexico (const std::string &mensaje, size_t posicion) 
        : std::runtime_error(mensaje), posicion(posicion){}
};