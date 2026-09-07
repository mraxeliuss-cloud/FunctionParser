#pragma once

#include <memory>
#include <vector>
#include <string>

#include "Sample.h"
#include "Range.h"

// Contrato público

namespace FunctionParser::v1
{
    // Implementación Pimpl (la implementación es privada y oculta al usuario)
    class Expression
    {
    public:
        explicit Expression(const std::string &expression); // Lanza Excepción si es inválida
        ~Expression();

        // Deshabilitar copia, habilitar movimiento
        Expression(const Expression &) = delete;
        Expression &operator=(const Expression &) = delete;
        Expression(Expression &&) noexcept;
        Expression &operator=(Expression &&) noexcept;

        // Métodos públicos de evaluación
        [[nodiscard]] double eval(double x, double y) const;
        [[nodiscard]] double eval(double x, double y, double z) const;

        // Evaluación de mallas (opcional, también podría ir en funciones libres)
        [[nodiscard]] std::vector<Punto3D> evaluateMesh(/* args de rango */) const;

    private:
        struct Impl;
        std::unique_ptr<Impl> pImpl;
    };

    // Funciones libres (si no quieres instanciar un objeto)
    [[nodiscard]] std::vector<Punto2D> evaluate_2d(const std::string &expr, const Rango2D& rango);
    [[nodiscard]] std::vector<Punto3D> evaluate_3d(const std::string &expr, const Rango2D& rango);

} // namespace