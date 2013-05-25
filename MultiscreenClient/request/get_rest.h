#ifndef GET_REST_H
#define GET_REST_H

/** @file get_rest.h
*  @addtogroup Request_Library
*  @{
*/

#include <string>
#include "NetCommon.h"

///����REST�������
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
    ///����GET����
    /**
     * @param url �����URL
     * @param body ���󷵻ص�����
     * @param connect_time_out ����ĳ�ʱʱ�䣬����Ϊ��λ
     * @param token �����token
     * @return: ����0��ʾ�����ͳɹ����������ʾʧ�ܡ�
     */
    static int get_rest(const std::string url, std::string& body, long connect_time_out = 1, const std::string token = "");
    ///����POST����
    /**
     * @param url �����URL
     * @param data �����������
     * @param body ���󷵻ص�����
     * @param connect_time_out ����ĳ�ʱʱ�䣬����Ϊ��λ
     * @param token �����token
     * @return: ����0��ʾ�����ͳɹ����������ʾʧ�ܡ�
     */
    static int post_rest(const std::string url, const std::string data, std::string& body, long connect_time_out = 1, const std::string token = "");
};

/**
*  @}
*/

#endif //#ifndef GET_REST_H
