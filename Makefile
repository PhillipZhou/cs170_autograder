all: sample_grader

sample_grader:autograder_main.c sample_program.c 
	gcc autograder_main.c sample_progam.c -o sample_grader
