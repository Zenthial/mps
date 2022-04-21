
#define _DEFAULT_SOURCE     // for usleep

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <curses.h>

#include "racer.h"

// GRAPHIC "~O=-------o>"
#define START "~O="
#define END "o>"
#define FLAT_TIRE 'X'
#define FLAT_TIRE_BOUNDARY 3000 // 3 milliseconds in microseconds

static int FINISH_LINE = 80;
static int MAX_DELAY = DEFAULT_WAIT;

pthread_mutex_t curses_mutex = PTHREAD_MUTEX_INITIALIZER;

void init_racers( long milliseconds, int length ) {
    MAX_DELAY = milliseconds;
    FINISH_LINE = (length - MAX_CAR_LEN - 2);
    srand(time(NULL));
}

/**
 * @brief Private internal function to create the racecar
 * 
 * @param name The name of the driver
 * @param start What should be at the head of the car
 * @return char* The premade graphic
 */
char *make_graphic(char *name, char * start) {
    char *graphic = (char *)malloc(sizeof(char) * 13);

    int length = strlen(name);
    int remaining = 7 - length;

    int start_len = strlen(start);

    for (int i = 0; i < start_len; i++) {
        graphic[i] = start[i];
    }

    for (int i = 0; i < length; i++) {
        graphic[start_len + i] = name[i];
    }

    for (int i = 0; i < remaining; i++) {
        graphic[i + length + start_len] = '-';
    }

    for (int i = 0; i < start_len; i++) {
        graphic[i + remaining + length + start_len] = END[i];
    }

    return graphic;
}

Racer * make_racer( char *name, int row ) {
    Racer *racer = (Racer *)malloc(sizeof(Racer));
    racer->row = row;
    racer->distance = 0;

    char *graphic_text = make_graphic(name, START);
    racer->graphic = graphic_text;

    return racer;
}

void destroy_racer( Racer *racer ) {
    free(racer->graphic);
    free(racer);
}

void *run( void *racer ) {
    Racer *real_racer = (Racer *)racer;
    int active = 1;

    while (active) {
        // * 1000 to convert to microseconds
        int sleep_val = (rand() % MAX_DELAY) * 1000;

        if (sleep_val <= FLAT_TIRE_BOUNDARY) {
            active = 0;
            real_racer->graphic[1] = FLAT_TIRE;
        } else {
            // printf("sleeping for %d", sleep_val);
            usleep(sleep_val);
            real_racer->distance++;
        }

        if (real_racer->distance >= FINISH_LINE) {
            active = 0;
        }

        // get single write access
        pthread_mutex_lock(&curses_mutex);
        
        // move to the start of the row
        move(real_racer->row, 0);
        // refresh();
        // clear the row
        clrtoeol();
        // refresh();

        // move to the new position
        move(real_racer->row, real_racer->distance);
        // refresh();
        // print out the new graphic
        printw("%s", real_racer->graphic);
        // fflush(stdout);
        refresh();

        // give back access
        pthread_mutex_unlock(&curses_mutex);

    }

    return NULL;
}