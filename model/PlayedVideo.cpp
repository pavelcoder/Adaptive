/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PlayedVideo.cpp
 * Author: pavel
 * 
 * Created on 23 марта 2018 г., 15:24
 */

#include "PlayedVideo.h"

#include <algorithm>

string getFileString(string path){
    std::ifstream ifs(path);
    return string((std::istreambuf_iterator<char>(ifs)),
                  (std::istreambuf_iterator<char>()));
}

PlayedVideo::PlayedVideo() {
    netSpeedChanges = new vector<NetSpeedChange*>();
}

Json::Value root;
PlayedVideo* PlayedVideo::readFromFile(string filename) {
    printf("Rading %s\n", filename.c_str());
    PlayedVideo *playedVideo = new PlayedVideo();
    Json::Reader reader;
    
    string content = getFileString(filename);

    bool parsingSuccessful = reader.parse( content, root );
    if ( !parsingSuccessful )
    {
        std::cout << "Failed to parse network data\n" << reader.getFormattedErrorMessages();
        return 0;
    }

    for(int j = 0; j < root["net"].size(); j++) {
        const Json::Value item = root["net"][j];
        long millis = item["durationMillis"].asInt();
        long speed = item["speedKBps"].asInt() * 1024L;
        if( speed == 0 ) {
            speed = 1;
        }
        NetSpeedChange *change = new NetSpeedChange(millis, speed);
        playedVideo->netSpeedChanges->push_back(change);
    }
    
    long *qualities = new long[root["kylobyterates"].size()];
    for( int j = 0; j < root["kilobyterates"].size(); ++j ) {
        qualities[j] = root["kilobyterates"][j].asInt() * 1024;
    }
    sort(qualities, qualities + root["kilobyterates"].size() );

    playedVideo->video = new Video(root["chunkCount"].asInt(), (int)root["kilobyterates"].size(), qualities);
    return playedVideo;
}
