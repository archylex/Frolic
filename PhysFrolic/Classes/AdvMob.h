#ifndef ADVMOB_H
#define ADVMOB_H

#include "cocos2d.h"

using namespace cocos2d;

class AdvMob {
    public:
        static void showInterstitial();
        static void showVideo();
        static bool getIsFinalVideo();
        static void resetIsFinalVideo();

};

#endif // ADVMOB_H
