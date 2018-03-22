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

#define MINIMUM_BUFFER_S 10
#define MINIMUM_BUFFER_PER_BITRATE_LEVEL_S 2

class AdaptiveTrackSelector: public BaseTrackSelector {
public:
    AdaptiveTrackSelector();
    virtual long getNextChunkBytesPerSecond(int chunkIndex, long playbackPositionMs, long bufferSizeMs);
private:    
    long getQualityFromBufferLevel(long bufferLevel);
};

#endif /* ADAPTIVETRACKSELECTOR_H */

