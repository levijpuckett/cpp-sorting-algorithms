#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <chrono>
#include <thread>
#include <GL/freeglut.h>

#include "colour.hpp"
#include "bubble_sort.hpp"
#include "insertion_sort.hpp"
#include "quick_sort.hpp"

// colour_array stores all the colours in order.
std::vector<Colour> colour_array;

// unsorted_array is shuffled randomly, and used for each of the sorting algorithms.
std::vector<int> unsorted_array;

// Each sorting algorithm has three associated arrays:
//  - snapshots: an array of arrays which holds an array showing 
//    the state of sorting at each iteration of the algorithm
//  - screen_current holds what is currently on screen. This allows
//    the display refresh function to only update what is different
//    with each iteration.
//  - _array: stores the current snapshot
//
// Bubble sort
std::vector<std::vector<int>> bubble_sort_snapshots;
std::vector<int> bubble_sort_array; // The array to be sorted by bubble sort
std::vector<int> screen_current_bubble; // what is currently on screen for the bubble sort

// Insertion sort
std::vector<std::vector<int>> insertion_sort_snapshots;
std::vector<int> insertion_sort_array; // The array to be sorted by insertion sort
std::vector<int> screen_current_insertion; // what is currently on screen for the insertion sort

// Quick sort
std::vector<std::vector<int>> quick_sort_snapshots;
std::vector<int> quick_sort_array; // The array to be sorted by insertion sort
std::vector<int> screen_current_quick; // what is currently on screen for the insertion sort

// full_refresh is used to tell the display update function that the entire screen needs to
// be redrawn.
bool full_refresh;

// screen_width and screen_height store the window size for the GUI. It is set to nearly the full 
// screen if possible, and will default to a smaller size if the screen size is unknown.
int screen_width;
int screen_height;

// render_text
// this is a helper function which renders text to the screen buffer.
// (x,y) is the top left of the text, font is the GLUT bitmap font, and text
// is a pointer to the text.
void render_text(float x, float y, void * font, char const * text)
{
    glColor3f(1,1,1);
    glRasterPos2f(x, y);
    for (int i = 0; text[i] != '\0'; ++i)
    {
        glutBitmapCharacter(font, text[i]);
    }
}

// display_refresh is the display callback for GLUT.
// It is responsible for rendering all onscreen content.
// if full_refresh is true, the entire screen is redrawn.
// otherwise, display_refresh will only draw anything new that needs to be updated onscreen.
void display_refresh()
{
    if (full_refresh)
    {
        // Clear the screen
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Render the onscreen text.
        render_text(-0.11, 0.9, GLUT_BITMAP_TIMES_ROMAN_24, "Bubble Sort");
        render_text(-0.12, 0.24, GLUT_BITMAP_TIMES_ROMAN_24, "Insertion Sort");
        render_text(-0.10, -0.42, GLUT_BITMAP_TIMES_ROMAN_24, "Quick Sort");
    }
 
    float pos = -static_cast<float>(colour_array.size()) / 2.0f; // x-axis position of the current colour
    for (std::size_t i = 0; i < colour_array.size(); ++i, ++pos)
    {
        // Only update the display if something has changed.
        if ((screen_current_bubble[i] != bubble_sort_array[i]) || full_refresh)
        {
            // Grab the colour from the colour array
            Colour c = colour_array[bubble_sort_array[i]];
            glColor3f(c.red, c.green, c.blue);
            // Draw the colour bar
            glRectd(pos / (colour_array.size() / 2), 0.3, (pos+1) / (colour_array.size() / 2), 0.88);
            // Update screen_current
            screen_current_bubble[i] = bubble_sort_array[i];
        }
        if ((screen_current_insertion[i] != insertion_sort_array[i]) || full_refresh)
        {
            // Grab the colour from the colour array
            Colour c = colour_array[insertion_sort_array[i]];
            glColor3f(c.red, c.green, c.blue);
            // Draw the colour bar
            glRectd(pos / (colour_array.size() / 2), -0.34, (pos+1) / (colour_array.size() / 2), 0.22);
            // Update screen_current
            screen_current_insertion[i] = insertion_sort_array[i];
        }
        if ((screen_current_quick[i] != quick_sort_array[i]) || full_refresh)
        {
            // Grab the colour from the colour array
            Colour c = colour_array[quick_sort_array[i]];
            glColor3f(c.red, c.green, c.blue);
            // Draw the colour bar
            glRectd(pos / (colour_array.size() / 2), -0.98, (pos+1) / (colour_array.size() / 2), -0.44);
            // Update screen_current
            screen_current_quick[i] = quick_sort_array[i];
        }
    }
    full_refresh = false;
    glutSwapBuffers(); // Show the updates
}

// Don't allow reshaping, simplifies text sizing.
void reshape(int,int)
{
    full_refresh = true;
    //glViewport(0,0,1024,512);
    glViewport(0,0,screen_width,screen_height);
    glutPostRedisplay();
}

