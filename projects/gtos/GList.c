#define TRACE_OFF

#include "GList.h"

GList* GList_new_full(int extent, double mult)
{
    TRACE("> GList.GList_new_full\n");
    if (GList$.id == 0) _initClass();
    GList * this = NEW(GList);
    TRACE("this = %p\n", this);
    this->class = &GList$;
    _(this).init(GList_ID, extent, mult);
    TRACE("< GList.GList_new_full %p\n", this);
    return this;
}

GList* GList_new(void)
{
    TRACE("> GList.new\n");
    GList * this = GList_new_full(0, 0);
    TRACE("< GList.new %p\n", this);
    return this;
}

static void init(int id, int extent, double mult) {
    GList* this = _THIS_; // special case for init
    TRACE("> GList.init %p extent=%d mult=%f\n", this, extent, mult);
    __(this).init(id);
    this->size = 0;
    this->extent = extent;
    this->mult = mult;
    if (extent == 0) this->extent = 8;
    if (mult == 0.0) this->mult = 2.0;
    this->array = CALLOC(this->extent, void*);
    TRACE("< GList.init %p extent=%d mult=%f\n", this, extent, mult);
}

static void* get(int n) {
    GList* this = THIS(GList, "GList.toString");
    TRACE("> GList.get %p n=%d\n", this, n);
    if (n < 0 || n >= this->size)
        return NULL;
    void* s = this->array[n];
    TRACE("< GList.get %p n=%d\n", this, n);
    _(this);
    return s;
}

static void push(void* s) {
    GList* this = THIS(GList, "GList.push");
    TRACE("> GList.push %p s=%p\n", this, s);
    TRACE("array=%p size=%d, extent=%d\n", this->array, this->size, this->extent);
    if (this->size == this->extent) {
        int new_extent = this->extent * this->mult;
        TRACE("... List Extent ... %d -> %d\n", this->extent, new_extent);
        this->extent = new_extent;
        this->array = REALLOC(this->array, this->extent);
    }
    this->array[this->size++] = s;
    TRACE("< GList.push %p s=%p\n", this, s);
}

static void debug(char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    GList* this = THIS(GList, "GList.debug");
    TRACE("> GList.debug %p\n", this);
    __(this).debug(fmt, args);
    printf(".list_array: %p\n", this->array);
    printf(".list_extent: %d\n", this->extent);
    printf(".list_size: %d\n", this->size);
    printf(".list_mult: %f\n", this->mult);
    // __(this).debug(".list_array: %p\n", this->array);
    // __(this).debug(".list_extent: %d\n", this->extent);
    // __(this).debug(".list_size: %d\n", this->size);
    // __(this).debug(".list_mult: %f\n", this->mult);
    for (int i = 0; i < this->size; i++) {
        printf("... %d %p\n", i, _(this).get(i));
    }
    TRACE("< GList.debug %p\n", this);
}

static void delete() {
    GList* this = THIS(GList, "GList.delete");
    TRACE("> GList.delete %p\n", this);
    free(this->array);
    __(this).delete();
    TRACE("< GList.delete %p\n", this);
}

GListClass GList$;
static void _initClass() {
    TRACE("> GList$._initClass\n");
    memcpy(&GList$, &GObj$, sizeof(GObj$));
    GList$.name = "GList";
    GList$.id = GList_ID;
    GList$.super = &GObj$;
    GList$.init = init;
    GList$.delete = delete;
    GList$.debug = debug;
    GList$.push = push;
    GList$.get = get;
    TRACE("< GList$._initClass\n");
}
