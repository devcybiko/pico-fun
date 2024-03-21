#ifndef __GList__
#define __GList__

#include "GObj.h"

// echo -n "GList" | xxd -ps
// 474c697374
#define GList_ID 0x4c697374


#define GList_MEMBERS(Obj, SuperObj) \
    void **array; \
    int extent; \
    int size; \
    double mult;

#define GList_CONSTRUCTOR(Obj, SuperObj) \
    METHOD(void, init)(int id, int extent, double mult);

#define GList_METHODS(Obj, SuperObj) \
    METHOD(void, push)(void *value); \
    METHOD(void *, get)(int n);

CLASS(GList, GObj)

extern GList* GList_new(void);
extern GList* GList_new_full(int extent, double mult);

#endif // __GList__
