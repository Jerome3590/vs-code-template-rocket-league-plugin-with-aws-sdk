#pragma once
#pragma comment(lib, "pluginsdk.lib")
#include "bakkesmod/wrappers/includes.h"
#include "bakkesmod/plugin/bakkesmodplugin.h"
#include <aws/core/Aws.h>
#include <aws/core/auth/AWSCredentialsProvider.h> 
#include <memory> 
#include <string>


namespace Aws {
    namespace DynamoDB {
        class DynamoDBClient;
    }
}

class Dashboard: public BakkesMod::Plugin::BakkesModPlugin
{
public:
    virtual void onLoad();
    virtual void onUnload();
private:
    Aws::SDKOptions options;
    std::shared_ptr<Aws::DynamoDB::DynamoDBClient> dynamoClient;
    void log(std::string msg);
    void dynamoDbOps();
    void loadHooks();

};

