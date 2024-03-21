#ifndef __GMap__
#define __GMap__

#include "GObj.h"
#include "GList.h"

// echo -n "GMap" | xxd -ps
// 474d6170
#define GMap_ID 0x474d6170

typedef struct GEntry {
    char *key;
    void *value;
} GEntry;

#define GMap_MEMBERS(Obj, SuperObj) \
    GList *list;

#define GMap_CONSTRUCTOR(Obj, SuperObj) \
    METHOD(void, init)(GID id);

#define GMap_METHODS(Obj, SuperObj) \
    METHOD(void, put)(char *key, void *value);\
    METHOD(void *, get)(char *key);\
    METHOD(GEntry *, getEntry)(char *key);\
    METHOD(void, putEntries)(GEntry *entries);

CLASS(GMap, GObj)

extern GMap* GMap_new();

#endif // __GMap__
