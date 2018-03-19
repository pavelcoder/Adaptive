/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PlayerListener.h
 * Author: pavel
 *
 * Created on 19 марта 2018 г., 11:32
 */

#ifndef PLAYERLISTENER_H
#define PLAYERLISTENER_H

#include "../model/Chunk.h"

class PlayerListener {
    public: 
        PlayerListener();
        virtual void onVideoStarted() = 0;
        virtual void onBufferizationStart() = 0;
        virtual void onBufferizationStop(long durationMs) = 0;
        virtual void onChunkLoadError(Chunk chunk) = 0;
        virtual void onVideoStopped() = 0;
};

#endif /* PLAYERLISTENER_H */

