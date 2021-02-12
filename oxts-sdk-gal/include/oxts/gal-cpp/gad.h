#ifndef GAD_H
#define GAD_H

#include "oxts/gal-c/gad_struct.h"

/**
 * Cpp wrapper class for C struct GEN_3D.
 * 
 * Provides an interface for concrete data structures used in Gad.
 */
class Gen3d : private GEN_3D
{
public:
  /*! Default Constructor */
  Gen3d();
  /*! Destructor */
  ~Gen3d();
  /*! Copy constructor */
  Gen3d(const GEN_3D& g);

  /*! Implicit conversion from Gad to GEN_AIDING_DATA* */
  operator ::GEN_3D*(){ return this; }
  /*! Implicit const conversion from Gad to GEN_AIDING_DATA* */
  operator const ::GEN_3D*() const { return this; }

  /*! Copy assignment operator GEN_AIDING_DATA -> Gad */
  Gen3d& operator=(const GEN_3D);
  /*! Copy assignment operator Gad -> Gad */
  Gen3d& operator=(const Gen3d& g);


  // Accessor functions 
  void SetMode(int mode);
  void SetValType(int x_type);
  void SetVal(double x0, double x1,double x2);
  void SetVarUpperDiag(double v0, double v1, double v2, double v3, double v4, double v5);
  void SetVarDiag(double v0, double v1,double v2);
  void SetVarSingle(double v0);

};




/**
 * Cpp wrapper class for C struct GEN_AIDING_DATA
 * 
 * Contains Generic Aiding data. The class also acts as a creator for Gen3d 
 * concrete implentations.
 */
class Gad : private GEN_AIDING_DATA
{
private:

public:
  /*! Default Constructor */
  Gad();
  /*! Destructor */
  ~Gad();

  /*! Copy constructor */
  Gad(const GEN_AIDING_DATA& g);

  /*! Implicit conversion from Gad to GEN_AIDING_DATA* */
  operator ::GEN_AIDING_DATA*(){ return this; }
  /*! Implicit const conversion from Gad to GEN_AIDING_DATA* */
  operator const ::GEN_AIDING_DATA*() const { return this; }

  // Copy assignment operator GEN_AIDING_DATA -> Gad */
  Gad& operator=(const GEN_AIDING_DATA& g);
  // Copy assignment operator Gad -> Gad */
  Gad& operator=(const Gad& g);

  // Implement C functions on struct as member functions (reset, delete, etc.)
  // ... 

  // Accessing struct data. 

  // Set streamId
  void SetStreamId(int id) { this->stream_id = id; }
  int  GetStreamId() { return this->stream_id; }

  // Aiding data acccessors
  // Position
  void SetWgs84Pos(double lat, double lon, double alt);
  void SetWgs84PosVar(double varLat, double varLon, double varAlt); // Check these args
  // Velocity
  void SetVelNeu(double vN, double vE, double vU);
  void SetVelNeuVar(double varN, double varE, double varU);

  // Speed / Wheelspeed
  void SetSpeedFw(double sF);
  void SetWheelspeed(double count, double period);

  // Attitude
  void SetAtt(double heading, double pitch, double roll);

  // Time setting functionality
  // GPS
  void   SetGpsTime(double week, double secondsFromSunday);
  int    GetGpsWeek();
  double GetGpsSecondsFromSunday();
  // PPS
  void   SetTimePpsRelative(double ns);
  double GetTimePpsRelative();
  // Latency
  void   SetTimeLatency(double ns);
  double GetTimeLatency();
  // Void
  void   SetTimeVoid();

  // Loc setting functionality
  void SetFixedLeverArm(double x, double y, double z);
  void SetOptimisingLeverArm(double x, double y, double z);
  void SetFixedOrientationOffset(double x, double y, double z);
  void SetOptimisingOrientationOffset(double x, double y, double z);
};






#endif // GAD_H