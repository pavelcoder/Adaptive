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

class AdaptiveTrackSelector: public PlayerListener {
public:
    AdaptiveTrackSelector(Video *video);
    long getNextChunkBitrate(int chunkIndex, long playbackPositionMs, long bufferSizeMs);
    
    void onVideoStarted();
    void onBufferizationStart();
    void onBufferizationStop(long durationMs);
    void onChunkLoadError(Chunk chunk);
    void onVideoStopped();

private:
    Video* video;
};

#endif /* ADAPTIVETRACKSELECTOR_H */

