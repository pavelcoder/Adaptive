/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Player.h
 * Author: pavel
 *
 * Created on 14 марта 2018 г., 20:28
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "AdaptiveTrackSelector.h"
#include "PlayerListener.h"
#include "../net/NetworkDownloader.h"
#include <stdio.h>
//#include <vector>

using namespace std;

#define DOWNLOAD_BUFFER_SIZE (10 * 1024)
#define VIDEO_FOR_PLAY_ATOM_MILLIS 1000
#define MIN_BUFFER_FOR_PLAY_MILLIS 4000

#define BUFFERING_REASON_NONE -1
#define BUFFERING_REASON_STARTING 0
#define BUFFERING_REASON_SEEK 1
#define BUFFERING_REASON_QUALITY_CHANGE 2
#define BUFFERING_REASON_BUFFER_EMPTY 3

class Player {
public:
    Player(NetworkDownloader* networkDownloader, Video* video);
    ~Player();
    /* return total play millis
     */
    long play();
private:
    NetworkDownloader* networkDownloader;
    Video* video;
    AdaptiveTrackSelector* trackSelector;
    
    long bufferizedMicros;
    long microsGoneFromVideoStart;
    long playbackPositionMicros;
    long lastVideoAtomStartedAtMicros;
    
    bool isBuffering;
    int bufferingReason;
    
    //vector<PlayerListener> listeners;
    
    void playVideoIfTimeCome();
    void setBufferingState(bool isBuffering, int reason) {
        if( isBuffering == this->isBuffering ) return;
        this->isBuffering = isBuffering;
        bufferingReason = reason;
        printf("New state: %s, position = %ld sec, buffered until %ld sec, millis gone =  %ld\r\n", 
                isBuffering ? "BUFFERING" : "PLAYING", 
                playbackPositionMicros / 1000000, 
                bufferizedMicros / 1000000,
                microsGoneFromVideoStart / 1000);
    }
};

#endif /* PLAYER_H */

