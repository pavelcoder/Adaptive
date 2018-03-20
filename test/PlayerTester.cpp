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

PlayerTester::PlayerTester() {
}

void PlayerTester::onVideoStarted(Video* video) {
    currentVideoStat = new VIDEO_STATS();
    currentVideoStat->agressiveness = 0;
    currentVideoStat->bufferizationEmptyBufferCount = 0;
}

void PlayerTester::onBufferizationStart(int reason) {
    currentVideoStat->bufferizationEmptyBufferCount++;
}

void PlayerTester::onBufferizationStop(int reason, long durationMs) {
}

void PlayerTester::onChunkLoadError(Chunk chunk) {
}

void PlayerTester::onVideoStopped(Video* video) {
    videoStats.push_back(*currentVideoStat);
    delete currentVideoStat;
}

void PlayerTester::onStartBufferingChunk(Chunk* chunk) {
    
}

void PlayerTester::onFinishBufferingChunk(Chunk* chunk, long durationMillis, bool isSuccess) {
    
}
