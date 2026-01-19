#ifndef __AHRS_H
#define __AHRS_H
#include "Fusion.h"
#include "imu_data.h"

extern FusionAhrs ahrs;

void navi_calculate( void );

#endif
