
// RobotpenWifiDemoDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "WBDlg.h"

// CRobotpenWifiDemoDlg �Ի���
class CRobotpenWifiDemoDlg : public CDialogEx
{
// ����
public:
	CRobotpenWifiDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_ROBOTPENWIFIDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	static void mqtt_onConnectResult(void* context, MqttConnect_Data* response);
	static void mqtt_onPushJob(void* conect, std::string& strNoteKey, std::string& strTarget);
	static void mqtt_onStartdAnswer(void* context);
	static void mqtt_onStopAnswer(void* context);
	static void mqtt_onFinishedAnswer();
private:
	mqtthandle handle;
	CWBDlg *m_pDlg;
public:
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedButtonStart();
	void InitListCtrl();
	void AddTarget(const CString &strTarget,const CString &strNoteKey);
	void ShowItem();
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	CString GetErrorMsg(returnCode code);
};
