/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ThroughputTrackSelector.cpp
 * Author: pavel
 * 
 * Created on 22 марта 2018 г., 14:53
 */

#include "ThroughputTrackSelector.h"
#include <stdio.h>

ThroughputTrackSelector::ThroughputTrackSelector() {
    totalBytes = 0;
    totalMillis = 0;
}

long ThroughputTrackSelector::getNextChunkBytesPerSecond(int chunkIndex, long playbackPositionMs, long bufferSizeMs) {
    int KBPerSecond = totalBytes * 1000 / (totalMillis + 1) / 1024 * NETWORK_FRACTION;
    long quality = video->getQualityAt(getIdealQualityIndex());
    //printf("Chunk %d, speed = %d KBps, selected %d KBps, position = %d sec, buffered %d sec\n", chunkIndex, KBPerSecond, quality / 1024, (int)playbackPositionMs / 1000, (int)bufferSizeMs / 1000);
    return quality;
}

void ThroughputTrackSelector::onStartBufferingChunk(Chunk* chunk) {
    
}

void ThroughputTrackSelector::onFinishBufferingChunk(Chunk* chunk, long durationMillis, long bytesRead, bool isSuccess) {
    totalBytes += bytesRead;
    totalMillis += durationMillis;
}

void ThroughputTrackSelector::onVideoStarted(Video* video) {
    BaseTrackSelector::onVideoStarted(video);
    totalBytes = 0;
    totalMillis = 0;
}

int ThroughputTrackSelector::getIdealQualityIndex() {
    if( totalMillis == 0 ) return 0;
    long bytesPerSecond = totalBytes * 1000 / totalMillis * NETWORK_FRACTION;
    int lastIndex = 0;
    for( int i = 0; i < video->getQualityCount(); i++ ) {
        if( video->getQualityAt(i) < bytesPerSecond ) {
            lastIndex = i;
        } else {
            return lastIndex;
        }
    } 
    return lastIndex;
}