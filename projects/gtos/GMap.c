#define TRACE_OFF

#include "GMap.h"

GMap* GMap_new() {
    TRACE("> GMap.new\n");
    if (GMap$.id == 0) _initClass();
    GMap* this = NEW(GMap);
    TRACE("this = %p\n", this);
    this->class = &GMap$;
    _(this).init(GMap_ID);
    TRACE("< GMap.new %p\n", this);
    return this;
}

static void init(GID id) {
    GMap* this = THIS(GMap, "GMap.init");
    TRACE("> GMap.init\n");
    __(this).init(id);
    this->list = GList_new_full(8, 2);
    TRACE("< GMap.init %p\n", this);
}

static void debug(char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    GMap* this = THIS(GMap, "GMap.debug");
    TRACE("> GMap.debug %p\n", this);
    __(this).debug(fmt, args);
    TRACE("< GMap.debug %p\n", this);
}

static void delete() {
    GMap* this = THIS(GMap, "GMap.delete");
    TRACE("> GMap.delete %p\n", this);
    _(this->list).delete();
    __(this).delete();
    TRACE("< GMap.delete\n");
}

static GEntry* getEntry(char* key) {
    GMap* this = THIS(GMap, "GMap.getEntry");
    TRACE("> GMap.getEntry %s\n", key);
    GEntry* result = NULL;
    for (int i = 0; result == NULL && i < this->list->size; i++) {
        GEntry* entry = (GEntry*)_(this->list).get(i);
        if (strcmp(entry->key, key) == 0) 
            result = entry;
    }
    TRACE("< GMap.getEntry %s=%p\n", key, result);
    return result;
}

static void putEntries(GEntry* entries) {
    GMap* this = THIS(GMap, "GMap.putEntries");
    TRACE("> GMap.putEntries\n");
    for (int i = 0; entries[i].key; i++) {
        GEntry entry = entries[i];
        _(this).put(entry.key, entry.value);
    }
    TRACE("< GMap.putEntries\n");
}

static void* get(char* key) {
    GMap* this = THIS(GMap, "GMap.get");
    TRACE("< GMap.get %s\n", key);
    GEntry* entry = _(this).getEntry(key);
    if (entry)
        return entry->value;
    TRACE("< GMap.getEntry %s\n", key);
    return NULL;
}

static void put(char* key, void* value) {
    GMap* this = THIS(GMap, "GMap.put");
    TRACE("> GMap.put %s\n", key);
    GEntry* entry = _(this).getEntry(key);
    TRACE("entry: %s=%p\n", key, entry);
    if (entry) {
        entry->value = value;
    } else {
        entry = NEW(GEntry);
        TRACE("entry: %p\n", entry);
        entry->key = key;
        TRACE("entry: %s=%p\n", key, entry);
        entry->value = value;
        TRACE("entry: %s=%s\n", key, (char *)entry->value);
        TRACE("list: %s\n", &this->list->class->id);
        (_THIS_=this->list, *(this->list->class)).push(entry);
        // _(this->list).push(entry);
    }
    TRACE("< GMap.put %s\n", key);
}

GMapClass GMap$;
static void _initClass() {
    TRACE("> GMap$._initClass\n");
    memcpy(&GMap$, &GObj$, sizeof(GObj$));
    GMap$.name = "GMap";
    GMap$.id = GMap_ID;
    GMap$.super = &GObj$;
    GMap$.init = init;
    GMap$.delete = delete;
    GMap$.debug = debug;
    GMap$.get = get;
    GMap$.put = put;
    GMap$.getEntry = getEntry;
    GMap$.putEntries = putEntries;
    TRACE("< GMap$._initClass\n");
}
