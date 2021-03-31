#include "oxts/gal-cpp/gad.hpp"

using namespace OxTS;
//==============================================================================
// Gen3d

Gen3d::Gen3d(const GEN_3D& g)
{
  mode = g.mode;
  x_type = g.x_type;
  x[0] = g.x[0];
  x[1] = g.x[1];
  x[2] = g.x[2];
  v_type = g.v_type;
  v[0] = g.v[0];
  v[1] = g.v[1];
  v[2] = g.v[2];
  v[3] = g.v[3];
  v[4] = g.v[4];
  v[5] = g.v[5];
}


void   Gen3d::SetMode(int mode){ this->mode = mode; }
void   Gen3d::SetValType(int x_type){ this->x_type = x_type; }
void   Gen3d::SetValX(double x){this->x[0] = x;}
double Gen3d::GetValX(){return this->x[0];}
void   Gen3d::SetValY(double y){this->x[1] = y;}
double Gen3d::GetValY(){return this->x[1];}
void   Gen3d::SetValZ(double z){this->x[2] = z;}
double Gen3d::GetValZ(){return this->x[2];}

void   Gen3d::SetVal(double x, double y,double z)
{
  SetValX(x);
  SetValY(y);
  SetValZ(z);
}
void   Gen3d::SetVarUpperDiag(double v0, double v1, double v2, double v3, double v4, double v5)
{
  this->v_type = GEN_VAR_TYPE::GEN_VAR_HMAT;
  this->v[0] = v0;
  this->v[1] = v1;
  this->v[2] = v2;
  this->v[3] = v3;
  this->v[4] = v4;
  this->v[5] = v5;
}

void Gen3d::SetVarDiag(double v0, double v1,double v2)
{
  this->v_type = GEN_VAR_TYPE::GEN_VAR_DIAG;
  this->v[0] = v0;
  this->v[1] = v1;
  this->v[2] = v2;
}

void Gen3d::SetVarSingle(double v0)
{
  this->v_type = GEN_VAR_TYPE::GEN_VAR_SINGLE;
  this->v[0] = v0;
}

//==============================================================================
// Gad superclass

// Default Constructor
Gad::Gad()
{
  this->SetStreamId(128);
  this->SetDataType(GEN_TYPE::GEN_VOID);
  this->SetValInvalid();
  this->SetTimeInvalid();
  this->SetLocInvalid();
  this->SetRes1Invalid();
  this->SetRes2Invalid();
}
// Constructor
Gad::Gad(uint8_t stream_id, int8_t aiding_type)
{
  this->SetStreamId(stream_id);
  this->SetDataType(aiding_type);
  this->SetValInvalid();
  this->SetTimeInvalid();
  this->SetLocInvalid();
  this->SetRes1Invalid();
  this->SetRes2Invalid();
  this->SetAcqInvalid();
  this->SetAcqTimestamp(0.0);
}

Gad::~Gad(){}

Gad::Gad(const Gad& g)
{
  this->SetDataType(g.type);
  this->SetStreamId(g.stream_id);
  this->val        = g.val;
  this->val_valid  = g.val_valid;
  this->time       = g.time;
  this->time_valid = g.time_valid;
  this->loc        = g.loc;
  this->loc_valid  = g.loc_valid;
  this->res1       = g.res1;
  this->res1_valid = g.res1_valid;
  this->res2       = g.res2;
  this->res2_valid = g.res2_valid;
  this->acq        = g.acq;
  this->acq_valid  = g.acq_valid;
}

Gad& Gad::operator=(const GEN_AIDING_DATA& g)
{
  this->SetDataType(g.type);
  this->SetStreamId(g.stream_id);
  this->val        = g.val;
  this->val_valid  = g.val_valid;
  this->time       = g.time;
  this->time_valid = g.time_valid;
  this->loc        = g.loc;
  this->loc_valid  = g.loc_valid;
  this->res1       = g.res1;
  this->res1_valid = g.res1_valid;
  this->res2       = g.res2;
  this->res2_valid = g.res2_valid;
  this->acq        = g.acq;
  this->acq_valid  = g.acq_valid;
  return *this;
}

GEN_AIDING_DATA Gad::getCStruct()
{
  GEN_AIDING_DATA g;
  g.type       = GetDataType();
  g.stream_id  = GetStreamId();
  g.val      = *(this->val);
  g.val_valid  = this->val_valid;
  g.time     = *(this->time);
  g.time_valid = this->time_valid;
  g.loc      = *(this->loc);
  g.loc_valid  = this->loc_valid;
  g.res1     = *(this->res1);
  g.res1_valid = this->res1_valid;
  g.res2     = *(this->res2);
  g.res2_valid = this->res2_valid;
  g.acq        = this->acq;
  g.acq_valid  = this->acq_valid;

  return g;
}


