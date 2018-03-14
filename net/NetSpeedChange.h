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

class NetSpeedChange {
public:
    NetSpeedChange(long millisFromStart, long bitrate);
    long millisFromStart;
    long bitrate;
private:
   
};

#endif /* NETSPEEDCHANGE_H */

