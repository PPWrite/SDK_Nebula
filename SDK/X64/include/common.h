#pragma once

#define FILEVERSION "1.1.6.6"

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

#define NUM 60

#define NEBULA_VID		0x0483
#define P1_VID			0x0ED1

//#define USE_RECOG

enum eDevicePid
{
	GATEWAY_PID	=	0x6001,
	T8A_PID		=	0x6002,
	T9A_PID		=	0x6003,
	W5E_PID		=	0x6007,
	X8_PID		=	0x600d,
	T7PL_PID	=   0x600e,
	T7E_TS_PID	=	0x600f,
	T9_J0_PID	=	0x6012,
	J0_A4_P_PID	=	0x6013,
	T9E_PID		=	0x6014,
	J0_T9_PID	=	0x6015,
	W7_PID		=	0x6019,
	T8B_PID		=	0x601e,
	T9B_YD_PID	=	0x601f,
	T7B_HF_PID	=	0x6020,
	X8E_A5_PID	=	0x6021,
	T9W_PID		=	0x6022,
	T8C_PID		=	0x6023,
	T7E_PID		=	0x6025,
	T7E_HFHH_PID=	0x6026,
	P1_CX_M3_PID=   0x6028,
	T9A_EN_PID  =   0x6029,
	T9W_TY_PID	=	0x602a,
	S1_DE_PID	=	0x602c,
	J7E_PID		=	0x602d,
	J7B_HF_PID  =	0x602e,
	J7B_ZY_PID  =	0x602f,
	T8S_PID		=	0x6030,
	J7B_PID		=	0x6031,
	T9W_QX_PID	=	0x6032,
	K7_HW_PID	=   0x6033,
	K8_ZM_PID	=	0x6034,
	K7_C5_PID	=	0x6035,
	T9W_YJ_PID	=	0x6037,
	T7PL_CL_PID =	0x6038,
	T9W_WX_PID  =   0x6039,
	T8B_DH2_PID =	0x603a,
	T9W_B_KZ_PID=	0x603b,
	C5_PID		=	0x603c,
	T9B_PID		=	0x603d,
	T9B_ZXB_PID =	0x603e,
	T8B_D2_PID  =	0x603f,
	T9W_A_TY_PID= 	0x6040,
	T9W_A_XF_PID=	0x6041,
	W9_XF_PID	=	0x6042,
	T9W_TAL_PID	=	0x6046,
	X9_PID		=	0x6047,
	X9_TAL_PID	=	0x6049,
	T9W_H_PID	=	0x604a,
	T10_PID		=	0x604b,
	T7PL_XDF_PID=	0x604c,
	K8_HF_PID	=	0x604d,
	K8_PID		=	0x604e,
	J7B_XY_PID	=	0x604f,
	T9C_PID		=	0x6050,
	T9C_FB_PID	=	0x6051,
	T9W_H_TAL_PID   =   0x6052,
	K7W_PID = 0x6053,
	X10_PID = 0x6054,
	T9Y_PID = 0x6055,
	T9W_ZHL_PID = 0x6056,
	T8S_LQ_PID = 0x6057,
	E3W_PID = 0x6058,
	T9W_H2_PID = 0x605a,
	T9W_H_FB_PID = 0x605b,
	T9Y_TAL_PID = 0x605c,
	T9W_H_ZB_PID = 0x605d,
	X10_B_PID = 0x605e,
	J7M_PID = 0x605f,
	T8Y_PID = 0x6060,
	DONGLE_PID  =	0x5001,
	P1_PID		=   0x7806,
	
};

