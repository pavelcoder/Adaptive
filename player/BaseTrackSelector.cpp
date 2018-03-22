/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BaseTrackSelector.cpp
 * Author: pavel
 * 
 * Created on 22 марта 2018 г., 14:42
 */

#include "BaseTrackSelector.h"

BaseTrackSelector::BaseTrackSelector() {
   
}

void BaseTrackSelector::onVideoStarted(Video* video) {
    this->video = video;
}


void BaseTrackSelector::onVideoStopped(Video* video, bool isSuccess) {
}