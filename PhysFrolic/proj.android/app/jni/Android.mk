LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := $(LOCAL_PATH)/hellocpp/main.cpp \
                   $(LOCAL_PATH)/../../../Classes/AnimationTools.cpp \
                   $(LOCAL_PATH)/../../../Classes/AppDelegate.cpp \
                   $(LOCAL_PATH)/../../../Classes/ArcadeUI.cpp \
                   $(LOCAL_PATH)/../../../Classes/BackgroundLayer.cpp \
                   $(LOCAL_PATH)/../../../Classes/CloudLayer.cpp \
                   $(LOCAL_PATH)/../../../Classes/EduUI.cpp \
                   $(LOCAL_PATH)/../../../Classes/ForegroundLayer.cpp \
                   $(LOCAL_PATH)/../../../Classes/FrolicArcade.cpp \
                   $(LOCAL_PATH)/../../../Classes/FrolicEdu.cpp \
                   $(LOCAL_PATH)/../../../Classes/GameOver.cpp \
                   $(LOCAL_PATH)/../../../Classes/FrolicUtils.cpp \
                   $(LOCAL_PATH)/../../../Classes/AdvMob.cpp \
                   $(LOCAL_PATH)/../../../Classes/HerbLayer.cpp \
                   $(LOCAL_PATH)/../../../Classes/Loading.cpp \
                   $(LOCAL_PATH)/../../../Classes/MenuLayer.cpp \
                   $(LOCAL_PATH)/../../../Classes/MovingButton.cpp \
                   $(LOCAL_PATH)/../../../Classes/PhysEngine.cpp \
                   $(LOCAL_PATH)/../../../Classes/Player.cpp \
                   $(LOCAL_PATH)/../../../Classes/Settings.cpp \
                   $(LOCAL_PATH)/../../../Classes/Stone.cpp \
                   $(LOCAL_PATH)/../../../Classes/StoneLayer.cpp \
                   $(LOCAL_PATH)/../../../Classes/TitleScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/TopGUI.cpp \
                   $(LOCAL_PATH)/../../../Classes/GoldLayer.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cc_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module, cocos)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
