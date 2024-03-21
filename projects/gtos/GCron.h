#ifndef __GCron__
#define __GCron__

#include "GObj.h"
#include "GList.h"
#include "GCronEntry.h"

// echo -n "GCron" | xxd -ps
// 4743726f6e
#define GCron_ID 0x43726f6e

#define GCRON_DEACTIVATED 0x01

#define GCron_MEMBERS(Obj, SuperObj) \
    GList *list;

#define GCron_CONSTRUCTOR(Obj, SuperObj) \
    METHOD(void, init)(int id);

#define GCron_METHODS(Obj, SuperObj) \
    METHOD(int, pump)(void); \
    METHOD(GCronEntry *, add)(int msRepeat, FUNC(int, callback, GCronEntry*), void *context);

CLASS(GCron, GObj)

extern GCron* GCron_new(void);

#endif // __GCron__
