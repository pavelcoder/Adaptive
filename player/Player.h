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

class Player {
public:
    Player(NetworkDownloader* networkDownloader, Video* video);
    /* return total play millis
     */
    long play();
private:
    NetworkDownloader* networkDownloader;
    Video* video;
    AdaptiveTrackSelector* trackSelector;
};

#endif /* PLAYER_H */

