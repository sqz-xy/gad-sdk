#include "oxts/gal-cpp/gad.hpp"

//==============================================================================
// Gen3d

void Gen3d::SetMode(int mode)
{
  this->mode = mode;
}

void Gen3d::SetValType(int x_type)
{
  this->x_type = x_type;
}

void Gen3d::SetVal(double x0, double x1,double x2)
{
  this->x[0] = x0;
  this->x[1] = x1;
  this->x[2] = x2;
}

void Gen3d::SetVarUpperDiag(double v0, double v1, double v2, double v3, double v4, double v5)
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

// streamId
void Gad::SetStreamId(int id) { this->stream_id = id; }
int  Gad::GetStreamId() { return this->stream_id; }
// type 
void Gad::SetDataType(int type){ this->type; } 
int  Gad::GetDataType(){ return this->type; } 
// val
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

// GPS
void   SetGpsTime(double week, double secondsFromSunday)
{
  this->time->SetMode(0);
  this->time->SetValType(TIME_SYS::TIME_GPS);
  this->time->SetVal(week,secondsFromSunday, 0);
}
int    GetGpsWeek()
{

}
double GetGpsSecondsFromSunday()
{

}
// PPS
void   SetTimePpsRelative(double ns)
{
  this->time->SetMode(0);
  this->time->SetValType(TIME_SYS::TIME_PPS_RELATIVE);
  this->time->SetVal(0.0, 0.0, ns);
}
double GetTimePpsRelative()
{

}
// Latency
void   SetTimeLatency(double ns)
{
  this->time->SetMode(0);
  this->time->SetValType(TIME_SYS::TIME_EST_LATENCY);
  this->time->SetVal(0.0, ns, 0.0);

}
double GetTimeLatency()
{

}
// Void
void   SetTimeVoid()
{
  this->time->SetMode(0);
  this->time->SetValType(TIME_SYS::TIME_VOID);
}

// loc  
void Gad::SetLocMode(int mode) { this->loc->SetMode(mode); }
void Gad::SetLocValType(int x_type) { this->loc->SetValType(x_type);}
void Gad::SetLocVal(double x0, double x1,double x2)
{
  this->val->SetVal(x0,x1,x2);
}
void Gad::SetLocVarUpperDiag(double v0, double v1, double v2, double v3, double v4, double v5)
{
  this->val->SetVarUpperDiag(v0,v1,v2,v3,v4,v5);
}
void Gad::SetLocVarDiag(double v0, double v1,double v2)
{
  this->val->SetVarDiag(v0,v1,v2);

}
void Gad::SetLocVarSingle(double v0)
{
  this->val->SetVarSingle(v0);
}

//==============================================================================
// GadPosition

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

//==============================================================================
// GadSpeed


//==============================================================================
// GadAttitude