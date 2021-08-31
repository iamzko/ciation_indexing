#ifndef MYDATABASEMODULE_H
#define MYDATABASEMODULE_H
#include <QFile>
#include <QMap>
#include <QObject>
#include <QScopedPointer>
#include <QVariant>
#include <QtSql>

class MyDataBaseModule : public QObject
{
    Q_OBJECT
public:
    explicit MyDataBaseModule(QObject *parent = nullptr);
    ~MyDataBaseModule();
    bool input_db_open(QString input_db_path);
    bool input_db_table_detail_read(QMap<QString, QMap<QString, QVariant>>& table_content);
    bool input_db_table_view_cn_read(QMap<QString, QMap<QString, QVariant>>& table_content);
    bool input_db_table_view_en_read(QMap<QString, QMap<QString, QVariant>>& table_content);
    bool input_db_table_article_read(QMap<QString, QMap<QString, QVariant>>& table_content);
    bool input_db_table_ciation_read(QMap<QString, QMap<QString, QVariant>>& table_content);
    void input_db_close();
    bool out_db_open(QString out_db_path);
    bool out_db_table_detail_read(QMap<QString, QMap<QString, QVariant>>& table_content);
    bool out_db_table_detail_write(const QMap<QString, QMap<QString, QVariant>>& table_content);
    bool out_db_table_result_read(QMap<QString, QMap<QString, QVariant>>& table_content);
    bool out_db_table_result_write(const QMap<QString, QMap<QString, QVariant>>& table_content);
    bool out_db_table_resource_read(QMap<QString, QMap<QString, QVariant>>& table_content);
    void out_db_close();
    bool out_db_create(QString out_db_path);
    bool system_info_db_open(QString system_db_path);
    bool system_info_db_job_table_read(QMap<QString, QMap<QString, QVariant>>& table_content);
    bool system_info_db_location_table_read(QMap<QString, QMap<QString, QVariant>>& table_content);
    bool system_info_db_publish_table_read(QMap<QString, QMap<QString, QVariant>>& table_content);
    bool system_info_db_literature_table_read(QMap<QString, QMap<QString, QVariant>>& table_content);
    void system_info_db_close();

    const QString& error() const;

private:
    bool open_db(QString db_path, QScopedPointer<QSqlDatabase>& db, const QString& db_name);
    bool read_system_info_table(QMap<QString, QMap<QString, QVariant>>& table_content, const QString& table_name);
    bool read_input_table(QMap<QString, QMap<QString, QVariant>>& table_content, const QString& table_name);
    bool read_out_table(QMap<QString, QMap<QString, QVariant>>& table_content, const QString& table_name);
    bool read_table_to_map(QSqlQuery& query, QMap<QString, QMap<QString, QVariant>>& table_content, const QString& table_name);
    bool write_map_to_table(const QMap<QString, QMap<QString, QVariant>>& table_content, QScopedPointer<QSqlDatabase>& db, const QString& table_name);
    void close_db(QScopedPointer<QSqlDatabase>& db);
    QStringList get_table_header_list(QScopedPointer<QSqlDatabase>& db, const QString& table_name);
    QStringList get_table_header_list(QSqlQuery& query, const QString& table_name);
    bool is_db_open(QScopedPointer<QSqlDatabase>& db);
    bool is_db_null(QScopedPointer<QSqlDatabase>& db);
    bool is_db_table_exist(QScopedPointer<QSqlDatabase>& db, const QString& table_name);

signals:
private:
    QScopedPointer<QSqlDatabase> m_task_input_db;
    QScopedPointer<QSqlDatabase> m_task_out_db;
    QScopedPointer<QSqlDatabase> m_system_info_db;
    QString m_error;
};

#endif // MYDATABASEMODULE_H
