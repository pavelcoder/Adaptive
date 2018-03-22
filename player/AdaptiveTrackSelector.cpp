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
 * 
 * http://reference.dashif.org/dash.js/v2.6.7/samples/dash-if-reference-player/index.html
 * https://dash.akamaized.net/dash264/TestCasesHD/MultiPeriod_OnDemand/ThreePeriods/ThreePeriod_OnDemand2.mpd
 * 
 */

#include "AdaptiveTrackSelector.h"
#include <math.h>
#include <algorithm>

using namespace std;

AdaptiveTrackSelector::AdaptiveTrackSelector() {}

long AdaptiveTrackSelector::getNextChunkBytesPerSecond(int chunkIndex, long playbackPositionMs, long bufferSizeMs) {
    long bufferLeftSec = ( bufferSizeMs - playbackPositionMs ) / 1000;
    return getQualityFromBufferLevel(bufferLeftSec);
}

long AdaptiveTrackSelector::getQualityFromBufferLevel(long bufferLeftSec) {
    if( video->getQualityCount() == 1 ) {
        return video->getQualityAt(0);
    }
    double utilities[video->getQualityCount()];
    double minUtility = log( video->getQualityAt(0) );
    double maxUtility = 0;
    for (int i = 0; i < video->getQualityCount(); ++i) {
        utilities[i] = log( video->getQualityAt(i) ) - minUtility + 1;
        if( utilities[i] > maxUtility ) {
            maxUtility = utilities[i];
        }
    }
    double bufferTime = max(12, MINIMUM_BUFFER_S + MINIMUM_BUFFER_PER_BITRATE_LEVEL_S * video->getQualityCount());
    
    double gp = ( maxUtility - 1 ) / ( bufferTime / MINIMUM_BUFFER_S - 1 );
    double vp = MINIMUM_BUFFER_S / gp;
    int chunksLeft = bufferLeftSec;// * 1000 / video->chunkDurationMillis;
    
    long qualityIndex = -1;
    double score = 0;
    
    for (int i = 0; i < video->getQualityCount(); ++i) {
        double s = (vp * (utilities[i] + gp) - chunksLeft) / video->getQualityAt(i);
        if(qualityIndex == -1 || s >= score) {
            score = s;
            qualityIndex = i;
        }
    }
    return video->getQualityAt(qualityIndex);
}