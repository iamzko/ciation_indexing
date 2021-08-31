#ifndef MYTASKMODULE_H
#define MYTASKMODULE_H

#include "TaskAidWrap.h"
#include <QMap>
#include <QObject>
#include <QSharedPointer>
#include <QString>
#define TASK_BUFF_SIZE 4096
#define TASK_ERROR_SIZE 1024

class MyTaskModule : public QObject {
    Q_OBJECT
public:
    explicit MyTaskModule(QObject* parent = nullptr);
    QString get_article_code() const; //文章编号
    QString get_code() const; //编号
    QString get_del_path() const; //
    unsigned int get_delay_times() const; //滞后时间
    QString get_down_time() const; //领取时间
    QString get_finish_time() const; //完成时间
    unsigned int get_key_name() const; //任务编码
    unsigned int get_line_id() const; //生产线编码
    unsigned int get_post_id() const; //岗位编码
    QString get_post_name() const; //岗位名称
    QString get_proc_type() const; //制作类型
    QString get_product_code() const; //产品编号
    QString get_reason() const; //原因（备注）
    QString get_start_time() const; //开始时间
    QString get_stop_time() const; //停止时间
    unsigned int get_submit_count() const; //提交次数
    QString get_task_code() const; //任务编号
    QString get_task_come_time() const; //到岗时间
    QString get_task_kind() const; //任务类型
    unsigned int get_task_level() const; //任务等级
    unsigned int get_task_status() const; //任务状态
    unsigned int get_task_weight() const; //任务权重
    unsigned int get_tip_count() const;
    QString get_upload_path() const; //上传路径
    QString get_work_path() const; //工作路径
    QString get_worker() const; //员工名字
    QString get_production_instruction() const; //制作说明
    QString get_emergency() const; //紧急情况
    QString get_production_method() const; //制作方式

    bool load_new_task();
    bool finish_cur_task(int task_status, QString production_instruction, QString reason);

    bool is_error() const;

    QString get_error_string() const;
    const QMap<QString, QMap<QString, QString>>& get_all_task_info() const;
public slots:
    void refresh_all_task_info();

private:
    /**********************************************************************
     * 函数名称：load_single_task
     * 功能描述：从task.ini文件中读取任务
     * 参数：key   任务索引值
     * 参数：task_content  任务内容键值map
     * 参数：error 错误信息
     * 返回值：int  -1：加载失败；0：无任务；1：正常返回
     * *******************************************************************/
    int load_single_task(int& key, QMap<QString, QString>& task_content, QString& error);
    /*******************************************************************************
    * 函数名称 : load_all_task
    * 功能描述 : 从task.ini获取所有任务
    * 参　　数 : task_content 所有任务的键值map
    * 参数：error  错误信息
    * 返 回 值 : int -1：加载失败；0：无任务；1：正常返回
    *******************************************************************************/
    int load_all_task(QMap<QString, QMap<QString, QString>>& task_content, QString& error);
    /*********************************************************************
     * 函数名称：finish_task
     * 功能描述：往task.ini文件写任务结果
     * 参数：key 任务索引值
     * 参数：task_state 任务状态：2 完成；7 不可做；8 存疑；9 延迟
     * 参数：error 错误信息
     * 参数：process_method 制作说明
     * 参数：reason 备注,不可做原因。。。
     * 返回值：bool true：成功；false：失败
     * *******************************************************************/
    bool finish_task(int key, int task_state, QString& error, QString process_method = QString(), QString reason = QString());
    QString process_proc_mode(QString key_name) const;
signals:

private:
    QMap<QString, QString> m_cur_task_info;
    QMap<QString, QMap<QString, QString>> m_cur_ini_all_task_info;
    QString m_error;
    bool m_is_error;
};

#endif // MYTASKMODULE_H
