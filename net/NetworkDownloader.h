/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NetworkDownloader.h
 * Author: pavel
 *
 * Created on 14 марта 2018 г., 18:18
 */

#ifndef NETWORKDOWNLOADER_H
#define NETWORKDOWNLOADER_H

#include "NetSpeedChange.h"


class NetworkDownloader {
public:
    NetworkDownloader(int speedChangeCount, NetSpeedChange speedChanges[]);

    /*
     *  @return количество миллисекунд, потраченных на скачивание
     */
    long readChunk(long size);
    void sleep(long millis);
private:
    NetSpeedChange* speedChanges;
    long millisGone;
    int currentNetSpeedIndex;
    int speedChangeCount;
    long bytesReadInCurrentSegment;
};

#endif /* NETWORKDOWNLOADER_H */