// GLUT timer callback
// When the timer expires, this function is called.
// it updates the arrays for each sorting algorithm, updating the screen to show each step.
void timer(int)
{
    static size_t i = 0;
    if (i < bubble_sort_snapshots.size())
    {
        bubble_sort_array = bubble_sort_snapshots[i]; 
        glutPostRedisplay();
    }
    if (i < insertion_sort_snapshots.size())
    {
        insertion_sort_array = insertion_sort_snapshots[i];
        glutPostRedisplay();
    }
    if (i < quick_sort_snapshots.size())
    {
        quick_sort_array = quick_sort_snapshots[i];
        glutPostRedisplay();
    }
    ++i;
    if (i == 1) { full_refresh = true; }
    glutTimerFunc(3, timer, 1); // Schedule the timer again. This makes the period 10ms
}

void usage_printout(char ** argv)
{ 
    std::cout << "Usage" << std::endl;
    std::cout << argv[0] << " [options]" << std::endl << std::endl;
    std::cout << "Options" << std::endl;
    std::cout << "--shuffle/-s <shuffle_type> - ";
    std::cout << "Specify the way the array is shuffled. Valid options are:" << std::endl;;
    std::cout << "\t\t\t\trandom : randomly shuffled." << std::endl;
    std::cout << "\t\t\t\treverse : ordered, reversed array." << std::endl;
    std::cout << "\t\t\t\thalf : half of the array is randomly shuffled." << std::endl;
    std::cout << "\t\t\t\talmost_sorted : the array is nearly sorted." << std::endl;
}

int main(int argc, char ** argv)
{
    // Parse command line options
    int shuffle = 0;
    if (argc != 1 && argc != 3)
    {
        // Wrong number of arguments. must be either 1 or 3
        usage_printout(argv);
        return 1;
    }
    if (argc == 3)
    {
        std::string arg_option(argv[1]);
        if (arg_option == "--shuffle" || arg_option == "-s")
        {
            std::string shuffle_type(argv[2]);
            if (shuffle_type == "random") { shuffle = 0; }
            else if (shuffle_type == "reverse") { shuffle = 1; }
            else if (shuffle_type == "half") { shuffle = 2; }
            else if (shuffle_type == "almost_sorted") { shuffle = 3; }
            else
            {
                // Invalid shuffle type
                usage_printout(argv);
                return 1;
            }
        }
        else
        {
            // Invalid option
            usage_printout(argv);
            return 1;
        }
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    // Find the screen width and height
    screen_width = glutGet(GLUT_SCREEN_WIDTH);
    screen_height = glutGet(GLUT_SCREEN_HEIGHT);
    if (screen_width && screen_height)
    {
        // if the screen size is known, use it
        screen_height -= 100;
    }
    else
    {
        // if the screen size is unknown, use a default size
        screen_width = 1024;
        screen_height = 512;
    }

    // Initialize window, set callbacks
    glutInitWindowSize(screen_width, screen_height);
    glutCreateWindow("Sorting Visualizer");
    glutDisplayFunc(display_refresh);
    glutReshapeFunc(reshape);

    // colour_generator is used to gather all the colours into an ordered array.
    colour_generator gen;
    do
    {
        colour_array.emplace_back(gen.red(), gen.green(), gen.blue());
    }
    while (gen.increment_colour());

    // initialize the unsorted array
    unsorted_array.resize(colour_array.size());
    std::iota(unsorted_array.begin(), unsorted_array.end(), 0);
    std::srand(std::time(0)); // seed rng

    // Shuffle the array in the requested manner.
    switch (shuffle)
    {
    case 0:
        // shuffle randomly
        std::random_shuffle(unsorted_array.begin(), unsorted_array.end());
        break;
    case 1:
        // reverse
        std::reverse(unsorted_array.begin(), unsorted_array.end());
        break;
    case 2:
        // half sorted
        std::random_shuffle(unsorted_array.begin() + unsorted_array.size()/2, unsorted_array.end());
        break;
    case 3:
        // almost sorted
        std::random_shuffle(unsorted_array.begin() + 7*unsorted_array.size()/8, unsorted_array.end());
        break;
    default:
        // shuffle randomly
        std::random_shuffle(unsorted_array.begin(), unsorted_array.end());
        break;
    }
 
    // initialize the screen arrays
    screen_current_bubble.resize(colour_array.size());
    screen_current_insertion.resize(colour_array.size());
    screen_current_quick.resize(colour_array.size());

    // Initialize the storage arrays with the unsorted array
    bubble_sort_array = unsorted_array;
    insertion_sort_array = unsorted_array;
    quick_sort_array = unsorted_array;

    // Gather the collection of snapshots by sorting the array
    bubble_sort_snapshots = bubble_sort(unsorted_array);
    insertion_sort_snapshots = insertion_sort(unsorted_array);
    quick_sort_snapshots = quick_sort(unsorted_array);

    // start the timer, expires in 1s
    glutTimerFunc(1000, timer, 1);

    // Pass control to GLUT
    glutMainLoop();
}
