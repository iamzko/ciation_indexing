/*******************************************************************************
* ��Ȩ����(C) 2017 . All right reserved
* �ļ����� : EncodeWrap.h
* ˵    �� : �ַ������롢���롢���ܡ����ܽӿ�
* ��ǰ�汾 : 1.0.0.1
* ��    �� : hzq (412201568@qq.com)
* �������� : 2017-07-31
* �޸����� : 2017-07-31
* �� �� �� : hzq
********************************************************************************/

#ifndef EncodeWrap_h__
#define EncodeWrap_h__

#ifdef ENCODEWRAP_EXPORTS
#define ENCODEWRAP_API __declspec(dllexport)
#else
#define ENCODEWRAP_API __declspec(dllimport)
#endif

/*******************************************************************************
* �������� : Base64EncodeWrap
* �������� : base64����
* �Ρ����� : strInput  ����
* �Ρ����� : strOutput ����
* �Ρ����� : strErrMsg ������Ϣ
* �� �� ֵ : BOOL      �ɹ� TRUE; ʧ�� FALSE 
*******************************************************************************/
ENCODEWRAP_API BOOL Base64EncodeWrap(CString strInput, CString& strOutput, CString& strErrMsg);

/*******************************************************************************
* �������� : Base64DecodeWrap
* �������� : base64����
* �Ρ����� : strInput  ����
* �Ρ����� : strOutput ����
* �Ρ����� : strErrMsg ������Ϣ
* �� �� ֵ : BOOL      �ɹ� TRUE; ʧ�� FALSE 
*******************************************************************************/
ENCODEWRAP_API BOOL Base64DecodeWrap(CString strInput, CString& strOutput, CString& strErrMsg);

/*******************************************************************************
* �������� : DESEncryptWrap
* �������� : DES����
* �Ρ����� : strKey    ��Կ(8λ����)
* �Ρ����� : strInput  ����
* �Ρ����� : strOutput ����
* �Ρ����� : strErrMsg ������Ϣ
* �� �� ֵ : BOOL      �ɹ� TRUE; ʧ�� FALSE
*******************************************************************************/
ENCODEWRAP_API BOOL DESEncryptWrap(CString strKey, CString strInput, CString& strOutput, CString& strErrMsg);

/*******************************************************************************
* �������� : DESDecryptWrap
* �������� : DES����
* �Ρ����� : strKey    ��Կ(8λ����)
* �Ρ����� : strInput  ����
* �Ρ����� : strOutput ����
* �Ρ����� : strErrMsg ������Ϣ
* �� �� ֵ : BOOL      �ɹ� TRUE; ʧ�� FALSE
*******************************************************************************/
ENCODEWRAP_API BOOL DESDecryptWrap(CString strKey, CString strInput, CString& strOutput, CString& strErrMsg);

#endif // EncodeWrap_h__
