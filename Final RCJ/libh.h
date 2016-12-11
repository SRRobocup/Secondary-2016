//PUT VARIABLES IN HERE

#ifndef _LIBH_
#define _LIBH_

#include "common.h"
//for the Color sensors
int LBlack = 80;
int LWhite = 300;

int RBlack = 65;
int RWhite = 228;

// the light (reflective mode) sensor
int MBlack = 5;
int MWhite = 50;

int LThreshold = (LBlack+LWhite)/2;
int RThreshold = (RBlack+RWhite)/2;
int MThreshold = (MBlack+MWhite)/2;

// for the chassis
int Wb=17.5;
float Tdia =  3; // tire diameter
float Gr = 1.0; // gear ratio

// for the encoder vs dist vs degrees of rotation
const float CmPerEncoder = (Tdia * PI)/(360.0*Gr);
const float EncoderPerCm = 360.0*Gr/(Tdia * PI);
const float DegPerEnc = Tdia/(Wb*Gr);
const float EncPerDeg  =(Wb/Tdia)*Gr ;

const tSensors Lc = S1;
const tSensors Rc = S3;

const tMotor Lm = motorA;
const tMotor Rm = motorB;



// S2 : NXT Sonar : 0x02
//      IR Dist : 0xA8
// S4 : 2 EV3 Sonar : 0x34 / USR   ;   0x38 / USL
//      EV3 Light : 0x32

enum  enSplit { enUSF, enLight, enUSR, enUSL, enIR};//based on direction Front, Left Right
tSensors Ports[] = { S2, S4, S4, S4, S2};
int i2cID[] = { 0x02, 0x32, 0x34, 0x38, 0xA8 };

#endif
