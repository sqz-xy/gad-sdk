#ifndef GAD_H
#define GAD_H

extern "C"
{
  #include "oxts/gal-c/gad_struct.h"
}

typedef GEN_BOOL GenBool;


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

  /*! Implicit conversion from Gen3d to GEN_3D* */
  operator ::GEN_3D*(){ return this; }
  /*! Implicit const conversion from Gen3d to GEN_3D* */
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
 */
class Gad 
{
private:
  /** 
   * Type of Aiding (position, velocity, ...). For enumerated values see 
   * GEN_TYPE. 
   */
  int8_t        type;                // GEN_TYPE - type of data 

  /** 
   * Aiding stream ID to identify the source device. 
   * Values 128-254. Each stream should have a unique ID. 
   */
  uint8_t       stream_id;

  /** Sub-struct VALUE. Contains navigation aiding data. */
  Gen3d*        val;                 // Navigation data
  GenBool       val_valid;

  /** Sub-struct TIME. Contains the time the data was recorded. */
  Gen3d*        time;                
  GenBool       time_valid;

  /** 
   * Sub-struct LOCATION. Contains lever arm (or alignment) data between the 
   * IMU and aiding source.
   */
  Gen3d*        loc;                 // Location/Position of Generic Aiding Device (lever arm)
  GenBool       loc_valid;

  // Sub-struct RESERVED
  Gen3d*        res1;
  GenBool       res1_valid;          

  // Sub-struct RESERVED
  Gen3d*        res2;
  GenBool       res2_valid;          

  /** 
   * Acquisition Time Stamp. The INS will fill in this timestamp upon its 
   * arrival to the INS. Leave blank.
   */ 
  uint32_t      acq;                 // Timestamp from INS. Leave empty.
  GenBool       acq_valid;
public:
  /*! Default Constructor */
  Gad();
  /*! Destructor */
  ~Gad();

  /*! Copy constructor */
  Gad(const GEN_AIDING_DATA& g);

  /*! Implicit conversion from Gad to GEN_AIDING_DATA* */
  // operator ::GEN_AIDING_DATA*(){ return this; }
  /*! Implicit const conversion from Gad to GEN_AIDING_DATA* */
  // operator const ::GEN_AIDING_DATA*() const { return this; }

  // Copy assignment operator GEN_AIDING_DATA -> Gad */
  Gad& operator=(const GEN_AIDING_DATA& g);
  // Copy assignment operator Gad -> Gad */
  Gad& operator=(const Gad& g);

  // General Accessors
  // streamId
  void SetStreamId(int id);
  int  GetStreamId();
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
   * 
   * @todo Verify WGS84 coordinate frame
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
  void SetAidingLeverArmFixed(double x, double y, double z);
  /**
   * Set lever arm from the INS to the aiding source. This lever arm will be
   * optimised by the Kalman Filter during navigation.
   * 
   * @param x Offset from INS to aiding source in the x axis of the IMU frame.
   * @param y Offset from INS to aiding source in the y axis of the IMU frame.
   * @param z Offset from INS to aiding source in the z axis of the IMU frame.
   */
  void SetAidingLeverArmOptimising(double x, double y, double z);
  /** 
   * Indicate that lever arm will be configured in the configuration file on 
   * the INS.
   * @todo Remove and set this mode to be default 
   */
  void SetAidingLeverArmConfig();
  /**
   * Set the variance (accuracy) of the lever arm measurements from the INS to 
   * the aiding source. 
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
  /**
   * Set the aiding velocity estimate in the local NEU coordinate frame.
   * @param vN Velocity estimate in the North direction (m/s).
   * @param vE Velocity estimate in the East direction (m/s).
   * @param vU Velocity estimate in the Up direction (m/s).
   */
  void SetVelNeu(double vN, double vE, double vU);
  /**
   * Set the aiding velocity variance estimate in the local NEU coordinate frame.
   * @param varN Velocity variance estimate in the North direction (m/s).
   * @param varE Velocity variance estimate in the East direction (m/s).
   * @param varU Velocity variance estimate in the Up direction (m/s).
   */
  void SetVelNeuVar(double varN, double varE, double varU);
  
  // loc 
  void SetAidingLeverArmFixed(double x, double y, double z);
  void SetAidingLeverArmOptimising(double x, double y, double z);
  void SetAidingLeverArmVar(double x, double y, double z);
};

/**
 * Generic Aiding speed. 
 */
class GadSpeed : public Gad
{
  // val
  void SetSpeedFw(double speed);
  void SetSpeedFwVar(double varS);
  void SetWheelspeedCount(double count);
  void SetWheelspeedVar(double varC);

  // loc 
  void SetAidingLeverArmFixed(double x, double y, double z);
  void SetAidingLeverArmOptimising(double x, double y, double z);
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
  void SetAidingAlignmentFixed(double x, double y, double z);
  void SetAidingAlignmentOptimising(double x, double y, double z);
  void SetAidingAlignmentVar(double x, double y, double z);
};




#endif // GAD_H