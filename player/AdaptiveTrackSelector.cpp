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

AdaptiveTrackSelector::AdaptiveTrackSelector(Video *video) {
    this->video = video;
}

long AdaptiveTrackSelector::getNextChunkBitrate(int chunkIndex, long playbackPositionMs, long bufferSizeMs) {
    return video->getQualityAt(video->getQualityCount() - 1);
}

void AdaptiveTrackSelector::onVideoStarted() {
}

void AdaptiveTrackSelector::onBufferizationStart() {
}

void AdaptiveTrackSelector::onBufferizationStop(long durationMs) {
}

void AdaptiveTrackSelector::onChunkLoadError(Chunk chunk) {
}

void AdaptiveTrackSelector::onVideoStopped() {
}
