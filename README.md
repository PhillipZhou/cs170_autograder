
# CS 170 Thread Library Autograder
This project will automatically grade your cs170 thread projects.

Each directory contains a main function that will run a suite of tests on your 
code. After the deadline we will release the private tests which were used for 
your grade. 

You are responsible for creating a Makefile which incorporates the autograder main

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
The public tests given here represent about half of your grade. So if you get 8/8
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

The grader is designed to be robust to crashes and hangs in the code under
test. If you do manage to break this autograder (I.E. you never get your
final score at the end) please send me an email: sgillen@ucsb.edu
