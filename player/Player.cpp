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

Player::Player(NetworkDownloader *networkDownloader, Video *video) {
    this->networkDownloader = networkDownloader;
    this->video = video;
    trackSelector = new AdaptiveTrackSelector(video);
}

Player::~Player() {
    delete trackSelector;
}

long Player::play() {
    microsGoneFromVideoStart = 0;
    playbackPositionMicros = 0;
    bufferizedMicros = 0;
    lastVideoAtomStartedAtMicros = 0;
    
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

