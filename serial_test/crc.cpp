#include "crc.h"

/*
* data:要反转的数据， bit:位数
*/
quint16 invertUint(quint16 data, quint8 bit) {
    quint16 temp = 0x00;

    for (quint8 i=0; i<bit; i++) {
        temp = ((data >> i) & 0x01) | temp;
        if(i < bit-1) {
            temp = temp << 1;
        }
    }
    return temp;
}

quint16  calculateCRC16(const QByteArray &data) {
    quint16  crc = CRC16_CCITT_SEED;
    quint16  poly;

    poly = invertUint(CRC16_CCITT_POLY16, 16); // 0x1021高低位取反就是8408

    for (uint32_t  i = 0; i < data.size(); ++i) {
        crc ^= static_cast<quint8>(data.at(i));
        for (uint8_t j = 0; j < 8; ++j) {
            if (crc & 0x0001) {
                crc >>= 1;
                crc ^= poly;
            } else {
                crc >>= 1;
            }
        }
    }

    return crc;
}

/*
*CRC校验码生成函数
*/
quint16 crc16_ccitt(const QByteArray &data) {
    quint16 crc = CRC16_CCITT_SEED;

    for (quint32 i = 0; i < data.size(); i++) {
        crc = CRC16_CCITT_TAB[(crc ^ static_cast<quint8>(data.at(i))) & 0xff] ^ (crc >> 8);

    }

    return crc;
}
