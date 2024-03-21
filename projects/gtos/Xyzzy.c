#define TRACE_OFF

#include "Xyzzy.h"

Xyzzy *Xyzzy_new(void)
{
    TRACE("> Xyzzy.new\n");
    if (Xyzzy$.id == 0)
        _initClass();
    Xyzzy *this = NEW(Xyzzy);
    TRACE("this = %p\n", this);
    this->class = &Xyzzy$;
    _(this).init(Xyzzy_ID);
    TRACE("< Xyzzy.new %p\n", this);
    return this;
}

static void init(int id)
{
    Xyzzy *this = _THIS_; // special case for init
    TRACE("> Xyzzy.init %p\n", this);
    __(this).init(id);
    TRACE("< Xyzzy.init %p\n", this);
}

static void delete()
{
    Xyzzy *this = THIS(Xyzzy, "Xyzzy.delete");
    TRACE("> Xyzzy.delete %p\n", this);
    __(this).delete();
    TRACE("< Xyzzy.delete %p\n", this);
}

static void debug(char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    Xyzzy *this = THIS(Xyzzy, "Xyzzy.debug");
    TRACE("> Xyzzy.debug %p\n", this);
    __(this).debug(fmt, args);
    TRACE("< Xyzzy.debug %p\n", this);
}

static void* get(int n) {
    Xyzzy* this = THIS(Xyzzy, "Xyzzy.toString");
    TRACE("> Xyzzy.get %p n=%d\n", this, n);
    if (n < 0 || n >= this->size)
        return NULL;
    void* s = this->array[n];
    TRACE("< Xyzzy.get %p n=%d\n", this, n);
    _(this);
    return s;
}

static void push(void* s) {
    Xyzzy* this = THIS(Xyzzy, "Xyzzy.push");
    TRACE("> Xyzzy.push %p s=%p\n", this, s);
    TRACE("array=%p size=%d, extent=%d\n", this->array, this->size, this->extent);
    if (this->size == this->extent) {
        int new_extent = this->extent * this->mult;
        TRACE("... List Extent ... %d -> %d\n", this->extent, new_extent);
        this->extent = new_extent;
        this->array = REALLOC(this->array, this->extent);
    }
    this->array[this->size++] = s;
    TRACE("< Xyzzy.push %p s=%p\n", this, s);
}

XyzzyClass Xyzzy$;
static void _initClass() {
    TRACE("> Xyzzy$._initClass\n");
    memcpy(&Xyzzy$, &GObj$, sizeof(GObj$));
    Xyzzy$.name = "Xyzzy";
    Xyzzy$.id = Xyzzy_ID;
    Xyzzy$.super = &GObj$;
    Xyzzy$.init = init;
    Xyzzy$.delete = delete;
    Xyzzy$.debug = debug;
    Xyzzy$.push = push;
    Xyzzy$.get = get;
    TRACE("< Xyzzy$._initClass\n");
}
