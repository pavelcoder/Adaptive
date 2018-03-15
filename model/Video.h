/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Video.h
 * Author: pavel
 *
 * Created on 14 марта 2018 г., 20:19
 */

#ifndef VIDEO_H
#define VIDEO_H

class Video {
public:
    Video(int chunkCount, int qualityCount, long qualitiesBitrate[]);
    
    int getQualityCount();
    long getQualityAt(int index);
    int getChunkCount();
    long chunkDurationMillis;
private:
    int chunkCount;
    int qualityCount;
    long* qualitiesBitrate;
};

#endif /* VIDEO_H */

