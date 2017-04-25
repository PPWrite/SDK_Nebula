#include <stdint.h>

#define NEBULA_VID		0x0483
#define P1_VID			0x0ED1

enum
{
	GATEWAY_PID	=	0x6001,
	T8A_PID		=	0x6002,
	T9A_PID		=	0x6003,
	DONGLE_PID  =	0x5001,
	P1_PID		=   0x7806,
};

enum eDeviceType
{
	GATEWAY = 0,
	NODE,
	DONGLE,
	P1,
	UNKNOWN,
};
////////////////////////////////////////NEBULA///////////////////////////////////////
#pragma pack(1)
//状态
typedef struct robot_status
{
	uint8_t	 device_status;
	uint8_t  battery_level;
	uint8_t  note_num;
}ROBOT_STATUS;
//报告
typedef struct robot_report
{
	uint8_t cmd_id;
	uint8_t reserved;
	uint8_t payload[60];
}ROBOT_REPORT;
//版本
typedef struct st_version
{
	uint8_t version;
	uint8_t version2;
	uint8_t version3;
	uint8_t version4;
}ST_VERSION;
//设备信息
typedef struct st_device_info
{
	ST_VERSION version;
	uint8_t  custom_num;
	uint8_t  class_num;
	uint8_t  device_num;
	uint8_t  mac[6];

}ST_DEVICE_INFO;

typedef struct st_option_packet
{
	uint8_t id;
	uint8_t option[6];

}ST_OPTION_PACKET;

typedef struct st_note_header_info
{
	uint16_t note_identifier;
	uint8_t note_number;
	uint8_t flash_erase_flag;
	uint16_t note_start_sector;
	uint32_t note_len;
	uint8_t note_time_year;
	uint8_t note_time_month;
	uint8_t note_time_day;
	uint8_t note_time_hour;
	uint8_t note_time_min;

} ST_NOTE_HEADER_INFO;

typedef struct st_note_plus_header_info
{
	uint16_t note_identifier;
	uint16_t note_number;
	uint8_t flash_erase_flag;
	uint8_t note_head_start;
	uint16_t note_start_sector;
	uint32_t note_len;
	uint8_t note_time_year;
	uint8_t note_time_month;
	uint8_t note_time_day;
	uint8_t note_time_hour;
	uint8_t note_time_min;

} ST_NOTE_PLUS_HEADER_INFO;

#pragma pack()

enum NEBULA_ERROR
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

enum GATEWAY_STATUS
{
	NEBULA_STATUS_OFFLINE = 0,
	NEBULA_STATUS_STANDBY,
	NEBULA_STATUS_VOTE,
	NEBULA_STATUS_MASSDATA,
	NEBULA_STATUS_CONFIG,
	NEBULA_STATUS_DFU,
	NEBULA_STATUS_MULTI_VOTE,
	NEBULA_STATUS_END,              
};

enum NODE_STATUS
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

