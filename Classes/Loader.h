//
// Created by Pichau on 17/09/2020.
//

#ifndef PROJ_ANDROID_LOADER_H
#define PROJ_ANDROID_LOADER_H

#include <cocos/network/CCDownloader.h>
#include "cocos2d.h"
#include "FairyGUI.h"
#include "Network.h"

USING_NS_FGUI;

class Loader : public GLoader {

public:

    virtual void loadExternal () override;

    virtual void freeExternal (cocos2d::SpriteFrame* sprite) override;

    static void setDownloader(cocos2d::network::Downloader *downloader);
    static std::unique_ptr<cocos2d::network::Downloader> &getDownloader();

    CREATE_FUNC(Loader);

public:
    static std::unique_ptr<cocos2d::network::Downloader> _downloader;
};


#endif //PROJ_ANDROID_LOADER_H
