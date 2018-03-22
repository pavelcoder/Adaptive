/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AdaptiveTrackSelector.h
 * Author: pavel
 *
 * Created on 14 марта 2018 г., 20:31
 */

#ifndef ADAPTIVETRACKSELECTOR_H
#define ADAPTIVETRACKSELECTOR_H

#include "PlayerListener.h"
#include "../model/Video.h"
#include "BaseTrackSelector.h"

class AdaptiveTrackSelector: public BaseTrackSelector {
public:
    AdaptiveTrackSelector();
    virtual long getNextChunkBytesPerSecond(int chunkIndex, long playbackPositionMs, long bufferSizeMs);
    
    virtual void onBufferizationStart(int reason);
    virtual void onBufferizationStop(int reason, long durationMs);
    virtual void onChunkLoadError(Chunk chunk);
    
    virtual void onStartBufferingChunk(Chunk* chunk);
    virtual void onFinishBufferingChunk(Chunk* chunk, long durationMillis, long bytesRead, bool isSuccess);
};

#endif /* ADAPTIVETRACKSELECTOR_H */

