/**
 * @file pt-cruisers.c
 * @author Thomas Schollenberger
 * @brief Main file, handles command parsing and thread initialization
 * 
 */

#define _DEFAULT_SOURCE

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <curses.h>
#include <stdio.h>
#include <ctype.h>

#include "racer.h"

#define USAGE "Usage: pt-cruisers [max-speed-delay] name1 name2 [name3...]\n"

typedef struct Number_T {
    int is_number; // 0 for not a number, 1 for a number, 2 for negative
    int val; // the value, unused in all cases except 1
} NumberReturn;

// To build: gcc -std=c99 -ggdb -Wall -Wextra demo_curses.c -o demo -lcurses
// you can use -lcurses or -lncurses
//

/**
 * @brief Checks if the first number is a string, negative or a number
 * 
 * @param first_arg The string to check
 * @return NumberReturn 
 */
NumberReturn check_first_num(char *first_arg) {
    NumberReturn return_struct;

    int len = strlen(first_arg);
    for (int i = 0; i < len; i++) {
        if (first_arg[i] == '-') {
            char *ptr;
            int ret = strtol(first_arg, &ptr, 10);
            return (NumberReturn){2, ret};
        } else if (!isdigit(first_arg[i])) {
            return (NumberReturn){0, 0};
        }
    }
    
    {
        char *ptr;
        int ret = strtol(first_arg, &ptr, 10);

        if (ret == 0) {
            return_struct = (NumberReturn){2, ret};
        }
        else {
            return_struct = (NumberReturn){1, ret};
        }
    }

    return return_struct;
}

// main entry point
int main(int argc, char *argv[]) {
    // make sure that we have at least 3 args
    if (argc < 2) {
        fprintf(stderr, USAGE);
        exit(EXIT_FAILURE);
    }

    // define some temporary variables allowing us to manuever a bit
    NumberReturn return_struct = check_first_num(argv[1]);
    int delay = DEFAULT_WAIT;
    int num_names = argc - 1;
    int offset = 1;

    if (return_struct.is_number == 1) {
        delay = return_struct.val;
        num_names--;
        offset++;
    } else if(return_struct.is_number == 2) {
        fprintf(stderr, "Error: delay (%s) is invalid.\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    if (num_names < 2) {
        fprintf(stderr, USAGE);
        exit(EXIT_FAILURE);
    }

    initscr();
    cbreak();
    noecho();
    int width = getmaxx(stdscr);
    clear(); 

    // initialize racers here
    init_racers(delay, width);

    pthread_t *thread_pool = (pthread_t *)malloc(sizeof(pthread_t) * num_names);
    Racer **racer_pool = (Racer **)malloc(sizeof(Racer *) * num_names);
    
    for (int t = 0; t < num_names; t++) {
        char *name = argv[t + offset];

        if (strlen(name) > MAX_NAME_LEN) {
            fprintf(stderr, "Error: racer %s exceeds length limit of 6.\n", name);
            endwin();
            exit(EXIT_FAILURE);
        }

        Racer *racer = make_racer(name, t+1);
        racer_pool[t] = racer;

        int rc = pthread_create(&thread_pool[t], NULL, run, (void *)racer);

        if (rc) {
            fprintf(stderr, "pthread_create failed");
            endwin();
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < num_names; i++) {
        pthread_t thread = thread_pool[i];

        int ret = pthread_join(thread, NULL);

        if (ret) {
            fprintf(stderr, "pthread_join failed");
            endwin();
            exit(EXIT_FAILURE);
        }
    }

    free(thread_pool);

    for (int i = 0; i < num_names; i++) {
        destroy_racer(racer_pool[i]);
    }

    free(racer_pool);

    move(0, 0);
    printw("The race is over! Press any key to exit the racetrack");
    refresh();
    getchar();

    endwin();
}