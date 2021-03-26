#ifndef GAD_HPP
#define GAD_HPP
/*! @file gad.hpp */

extern "C"
{
  #include "oxts/gal-c/gad_struct.h"
}

namespace OxTS
{
  

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
  // Gen3d& operator=(const GEN_3D);
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
 */
class Gad 
{
private:
  /** 
   * Type of Aiding (position, velocity, ...). For enumerated values see 
   * GEN_TYPE. 
   */
  int8_t        type;
  /** 
   * Aiding stream ID to identify the source device. 
   * Values 128-254. Each stream should have a unique ID. 
   */
  uint8_t       stream_id;
  /** Sub-struct VALUE. Contains navigation aiding data. */
  Gen3d         val;
  GenFlag       val_valid;
  /** Sub-struct TIME. Contains the time the data was recorded. */
  Gen3d         time;
  GenFlag       time_valid;
  /** Sub-struct LOCATION. Contains lever arm (or alignment) data between the 
   * IMU and aiding source.
   */
  Gen3d         loc;
  GenFlag       loc_valid;
  // Sub-struct RESERVED
  Gen3d         res1;
  GenFlag       res1_valid;
  // Sub-struct RESERVED
  Gen3d         res2;
  GenFlag       res2_valid;
  /** 
   * Acquisition Time Stamp. The INS will fill in this timestamp upon its 
   * arrival to the INS. Leave blank.
   */ 
  uint32_t      acq;                 // Timestamp from INS. Leave empty.
  GenFlag       acq_valid;
protected:
  // type 
  void SetDataType(int type); 
  int  GetDataType(); 
  // val
  void SetValValid();
  void SetValInvalid();
  void SetDataMode(int mode);
  void SetDataValType(int x_type);
  void SetDataVal(double x0, double x1,double x2);
  void SetDataVarUpperDiag(double v0, double v1, double v2, double v3, double v4, double v5);
  void SetDataVarDiag(double v0, double v1,double v2);
  void SetDataVarSingle(double v0);
  // loc  
  void SetLocValid();
  void SetLocInvalid();
  void SetLocMode(int mode);
  void SetLocValType(int x_type);
  void SetLocVal(double x0, double x1,double x2);
  void SetLocVarUpperDiag(double v0, double v1, double v2, double v3, double v4, double v5);
  void SetLocVarDiag(double v0, double v1,double v2);
  void SetLocVarSingle(double v0);

public:
  /*! Default Constructor */
  Gad();
  /*! Constructor */
  Gad(uint8_t stream_id, int8_t aiding_type);
  /*! Destructor */
  ~Gad();
  /*! Copy constructor to allow direct copy to C struct. */
  Gad(const GEN_AIDING_DATA& g);
  Gad(const Gad& g);

  /*! Implicit conversion from Gad to GEN_AIDING_DATA* */
  //operator ::GEN_AIDING_DATA*(){ return this; }
  /*! Implicit const conversion from Gad to GEN_AIDING_DATA* */
  //operator const ::GEN_AIDING_DATA*() const { return this; }

  GEN_AIDING_DATA  getCStruct();
  /** Copy assignment operator GEN_AIDING_DATA -> Gad 
   *  @todo Implement the copy assignment operator GEN_AIDING_DATA -> Gad
  */
  Gad& operator=(const GEN_AIDING_DATA& g);
  // Copy assignment operator Gad -> Gad */
  Gad& operator=(const Gad& g);

  // General Accessors
  /** Set Stream ID for this GAD packet */
  void SetStreamId(int id);
  /** Get Stream ID for this GAD packet */
  int  GetStreamId();

  // Time accessors
  /** Set Time Valid flag to false */
  void SetTimeInvalid();
  /** Set Time Valid flag to true */
  void SetTimeValid();
  /** Set timestamp for this data 
   * @param week GPS Week 
   * @param seconds_from_sunday Seconds from Midnight Sunday (s)
   */
  void   SetGpsTime(double week, double seconds_from_sunday);
  /** Get the GPS Week value. Note that this function assumes that 
   *  the time has been set in this format, there is no check. */
  double GetGpsWeek();
  /** Get the Seconds from Sunday value. Note that this function assumes that 
   *  the time has been set in this format, there is no check. */
  double GetGpsSecondsFromSunday();
  /** Set a PPS relative timestamp
   * @param ns Time since PPS timestamp (nanoseconds)
   */
  void   SetTimePpsRelative(double ns);
  double GetTimePpsRelative();
  /**
   * Set the timestamp type for this data to Latency. The latency is an estimate
   * of the time taken for the packet to travel from the aiding source to the 
   * INS. Upon arrival the INS will timestamp the data, adjusting for the 
   * latency.
   * @param ns Latency estimate in (nanoseconds).
   */
  void   SetTimeLatency(double ns);
  /** Get latency estimate.   */
  double GetTimeLatency();
  /**
   * Set the timestamp type for this data to void. Data with a void timestamp
   * will be timestamped by the INS upon receipt.
   */
  void   SetTimeVoid();
  
  void SetRes1Invalid();
  void SetRes1Valid();
  void SetRes2Invalid();
  void SetRes2Valid();

