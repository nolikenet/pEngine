//
//  LTimer.cpp
//  pEngine
//
//  Created by Arthur on 12.11.17.
//  Copyright © 2017 plaiko. All rights reserved.
//

#include "../Inc/LTimer.hpp"

LTimer::LTimer() {
    
    mStartTicks = 0;
    mPausedTicks = 0;
    mPaused = false;
    mStarted = false;
}

void LTimer::start() {
    mStarted = true;
    mPaused = false;
    //Get the current clock time
    mStartTicks = SDL_GetTicks();
    mPausedTicks = 0;
}

void LTimer::stop() {
    mStarted = false;
    mPaused = false;
    mStartTicks = 0;
    mPausedTicks = 0;
}

void LTimer::pause() { //If the timer is running and isn't already paused
    if( mStarted && !mPaused ) {
        //Pause the timer mPaused = true;
        //Calculate the paused ticks
        mPausedTicks = SDL_GetTicks() - mStartTicks; mStartTicks = 0;
    }
}

void LTimer::unpause() { //If the timer is running and paused
    if( mStarted && mPaused ) {
        //Unpause the timer
        mPaused = false;
        //Reset the starting ticks
        mStartTicks = SDL_GetTicks() - mPausedTicks;
        //Reset the paused ticks
        mPausedTicks = 0;
    }
}

Uint32 LTimer::getTicks() {
    //The actual timer time
    Uint32 time = 0;
    //If the timer is running
    if( mStarted ) {
        //If the timer is paused
        if( mPaused ) {
            //Return the number of ticks when the timer was paused
            time = mPausedTicks;
        }
        else {
            //Return the current time minus the start time
            time = SDL_GetTicks() - mStartTicks;
        }
    }
    return time;
}

bool LTimer::isStarted() {
    //Timer is running and paused or unpaused
    return mStarted;
}
bool LTimer::isPaused() { //Timer is running and paused
    return mPaused && mStarted;
}
