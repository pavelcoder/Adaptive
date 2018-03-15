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

NetworkDownloader::NetworkDownloader(int speedChangeCount, NetSpeedChange speedChanges[]) {
    this->speedChanges = speedChanges;
    bytesReadInCurrentSegment = 0;
    currentNetSpeedIndex = 0;
    this->speedChangeCount = speedChangeCount;
}

//return microseconds
long NetworkDownloader::readChunk(long size) {
    if( size == 0 ) return 0;
    NetSpeedChange currentSpeedChange = speedChanges[currentNetSpeedIndex];
    long segmentSizeBytes = currentSpeedChange.getTotalBytes();
    long bytesLeft = segmentSizeBytes - bytesReadInCurrentSegment;
    long bytesToReadFromCurrentSegment = size;
    long bytesLeftAfterSegment = 0;
    if( size > bytesLeft ) {
        bytesToReadFromCurrentSegment = bytesLeft;
        bytesLeftAfterSegment = size - bytesLeft;
    }
     
    long currentSegmentDurationMicros = bytesToReadFromCurrentSegment * 1000 * 1000 / currentSpeedChange.speedBytesPerSecond;
    bytesReadInCurrentSegment += bytesToReadFromCurrentSegment;
    
    if( bytesLeftAfterSegment > 0 ) {
        currentNetSpeedIndex = getNextChunkIndex();
        bytesReadInCurrentSegment = 0;
        return currentSegmentDurationMicros + readChunk(bytesLeftAfterSegment);
    } else {
        return currentSegmentDurationMicros;
    }
}

void NetworkDownloader::sleep(long millis) {
    
}
