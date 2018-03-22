/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ThroughputTrackSelector.h
 * Author: pavel
 *
 * Created on 22 марта 2018 г., 14:53
 */

#ifndef THROUGHPUTTRACKSELECTOR_H
#define THROUGHPUTTRACKSELECTOR_H

#include "BaseTrackSelector.h"

class ThroughputTrackSelector : public BaseTrackSelector {
public:
    ThroughputTrackSelector();
    virtual long getNextChunkBytesPerSecond(int chunkIndex, long playbackPositionMs, long bufferSizeMs);
    
    virtual void onBufferizationStart(int reason);
    virtual void onBufferizationStop(int reason, long durationMs);
    virtual void onChunkLoadError(Chunk chunk);
    
    virtual void onStartBufferingChunk(Chunk* chunk);
    virtual void onFinishBufferingChunk(Chunk* chunk, long durationMillis, long bytesRead, bool isSuccess);
private:

};

#endif /* THROUGHPUTTRACKSELECTOR_H */

