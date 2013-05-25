#ifndef GET_REST_H
#define GET_REST_H

/** @file get_rest.h
*  @addtogroup Request_Library
*  @{
*/

#include <string>
#include "NetCommon.h"

///发送REST请求的类
/** @class sky_rest
 *
 */
class sky_rest
{
private:
    static bool parse_url(const std::string url, std::string& host, short& port, std::string& path);
    static int connect_to_server(const std::string host, const short port, long connect_time_out);
    static int send_request(int s, const std::string path, const std::string token, const std::string host, const short port);
    static int send_post_request(int s, const std::string path, const std::string data, const std::string token, const std::string host, const short port);
    static int get_response(int s, std::string& result);
    static int get_response_body(const std::string response, std::string& body);
    static int setTransMode(int s, int mode);
public:
    ///发送GET请求
    /**
     * @param url 请求的URL
     * @param body 请求返回的内容
     * @param connect_time_out 请求的超时时间，以秒为单位
     * @param token 请求的token
     * @return: 返回0表示请求发送成功，其他则表示失败。
     */
    static int get_rest(const std::string url, std::string& body, long connect_time_out = 1, const std::string token = "");
    ///发送POST请求
    /**
     * @param url 请求的URL
     * @param data 请求体的内容
     * @param body 请求返回的内容
     * @param connect_time_out 请求的超时时间，以秒为单位
     * @param token 请求的token
     * @return: 返回0表示请求发送成功，其他则表示失败。
     */
    static int post_rest(const std::string url, const std::string data, std::string& body, long connect_time_out = 1, const std::string token = "");
};

/**
*  @}
*/

#endif //#ifndef GET_REST_H