enum eDeviceType
{
	Unknow = 0,
	RobotPen_P7,
	Elite,
	Elite_Plus,
	RobotPen_P1,
	Elite_Plus_New,
	T8A,
	W5E,
	J0_A5,
	Gateway,
	Dongle,
	J0_A4,
	T9A,
	X8,
	T7PL,
	T7E_TS,
	T7_TS,
	T7_XGL,
	T9_J0,
	J0_A4_P,
	T9E,
	J0_T9,
	T7_CY,
	D1_CY,
	C7,
	W7,
	S7_JD,
	DM6,
	T7A,
	T7_HI,
	T8B,
	T9B_YD,
	T7B_HF,
	X8E_A5,
	T9W,
	T8C,
	S7_SD,
	T7E,
	T7E_HFHH,
	S7_JD_M3,
	P1_CX_M3,
	T9A_EN,
	T9W_TY,
	T9B_YD2,
	S1_DE,
	J7E,
	J7B_HF,
	J7B_ZY,
	T8S,
	J7B,
	T9W_QX,
	K7_HW,
	K8_ZM,
	K7_C5,
	T7C_BN,
	T9W_YJ,
	T7PL_CL,
	T9W_WX,
	T8B_DH2,
	T9W_B_KZ,
	C5,
	T9B,
	T9B_ZXB,
	T8B_D2,
	T9W_A_TY, 
	T9W_A_XF, 
	W9_XF,
	S7_TY_A,
	S7_TY_B,
	T7C,
	T9W_TAL,
	X9,
	T7A_QX,
	X9_TAL,
	T9W_H,
	T10,
	T7PL_XDF,
	K8_HF,
	K8,
	J7B_XY,
	T9C,
	T9C_FB,
	T9W_H_TAL,
	K7W,
	X10,
	T9Y,
	T9W_ZHL,
	T8S_LQ,
	E3W,
	D7,
	T9W_H2,
	T9W_H_FB,
	T9Y_TAL,
	T9W_H_ZB,
	X10_B,
	J7M,
	T8Y,
};
////////////////////////////////////////NEBULA///////////////////////////////////////
#pragma pack(1)
//״̬
typedef struct node_status
{
	uint8_t	 device_status;
	uint8_t  battery_level;
	uint8_t  note_num;
	uint8_t  note_percent;
	uint8_t	 feature;
	uint8_t  note_num_h;

}NODE_STATUS;
//����
typedef struct robot_report
{
	uint8_t cmd_id;
	uint8_t reserved;
	uint8_t payload[60];

}ROBOT_REPORT;
//�汾
typedef struct st_version
{
	uint8_t version;
	uint8_t version2;
	uint8_t version3;
	uint8_t version4;

}ST_VERSION;
//�豸��Ϣ
typedef struct st_device_info
{
	ST_VERSION version;
	uint8_t  custom_num;
	uint8_t  class_num;
	uint8_t  device_num;
	uint8_t  mac[6];
	uint16_t  hardware_num;

}ST_DEVICE_INFO;
//�豸�汾��
typedef struct st_device_version
{
	uint16_t hard_version;
	ST_VERSION version;

}ST_DEVICE_VERSION;
//ģ��汾��
typedef struct st_module_version
{
	uint8_t  low_version;
	uint8_t  high_version;
	uint8_t  adjust;

}ST_MODULE_VERSION;

typedef struct st_option_packet
{
	uint8_t id;
	uint8_t option[6];

}ST_OPTION_PACKET;

typedef struct st_rtc_info
{
	uint8_t note_time_year;
	uint8_t note_time_month;
	uint8_t note_time_day;
	uint8_t note_time_hour;
	uint8_t note_time_min;

} ST_RTC_INFO;

typedef struct st_elite_header_info
{
	uint16_t note_identifier;
	uint8_t note_number;
	uint8_t flash_erase_flag;
	uint16_t note_start_sector;
	uint32_t note_len;
	ST_RTC_INFO note_time;

} ST_ELITE_HEADER_INFO;

typedef struct st_note_header_info
{
	uint16_t note_identifier;
	uint16_t note_number;
	uint8_t flash_erase_flag;
	uint8_t note_head_start;
	uint16_t note_start_sector;
	uint32_t note_len;
	ST_RTC_INFO note_time;

} ST_NOTE_HEADER_INFO;

typedef struct st_t9_note_header_info
{
	uint16_t note_identifier;
	uint32_t note_number;
	uint8_t flash_erase_flag;
	uint8_t note_head_start;
	uint16_t note_start_sector;
	uint32_t note_len;
	ST_RTC_INFO note_time;

} ST_T9_NOTE_HEADER_INFO;

//�ʼ�ͷ
typedef struct ST_KZ_NOTE_HEADER_INFO
{
	uint16_t note_identifier;
	uint16_t note_start_sector;
	uint32_t note_len;
	/****�������߱ʼǵĿ�Ŀ�����***/
	uint8_t note_current_subject;
	uint8_t note_current_topic;
	/****������ʼʱ����λ���������߱ʼ�����ʱ��***/
	ST_RTC_INFO rtc;
	uint16_t note_use_times;

} st_kz_note_header_info;

