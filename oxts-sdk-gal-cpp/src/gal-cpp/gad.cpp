#include "oxts/gal-cpp/gad.hpp"

//==============================================================================
// Gen3d


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
  SetStreamId(128);
  SetDataType(GEN_TYPE::GEN_VOID);
  val  = new Gen3d();
  time = new Gen3d();
  loc  = new Gen3d();
  res1 = new Gen3d();
  res2 = new Gen3d();
  // SetAcqTimestamp(0.0);
}
// Constructor
Gad::Gad(uint8_t stream_id, int8_t aiding_type)
{
  SetStreamId(stream_id);
  SetDataType(aiding_type);
  val  = new Gen3d();
  time = new Gen3d();
  loc  = new Gen3d();
  res1 = new Gen3d();
  res2 = new Gen3d();
  // SetAcqTimestamp(0.0);
}

Gad::~Gad()
{
  delete(val);
  delete(time);
  delete(loc);
  delete(res2);
  delete(res1);
}

Gad::Gad(const Gad& g)
{
  this->val  = new Gen3d();
  this->time = new Gen3d();
  this->loc  = new Gen3d();
  this->res1 = new Gen3d();
  this->res2 = new Gen3d();

  this->SetDataType(g.type);
  this->SetStreamId(g.stream_id);
  *this->val       = *g.val;
  this->val_valid  = g.val_valid;
  *this->time      = *g.time;
  this->time_valid = g.time_valid;
  *this->loc       = *g.loc;
  this->loc_valid  = g.loc_valid;
  *this->res1      = *g.res1;
  this->res1_valid = g.res1_valid;
  *this->res2      = *g.res2;
  this->res2_valid = g.res2_valid;
  this->acq        = g.acq;
  this->acq_valid  = g.acq_valid;
}

// streamId
void Gad::SetStreamId(int id) { this->stream_id = id; }
int  Gad::GetStreamId() { return this->stream_id; }
// type 
void Gad::SetDataType(int type){ this->type; } 
int  Gad::GetDataType(){ return this->type; } 
// val
void Gad::SetValValid(GenFlag validity){this->val_valid = validity;}

void Gad::SetDataMode(int mode){ this->val->SetMode(mode); }
void Gad::SetDataValType(int x_type) { this->val->SetValType(x_type); }
void Gad::SetDataVal(double x0, double x1,double x2)
{
  this->val->SetVal(x0,x1,x2);
}

void Gad::SetDataVarUpperDiag(double v0, double v1, double v2, double v3, double v4, double v5)
{
  this->val->SetVarUpperDiag(v0,v1,v2,v3,v4,v5);
}

void Gad::SetDataVarDiag(double v0, double v1,double v2)
{
  this->val->SetVarDiag(v0,v1,v2);
}

void Gad::SetDataVarSingle(double v0)
{
  this->val->SetVarSingle(v0);
}

// time
void Gad::SetTimeValid(GenFlag validity){this->time_valid = validity;}

// GPS
void   Gad::SetGpsTime(double week, double secondsFromSunday)
{
  this->time->SetMode(0);
  this->time->SetValType(TIME_SYS::TIME_GPS);
  this->time->SetVal(week,secondsFromSunday, 0);
}
double Gad::GetGpsWeek(){ return this->time->GetValX(); }
double Gad::GetGpsSecondsFromSunday(){ return this->time->GetValY(); }
// PPS
void   Gad::SetTimePpsRelative(double ns)
{
  this->time->SetMode(0);
  this->time->SetValType(TIME_SYS::TIME_PPS_RELATIVE);
  this->time->SetVal(0.0, 0.0, ns);
}
double Gad::GetTimePpsRelative(){ return this->time->GetValY(); }
// Latency
void   Gad::SetTimeLatency(double ns)
{
  this->time->SetMode(0);
  this->time->SetValType(TIME_SYS::TIME_EST_LATENCY);
  this->time->SetVal(0.0, ns, 0.0);
}
double Gad::GetTimeLatency(){ return this->time->GetValY(); }
// Void
void   Gad::SetTimeVoid()
{
  this->time->SetMode(0);
  this->time->SetValType(TIME_SYS::TIME_VOID);
}

