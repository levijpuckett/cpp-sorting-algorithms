#include <cstdint>
#include "colour.hpp"

// Colour struct constructor
Colour::Colour(float r, float g, float b) : red(r), green(g), blue(b) {}

// Default constructor
// Always starts at red, headed to green.
colour_generator::colour_generator() : red_(255), green_(0), blue_(0), state(state::TO_GREEN) {}

// returns the next colour according to the current colour
// This funtion increments the colours in one direction only.
// Once all the colours have been exhausted (completing the colour wheel),
// This function returns false every time it is called.
// If the colour was successfully incremented, it returns true.
bool colour_generator::increment_colour()
{
    switch (state)
    {
    case state::TO_GREEN:
        if (green_ < 255) { green_ += 4; red_ -= 4; }
        else { state = state::TO_BLUE; }
        break;
    case state::TO_BLUE:
        if (blue_ < 255) { blue_ += 4; green_ -= 4; }
        else { state = state::TO_RED; }
        break;
    case state::TO_RED:
        if (red_ < 255) { red_ += 4; blue_ -= 4; }
        else { return false; }
        break;
    default:
        break;
    }
    return true;
}

float colour_generator::red() const { return red_ / 255.0f; }
float colour_generator::green() const { return green_ / 255.0f; }
float colour_generator::blue() const { return blue_ / 255.0f; }
