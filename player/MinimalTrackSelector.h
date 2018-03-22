/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MinimalTrackSelector.h
 * Author: pavel
 *
 * Created on 22 марта 2018 г., 15:30
 */

#ifndef MINIMALTRACKSELECTOR_H
#define MINIMALTRACKSELECTOR_H

#include "BaseTrackSelector.h"

class MinimalTrackSelector : public BaseTrackSelector {
public:
    MinimalTrackSelector();
    virtual long getNextChunkBytesPerSecond(int chunkIndex, long playbackPositionMs, long bufferSizeMs);

private:

};

#endif /* MINIMALTRACKSELECTOR_H */

