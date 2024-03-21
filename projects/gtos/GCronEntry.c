#define TRACE_OFF

#include "GCronEntry.h"
#include "GTimer.h"

GCronEntry* GCronEntry_new(int msRepeat, int (*callback)(GCronEntry*), void* context) {
    TRACE("> GCronEntry.new\n");
    if (GCronEntry$.id == 0) _initClass();
    GCronEntry* this = NEW(GCronEntry);
    TRACE("this = %p\n", this);
    this->class = &GCronEntry$;
    _(this).init(GCronEntry_ID, msRepeat, callback, context);
    TRACE("< GCronEntry.new %p\n", this);
    return this;
}

static void init(int id, int msRepeat, int (*callback)(GCronEntry*), void* context) {
    GCronEntry* this = _THIS_; // special case for init
    TRACE("> GCronEntry.init %p msRepeat=%d, callback=%p, context=%p\n", this, msRepeat, callback, context);
    __(this).init(id);
    this->msRepeat = msRepeat;
    this->callback = callback;
    this->context = context;
    this->flags = 0;
    this->msLast = GTimer.mSecs();
    TRACE("< GCronEntry.init %p msRepeat=%d, callback=%p, context=%p\n", this, msRepeat, callback, context);
}

static void delete() {
    GCronEntry* this = THIS(GCronEntry, "GCronEntry.delete");
    TRACE("> GCronEntry.delete %p\n", this);
    __(this).delete();
    TRACE("< GCronEntry.delete %p\n", this);
}

static void debug(char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    GCronEntry* this = THIS(GCronEntry, "GCronEntry.debug");
    TRACE("> GCronEntry.debug %p\n", this);
    __(this).debug(fmt, args);
    __(this).debug("this=%p, msRepeat=%d, msLast=%d, callback=%p, context=%p, flags=%d\n", this, this->msRepeat, this->msLast, this->callback, this->context, this->flags);
    TRACE("< GCronEntry.debug %p\n", this);
}

GCronEntryClass GCronEntry$;
static void _initClass() {
    TRACE("> GCronEntry$._initClass\n");
    memcpy(&GCronEntry$, &GObj$, sizeof(GObj$));
    GCronEntry$.name = "GCronEntry";
    GCronEntry$.id = GCronEntry_ID;
    GCronEntry$.super = &GObj$;
    GCronEntry$.init = init;
    // GCronEntry$.delete = delete;
    // GCronEntry$.debug = debug;
    TRACE("< GCronEntry$._initClass\n");
}
