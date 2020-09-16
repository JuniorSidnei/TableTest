//
// Created by Pichau on 15/09/2020.
//

#include "Network.h"

//using namespace rapidjson;

//void Network::onHttpRequestCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response) {
//
//    if (!response) {
//        return;
//    }
//
//    //std::vector<char>* json = response->getResponseData();
//
////    Document kitDocument;
////    kitDocument.Parse(json->data());
////
////    GenericArray<false, GenericValue<UTF8<char>>::ValueType> kits = kitDocument["kits"].GetArray();
//
////    for(auto& kit : kits) {
////        KitData.name = kit["name"].GetString();
////        KitData.authorName = kit["authorName"].GetString();
////        KitData.musicName = kit["musicName"].GetString();
////        KitData.imgUrl = kit["imageUrl"].GetString();
////    }
//}

void Network::getRequest(const std::string& urlRequest, std::function<void(rapidjson::Document)> onFinishRequest) {

    request = new (std :: nothrow) cocos2d::network::HttpRequest();
    request->setUrl(urlRequest);
    request->setRequestType(cocos2d::network::HttpRequest::Type::GET);
    request->setResponseCallback([onFinishRequest](cocos2d::network::HttpClient* client, cocos2d::network::HttpResponse* response) {

        if (!response) {
            return;
        }

        rapidjson::Document document;
        document.Parse(response->getResponseData()->data());
        onFinishRequest(std::move(document));
    });
    cocos2d::network::HttpClient::getInstance()->sendImmediate(request);
    request->release();
}

