/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NetworkDownloader.cpp
 * Author: pavel
 * 
 * Created on 14 марта 2018 г., 18:18
 */

#include "NetworkDownloader.h"

NetworkDownloader::NetworkDownloader(int speedChangeCount, NetSpeedChange speedChanges[]) {
    this->speedChanges = speedChanges;
    millisGone = 0;
    bytesReadInCurrentSegment = 0;
    currentNetSpeedIndex = 0;
    this->speedChangeCount = 0;
}

long NetworkDownloader::readChunk(long size) {
    if( currentNetSpeedIndex < speedChangeCount - 1 ) {
        NetSpeedChange nextSpeedChange = this->speedChanges[currentNetSpeedIndex + 1];
        //int totalBytesLeft
    }
    
    return 100;
}

void NetworkDownloader::sleep(long millis) {
    
}
