#ifndef __Template__
#define __Template__

extern void *_THIS_; // this
extern void *_this();
extern void _trace(char *, ...);
extern void *_isa(void *, int); 

#ifdef TRACE_ON
#define TRACE(...) _trace(__VA_ARGS__)
#else
#define TRACE
#endif

#define _(Obj) (_THIS_=Obj, *(Obj->class))
#define __(Obj) (_THIS_=Obj, *(Obj->class->super))
#define CALL(Obj, NAME) (Obj->class->NAME ? () : _throw(Obj)) ; _(Obj).NAME
#define THIS(Obj, NAME)  _this(Obj##_ID, NAME)

#define CLASS_NAME(Obj) Obj##Class
#define METHOD(TYPE, NAME) TYPE(*NAME)

#define INSTANCE(Obj, SuperObj) \
typedef struct CLASS_NAME(Obj) CLASS_NAME(Obj); \
typedef struct Obj { \
    SuperObj##_MEMBERS(Obj, SuperObj) \
    Obj##_MEMBERS(Obj, SuperObj) \
} Obj;

#define CLASS(Obj, SuperObj) \
INSTANCE(Obj, SuperObj) \
typedef struct CLASS_NAME(Obj) { \
    char *name; \
    GID id; \
    CLASS_NAME(SuperObj) *super; \
    Obj##_CONSTRUCTOR(Obj, SuperObj) \
    SuperObj##_METHODS(Obj, SuperObj) \
    Obj##_METHODS(Obj, Obj) \
} CLASS_NAME(Obj); \
extern struct CLASS_NAME(Obj) Obj##$; // concrete class

#define CONSTANTS(Obj, SuperObj) \
extern CLASS_NAME(Obj) Obj##$;

//// Root Objects

#define ROOT_INSTANCE(Obj) \
typedef struct CLASS_NAME(Obj) CLASS_NAME(Obj); \
typedef struct Obj { \
    Obj##_MEMBERS(Obj, Obj) \
} Obj;

#define ROOT_CLASS(Obj) \
ROOT_INSTANCE(Obj) \
typedef struct CLASS_NAME(Obj) { \
    char *name; \
    GID id; \
    CLASS_NAME(Obj) *super; \
    Obj##_CONSTRUCTOR(Obj, Obj) \
    Obj##_METHODS(Obj, Obj) \
} CLASS_NAME(Obj); \
extern struct CLASS_NAME(Obj) Obj##$; // concrete class

// Generic New Method
#define STRINGIFY(x) #x

#define GNEW(Obj, ...) \
Obj* Obj##_new(__VA_ARGS__)\
{\
    TRACE("> %s.new\n", STRINGIFY(Obj));\
    if (Obj##$.id == 0) _initClass();\
    Obj * this = NEW(Obj);\
    TRACE("this = %p\n", this);\
    this->class = &Obj##$;\
    _(this) .init(Obj##_ID, __VA_ARGS__);\
    TRACE("< %s.new %p\n", STRINGIFY(Obj), this);\
    return this;\
}
#endif // __Template__