typedef struct st_note_number_info
{
	uint32_t note_number : 17;
	uint32_t unsigned_type : 6;
	uint32_t flash_erase_flag : 1;

} ST_NOTE_NUMBER_INFO;
//ҳ����Ϣ
typedef struct page_info
{
	uint8_t page_num;
	uint16_t note_num : 12;
	bool operator==(page_info &pageInfo) const
	{
		if (pageInfo.page_num == this->page_num
			&& pageInfo.note_num == this->note_num)
		{
			return true;
		}
		return false;
	}
}PAGE_INFO;
typedef struct oid_info
{
	uint32_t oid_x : 20;
	uint32_t oid_y : 20;
	uint16_t oid_angle : 15;
	uint16_t oid_angle_symbol : 1;//0Ϊ�� 1Ϊ��
	oid_info() :oid_x(0), oid_y(0) , oid_angle_symbol(0), oid_angle(0){}
}OID_INFO;
//oid3ҳ����Ϣ(X10����)
typedef struct oid_page_info
{
	float fX;
	float fY;
	float fAngle;
	oid_page_info():fX(0.0f),fY(0.0f),fAngle(0){}
}OID_PAGE_INFO;
// ��������Ϣ
typedef struct pen_info
{
	uint8_t nStatus;		// ��״̬
	uint16_t nX;			// ��x������
	uint16_t nY;			// ��y������
	uint16_t nPress;		// ��ѹ��
	bool operator==(pen_info &penInfo) const
	{
		if (penInfo.nX == this->nX
			&& penInfo.nY == this->nY
			&& penInfo.nPress == this->nPress
			&& penInfo.nStatus == this->nStatus)
		{
			return true;
		}
		return false;
	}
}PEN_INFO;  
//�ʼ�����
typedef struct pen_e3_info
{
	uint8_t  status;		// ��״̬
	uint32_t  x;			// ��x������
	uint32_t  y;			// ��y������
	uint16_t  press;		// ��ѹ��
	uint16_t  angle;		// �Ƕ�
}PEN_E3_INFO;
// �Ż���������Ϣ
typedef struct pen_infof
{
	uint8_t nStatus;		// ��״̬
	uint16_t nX;			// ��x������8
	uint16_t nY;			// ��y������
	float fWidth;			// �ʿ���
	float fSpeed;			// �ٶ�
}PEN_INFOF;  
//�豸��Ϣ
typedef struct usb_info
{
	char szDevPath[260];
	char szDevName[260];
	unsigned short nVendorNum;    
	unsigned short nProductNum;         
}USB_INFO;
//�豸��Ϣ
typedef struct device_info
{
	char szDevName[260];
	eDeviceType type;
}DEVICE_INFO;
//������Ϣ
typedef struct storage_info
{
	uint16_t total;
	uint16_t free;

}STORAGE_INFO;
//�ʼ�����
typedef struct position_packet
{
	uint8_t x_l;
	uint8_t x_h;
	uint8_t y_l;
	uint8_t y_h;
	uint8_t flag : 3;
	uint8_t press : 5;

}POSITION_PACKET;

//�ʼǰ�
typedef struct st_usb_e3_packet
{
	uint8_t  status;		// ��״̬
	uint8_t  x_l;		    // x��8λ
	uint8_t  x;		        // x��8λ
	uint8_t  x_h;		    // x��8λ
	uint8_t  y_l;		    // y��8λ
	uint8_t  y;		        // y��8λ
	uint8_t  y_h;		    // y��8λ
	uint8_t  press_l;		// ѹ��ֵ
	uint8_t  press_h;		// ѹ��ֵ
	uint8_t  angle_l;		// �Ƕ�
	uint8_t  angle_h;		// �Ƕ�

}ST_USB_E3_PACKET;

typedef struct hard_info
{
	uint16_t x_range;  //X���귶Χ
	uint16_t y_range;  //Y���귶Χ
	uint16_t lpi;		//�����ֱ���
	uint8_t page_num;	//ҳ��λ�� 16 or 24

}HARD_INFO;

//ҳ�봫������20��ֵ
typedef struct st_page_sensor
{
	uint16_t sensor1;
	uint16_t sensor2;
	uint16_t sensor3;
	uint16_t sensor4;
	uint16_t sensor5;
	uint16_t sensor6;
	uint16_t sensor7;
	uint16_t sensor8;
	uint16_t sensor9;
	uint16_t sensor10;
	uint16_t sensor11;
	uint16_t sensor12;
	uint16_t sensor13;
	uint16_t sensor14;
	uint16_t sensor15;
	uint16_t sensor16;
	uint16_t sensor17;
	uint16_t sensor18;
	uint16_t sensor19;
	uint16_t sensor20;
}ST_PAGE_SENSOR;

