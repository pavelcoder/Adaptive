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

ThroughputTrackSelector::ThroughputTrackSelector() {
}

long ThroughputTrackSelector::getNextChunkBytesPerSecond(int chunkIndex, long playbackPositionMs, long bufferSizeMs) {
    return video->getQualityAt(0);
}

void ThroughputTrackSelector::onBufferizationStart(int reason) {
}

void ThroughputTrackSelector::onBufferizationStop(int reason, long durationMs) {
}

void ThroughputTrackSelector::onChunkLoadError(Chunk chunk) {
}

void ThroughputTrackSelector::onStartBufferingChunk(Chunk* chunk) {
    
}

void ThroughputTrackSelector::onFinishBufferingChunk(Chunk* chunk, long durationMillis, long bytesRead, bool isSuccess) {
    
}