# C++ Sorting Algorithm Visualizer
This repository contains a sorting algorithm visualizer, developed for the SENG 475 course at UVic: Advanced Programming Techniques for Robust Efficient Computing (With C++). The program demonstrates the internal workings of three popular sorting algorithms: bubble sort, insertion sort, and quick sort. The algorithms are shown sorting an array of colours.

A custom algorithm was developed for each of the three sorting methods, which shows 'snapshots' of each step of the sorting algorithm, allowing for a smooth comparison between sorting algorithms, as well as the possibility for easily adding more in the future - just add a function which sorts according to another algorithm and returns an array of snapshots for display.

GLUT is used to display the sorting process on screen.

The following video describes the program in more detail:

[![Video Presentation](https://img.youtube.com/vi/00L-4fra4Fg/0.jpg)](https://www.youtube.com/watch?v=00L-4fra4Fg)


## Building
To build the project, navigate to the top level of the repo, and use the following commands:

    cmake -H. -Btmp_cmake -DCMAKE_INSTALL_PREFIX=$INSTALL_DIRECTORY
    cmake --build tmp_cmake --clean-first --target install

Where `$INSTALL_DIRECTORY` is the directory into which this software is to be installed.

### Demonstration
To run a demonstration of this software, run the following command:

    $INSTALL_DIR/bin/demo

## Hints
The command line option `--shuffle`/`-s` allows the user to change the way the array is shuffled before it is sorted.

Valid options include:
* random : randomly shuffled.
* reverse : ordered, reversed array.
* half : half of the array is randomly shuffled.
* almost_sorted : the array is nearly sorted.
    
