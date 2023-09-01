#include "pch.h"
#include "Dashboard.h"
#include <bakkesmod/wrappers/GameWrapper.h>
#include <bakkesmod/wrappers/GameEvent/ServerWrapper.h>
#include <bakkesmod/wrappers/GameEvent/GameEventWrapper.h>
#include <bakkesmod/wrappers/GameObject/TeamWrapper.h>
#include <bakkesmod/wrappers/GameObject/PriWrapper.h>
#include <bakkesmod/wrappers/GameEvent/TeamGameEventWrapper.h>
#include <bakkesmod/wrappers/Engine/ActorWrapper.h>
#include <bakkesmod/wrappers/Engine/ObjectWrapper.h>
#include <aws/dynamodb/DynamoDBClient.h>
#include <aws/dynamodb/model/ListTablesRequest.h>
#include <aws/dynamodb/model/ListTablesResult.h>
#include <iostream>
#include <functional>
#include <thread>
#include <chrono>

BAKKESMOD_PLUGIN(Dashboard, "Rocket League Game Dashboard", "1.0", PLUGINTYPE_FREEPLAY)

void Dashboard::log(std::string msg) {
	cvarManager->log(msg);
}


void Dashboard::loadHooks() {
   
    gameWrapper->HookEvent("Function TAGame.GameEvent_TA.StartEvent",
        std::bind(&Dashboard::dynamoDbOps, this));
    gameWrapper->HookEvent("Function ProjectX.GRI_X.EventGameStarted",
        std::bind(&Dashboard::dynamoDbOps, this));
     gameWrapper->HookEvent("Function TAGame.GameEvent_TA.StartCountDown",
        std::bind(&Dashboard::dynamoDbOps, this));
    gameWrapper->HookEvent("Function ProjectX.OnlinePlayer_X.OnNewGame",
        std::bind(&Dashboard::dynamoDbOps, this));
    gameWrapper->HookEvent("Function GameEvent_Soccar_TA.Active.EndState",
        std::bind(&Dashboard::dynamoDbOps, this));
}


void Dashboard::onLoad() {
	this->log("Dashboard plugin started..");
	this->loadHooks();
	
}


void Dashboard::dynamoDbOps() {
	{   
		Aws::SDKOptions options;
        InitAPI(options);
        
		{
		
		  dynamoClient = std::make_shared<Aws::DynamoDB::DynamoDBClient>();
		
		  Aws::DynamoDB::Model::ListTablesRequest req;
		  auto outcome = dynamoClient->ListTables(req);

		  if (outcome.IsSuccess()) {
		    	this->log("Your DynamoDB tables:");

		    	Aws::Vector<Aws::String> table_list = outcome.GetResult().GetTableNames();

			    for (auto const& table_name : table_list) {
				   this->log(table_name);
			    }
		  }
		   else {
			  this->log("ListTables error: " + outcome.GetError().GetExceptionName() + " - " + outcome.GetError().GetMessage());
		   }
	  }
	  
	  dynamoClient = std::make_shared<Aws::DynamoDB::DynamoDBClient>();

      ShutdownAPI(options); // 
	  
	}
    
}



void Dashboard::onUnload() {
	this->log("Dashboard plugin unloaded..");
}


