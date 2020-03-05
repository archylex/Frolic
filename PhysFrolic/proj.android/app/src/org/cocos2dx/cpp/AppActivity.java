/****************************************************************************
Copyright (c) 2015-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.cpp;

import android.os.Bundle;
import android.app.Activity;
import org.cocos2dx.lib.Cocos2dxActivity;
import android.widget.Toast;
import android.net.NetworkInfo;
import android.net.ConnectivityManager;
import android.content.Context; 
import com.google.android.gms.ads.AdListener;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.InterstitialAd;
import com.google.android.gms.ads.MobileAds;
import com.google.android.gms.ads.reward.RewardItem;
import com.google.android.gms.ads.reward.RewardedVideoAd;
import com.google.android.gms.ads.reward.RewardedVideoAdListener;

public class AppActivity extends Cocos2dxActivity {

    private static Activity instance;
    private static InterstitialAd interstitialAd;
    private static RewardedVideoAd mRewardedVideoAd;
    private static ConnectivityManager cm;
    private static NetworkInfo mWifi;
    private static boolean isFinalVideo;

    private static final String AD_UNIT_ID = "ca-app-pub-3143297239120863/9979422174";    
    private static final String APP_ID = "ca-app-pub-3143297239120863~6004518146";
    private static final String AD_VIDEO_ID = "ca-app-pub-3143297239120863/8099009070";

    @Override
    protected void onCreate(Bundle savedInstanceState) {        
        instance = this;
        super.setEnableVirtualButton(false);
        super.onCreate(savedInstanceState);

        isFinalVideo = false;

        cm = (ConnectivityManager)getSystemService(Context.CONNECTIVITY_SERVICE);

        mWifi = cm.getNetworkInfo(ConnectivityManager.TYPE_WIFI);
 
        MobileAds.initialize(this, APP_ID);

        interstitialAd = new InterstitialAd(this);
         
        interstitialAd.setAdUnitId(AD_UNIT_ID);
 
        interstitialAd.setAdListener(new AdListener() {
            @Override
            public void onAdClosed() {
                startAd();                
            }
        });
        
        startAd();
        
                
        mRewardedVideoAd = MobileAds.getRewardedVideoAdInstance(this);

        mRewardedVideoAd.setRewardedVideoAdListener(new RewardedVideoAdListener() { 
            @Override
            public void onRewarded(RewardItem rewardItem) {
                Toast.makeText(AppActivity.this, "Thank you! Close this video and continue the game.", Toast.LENGTH_LONG).show();
            }
 
            @Override
            public void onRewardedVideoAdLeftApplication() {
            }
 
            @Override
            public void onRewardedVideoAdClosed() {
                //Toast.makeText(AppActivity.this, "onRewardedVideoAdClosed", Toast.LENGTH_SHORT).show();
                loadRewardedVideoAd();
            }
 
            @Override
            public void onRewardedVideoAdFailedToLoad(int errorCode) {                
                if (errorCode == 3) {
                    Toast.makeText(AppActivity.this, "No rewarded video now", Toast.LENGTH_SHORT).show();
                    
                } else {
                    Toast.makeText(AppActivity.this, "No network connection", Toast.LENGTH_SHORT).show();
                }
            }
 
            @Override
            public void onRewardedVideoAdLoaded() {                
            }
 
            @Override
            public void onRewardedVideoAdOpened() {
            }
 
            @Override
            public void onRewardedVideoStarted() {                
            }

            @Override
            public void onRewardedVideoCompleted() {
                isFinalVideo = true;
                loadRewardedVideoAd();
            }
        });
 
        if ( mWifi.isConnected() ) {
            loadRewardedVideoAd();
        }
    }
    
    public static void startAd() {
        if (!interstitialAd.isLoading() && !interstitialAd.isLoaded()) {
            AdRequest adRequest = new AdRequest.Builder().build();
            interstitialAd.loadAd(adRequest);
        }
    }

    public static void showInterstitial() {
        if ( interstitialAd.isLoaded()) {
            interstitialAd.show();    
            AppActivity.startAd();        
        } else {        
            startAd();
        }        
    }

    public static Activity getInstance() {
        return instance;
    }

    public static void loadRewardedVideoAd() {
        mRewardedVideoAd.loadAd(AD_VIDEO_ID, new AdRequest.Builder().build());
    }
 
    public static void showRewardedVideo() {
        if ( mWifi.isConnected() ) {
            if (mRewardedVideoAd.isLoaded()) {                
                mRewardedVideoAd.show();                
                loadRewardedVideoAd();
            }
        }
    }

    public static boolean getIsFinalVideo() {
        return isFinalVideo;
    }

    public static void resetIsFinalVideo() {
        isFinalVideo = false;
    }
 
    @Override
    public void onResume() {
        mRewardedVideoAd.resume(this);
        super.onResume();
    }
 
    @Override
    public void onPause() {
        mRewardedVideoAd.pause(this);
        super.onPause();
    }
 
    @Override
    public void onDestroy() {
        mRewardedVideoAd.destroy(this);
        super.onDestroy();
    }

}