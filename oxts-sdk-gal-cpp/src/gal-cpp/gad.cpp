#include "oxts/gal-cpp/gad.hpp"

using std::vector;

namespace OxTS
{

//==============================================================================
// Gen3d

Gen3d::Gen3d() : GEN_3D()
{
  SetMode(0);
  SetValType(0);
  SetVal(0.0,0.0,0.0);
  SetVarUpperDiag(0.0,0.0,0.0,0.0,0.0,0.0);
}

Gen3d::Gen3d(const GEN_3D& g) : GEN_3D()
{
  SetMode(g.mode);
  SetValType(g.x_type);
  SetVal(g.x[0], g.x[1], g.x[2]);
  this->v_type = g.v_type;
  switch (g.v_type)
  {
    case GEN_VAR_TYPE::GEN_VAR_HMAT:
      SetVarUpperDiag(g.v[0],g.v[1],g.v[2],g.v[3],g.v[4],g.v[5]);
      break;
    case GEN_VAR_TYPE::GEN_VAR_DIAG:
      SetVarDiag(g.v[0],g.v[1],g.v[2]);
      break;
    case GEN_VAR_TYPE::GEN_VAR_SINGLE:
      SetVarSingle(g.v[0]);
      break;
    default:
      break;
  }
}

auto Gen3d::GetVarType() const -> int {return static_cast<int>(this->v_type);}

auto Gen3d::getCStruct() const -> GEN_3D
{
  GEN_3D g;
  g.mode   = this->GetMode(); 
  g.v_type = this->GetValType();
  g.x[0]   = this->GetValX();
  g.x[1]   = this->GetValY();
  g.x[2]   = this->GetValZ();
  g.v_type = this->GetVarType();
  std::vector<double> cov = this->GetVar();
  for (int i = 0; i < cov.size(); ++i)
  {
    g.v[i] = cov.at(i);
  }
  
  return g;
}

void Gen3d::SetMode(int mode){ this->mode = mode; }
auto Gen3d::GetMode() const -> int {return this->mode;}
void Gen3d::SetValType(int x_type){ this->x_type = x_type; }
auto Gen3d::GetValType() const -> int {return this->v_type;}

void Gen3d::SetValX(double x){this->x[0] = x;}
auto Gen3d::GetValX() const -> double{return this->x[0];}
void Gen3d::SetValY(double y){this->x[1] = y;}
auto Gen3d::GetValY() const -> double{return this->x[1];}
void Gen3d::SetValZ(double z){this->x[2] = z;}
auto Gen3d::GetValZ() const -> double{return this->x[2];}

void Gen3d::SetVal(double x, double y,double z)
{
  this->SetValX(x);
  this->SetValY(y);
  this->SetValZ(z);
}
auto Gen3d::GetVal() const -> std::vector<double>
{
  return std::vector<double> {
    this->GetValX(),
    this->GetValY(),
    this->GetValZ()
  };
}

void Gen3d::SetVarUpperDiag(double v_00, double v_11, double v_22, 
                       double v_01, double v_02, double v_12)
{
  this->v_type = GEN_VAR_TYPE::GEN_VAR_HMAT;
  this->v[0] = v_00;
  this->v[1] = v_11;
  this->v[2] = v_22;
  this->v[3] = v_01;
  this->v[4] = v_02;
  this->v[5] = v_12;
}

void Gen3d::SetVarDiag(double v_00, double v_11,double v_22)
{
  this->v_type = GEN_VAR_TYPE::GEN_VAR_DIAG;
  this->v[0] = v_00;
  this->v[1] = v_11;
  this->v[2] = v_22;
}

void Gen3d::SetVarSingle(double v_0)
{
  this->v_type = GEN_VAR_TYPE::GEN_VAR_SINGLE;
  this->v[0] = v_0;
}

auto Gen3d::GetVar() const -> std::vector<double>
{
  std::vector<double> cov;
  int length = 0;

  switch (this->v_type)
  {
    case GEN_VAR_TYPE::GEN_VAR_HMAT:
      length = 6;
      break;
    case GEN_VAR_TYPE::GEN_VAR_DIAG:
      length = 3;
      break;
    case GEN_VAR_TYPE::GEN_VAR_SINGLE:
      length = 1;
      break;
  }

  for (int i = 0; i<length; ++i) {
    cov.push_back(v[i]);
  } 

  return cov;
}


//==============================================================================
// Gad superclass
const int DEFAULT_STREAM_ID = 128;
// Default Constructor
Gad::Gad() :
     stream_id(DEFAULT_STREAM_ID),
     type(GEN_TYPE::GEN_VOID)
{}
// Constructor
Gad::Gad(uint8_t stream_id, int8_t aiding_type) : 
     stream_id(stream_id),
     type(aiding_type)
{}

Gad::~Gad() = default;
Gad::Gad(const Gad& g) = default;
auto Gad::operator=(const Gad& g) -> Gad& = default;


auto Gad::operator=(const GEN_AIDING_DATA& g) -> Gad&
{
  this->SetDataType(g.type);
  this->SetStreamId(g.stream_id);
  this->val        = Gen3d(g.val);
  this->val_valid  = g.val_valid;
  this->time       = Gen3d(g.time);
  this->time_valid = g.time_valid;
  this->loc        = Gen3d(g.loc);
  this->loc_valid  = g.loc_valid;
  this->res1       = Gen3d(g.res1);
  this->res1_valid = g.res1_valid;
  this->res2       = Gen3d(g.res2);
  this->res2_valid = g.res2_valid;
  this->acq        = g.acq;
  this->acq_valid  = g.acq_valid;
  return *this;
}

auto Gad::getCStruct() -> GEN_AIDING_DATA
{
  GEN_AIDING_DATA g;
  g.type       = GetDataType();
  g.stream_id  = GetStreamId();
  g.val        = GEN_3D(this->val);
  g.val_valid  = this->val_valid;
  g.time       = GEN_3D(this->time);
  g.time_valid = this->time_valid;
  g.loc        = GEN_3D(this->loc);
  g.loc_valid  = this->loc_valid;
  g.res1       = GEN_3D(this->res1);
  g.res1_valid = this->res1_valid;
  g.res2       = GEN_3D(this->res2);
  g.res2_valid = this->res2_valid;
  g.acq        = this->acq;
  g.acq_valid  = this->acq_valid;

  return g;
}


// streamId
void Gad::SetStreamId(int id) { this->stream_id = id; }
auto  Gad::GetStreamId() const -> int { return this->stream_id; }
// type 
void Gad::SetDataType(int type){ this->type = type; } 
auto  Gad::GetDataType() const -> int{ return this->type; } 
// val
void Gad::SetValValid(bool flag)  {this->val_valid = flag;}
auto Gad::GetValValid() const -> bool {return this->val_valid;}

void Gad::SetDataMode(int mode){ this->val.SetMode(mode); }
void Gad::SetDataValType(int x_type) { this->val.SetValType(x_type); }
void Gad::SetDataVal(double x_0, double x_1,double x_2)
{
  this->SetValValid(true);
  this->val.SetVal(x_0,x_1,x_2);
}
auto Gad::GetDataVal() const -> std::vector<double>
{
  return this->val.GetVal();
}

void Gad::SetDataVarUpperDiag(double v_00, double v_11, double v_22, 
                              double v_01, double v_02, double v_12)
{
  this->val.SetVarUpperDiag(v_00,v_11,v_22,v_01,v_02,v_12);
}

void Gad::SetDataVarDiag(double v_00, double v_11,double v_22)
{
  this->val.SetVarDiag(v_00,v_11,v_22);
}

void Gad::SetDataVarSingle(double v_0)
{
  this->val.SetVarSingle(v_0);
}

auto Gad::GetDataVar() const -> std::vector<double>
{
  return this->val.GetVar();
}

// time
void Gad::SetTimeValid(bool flag)  {this->time_valid = flag;}
auto Gad::GetTimeValid() const -> bool {return this->time_valid;}
//
void Gad::SetTimeExternal(double week, double secs)
{
  this->SetTimeValid(true);
  this->time.SetMode(0);
  this->time.SetValType(TIME_SYS::TIME_EXT);
  this->time.SetVal(week,secs,0.0);
}
auto Gad::GetTimeExternalWeek() const -> double { return time.GetValX(); }
auto Gad::GetTimeExternalSecondsFromSunday() const -> double { return this->time.GetValY(); }
auto Gad::GetTimeExternal() const -> std::vector<double>
{
  return std::vector<double>{this->GetTimeExternalWeek(), this->GetTimeExternalSecondsFromSunday()};
}
// GPS
void Gad::SetTimeGps(double week, double seconds_from_sunday)
{
  this->SetTimeValid(true);
  this->time.SetMode(0);
  this->time.SetValType(TIME_SYS::TIME_GPS);
  this->time.SetVal(week,seconds_from_sunday, 0);
}
auto Gad::GetTimeGps() const -> std::vector<double>
{
  return std::vector<double>{this->GetTimeGpsWeek(), this->GetTimeGpsSecondsFromSunday()};
}
auto Gad::GetTimeGpsWeek() const -> double { return this->time.GetValX(); }
auto Gad::GetTimeGpsSecondsFromSunday() const -> double{ return this->time.GetValY(); }
// PPS
void Gad::SetTimePpsRelative(double ns)
{
  this->SetTimeValid(true);

  this->time.SetMode(0);
  this->time.SetValType(TIME_SYS::TIME_PPS_RELATIVE);
  this->time.SetVal(0.0, 0.0, ns);
}
auto Gad::GetTimePpsRelative() const -> double { return this->time.GetValY(); }
// Latency
void   Gad::SetTimeLatency(double ns)
{
  this->SetTimeValid(true);
  this->time.SetMode(0);
  this->time.SetValType(TIME_SYS::TIME_EST_LATENCY);
  this->time.SetVal(0.0, ns, 0.0);
}
auto Gad::GetTimeLatency() const -> double{ return this->time.GetValY(); }
// Void
void   Gad::SetTimeVoid()
{
  this->SetTimeValid(true);
  this->time.SetMode(0);
  this->time.SetValType(TIME_SYS::TIME_VOID);
}

// loc  
void Gad::SetLocValid(bool flag)  {this->loc_valid = flag;}
auto Gad::GetLocValid() const -> bool {return this->loc_valid;}

void Gad::SetLocMode(int mode) { this->loc.SetMode(mode); }
void Gad::SetLocValType(int x_type) { this->loc.SetValType(x_type);}
void Gad::SetLocVal(double x_0, double x_11,double x_22)
{
  this->SetLocValid(true);
  this->loc.SetVal(x_0,x_11,x_22);
}
auto Gad::GetLocVal() const -> std::vector<double>
{
  return this->loc.GetVal();
}
void Gad::SetLocVarUpperDiag(double v_00, double v_11, double v_22,
                             double v_01, double v_02, double v_12)
{
  this->loc.SetVarUpperDiag(v_00,v_11,v_22,v_01,v_02,v_12);
}
void Gad::SetLocVarDiag(double v_00, double v_11,double v_22)
{
  this->loc.SetVarDiag(v_00,v_11,v_22);
}
void Gad::SetLocVarSingle(double v_0)
{
  this->loc.SetVarSingle(v_0);
}
auto Gad::GetLocVar() const -> std::vector<double>
{
  return this->loc.GetVar();
}

void Gad::SetRes1Valid(bool flag)  {this->res1_valid = flag;}
auto Gad::GetRes1Valid() const -> bool {return this->res1_valid;}
void Gad::SetRes2Valid(bool flag)  {this->res2_valid = flag;}
auto Gad::GetRes2Valid() const -> bool {return this->res2_valid;}
void Gad::SetAcqValid(bool flag)  {this->acq_valid = flag;}
auto Gad::GetAcqValid() const -> bool {return this->acq_valid;}

void Gad::SetAcqTimestamp(uint32_t acq_time)
{
  this->acq = acq_time;
  this->acq_valid = 1;
}
auto Gad::GetAcqTimestamp() const -> uint32_t
{
  return this->acq;
}

//==============================================================================
// GadPosition

GadPosition::GadPosition(uint8_t stream_id) : Gad(stream_id, GEN_TYPE::GEN_POS){}

void GadPosition::SetPosGeodetic(double lat, double lon, double alt)
{
  this->SetDataMode(0);
  this->SetDataValType(POS_SYS_TYPE::POS_SYS_WGS84);
  this->SetDataVal(lat,lon,alt);
}

void GadPosition::SetPosLocal(double x, double y, double z)
{
  this->SetDataMode(0);
  this->SetDataValType(POS_SYS_TYPE::POS_SYS_LOCAL);
  this->SetDataVal(x,y,z);
}

auto GadPosition::GetPos() const -> std::vector<double>
{
  return this->GetDataVal();
}

void GadPosition::SetPosGeodeticVar(double v_n, double v_e, double v_d)
{
  this->SetDataVarDiag(v_n,v_e,v_d);
}

void GadPosition::SetPosGeodeticVarFull(
  double v_00, double v_11, double v_22, 
  double v_01, double v_02, double v_12
){
  this->SetDataVarUpperDiag(v_00,v_11,v_22,v_01,v_02,v_12);
}

void GadPosition::SetPosLocalVar(double v_x, double v_y, double v_z)
{
  this->SetDataVarDiag(v_x,v_y,v_z);
}

void GadPosition::SetPosLocalVarFull(
    double v_00, double v_11, double v_22, 
    double v_01, double v_02, double v_12
){
  this->SetDataVarUpperDiag(v_00,v_11,v_22,v_01,v_02,v_12);
}

auto GadPosition::GetPosVar() const -> std::vector<double>
{
  return this->GetDataVar();
}

void GadPosition::SetAidingLeverArmFixed(double x, double y, double z)
{
  this->SetLocMode(LOC_SYS::LOC_FIXED);
  this->SetLocVal(x,y,z);
}

auto GadPosition::GetAidingLeverArm() const -> std::vector<double>
{
  return this->GetLocVal();
}

void GadPosition::SetAidingLeverArmOptimising()
{
  this->SetLocMode(LOC_SYS::LOC_KF);
  this->SetLocVal(0.0,0.0,0.0);
}

void GadPosition::SetAidingLeverArmConfig()
{
  this->SetLocMode(LOC_SYS::LOC_CONFIG);
  this->SetLocVal(0.0,0.0,0.0);
}

void GadPosition::SetAidingLeverArmVar(double x, double y, double z)
{
  this->SetLocVarDiag(x,y,z);
}

auto GadPosition::GetAidingLeverArmVar() const -> std::vector<double>
{
  return this->GetLocVar();
}

//==============================================================================
// GadVelocity
GadVelocity::GadVelocity(uint8_t stream_id) : Gad(stream_id, GEN_TYPE::GEN_VEL){}

// val
void GadVelocity::SetVelNeu(double v_n, double v_e, double v_u)
{
  this->SetDataMode(0);
  this->SetDataValType(VEL_SYS_TYPE::VEL_SYS_NEU);
  this->SetDataVal(v_n,v_e,v_u);
}

void GadVelocity::SetVelOdom(double v_x, double v_y, double v_z)
{
  this->SetDataMode(0);
  this->SetDataValType(VEL_SYS_TYPE::VEL_SYS_ODO);
  this->SetDataVal(v_x,v_y,v_z);
}

void GadVelocity::SetVelLocal(double v_x, double v_y, double v_z)
{
  this->SetDataMode(0);
  this->SetDataValType(VEL_SYS_TYPE::VEL_SYS_LOCAL);
  this->SetDataVal(v_x,v_y,v_z);
}

auto GadVelocity::GetVel() const -> std::vector<double>
{
  return this->GetDataVal();
}

void GadVelocity::SetVelNeuVar(double v_n, double v_e, double v_u)
{
  this->SetDataVarDiag(v_n,v_e,v_u);
}

void GadVelocity::SetVelNeuVarFull(
  double v_nn, double v_ee, double v_uu, 
  double v_ne, double v_nu, double v_eu
){
  this->SetDataVarUpperDiag(v_nn,v_ee,v_uu,v_ne,v_nu,v_eu);
}

void GadVelocity::SetVelOdomVar(double v_x, double v_y, double v_z)
{
  this->SetDataVarDiag(v_x,v_y,v_z);
}

void GadVelocity::SetVelOdomVarFull(
  double v_xx, double v_yy, double v_zz, 
  double v_xy, double v_xz, double v_yz
){
  this->SetDataVarUpperDiag(v_xx,v_yy,v_zz,v_xy,v_xz,v_yz);
}

void GadVelocity::SetVelLocalVar(double v_x, double v_y, double v_z)
{
  this->SetDataVarDiag(v_x,v_y,v_z);
}

void GadVelocity::SetVelLocalVarFull(
  double v_xx, double v_yy, double v_zz, 
  double v_xy, double v_xz, double v_yz
){
  this->SetDataVarUpperDiag(v_xx,v_yy,v_zz,v_xy,v_xz,v_yz);
}

auto GadVelocity::GetVelVar() const -> std::vector<double> 
{
  return this->GetDataVar();
}

// loc 
void GadVelocity::SetAidingLeverArmFixed(double x, double y, double z)
{
  this->SetLocMode(LOC_SYS::LOC_FIXED);
  this->SetLocVal(x,y,z);
}

auto GadVelocity::GetAidingLeverArm() const -> std::vector<double> 
{
  return this->GetLocVal();
}

void GadVelocity::SetAidingLeverArmConfig()
{
  this->SetLocMode(LOC_SYS::LOC_CONFIG);
  this->SetLocVal(0.0,0.0,0.0);
}
void GadVelocity::SetAidingLeverArmOptimising()
{
  this->SetLocMode(LOC_SYS::LOC_KF);
  this->SetLocVal(0.0,0.0,0.0);
}
void GadVelocity::SetAidingLeverArmVar(double x, double y, double z)
{
  this->SetLocVarDiag(x,y,z);
}

auto GadVelocity::GetAidingLeverArmVar() const -> std::vector<double> 
{
  return this->GetLocVar();
}
//==============================================================================
// GadSpeed
GadSpeed::GadSpeed(uint8_t stream_id) : Gad(stream_id, GEN_TYPE::GEN_SPEED){}

// val
void GadSpeed::SetSpeedFw(double speed)
{
  this->SetDataMode(0);
  this->SetDataValType(SPEED_SYS_TYPE::SPEED_SYS_FW_VEL);
  this->SetDataVal(speed,0.0,0.0); /** @todo Implement with time interval */
}

auto GadSpeed::GetSpeedFw() const -> double
{
  return this->GetDataVal()[0];
}

void GadSpeed::SetSpeedFwVar(double v_s)
{
  this->SetDataVarSingle(v_s);
}

auto GadSpeed::GetSpeedFwVar() const -> double
{
  return this->GetDataVar()[0];
}

void GadSpeed::SetWheelspeedCount(double count, double period)
{
  this->SetDataMode(0);
  this->SetDataValType(SPEED_SYS_TYPE::SPEED_SYS_FW_VEL);
  this->SetDataVal(count,period,0.0); /** @todo Implement with time interval */
}

auto GadSpeed::GetWheelspeedCount() const -> std::vector<double>
{
  return std::vector<double>{this->GetDataVal()[0], this->GetDataVal()[1]};
}

void GadSpeed::SetWheelspeedVar(double v_c)
{
  this->SetDataVarSingle(v_c);
}

auto GadSpeed::GetWheelspeedVar() const -> double
{
    return this->GetDataVar()[0];
}

// loc 
void GadSpeed::SetAidingLeverArmFixed(double x, double y, double z)
{
  this->SetLocMode(LOC_SYS::LOC_FIXED);
  this->SetLocVal(x,y,z);
}

void GadSpeed::SetAidingLeverArmConfig()
{
  this->SetLocMode(LOC_SYS::LOC_CONFIG);
  this->SetLocVal(0.0,0.0,0.0);
}

void GadSpeed::SetAidingLeverArmOptimising()
{
  this->SetLocMode(LOC_SYS::LOC_KF);
  this->SetLocVal(0.0,0.0,0.0);
}

auto GadSpeed::GetAidingLeverArm() const -> std::vector<double>
{
  return this->GetLocVal();
}
void GadSpeed::SetAidingLeverArmVar(double x, double y, double z)
{
  this->SetLocVarDiag(x,y,z);
}

auto GadSpeed::GetAidingLeverArmVar() const -> std::vector<double>
{
  return this->GetLocVar();
}
//==============================================================================
// GadAttitude
GadAttitude::GadAttitude() : Gad(DEFAULT_STREAM_ID, GEN_TYPE::GEN_ATT){}

GadAttitude::GadAttitude(uint8_t stream_id) : Gad(stream_id, GEN_TYPE::GEN_ATT){}

// val
void GadAttitude::SetAtt(double heading, double pitch, double roll)
{
  this->SetDataMode(0);
  this->SetDataValType(ATT_SYS_TYPE::ATT_SYS_HPR);
  this->SetDataVal(heading,pitch,roll); 
}

auto GadAttitude::GetAtt() const -> std::vector<double>
{
  return this->GetDataVal();
}

void GadAttitude::SetAttVar(double v_h, double v_p, double v_r)
{
  this->SetDataVarDiag(v_h,v_p,v_r);
}

auto GadAttitude::GetAttVar() const -> std::vector<double>
{
  return this->GetDataVar();
}
// loc 
auto GadAttitude::GetAidingAlignment() const -> std::vector<double>
{
  return this->GetLocVal();
}

// void GadAttitude::SetAidingAlignmentFixed(double x, double y, double z)
// {
//   this->SetLocMode(LOC_SYS::LOC_FIXED);
//   this->SetLocVal(x,y,z);
// }

void GadAttitude::SetAidingAlignmentOptimising()
{
  this->SetLocMode(LOC_SYS::LOC_KF);
  this->SetLocVal(0.0,0.0,0.0);
}

void GadAttitude::SetAidingAlignmentVar(double x, double y, double z)
{
  this->SetDataVarDiag(x,y,z);
}

auto GadAttitude::GetAidingAlignmentVar() const -> std::vector<double>
{
  return this->GetLocVar();
}

} // namespace OxTS
