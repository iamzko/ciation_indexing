/*******************************************************************************
* 版权所有(C) 2017 . All right reserved
* 文件名称 : TaskAidWrap.h
* 说    明 : 任务处理通用接口
* 当前版本 : 1.0.0.1
* 作    者 : hzq (412201568@qq.com)
* 创建日期 : 2017-07-31
* 修改日期 : 2017-12-05
* 修 改 人 : hzq
********************************************************************************/

#ifndef TaskAidWrap_h__
#define TaskAidWrap_h__

#ifdef TASKAIDWRAP_EXPORTS
#define TASKAIDWRAP_API __declspec(dllexport)
#else
#define TASKAIDWRAP_API __declspec(dllimport)
#endif

///////////////////////////////////////////////////通过任务路径加载任务提交任务接口///////////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* 函数名称 : LoadTaskWrap
* 功能描述 : 加载任务(UNICODE VS2010)
* 参　　数 : strIniPath   任务路径
* 参　　数 : nKey         键值
* 参　　数 : strTaskJson  任务json
* 参　　数 : strErrMsg    错误信息
* 返 回 值 : int          错误码：-1 任务加载失败；0 无任务；1 正常返回任务
*******************************************************************************/
TASKAIDWRAP_API int LoadTaskWrap(CString strIniPath, int& nKey, CString& strTaskJson, CString& strErrMsg);

/*******************************************************************************
* 函数名称 : LoadTaskWrapA
* 功能描述 : 加载任务(ANSI VC6.0)
* 参　　数 : pIniPath   任务路径
* 参　　数 : nKey       键值
* 参　　数 : pTaskJson  任务json
* 参　　数 : pErrMsg    错误信息
* 返 回 值 : int          错误码：-1 任务加载失败；0 无任务；1 正常返回任务
*******************************************************************************/
TASKAIDWRAP_API int LoadTaskWrapA(const char* pIniPath, int& nKey, char* pTaskJson, char* pErrMsg);

/*******************************************************************************
* 函数名称 : FinishTaskWrap
* 功能描述 : 完成任务(UNICODE VS2010)
* 参　　数 : strIniPath 任务路径
* 参　　数 : nKey       键值
* 参　　数 : nTaskState 任务状态：2 完成；7 不可做；8 存疑； 9 延迟
* 参　　数 : strErrMsg  错误信息
* 参　　数 : strZZSM    制作说明
* 参　　数 : strReason  备注信息
* 返 回 值 : BOOL       成功 TURE; 失败 FALSE
*******************************************************************************/
TASKAIDWRAP_API BOOL FinishTaskWrap(CString strIniPath, int nKey, int nTaskState, CString& strErrMsg, CString strZZSM = _T(""), CString strReason = _T(""));

/*******************************************************************************
* 函数名称 : FinishTaskWrapA
* 功能描述 : 完成任务(ANSI VC6.0)
* 参　　数 : pIniPath   任务路径
* 参　　数 : nKey       键值
* 参　　数 : nTaskState 任务状态：2 完成；7 不可做；8 存疑； 9 延迟
* 参　　数 : pErrMsg    错误信息
* 参　　数 : pZZSM      制作说明
* 参　　数 : pReason    备注信息
* 返 回 值 : BOOL       成功 TURE; 失败 FALSE
*******************************************************************************/
TASKAIDWRAP_API BOOL FinishTaskWrapA(const char* pIniPath, int nKey, int nTaskState, char* pErrMsg, const char* pZZSM = "", const char* pReason = "");


///////////////////////////////////////////////////通过注册表加载任务提交任务接口///////////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* 函数名称 : LoadTaskWrapEx
* 功能描述 : 加载任务(UNICODE VS2010)
* 参　　数 : nKey         键值
* 参　　数 : strTaskJson  任务json
* 参　　数 : strErrMsg    错误信息
* 返 回 值 : int          错误码：-1 任务加载失败；0 无任务；1 正常返回任务
*******************************************************************************/
TASKAIDWRAP_API int LoadTaskWrapEx(int& nKey, CString& strTaskJson, CString& strErrMsg);

