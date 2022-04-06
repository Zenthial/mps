#include <stdlib.h>
#include "KStream.h"

#define S_SIZE 256 // some magic number in the kstream algorithm

unsigned char ks_next_byte(KStream *stream) {
    int i = stream->i;
    int j = stream->j;

    i = (i + 1) % S_SIZE;
    j = (j + stream->s[i]) % S_SIZE;

    unsigned char temp = stream->s[i];
    stream->s[i] = j;
    stream->s[j] = i;

    stream->i = i;
    stream->j = j;

    return stream->s[(stream->s[i] + stream->s[j]) % S_SIZE];
}

unsigned char ks_encode(KStream *stream, unsigned char character) {
    return character ^ ks_next_byte(stream);
}

unsigned char *ks_translate(KStream *stream, unsigned char *input, int input_len) {
    unsigned char *output = (unsigned char *)malloc(sizeof(char) * input_len);

    for (int i = 0; i < input_len; i++) {
        output[i] = ks_encode(stream, input[i]);
    }

    free(input);
    return output;
}

void ks_destroy(KStream *stream) {
    free(stream->s);
    free(stream);
}

KStream *ks_create(unsigned char *key, int key_len) {
    KStream *stream = (KStream *)malloc(sizeof(KStream));
    int *s = (int *)malloc(sizeof(int) * S_SIZE);

    for (int i = 0; i < S_SIZE; i++) {
        s[i] = i;
    }

    int j = 0;
    for (int i = 0; i < S_SIZE; i++) {
        j = (j + s[i] + key[i % key_len]) % S_SIZE;
        int temp = s[i];
        s[i] = j;
        s[j] = i;
    }

    stream->i = 0;
    stream->j = 1;
    stream->s = s;

    for (int i = 0; i < 1024; i++) {
        ks_next_byte(stream);
    }

    return stream;
}