//ͨ���ţ�����ֵ��ADC
typedef struct st_test_firmware_info
{
	uint8_t num;
	uint8_t channel_gain;
	uint16_t adc_value; 
}ST_TEST_FIRMWARE_INFO;

#pragma pack()

enum eKeyPress
{
	CLICK			= 0x01,
	DBCLICK,
	PAGEUP,
	PAGEDOWN,
	CREATEPAGE,
	KEY_A			= 0x06,
	KEY_B,
	KEY_C,
	KEY_D,
	KEY_E,
	KEY_F,
	KEY_UP			= 0x10,
	KEY_DOWN,
	KEY_YES,			
	KEY_NO,
	KEY_CANCEL,
	KEY_OK,
	PAGEUPCLICK		= 0x20,
	PAGEUPDBCLICK,
	PAGEUPPRESS,
	PAGEDOWNCLICK,
	PAGEDOWNDBCLICK,
	PAGEDOWNPRESS,
	SELF1CLICK		= 0x26,
	SELF1DBCLICK,		
	SELF1PRESS,	
	SELF2CLICK,
	SELF2DBCLICK,		
	SELF2PRESS,	
};

enum eNebulaError
{
	ERROR_NONE,
	ERROR_FLOW_NUM,
	ERROR_FW_LEN,
	ERROR_FW_CHECKSUM,
	ERROR_STATUS,
	ERROR_VERSION,
	ERROR_NAME_CONTENT,
	ERROR_NO_NOTE,
};

enum eGatewayStatus
{
	NEBULA_STATUS_OFFLINE = 0,
	NEBULA_STATUS_STANDBY,
	NEBULA_STATUS_VOTE,
	NEBULA_STATUS_MASSDATA,
	NEBULA_STATUS_CONFIG,
	NEBULA_STATUS_DFU,
	NEBULA_STATUS_MULTI_VOTE,
	NEBULA_STATUS_VOTE_ANSWER,              
};

enum eNodeStatus
{
	DEVICE_POWER_OFF = 0,
	DEVICE_STANDBY,
	DEVICE_INIT_BTN,
	DEVICE_OFFLINE,
	DEVICE_ACTIVE,
	DEVICE_LOW_POWER_ACTIVE,
	DEVICE_OTA_MODE,//06
	DEVICE_OTA_WAIT_SWITCH,
	DEVICE_TRYING_POWER_OFF,
	DEVICE_FINISHED_PRODUCT_TEST,
	DEVICE_SYNC_MODE,
	DEVICE_DFU_MODE,
};

enum eNodeMode
{
	NODE_BLE = 0,
	NODE_2_4G,
	NODE_USB,
};

