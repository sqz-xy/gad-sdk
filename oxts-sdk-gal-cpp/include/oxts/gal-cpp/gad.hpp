#ifndef GAD_H
#define GAD_H
/*! \file gad.hpp */

extern "C"
{
  #include "oxts/gal-c/gad_struct.h"
}

typedef GEN_BOOL GenFlag;

/**
 * Cpp wrapper class for C struct GEN_3D.
 * 
 * Provides an interface for concrete data structures used in Gad.
 */
class Gen3d : private GEN_3D
{
public:
  /*! Default Constructor */
  Gen3d()
  {
    SetMode(0);
    SetValType(0);
    SetVal(0.0,0.0,0.0);
    SetVarUpperDiag(0.0,0.0,0.0,0.0,0.0,0.0);
  }
  /*! Destructor */
  ~Gen3d(){ }
  /*! Copy constructor */
  Gen3d(const GEN_3D& g);

  /*! Implicit conversion from Gen3d to GEN_3D* */
  operator ::GEN_3D*(){ return this; }
  /*! Implicit const conversion from Gen3d to GEN_3D* */
  operator const ::GEN_3D*() const { return this; }

  /*! Copy assignment operator Gen3d -> GEN_3D */
  Gen3d& operator=(const GEN_3D);
  /*! Copy assignment operator Gen3d -> Gen3d */
  //Gen3d& operator=(const Gen3d& g);


  // Accessor functions 
  /*! Set the struct mode. Typically set to 0.*/
  void SetMode(int mode);
  /*! Set the struct mode.*/
  int  GetMode();
  /** Set the value type. Index source depends on use of the struct. Sources
   *  include ::POS_SYS_TYPE, ::VEL_SYS_TYPE, ::SPEED_SYS_TYPE, ::LOC_SYS.
   */
  void SetValType(int x_type);
  /*! Get the value type. See ::GetMode() for indexes */
  int  GetValType();

  void   SetValX(double x);
  double GetValX();
  void   SetValY(double y);
  double GetValY();
  void   SetValZ(double z);
  double GetValZ();
  /*! Set the value array. Used to store the aiding data.*/
  void   SetVal(double x, double y,double z);

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
  GenFlag       val_valid;

  /** Sub-struct TIME. Contains the time the data was recorded. */
  Gen3d*        time;                
  GenFlag       time_valid;

  /** 
   * Sub-struct LOCATION. Contains lever arm (or alignment) data between the 
   * IMU and aiding source.
   */
  Gen3d*        loc;                 // Location/Position of Generic Aiding Device (lever arm)
  GenFlag       loc_valid;

  // Sub-struct RESERVED
  Gen3d*        res1;
  GenFlag       res1_valid;          

  // Sub-struct RESERVED
  Gen3d*        res2;
  GenFlag       res2_valid;          

  /** 
   * Acquisition Time Stamp. The INS will fill in this timestamp upon its 
   * arrival to the INS. Leave blank.
   */ 
  uint32_t      acq;                 // Timestamp from INS. Leave empty.
  GenFlag       acq_valid;

public:
  /*! Default Constructor */
  Gad();
  /*! Constructor */
  Gad(uint8_t stream_id, int8_t aiding_type);
  /*! Destructor */
  ~Gad();

  /*! Copy constructor */
  Gad(const GEN_AIDING_DATA& g);
  Gad(const Gad& g);

  /*! Implicit conversion from Gad to GEN_AIDING_DATA* */
  // operator ::GEN_AIDING_DATA*(){ return this; }
  /*! Implicit const conversion from Gad to GEN_AIDING_DATA* */
  // operator const ::GEN_AIDING_DATA*() const { return this; }

  /** Copy assignment operator GEN_AIDING_DATA -> Gad 
   *  @todo Implement the copy assignment operator GEN_AIDING_DATA -> Gad
  */
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
  void SetValValid(GenFlag validity);
  void SetDataMode(int mode);
  void SetDataValType(int x_type);
  void SetDataVal(double x0, double x1,double x2);
  void SetDataVarUpperDiag(double v0, double v1, double v2, double v3, double v4, double v5);
  void SetDataVarDiag(double v0, double v1,double v2);
  void SetDataVarSingle(double v0);
  // time

  // loc  
  void SetLocValid(GenFlag validity);
  void SetLocMode(int mode);
  void SetLocValType(int x_type);
  void SetLocVal(double x0, double x1,double x2);
  void SetLocVarUpperDiag(double v0, double v1, double v2, double v3, double v4, double v5);
  void SetLocVarDiag(double v0, double v1,double v2);
  void SetLocVarSingle(double v0);

  // Time accessors
  void SetTimeValid(GenFlag validity);
  // GPS
  void   SetGpsTime(double week, double secondsFromSunday);
  double GetGpsWeek();
  double GetGpsSecondsFromSunday();
  // PPS
  void   SetTimePpsRelative(double ns);
  double GetTimePpsRelative();
  // Latency
  void   SetTimeLatency(double ns);
  double GetTimeLatency();
  // Void
  void   SetTimeVoid();
  
  // Acquisiton time accessors.
  /*! Set the acquisition time of the data. Not to be used outside of the INS.*/
  void SetAcqTimestamp();
  /*! Get the acquisition time of the data. Not expected to be set outside of the INS.*/
  int  GetAcqTimestamp();

};

/**
 * Generic Aiding position. 
 */
class GadPosition : public Gad
{
private:

public:
  /**
   * Constructor
   * 
   * @param stream_id Stream ID for the position aiding. Must be unique 128-254.
   */
  GadPosition(uint8_t stream_id);
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
private:

public:
  GadVelocity(uint8_t stream_id);
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
 * Generic Aiding speed. 
 */
class GadSpeed : public Gad
{
private:

public:
  GadSpeed(uint8_t stream_id);

  /**
   * Set the forward speed aiding estimate. 
   * 
   * @param speed Forward speed estimate in the vehicle frame (m/s).
   */
  void SetSpeedFw(double speed);
  /**
   * Set estimated variance on the forward speed aiding measurement. 
   * 
   * @param varS Forward speed estimate in the vehicle frame (units).
   */
  void SetSpeedFwVar(double varS);
  /**
   * Set the pulse count measurement from a wheelspeed encoder. 
   * 
   * @param count Number of pulses recorded during the period.
   * @param period The period over which the current pulse count was recorded.
   * 
   * @todo Clarify where the timestamp should correspond to in the period: 
   * start, middle, end.
   */
  void SetWheelspeedCount(double count, double period);
  /**
   * Set the estimated variance on the wheelspeed pulse count. 
   * 
   * @param varC Estimated variance (pulses).
   * @todo Clarify units
   */
  void SetWheelspeedVar(double varC);

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
 * Generic Aiding attitude. 
 */
class GadAttitude : public Gad
{
private:

public:
  // val
  void SetAtt(double heading, double pitch, double roll);
  void SetAttVar(double varH, double varP, double varR);

  // loc 
  void SetAidingAlignmentFixed(double x, double y, double z);
  void SetAidingAlignmentOptimising(double x, double y, double z);
  void SetAidingAlignmentVar(double x, double y, double z);
};




#endif // GAD_H