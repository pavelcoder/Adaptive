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
#include <stdio.h>

NetworkDownloader::NetworkDownloader(vector<NetSpeedChange*>* changes) {
    this->speedChanges = changes;
    currentNetSpeedIndex = 0;
    bytesReadInCurrentSegment = 0;
}

//return microseconds
long NetworkDownloader::readChunk(long size) {
    if( size == 0 ) return 0;
    NetSpeedChange *currentSpeedChange = this->speedChanges->at(currentNetSpeedIndex);
    long segmentSizeBytes = currentSpeedChange->getTotalBytes();
    long bytesLeft = segmentSizeBytes - bytesReadInCurrentSegment;
    long bytesToReadFromCurrentSegment = size;
    long bytesLeftAfterSegment = 0;
    if( size > bytesLeft ) {
        bytesToReadFromCurrentSegment = bytesLeft;
        bytesLeftAfterSegment = size - bytesLeft;
    }
     
    long currentSegmentDurationMicros = bytesToReadFromCurrentSegment * 1000 * 1000 / currentSpeedChange->speedBytesPerSecond;
    bytesReadInCurrentSegment += bytesToReadFromCurrentSegment;
    
    if( bytesLeftAfterSegment > 0 ) {
        currentNetSpeedIndex = getNextSegmentIndex();
        bytesReadInCurrentSegment = 0;
        return currentSegmentDurationMicros + readChunk(bytesLeftAfterSegment);
    } else {
        return currentSegmentDurationMicros;
    }
}

void NetworkDownloader::sleep(long millis) {
    
}
