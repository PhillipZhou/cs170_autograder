all: reference_grader

reference_grader:autograder_main.c 
	gcc autograder_main.c -o autograder_reference -lpthread
