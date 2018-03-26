/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 * 
 */

/* 
 * File:   main.cpp
 * Author: pavel
 *
 * Created on 14 марта 2018 г., 18:06
 */

#include <cstdlib>
#include <glob.h>
#include <vector>
#include "player/Player.h"
#include "net/NetworkDownloader.h"
#include "net/NetSpeedChange.h"
#include "test/PlayerTester.h"
#include "player/ThroughputTrackSelector.h"
#include "player/AdaptiveTrackSelector.h"
#include "player/MinimalTrackSelector.h"
#include "model/PlayedVideo.h"

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

vector<PlayedVideo*>* getAllVideos(string path) {
    vector<PlayedVideo*>* all = new vector<PlayedVideo*>();
    vector<string> videoFiles = globVector(path);
    for(int i = 0; i < videoFiles.size(); i++) {
        all->push_back(PlayedVideo::readFromFile(videoFiles[i]));
    }
    return all;
}

void testTrackSelector(vector<PlayedVideo*>* videos, BaseTrackSelector* trackSelector) {
    PlayerTester tester;
    
    for( int i = 0; i < videos->size(); i++ ) {
        PlayedVideo* playedVideo = videos->at(i);
        NetworkDownloader networkDownloader(playedVideo->netSpeedChanges);

        Player player(&networkDownloader, playedVideo->video, trackSelector);
        player.addListener(&tester);
        player.play();
        player.removeListener(&tester);
    }
    
    tester.printResult();
}

int main(int argc, char** argv) {
    vector<PlayedVideo*>* videos = getAllVideos("test-data/*");
    
    printf(" === MinimalTrackSelector ===\n");
    MinimalTrackSelector minimalTrackSelector;
    testTrackSelector(videos, &minimalTrackSelector);
    
    printf(" === ThroughputTrackSelector ===\n");
    ThroughputTrackSelector throughputTrackSelector;
    testTrackSelector(videos, &throughputTrackSelector);
    
    printf("=== AdaptiveTrackSelector ===\n");
    AdaptiveTrackSelector adaptiveTrackSelector;
    testTrackSelector(videos, &adaptiveTrackSelector);
    
    fflush(stdout);
    return 0;
}