/*******************************************************************************
* 函数名称 : LoadTaskWrapExA
* 功能描述 : 加载任务(ANSI VC6.0)
* 参　　数 : nKey       键值
* 参　　数 : pTaskJson  任务json
* 参　　数 : pErrMsg    错误信息
* 返 回 值 : int          错误码：-1 任务加载失败；0 无任务；1 正常返回任务
*******************************************************************************/
TASKAIDWRAP_API int LoadTaskWrapExA(int& nKey, char* pTaskJson, char* pErrMsg);

/*******************************************************************************
* 函数名称 : FinishTaskWrapEx
* 功能描述 : 完成任务(UNICODE VS2010)
* 参　　数 : nKey       键值
* 参　　数 : nTaskState 任务状态：2 完成；7 不可做；8 存疑； 9 延迟
* 参　　数 : strErrMsg  错误信息
* 参　　数 : strZZSM    制作说明
* 参　　数 : strReason  备注信息
* 返 回 值 : BOOL       成功 TURE; 失败 FALSE
*******************************************************************************/
TASKAIDWRAP_API BOOL FinishTaskWrapEx(int nKey, int nTaskState, CString& strErrMsg, CString strZZSM = _T(""), CString strReason = _T(""));

/*******************************************************************************
* 函数名称 : FinishTaskWrapExA
* 功能描述 : 完成任务(ANSI VC6.0)
* 参　　数 : nKey       键值
* 参　　数 : nTaskState 任务状态：2 完成；7 不可做；8 存疑； 9 延迟
* 参　　数 : pErrMsg    错误信息
* 参　　数 : pZZSM      制作说明
* 参　　数 : pReason    备注信息
* 返 回 值 : BOOL       成功 TURE; 失败 FALSE
*******************************************************************************/
TASKAIDWRAP_API BOOL FinishTaskWrapExA(int nKey, int nTaskState, char* pErrMsg, const char* pZZSM = "", const char* pReason = "");

/*******************************************************************************
* 函数名称 : GetAllTaskJsonWrapEx
* 功能描述 : 获取所有任务(UNICODE VS2010)
* 参　　数 : strAllTaskJson 任务json信息
* 参　　数 : strErrMsg      错误信息
* 返 回 值 : int            -1 任务加载失败；0 无任务；1 正常返回任务
*******************************************************************************/
TASKAIDWRAP_API int GetAllTaskJsonWrapEx(CString& strAllTaskJson, CString& strErrMsg);

/*******************************************************************************
* 函数名称 : GetAllTaskJsonWrapExA
* 功能描述 : 获取所有任务(ANSI VC6.0)
* 参　　数 : pAllTaskJson 任务json信息
* 参　　数 : pErrMsg      错误信息
* 返 回 值 : int            -1 任务加载失败；0 无任务；1 正常返回任务
*******************************************************************************/
TASKAIDWRAP_API int GetAllTaskJsonWrapExA(char* pAllTaskJson, char* pErrMsg);

/*******************************************************************************
* 函数名称 : StopTaskWrap
* 功能描述 : 暂停任务(UNICODE VS2010)
* 参　　数 : nKey       键值
* 参　　数 : strErrMsg  错误信息
* 返 回 值 : BOOL       成功 TURE; 失败 FALSE
*******************************************************************************/
TASKAIDWRAP_API BOOL StopTaskWrap(int nKey, CString& strErrMsg);

/*******************************************************************************
* 函数名称 : StopTaskWrapA
* 功能描述 : 暂停任务(ANSI VC6.0)
* 参　　数 : nKey       键值
* 参　　数 : strErrMsg  错误信息
* 返 回 值 : BOOL       成功 TURE; 失败 FALSE
*******************************************************************************/
TASKAIDWRAP_API BOOL StopTaskWrapA(int nKey, char* pErrMsg);

#endif // TaskAidWrap_h__
