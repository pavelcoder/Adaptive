/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PlayerTester.h
 * Author: pavel
 *
 * Created on 14 марта 2018 г., 20:45
 */

#ifndef PLAYERTESTER_H
#define PLAYERTESTER_H

#include "../player/PlayerListener.h"
#include <vector>

using namespace std;

struct VIDEO_STATS {
    int bufferizationEmptyBufferCount;
    float agressiveness;
};

class PlayerTester : public PlayerListener {
public:
    PlayerTester();
    
    virtual void onVideoStarted(Video* video);
    virtual void onBufferizationStart(int reason);
    virtual void onBufferizationStop(int reason, long durationMs);
    virtual void onChunkLoadError(Chunk chunk);
    virtual void onVideoStopped(Video* video);
    
    virtual void onStartBufferingChunk(Chunk* chunk);
    virtual void onFinishBufferingChunk(Chunk* chunk, long durationMillis, bool isSuccess);
private:
    vector<VIDEO_STATS> videoStats;
    VIDEO_STATS* currentVideoStat;
    
};

#endif /* PLAYERTESTER_H */

