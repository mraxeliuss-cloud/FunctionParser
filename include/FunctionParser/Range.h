#pragma once
#include <cstddef>

namespace FunctionParser::v1
{

    struct Rango2D
    {
        double x_min = 0.0;
        double x_max = 1.0;
        std::size_t x_pasos = 100;

        double y_min = 0.0;
        double y_max = 1.0;
        std::size_t y_pasos = 100;
    };

    struct Rango3D
    {
        double x_min = 0.0;
        double x_max = 1.0;
        std::size_t x_pasos = 50;

        double y_min = 0.0;
        double y_max = 1.0;
        std::size_t y_pasos = 50;

        double z_min = 0.0;
        double z_max = 1.0;
        std::size_t z_pasos = 50;
    };

}