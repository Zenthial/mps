/**
 * @file KStream.c
 * @author Tom Schollenberger
 * @brief The KStream implementation file, containing both public and private functions
 * 
 */

#include <stdlib.h>

#define S_SIZE 256 // some magic number in the kstream algorithm

typedef struct kStream {
    int *s;
    int i;
    int j;
} KStream;

#define _K_STREAM_
#include "KStream.h"

/// Gets the next byte from the stream
/// @param stream The KStream to get the next byte from
/// @return The next unsigned char byte in the stream
static unsigned char ks_next_byte(KStream *stream) {
    int i = stream->i;
    int j = stream->j;

    i = (i + 1) % S_SIZE;
    j = (j + stream->s[i]) % S_SIZE;

    unsigned char temp = stream->s[i];
    stream->s[i] = stream->s[j];
    stream->s[j] = temp;

    stream->i = i;
    stream->j = j;

    return stream->s[(stream->s[i] + stream->s[j]) % S_SIZE];
}

/// Encodes the passed character, 
/// by XORing the character with the next byte in the stream
/// @param stream The KStream to get the next byte from
/// @param character The character to encode
/// @return The next unsigned char byte in the stream XOR character
static unsigned char ks_encode(KStream *stream, unsigned char character) {
    return character ^ ks_next_byte(stream);
}

/// Translates a given byte input 
unsigned char *ks_translate(KStream *stream, unsigned char *input, int input_len) {
    unsigned char *output = (unsigned char *)malloc(sizeof(char) * input_len);

    for (int i = 0; i < input_len; i++) {
        output[i] = ks_encode(stream, input[i]);
    }

    return output;
}


/// Creates a new stream based off of the given key
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
        s[i] = s[j];
        s[j] = temp;
    }

    stream->i = 0;
    stream->j = 1;
    stream->s = s;

    for (int i = 0; i < 1024; i++) {
        ks_next_byte(stream);
    }

    return stream;
}

/// Destroys a stream
void ks_destroy(KStream *stream) {
    free(stream->s);
    free(stream);
}
