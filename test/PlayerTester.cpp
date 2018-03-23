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
    adaptationsCount = 0;
    chunkLoadFailure = 0;
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

void PlayerTester::onDownloadTrackChanged(long prevByterate, long newByterate) {
    if( prevByterate != NO_QUALITY ) {
        adaptationsCount++;
    }
}

void PlayerTester::onVideoStopped(Video* video, int chunksPlayed, bool isSuccess) {
    errorCount += isSuccess ? 0 : 1;
    float sumAdaptability = 0;
    for( int i = 0; i < segmentsAdaptability.size(); ++i ) {
        sumAdaptability += segmentsAdaptability[i];
    }
    VIDEO_STATS stats;
    if(isSuccess)
    {
        stats.adaptability = sumAdaptability / segmentsAdaptability.size();
    }
    else
    {
        stats.adaptability = 0;
    }
    stats.bufferizationEmptyBufferCount = bufferizationCount;
    stats.chunkLoadFailureCount = chunkLoadFailure;
    stats.adaptationFrequency = chunksPlayed == 0 ? 0 : adaptationsCount / (float)chunksPlayed;
    videoStats.push_back(stats);
}

void PlayerTester::onStartBufferingChunk(Chunk* chunk) {
    
}

void PlayerTester::onFinishBufferingChunk(Chunk* chunk, long durationMillis, long bytesRead, bool isSuccess) {
    chunkLoadFailure += isSuccess ? 0 : 1;
    long networkBytesPerSec = chunk->size * 1000 / durationMillis;
    long chunkBytesPerSec = chunk->size / ( video->chunkDurationMillis / 1000 );
    float chunkAdaptiveness = ((float)chunkBytesPerSec) / min( networkBytesPerSec, video->getMaxQualityBytesPerSecond() );
    if(isSuccess)
    {
        segmentsAdaptability.push_back( chunkAdaptiveness );
    }
    else
    {
        segmentsAdaptability.push_back( 0 );
    }
}

void PlayerTester::printResult() {
    double videoCount = videoStats.size();
    float sumAdaptability = 0;
    double bufferizations = 0;
    double sumAdaptationsFrequency = 0;
    int sumChunkLoadFailure = 0;
    for( int i = 0; i < videoStats.size(); ++i ) {
        sumAdaptability += videoStats[i].adaptability; 
        bufferizations += videoStats[i].bufferizationEmptyBufferCount;
        sumAdaptationsFrequency += videoStats[i].adaptationFrequency;
        sumChunkLoadFailure += videoStats[i].chunkLoadFailureCount;
    }
    printf("Played %d video.\n"
            "Adaptiveness = %.3g\n"
            "Adaptation frequency = %.3g\n"
            "Bufferization per video = %.3g\n"
            "Video error because cant download chunk = %.2f %%\n"
            "Chunk load error per video = %.3g\n", 
            (int)videoCount,
            sumAdaptability / (videoCount - errorCount),
            (double)sumAdaptationsFrequency / videoCount,
            (double)bufferizations / videoCount,
            (double)errorCount * 100 / videoCount, 
            (double)sumChunkLoadFailure / videoCount);
}
