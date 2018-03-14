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

Player::Player(NetworkDownloader *networkDownloader, Video *video) {
    this->networkDownloader = networkDownloader;
    this->video = video;
}

long Player::play() {
    return 0;
}

