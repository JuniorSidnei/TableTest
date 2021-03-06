/****************************************************************************
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

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include <extensions/cocos-ext.h>
#include "Loader.h"

struct KitData {
    std::string name;
    std::string authorName;
    std::string musicName;
    std::string imgUrl;
};


USING_NS_FGUI;

class HelloWorld : public cocos2d::Scene//, public cocos2d::extension::TableViewDataSource, public cocos2d::extension::TableViewDelegate
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

//    cocos2d::Sprite *createTopPanel();
//    cocos2d::Sprite *createSongPanel(const cocos2d::Vec2 &position);

      void populateKitPanels();
//    virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view)override {};
//    virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view)override {}
//    virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell)override;
//    virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx)override;
//    virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)override;
//    virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table)override;

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

public:
    //cocos2d::extension::TableView* tableView;

    GRoot* _groot;
    GComponent* _view;
    GList* _list;
    Network _network;
    std::vector<KitData> _kitDatas;
    cocos2d::Map<std::string, Loader*> _loadersMap;
};

#endif // __HELLOWORLD_SCENE_H__
