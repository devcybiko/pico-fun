#define TRACE_OFF

#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"

#include "Tps65.h"

Tps65* Tps65_new(bool isPort0, int baud, int sdaPin, int sclPin, int resetPin, uint8_t addr) {
    TRACE("> Tps65.new\n");
    if (Tps65$.id == 0) _initClass();
    Tps65* this = NEW(Tps65);
    TRACE("this = %p\n", this);
    this->class = &Tps65$;
    _(this).init(Tps65_ID, isPort0, baud, sdaPin, sclPin, resetPin, addr);
    TRACE("< Tps65.new %p\n", this);
    return this;
}

static void init(int id, bool isPort0, int baud, int sdaPin, int sclPin, int resetPin, uint8_t addr) {
    Tps65* this = _THIS_; // special case for init
    TRACE("> Tps65.init %p\n", this);
    __(this).init(id); // super class
    if (isPort0) this->i2cPort = i2c0;
    else this->i2cPort = i2c1;
    this->addr = addr;
    this->sdaPin = sdaPin;
    this->sclPin = sclPin;
    this->resetPin = resetPin;
    this->baud = baud;
    i2c_init(this->i2cPort, baud);
    gpio_set_function(sdaPin, GPIO_FUNC_I2C);
    gpio_set_function(sclPin, GPIO_FUNC_I2C);
    gpio_init(resetPin);
    gpio_set_dir(resetPin, GPIO_OUT);
    gpio_pull_up(resetPin);
    gpio_pull_up(sdaPin);
    gpio_pull_up(sclPin);
    _(this).reset();

    TRACE("< Tps65.init %p\n", this);
}

static void delete() {
    Tps65* this = THIS(Tps65, "Tps65.delete");
    TRACE("> Tps65.delete %p\n", this);
    __(this).delete();
    TRACE("< Tps65.delete %p\n", this);
}

static void debug(char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    Tps65* this = THIS(Tps65, "Tps65.debug");
    TRACE("> Tps65.debug %p\n", this);
    __(this).debug(fmt, args);
    int productNumber = _(this).readUWord(0x00);
    int projectNumber = _(this).readUWord(0x02);
    int version = _(this).readUWord(0x04);
    int bootloaderStatus = _(this).readUByte(0x06);
    int maxTouch = _(this).readUByte(0x0b);
    int prevCycleTime = _(this).readUByte(0x0c);
    int gestureEvents0 = _(this).readUByte(0x0d);
    int gestureEvents1 = _(this).readUByte(0x0e);
    int systemInfo0 = _(this).readUByte(0x0f);
    int systemInfo1 = _(this).readUByte(0x10);

    printf("Product Number: %04x\n", productNumber);
    printf("Project Number: %04x\n", projectNumber);
    printf("Version: %04x\n", version);
    printf("Bootloader Status: %02x\n", bootloaderStatus);
    printf("Max Touch: %02x\n", maxTouch);
    printf("Prev Cycle Time: %02x\n", prevCycleTime);
    printf("Gesture Events 0: %02x\n", gestureEvents0);
    printf("Gesture Events 1: %02x\n", gestureEvents1);
    printf("System Info 0: %02x\n", systemInfo0);
    printf("System Info 1: %02x\n", systemInfo1);
    printf("\n");
    va_end(args);
    TRACE("< Tps65.debug %p\n", this);
}

static void reset(void) {
    Tps65 *this = THIS(Tps65, "Tps65.reset");
    TRACE("> Tps65$.reset\n");
    gpio_put(this->resetPin, 0);
    sleep_ms(200);
    gpio_put(this->resetPin, 1);
    sleep_ms(2000);
    TRACE("< Tps65$.reset\n");
}

static uint8_t readUByte( uint16_t reg) {
    Tps65 *this = THIS(Tps65, "Tps65.readUByte");
    TRACE("> Tps65$.readUByte\n");
    uint8_t buf[2] = { reg >> 8, reg & 0xFF };
    uint8_t data;
    TRACE("addressing... %02x, reg=%02x %02x\n", this->addr, buf[0], buf[1]);
    i2c_write_blocking(this->i2cPort, this->addr, buf, 2, true);
    TRACE("reading... %02x\n", this->addr);
    i2c_read_blocking(this->i2cPort, this->addr, &data, 1, false);
    TRACE("Got... %02x\n", data);
    TRACE("< Tps65$.readUByte\n");
    return data;
}

static uint16_t readUWord( uint16_t reg) {
    Tps65 *this = THIS(Tps65, "Tps65.readUWord");
    TRACE("> Tps65$.readUWord\n");
    uint8_t hi = _(this).readUByte(reg);
    uint8_t lo = _(this).readUByte(reg + 1);
    TRACE("< Tps65$.readUWord\n");
    return (hi << 8) | lo;
}

static int8_t readByte( int reg) {
    Tps65 *this = THIS(Tps65, "Tps65.readByte");
    TRACE("> Tps65$.readUWord\n");
    int value = _(this).readUByte(reg);
    // if (value & 0x80) value = 256 - value;
    TRACE("< Tps65$.readUWord\n");
    return (int8_t)value;
}

static int16_t readWord( int reg) {
    Tps65 *this = THIS(Tps65, "Tps65.readWord");
    TRACE("> Tps65$.readWord\n");
    int value = _(this).readUWord(reg);
    // if (value & 0x8000) value = 65536 - value;
    TRACE("< Tps65$.readWord\n");
    return (int16_t)value;
}

static void write( uint16_t reg, uint8_t data[], int nbytes) {
    Tps65 *this = THIS(Tps65, "Tps65.write");
    TRACE("> Tps65$.write\n");
    uint8_t buf[nbytes + 2];
    buf[0] = reg >> 8;
    buf[1] = reg & 0xFF;
    for (int i = 0; i < nbytes; i++) buf[i + 2] = data[i];
    i2c_write_blocking(this->i2cPort, this->addr, buf, nbytes + 2, false);
    TRACE("< Tps65$.write\n");
}

static Tps65 *readFinger() {
    Tps65 *this = THIS(Tps65, "Tps65.readFinger");
    Tps65 *result = NULL;
    TRACE("> Tps65$.readFinger\n");
    int lastFingers = this->fingers;
    int lastX = this->x;
    int lastY = this->y;
    int fingers = _(this).readUByte(0x11);
    int rx = _(this).readWord(0x12);
    int ry = _(this).readWord(0x14);
    int x = _(this).readUWord(0x16);
    int y = _(this).readUWord(0x18);
    if (fingers != lastFingers || x != lastX || y != lastY || rx != this->rx || ry != this->ry) {
        this->fingers = fingers;
        this->x = x;
        this->y = y;
        this->rx = rx;
        this->ry = ry;
        result = this;
    }
    TRACE("< Tps65$.readFinger\n");
    return result;
}

Tps65Class Tps65$;
static void _initClass() {
    TRACE("> Tps65$._initClass\n");
    memcpy(&Tps65$, &GObj$, sizeof(GObj$));
    Tps65$.name = "Tps65";
    Tps65$.id = Tps65_ID;
    Tps65$.super = &GObj$;
    Tps65$.init = init;
    Tps65$.delete = delete;
    Tps65$.debug = debug;
    Tps65$.reset = reset;
    Tps65$.readUByte = readUByte;
    Tps65$.readUWord = readUWord;
    Tps65$.readByte = readByte;
    Tps65$.readWord = readWord;
    Tps65$.write = write;
    Tps65$.readFinger = readFinger;
    TRACE("< Tps65$._initClass\n");
}
