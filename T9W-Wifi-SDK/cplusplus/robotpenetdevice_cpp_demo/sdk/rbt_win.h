#ifndef _RBT_WIN_H_
#define _RBT_WIN_H_
#include "rbt_win_common.h"

#ifdef __cplusplus
extern "C" {
#endif

	// 初始化
	bool rbt_win_init(Init_Param* arg);
	void rbt_win_uninit();

	void rbt_win_send(sendCmdID cmdId);
	bool rbt_win_send_startanswer(int type, int totalTopic, char* pTopicType);
	//停止答题
	bool rbt_win_send_stopanswer();
	//结束答题
	bool rbt_win_send_endanswer();
	bool rbt_win_start();
	void rbt_win_stop();
	void rbt_win_config_stu(const char *mac, const char *stu);
	void rbt_win_config_bmp_stu(const char *mac, const char *stuNo, const char *stuName);
	int rbt_win_config_wifi(const char *ssid, const char *pwd, const char *source);
	int rbt_win_config_net(const char *ip, int port, bool mqtt, bool tcp, const char *source);
	int rbt_win_config_wifi_net(const char *ssid, const char *pwd, const char *ip, int port, bool mqtt, bool tcp, const char *source);
	void rbt_win_config_freq(int freq);
	void rbt_win_config_sleep(int mins);
	void rbt_win_open_module(bool open);

#ifdef __cplusplus
}

#endif

#endif

