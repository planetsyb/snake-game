#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Point.h"

class GameObject {
protected:
    Point position;

public:
    GameObject(Point startPosition = Point());
    virtual ~GameObject();

    virtual void update();

    Point getPosition() const;
    void setPosition(Point newPosition);
    virtual char getSymbol() const;
};

#endif