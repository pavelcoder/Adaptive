/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AdaptiveTrackSelector.cpp
 * Author: pavel
 * 
 * Created on 14 марта 2018 г., 20:31
 */

#include "AdaptiveTrackSelector.h"

AdaptiveTrackSelector::AdaptiveTrackSelector() {}

long AdaptiveTrackSelector::getNextChunkBytesPerSecond(int chunkIndex, long playbackPositionMs, long bufferSizeMs) {
    return video->getQualityAt(video->getQualityCount() - 1);
}

void AdaptiveTrackSelector::onVideoStarted(Video* video) {
    this->video = video;
}

void AdaptiveTrackSelector::onBufferizationStart(int reason) {
}

void AdaptiveTrackSelector::onBufferizationStop(int reason, long durationMs) {
}

void AdaptiveTrackSelector::onChunkLoadError(Chunk chunk) {
}

void AdaptiveTrackSelector::onVideoStopped(Video* video, bool isSuccess) {
}


void AdaptiveTrackSelector::onStartBufferingChunk(Chunk* chunk) {
    
}

void AdaptiveTrackSelector::onFinishBufferingChunk(Chunk* chunk, long durationMillis, long bytesRead, bool isSuccess) {
    
}