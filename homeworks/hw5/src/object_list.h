typedef struct ObjectList_S {} ObjectList;
typedef struct Iter_S {} Iter;

ObjectList * ol_create(void);

void ol_destroy(ObjectList *list);

size_t ol_get_size(const ObjectList *list);

int ol_insert(ObjectList *list, void *data);

Iter * ol_iterator(ObjectList *list);

int ol_has_next(const Iter *iter);

void * ol_next(Iter *iter);