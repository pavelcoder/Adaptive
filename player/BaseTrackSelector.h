/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BaseTrackSelector.h
 * Author: pavel
 *
 * Created on 22 марта 2018 г., 14:42
 */

#ifndef BASETRACKSELECTOR_H
#define BASETRACKSELECTOR_H

#include "PlayerListener.h"

class BaseTrackSelector : public PlayerListener {
public:
    BaseTrackSelector();
    virtual long getNextChunkBytesPerSecond(int chunkIndex, long playbackPositionMs, long bufferAheadSizeMs) = 0;
    
    virtual void onVideoStarted(Video* video);
    virtual void onVideoStopped(Video* video, int chunksPlayed, bool isSuccess);
        
    virtual void onBufferizationStart(int reason);
    virtual void onBufferizationStop(int reason, long durationMs);
    virtual void onChunkLoadError(Chunk chunk);
    virtual void onDownloadTrackChanged(long prevByterate, long newByterate);
    
    virtual void onStartBufferingChunk(Chunk* chunk);
    virtual void onFinishBufferingChunk(Chunk* chunk, long durationMillis, long bytesRead, bool isSuccess);
protected:
    Video* video;
};

#endif /* BASETRACKSELECTOR_H */

