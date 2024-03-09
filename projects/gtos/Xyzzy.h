#ifndef __Xyzzy__
#define __Xyzzy__

#include "GObj.h"
#include "GList.h"
#include "XyzzyEntry.h"

// echo -n "Xyzzy" | xxd -ps
// 4743726f6e
#define Xyzzy_ID 0x43726f6e

#define Xyzzy_MEMBERS(Obj, SuperObj) \
    GList *list;

#define Xyzzy_CONSTRUCTOR(Obj, SuperObj) \
    METHOD(void, init)(int id);

#define Xyzzy_METHODS(Obj, SuperObj) \
    METHOD(int, pump)(void); \
    METHOD(XyzzyEntry *, add)(int msRepeat, FUNC(int, callback, XyzzyEntry*), void *context);

CLASS(Xyzzy, GObj)

extern Xyzzy* Xyzzy_new(void);

#endif // __Xyzzy__
