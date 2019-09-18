#ifndef _RBT_WIN_H_
#define _RBT_WIN_H_
#include "rbt_win_common.h"

#ifdef __cplusplus
extern "C" {
#endif

	// 初始化
	bool rbt_win_init(Init_Param* arg);
	// 初始化
	bool rbt_win_init2(int port, int listenCount, bool open, bool optimize);
	//释放
	void rbt_win_uninit();
	//发送命令
	void rbt_win_send(int cmdId, const char *mac = "");
	//开始答题
	//type 0为主观题 1为客观题 2为投票 3为不定选择 4为测试 5为书写
	//totalTopic 题目总数
	//pTopicType 题目类型 1判断 2单选 3多选 4抢答 5解答
	//mac 为空时，发送命令到所有设备，否则为当前mac设备
	bool rbt_win_send_startanswer(int type, int totalTopic, char* pTopicType, const char* mac = "");
	//开始答题(若支持多主观题用此接口)
	//type 0为主观题 1为客观题
	//totalTopic 题目总数
	//pTopicType 题目类型 1判断 2单选 3多选 4抢答
	//mac 为空时，发送命令到所有设备，否则为当前mac设备
	bool rbt_win_send_startanswerEx(int type, int totalTopic, char* pTopicType, const char* mac = "");
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
	int rbt_win_config_stu(const char *mac, const char *stu);
	//设置学生中文姓名
	int rbt_win_config_bmp_stu(const char *mac, const char *stuNo, const char *stuName);
	//设置学生中文姓名 超过3个...显示
	int rbt_win_config_bmp_stu_more(const char *mac, const char *stuNo, const char *stuName);
	//设置学生中文姓名2
	int rbt_win_config_bmp_stu2(const char *mac, const char *stuName);
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
	int rbt_win_config_freq(int freq, const char* mac = "");
	//设置休眠时间 
	//mins 分钟
	int rbt_win_config_sleep(int mins, const char* mac = "");
	//设置打开模组
	int rbt_win_open_module(bool open, const char* mac = "");
	//设置打开悬浮点
	void rbt_win_open_suspension(bool open);
	//获取画布ID
	void rbt_win_get_canvas_id(int canvasID = 0);
	//设置刷新时间 1-5秒
	void rbt_win_set_screen_freq(int seconds);
	//设置心跳(测试)
	void rbt_win_set_keepalive(int channel, int enable, int keepintvl, int keepcnt);
	//删除离线笔记
	bool rbt_win_del_notes(bool del, const char* mac = "");
	//设置手写板中心点偏移
	void rbt_win_set_offset_center(int x = 0, int y = 0, const char* mac = "");
	//笔迹优化
	//优化笔迹转成path
	float* rbt_win_toPath(const char *mac, float* points, int len, int *nLen);
	//转成优化轨迹的path
	float* rbt_win_toTrailsPath(const char *mac, float* points, int len, int *nLen);
	//设置线条是否进行spline处理
	void rbt_win_setIsSpline(bool open);
	//设置笔宽度
	void rbt_win_setPenWidth(float width);
	//设置拖尾阈值，设置的越小，拖尾越长(0~1)
	void rbt_win_setPointDelay(float delay);
	//设置粗细变化阈值，设置的越小，粗细变化越小
	void rbt_win_setPointDamping(float damping);
	//设置基础宽度，用于过滤点和点之间的距离，默认取PenWidth
	void rbt_win_setBaseWidth(float width);
	//设置结尾宽度，此参数决定拖尾笔锋终点宽度，默认取BaseWidth * 0.1
	void rbt_win_setEndWidth(float width);
	//笔锋收尾触发速度判断，当速度大于笔宽度/decrease时会触发笔锋
	void rbt_win_setWidthDecrease(float decrease);

#ifdef __cplusplus
}

#endif

#endif

