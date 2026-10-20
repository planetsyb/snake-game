
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Point.h"

class GameObject {
protected:
    Point position;

public:
    explicit GameObject(Point startPosition = Point())
        : position(startPosition) {
    }

    virtual ~GameObject() = default;

    Point getPosition() const {
        return position;
    }

    void setPosition(Point newPosition) {
        position = newPosition;
    }

    virtual char getSymbol() const {
        return '?';
    }

    virtual void update() {
    }
};

#endif
