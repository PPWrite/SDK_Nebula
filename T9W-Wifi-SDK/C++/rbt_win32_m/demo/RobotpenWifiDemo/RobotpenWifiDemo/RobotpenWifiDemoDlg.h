
// RobotpenWifiDemoDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "WBDlg.h"

// CRobotpenWifiDemoDlg 对话框
class CRobotpenWifiDemoDlg : public CDialogEx
{
// 构造
public:
	CRobotpenWifiDemoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_ROBOTPENWIFIDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
