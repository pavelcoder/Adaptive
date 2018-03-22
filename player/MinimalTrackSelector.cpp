/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MinimalTrackSelector.cpp
 * Author: pavel
 * 
 * Created on 22 марта 2018 г., 15:30
 */

#include "MinimalTrackSelector.h"

MinimalTrackSelector::MinimalTrackSelector() {
}


long MinimalTrackSelector::getNextChunkBytesPerSecond(int chunkIndex, long playbackPositionMs, long bufferSizeMs) {
    return video->getQualityAt(0);
}