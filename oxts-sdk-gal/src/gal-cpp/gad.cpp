#include "oxts/gal-cpp/gad.h"



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

void GadPosition::SetAidingFixedLeverArm(double x, double y, double z)
{
  this->SetLocMode(LOC_SYS::LOC_FIXED);
  this->SetLocVal(x,y,z);
}

void GadPosition::SetAidingOptimisingLeverArm(double x, double y, double z)
{
  this->SetLocMode(LOC_SYS::LOC_KF);
  this->SetLocVal(x,y,z);

}

void GadPosition::SetAidingConfigLeverArm()
{
  this->SetLocMode(LOC_SYS::LOC_CONFIG);
}

void GadPosition::SetAidingLeverArmVar(double x, double y, double z)
{
  this->SetDataVarDiag(x,y,z);
}