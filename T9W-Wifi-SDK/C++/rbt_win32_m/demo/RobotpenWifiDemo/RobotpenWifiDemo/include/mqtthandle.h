#pragma once
#include "robotpen_global.h"
#include "robopenentity.h"


/*
* summary: mqtt处理接口
* date: 2017-2-1
* author: robotpen
*/

class mqtthandlePrivate;

class ROBOTPEN_API mqtthandle
{
public:

	mqtthandle(void);
	~mqtthandle(void);
	/*
	* 初始化
	* @return returnCode 接口调用返回码
	*/
	returnCode init(Init_Options* opts);

	/*
	* 异步登录mqtt服务器
	* @return returnCode 接口调用返回码
	*/
	returnCode loginMqttServer();

	/*
	* 断开与服务器的连接
	* @return void 无
	*/
	void disconnectMqttServer();

	/*
	* 获取服务端轨迹
	* @param [IN] strNoteKey 指定key
	* @param [OUT] 轨迹数据
	* @return returnCode 接口调用返回码 
	*/
	returnCode getServerTrails(const std::string& strNoteKey, Trails_Data** pData);
	returnCode getServerTrails(const std::string& strNoteKey, char** pData);
	char* getTrailsCache(const std::string& strNoteKey);
	

	void cleaupJson(char* p);

public:

private:
	mqtthandlePrivate* d_ptr;
	R_DECLARE_PRIVATE(mqtthandle)
};