// streamId
void Gad::SetStreamId(int id) { this->stream_id = id; }
int  Gad::GetStreamId() { return this->stream_id; }
// type 
void Gad::SetDataType(int type){ this->type = type; } 
int  Gad::GetDataType(){ return this->type; } 
// val
void Gad::SetValInvalid(){this->val_valid = 0;}
void Gad::SetValValid(){this->val_valid = 1;}

void Gad::SetDataMode(int mode){ this->val.SetMode(mode); }
void Gad::SetDataValType(int x_type) { this->val.SetValType(x_type); }
void Gad::SetDataVal(double x0, double x1,double x2)
{
  this->SetValValid();
  this->val.SetVal(x0,x1,x2);
}

void Gad::SetDataVarUpperDiag(double v0, double v1, double v2, double v3, double v4, double v5)
{
  this->val.SetVarUpperDiag(v0,v1,v2,v3,v4,v5);
}

void Gad::SetDataVarDiag(double v0, double v1,double v2)
{
  this->val.SetVarDiag(v0,v1,v2);
}

void Gad::SetDataVarSingle(double v0)
{
  this->val.SetVarSingle(v0);
}

// time
void Gad::SetTimeInvalid(){this->time_valid = 0;}
void Gad::SetTimeValid()  {this->time_valid = 1;}

// GPS
void   Gad::SetGpsTime(double week, double seconds_from_sunday)
{
  this->SetTimeValid();
  this->time.SetMode(0);
  this->time.SetValType(TIME_SYS::TIME_GPS);
  this->time.SetVal(week,seconds_from_sunday, 0);
}
double Gad::GetGpsWeek(){ return this->time.GetValX(); }
double Gad::GetGpsSecondsFromSunday(){ return this->time.GetValY(); }
// PPS
void   Gad::SetTimePpsRelative(double ns)
{
  this->SetTimeValid();

  this->time.SetMode(0);
  this->time.SetValType(TIME_SYS::TIME_PPS_RELATIVE);
  this->time.SetVal(0.0, 0.0, ns);
}
double Gad::GetTimePpsRelative(){ return this->time.GetValY(); }
// Latency
void   Gad::SetTimeLatency(double ns)
{
  this->SetTimeValid();
  this->time.SetMode(0);
  this->time.SetValType(TIME_SYS::TIME_EST_LATENCY);
  this->time.SetVal(0.0, ns, 0.0);
}
double Gad::GetTimeLatency(){ return this->time.GetValY(); }
// Void
void   Gad::SetTimeVoid()
{
  this->SetTimeValid();
  this->time.SetMode(0);
  this->time.SetValType(TIME_SYS::TIME_VOID);
}

// loc  
void Gad::SetLocInvalid(){this->loc_valid = 0;}
void Gad::SetLocValid(){this->loc_valid = 1;}

void Gad::SetLocMode(int mode) { this->loc.SetMode(mode); }
void Gad::SetLocValType(int x_type) { this->loc.SetValType(x_type);}
void Gad::SetLocVal(double x0, double x1,double x2)
{
  this->SetLocValid();
  this->loc.SetVal(x0,x1,x2);
}
void Gad::SetLocVarUpperDiag(double v0, double v1, double v2, double v3, double v4, double v5)
{
  this->loc.SetVarUpperDiag(v0,v1,v2,v3,v4,v5);
}
void Gad::SetLocVarDiag(double v0, double v1,double v2)
{
  this->loc.SetVarDiag(v0,v1,v2);
}
void Gad::SetLocVarSingle(double v0)
{
  this->loc.SetVarSingle(v0);
}

void Gad::SetRes1Invalid(){ this->res1_valid = 0; }
void Gad::SetRes1Valid()  { this->res1_valid = 1; }
void Gad::SetRes2Invalid(){ this->res2_valid = 0; }
void Gad::SetRes2Valid()  { this->res2_valid = 1; }
void Gad::SetAcqInvalid() { this->acq_valid = 0;  }
void Gad::SetAcqValid()   { this->acq_valid = 1;  }

void Gad::SetAcqTimestamp(uint32_t acq_time)
{
  this->acq = acq_time;
  this->acq_valid = 1;

}
uint32_t  Gad::GetAcqTimestamp()
{
  return this->acq;
}

//==============================================================================
// GadPosition

GadPosition::GadPosition(uint8_t stream_id) : Gad(stream_id, GEN_TYPE::GEN_POS){}

void GadPosition::SetWgs84Pos(double lat, double lon, double alt)
{
  this->SetDataMode(0);
  this->SetDataValType(POS_SYS_TYPE::POS_SYS_WGS84);
  this->SetDataVal(lat,lon,alt);
}

