#include "Snake.h"
#include <stdexcept>

static const int MIN_LENGTH       = 1;    // the snake can never be shorter than this
static const int DEFAULT_CAPACITY = 16;   // starting size of the dynamic array

// ---------- private helpers ----------

Direction Snake::opposite(Direction d) {
    switch (d) {
        case Direction::Up:    return Direction::Down;
        case Direction::Down:  return Direction::Up;
        case Direction::Left:  return Direction::Right;
        default:               return Direction::Left;
    }
}

Point Snake::stepFrom(const Point& p, Direction d) {
    Point result = p;
    switch (d) {
        case Direction::Up:    result.y -= 1; break;
        case Direction::Down:  result.y += 1; break;
        case Direction::Left:  result.x -= 1; break;
        case Direction::Right: result.x += 1; break;
    }
    return result;
}

// If the array is too small, allocate a bigger one, copy, and free the old one.
void Snake::ensureCapacity(int needed) {
    if (needed <= capacity) return;

    int newCapacity = capacity;
    while (newCapacity < needed) newCapacity *= 2;

    Point* bigger = new Point[newCapacity];
    for (int i = 0; i < length; i++) {
        bigger[i] = body[i];
    }
    delete[] body;          // release the old array
    body = bigger;          // point to the new one
    capacity = newCapacity;
}

// ---------- constructors / destructor ----------

Snake::Snake(Point start, int initialLength, Direction dir)
    : GameObject(start),
      body(nullptr),
      length(0),
      capacity(0),
      direction(dir),
      nextDirection(dir) {

    if (initialLength < MIN_LENGTH) initialLength = MIN_LENGTH;

    length = initialLength;
    capacity = (initialLength > DEFAULT_CAPACITY) ? initialLength : DEFAULT_CAPACITY;
    body = new Point[capacity];

    // Head at 'start'; the other segments trail behind it.
    Point current = start;
    for (int i = 0; i < length; i++) {
        body[i] = current;
        current = stepFrom(current, opposite(dir));
    }
}

// Deep copy: the new snake gets its OWN array with the same contents.
Snake::Snake(const Snake& other)
    : GameObject(other),
      body(nullptr),
      length(other.length),
      capacity(other.capacity),
      direction(other.direction),
      nextDirection(other.nextDirection) {

    body = new Point[capacity];
    for (int i = 0; i < length; i++) {
        body[i] = other.body[i];
    }
}

// Same idea for "a = b;". We build the copy first so that nothing is lost if new[] fails.
Snake& Snake::operator=(const Snake& other) {
    if (this == &other) return *this;     // protect against a = a

    Point* newBody = new Point[other.capacity];
    for (int i = 0; i < other.length; i++) {
        newBody[i] = other.body[i];
    }

    delete[] body;                        // free the old array
    body = newBody;

    GameObject::operator=(other);         // copy the base-class part
    length = other.length;
    capacity = other.capacity;
    direction = other.direction;
    nextDirection = other.nextDirection;
    return *this;
}

Snake::~Snake() {
    delete[] body;
    body = nullptr;
}

// ---------- GameObject interface ----------

void Snake::update() {
    move();
}

// ---------- movement ----------

void Snake::move() {
    direction = nextDirection;

    // Segment following: from the tail to the neck, each segment takes the
    // place of the one in front of it. (Going backwards so nothing is overwritten.)
    for (int i = length - 1; i > 0; i--) {
        body[i] = body[i - 1];
    }

    // Then the head steps forward.
    body[0] = stepFrom(body[0], direction);
    position = body[0];                   // keep GameObject's position = head
}

void Snake::setDirection(Direction newDir) {
    // A snake longer than 1 cannot turn back into its own neck.
    if (length > 1 && newDir == opposite(direction)) return;
    nextDirection = newDir;
}

Direction Snake::getDirection() const {
    return direction;
}

// ---------- growing / shrinking ----------

void Snake::grow(int amount) {
    if (amount <= 0) return;

    ensureCapacity(length + amount);
    for (int i = 0; i < amount; i++) {
        body[length] = body[length - 1];  // new segment starts on the tail; it separates on the next move
        length++;
    }
}

bool Snake::shrink(int amount) {
    if (amount <= 0) return false;

    int newLength = length - amount;
    if (newLength < MIN_LENGTH) newLength = MIN_LENGTH;

    bool changed = (newLength != length);
    length = newLength;                   // the extra array space is simply left unused
    return changed;
}

// ---------- information ----------

Point Snake::getHead() const {
    return body[0];
}

Point Snake::getTail() const {
    return body[length - 1];
}

int Snake::getLength() const {
    return length;
}

Point Snake::getSegment(int index) const {
    if (index < 0 || index >= length) {
        throw std::out_of_range("Snake::getSegment - index out of range");
    }
    return body[index];
}

bool Snake::occupies(const Point& p) const {
    for (int i = 0; i < length; i++) {
        if (body[i] == p) return true;
    }
    return false;
}

bool Snake::hitsItself() const {
    for (int i = 1; i < length; i++) {
        if (body[i] == body[0]) return true;
    }
    return false;
}