// loc  
void Gad::SetLocValid(GenFlag validity){this->loc_valid = validity;}

void Gad::SetLocMode(int mode) { this->loc->SetMode(mode); }
void Gad::SetLocValType(int x_type) { this->loc->SetValType(x_type);}
void Gad::SetLocVal(double x0, double x1,double x2)
{
  this->loc->SetVal(x0,x1,x2);
}
void Gad::SetLocVarUpperDiag(double v0, double v1, double v2, double v3, double v4, double v5)
{
  this->loc->SetVarUpperDiag(v0,v1,v2,v3,v4,v5);
}
void Gad::SetLocVarDiag(double v0, double v1,double v2)
{
  this->loc->SetVarDiag(v0,v1,v2);
}
void Gad::SetLocVarSingle(double v0)
{
  this->loc->SetVarSingle(v0);
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

void GadPosition::SetWgs84PosVar(double varLat, double varLon, double varAlt)
{
  this->SetDataVarDiag(varLat,varLon,varAlt);
}

void GadPosition::SetAidingLeverArmFixed(double x, double y, double z)
{
  this->SetLocMode(LOC_SYS::LOC_FIXED);
  this->SetLocVal(x,y,z);
}

void GadPosition::SetAidingLeverArmOptimising(double x, double y, double z)
{
  this->SetLocMode(LOC_SYS::LOC_KF);
  this->SetLocVal(x,y,z);
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
void GadVelocity::SetVelNeu(double vN, double vE, double vU)
{
  this->SetDataMode(0);
  this->SetDataValType(VEL_SYS_TYPE::VEL_SYS_NEU);
  this->SetDataVal(vN,vE,vU);
}

void GadVelocity::SetVelNeuVar(double varN, double varE, double varU)
{
  this->SetDataVarDiag(varN,varE,varU);
}

// loc 
void GadVelocity::SetAidingLeverArmFixed(double x, double y, double z)
{
  this->SetLocMode(LOC_SYS::LOC_FIXED);
  this->SetLocVal(x,y,z);
}
void GadVelocity::SetAidingLeverArmOptimising(double x, double y, double z)
{
  this->SetLocMode(LOC_SYS::LOC_KF);
  this->SetLocVal(x,y,z);
}
void GadVelocity::SetAidingLeverArmVar(double x, double y, double z)
{
  this->SetDataVarDiag(x,y,z);
}
//==============================================================================
// GadSpeed
GadSpeed::GadSpeed(uint8_t stream_id) : Gad(stream_id, GEN_TYPE::GEN_SPEED){}

// val
void GadSpeed::SetSpeedFw(double sF)
{
  this->SetDataMode(0);
  this->SetDataValType(SPEED_SYS_TYPE::SPEED_SYS_FW_VEL);
  this->SetDataVal(sF,0.0,0.0); /** @todo Implement with time interval */
}
void GadSpeed::SetSpeedFwVar(double varS)
{
  this->SetDataVarSingle(varS);
}
void GadSpeed::SetWheelspeedCount(double count, double period)
{
  this->SetDataMode(0);
  this->SetDataValType(SPEED_SYS_TYPE::SPEED_SYS_FW_VEL);
  this->SetDataVal(count,period,0.0); /** @todo Implement with time interval */
}
void GadSpeed::SetWheelspeedVar(double varC)
{
  this->SetDataVarSingle(varC);
}

// loc 
void GadSpeed::SetAidingLeverArmFixed(double x, double y, double z)
{
  this->SetLocMode(LOC_SYS::LOC_FIXED);
  this->SetLocVal(x,y,z);
}
void GadSpeed::SetAidingLeverArmOptimising(double x, double y, double z)
{
  this->SetLocMode(LOC_SYS::LOC_KF);
  this->SetLocVal(x,y,z);
}
void GadSpeed::SetAidingLeverArmVar(double x, double y, double z)
{
  this->SetDataVarDiag(x,y,z);
}
//==============================================================================
// GadAttitude