#ifndef GAD_HPP
#define GAD_HPP
/*! @file gad.hpp */

#include <vector>

#include "oxts/gal-c/gad_struct.h"


namespace OxTS
{
  

using GenFlag = GEN_BOOL;
/**
 * Cpp wrapper class for C struct GEN_3D.
 * 
 * Provides an interface for concrete data structures used in Gad.
 */
class Gen3d : public GEN_3D
{
public:
  /*! Default Constructor */
  Gen3d();
  /*! Destructor */
  ~Gen3d() = default;
  /*! Copy constructor */
  explicit Gen3d(const GEN_3D& g);

  /*! Implicit conversion from Gen3d to GEN_3D* */
  explicit operator ::GEN_3D*(){ return this; }
  /*! Implicit const conversion from Gen3d to GEN_3D* */
  explicit operator const ::GEN_3D*() const { return this; }


  auto getCStruct() const -> GEN_3D;

  // Accessor functions 
  /*! Set the struct mode. Typically set to 0.*/
  void SetMode(int mode);
  /*! Set the struct mode.*/
  auto GetMode() const -> int;
  /** Set the value type. Index source depends on use of the struct. Sources
   *  include ::POS_SYS_TYPE, ::VEL_SYS_TYPE, ::SPEED_SYS_TYPE, ::LOC_SYS.
   */
  void SetValType(int x_type);
  /*! Get the value type. See ::GetMode() for indexes */
  auto GetValType() const -> int;

  void SetValX(double x);
  auto GetValX() const -> double;
  void SetValY(double y);
  auto GetValY() const -> double;
  void SetValZ(double z);
  auto GetValZ() const -> double;
  /*! Set the value array. Used to store the aiding data.*/
  void SetVal(double x, double y,double z);

  auto GetVarType() const -> int;
  void SetVarUpperDiag(double v_00, double v_11, double v_22, 
                       double v_01, double v_02, double v_12);
  void SetVarDiag(double v_00, double v_11,double v_22);
  void SetVarSingle(double v_0);
  auto GetVar() const -> std::vector<double>;

};


/**
 * Cpp wrapper class for C struct GEN_AIDING_DATA
 */
class Gad 
{
private:
  /** Type of Aiding (position, velocity, ...). For enumerated values see 
   * GEN_TYPE. 
   */
  int8_t        type = {0};
  /** Aiding stream ID to identify the source device. 
   *  Values 128-254. Each stream should have a unique ID. 
   */
  uint8_t       stream_id = {0};
  /** Sub-struct VALUE. Contains navigation aiding data. */
  Gen3d         val;
  GenFlag       val_valid = {0};
  /** Sub-struct TIME. Contains the time the data was recorded. */
  Gen3d         time;
  GenFlag       time_valid = {0};
  /** Sub-struct LOCATION. Contains lever arm (or alignment) data between the 
   * IMU and aiding source.
   */
  Gen3d         loc;
  GenFlag       loc_valid = {0};
  // Sub-struct RESERVED
  Gen3d         res1;
  GenFlag       res1_valid = {0};
  // Sub-struct RESERVED
  Gen3d         res2;
  GenFlag       res2_valid = {0};
  /** 
   * Acquisition Time Stamp. The INS will fill in this timestamp upon its 
   * arrival to the INS. Leave blank.
   */ 
  uint32_t      acq = {0};                 // Timestamp from INS. Leave empty.
  GenFlag       acq_valid = {0};
protected:
  // type 
  void SetDataType(int type); 
  auto  GetDataType() const -> int; 
  // val
  void SetValValid();
  void SetValInvalid();
  void SetDataMode(int mode);
  void SetDataValType(int x_type);
  void SetDataVal(double x_0, double x_1,double x_2);
  void SetDataVarUpperDiag(double v_00, double v_11, double v_22, 
                           double v_01, double v_02, double v_12);
  void SetDataVarDiag(double v_0, double v_1,double v_2);
  void SetDataVarSingle(double v_0);
  // loc  
  void SetLocValid();
  void SetLocInvalid();
  void SetLocMode(int mode);
  void SetLocValType(int x_type);
  void SetLocVal(double x_0, double x_1,double x_2);
  void SetLocVarUpperDiag(double v_00, double v_11, double v_22, 
                          double v_01, double v_02, double v_12);
  void SetLocVarDiag(double v_00, double v_11,double v_22);
  void SetLocVarSingle(double v_0);

public:
  /*! Default Constructor */
  Gad();
  /*! Constructor */
  Gad(uint8_t stream_id, int8_t aiding_type);
  /*! Destructor */
  ~Gad();
  /*! Copy constructor */
  Gad(const Gad& g);
  /*! Copy constructor to allow direct copy to C struct. */
  explicit Gad(const GEN_AIDING_DATA& g);
  // Copy assignment operator Gad -> Gad */
  auto operator=(const Gad& g) -> Gad&;
  // Copy data from Gad to an instance of the C struct GEN_AIDING_DATA
  auto  getCStruct() -> GEN_AIDING_DATA;
  /** Copy assignment operator GEN_AIDING_DATA -> Gad   */
  auto operator=(const GEN_AIDING_DATA& g) -> Gad&;

