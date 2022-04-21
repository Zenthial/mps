#define _DEFAULT_SOURCE

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>
#include <string.h>
#include <curses.h>
#include <stdio.h>

#include "racer.h"

#define USAGE "Usage: pt-cruisers [max-speed-delay] name1 name2 [name3...]\n"

// To build: gcc -std=c99 -ggdb -Wall -Wextra demo_curses.c -o demo -lcurses
// you can use -lcurses or -lncurses
//

int check_first_num(char *first_arg) {
    char *ptr;
    int ret = strtol(first_arg, &ptr, 10);

    if (ret <= 0) {
        return -1;
    } else {
        return ret;
    }
}

int main(int argc, char *argv[]) {
    initscr();               // initialize curses window
    cbreak();                      // set no waiting for Enter key
    noecho();                      // set no echoing of user input
    int width = getmaxx(stdscr);
    clear();                       // clear screen and send cursor to (0,0)

    // make sure that we have at least 3 args
    if (argc < 3) {
        fprintf(stderr, USAGE);
        endwin();
        exit(EXIT_FAILURE);
    }

    // define some temporary variables allowing us to manuever a bit
    int first_arg = check_first_num(argv[1]);
    int delay = DEFAULT_WAIT;
    int num_names = argc - 1;
    int offset = 1;

    if (first_arg != -1) {
        delay = first_arg;
        num_names--;
        offset++;
    }

    // initialize racers here
    init_racers(delay, width);

    if (num_names < 2) {
        fprintf(stderr, USAGE);
        endwin();
        exit(EXIT_FAILURE);
    }

    pthread_t *thread_pool = (pthread_t *)malloc(sizeof(pthread_t) * num_names);
    Racer **racer_pool = (Racer **)malloc(sizeof(Racer *) * num_names);
    
    for (int t = 0; t < num_names; t++) {
        char *name = argv[t + offset];

        if (strlen(name) > MAX_NAME_LEN) {
            fprintf(stderr, "Error: racer %s exceeds length limit of 6.", name);
            endwin();
            exit(EXIT_FAILURE);
        }

        Racer *racer = make_racer(name, t+1);
        racer_pool[t] = racer;

        int rc = pthread_create(&thread_pool[t], NULL, run, (void *)racer);
        // printf("created thread %d\n", t);

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
    refresh();
    printf("The race is over! Press any key to exit the racetrack.");
    getchar();

    endwin();
}