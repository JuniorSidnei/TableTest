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

#include <cocos/network/HttpRequest.h>
#include "HelloWorldScene.h"
#include "CustomTableViewCell.h"
#include "ui/CocosGUI.h"
#include "Network.h"

const char* font = "fonts/Uni Sans Heavy.otf";

USING_NS_CC;
USING_NS_CC_EXT;
using namespace rapidjson;

Scene* HelloWorld::createScene() {
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename) {
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init() {

    if ( !Scene::init() ) {
        return false;
    }

    UIObjectFactory::setLoaderExtension([](){
       return Loader::create();
    });

    Loader::setDownloader(new cocos2d::network::Downloader());
    Loader::getDownloader()->onFileTaskSuccess = [&](const cocos2d::network::DownloadTask& task) {

        auto loaderKit = _loadersMap.at(task.identifier);
        loaderKit->setURL(task.storagePath);
    };

    //request data from server
    _network.getRequest("http://api.kondzilla.opalastudios.com/api/fetch?version=4", [&](rapidjson::Document document) {

        auto kits = document["kits"].GetArray();

        for(const auto& kit : kits) {
            KitData tempData;
            tempData.name = kit["name"].GetString();
            tempData.authorName = kit["authorName"].GetString();
            tempData.musicName = kit["musicName"].GetString();
            tempData.imgUrl = kit["imageUrl"].GetString();
            _kitDatas.push_back(tempData);
        }

        populateKitPanels();
    });

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    _groot = GRoot::create(this);
    _groot->retain();

    UIPackage::addPackage("ui/MenuKit");
    _view = UIPackage::createObject("MenuKit", "Main")->as<GComponent>();
    _groot->addChild(_view);

    _list = _view->getChild("KitList")->as<GList>();

//    // add background
//    auto bg = DrawNode::create();
//    bg->drawSolidRect(origin, visibleSize, Color4F(0.14,0.16,0.18, 1)); // 36, 43, 46
//    this->addChild(bg);

    //this->addChild(createTopPanel());

//    tableView = TableView::create(this, Size(828, 1472));
//    tableView->setDirection(ScrollView::Direction::VERTICAL);
//    tableView->setPosition(Vec2(50,0));
//    tableView->setTouchEnabled(true);
//    tableView->setBounceable(true);
//    tableView->setDelegate(this);
//    tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
//    this->addChild(tableView);
//    tableView->reloadData();
    return true;
}

void HelloWorld::populateKitPanels() {

    for (auto& _kitData : _kitDatas) {
       auto kitPanel =  _list->addItemFromPool()->as<GComponent>();

        auto authorName = kitPanel->getChild("AuthorName")->as<GTextField>();
        authorName->setText(_kitData.authorName);

        auto musicName = kitPanel->getChild("MusicName")->as<GTextField>();
        musicName->setText(_kitData.musicName);

        auto loader = kitPanel->getChild("SpriteKitLoader")->as<Loader>();

        loader->setURL(_kitData.imgUrl);
        _loadersMap.insert(_kitData.name, loader);
    }
}

//cocos2d::Sprite * HelloWorld::createSongPanel(const Vec2 &position) {
//
//    //add kitPanel
//    auto kitPanelBg = Sprite::create("KitPanelBg.png");
//    kitPanelBg->setPosition(position);
//
//    //add arrowBtnBg
//    auto arrowBtnBg = Sprite::create("arrowBg.png");
//    arrowBtnBg->setPosition(700,40);
//    kitPanelBg->addChild(arrowBtnBg);
//
//    //add arrowBtn
//    auto arrowBtn = MenuItemImage::create("arrowBtn.png", "arrowBtn.png");
//    arrowBtn->setPosition(700,40);
//    kitPanelBg->addChild(arrowBtn,2);
//
//    //add kitNameBg
//    auto kitNameBg = Sprite::create("KitNameBg.png");
//    kitNameBg->setPosition(100,110);
//    kitPanelBg->addChild(kitNameBg,2);
//
//    //TEXTS
//    //add kitTxt
//    auto kitTxt = Label::createWithTTF("KIT", font, 50);
//    kitTxt->setPosition(90,130);
//    kitPanelBg->addChild(kitTxt,2);
//
//    //add nameTxt
//    auto nameTxt = Label::createWithTTF("NAME", font, 50);
//    nameTxt->setPosition(90,80);
//    kitPanelBg->addChild(nameTxt,2);
//
//    //add inspiredTxt
//    auto inspiredTxt = Label::createWithTTF("INSPIRADO EM", font, 25);
//    inspiredTxt->setPosition(280,160);
//    kitPanelBg->addChild(inspiredTxt,2);
//
//    //add kitNameBg
//    auto inspiredImg = Sprite::create("Rectangle52.png");
//    inspiredImg->setPosition(235,145);
//    kitPanelBg->addChild(inspiredImg,2);
//
//    //add songNameTxt
//    auto songNameTxt = Label::createWithTTF("NOME DA MÚSICA", font, 35);
//    songNameTxt->setPosition(330,100);
//    kitPanelBg->addChild(songNameTxt,2);
//
//    //add artistNameTxt
//    auto artistNameTxt = Label::createWithTTF("NOME DOS ARTISTAS", font, 25);
//    artistNameTxt->setPosition(315,50);
//    kitPanelBg->addChild(artistNameTxt,2);
//
//    return kitPanelBg;
//}
//
//cocos2d::Sprite *HelloWorld::createTopPanel() {
//
//    //add top image
//    auto topBg = Sprite::create("topBg.png");
//    topBg->setPosition(420,1400);
//
//    //add closeBr to menu
//    auto closeBtn = Sprite::create("closeBtn.png");
//    closeBtn->setPosition(100, 80);
//    topBg->addChild(closeBtn, 1);
//
//    //add closeBr to menu
//    auto closeBtnX = MenuItemImage::create("XBtn.png", "XBtn.png");
//    closeBtnX->setPosition(100, 80);
//    topBg->addChild(closeBtnX, 2);
//    return topBg;
//}


//void HelloWorld::tableCellTouched(cocos2d::extension::TableView *table, cocos2d::extension::TableViewCell *cell) {
//    CCLOG("cell touched at index: %ld", static_cast<long>(cell->getIdx()));
//}
//
//cocos2d::Size HelloWorld::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx) {
//    return Size(741, 209);
//}
//
//cocos2d::extension::TableViewCell *HelloWorld::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx) {
//    auto string = StringUtils::format("%ld", static_cast<long>(idx));
//    TableViewCell *cell = table->dequeueCell();
//
//    if (!cell) {
//        cell = new (std::nothrow) CustomTableViewCell();
//        cell->autorelease();
//        auto songPanel = createSongPanel(Vec2(0,0));
//        songPanel->setPosition(Vec2(songPanel->getContentSize().width/2, 0));
//        cell->addChild(songPanel);
//    }
//    return cell;
//}
//
//ssize_t HelloWorld::numberOfCellsInTableView(cocos2d::extension::TableView *table) {
//    return 20;
//}
