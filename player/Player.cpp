/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Player.cpp
 * Author: pavel
 * 
 * Created on 14 марта 2018 г., 20:28
 */

#include "Player.h"
#include <stdio.h>
#include <ctime>
#include "PlayerListener.h"

Player::Player(NetworkDownloader *networkDownloader, Video *video, AdaptiveTrackSelector* selector) {
    this->networkDownloader = networkDownloader;
    this->video = video;
    trackSelector = new AdaptiveTrackSelector();
    listeners.push_back(trackSelector);
}

Player::~Player() {
    delete trackSelector;
}

void Player::addListener(PlayerListener* listener) {
    listeners.push_back(trackSelector);
}

void Player::removeListener(PlayerListener* listener) {
    for(int i = 0; i < listeners.size(); ++i) {
        if( listeners[i] == listener ) {
            listeners.erase(listeners.begin() + i);
            return;
        }
    }
}

long Player::play() {
    microsGoneFromVideoStart = 0;
    playbackPositionMicros = 0;
    bufferizedMicros = 0;
    lastVideoAtomStartedAtMicros = 0;
    
    for(int i = 0; i < listeners.size(); ++i) {
        listeners[i]->onVideoStarted(video);
    }
    setBufferingState(true, BUFFERING_REASON_STARTING);
    for( int i = 0; i < video->getChunkCount(); i++ ) {
        printf("Downloading chunk : %d, bufferizedMillisFromStart = %ld\r\n", i, bufferizedMicros / 1000000);
        long chunkBitrate = trackSelector->getNextChunkBitrate(i, playbackPositionMicros / 1000, (bufferizedMicros - playbackPositionMicros) / 1000);
        long chunkTotalBytes = chunkBitrate / 8 * video->chunkDurationMillis / 1000;
        long chunkBytesAlreadyRead = 0;
        while(true) {
            playVideoIfTimeCome();
            
            long bytesInChunkLeft = chunkTotalBytes - chunkBytesAlreadyRead;
            long bytesToReadNow = DOWNLOAD_BUFFER_SIZE;
            bool chunkFinished;
            if( bytesToReadNow > bytesInChunkLeft ) {
                bytesToReadNow = bytesInChunkLeft;
                chunkFinished = true;
            } else {
                chunkFinished = false;
            }
            
            chunkBytesAlreadyRead += bytesToReadNow;
            microsGoneFromVideoStart += networkDownloader->readChunk(bytesToReadNow);
            long videoMicrosWasRead = bytesToReadNow * 8 * 1000 * 1000 / chunkBitrate;
            bufferizedMicros += videoMicrosWasRead;
           
            if(chunkFinished) {
                break;
            }
        }
    }
    for(int i = 0; i < listeners.size(); ++i) {
        listeners[i]->onVideoStopped(video);
    }
    return microsGoneFromVideoStart;
}

void Player::playVideoIfTimeCome() {
    bool needToPlay = lastVideoAtomStartedAtMicros + VIDEO_FOR_PLAY_ATOM_MILLIS * 1000 < microsGoneFromVideoStart;
    if( ! needToPlay ) return;
    bool canPlay;
    if( isBuffering ) {
        canPlay = playbackPositionMicros + MIN_BUFFER_FOR_PLAY_MILLIS * 1000 < bufferizedMicros;
    } else {
        canPlay = playbackPositionMicros + VIDEO_FOR_PLAY_ATOM_MILLIS * 1000 < bufferizedMicros ;
    }
         
    if( canPlay ) {
        setBufferingState(false, BUFFERING_REASON_NONE);
        printf("Played 1 second from position %ld sec\r\n", playbackPositionMicros / 1000000);
        lastVideoAtomStartedAtMicros = microsGoneFromVideoStart;
        playbackPositionMicros += VIDEO_FOR_PLAY_ATOM_MILLIS * 1000;
    } else {
        setBufferingState(true, BUFFERING_REASON_BUFFER_EMPTY);
    }
}

void Player::setBufferingState(bool isBuffering, int reason) {
    if( isBuffering == this->isBuffering ) return;
    this->isBuffering = isBuffering;
    bufferingReason = reason;
    for(int i = 0; i < listeners.size(); ++i) {
        if( isBuffering ) {
            listeners[i]->onBufferizationStart(reason);
            bufferizationStartTs = std::time(0);
        } else {
            listeners[i]->onBufferizationStop(reason, std::time(0) - bufferizationStartTs);
        }
    }
    printf("New state: %s, position = %ld sec, buffered until %ld sec, millis gone =  %ld\r\n", 
            isBuffering ? "BUFFERING" : "PLAYING", 
            playbackPositionMicros / 1000000, 
            bufferizedMicros / 1000000,
            microsGoneFromVideoStart / 1000);
}