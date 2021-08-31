#include "mytaskmodule.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariant>
#include <QtDebug>

#define GET_TARGET_STR(x)                \
    if (!m_is_error)                     \
        return m_cur_task_info.value(x); \
    return QString();
#define GET_TARGET_INT(x)                        \
    if (!m_is_error)                             \
        return m_cur_task_info.value(x).toInt(); \
    return 0;

MyTaskModule::MyTaskModule(QObject* parent)
    : QObject(parent)
    , m_error("")
    , m_is_error(false)
{
}

QString MyTaskModule::get_article_code() const
{
    if (!m_is_error) {
        return m_cur_task_info.value("ArticleCode");
    }
    return QString();
}

QString MyTaskModule::get_code() const
{
    if (!m_is_error) {
        return m_cur_task_info.value("Code");
    }
    return QString();
}

QString MyTaskModule::get_del_path() const
{
    GET_TARGET_STR("DelPath")
}

unsigned int MyTaskModule::get_delay_times() const
{
    GET_TARGET_INT("DelayTimes")
}

QString MyTaskModule::get_down_time() const
{
    GET_TARGET_STR("DownTime")
}

QString MyTaskModule::get_finish_time() const
{
    GET_TARGET_STR("FinishTime")
}

unsigned int MyTaskModule::get_key_name() const
{
    GET_TARGET_INT("KeyName")
}

unsigned int MyTaskModule::get_line_id() const
{
    GET_TARGET_INT("LineID")
}

unsigned int MyTaskModule::get_post_id() const
{
    GET_TARGET_INT("PostID")
}

QString MyTaskModule::get_post_name() const
{
    GET_TARGET_STR("PostName")
}

QString MyTaskModule::get_proc_type() const
{
    GET_TARGET_STR("ProcType")
}

QString MyTaskModule::get_product_code() const
{
    GET_TARGET_STR("ProductCode")
}

QString MyTaskModule::get_reason() const
{
    GET_TARGET_STR("Reason")
}

QString MyTaskModule::get_start_time() const
{
    GET_TARGET_STR("StartTime")
}

QString MyTaskModule::get_stop_time() const
{
    GET_TARGET_STR("StopTime")
}

unsigned int MyTaskModule::get_submit_count() const
{
    GET_TARGET_INT("SubmitCount")
}

QString MyTaskModule::get_task_code() const
{
    GET_TARGET_STR("TaskCode")
}

QString MyTaskModule::get_task_come_time() const
{
    GET_TARGET_STR("TaskComeTime")
}

QString MyTaskModule::get_task_kind() const
{
    GET_TARGET_STR("TaskKind")
}

unsigned int MyTaskModule::get_task_level() const
{
    GET_TARGET_INT("TaskLevel")
}

unsigned int MyTaskModule::get_task_status() const
{
    GET_TARGET_INT("TaskStatus")
}

unsigned int MyTaskModule::get_task_weight() const
{
    GET_TARGET_INT("TaskWeight")
}

unsigned int MyTaskModule::get_tip_count() const {
    GET_TARGET_INT("TipCount")
}

QString MyTaskModule::get_upload_path() const {
    GET_TARGET_STR("UpPath")
}

QString MyTaskModule::get_work_path() const {
    GET_TARGET_STR("WorkPath")
}

QString MyTaskModule::get_worker() const {
    GET_TARGET_STR("Worker")
}

QString MyTaskModule::get_production_instruction() const {
    GET_TARGET_STR("Zzsm")
}

QString MyTaskModule::get_emergency() const
{
    if (!m_is_error) {
        return process_proc_mode(QString::fromUtf8(u8"紧急情况"));
    }
    return QString();
}

QString MyTaskModule::get_production_method() const
{
    if (!m_is_error) {
        return process_proc_mode(QString::fromUtf8(u8"制作方式"));
    }
    return QString();
}

bool MyTaskModule::load_new_task()
{
    int key;
    int ret = load_single_task(key, m_cur_task_info, m_error);
    if (ret != 1) {
        m_is_error = true;
    } else {
        m_is_error = false;
    }
    return !m_is_error;
}

bool MyTaskModule::finish_cur_task(int task_status, QString production_instruction, QString reason)
{
    if (m_is_error) {
        return false;
    }
    return finish_task(get_key_name(), task_status, m_error, production_instruction, reason);
}

