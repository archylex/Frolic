#include "AdvMob.h"

#define CLASS_NAME "com/nazoroot/jni/AdMob"

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

void AdvMob::showInterstitial() {
    JniMethodInfo method;
    JniHelper::getStaticMethodInfo(method, CLASS_NAME, "showInterstitial", "()V");
    method.env->CallStaticVoidMethod(method.classID, method.methodID);
    method.env->DeleteLocalRef(method.classID);
}

void AdvMob::showVideo() {
    JniMethodInfo method;
    JniHelper::getStaticMethodInfo(method, CLASS_NAME, "showRewardedVideo", "()V");
    method.env->CallStaticVoidMethod(method.classID, method.methodID);
    method.env->DeleteLocalRef(method.classID);
}

bool AdvMob::getIsFinalVideo() {
    JniMethodInfo method;
    JniHelper::getStaticMethodInfo(method, "org/cocos2dx/cpp/AppActivity", "getIsFinalVideo", "()Z");
    bool res = method.env->CallStaticBooleanMethod(method.classID, method.methodID);
    method.env->DeleteLocalRef(method.classID);

    return res;
}

void AdvMob::resetIsFinalVideo() {
    JniMethodInfo method;
    JniHelper::getStaticMethodInfo(method, "org/cocos2dx/cpp/AppActivity", "resetIsFinalVideo", "()V");
    method.env->CallStaticVoidMethod(method.classID, method.methodID);
    method.env->DeleteLocalRef(method.classID);
}

#endif
