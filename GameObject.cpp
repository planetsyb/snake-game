
#include "GameObject.h"

// Constructor
GameObject::GameObject(Point startPosition) {
    position = startPosition;
}

// Virtual destructor
GameObject::~GameObject() {
    // No dynamic memory is owned by this class.
}

// Return the current position
Point GameObject::getPosition() const {
    return position;
}

// Update the current position
void GameObject::setPosition(Point newPosition) {
    position = newPosition;
}

// Default display symbol
char GameObject::getSymbol() const {
    return '?';
}
