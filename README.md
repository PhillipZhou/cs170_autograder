
# CS 170 Thread Library Autograder
This project will automatically grade your cs170 thread library.
You are responsible for creating a Makefile which incorporates autograder_main.c
see the Makefile and sample_pthread.c for one example of that. 

We advise you to NOT modify this code in any way. If you want please create
copy of autograder_main.c or just copy the individual tests.

## Suggested workflow
The intention was to have you compile autograder_main.c into your own program.
We suggest you copy autograder_main.c into your own project directory. 
This program was not intended to help you debug at all. We recommend 
that you copy tests you want to test over to a separate debugging main.c file
(you can create a Makefile that outputs two executables, if you want).
We grouped all the variables and helper functions needed for each test together. 

## Disclaimer
The tests given here represent about half of your grade. So if you get 8/8
tests correct you can be sure you got at least for 50% of the total points. 
Because of this it is essential that you have your own test cases, and 
that you carefully read the project spec.

## Design Notes
We chose to intentionally put all the tests and the autograder itself in 
a single C file. This was to make it very easy for the student to compile
everything, and not exposing everything in a header prevents polluting the
global namespace. Furthermore we figured students who want to call an 
individual test for debugging purposes would want to add print statements 
anyway. 

We did everything in C++ compatible C code for maximum compatibility. 

The code is designed to not fail, even if the code it's testing crashes or 
hangs, if you do manage to break this autograder (I.E. you never get your
final score at the end) please send me an email: sgillen@ucsb.edu
