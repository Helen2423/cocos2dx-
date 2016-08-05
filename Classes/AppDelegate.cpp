#include "AppDelegate.h"
#include "MainMenu.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate() {
    
}

AppDelegate::~AppDelegate()
{
    
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }
    
    glview->setDesignResolutionSize(1136,640, ResolutionPolicy::FIXED_HEIGHT);
    
    // turn on display FPS 调试信息关闭
    director->setDisplayStats(false);
   
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 30);
    
    // create a scene. it's an autorelease object
    auto scene = MainMenu::createScene();
   
    // run
    director->runWithScene(scene);
    
    // 开始播放背景音乐 循环播放
    SimpleAudioEngine::getInstance()->playBackgroundMusic("background.mp3");
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
