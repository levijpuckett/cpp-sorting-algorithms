#ifndef COLOUR_HPP_
#define COLOUR_HPP_
#include <cstdint>

// Holds a GLUT-friendly RGB colour.
struct Colour
{
    Colour(float r, float g, float b);

    float red;
    float green;
    float blue;
};

// The colour_generator class is used to store RGB values for display onscreen.
// The values are returned in a GLUT-friendly format, as a float between 0-1.
// This class is intended as a way to generate an ordered array with colour values.
// The order is defined similar to traversing a colour wheel, starting and ending at red.
class colour_generator
{
public:
    // Default constructible only.
    // Always starts at red, headed to green.
    colour_generator();

    // Not copyable or movable
    colour_generator(const colour_generator&) = delete;
    colour_generator& operator=(const colour_generator&) = delete;
    colour_generator(colour_generator&&) = delete;
    colour_generator& operator=(colour_generator&&) = delete;

    // returns the next colour according to the current colour
    // This funtion increments the colours in one direction only.
    // Once all the colours have been exhausted (completing the colour wheel),
    // This function returns false every time it is called.
    // If the colour was successfully incremented, it returns true.
    bool increment_colour();
    
    float red() const;
    float green() const;
    float blue() const;

private:
    int red_;
    int green_;
    int blue_;
    enum class state
    {
        TO_GREEN,
        TO_BLUE,
        TO_RED
    } state;
};
#endif /* COLOUR_HPP_ */