enum ROBOT_NEBULA_TYPE
{
	ROBOT_GATEWAY_STATUS			= 0x00,		//获取状态
	ROBOT_ENTER_VOTE,							//进入投票模式
	ROBOT_EXIT_VOTE,							//退出投票模式
	ROBOT_EXIT_VOTE_MULIT,						//多选投票模式
	ROBOT_ENTER_BIG_DATA,						//进入大数据模式
	ROBOT_BIG_DATA_REPORT,						//大数据上报
	ROBOT_PAGE_NO,								//页码显示
	ROBOT_EXIT_BIG_DATA,						//退出大数据模式
	ROBOT_GATEWAY_ERROR,						//错误
	ROBOT_NODE_MODE,							//设备服务模式
	ROBOT_SET_DEVICE_NUM,						//设置设备网络号
	ROBOT_ENTER_DFU,							//进入dfu模式
	ROBOT_FIRMWARE_LEN,							//获取固件长度
	ROBOT_FIRMWARE_DATA,						//获取固件信息
	ROBOT_FIRMWARE_CHECK_SUM,					//获取校验和
	ROBOT_RAW_RESULT,							//校验结果
	ROBOT_GATEWAY_REBOOT,						//设备重启
	ROBOT_EXIT_DFU,								//退出dfu模式
	ROBOT_GATEWAY_VERSION,						//设备版本号
	ROBOT_ONLINE_STATUS,						//在线状态
	ROBOT_DEVICE_CHANGE,						//设备改变
	ROBOT_NODE_INFO,							//设备信息
	ROBOT_NODE_ERROR,							//node错误
	ROBOT_USB_PACKET,							//上传坐标
	ROBOT_SET_RTC,								//设置RTC
	ROBOT_KEY_PRESS,							//按键按下
	ROBOT_SHOW_PAGE,							//显示页码		
	ROBOT_ENTER_SYNC,							//进入sync模式
	ROBOT_EXIT_SYNC,							//退出sync模式
	ROBOT_GET_SYNC_HEAD,						//获取存储笔记包头
	ROBOT_SYNC_TRANS_BEGIN,						//笔记传输命令开始
	ROBOT_ORIGINAL_PACKET,						//原始笔记数据包
	ROBOT_SYNC_TRANS_END,						//笔记传输命令结束
};
// 笔数据信息
typedef struct sPenInfo
{
	uint8_t nStatus;		// 笔状态
	uint16_t nX;			// 笔x轴坐标
	uint16_t nY;			// 笔y轴坐标
	uint16_t nPress;		// 笔压力
}PEN_INFO;  
//设备信息
typedef struct usb_info
{
	char szDevName[260];
	unsigned short nVendorNum;    
	unsigned short nProductNum;         
}USB_INFO;

enum
{
	CLICK = 1,
	DBCLICK,
	PAGEUP,
	PAGEDOWN,
	CREATEPAGE,
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

//蓝牙状态
enum BLE_STATUS
{
	BLE_STANDBY				= 0,
	BLE_SCANNING			= 1,	//正在扫描
	BLE_CONNECTING			= 2,	//连接中
	BLE_CONNECTED			= 3,	//连接成功
	BLE_ACTIVE_DISCONNECT	= 4,	//正在断开链接
	BLE_RECONNECTING		= 5,	//重新连接
	BLE_LINK_BREAKOUT		= 6,	//蓝牙正在升级中
	BLE_DFU_START			= 7,	//蓝牙dfu模式
};

enum DONGLE_DEVICE
{
	P7			= 1,
	ELITE		= 2,
	ELITE_PLUS	= 3,
	J0			= 8,
};

enum ROBOT_DONGLE_TYPE
{
	ROBOT_DONGLE_STATUS			= 0x00,		//dongele状态
	ROBOT_DONGLE_VERSION,					//dongle版本
	ROBOT_DONGLE_SCAN_RES,					//扫描结果
	ROBOT_SET_NAME,							//设置名称
	ROBOT_SLAVE_ERROR,						//错误信息
	ROBOT_DONGLE_FIRMWARE_DATA,				//进度
	ROBOT_DONGLE_RAW_RESULT,				//升级结果
	ROBOT_SLAVE_STATUS,						//slave状态
	ROBOT_SLAVE_VERSION,					//slave版本
	ROBOT_DONGLE_PACKET,					//坐标数据
	ROBOT_SLAVE_SYNC_BEGIN,					//获取存储笔记包头
	ROBOT_SLAVE_SYNC_END,					//结束同步
};

enum UPDATE_TYPE
{
	DONGLE_BLE = 0,
	DONGLE_MCU,
	SLAVE_MCU,
};

enum SALVE_ERROR
{
	ERROR_SLAVE_NONE = 0,
	ERROR_OTA_FLOW_NUM,
	ERROR_OTA_LEN,
	ERROR_OTA_CHECKSUM,
	ERROR_OTA_STATUS,
	ERROR_OTA_VERSION,
};