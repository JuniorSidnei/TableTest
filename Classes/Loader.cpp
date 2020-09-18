//
// Created by Pichau on 17/09/2020.
//

#include "Loader.h"

std::unique_ptr<cocos2d::network::Downloader> Loader::_downloader;

std::unique_ptr<cocos2d::network::Downloader> & Loader::getDownloader() {
    return _downloader;
}

void Loader::loadExternal() {

    auto isHttp = getURL().compare(0,4, "http") == 0;

    if(isHttp) {

        auto fileName = getURL();
        std::size_t found = fileName.find_last_of("/\\");
        fileName = fileName.substr(found);

        auto filePath = cocos2d::FileUtils::getInstance()->getWritablePath() + fileName;
        auto fileExists = cocos2d::FileUtils::getInstance()->isFileExist(filePath);

        if(fileExists) {
            setURL(filePath);
            return;
        }

        _downloader->createDownloadFileTask(getURL(), filePath, fileName);

    }
    else {
        GLoader::loadExternal();
    }
}

void Loader::freeExternal(cocos2d::SpriteFrame *sprite) {
    GLoader::freeExternal(sprite);
}

void Loader::setDownloader(cocos2d::network::Downloader *downloader) {
    _downloader.reset(downloader);
}
