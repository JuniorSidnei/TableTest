//
// Created by Pichau on 15/09/2020.
//

#ifndef TEMPLATECPP_NETWORK_H
#define TEMPLATECPP_NETWORK_H

#include <cocos/network/HttpClient.h>
#include "cocos2d.h"
#include <json/document-wrapper.h>

class Network {

public:

    cocos2d::network::HttpRequest* request;

    void getRequest(const std::string &urlRequest,
                std::function<void(rapidjson::Document)> onFinishRequest);
};

#endif //TEMPLATECPP_NETWORK_H