enum eRobotCmd
{
	ROBOT_GATEWAY_STATUS			= 0x00,		//��ȡ״̬
	ROBOT_NODE_STATUS,							//node״̬
	ROBOT_ENTER_VOTE,							//����ͶƱģʽ
	ROBOT_EXIT_VOTE,							//�˳�ͶƱģʽ
	ROBOT_EXIT_VOTE_MULIT,						//��ѡͶƱģʽ
	ROBOT_ENTER_BIG_DATA,						//���������ģʽ
	ROBOT_MASS_DATA,							//�������ϱ�
	ROBOT_EXIT_BIG_DATA,						//�˳�������ģʽ
	ROBOT_GATEWAY_ERROR,						//����
	ROBOT_NODE_MODE,							//�豸����ģʽ
	ROBOT_SET_DEVICE_NUM,						//�����豸�����
	ROBOT_ENTER_DFU,							//����dfuģʽ
	ROBOT_FIRMWARE_LEN,							//��ȡ�̼�����
	ROBOT_FIRMWARE_DATA,						//��ȡ�̼���Ϣ
	ROBOT_FIRMWARE_CHECK_SUM,					//��ȡУ���
	ROBOT_RAW_RESULT,							//У����
	ROBOT_GATEWAY_REBOOT,						//�豸����
	ROBOT_EXIT_DFU,								//�˳�dfuģʽ
	ROBOT_GATEWAY_VERSION,						//�豸�汾��
	ROBOT_ONLINE_STATUS,						//����״̬
	ROBOT_DEVICE_CHANGE,						//�豸�ı�
	ROBOT_DEVICE_CHANGED,						//�豸�ı�2
	ROBOT_NODE_INFO,							//�豸��Ϣ
	ROBOT_NODE_ERROR,							//node����
	ROBOT_ORIGINAL_PACKET,						//ԭʼ�ʼ����ݰ�
	ROBOT_SET_RTC,								//����RTC
	ROBOT_KEY_PRESS,							//��������
	ROBOT_SHOW_PAGE,							//��ʾҳ��
	ROBOT_ENTER_SYNC,							//����syncģʽ
	ROBOT_EXIT_SYNC,							//�˳�syncģʽ
	ROBOT_GET_SYNC_HEAD,						//��ȡ�洢�ʼǰ�ͷ
	ROBOT_SYNC_TRANS_BEGIN,						//�ʼǴ������ʼ
	ROBOT_SYNC_PACKET,							//�ϴ�����
	ROBOT_SYNC_TRANS_END,						//�ʼǴ����������
	ROBOT_VOTE_ANSWER,							//����ģʽ
	ROBOT_OPTIMIZE_PACKET,						//�Ż��ʼ�
	ROBOT_SET_ANALOG_VALUE,						//��������
	ROBOT_SET_CLASS_SSID,						//���ð༶ssid
	ROBOT_SET_CLASS_PWD,						//���ð༶password
	ROBOT_SET_STUDENT_ID,						//����ѧ��id
	ROBOT_SET_SECRET,							//����Secret
	ROBOT_UPDATE_SEARCH,						//������ѯ
	ROBOT_UPDATE_WIFI,							//����wifi
	ROBOT_MASS_MAC,								//�ϱ�mac��ַ
	ROBOT_LOG_OUTPUT,							//log���
	ROBOT_SWITCH_MODE,							//�л�ģʽ
	ROBOT_SET_BMP,								//����BMP
	ROBOT_DATA_PACKET,							//�ʼ����ݰ�
	ROBOT_ENTER_EMR_DFU,						//����dfuģʽ
	ROBOT_FIRMWARE_EMR_LEN,						//��ȡ�̼�����
	ROBOT_FIRMWARE_EMR_DATA,					//��ȡ�̼���Ϣ
	ROBOT_FIRMWARE_EMR_CHECK_SUM,				//��ȡУ���
	ROBOT_RAW_EMR_RESULT,						//У����
	ROBOT_GATEWAY_EMR_SWITCH,					//�豸����
	ROBOT_EXIT_EMR_DFU,							//�˳�dfuģʽ
	//////////////////////////Dongle/////////////////////////////
	ROBOT_DONGLE_STATUS,						//dongele״̬
	ROBOT_DONGLE_VERSION,						//dongle�汾
	ROBOT_DONGLE_SCAN_RES,						//ɨ����
	ROBOT_SET_NAME,								//��������
	ROBOT_SLAVE_ERROR,							//������Ϣ
	ROBOT_SLAVE_STATUS,							//slave״̬
	ROBOT_SLAVE_VERSION,						//slave�汾
	ROBOT_MODULE_VERSION,						//ģ��汾��
	ROBOT_ENTER_ADJUST_MODE,					//����ģ��У׼ģʽ
	ROBOT_MODULE_ADJUST_RESULT,					//ģ��У׼���
	ROBOT_GET_X8_MAC,							//��ȡmac��ַ
	ROBOT_DONGLE_BIND,							//��
	ROBOT_GET_DEVICE_ID,						//��ȡ�豸ΨһID
	ROBOT_VIRTUAL_KEY_PRESS,					//���ⰴ������
	ROBOT_ENTER_SYNC_RES,						//��ʼͬ�����߱ʼǽ��
	////////////////////////////////////////////////////////////
	ROBOT_SEARCH_MODE,							//��ѯģʽ
	ROBOT_PEN_TYPE,								//������
	ROBOT_SEARCH_STORAGE,						//��ѯ�豸����
	ROBOT_SET_MAC,								//����mac���
	ROBOT_BUTTON_ACTIVE,						//���ð�ť��Ч
	ROBOT_GET_PROPERTY,							//��ȡ�豸����
	ROBOT_SET_FEATURE,							//����������
	ROBOT_SET_ADJUST_VALUE,						//����У׼��λֵ
	ROBOT_GET_ADJUST_VALUE,						//��ȡУ׼��λֵ
	ROBOT_SHOW_OID_PAGE,						//��ʾOIDҳ��
	ROBOT_SET_MQTT_IP,							//����mqttIP
	ROBOT_GET_FREQ,                             //��ȡM5Ƶ��ֵ--------�������ṩ
	ROBOT_GET_E3W_MAC,
	ROBOT_X10_SET_OFFSET_VALUE,					//X10 ���ù̼���װƫ������
	ROBOT_SET_FB_MSG_RESULT,					//����FB �豸��Ϣ
	ROBOT_PAGE_SENSOR,							//ҳ�봫����
	ROBOT_PAPER_TYPE,							//ֽ������
	ROBOT_DEVICE_INFO,							//�豸��Ϣ
};


