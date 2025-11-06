#ifndef SHAPE_FACTORY_TEMPLATE_HPP
#define SHAPE_FACTORY_TEMPLATE_HPP

#include <memory>
#include "../job04/shape.hpp"

template <typename ShapeType>
class ShapeFactory
{
public:
    static std::unique_ptr<Shape> createShape()
    {
        static_assert(std::is_base_of<Shape, ShapeType>::value, "ShapeType must be derived from Shape");
        return std::make_unique<ShapeType>();
    }
};

#endif // SHAPE_FACTORY_TEMPLATE_HPP