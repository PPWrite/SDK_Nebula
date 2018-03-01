#pragma once
#include "robotpen_global.h"
#include "robopenentity.h"


/*
* summary: mqtt����ӿ�
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
	* ��ʼ��
	* @return returnCode �ӿڵ��÷�����
	*/
	returnCode init(Init_Options* opts);

	/*
	* �첽��¼mqtt������
	* @return returnCode �ӿڵ��÷�����
	*/
	returnCode loginMqttServer();

	/*
	* �Ͽ��������������
	* @return void ��
	*/
	void disconnectMqttServer();

	/*
	* ��ȡ����˹켣
	* @param [IN] strNoteKey ָ��key
	* @param [OUT] �켣����
	* @return returnCode �ӿڵ��÷����� 
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

