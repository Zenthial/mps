typedef struct kStream {
    int *s;
    int i;
    int j;
} KStream;

/// Create takes full ownership of the key pointer.
/// It should not be referenced after passing it to ks_create
KStream *ks_create(unsigned char *key, int key_len);

/// takes ownership of input, freed after reading
/// returned unsigned char pointer must be freed
unsigned char *ks_translate(KStream *stream, unsigned char *input, int input_len);

void ks_destroy(KStream *stream);