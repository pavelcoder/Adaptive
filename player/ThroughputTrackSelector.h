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

#define NETWORK_FRACTION 0.75f

#include "BaseTrackSelector.h"

class ThroughputTrackSelector : public BaseTrackSelector {
public:
    ThroughputTrackSelector();
    virtual long getNextChunkBytesPerSecond(int chunkIndex, long playbackPositionMs, long bufferSizeMs);
    
    virtual void onVideoStarted(Video* video);
    virtual void onStartBufferingChunk(Chunk* chunk);
    virtual void onFinishBufferingChunk(Chunk* chunk, long durationMillis, long bytesRead, bool isSuccess);
private:
    long totalBytes;
    long totalMillis;
    
    int getIdealQualityIndex();
};

#endif /* THROUGHPUTTRACKSELECTOR_H */