////////////////////////////DONGLE////////////////////////////////
#pragma pack(1)

typedef struct st_ble_device
{
	uint8_t num;
	uint8_t rssi;
	uint8_t match;
	uint8_t addr[6];
	uint8_t device_name[18];
	uint8_t device_type;
}ST_BLE_DEVICE;

#pragma pack()

//����״̬
enum eDongleStatus
{
	BLE_STANDBY				= 0,
	BLE_SCANNING			= 1,	//����ɨ��
	BLE_CONNECTING			= 2,	//������
	BLE_CONNECTED			= 3,	//���ӳɹ�
	BLE_ACTIVE_DISCONNECT	= 4,	//���ڶϿ�����
	BLE_RECONNECTING		= 5,	//��������
	BLE_LINK_BREAKOUT		= 6,	//��������������
	BLE_DFU_START			= 7,	//����dfuģʽ
};

enum eUpdateType
{
	DONGLE_BLE = 0,
	DONGLE_MCU,
	SLAVE_MCU,
	MODULE_MCU,
};

enum eSlaveError
{
	ERROR_SLAVE_NONE = 0,
	ERROR_OTA_FLOW_NUM,
	ERROR_OTA_LEN,
	ERROR_OTA_CHECKSUM,
	ERROR_OTA_STATUS,
	ERROR_OTA_VERSION,
	ERROR_SYNC_STATUS = 7,
};

enum eDeviceStatus
{
	DEVICE_IN	= 0,
	DEVICE_OUT,
};

enum eAdujstResult
{
	ADJUST_SUCCESSED = 0,
	ADJUST_FAILED,
	ADJUST_TIMEOUT,
};

enum eDeviceMode
{
	DEVICE_MOUSE = 0,
	DEVICE_HAND,
};

enum ePenType
{
	M2 = 1,
	M3K,
	M3,
};
//��״̬
enum ePenStatus
{
	PEN_LEAVE			= 0x00,		//�뿪
	PEN_SUSPEND			= 0x10,		//����
	PEN_WRITE			= 0x11,		//��д
	PEN_SIDE_SUSPEND	= 0x20,		//�����ѹ����
	PEN_SIDE_WRITE		= 0x21,		//�����ѹ��д
};

//ֽ������
enum ePaperType {
	eDefult = 0,
	eA4,	//A4ֽ
	eA5,	//A5ֽ
	eCustom, //�Զ���ֽ
};
#define WIDTH_T7P	22015
#define HEIGHT_T7P	15359

#define WIDTH_P1	17407
#define HEIGHT_P1	10751

#define WIDTH_A4	22600
#define HEIGHT_A4	16650

#define WIDTH_A5	14335
#define HEIGHT_A5	8191

#define WIDTH_X8	22100 //22500
#define HEIGHT_X8	14650 //14880

#define WIDTH_K7	22016
#define HEIGHT_K7	14787

#define WIDTH_K7_C5	20200
#define HEIGHT_K7_C5 14328

#define WIDTH_C5	10485
#define HEIGHT_C5	6327

#define WIDTH_W5E	21349
#define HEIGHT_W5E	13932

#define WIDTH_K8	21100
#define HEIGHT_K8	13500

#define WIDTH_A4_X9  29700 //28348
#define HEIGHT_A4_X9 21000 //20924

#define WIDTH_A4_T9WH  29700 //28348
#define HEIGHT_A4_T9WH 21000 //20924

#define WIDTH_T10	29758
#define HEIGHT_T10	18934

#define WIDTH_T9C_FB 22600
#define HEIGHT_T9C_FB 16650

#define WIDTH_K7W 20949
#define HEIGHT_K7W 13600

#define WIDTH_X10 28472
#define HEIGHT_X10 21661
