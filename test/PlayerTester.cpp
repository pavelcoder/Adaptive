/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PlayerTester.cpp
 * Author: pavel
 * 
 * Created on 14 марта 2018 г., 20:45
 */

#include "PlayerTester.h"
#include <algorithm>
#include <stdio.h>

PlayerTester::PlayerTester() {
    errorCount = 0;
}

void PlayerTester::onVideoStarted(Video* video) {
    this->video = video;
    bufferizationCount = 0;
    segmentsAdaptability.clear();
}

void PlayerTester::onBufferizationStart(int reason) {
    if( reason == BUFFERING_REASON_BUFFER_EMPTY ) {
        bufferizationCount++;
    }
}

void PlayerTester::onBufferizationStop(int reason, long durationMs) {
}

void PlayerTester::onChunkLoadError(Chunk chunk) {
}

void PlayerTester::onVideoStopped(Video* video, bool isSuccess) {
    errorCount += isSuccess ? 0 : 1;
    float sumAdaptability = 0;
    for( int i = 0; i < segmentsAdaptability.size(); ++i ) {
        sumAdaptability += segmentsAdaptability[i];
    }
    VIDEO_STATS stats;
    stats.adaptability = sumAdaptability / segmentsAdaptability.size();
    stats.bufferizationEmptyBufferCount = bufferizationCount;
    videoStats.push_back(stats);
}

void PlayerTester::onStartBufferingChunk(Chunk* chunk) {
    
}

void PlayerTester::onFinishBufferingChunk(Chunk* chunk, long durationMillis, long bytesRead, bool isSuccess) {
    long networkBytesPerSec = chunk->size * 1000 / durationMillis;
    long chunkBytesPerSec = chunk->size / ( video->chunkDurationMillis / 1000 );
    float chunkAdaptiveness = ((float)chunkBytesPerSec) / min( networkBytesPerSec, video->getMaxQualityBytesPerSecond() );
    segmentsAdaptability.push_back( chunkAdaptiveness );
}

void PlayerTester::printResult() {
    float sumAdaptability = 0;
    int bufferizations = 0;
    for( int i = 0; i < videoStats.size(); ++i ) {
        sumAdaptability += videoStats[i].adaptability;
        bufferizations += videoStats[i].bufferizationEmptyBufferCount;
    }
    printf("===========\r\nPlayed %d video.\r\nAdaptiveness = %.3g\r\nBufferization per video = %.3g\r\nVideo error because cant download chunk = %.2g%%", 
            (int)videoStats.size(),
            sumAdaptability / videoStats.size(),
            (double)bufferizations / videoStats.size(),
            (double)errorCount * 100 / videoStats.size());
}