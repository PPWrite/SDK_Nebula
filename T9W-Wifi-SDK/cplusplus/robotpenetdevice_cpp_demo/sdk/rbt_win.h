#ifndef _RBT_WIN_H_
#define _RBT_WIN_H_
#include "rbt_win_common.h"

#ifdef __cplusplus
extern "C" {
#endif

	// ��ʼ��
	bool rbt_win_init(Init_Param* arg);
	//�ͷ�
	void rbt_win_uninit();
	//��������
	void rbt_win_send(int cmdId);
	//��ʼ����
	//type 0Ϊ������ 1Ϊ�͹���
	//pTopicType ��Ŀ����
	//pTopicType ��Ŀ���� 1�ж� 2��ѡ 3��ѡ 4����
	//mac Ϊ��ʱ��������������豸������Ϊ��ǰmac�豸
	bool rbt_win_send_startanswer(int type, int totalTopic, char* pTopicType, const char* mac = "");
	//ֹͣ����
	//mac Ϊ��ʱ��������������豸������Ϊ��ǰmac�豸
	bool rbt_win_send_stopanswer(const char* mac = "");
	//��������
	//mac Ϊ��ʱ��������������豸������Ϊ��ǰmac�豸
	bool rbt_win_send_endanswer(const char* mac = "");
	//��������
	bool rbt_win_start();
	//ֹͣ����
	void rbt_win_stop();
	//����ѧ������
	void rbt_win_config_stu(const char *mac, const char *stu);
	//����ѧ����������
	void rbt_win_config_bmp_stu(const char *mac, const char *stuNo, const char *stuName);
	//����
	//source Ĭ��Ϊ��,��ʱ��Ч
	int rbt_win_config_wifi(const char *ssid, const char *pwd, const char *source = "");
	//�л�����
	//ipΪ��ʱ�����α�����������������
	//port Ĭ��6001
	//source Ĭ��Ϊ��,��ʱ��Ч
	int rbt_win_config_net(const char *ip, int port, bool mqtt, bool tcp, const char *source = "");
	//�������л�����
	//source Ĭ��Ϊ��,��ʱ��Ч
	int rbt_win_config_wifi_net(const char *ssid, const char *pwd, const char *ip, int port, bool mqtt, bool tcp, const char *source = "");
	//���ñ���Ƶ�� 
	//freq��ΧΪ0-4��0Ϊ��ߣ�4Ϊ���
	void rbt_win_config_freq(int freq);
	//��������ʱ�� 
	//mins ����
	void rbt_win_config_sleep(int mins);
	//���ô�ģ��
	void rbt_win_open_module(bool open);
	//���ô�������
	void rbt_win_open_suspension(bool open);

#ifdef __cplusplus
}

#endif

#endif

