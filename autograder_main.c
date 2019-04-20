/**
 * Sean Gillen April 2019
 *
 * This file will automatically grade your cs170 project 2.
 * Please see the Readme for more info.
 */


#include  <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <poll.h>
#include <signal.h>
#include <fcntl.h>

#define NUM_TESTS 6
#define PASS 1
#define FAIL 0
#define THREAD_WAIT_MICRO 500000 // how many microseconds do we wait for the threads to complete their task


//if your code compiles you pass test 0 for free
//==============================================================================
int test0(void){
    return PASS;
}

//basic pthread create tests
//==============================================================================
void* _thread_dummy(void* arg){
    pthread_t a = pthread_self();
    pthread_exit(0);
}

int test1(void){
    pthread_t tid;
    pthread_create(&tid, NULL,  &_thread_dummy, NULL);
    return PASS;
}

int test2(void){
    pthread_t tid1 = 0;
    pthread_t tid2 = 0;
    
    pthread_create(&tid1, NULL,  &_thread_dummy, NULL);
    pthread_create(&tid2, NULL,  &_thread_dummy, NULL);

    if(tid1 != tid2){
        return PASS;
    }else{
        return FAIL;
    }
}


//basic pthread self test
//==============================================================================
static pthread_t global_tid = 0;
void* _thread_self_test(void* arg){
    global_tid = pthread_self();
    return arg;
}

int test3(void){
    pthread_t main_tid = 0;
    pthread_t tid1 = 0;
    
    pthread_create(&tid1, NULL,  &_thread_self_test, NULL);
    main_tid = pthread_self(); //yes main should have thread id too
    usleep(500);
    
    if(global_tid != main_tid && tid1 == global_tid){
        return PASS;
    }else{
        return FAIL;
    }
}




//scheduler test 1
//==============================================================================
static int a = 0;
static int b = 0;

void* _thread_schedule_a(void* arg){
    while(1){
        a = 1;
    }

}
void* _thread_schedule_b(void* arg){
    while(1){
        if(a){
            b = 1;
        }
    }
}

int test4(void){
    pthread_t tid1; pthread_t tid2;
        
    pthread_create(&tid1, NULL,  &_thread_schedule_a, NULL);
    pthread_create(&tid2, NULL,  &_thread_schedule_b, NULL);
    usleep(THREAD_WAIT_MICRO);
    
    if(b == 1){
        return PASS;
    }else{
        return FAIL;
    }
}



//scheduler test 2
//==============================================================================
static int c = 0;
void* _thread_inc(void* arg){
    int i;
    for(i = 0; i < 10; i++){
        c++;
    }
    
    pthread_exit(0);
}

int test5(void){
    int i;
    pthread_t tid1; pthread_t tid2;
        
    pthread_create(&tid1, NULL,  &_thread_inc, NULL);
    pthread_create(&tid2, NULL,  &_thread_inc, NULL);
    
    for(i = 0; i < 10; i++){
        c++;
    }

    usleep(THREAD_WAIT_MICRO);

    if(c == 30){
        return PASS;
    }else{
        return FAIL;
    }
    
}


//end of tests
//==============================================================================

int test_launcher(int test_num){
    switch(test_num){
    case 0 :
        return test0();

    case 1 :
        return test1();
        
    case 2:
        return test2();

    case 3:
        return test3();

    case 4:
        return test4();

    case 5:
        return test5();
        
    default:
        return 0;
        
    }
}


/**
 *  Some implementation details: Main spawns a child process for each
 *  test, that way if test 2/20 segfaults, we can still run the remaining
 *  test. It also hands the child a pipe to write the result of the test.
 *  the parent polls this pipe, and counts the test as a failure if there
 *  is a timeout (which would indicate the child is hung).
 */
int main(void){
    
    int status; pid_t pid;
    int pipe_fd[2]; int timeout; struct pollfd poll_fds;
    int score = 0; int total_score = 0;

    int devnull_fd = open("/dev/null", O_WRONLY);


    pipe(pipe_fd);
    poll_fds.fd = pipe_fd[0]; // only going to poll the read end of our pipe
    poll_fds.events = POLLRDNORM; //only care about normal read operations
        
    for(int i = 0; i < NUM_TESTS; i++){
        score = 0;
        pid = fork();

        //child, launches the test
        if (pid == 0){
            dup2(devnull_fd, STDOUT_FILENO); //begone debug messages
            dup2(devnull_fd, STDERR_FILENO);
            
            score = test_launcher(i);
            
            write(pipe_fd[1], &score, sizeof(score));
            exit(0); 
        }

        //parent, polls on the pipe we gave the child, kills the child,
        //keeps track of score
        else{  
            
            if(poll(&poll_fds, 1, 1000)){
                read(pipe_fd[0], &score, sizeof(score));
            }
            
            total_score += score;
            kill(pid, SIGKILL);
            waitpid(pid,&status,0);
            
            
            if(score){
                printf("test %i : PASS\n", i);
            }
            else{
                printf("test %i : FAIL\n", i);
            }
        }
    }
    
    printf("total score was %i / %i\n", total_score, NUM_TESTS);
    return 0;
}
