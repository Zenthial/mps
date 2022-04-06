#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "KStream.h"

#define BUFF_SIZE 8
#define BYTE_SIZE 1

int read_file(FILE *file_ptr, unsigned char *key, int key_size, int key_len) {
    unsigned char buff[BUFF_SIZE];
    int read_bytes = fread(buff, BYTE_SIZE, BUFF_SIZE, file_ptr);

    for (int i = 0; i < read_bytes; i++) {
        key[key_len] = buff[i];
        key_len++;
    }

    if (read_bytes == BUFF_SIZE) {
        key_size *= 2;
        key = (unsigned char*)realloc(key, key_size);
        return read_file(file_ptr, key, key_size, key_len);
    } else {
        return key_len;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: mop_message keyfile in-file [ out-file | - ]\n");
        return 0;
    }

    unsigned char *key = (unsigned char *)malloc(BUFF_SIZE * sizeof(char));
    unsigned char *input = (unsigned char *)malloc(BUFF_SIZE * sizeof(char));
    FILE *key_file = fopen(argv[1], "r");
    FILE *input_file = fopen(argv[2], "r");
    int key_len = read_file(key_file, key, BUFF_SIZE, 0);
    int input_len = read_file(input_file, input, BUFF_SIZE, 0);

    KStream *stream = ks_create(key, key_len);
    free(key);

    const char *out = (const char *)ks_translate(stream, input, input_len);
    FILE *out_file;
    if (strcmp(argv[3],"/") == 0) {
        out_file = stdout;
    } else {
        out_file = fopen(argv[3], "w");
    }

    for (int i = 0; i < input_len; i++) {
        if (out[i] != '0') {
            fprintf(out_file, "%c", out[i]);
        }
    }

    ks_destroy(stream);
    fclose(key_file);
    fclose(input_file);
    fclose(out_file);
    return 0;
}