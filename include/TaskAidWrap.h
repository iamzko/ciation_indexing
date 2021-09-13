/*******************************************************************************
* ��Ȩ����(C) 2017 . All right reserved
* �ļ����� : TaskAidWrap.h
* ˵    �� : ������ͨ�ýӿ�
* ��ǰ�汾 : 1.0.0.1
* ��    �� : hzq (412201568@qq.com)
* �������� : 2017-07-31
* �޸����� : 2017-12-05
* �� �� �� : hzq
********************************************************************************/

#ifndef TaskAidWrap_h__
#define TaskAidWrap_h__

#ifdef TASKAIDWRAP_EXPORTS
#define TASKAIDWRAP_API __declspec(dllexport)
#else
#define TASKAIDWRAP_API __declspec(dllimport)
#endif

///////////////////////////////////////////////////ͨ������·�����������ύ����ӿ�///////////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* �������� : LoadTaskWrap
* �������� : ��������(UNICODE VS2010)
* �Ρ����� : strIniPath   ����·��
* �Ρ����� : nKey         ��ֵ
* �Ρ����� : strTaskJson  ����json
* �Ρ����� : strErrMsg    ������Ϣ
* �� �� ֵ : int          �����룺-1 �������ʧ�ܣ�0 ������1 ������������
*******************************************************************************/
TASKAIDWRAP_API int LoadTaskWrap(CString strIniPath, int& nKey, CString& strTaskJson, CString& strErrMsg);

/*******************************************************************************
* �������� : LoadTaskWrapA
* �������� : ��������(ANSI VC6.0)
* �Ρ����� : pIniPath   ����·��
* �Ρ����� : nKey       ��ֵ
* �Ρ����� : pTaskJson  ����json
* �Ρ����� : pErrMsg    ������Ϣ
* �� �� ֵ : int          �����룺-1 �������ʧ�ܣ�0 ������1 ������������
*******************************************************************************/
TASKAIDWRAP_API int LoadTaskWrapA(const char* pIniPath, int& nKey, char* pTaskJson, char* pErrMsg);

/*******************************************************************************
* �������� : FinishTaskWrap
* �������� : �������(UNICODE VS2010)
* �Ρ����� : strIniPath ����·��
* �Ρ����� : nKey       ��ֵ
* �Ρ����� : nTaskState ����״̬��2 ��ɣ�7 ��������8 ���ɣ� 9 �ӳ�
* �Ρ����� : strErrMsg  ������Ϣ
* �Ρ����� : strZZSM    ����˵��
* �Ρ����� : strReason  ��ע��Ϣ
* �� �� ֵ : BOOL       �ɹ� TURE; ʧ�� FALSE
*******************************************************************************/
TASKAIDWRAP_API BOOL FinishTaskWrap(CString strIniPath, int nKey, int nTaskState, CString& strErrMsg, CString strZZSM = _T(""), CString strReason = _T(""));

/*******************************************************************************
* �������� : FinishTaskWrapA
* �������� : �������(ANSI VC6.0)
* �Ρ����� : pIniPath   ����·��
* �Ρ����� : nKey       ��ֵ
* �Ρ����� : nTaskState ����״̬��2 ��ɣ�7 ��������8 ���ɣ� 9 �ӳ�
* �Ρ����� : pErrMsg    ������Ϣ
* �Ρ����� : pZZSM      ����˵��
* �Ρ����� : pReason    ��ע��Ϣ
* �� �� ֵ : BOOL       �ɹ� TURE; ʧ�� FALSE
*******************************************************************************/
TASKAIDWRAP_API BOOL FinishTaskWrapA(const char* pIniPath, int nKey, int nTaskState, char* pErrMsg, const char* pZZSM = "", const char* pReason = "");


///////////////////////////////////////////////////ͨ��ע�����������ύ����ӿ�///////////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* �������� : LoadTaskWrapEx
* �������� : ��������(UNICODE VS2010)
* �Ρ����� : nKey         ��ֵ
* �Ρ����� : strTaskJson  ����json
* �Ρ����� : strErrMsg    ������Ϣ
* �� �� ֵ : int          �����룺-1 �������ʧ�ܣ�0 ������1 ������������
*******************************************************************************/
TASKAIDWRAP_API int LoadTaskWrapEx(int& nKey, CString& strTaskJson, CString& strErrMsg);

