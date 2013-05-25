#ifndef REQUEST_GLOBAL_H
#define REQUEST_GLOBAL_H

/** @file request_global.h
 * @defgroup Request_Library 公安实战平台服务端的REST接口
 *
 * 本模块封装了公安实战平台服务端的REST接口，其中包含两种发送请求的方法，一种是使
 * 用Qt的QNetworkRequest类来发送请求，另一种是使用系统底层Socket发送请求。
 * 两种方式都对应一个请求类的基类，分别是SingleRequest和RestRequest。\n
 *
 * SingleRequest会以异步的方式来发送请求。但是正因为发送请求是异步的，所以很
 * 难对其进行封装，所以现在基本已经不再使用，而是使用同步的方式发送请求。\n
 *
 * RestRequest本身并不发送请求，它只封装了请求的数据，例如：请求的参数、如果
 * 解析请求的结果等。具体的发送过程在RequestManager中完成。\n
 *
 * 当前绝大多数的请求都已经从异步的方式迁移到了同步的方式，但还有个别的请求没有
 * 迁移，例如：获取图片数据的请求。\n
 *
 * @author 赵抒宏
 * @author 劳玲英
 * @author 宋伟民
 * @author 陈兴华
 * @author 黄琪锋
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