int MyTaskModule::load_single_task(int& key, QMap<QString, QString>& task_content, QString& error)
{
    key = -1;
    task_content.clear();
    char task_json[TASK_BUFF_SIZE] = { 0 };
    char err_msg[TASK_ERROR_SIZE] = { 0 };
    int ret = LoadTaskWrapExA(key, task_json, err_msg);
    switch (ret) {
    case -1:
        error = QString::fromLocal8Bit(err_msg);
        break;
    case 0:
        error = QString::fromUtf8(u8"无任务");
        break;
    case 1: {
        //        qDebug() << key;
        //        qDebug() << QString::fromLocal8Bit(task_json);
        QJsonDocument json_doc;
        QJsonParseError json_err;
        json_doc = json_doc.fromJson(QString::fromLocal8Bit(task_json).toUtf8(), &json_err);
        if (json_err.error == QJsonParseError::NoError) {
            auto obj = json_doc.object();
            for (auto it = obj.begin(); it != obj.end(); ++it) {
                task_content.insert(it.key(), it.value().isDouble() ? QString::number(it.value().toInt()) : it.value().toString());
            }
        } else {
            error = json_err.errorString();
        }
        //        qDebug() << task_content;

    } break;
    }
    return ret;
}

int MyTaskModule::load_all_task(QMap<QString, QMap<QString, QString>>& task_content, QString& error)
{
    char all_task_json[TASK_BUFF_SIZE] = { 0 };
    char err_msg[TASK_ERROR_SIZE] = { 0 };
    int ret = GetAllTaskJsonWrapExA(all_task_json, err_msg);
    switch (ret) {
    case -1:
        error = QString::fromLocal8Bit(err_msg);
        break;
    case 0:
        error = QString::fromUtf8(u8"无任务");
        break;
    case 1: {
        //        qDebug() << QString::fromLocal8Bit(all_task_json);
        QJsonDocument json_doc;
        QJsonParseError json_err;
        json_doc = json_doc.fromJson(QString::fromLocal8Bit(all_task_json).toUtf8(), &json_err);
        if (json_err.error == QJsonParseError::NoError) {
            if (json_doc.isArray()) {
                //                qDebug() << "array";
                auto json_obj = json_doc.array();
                for (auto it = json_obj.begin(); it != json_obj.end(); ++it) {
                    QMap<QString, QString> temp_map;
                    if (it->isObject()) {
                        auto child_obj = it->toObject();
                        for (auto itt = child_obj.begin(); itt != child_obj.end(); ++itt) {
                            //                            qDebug() << itt.key();
                            temp_map.insert(itt.key(), itt.value().isDouble() ? QString::number(itt.value().toInt()) : itt.value().toString());
                        }
                        task_content.insert(temp_map["KeyName"], temp_map);
                    }
                }
                //                qDebug() << task_content;
            }
        }

    } break;
    }
    return ret;
}

bool MyTaskModule::finish_task(int key, int task_state, QString& error, QString process_method, QString reason)
{
    char err_msg[TASK_ERROR_SIZE] = { 0 };
    auto ret = FinishTaskWrapExA(key, task_state, err_msg, process_method.toLocal8Bit().data(), reason.toLocal8Bit().data());
    error = QString::fromLocal8Bit(err_msg);
    return ret;
}

QString MyTaskModule::process_proc_mode(QString key_name) const
{
    auto temp_str = m_cur_task_info["ProcMode"];
    QJsonParseError temp_err;
    QJsonDocument temp_doc = QJsonDocument::fromJson(temp_str.toUtf8(), &temp_err);
    if (temp_err.error == QJsonParseError::NoError) {
        auto temp_obj = temp_doc.object();
        return temp_obj.value(key_name).toString();
    }
    return QString();
}

bool MyTaskModule::is_error() const
{
    return m_is_error;
}

QString MyTaskModule::get_error_string() const
{
    return m_error;
}

const QMap<QString, QMap<QString, QString>>& MyTaskModule::get_all_task_info() const
{
    return m_cur_ini_all_task_info;
}

void MyTaskModule::refresh_all_task_info()
{
    load_all_task(m_cur_ini_all_task_info, m_error);
}
