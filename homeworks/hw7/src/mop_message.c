#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "KStream.h"

#define BUFF_SIZE 8
#define BYTE_SIZE 1

/// Representation of a File
/// @field buffer - Char array pointer
/// @field buffer_size - size of the underlying buffer array
/// @field buffer_len - the amount of elements in the underlying array
typedef struct fileBuffer {
    unsigned char *buffer;
    int buffer_size;
    int buffer_len;
} FileBuffer;

/// Based off of a given file pointer, convert it to a FileBuffer struct
/// @param file_ptr A valid, non-null FILE ptr 
/// @return FileBuffer 
FileBuffer read_file(FILE *file_ptr) {
    int buffer_size = 0;
    int buffer_len = 0;
    unsigned char buff[BUFF_SIZE];
    unsigned char *buffer = malloc(1);

    int read_bytes;
    do {
        buffer_size += 8;
        buffer = (unsigned char *)realloc(buffer, buffer_size + 1);
        if (buffer == NULL) {
            perror("PANIC!!!");
        }
        read_bytes = fread(buff, BYTE_SIZE, BUFF_SIZE, file_ptr);

        for (int i = 0; i < read_bytes; i++) {
            buffer[buffer_len] = buff[i];
            buffer_len++;
        }
    } while (read_bytes == BUFF_SIZE);

    FileBuffer buf = {buffer, buffer_size, buffer_len};
    return buf;
}

/// Main entry point of the program
int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: mop_message keyfile in-file [ out-file | - ]\n");
        return 0;
    }

    FILE *key_file = fopen(argv[1], "r");
    FILE *input_file = fopen(argv[2], "r");
    
    FileBuffer key_buff = read_file(key_file);
    FileBuffer input_buff = read_file(input_file);

    KStream *stream = ks_create(key_buff.buffer, key_buff.buffer_len);
    char *out = (char *)ks_translate(stream, input_buff.buffer, input_buff.buffer_len);

    FILE *out_file;
    int stdout_bool = 0;
    if (strcmp(argv[3], "-") == 0) {
        out_file = stdout;
        stdout_bool = 1;
    }
    else {
        out_file = fopen(argv[3], "w");
    }

    for (int i = 0; i < input_buff.buffer_len; i++) {
        if (out[i] != '0') {
            if (stdout_bool == 1 && !isascii(out[i])) {
                fprintf(out_file, "%2x", out[i]);
            }
            else {
                fprintf(out_file, "%c", out[i]);
            }
        }
    }

    free(input_buff.buffer);
    free(key_buff.buffer);
    free(out);
    ks_destroy(stream);
    fclose(key_file);
    fclose(out_file);
    fclose(input_file);
    return 0;
}
