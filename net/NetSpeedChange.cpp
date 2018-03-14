/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NetSpeedChange.cpp
 * Author: pavel
 * 
 * Created on 14 марта 2018 г., 20:24
 */

#include "NetSpeedChange.h"

NetSpeedChange::NetSpeedChange(long millisFromStart, long bitrate) {
    this->millisFromStart = millisFromStart;
    this->bitrate = bitrate;
}

