#ifndef __GObj__
#define __GObj__

#define TRACE_OFF

#include "GDefines.h"
#include "Template.h"

static void _initClass();

// echo -n "GObj" | xxd -ps
// 474f626a
#define GObj_ID 0x474f626a

typedef int GID;

#define GObj_MEMBERS(Obj, SuperObj) \
    GID id; \
    CLASS_NAME(Obj) *class; \

#define GObj_CONSTRUCTOR(Obj, SuperObj) \
    METHOD(void, init)(int id);

#define GObj_METHODS(Obj, SuperObj) \
    METHOD(void, delete)(void); \
    METHOD(char *, toString)(void); \
    METHOD(char *, format)(char *fmt, ...); \
    METHOD(void, debug)(char *fmt, ...);

ROOT_CLASS(GObj)

extern GObj* GObj_new(void);

#endif // __GObj__
