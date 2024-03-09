#include "GDefines.h"
#include "Template.h"
#include "GObj.h"

void* _THIS_; // this
static int _indent = 0;

void* _this(int obj_id, char* fnName) {
    GObj* this = _THIS_;
    if (this == NULL) {
        printf("ERROR: \"%s\" called with \"->\" instead of \"_(x).\" \n", fnName);
        exit(1);
    }
    if (this->id != obj_id) {
        GObjClass* class = _isa(this, obj_id);
        if (class == NULL) {
            printf("ERROR: \"%s\" called with wrong object type \"%s(%d)\" instead of \"%d\" \n", fnName, this->class->name, this->id, obj_id);
            exit(1);
        }
    }
    _THIS_ = NULL;
    return this;
}

void _throw(void* this, char* name) {
    printf("Error: %p tried to call uninitialized method \"%s\"\n", this, name);
    exit(1);
}

void _trace(char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    if (fmt[0] == '<') _indent--;
    for (int i = 0; i < _indent; i++) printf("  ");
    vprintf(fmt, args);
    if (fmt[0] == '>') _indent++;
    va_end(args);
}

void *_isa(void* this, GID obj_id) {
    GObjClass* class = ((GObj*)this)->class;
    while (class != NULL) {
        if (class->id == obj_id) return class;
        class = class->super;
    }
    return NULL;
}