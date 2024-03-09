#define TRACE_OFF

#include "GObj.h"
#include "GList.h"
#include "GMap.h"
#include "GCronEntry.h"
#include "GCron.h"
// #include "config.h"

#define GCRON_DEACTIVATED 0x01

typedef struct Context
{
    char *message;
    int counter;
} Context;

void *newContext(char *message, int counter)
{
    Context *context = NEW(Context);
    context->message = message;
    context->counter = counter;
    return context;
}

int cronPrint(GCronEntry *entry)
{
    TRACE("cronPrint: %p\n", entry);
    Context *context = (Context *)entry->context;
    TRACE("cronPrint: context=%p\n", entry->context);
    printf("cronPrint: %s, %d\n", context->message, context->counter);
    context->counter--;
    if (context->counter == 0)
    {
        printf("\n%s deactivated\n\n", context->message);
        return GCRON_DEACTIVATED;
    }
    TRACE("  %s leaving cronPrint\n\n", context->message);
    return 0;
}

int main(int argc, char const *argv[])
{
    printf("Hello, World!\n");
    GObj *obj = GObj_new();
    _(obj).debug("GObj Test");
    printf("%s\n", _(obj).toString());
    _(obj).delete();

    GList *list = GList_new();
    _(list).push("zero");
    _(list).push("one");
    _(list).push("two");
    _(list).debug("GList Test");
    printf("%s\n", (char *)_(list).get(0));
    printf("%s\n", (char *)_(list).get(1));
    printf("%s\n", (char *)_(list).get(2));
    _(list).delete();
    printf("\n");

    GMap *map = GMap_new();
    _(map).put("zero", "cero");
    _(map).put("one", "uno");
    _(map).put("two", "dos");
    _(map).debug("GMap Test");
    printf("%s\n", (char *)_(map).get("zero"));
    printf("%s\n", (char *)_(map).get("one"));
    printf("%s\n", (char *)_(map).get("two"));
    _(map).delete();
    printf("\n");

    GCronEntry *entry = GCronEntry_new(1000, cronPrint, newContext("SLOW!", 10));
    _(entry).debug("GCronEntry Test");
    _(entry).delete();

    GCron *cron = GCron_new();
    _(cron).add(250, cronPrint, newContext("FAST!", 10));
    _(cron).add(500, cronPrint, newContext("MEDIUM!", 10));
    _(cron).add(1000, cronPrint, newContext("SLOW!", 10));

    for (
        int processed = _(cron).pump();
        processed > 0;
        processed = _(cron).pump())
    {
        TRACE("Pumping...%d\n", processed);
    }
    return 0;
}