#ifndef SHAPE_FACTORY_HPP
#define SHAPE_FACTORY_HPP

#include <string>
#include <memory>
#include "../job04/shape.hpp"

class ShapeFactory
{
public:
    static std::unique_ptr<Shape> createShape(const std::string &type)
    {
        if (type == "circle")
        {
            return std::make_unique<Circle>();
        }
        else if (type == "rectangle")
        {
            return std::make_unique<Rectangle>();
        }
        return nullptr;
    }
};

#endif // SHAPE_FACTORY_HPP