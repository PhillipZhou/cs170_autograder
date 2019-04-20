# CS 170 Autograder

This project will automatically grade your cs170 project 2.
You are responsible for creating a Makefile which incorporates grader_main.c

You should NOT modify this code in any way.

We suppress all output from your program and it will not be obvious why your 
code failed. Because of this we really recommend that you have a separate main
that you use for debugging, and copying individual tests over when you want to
debug them. You also really need to have your own test cases. 

This code represents a small sample of the tests we will run for your final 
grade on the project, passing all the tests does not guarantee your grade.

More tests may be made available soon, announcements will be made on piazza 
when new tests are released. 

If you think you are failing a test due to a bug in the autograder, please
make sure to test against the glibc pthread library first, you can do that
by running the "autograder_reference" executable that is created by this projects Makefile

The code is designed to not fail, even if the code it's testing crashes or 
hangs, if you do manage to break this autograder (I.E. you never get your
final score at the end) please send me an email: sgillen@ucsb.edu