void GadPosition::SetLocalPos(double x, double y, double z)
{
  this->SetDataMode(0);
  this->SetDataValType(POS_SYS_TYPE::POS_SYS_LOCAL);
  this->SetDataVal(x,y,z);
}

void GadPosition::SetPosVar(double var_x, double var_y, double var_z)
{
  this->SetDataVarDiag(var_x,var_y,var_z);
}

void GadPosition::SetAidingLeverArmFixed(double x, double y, double z)
{
  this->SetLocMode(LOC_SYS::LOC_FIXED);
  this->SetLocVal(x,y,z);
}

void GadPosition::SetAidingLeverArmOptimising()
{
  this->SetLocMode(LOC_SYS::LOC_KF);
  this->SetLocVal(0.0,0.0,0.0);
}

void GadPosition::SetAidingLeverArmConfig()
{
  this->SetLocMode(LOC_SYS::LOC_CONFIG);
}

void GadPosition::SetAidingLeverArmVar(double x, double y, double z)
{
  this->SetDataVarDiag(x,y,z);
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

void GadVelocity::SetVelNeuVar(double v_n, double v_e, double v_u)
{
  this->SetDataVarDiag(v_n,v_e,v_u);
}

void GadVelocity::SetVelOdomVar(double v_x, double v_y, double v_z)
{
  this->SetDataVarDiag(v_x,v_y,v_z);
}

void GadVelocity::SetVelLocalVar(double v_x, double v_y, double v_z)
{
  this->SetDataVarDiag(v_x,v_y,v_z);
}

// loc 
void GadVelocity::SetAidingLeverArmFixed(double x, double y, double z)
{
  this->SetLocMode(LOC_SYS::LOC_FIXED);
  this->SetLocVal(x,y,z);
}
void GadVelocity::SetAidingLeverArmOptimising()
{
  this->SetLocMode(LOC_SYS::LOC_KF);
  this->SetLocVal(0.0,0.0,0.0);
}
void GadVelocity::SetAidingLeverArmVar(double x, double y, double z)
{
  this->SetDataVarDiag(x,y,z);
}
//==============================================================================
// GadSpeed
GadSpeed::GadSpeed(uint8_t stream_id) : Gad(stream_id, GEN_TYPE::GEN_SPEED){}

// val
void GadSpeed::SetSpeedFw(double s_f)
{
  this->SetDataMode(0);
  this->SetDataValType(SPEED_SYS_TYPE::SPEED_SYS_FW_VEL);
  this->SetDataVal(s_f,0.0,0.0); /** @todo Implement with time interval */
}
void GadSpeed::SetSpeedFwVar(double v_s)
{
  this->SetDataVarSingle(v_s);
}
void GadSpeed::SetWheelspeedCount(double count, double period)
{
  this->SetDataMode(0);
  this->SetDataValType(SPEED_SYS_TYPE::SPEED_SYS_FW_VEL);
  this->SetDataVal(count,period,0.0); /** @todo Implement with time interval */
}
void GadSpeed::SetWheelspeedVar(double v_c)
{
  this->SetDataVarSingle(v_c);
}

// loc 
void GadSpeed::SetAidingLeverArmFixed(double x, double y, double z)
{
  this->SetLocMode(LOC_SYS::LOC_FIXED);
  this->SetLocVal(x,y,z);
}
void GadSpeed::SetAidingLeverArmOptimising()
{
  this->SetLocMode(LOC_SYS::LOC_KF);
  this->SetLocVal(0.0,0.0,0.0);
}
void GadSpeed::SetAidingLeverArmVar(double x, double y, double z)
{
  this->SetDataVarDiag(x,y,z);
}
//==============================================================================
// GadAttitude
GadAttitude::GadAttitude(uint8_t stream_id) : Gad(stream_id, GEN_TYPE::GEN_ATT){}

// val
void GadAttitude::SetAtt(double heading, double pitch, double roll)
{
  this->SetDataMode(0);
  this->SetDataValType(ATT_SYS_TYPE::ATT_SYS_HPR);
  this->SetDataVal(heading,pitch,roll); 
}
void GadAttitude::SetAttVar(double v_h, double v_p, double v_r)
{
  this->SetDataVarDiag(v_h,v_p,v_r);
}

// loc 
void GadAttitude::SetAidingAlignmentFixed(double x, double y, double z)
{
  this->SetLocMode(LOC_SYS::LOC_FIXED);
  this->SetLocVal(x,y,z);
}
void GadAttitude::SetAidingAlignmentOptimising()
{
  this->SetLocMode(LOC_SYS::LOC_KF);
  this->SetLocVal(0.0,0.0,0.0);
}
void GadAttitude::SetAidingAlignmentVar(double x, double y, double z)
{
  this->SetDataVarDiag(x,y,z);
}

