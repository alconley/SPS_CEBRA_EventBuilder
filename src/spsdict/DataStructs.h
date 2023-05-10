/*DataStructs.h
 *Data structures for analysis. To be implemented as a dictionary for ROOT in LinkDef
 *Based on: FocalPlane_SABRE.h
 *Gordon M. Oct. 2019
 */
#ifndef DATA_STRUCTS_H
#define DATA_STRUCTS_H

#include <vector>

struct DPPChannel 
{
  double Timestamp;
  int Channel, Board, Energy, EnergyShort;
  int Flags;
};

struct DetectorHit 
{
  double Long=-1, Short=-1, Time=-1;
  int Ch=-1;
};

struct CeBrADetector 
{
  std::vector<DetectorHit> cebr;
};


struct FPDetector 
{
  std::vector<DetectorHit> delayFL, delayFR, delayBL, delayBR;
  std::vector<DetectorHit> anodeF, anodeB, scintL, scintR, cathode;
  std::vector<DetectorHit> monitor;
};

struct CoincEvent 
{
  FPDetector focalPlane;
  CeBrADetector cebraArray[5]; 
};

struct ProcessedEvent 
{
  double fp1_tdiff = -1e6, fp2_tdiff = -1e6, fp1_tsum = -1, fp2_tsum = -1,
           fp1_tcheck = -1, fp2_tcheck = -1;
  double fp1_y=-1, fp2_y=-1;
  double anodeFront = -1, anodeBack = -1, scintRight = -1, scintLeft = -1;
  double scintRightShort = -1, scintLeftShort = -1;
  double cathode = -1;
  double xavg = -1e6, x1 = -1e6, x2 = -1e6;
  double theta = -1e6;

  
  double delayFrontRightE = -1, delayFrontLeftE = -1;
  double delayBackRightE = -1, delayBackLeftE = -1;
  double delayFrontRightShort = -1, delayFrontLeftShort = -1;
  double delayBackRightShort = -1, delayBackLeftShort = -1;
  double anodeFrontTime = -1, anodeBackTime = -1;
  double scintRightTime = -1, scintLeftTime = -1;
  double delayFrontMaxTime = -1, delayBackMaxTime = -1;
  double delayFrontLeftTime = -1, delayFrontRightTime = -1;
  double delayBackLeftTime = -1, delayBackRightTime = -1;
  double cathodeTime = -1;

  double monitorE = -1, monitorShort = -1;
  double monitorTime = -1;

  double cebraE[5] = {-1,-1,-1,-1,-1};
  double cebraChannel[5] = {-1,-1,-1,-1,-1};
  double cebraTime[5] = {-1,-1,-1,-1,-1};

  double cebraE0 = -1;
  double cebraE1 = -1;
  double cebraE2 = -1;
  double cebraE3 = -1;
  double cebraE4 = -1;

  double cebraChannel0 = -1;
  double cebraChannel1 = -1;
  double cebraChannel2 = -1;
  double cebraChannel3 = -1;
  double cebraChannel4 = -1;


  double cebraTime0 = -1;
  double cebraTime1 = -1;
  double cebraTime2 = -1;
  double cebraTime3 = -1;
  double cebraTime4 = -1;





  CeBrADetector cebraArray[5];
};

/*
  ROOT does a bad job of ensuring that header-only type dictionaries (the only type they explicity accept)
  are linked when compiled as shared libraries (the recommended method). As a work around, as a dummy function that 
  ensures the library is linked (better than no-as-needed which I dont think is in general supported across platforms)
*/
bool EnforceDictionaryLinked();

#endif
