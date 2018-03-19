/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NetSpeedChange.h
 * Author: pavel
 *
 * Created on 14 марта 2018 г., 20:24
 */

#ifndef NETSPEEDCHANGE_H
#define NETSPEEDCHANGE_H

#include <stdio.h>

class NetSpeedChange {
public:
    NetSpeedChange(long durationMillis, long speedBytesPerSecond);
    long speedBytesPerSecond;
    long durationMillis;
    
    long getTotalBytes() {
        long res = speedBytesPerSecond * durationMillis / 1000;
        return res;
    }
private:
   
};

#endif /* NETSPEEDCHANGE_H */

