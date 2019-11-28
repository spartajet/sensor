//
// Created by guoxi on 2019/11/1.
//

#ifndef SENSOR_SENSOR_H
#define SENSOR_SENSOR_H

#endif //SENSOR_SENSOR_H
#include "libserialport.h"


struct sensor_info{
    char *port_name;
    int baud_rate;
    enum sp_parity parity;
    int data_bits;
    int stop_bits;
};

enum acquire_mode{
    ALL,LATEST,LATEST_SOME
};
