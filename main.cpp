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
    NetSpeedChange netSpeedChange( 60 * 60 * 1000, 100 * 1000); 
    NetSpeedChange netChanges[] = {netSpeedChange};
    NetworkDownloader networkDownloader(1, netChanges);
    long qualities[] = {100 * 1000, 150 * 1000, 120 * 1000};
    Video video(30, 3, qualities);
    AdaptiveTrackSelector trackSelector;
    PlayerTester tester;
    Player player(&networkDownloader, &video, &trackSelector);
    player.addListener(&tester);
    long duration = player.play();
    player.removeListener(&tester);
    tester.printResult();
    fflush(stdout);
    return 0;
}

