#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "pico/time.h"

static uint8_t addr = 0x74;

#define DEBUG quiet

void quiet()
{
}

int blink(int onms, int offms)
{
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, 1);
    sleep_ms(onms);
    gpio_put(LED_PIN, 0);
    sleep_ms(offms);
}

typedef struct _TPS65
{
    void* i2cPort;
    uint8_t addr;
    uint8_t sdaPin;
    uint8_t sclPin;
    uint8_t resetPin;
    int baud;
    int fingers;
    int x;
    int y;
    int rx;
    int ry;
} TPS65;

void TPS65Debug(TPS65* this)
{
    DEBUG("TPS65: i2cPort=%08x, addr=%02x, sdaPin=%02x, sclPin=%02x, baud=%d\n", this->i2cPort, this->addr, this->sdaPin, this->sclPin, this->baud);
}

void TPS65Reset(TPS65* this)
{
    gpio_put(this->resetPin, 0);
    sleep_ms(200);
    gpio_put(this->resetPin, 1);
    sleep_ms(2000);
}
void TPS65Init(TPS65* this, bool isPort0, int baud, int sdaPin, int sclPin, int resetPin, uint8_t addr)
{
    if (isPort0)
        this->i2cPort = i2c0;
    else
        this->i2cPort = i2c1;
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
    TPS65Reset(this);
}

uint8_t TPS65ReadUByte(TPS65* this, uint16_t reg)
{
    uint8_t buf[2] = { reg >> 8, reg & 0xFF };
    uint8_t data;
    TPS65Debug(this);
    DEBUG("addressing... %02x, reg=%02x %02x\n", this->addr, buf[0], buf[1]);
    i2c_write_blocking(this->i2cPort, this->addr, buf, 2, true);
    DEBUG("reading... %02x\n", this->addr);
    i2c_read_blocking(this->i2cPort, this->addr, &data, 1, false);
    DEBUG("Got... %02x\n", data);
    return data;
}

uint16_t TPS65ReadUWord(TPS65* this, uint16_t reg)
{
    uint8_t hi = TPS65ReadUByte(this, reg);
    uint8_t lo = TPS65ReadUByte(this, reg + 1);
    return (hi << 8) | lo;
}

int TPS65ReadByte(TPS65* this, int reg)
{
    int value = TPS65ReadUByte(this, reg);
    // if (value & 0x80)
    //     value = 256 - value;
    return (int8_t)value;
}

int TPS65ReadWord(TPS65* this, int reg)
{
    int value = TPS65ReadUWord(this, reg);
    // if (value & 0x8000)
    //     value = 65536 - value;
    return (int16_t)value;
}

void TPS65Write(TPS65* this, uint16_t reg, uint8_t data[], int nbytes)
{
    uint8_t buf[nbytes + 2];
    buf[0] = reg >> 8;
    buf[1] = reg & 0xFF;
    for (int i = 0; i < nbytes; i++)
        buf[i + 2] = data[i];
    i2c_write_blocking(this->i2cPort, this->addr, buf, nbytes + 2, false);
}

void TPS665Status(TPS65* this)
{
    int productNumber = TPS65ReadUWord(this, 0x00);
    int projectNumber = TPS65ReadUWord(this, 0x02);
    int version = TPS65ReadUWord(this, 0x04);
    int bootloaderStatus = TPS65ReadUByte(this, 0x06);
    int maxTouch = TPS65ReadUByte(this, 0x0b);
    int prevCycleTime = TPS65ReadUByte(this, 0x0c);
    int gestureEvents0 = TPS65ReadUByte(this, 0x0d);
    int gestureEvents1 = TPS65ReadUByte(this, 0x0e);
    int systemInfo0 = TPS65ReadUByte(this, 0x0f);
    int systemInfo1 = TPS65ReadUByte(this, 0x10);

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
}

void TPS65Release(TPS65* this)
{
    // TODO: release I2C and GPIO Pins
    free(this);
}

TPS65* TPS65GetFinger(TPS65* this)
{
    int lastFingers = this->fingers;
    int lastX = this->x;
    int lastY = this->y;
    int fingers = TPS65ReadUByte(this, 0x11);
    int rx = TPS65ReadWord(this, 0x12);
    int ry = TPS65ReadWord(this, 0x14);
    int x = TPS65ReadUWord(this, 0x16);
    int y = TPS65ReadUWord(this, 0x18);
    if (fingers != lastFingers || x != lastX|| y != lastY || rx != this->rx || ry != this->ry) {
        this->fingers = fingers;
        this->x = x;
        this->y = y;
        this->rx = rx;
        this->ry = ry;
        return this;
    }
    return NULL;
}

TPS65* newTPS65(bool isPort0, int baud, int sdaPin, int sclPin, int resetPin, uint8_t addr)
{
    TPS65* obj = (TPS65*)malloc(sizeof(TPS65));
    TPS65Init(obj, isPort0, baud, sdaPin, sclPin, resetPin, addr);
    return obj;
}

int main(void)
{
    stdio_init_all(); // Initialise STD I/O for printing over serial
    blink(75, 500);
    printf("\nTPS65 for Raspberry Pi Pico (c) 2024 Agile Frontiers\n");
    blink(75, 500);
    TPS65* tps65 = newTPS65(false, 400 * 1000, 2, 3, 4, 0x74);
    blink(75, 500);
    printf("\nGot the tps65 object %08x\n", tps65);

    int REPORT = 10000;
    int FINGER = 125;
    uint32_t lastReport = 0;
    uint32_t lastFinger = 0;
    while (true) {
        uint32_t currentMillis = to_ms_since_boot(get_absolute_time());
        if (currentMillis - lastReport > REPORT) {
            TPS665Status(tps65);
            lastReport = currentMillis;
            printf("CNT: %d, Fingers: %d, X: %d, Y: %d, RX: %d, RY: %d\n", currentMillis, tps65->fingers, tps65->x, tps65->y, tps65->rx, tps65->ry);
        }
        if ((currentMillis - lastFinger > FINGER) ){
            lastFinger = currentMillis;
            TPS65* finger = TPS65GetFinger(tps65);
            if (finger) printf("CNT: %d, Fingers: %d, X: %d, Y: %d, RX: %d, RY: %d\n", currentMillis, tps65->fingers, tps65->x, tps65->y, tps65->rx, tps65->ry);
        }
    }
}
