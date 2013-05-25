#ifndef REQUEST_CONST_H
#define REQUEST_CONST_H

/** @file request_const.h
*  @addtogroup Request_Library
*  @{
*/

#define LOGIN_REQUEST "sessionService/login"
#define LOGOUT_REQUEST "sessionService/logout"
#define GET_SERVICE_INFO "sessionService/getServerInfo"
#define DICT_REQUEST "dictService/loadAll"
#define GET_USER_REQUEST "partyService/getUser"
#define GET_ORG_REQUEST "partyService/getOrg"
#define GET_USER_ORG_REQUEST "partyService/getUserOrg"
#define GET_ORG_TREE_REQUEST "partyService/getOrgTree"
#define GET_POST_ORG_REQUEST "partyService/getPostOrg"
#define SEARCH_RESOURCE_REQUEST "resourceService/list"
#define GET_RESOURCE_REQUEST "resourceService/load"
#define GET_RELATED_PERSON_REQUEST "relatedPersonService/load"
#define GET_CASE_REQUEST "caseService/load"
#define SAVE_RESOURCE_REQUEST "resourceService/save"
#define DELETE_RESOURCE_REQUEST "resourceService/delete"
#define SEARCH_RELATED_PERSON_REQUEST "relatedPersonService/list"
#define SAVE_RELATED_PERSON_REQUEST "relatedPersonService/save"
#define DELETE_RELATED_PERSON_REQUEST "relatedPersonService/delete"
#define SEARCH_CASE_REQUEST "caseService/list"
#define SAVE_CASE_REQUEST "caseService/save"
#define DELETE_CASE_REQUEST "caseService/delete"
#define CASE_ASSOCIATE_RESOURCE_REQUEST "caseService/relateOrReleaseResources"
#define FULLTEXT_SEARCH_REQUEST "searchService/search"
#define SMART_SEARCH_REQUEST    "searchService/smartSearch"
#define DELETE_MONITOR_POINT_REQUEST "monitorService/delete"
#define DELETE_MONITOR_GROUP_REQUEST "monitorGroupService/delete"
#define SAVE_MONITOR_POINT_REQUEST "monitorService/save"
#define SAVE_MONITOR_GROUP_REQUEST "monitorGroupService/save"
#define SEARCH_MONITOR_POINT_REQUEST "monitorService/findMonitorsWithOrg"
#define SEARCH_MONITOR_GROUP_REQUEST "monitorGroupService/findMonitorGroupsWithOrg"
#define IMPORT_VIDEO_REQUEST    "jobService/addVideoImport"
#define ENCODE_VIDEO_REQUEST    "jobService/addVideoDecode"
#define ANALYSE_VIDEO_REQUEST   "jobService/addVideoAnalyse"
#define SEARCH_MYJOBS_REQUEST   "jobService/getMyJobs"
#define SEARCH_ORGJOBS_REQUEST   "jobService/getSystemJobs"
#define SAVE_VIDEO_INFO_REQUEST "resourceService/saveVideoInfo"
#define UPLOAD_RESOURCE_REQUEST "transService/upload"
#define GET_MONITORPHOTO_REQUEST "monitor/getPhoto"

#define SEARCH_PLAY_LOGICAL_REQUEST "monitorService/getPlayParams"
#define SEARCH_VIDEO_FILE_REQUEST "monitorService/findVideos"
#define SEARCH_MONITOR_RESOURCE "monitorService/getRelatedResource"
#define GET_PHOTO_MARK_REQUEST "resourceService/getMark"
#define SAVE_PHOTO_MARK_REQUEST "resourceService/savePhotoMark"
#define APPEND_ASSOCIATED_PHOTO_REQUEST "resourceService/appendAssociatedPhoto"
#define GET_ONE_MARK_OF_VIDEO_REQUEST "resourceService/getOneMarkOfVideo"
#define SAVE_VIDEO_PHOTO_MARK_REQUEST "resourceService/updateVideoMark"
#define SAVE_VIDEO_PHOTO_MARK_DETAIL_REQUEST "resourceService/updateVideoMarkDetail"
#define GET_VIDEO_MARK    "resourceService/getVideoMarks"
#define CREATE_VIDEO_MARK "resourceService/createVideoMark"
#define GRT_PHOTO_OF_VIDEO  "resourceService/getPhotoOfVideo"

//监控组和监控点 请求
#define  MONITOR_GROUP_ORGNIZATION  "organizations"
#define  MONITOR_GROUP_MONITORS     "monitors"
#define  MONITOR_GROUP_MYGROUP      "myGroups"
#define  MONITOR_GROUPS             "groups"
#define  MONITOR_VIDEOS             "videos"

#define DELETE_JOB_REQUEST "jobService/deleteJobs"
#define RESTART_JOB_REQUEST "jobService/restartJobs"
#define STOP_JOB_REQUEST "jobService/stopJobs"

#define ERROR_NO_INPUT "no input"
#define ERROR_NO_REQUEST "no request"
#define ERROR_SEND_REQUEST "send http request error"
#define ERROR_PARSE_XML "xml parse error"

/**
*  @}
*/

#endif // REQUEST_CONST_H
