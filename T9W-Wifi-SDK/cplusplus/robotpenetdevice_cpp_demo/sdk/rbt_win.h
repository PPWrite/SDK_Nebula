#ifndef _RBT_WIN_H_
#define _RBT_WIN_H_
#include "rbt_win_common.h"

#ifdef __cplusplus
extern "C" {
#endif

	// ��ʼ��
	bool rbt_win_init(Init_Param* arg);
	// ��ʼ��
	bool rbt_win_init2(int port, int listenCount, bool open, bool optimize);
	//�ͷ�
	void rbt_win_uninit();
	//��������
	void rbt_win_send(int cmdId, const char *mac = "");
	//��ʼ����
	//type 0Ϊ������ 1Ϊ�͹��� 2ΪͶƱ 3Ϊ����ѡ�� 4Ϊ���� 5Ϊ��д
	//totalTopic ��Ŀ����
	//pTopicType ��Ŀ���� 1�ж� 2��ѡ 3��ѡ 4���� 5���
	//mac Ϊ��ʱ��������������豸������Ϊ��ǰmac�豸
	bool rbt_win_send_startanswer(int type, int totalTopic, char* pTopicType, const char* mac = "");
	//��ʼ����(��֧�ֶ��������ô˽ӿ�)
	//type 0Ϊ������ 1Ϊ�͹���
	//totalTopic ��Ŀ����
	//pTopicType ��Ŀ���� 1�ж� 2��ѡ 3��ѡ 4����
	//mac Ϊ��ʱ��������������豸������Ϊ��ǰmac�豸
	bool rbt_win_send_startanswerEx(int type, int totalTopic, char* pTopicType, const char* mac = "");
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
	int rbt_win_config_stu(const char *mac, const char *stu);
	//����ѧ����������
	int rbt_win_config_bmp_stu(const char *mac, const char *stuNo, const char *stuName);
	//����ѧ���������� ����3��...��ʾ
	int rbt_win_config_bmp_stu_more(const char *mac, const char *stuNo, const char *stuName);
	//����ѧ����������2
	int rbt_win_config_bmp_stu2(const char *mac, const char *stuName);
	//TAL������������3(TAL֧��4����)
	int rbt_win_config_bmp_stu3(const char *mac, const char *stuNo, const char *stuName);
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
	int rbt_win_config_freq(int freq, const char* mac = "");
	//��������ʱ�� 
	//mins ����
	int rbt_win_config_sleep(int mins, const char* mac = "");
	//���ô�ģ��
	int rbt_win_open_module(bool open, const char* mac = "");
	//���ô�������
	void rbt_win_open_suspension(bool open);
	//��ȡ����ID
	void rbt_win_get_canvas_id(int canvasID = 0);
	//����ˢ��ʱ�� 1-5��
	void rbt_win_set_screen_freq(int seconds);
	//��������(����)
	void rbt_win_set_keepalive(int channel, int enable, int keepintvl, int keepcnt);
	//ɾ�����߱ʼ�
	bool rbt_win_del_notes(bool del, const char* mac = "");
	//������д�����ĵ�ƫ��
	void rbt_win_set_offset_center(int x = 0, int y = 0, const char* mac = "");
	//�ʼ��Ż�
	//�Ż��ʼ�ת��path
	float* rbt_win_toPath(const char *mac, float* points, int len, int *nLen);
	//ת���Ż��켣��path
	float* rbt_win_toTrailsPath(const char *mac, float* points, int len, int *nLen);
	//���������Ƿ����spline����
	void rbt_win_setIsSpline(bool open);
	//���ñʿ��
	void rbt_win_setPenWidth(float width);
	//������β��ֵ�����õ�ԽС����βԽ��(0~1)
	void rbt_win_setPointDelay(float delay);
	//���ô�ϸ�仯��ֵ�����õ�ԽС����ϸ�仯ԽС
	void rbt_win_setPointDamping(float damping);
	//���û�����ȣ����ڹ��˵�͵�֮��ľ��룬Ĭ��ȡPenWidth
	void rbt_win_setBaseWidth(float width);
	//���ý�β��ȣ��˲���������β�ʷ��յ��ȣ�Ĭ��ȡBaseWidth * 0.1
	void rbt_win_setEndWidth(float width);
	//�ʷ���β�����ٶ��жϣ����ٶȴ��ڱʿ��/decreaseʱ�ᴥ���ʷ�
	void rbt_win_setWidthDecrease(float decrease);
	//���ô�ӡ���㵱ǰ����ֵ(x1,y1���� x2,y2���ĵ� x3,y3����)
	void rbt_win_setPrintThreePoint(int x1, int y1, int x2, int y2, int x3, int y3);
	//���ô�ӡ��ƫ����
	void rbt_win_setPrintThreeOffset(int x1, int y1, int x2, int y2, int x3, int y3);
	//����X10ҳ�����Χ
	void rbt_win_setX10Matirx(int nMaxX, int nMaxY, int nWidth, int nHeight);
	//����E3Wҳ�����Χ
	void rbt_win_setE3WMatirx(int nMaxX, int nMaxY, int nWidth, int nHeight);
	//����x10�����Ƕ���ת
	void rbt_win_setX10EnableAngle(bool isEnable);
	//����X10����ͷ���ĵ�����
	void rbt_win_setX10CameraCenter(float centerX, float centerY);
	//����FB��д����Ϣ
	void rbt_win_setFBDeviceMessage(const char *mac, const char *msg);
	//�ϴ�WAV�����ļ�
	void rbt_win_upload_wavfile(const char *mac, const char *filePath);

#ifdef __cplusplus
}

#endif

#endif

