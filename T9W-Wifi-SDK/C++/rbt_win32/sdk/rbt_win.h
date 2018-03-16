#ifndef _RBT_WIN_H_
#define _RBT_WIN_H_
#include "rbt_win_common.h"

#ifdef __cplusplus
extern "C" {
#endif

	// ≥ı ºªØ
	void rbt_win_init(Init_Param* arg);
	void rbt_win_uninit();

	void rbt_win_send(sendCmdID cmdId);
	bool rbt_win_send_startanswer(int totalTopic, char* pTopicType);
	bool rbt_win_send_stopanswer();
	bool rbt_win_start();
	void rbt_win_stop();
	int rbt_win_config(const char *ssid,const char *pwd,const char *stu,const char *source);

#ifdef __cplusplus
}

#endif

#endif

