/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Video.cpp
 * Author: pavel
 * 
 * Created on 14 марта 2018 г., 20:19
 */

#include "Video.h"

Video::Video(int chunkCount, int qualityCount, long qualitiesBitrate[]) {
    this->chunkCount = chunkCount;
    this->qualityCount = qualityCount;
    this->qualitiesBitrate = qualitiesBitrate;
    chunkDurationMillis = 8 * 1000;
}

int Video::getQualityCount() {
    return qualityCount;
}

long Video::getQualityAt(int index) {
    return this->qualitiesBitrate[index];
}

int Video::getChunkCount() {
    return chunkCount;
}