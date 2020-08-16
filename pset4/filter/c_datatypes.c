#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint16_t convertFrom8To16(uint8_t dataFirst, uint8_t dataSecond) {
    uint16_t dataBoth = 0x0000;
    uint8_t dataBoth8Bit = 0x00;

    uint8_t dataThird = 0x07;

    dataBoth = dataFirst;
    dataBoth = dataBoth << 8;
    dataBoth |= dataSecond;

    dataBoth8Bit = dataFirst | dataSecond | dataThird;
    printf("dataBoth8Bit = %02X\n", dataBoth8Bit);
    printf("dataBoth8Bit = %i\n", dataBoth8Bit);
    return dataBoth;
}

uint8_t *convertFrom16To8(uint16_t dataAll) {
    static uint8_t arrayData[2] = { 0x00, 0x00 };

    *(arrayData) = (dataAll >> 8) & 0x00FF;
    arrayData[1] = dataAll & 0x00FF;
    return arrayData;
}

int main() {
    uint8_t *dataMix;
    uint8_t data1 = 0xAB;
    uint8_t data2 = 0xCD;
    uint16_t data3 = 0x0000;

    data3 = convertFrom8To16(data1, data2);
    printf("data1 = %04X\n", data1);
    printf("data2 = %04X\n", data2);
    printf("data3 = %04X\n", data3);

    dataMix = convertFrom16To8(data3);
    printf("dataMix[0] = %02X\n", dataMix[0]);
    printf("(++dataMix) = %02X\n", *(++dataMix));
    return 0;
}