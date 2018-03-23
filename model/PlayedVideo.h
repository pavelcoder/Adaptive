/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PlayedVideo.h
 * Author: pavel
 *
 * Created on 23 марта 2018 г., 15:24
 */

#ifndef PLAYEDVIDEO_H
#define PLAYEDVIDEO_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "../net/NetSpeedChange.h"
#include "Video.h"
#include "../json/json.h"

using namespace std;

class PlayedVideo {
public:
    PlayedVideo();
    Video* video;
    vector<NetSpeedChange*>* netSpeedChanges;
    
    static PlayedVideo* readFromFile(string filename);
private:

};

#endif /* PLAYEDVIDEO_H */

