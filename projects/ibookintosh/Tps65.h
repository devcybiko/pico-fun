#ifndef __Tps65__
#define __Tps65__

#include "GObj.h"

// echo -n "Tps65" | xxd -ps
// 4743726f6e
#define Tps65_ID 0x43726f6e

#define Tps65_MEMBERS(Obj, SuperObj) \
    void* i2cPort;\
    uint8_t addr;\
    uint8_t sdaPin;\
    uint8_t sclPin;\
    uint8_t resetPin;\
    int baud;\
    int fingers;\
    int x;\
    int y;\
    int rx;\
    int ry;


#define Tps65_CONSTRUCTOR(Obj, SuperObj) \
    METHOD(void, init)(int id, bool isPort0, int baud, int sdaPin, int sclPin, int resetPin, uint8_t addr);

#define Tps65_METHODS(Obj, SuperObj) \
    METHOD(void, reset)(void); \
    METHOD(uint8_t, readUByte)(uint16_t reg);\
    METHOD(uint16_t, readUWord)(uint16_t reg);\
    METHOD(int8_t, readByte)(int reg);\
    METHOD(int16_t, readWord)(int reg);\
    METHOD(void, write)(uint16_t reg, uint8_t data[], int nbytes);\
    METHOD(Tps65 *, readFinger)(Tps65* this);

CLASS(Tps65, GObj)

Tps65* Tps65_new(bool isPort0, int baud, int sdaPin, int sclPin, int resetPin, uint8_t addr);

#endif // __Tps65__