/*******************************************************************************
* �������� : LoadTaskWrapExA
* �������� : ��������(ANSI VC6.0)
* �Ρ����� : nKey       ��ֵ
* �Ρ����� : pTaskJson  ����json
* �Ρ����� : pErrMsg    ������Ϣ
* �� �� ֵ : int          �����룺-1 �������ʧ�ܣ�0 ������1 ������������
*******************************************************************************/
TASKAIDWRAP_API int LoadTaskWrapExA(int& nKey, char* pTaskJson, char* pErrMsg);

/*******************************************************************************
* �������� : FinishTaskWrapEx
* �������� : �������(UNICODE VS2010)
* �Ρ����� : nKey       ��ֵ
* �Ρ����� : nTaskState ����״̬��2 ��ɣ�7 ��������8 ���ɣ� 9 �ӳ�
* �Ρ����� : strErrMsg  ������Ϣ
* �Ρ����� : strZZSM    ����˵��
* �Ρ����� : strReason  ��ע��Ϣ
* �� �� ֵ : BOOL       �ɹ� TURE; ʧ�� FALSE
*******************************************************************************/
TASKAIDWRAP_API BOOL FinishTaskWrapEx(int nKey, int nTaskState, CString& strErrMsg, CString strZZSM = _T(""), CString strReason = _T(""));

/*******************************************************************************
* �������� : FinishTaskWrapExA
* �������� : �������(ANSI VC6.0)
* �Ρ����� : nKey       ��ֵ
* �Ρ����� : nTaskState ����״̬��2 ��ɣ�7 ��������8 ���ɣ� 9 �ӳ�
* �Ρ����� : pErrMsg    ������Ϣ
* �Ρ����� : pZZSM      ����˵��
* �Ρ����� : pReason    ��ע��Ϣ
* �� �� ֵ : BOOL       �ɹ� TURE; ʧ�� FALSE
*******************************************************************************/
TASKAIDWRAP_API BOOL FinishTaskWrapExA(int nKey, int nTaskState, char* pErrMsg, const char* pZZSM = "", const char* pReason = "");

/*******************************************************************************
* �������� : GetAllTaskJsonWrapEx
* �������� : ��ȡ��������(UNICODE VS2010)
* �Ρ����� : strAllTaskJson ����json��Ϣ
* �Ρ����� : strErrMsg      ������Ϣ
* �� �� ֵ : int            -1 �������ʧ�ܣ�0 ������1 ������������
*******************************************************************************/
TASKAIDWRAP_API int GetAllTaskJsonWrapEx(CString& strAllTaskJson, CString& strErrMsg);

/*******************************************************************************
* �������� : GetAllTaskJsonWrapExA
* �������� : ��ȡ��������(ANSI VC6.0)
* �Ρ����� : pAllTaskJson ����json��Ϣ
* �Ρ����� : pErrMsg      ������Ϣ
* �� �� ֵ : int            -1 �������ʧ�ܣ�0 ������1 ������������
*******************************************************************************/
TASKAIDWRAP_API int GetAllTaskJsonWrapExA(char* pAllTaskJson, char* pErrMsg);

/*******************************************************************************
* �������� : StopTaskWrap
* �������� : ��ͣ����(UNICODE VS2010)
* �Ρ����� : nKey       ��ֵ
* �Ρ����� : strErrMsg  ������Ϣ
* �� �� ֵ : BOOL       �ɹ� TURE; ʧ�� FALSE
*******************************************************************************/
TASKAIDWRAP_API BOOL StopTaskWrap(int nKey, CString& strErrMsg);

/*******************************************************************************
* �������� : StopTaskWrapA
* �������� : ��ͣ����(ANSI VC6.0)
* �Ρ����� : nKey       ��ֵ
* �Ρ����� : strErrMsg  ������Ϣ
* �� �� ֵ : BOOL       �ɹ� TURE; ʧ�� FALSE
*******************************************************************************/
TASKAIDWRAP_API BOOL StopTaskWrapA(int nKey, char* pErrMsg);

#endif // TaskAidWrap_h__
