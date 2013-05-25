#ifndef SOCKET_CMD_H
#define SOCKET_CMD_H

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

#endif // SOCKET_CMD_H
