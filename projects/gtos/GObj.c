#include "GObj.h"

GObj* GObj_new(void)
{
    TRACE("> GObj_new\n");
    if (GObj$.id == 0) _initClass();
    GObj* this = NEW(GObj);
    TRACE(" this=%p\n");
    this->class = &GObj$;
    _(this).init(GObj_ID);
    TRACE("< GObj_new\n");
    return this;
}

static void init(int id) {
    GObj* this = _THIS_; // special case for init
    TRACE("> GObj.init %p\n", this);
    this->id = id;
    TRACE("< GObj.init %p\n", this);
}

static void delete(void) {
    GObj* this = THIS(GObj, "GObj.delete");
    TRACE("> GObj.delete %p\n", this);
    FREE(this);
    TRACE("< GObj.delete\n");
}

static char buffer[256];
static char* format(char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    TRACE("> GObj.format %s ...\n", fmt);
    int n = vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);
    TRACE("< GObj.format %s=>%s\n", fmt, buffer);
    return buffer;
}

static char* toString(void) {
    GObj* this = THIS(GObj, "GObj.toString");
    TRACE("> GObj.toString %p\n", this);
    _THIS_ = this;
    char* s = format("%s: %p", this->class->name, this);
    TRACE("< GObj.toString %p\n", this);
    return s;
}

static void debug(char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    GObj* this = THIS(GObj, "GObj.debug");
    TRACE("> GObj.debug %p %s\n", this, this->class->name);
    _THIS_ = this;
    char* s = format(fmt, args);
    // char *s = "GObj.toString: 0x12345678";
    printf("%s\n", s);
    TRACE("< GObj.debug %p\n", this);
    va_end(args);
}

GObjClass GObj$;
static void _initClass() {
    TRACE("> GObj$._initClass\n");
    GObj$.name = "GObj";
    GObj$.id = GObj_ID;
    GObj$.super = NULL;
    GObj$.init = init;
    GObj$.delete = delete;
    GObj$.toString = toString;
    GObj$.format = format;
    GObj$.debug = debug;
    TRACE("< GObj$._initClass\n");
}
