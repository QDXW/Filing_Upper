#ifndef QRCODE_H
#define QRCODE_H
/******************************************************************************/
#include "common/Common.h"
/******************************************************************************/
#define QRCODE_BUFFER_SIZE 400
#define QRCODE_TEST_NAME_MAX 20
/******************************************************************************/
typedef struct {
    uint16 crc;
    uint8 name[20];
    uint8 SN[10];
    uint8 time;
    uint8 midC;
    uint8 distC_T;
    uint8 distC_Base1;
    uint8 distC_Base2;
    uint8 distC_Base3;
    uint8 distC_Base4;
    uint8 stripNum;
    uint16 searchHalfRadius_C;
    uint16 searchHalfRadius_T;
    uint16 areaC_HalfRadius;
    uint16 areaT_HalfRadius;
    uint16 winSize;
    uint8 limitEnabled;
    uint8 value;
    uint16 C_stepSize;
    uint16 C_magnitude;
    uint16 C_MIN;
    uint16 reserved;
} QRCODE_HEAD_STRUCT;

/******************************************************************************/
typedef struct {
    uint8 TName[QRCODE_TEST_NAME_MAX];
    uint8 Switch_Bool;
    float threshold1;
    float threshold2;
    float threshold3;
} QRCODE_SINGLE_LINE;

/******************************************************************************/
typedef struct {
    QRCODE_HEAD_STRUCT head;
    QRCODE_SINGLE_LINE ch_data[12];
} QRCODE_STRUCT;

/******************************************************************************/
//extern QRCODE_STRUCT QR_Date;
//extern uint8 QRCode_Buffer[QRCODE_BUFFER_SIZE];
#endif // QRCODE_H
