#ifndef REQUEST_GLOBAL_H
#define REQUEST_GLOBAL_H

/** @file request_global.h
 * @defgroup Request_Library ����ʵսƽ̨����˵�REST�ӿ�
 *
 * ��ģ���װ�˹���ʵսƽ̨����˵�REST�ӿڣ����а������ַ�������ķ�����һ����ʹ
 * ��Qt��QNetworkRequest��������������һ����ʹ��ϵͳ�ײ�Socket��������
 * ���ַ�ʽ����Ӧһ��������Ļ��࣬�ֱ���SingleRequest��RestRequest��\n
 *
 * SingleRequest�����첽�ķ�ʽ���������󡣵�������Ϊ�����������첽�ģ����Ժ�
 * �Ѷ�����з�װ���������ڻ����Ѿ�����ʹ�ã�����ʹ��ͬ���ķ�ʽ��������\n
 *
 * RestRequest����������������ֻ��װ����������ݣ����磺����Ĳ��������
 * ��������Ľ���ȡ�����ķ��͹�����RequestManager����ɡ�\n
 *
 * ��ǰ��������������Ѿ����첽�ķ�ʽǨ�Ƶ���ͬ���ķ�ʽ�������и��������û��
 * Ǩ�ƣ����磺��ȡͼƬ���ݵ�����\n
 *
 * @author �����
 * @author ����Ӣ
 * @author ��ΰ��
 * @author ���˻�
 * @author ������
 *
 * @see RequestManager
 * @see RestRequest
 * @see sky_rest
 * @see SingleRequest
 * @{
 */

#if defined(UNIT_TEST)
# define REQUEST_EXPORT
#else
# if defined(REQUEST_LIB)
#  define REQUEST_EXPORT Q_DECL_EXPORT
# else
#  define REQUEST_EXPORT Q_DECL_IMPORT
# endif
#endif

/**
*  @}
*/

#endif // ENTITY_GLOBAL_H
