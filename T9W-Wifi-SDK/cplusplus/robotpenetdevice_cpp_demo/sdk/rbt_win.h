#ifndef _RBT_WIN_H_
#define _RBT_WIN_H_
#include "rbt_win_common.h"

#ifdef __cplusplus
extern "C" {
#endif

	// ≥ı ºªØ
	bool rbt_win_init(Init_Param* arg);
	void rbt_win_uninit();

	void rbt_win_send(sendCmdID cmdId);
	bool rbt_win_send_startanswer(int type,int totalTopic, char* pTopicType);
	bool rbt_win_send_stopanswer();
	bool rbt_win_start();
	void rbt_win_stop();
	void rbt_win_config_stu(const char *mac, const char *stu);
	int rbt_win_config_wifi(const char *ssid, const char *pwd, const char *stu, const char *source);
	int rbt_win_config_net(const char *group, const char *ip, int port, bool mqtt, bool tcp, const char *source);
	void rbt_win_config_freq(int freq);
	void rbt_win_config_sleep(int mins);

#ifdef __cplusplus
}

#endif

#endif

