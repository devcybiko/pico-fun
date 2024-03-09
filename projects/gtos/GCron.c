#define TRACE_OFF

#include "GCron.h"
#include "GTimer.h"
#include "GCronEntry.h"

GCron *GCron_new(void)
{
    TRACE("> GCron.new\n");
    if (GCron$.id == 0)
        _initClass();
    GCron *this = NEW(GCron);
    TRACE("this = %p\n", this);
    this->class = &GCron$;
    _(this).init(GCron_ID);
    TRACE("< GCron.new %p\n", this);
    return this;
}

static void init(int id)
{
    GCron *this = _THIS_; // special case for init
    TRACE("> GCron.init %p\n", this);
    __(this).init(id);
    this->list = GList_new();
    TRACE("< GCron.init %p\n", this);
}

static void delete(void)
{
    GCron *this = THIS(GCron, "GCron.delete");
    TRACE("> GCron.delete %p\n", this);
    _(this->list).delete();
    __(this).delete();
    TRACE("< GCron.delete %p\n", this);
}

static void debug(char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    GCron *this = THIS(GCron, "GCron.debug");
    TRACE("> GCron.debug %p\n", this);
    __(this).debug(fmt, args);
    TRACE("< GCron.debug %p\n", this);
}

static GCronEntry *add(int msRepeat, int (*callback)(struct GCronEntry *), void *context)
{
    GCron *this = THIS(GCron, "GCron.add");
    TRACE("> GCron.add %p\n", this);
    GCronEntry *entry = GCronEntry_new(msRepeat, callback, context);
    TRACE("entry=%p, msRepeat=%d, msLast=%d\n", entry, entry->msRepeat, entry->msLast);
    _(this->list).push(entry);
    TRACE("< GCron.add this=%p. entry=%p\n", this, entry);
    return entry;
}

typedef struct Context
{
    char *message;
    int counter;
} Context;

static int pump(void)
{
    GCron *this = THIS(GCron, "GCron.add");
    TRACE("> GCron.pump %p\n", this);
    // returns the number of entries that were processed
    // if the number is 0, it means that no entries were processed
    int count = 0;
    int now = GTimer.mSecs();
    TRACE("list=%p, list->size=%d\n", this->list, this->list->size);

    for (int i = 0; i < this->list->size; i++)
    {
        GCronEntry *entry = (GCronEntry *)_(this->list).get(i);
        TRACE("entry=%p, msRepeat=%d, msLast=%d\n", entry, entry->msRepeat, entry->msLast);

        TRACE("GCron.pump %p, context=%p, msLast=%d, msRepeat=%d, now=%d, then=%d\n", this, entry->context, entry->msLast, entry->msRepeat, now, entry->msLast + entry->msRepeat);
        TRACE("context.message=%s, context.counter=%d\n", ((Context *)entry->context)->message, ((Context *)entry->context)->counter);
        if (entry && !(entry->flags & GCRON_DEACTIVATED))
        {
            count++;
            if (entry->msLast + entry->msRepeat < now)
            {
                TRACE("callback=%p\n", entry->callback);
                int newFlags = entry->callback(entry);
                entry->flags = newFlags;
                entry->msLast = now;
            }
        }
    }
    TRACE("< GCron.pump this=%p, count=%d\n", this, count);
    return count;
}

GCronClass GCron$;
static void _initClass()
{
    TRACE("> GCron$._initClass\n");
    memcpy(&GCron$, &GObj$, sizeof(GObj$));
    GCron$.name = "GCron";
    GCron$.id = GCron_ID;
    GCron$.super = &GObj$;
    GCron$.init = init;
    GCron$.delete = delete;
    GCron$.debug = debug;
    GCron$.add = add;
    GCron$.pump = pump;
    TRACE("< GCron$._initClass\n");
}
