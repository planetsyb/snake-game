#ifndef SNAKE_H
#define SNAKE_H

#include "GameObject.h"
#include "Point.h"

// The four directions the snake can travel in.
enum class Direction { Up, Down, Left, Right };

/*
 * Snake - owns the snake's body, direction, movement and growth.
 *
 * The body is stored in a dynamically allocated array of Point (new[]).
 * body[0] is the HEAD, body[length - 1] is the TAIL.
 *
 * Because this class owns raw memory it follows the "Rule of Three":
 *   - destructor, copy constructor (deep copy) and copy assignment operator.
 */
class Snake : public GameObject {
private:
    Point*    body;           // dynamic array of segments
    int       length;         // how many segments are in use
    int       capacity;       // how many segments the array can hold
    Direction direction;      // direction used for the last move
    Direction nextDirection;  // direction requested by the player

    void ensureCapacity(int needed);                 // grows the array if needed
    static Point     stepFrom(const Point& p, Direction d);
    static Direction opposite(Direction d);

public:
    // Default arguments: Snake s;  Snake s(Point(5,5));  Snake s(Point(5,5), 4);
    Snake(Point start = Point(10, 10),
          int initialLength = 3,
          Direction dir = Direction::Right);

    Snake(const Snake& other);              // deep-copy constructor
    Snake& operator=(const Snake& other);   // deep-copy assignment
    ~Snake() override;                      // frees the dynamic array

    // ---- GameObject interface ----
    void update() override;                 // advances the snake by one step

    // ---- movement ----
    void move();                            // head steps forward, every segment follows
    void setDirection(Direction newDir);    // ignored if it would reverse the snake
    Direction getDirection() const;

    // ---- size changes ----
    void grow(int amount = 1);              // adds segments at the tail
    bool shrink(int amount = 1);            // removes segments (never below 1); false if nothing removed

    // ---- information ----
    Point getHead() const;
    Point getTail() const;
    int   getLength() const;
    Point getSegment(int index) const;      // throws std::out_of_range for a bad index
    bool  occupies(const Point& p) const;   // true if any segment is on p
    bool  hitsItself() const;               // true if the head is on another segment
};

#endif
