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


  // General Accessors
  // streamId
  void SetStreamId(int id) { this->stream_id = id; }
  int  GetStreamId() { return this->stream_id; }
  // type 
  void SetDataType(int type); 
  int  GetDataType(); 
  // val
  void SetDataMode(int mode);
  void SetDataValType(int x_type);
  void SetDataVal(double x0, double x1,double x2);
  void SetDataVarUpperDiag(double v0, double v1, double v2, double v3, double v4, double v5);
  void SetDataVarDiag(double v0, double v1,double v2);
  void SetDataVarSingle(double v0);
  // time

  // loc  
  void SetLocMode(int mode);
  void SetLocValType(int x_type);
  void SetLocVal(double x0, double x1,double x2);
  void SetLocVarUpperDiag(double v0, double v1, double v2, double v3, double v4, double v5);
  void SetLocVarDiag(double v0, double v1,double v2);
  void SetLocVarSingle(double v0);

  // Time accessors
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

  // Loc accessors
  void SetFixedLoc(double x, double y, double z);
  void SetOptimisingLoc(double x, double y, double z);
  void SetLocVar(double x, double y, double z);
};

/**
 * Generic Aiding position. 
 */
class GadPosition : public Gad
{
  /**
   * Set the aiding position in the WGS84 coordinate frame.
   * @param lat Latitude of the position estimate (deg).
   * @param lon Longitude of the position estimate (deg).
   * @param alt Altitude of the position estimate (deg).
   */
  void SetWgs84Pos(double lat, double lon, double alt);
  /**
   * Set the variance aiding position in the WGS84 coordinate frame.
   * @param varLat Variance of the Latitude position estimate (units).
   * @param varLon Variance of the Longitude position estimate (units).
   * @param varAlt Variance of the Altitude position estimate (units).
   */
  void SetWgs84PosVar(double varLat, double varLon, double varAlt); // Check these args

  /**
   * Set lever arm from the INS to the aiding source. This lever arm will not be
   * optimised by the Kalman Filter.
   * 
   * @param x Offset from INS to aiding source in the x axis of the IMU frame (m).
   * @param y Offset from INS to aiding source in the y axis of the IMU frame (m).
   * @param z Offset from INS to aiding source in the z axis of the IMU frame (m).
   */
  void SetAidingFixedLeverArm(double x, double y, double z);
  /**
   * Set lever arm from the INS to the aiding source. This lever arm will be
   * optimised by the Kalman Filter during navigation.
   * 
   * @param x Offset from INS to aiding source in the x axis of the IMU frame.
   * @param y Offset from INS to aiding source in the y axis of the IMU frame.
   * @param z Offset from INS to aiding source in the z axis of the IMU frame.
   */
  void SetAidingOptimisingLeverArm(double x, double y, double z);
  /** 
   * Indicate that lever arm will be configured in the configuration file on 
   * the INS.
   * @todo Remove and set this mode to be default 
   */
  void SetAidingConfigLeverArm();
  /**
   * Set lever arm from the INS to the aiding source. This lever arm will be
   * optimised by the Kalman Filter during navigation.
   * 
   * @param x Variance on the lever arm from INS to aiding source in the x axis of the IMU frame.
   * @param y Variance on the lever arm from INS to aiding source in the y axis of the IMU frame.
   * @param z Variance on the lever arm from INS to aiding source in the z axis of the IMU frame.
   */ 
  void SetAidingLeverArmVar(double x, double y, double z);
};

/**
 * Generic Aiding velocity. 
 */
class GadVelocity : public Gad
{
  // val
  void SetVelNeu(double vN, double vE, double vU);
  void SetVelNeuVar(double varN, double varE, double varU);
  
  // loc 
  void SetAidingFixedLeverArm(double x, double y, double z);
  void SetAidingOptimisingLeverArm(double x, double y, double z);
  void SetAidingLeverArmVar(double x, double y, double z);
};

/**
 * Generic Aiding speed. 
 */
class GadSpeed : public Gad
{
  // val
  void SetSpeedFw(double sF);
  void SetSpeedFwVar(double vS);
  void SetWheelspeedVar(double count);

  // loc 
  void SetAidingFixedLeverArm(double x, double y, double z);
  void SetAidingOptimisingLeverArm(double x, double y, double z);
  void SetAidingLeverArmVar(double x, double y, double z);
};

/**
 * Generic Aiding attitude. 
 */
class GadAttitude : public Gad
{
  // val
  void SetAtt(double heading, double pitch, double roll);
  void SetAttVar(double varH, double varP, double varR);

  // loc 
  void SetAidingFixedOffset(double x, double y, double z);
  void SetAidingOptimisingOffset(double x, double y, double z);
  void SetAidingOffsetVar(double x, double y, double z);
};




#endif // GAD_H