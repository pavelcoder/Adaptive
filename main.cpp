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
#include <stdio.h>
#include "net/NetworkDownloader.h"
#include "player/Player.h"
#include "test/PlayerTester.h"
#include "net/NetSpeedChange.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    NetSpeedChange netSpeedChange( 10 * 1000, 200000); 
    NetSpeedChange netChanges[] = {netSpeedChange};
    NetworkDownloader networkDownloader(1, netChanges);
    long qualities[] = {700000, 1200000, 2500000};
    Video video(30, 3, qualities);
    AdaptiveTrackSelector trackSelector;
    Player player(&networkDownloader, &video, &trackSelector);
    long duration = player.play();
    printf("Played durung %ld sec\r\n", duration / 1000000);
    fflush(stdout);
    return 0;
}

