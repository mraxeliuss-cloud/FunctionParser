#pragma once

#include <string>
#include <memory>
#include <vector>

// Componentes públicos de la librería
#include <FunctionParser/Sample.h>
#include <FunctionParser/Range.h>

namespace FunctionParser
{
    inline namespace v1
    {
        class Expression
        {
        public:
            explicit Expression(const std::string &input);
            ~Expression();

            // Deshabilitar copia (el Impl contiene un unique_ptr no copiable)
            Expression(const Expression &) = delete;
            Expression &operator=(const Expression &) = delete;

            // Habilitar movimiento (eficiente)
            Expression(Expression &&) noexcept;
            Expression &operator=(Expression &&) noexcept;
            [[nodiscard]] double eval(double x, double y) const;
            [[nodiscard]] double eval(double x, double y, double z) const;
            [[nodiscard]] std::vector<Punto2D> evaluateMesh(const Rango2D &rango) const;
            [[nodiscard]] std::vector<Punto3D> evaluateMesh(const Rango3D &rango) const;
            [[nodiscard]] std::string dependentVariable() const;

        private:
            struct Impl;
            std::unique_ptr<Impl> pImpl;
        };

        [[nodiscard]] std::vector<Punto2D> evaluate_2d(const std::string &input, const Rango2D &rango);
        [[nodiscard]] std::vector<Punto3D> evaluate_3d(const std::string &input, const Rango3D &rango);

    }
}