  // General Accessors
  /** Set Stream ID for this GAD packet */
  void SetStreamId(int id);
  /** Get Stream ID for this GAD packet */
  auto GetStreamId() const -> int;

  // Time accessors
  /** Set Time Valid flag 
   * @param flag boolean to indicate whether time is valid or invalid
   */
  void SetTimeValid(bool flag);
  /** Set Time Valid flag 
  * @return flag boolean to indicate whether time validity
  */
  bool GetTimeValid();

  /** Set time from an external clock
   * @param week Week in the external time frame
   * @param seconds Seconds in the external time frame
   */
  void   SetTimeExternal(double week, double secs);
  /** Get the week in the external time */
  auto GetTimeExternalWeek() const -> double;
  /** Get the seconds into the week in the external time */
  auto GetTimeExternalSecondsFromSunday() const -> double;
  /** Set timestamp for this data 
   * @param week GPS Week 
   * @param seconds_from_sunday Seconds from Midnight Sunday (s)
   */
  void   SetTimeGps(double week, double seconds_from_sunday);
  /** Get the GPS Week value. Note that this function assumes that 
   *  the time has been set in this format, there is no check. */
  auto GetTimeGpsWeek() const -> double;
  /** Get the Seconds from Sunday value. Note that this function assumes that 
   *  the time has been set in this format, there is no check. */
  auto GetTimeGpsSecondsFromSunday() const -> double;
  /** Set a PPS relative timestamp
   * @param ns Time since PPS timestamp (nanoseconds)
   */
  void   SetTimePpsRelative(double ns);
  auto GetTimePpsRelative() const -> double;
  /**
   * Set the timestamp type for this data to Latency. The latency is an estimate
   * of the time taken for the packet to travel from the aiding source to the 
   * INS. Upon arrival the INS will timestamp the data, adjusting for the 
   * latency.
   * @param ns Latency estimate in (nanoseconds).
   */
  void   SetTimeLatency(double ns);
  /** Get latency estimate.   */
  auto GetTimeLatency() const -> double;
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
  auto  GetAcqTimestamp() const -> uint32_t;

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
  explicit GadPosition(uint8_t stream_id);
  /**
   * Set the aiding position in the WGS84 coordinate frame.
   * @param lat Latitude of the position estimate (deg).
   * @param lon Longitude of the position estimate (deg).
   * @param alt Altitude of the position estimate (deg).
   */
  void SetPosGeodetic(double lat, double lon, double alt);
  /**
   * Set the aiding position in the user-defined local coordinate frame.
   * @param x Position in the x axis of the local frame (m).
   * @param y Position in the y axis of the local frame (m).
   * @param z Position in the z axis of the local frame (m).
   */
  void SetPosLocal(double x, double y, double z);
  /**
   * Set the variance aiding position in the coordinate frame.
   * @param v_n Variance of the position estimate (m^2).
   * @param v_e Variance of the position estimate (m^2).
   * @param v_d Variance of the position estimate (m^2).
   */
  void SetPosGeodeticVar(double v_n, double v_e, double v_d);
  /**
   * Set the variance aiding position in the coordinate frame.
   * @param v_x Variance of the position estimate (m^2).
   * @param v_y Variance of the position estimate (m^2).
   * @param v_z Variance of the position estimate (m^2).
   */
  void SetPosLocalVar(double v_x, double v_y, double v_z);
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
   * Set lever arm from the INS to the position aiding source. to be
   * optimised by the Kalman Filter during navigation.
   */
  void SetAidingLeverArmOptimising();
  /** 
   * Indicate that lever arm will be configured in the configuration file on 
   * the INS.
   */
  void SetAidingLeverArmConfig();
  /**
   * Set the variance (accuracy) of the lever arm measurements from the INS to 
   * the aiding source. Only required for fixed lever-arm.
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
  explicit GadVelocity(uint8_t stream_id);
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
  explicit GadSpeed(uint8_t stream_id);

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
  explicit GadAttitude(uint8_t stream_id);
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

} // namespace OxTS



#endif // GAD_HPP