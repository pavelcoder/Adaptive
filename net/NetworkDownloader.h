/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NetworkDownloader.h
 * Author: pavel
 *
 * Created on 14 марта 2018 г., 18:18
 */

#ifndef NETWORKDOWNLOADER_H
#define NETWORKDOWNLOADER_H

#include <vector>
#include "NetSpeedChange.h"

using namespace std;

class NetworkDownloader {
public:
    NetworkDownloader(vector<NetSpeedChange*>* changes);

    /*
     *  @return количество миллисекунд, потраченных на скачивание
     */
    long readChunk(long size);
    void sleep(long millis);
private:
    vector<NetSpeedChange*>* speedChanges;
    int currentNetSpeedIndex;
    long bytesReadInCurrentSegment;
    
    int getNextSegmentIndex() {
        return (currentNetSpeedIndex + 1) % speedChanges->size();
    }
};

#endif /* NETWORKDOWNLOADER_H */

