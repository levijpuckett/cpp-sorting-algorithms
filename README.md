# C++ Sorting Algorithm Visualizer
This repository contains a sorting algorithm visualizer.

## Building
To build the project, navigate to the top level of the repo, and use the following commands:

    cmake -H. -Btmp_cmake -DCMAKE_INSTALL_PREFIX=$INSTALL_DIRECTORY
    cmake --build tmp_cmake --clean-first --target install

Where INSTALL_DIRECTORY is the directory into which this software is to be installed.

To run a demonstration of this software, run the following command:

    $INSTALL_DIR/bin/demo

## Hints
The command line option --shuffle/-s allows the user to change the way the array is shuffled before it is sorted.
Valid options include:
    random : randomly shuffled.
    reverse : ordered, reversed array.
    half : half of the array is randomly shuffled.
    almost_sorted : the array is nearly sorted.
