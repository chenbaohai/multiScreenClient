
#ifndef CONST_H
#define CONST_H


//rtsp
#define RTSP_DEFAULT_HOST "192.168.202.142"
#define RTSP_DEFAULT_PORT "8554"


enum PLAYSTATE{STATE_IDLE = 0, STATE_PLAY};
enum STATUS{PGIS=0,REPLAY,PREVIEW,NONE};
enum PLAYWINDOWTYPE{GENERALPREVIEW=0,GENERALREPLAY,RTSPREPLAY};

enum NODETYPE
{
    NODE_ORGANIZTION = 0,
    NODE_MONITORGROUP = 1,
    NODE_DVR = 2,
    NODE_CHANNEL = 3,

    NODE_CHANNELPLAYING=4,
    NODE_ONLINES=4,
    NODE_OFFLINES=5,
    NODE_MYGROUP=6,
    NODE_SCHEDULE=7
};

enum PTZCmd {
    Iris_out=7,
    Iris_in=6,
    Focuse_out=9,
    Focuse_in=8,
    Zoom_out=11,
    Zoom_in=10,
    Up=12,
    UpRight=13,
    Right=14,
    DownRight=15,
    Down=16,
    DownLeft=17,
    Left=18,
    UpLeft=19,
    Auto,
    Lock=99};


#define SAFE_DELETE(p) {if(p) delete p; p = NULL;}


#define  ONLINE       "online"
#define  OFFLINE      "offline"
#define  ORGANIZATION "organization"
#define  MONITORPOINT   "monitorpoint"

#define LISTEN_PORT   5234   ////侦听端口

//--------所有请求返回的格式: {"result":num}  num:返回的结果值

#define INIT_REQUEST   0x0001   //初始化请求
#define INIT_RESPONSE   0x1001

#define IDENTIFY_REQUEST   0x0002   //识别请求
#define IDENTIFY_RESPONSE   0x1002

#define CONFIG_REQUEST   0x0003   //电视墙配置请求     JSON:[{"displayid":1,"row":0,"col":0},{"displayid":3,"row":0,"col":1},...]
#define CONFIG_RESPONSE   0x1003

#define ORGXML_REQUEST   0x0004   //组织机构请求
#define ORGXML_RESPONSE   0x1004

#define GROUPXML_REQUEST   0x0005   //组信息请求
#define GROUPXML_RESPONSE   0x1005

#define SPLITWINDOW_REQUEST   0x0006   //画面分割请求  JSON:[{"displayid":4,"number":9}]  (备注：支持多画面分割)
#define SPLITWINDOW_RESPONSE   0x1006

#define PREVIEW_REQUEST   0x0007   //小窗口预览请求    JSON:{"displayid":3,"dvrid":2563525,"channelid":234234,"smallwindow":2}
#define PREVIEW_RESPONSE   0x1007                      //参数说明：  显示器id           通道id                   几号窗口预览

#define TOKEN_REQUEST   0x0008
#define TOKEN_RESPONSE  0x1008

#define STOPPREVIEW_REQUEST   0x0009   //停止预览请求 JSON:{"displayid":6,"smallwindow":2}
#define STOPPREVIEW_RESPONSE   0x1009

#define EXIT_REQUEST   0x000A   //退出请求 JSON:[{"displayid":6}] (备注：支持多个分屏退出) ->JSON:[] 停止所有视频
#define EXIT_RESPONSE   0x100A

#define STRETCH_REQUEST   0x000B   //拼接拆分  JSON:[{"displayid":4,"displayids":"1,2,3,4"},{"displayid":5,"displayids":"5"},{"displayid":6,"displayids":"6,7,8"}]
#define STRETCH_RESPONSE   0x100B

#define SCHEDULEXML_REQUEST   0x000C  //轮巡方案XML (新增、删除、修改)
#define SCHEDULEXML_RESPONSE   0x100C

#define STARTCIRCULATE_REQUEST   0x000D   //开始轮巡请求 JSON:{"displayid":6,"schedulename","方案一"}
#define STARTCIRCULATE_RESPONSE   0x100D

#define STOPCIRCULATE_REQUEST   0x000E   //停止轮巡请求 JSON:[{"displayid":6},{"displayid":1}] (备注：支持停止多个分屏轮巡)
#define STOPCIRCULATE_RESPONSE   0x100E                         //->JSON:[] 停止所有轮巡

#define SCHEDULE_REQUEST   0x000F  //轮巡方案XML (新增、删除、修改)
#define SCHEDULE_RESPONSE   0x100F

#define VISIONLAYOUT_REQUEST   0x0011  //VISION窗口数
#define VISIONLAYOUT_RESPONSE   0x1011          //返回值：[{"displayid":4,"layout":4},{"displayid":5,"layout":9}]

#define FULLPREVIEW_REQUEST   0x0012   //全屏预览请求 JSON:{"displayid":1,"smallwindow":2,"fullpreview":1}   fullpreview 1:全屏 0:恢复
#define FULLPREVIEW_RESPONSE   0x1012
#endif // CONST_H

