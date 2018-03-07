#ifndef ROBOTPEN_ENTITY_H
#define ROBOTPEN_ENTITY_H

#include <string>

/*
* 连接事件类型
*/
enum connectEvt {
	mqttConnectEvt,
	mqttSubscribeEvt,
	mqttConnectLostEvt,

};

/*
* 接口返回码
*/
enum returnCode
{
	eOk,
	eFail,
	eActiveFail,
	eLoginMqttServerFail,
	eParameterError,
	eHttpRequestError,
	eParseError,
	eTrailsParseError,
	eMqttConnectError,
};

typedef struct _MqttConnect_Data
{
	connectEvt evty;
	int nErrorCode;
	std::string strMsg;
}MqttConnect_Data;

typedef void mqtt_onConnectResult(void* context, MqttConnect_Data* response);
typedef void mqtt_onPushJob(void* conect, std::string& strNoteKey, std::string& strTarget);
typedef void mqtt_onStartdAnswer(void* context);
typedef void mqtt_onStopAnswer(void* context);
typedef void mqtt_onFinishedAnswer();

typedef struct _Init_Options {
	mqtt_onConnectResult* onConnectResult;
	mqtt_onPushJob* onPushJob;
	mqtt_onStartdAnswer* onStartAnswer;
	mqtt_onStopAnswer* onStopAnswer;
	mqtt_onFinishedAnswer* onFinishedAnswer;
	void* context;

}Init_Options;

/*
* mqtt服务端推送的消息类型枚举
*/
enum MqttMT
{
	pushjob,
	trailsData,
	startAnswer,
	stopAnswer,
	finishedAnswer,
};

/*
* mqtt服务器推送的数据实体
*/
typedef struct _Mqtt_Data
{
	MqttMT mmt;
	void* data;
}Mqtt_Data;

/*
* 推送作业结构
*/
typedef struct _Push_Job
{
	std::string strDevice_Name;
	std::string strTarget;
	std::string strNote_key;
}Push_Job;

typedef unsigned short _u_short_;

typedef struct _Trails_Data
{
	_u_short_ ns;
	_u_short_ nx;
	_u_short_ ny;
	_u_short_ np;

	struct _Trails_Data* next;
}Trails_Data;

#pragma pack(1)

typedef struct _Origin_Data
{
	unsigned char id;
	unsigned char key;
	unsigned char x_l;
	unsigned char x_h;
	unsigned char y_l;
	unsigned char y_h;
	unsigned char press_l;
	unsigned char press_h;

}Origin_Data;

#pragma pack()
#endif