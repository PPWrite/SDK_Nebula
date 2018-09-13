#ifndef _RBT_WIN_H_
#define _RBT_WIN_H_
#include "rbt_win_common.h"

#ifdef __cplusplus
extern "C" {
#endif

	// 初始化
	bool rbt_win_init(Init_Param* arg);
	//释放
	void rbt_win_uninit();
	//发送命令
	void rbt_win_send(int cmdId);
	//开始答题
	//type 0为主观题 1为客观题
	//pTopicType 题目总数
	//pTopicType 题目类型 1判断 2单选 3多选 4抢答
	//mac 为空时，发送命令到所有设备，否则为当前mac设备
	bool rbt_win_send_startanswer(int type, int totalTopic, char* pTopicType, const char* mac = "");
	//停止答题
	//mac 为空时，发送命令到所有设备，否则为当前mac设备
	bool rbt_win_send_stopanswer(const char* mac = "");
	//结束答题
	//mac 为空时，发送命令到所有设备，否则为当前mac设备
	bool rbt_win_send_endanswer(const char* mac = "");
	//开启服务
	bool rbt_win_start();
	//停止服务
	void rbt_win_stop();
	//设置学生姓名
	void rbt_win_config_stu(const char *mac, const char *stu);
	//设置学生中文姓名
	void rbt_win_config_bmp_stu(const char *mac, const char *stuNo, const char *stuName);
	//配网
	//source 默认为空,暂时无效
	int rbt_win_config_wifi(const char *ssid, const char *pwd, const char *source = "");
	//切换网络
	//ip为空时，依次遍历本机网卡并发送
	//port 默认6001
	//source 默认为空,暂时无效
	int rbt_win_config_net(const char *ip, int port, bool mqtt, bool tcp, const char *source = "");
	//配网并切换网络
	//source 默认为空,暂时无效
	int rbt_win_config_wifi_net(const char *ssid, const char *pwd, const char *ip, int port, bool mqtt, bool tcp, const char *source = "");
	//设置报点频率 
	//freq范围为0-4，0为最高，4为最低
	void rbt_win_config_freq(int freq);
	//设置休眠时间 
	//mins 分钟
	void rbt_win_config_sleep(int mins);
	//设置打开模组
	void rbt_win_open_module(bool open);
	//设置打开悬浮点
	void rbt_win_open_suspension(bool open);

#ifdef __cplusplus
}

#endif

#endif

