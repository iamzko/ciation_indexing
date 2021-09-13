/*******************************************************************************
* 版权所有(C) 2017 . All right reserved
* 文件名称 : EncodeWrap.h
* 说    明 : 字符串编码、解码、加密、解密接口
* 当前版本 : 1.0.0.1
* 作    者 : hzq (412201568@qq.com)
* 创建日期 : 2017-07-31
* 修改日期 : 2017-07-31
* 修 改 人 : hzq
********************************************************************************/

#ifndef EncodeWrap_h__
#define EncodeWrap_h__

#ifdef ENCODEWRAP_EXPORTS
#define ENCODEWRAP_API __declspec(dllexport)
#else
#define ENCODEWRAP_API __declspec(dllimport)
#endif

/*******************************************************************************
* 函数名称 : Base64EncodeWrap
* 功能描述 : base64编码
* 参　　数 : strInput  明文
* 参　　数 : strOutput 密文
* 参　　数 : strErrMsg 错误信息
* 返 回 值 : BOOL      成功 TRUE; 失败 FALSE 
*******************************************************************************/
ENCODEWRAP_API BOOL Base64EncodeWrap(CString strInput, CString& strOutput, CString& strErrMsg);

/*******************************************************************************
* 函数名称 : Base64DecodeWrap
* 功能描述 : base64解码
* 参　　数 : strInput  密文
* 参　　数 : strOutput 明文
* 参　　数 : strErrMsg 错误信息
* 返 回 值 : BOOL      成功 TRUE; 失败 FALSE 
*******************************************************************************/
ENCODEWRAP_API BOOL Base64DecodeWrap(CString strInput, CString& strOutput, CString& strErrMsg);

/*******************************************************************************
* 函数名称 : DESEncryptWrap
* 功能描述 : DES加密
* 参　　数 : strKey    秘钥(8位密码)
* 参　　数 : strInput  明文
* 参　　数 : strOutput 密文
* 参　　数 : strErrMsg 错误信息
* 返 回 值 : BOOL      成功 TRUE; 失败 FALSE
*******************************************************************************/
ENCODEWRAP_API BOOL DESEncryptWrap(CString strKey, CString strInput, CString& strOutput, CString& strErrMsg);

/*******************************************************************************
* 函数名称 : DESDecryptWrap
* 功能描述 : DES解密
* 参　　数 : strKey    秘钥(8位密码)
* 参　　数 : strInput  密文
* 参　　数 : strOutput 明文
* 参　　数 : strErrMsg 错误信息
* 返 回 值 : BOOL      成功 TRUE; 失败 FALSE
*******************************************************************************/
ENCODEWRAP_API BOOL DESDecryptWrap(CString strKey, CString strInput, CString& strOutput, CString& strErrMsg);

#endif // EncodeWrap_h__
