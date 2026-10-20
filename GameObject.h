
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Point.h"

class GameObject {
protected:
    Point position;

public:
    // Constructor
    GameObject(Point startPosition = Point());

    // Virtual destructor
    virtual ~GameObject();

    // Get the object's position
    Point getPosition() const;

    // Change the object's position
    void setPosition(Point newPosition);

    // Get the character used to display the object
    virtual char getSymbol() const;
};

#endif