  // Acquisiton time accessors.
  void SetAcqInvalid();
  void SetAcqValid();
  /*! Set the acquisition time of the data. Not to be used outside of the INS.*/
  void SetAcqTimestamp(uint32_t acq_time);
  /*! Get the acquisition time of the data. Not expected to be set outside of the INS.*/
  uint32_t  GetAcqTimestamp();

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
   * @param stream_id Stream ID for the position aiding source. Must be unique 128-254.
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
   * Set the aiding position in the WGS84 coordinate frame.
   * @param x Position in the x axis of the local frame (m).
   * @param y Position in the y axis of the local frame (m).
   * @param z Position in the z axis of the local frame (m).
   * 
   * @todo Verify WGS84 coordinate frame
   */
  void SetLocalPos(double x, double y, double z);
  /**
   * Set the variance aiding position in the coordinate frame.
   * @param var_x Variance of the position estimate (m^2).
   * @param var_y Variance of the position estimate (m^2).
   * @param var_z Variance of the position estimate (m^2).
   */
  void SetPosVar(double var_x, double var_y, double var_z); // Check these args

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
  /**
   * Constructor
   * 
   * @param stream_id Stream ID for the velocity aiding source. Must be unique 128-254.
   */
  GadVelocity(uint8_t stream_id);
  /**
   * Set the aiding velocity estimate in the local NEU coordinate frame.
   * @param v_n Velocity estimate in the North direction (m/s).
   * @param v_e Velocity estimate in the East direction (m/s).
   * @param v_u Velocity estimate in the Up direction (m/s).
   */
  void SetVelNeu(double v_n, double v_e, double v_u);
  /**
   * Set the aiding velocity estimate in the odometry frame.
   * @param v_x Velocity estimate in the x direction (m/s).
   * @param v_y Velocity estimate in the y direction (m/s).
   * @param v_z Velocity estimate in the z direction (m/s).
   */
  void SetVelOdom(double v_x, double v_y, double v_z);
  /**
   * Set the aiding velocity estimate in the user-defined local coordinate frame.
   * @param v_x Velocity estimate in the x direction (m/s).
   * @param v_y Velocity estimate in the y direction (m/s).
   * @param v_z Velocity estimate in the z direction (m/s).
   */
  void SetVelLocal(double v_x, double v_y, double v_z);
  /**
   * Set the aiding velocity variance estimate in the local NEU coordinate frame.
   * @param v_n Velocity variance estimate in the North direction (m/s)^2.
   * @param v_e Velocity variance estimate in the East direction (m/s)^2.
   * @param v_u Velocity variance estimate in the Up direction (m/s)^2.
   */
  void SetVelNeuVar(double v_n, double v_e, double v_u);
  /**
   * Set the aiding velocity variance estimate in the local NEU coordinate frame.
   * @param v_x Velocity variance estimate in the x direction (m/s)^2.
   * @param v_y Velocity variance estimate in the y direction (m/s)^2.
   * @param v_z Velocity variance estimate in the z direction (m/s)^2.
   */
  void SetVelOdomVar(double v_x, double v_y, double v_z);
  /**
   * Set the aiding velocity variance estimate in the local NEU coordinate frame.
   * @param v_x Velocity variance estimate in the x direction (m/s)^2.
   * @param v_y Velocity variance estimate in the y direction (m/s)^2.
   * @param v_z Velocity variance estimate in the z direction (m/s)^2.
   */
  void SetVelLocalVar(double v_x, double v_y, double v_z);
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
   * Set lever arm from the INS to the aiding source to be taken from the .gap
   * file. This lever arm will be optimised by the Kalman Filter during 
   * navigation. Note that if using this, the GNSS antenna lever arm must be set
   * in mobile.cfg.
   */
  void SetAidingLeverArmOptimising();
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
   * @param v_s Forward speed estimate in the vehicle frame (units).
   */
  void SetSpeedFwVar(double v_s);
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
   * @param v_c Estimated variance (pulses).
   * @todo Clarify units
   */
  void SetWheelspeedVar(double v_c);
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
   * Set lever arm from the INS to the aiding source to be taken from the .gap
   * file. This lever arm will be optimised by the Kalman Filter during 
   * navigation. Note that if using this, the GNSS antenna lever arm must be set
   * in mobile.cfg.
   */
  void SetAidingLeverArmOptimising();
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
public:
  /** Constructor. 
   *  @param stream_id Stream ID for the attitude aiding source. Must be unique 128-254.
  */
  GadAttitude(uint8_t stream_id);
  // val
  /**
   * Set the aiding attitude measurement relative to the NED coordinate frame.
   * @param heading (deg)
   * @param pitch   (deg)
   * @param roll    (deg)
   * 
   * @todo Confirm whether the roll estimate is used from the update.
   */
  void SetAtt(double heading, double pitch, double roll);
  /**
   * Set the estimated variance on the aiding attitude measurement.
   * @param v_h Variance estimate on the heading angle (deg)^2
   * @param v_p Variance estimate on the pitch angle (deg)^2
   * @param v_r Variance estimate on the roll angle (deg)^2
   */
  void SetAttVar(double v_h, double v_p, double v_r);
  /**
   * Set the angles which specify the rotation required to align the IMU and 
   * aiding sensor frames. This alignment will not be optimised by the INS.
   * @param x
   * @param y
   * @param z
   */
  void SetAidingAlignmentFixed(double x, double y, double z);
  /**
   * Set alignment to be optimised by the INS. The alignment values will be read
   * from the mobile.att file, so are not set here.
   */
  void SetAidingAlignmentOptimising();
  /**
   * Set the estimated variance (error) on the alignment angles between the IMU 
   * and aiding sensor frames.
   * @param x
   * @param y
   * @param z
   */
  void SetAidingAlignmentVar(double x, double y, double z);
};

}



#endif // GAD_HPP