/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: pavel
 *
 * Created on 14 марта 2018 г., 18:06
 */

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <glob.h>
#include <vector>
#include "json/json.h"
#include "player/Player.h"
#include "net/NetworkDownloader.h"
#include "net/NetSpeedChange.h"
#include "test/PlayerTester.h"
#include "player/ThroughputTrackSelector.h"
#include "player/AdaptiveTrackSelector.h"
#include "player/MinimalTrackSelector.h"

using namespace std;

vector<string> globVector(const string& pattern){
    glob_t glob_result;
    glob(pattern.c_str(),GLOB_TILDE,NULL,&glob_result);
    vector<string> files;
    for(unsigned int i=0;i<glob_result.gl_pathc;++i){
        files.push_back(string(glob_result.gl_pathv[i]));
    }
    globfree(&glob_result);
    return files;
}

string getFileString(string path){
    std::ifstream ifs(path);
    return string((std::istreambuf_iterator<char>(ifs)),
                  (std::istreambuf_iterator<char>()));
}

/**
 * need to free memory
 * @return 
 */
vector<vector<NetSpeedChange*>*>* readAllSpeedChanges(string path) {
    vector<string> netFiles = globVector(path);
    vector<vector<NetSpeedChange*>*>* all= new vector<vector<NetSpeedChange*>*>();
    for(int i = 0; i < netFiles.size(); i++) {
        Json::Reader reader;
        Json::Value root;
        string content = getFileString(netFiles[i]);
        
        bool parsingSuccessful = reader.parse( content, root );
        if ( !parsingSuccessful )
        {
            std::cout << "Failed to parse network data\n" << reader.getFormattedErrorMessages();
            continue;
        }
        
        vector<NetSpeedChange*>* netChanges = new vector<NetSpeedChange*>();
        for(int j = 0; j < root.size(); j++) {
            const Json::Value item = root[j];
            long millis = item["duration"].asInt() * 1000L;
            long speed = item["speedKBps"].asInt() * 1024L;
            NetSpeedChange *change = new NetSpeedChange(millis, speed);
            netChanges->push_back(change);
        }
        all->push_back(netChanges);
        
    }
    return all;
}

/**
 * need to free memory: qualities
 * @return 
 */
vector<Video*>* getAllVideos(string path) {
    vector<Video*>* all = new vector<Video*>();
    vector<string> videoFiles = globVector(path);
    for(int i = 0; i < videoFiles.size(); i++) {
        Json::Reader reader;
        Json::Value root;
        string content = getFileString(videoFiles[i]);
        
        bool parsingSuccessful = reader.parse( content, root );
        if ( !parsingSuccessful )
        {
            std::cout << "Failed to parse video \n" << reader.getFormattedErrorMessages();
            continue;
        }
        
        long *qualities = new long[root["kylobyterates"].size()];
        for( int j = 0; j < root["kylobyterates"].size(); ++j ) {
            qualities[j] = root["kylobyterates"][j].asInt() * 1024;
        }
        Video* video = new Video(root["chunkCount"].asInt(), (int)root["kylobyterates"].size(), qualities);
        all->push_back(video);
    }
    return all;
}

void testTrackSelector(vector<vector<NetSpeedChange*>*>* netFiles, vector<Video*>* videos, BaseTrackSelector* trackSelector) {
    PlayerTester tester;
    
    for( int i = 0; i < netFiles->size(); i++ ) {
        for( int j = 0; j < videos->size(); j++ ) {
            vector<NetSpeedChange*>* changes = netFiles->at(i);
            NetworkDownloader networkDownloader(changes);
            Video* video = videos->at(j);
            
            Player player(&networkDownloader, video, trackSelector);
            player.addListener(&tester);
            player.play();
            player.removeListener(&tester);
        }
    }
    
    tester.printResult();
}

int main(int argc, char** argv) {
    vector<vector<NetSpeedChange*>*>* netFiles = readAllSpeedChanges("res/net/*");
    vector<Video*>* videos = getAllVideos("res/video/*");
    
    printf(" === MinimalTrackSelector ===\n");
    MinimalTrackSelector minimalTrackSelector;
    testTrackSelector(netFiles, videos, &minimalTrackSelector);
    
    printf(" === ThroughputTrackSelector ===\n");
    ThroughputTrackSelector throughputTrackSelector;
    testTrackSelector(netFiles, videos, &throughputTrackSelector);
    
    printf("=== AdaptiveTrackSelector ===\n");
    AdaptiveTrackSelector adaptiveTrackSelector;
    testTrackSelector(netFiles, videos, &adaptiveTrackSelector);
    
    fflush(stdout);
    return 0;
}

