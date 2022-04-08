/**
 * @file KStream.h
 * @author Tom Schollenberger
 * @brief Contains the function definitions for the KStream
 * 
 */

#ifndef _K_STREAM_H_

#ifndef _K_STREAM_
    typedef struct kStream KStream;
#endif

/// Create takes full ownership of the key pointer.
/// It should not be referenced after passing it to ks_create
KStream *ks_create(unsigned char *key, int key_len);

/// Does not take ownership of input, needs to be freed by the user
/// Returned unsigned char pointer must be freed
/// @param stream The KStream to use to be translated
/// @param input The byte input array
/// @param input_len The length of the input byte array
/// @return unsigned char * The translated byte array
unsigned char *ks_translate(KStream *stream, unsigned char *input, int input_len);

/// Destroys the stream object
/// Frees the underlying array inside the object
/// @param stream The KStream to be destroyed
void ks_destroy(KStream *stream);

#endif // !_K_STREAM_H_

