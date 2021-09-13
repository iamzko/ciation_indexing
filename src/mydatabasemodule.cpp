#include "mydatabasemodule.h"
#include <QSqlQuery>
static const QString DB_TYPE_SQLITE = QString("QSQLITE");
static const QString DB_TABLE_NAME_JOB = QString::fromUtf8(u8"RY_岗位流程属性表");
static const QString DB_TABLE_NAME_PUBLISH = QString::fromUtf8(u8"母体出版社");
static const QString DB_TABLE_NAME_LOCATION = QString::fromUtf8(u8"母体出版地");
static const QString DB_TABLE_NAME_LITERATURE = QString::fromUtf8(u8"文献出处");

static const QString DB_TABLE_NAME_DETAIL = QString::fromUtf8(u8"db_detail");
static const QString DB_TABLE_NAME_VIEW_CN = QString::fromUtf8(u8"V_YW_中文标记数据视图");
static const QString DB_TABLE_NAME_VIEW_EN = QString::fromUtf8(u8"V_YW_英文标记数据视图");
static const QString DB_TABLE_NAME_ARTICLE = QString::fromUtf8(u8"YW_文章信息表");
static const QString DB_TABLE_NAME_CIATION = QString::fromUtf8(u8"YW_引文信息表");
static const QString DB_TABLE_NAME_RESULT = QString::fromUtf8(u8"RefResults");
static const QString DB_TABLE_NAME_RESOURCE = QString::fromUtf8(u8"YW_RESOURCE");

static const QString DB_NAME_INPUT = QString("input");
static const QString DB_NAME_SYSTEM = QString("system");
static const QString DB_NAME_OUT = QString("out");

MyDataBaseModule::MyDataBaseModule(QObject* parent)
    : QObject(parent)
    , m_task_input_db(nullptr)
    , m_task_out_db(nullptr)
    , m_system_info_db(nullptr)
{
}

MyDataBaseModule::~MyDataBaseModule()
{
    input_db_close();
    out_db_close();
    system_info_db_close();
}

bool MyDataBaseModule::input_db_open(QString input_db_path)
{
    return open_db(input_db_path, m_task_input_db, DB_NAME_INPUT);
}

bool MyDataBaseModule::input_db_table_detail_read(QMap<QString, QMap<QString, QVariant>>& table_content)
{
    return read_input_table(table_content, DB_TABLE_NAME_DETAIL);
}

bool MyDataBaseModule::input_db_table_view_cn_read(QMap<QString, QMap<QString, QVariant>>& table_content)
{
    return read_input_table(table_content, DB_TABLE_NAME_VIEW_CN);
}

bool MyDataBaseModule::input_db_table_view_en_read(QMap<QString, QMap<QString, QVariant>>& table_content)
{
    return read_input_table(table_content, DB_TABLE_NAME_VIEW_EN);
}

bool MyDataBaseModule::input_db_table_article_read(QMap<QString, QMap<QString, QVariant>>& table_content)
{
    return read_input_table(table_content, DB_TABLE_NAME_ARTICLE);
}

bool MyDataBaseModule::input_db_table_ciation_read(QMap<QString, QMap<QString, QVariant>>& table_content)
{
    return read_input_table(table_content, DB_TABLE_NAME_CIATION);
}

bool MyDataBaseModule::out_db_open(QString out_db_path)
{
    return open_db(out_db_path, m_task_out_db, DB_NAME_OUT);
}

bool MyDataBaseModule::out_db_is_open()
{
    return is_db_open(m_task_out_db);
}

bool MyDataBaseModule::out_db_table_detail_read(QMap<QString, QMap<QString, QVariant>>& table_content)
{
    return read_out_table(table_content, DB_TABLE_NAME_DETAIL);
}

bool MyDataBaseModule::out_db_table_detail_write(const QMap<QString, QMap<QString, QVariant>>& table_content)
{
    return write_map_to_table(table_content, m_task_out_db, DB_TABLE_NAME_RESULT);
}

bool MyDataBaseModule::out_db_table_result_read(QMap<QString, QMap<QString, QVariant>>& table_content)
{
    return read_out_table(table_content, DB_TABLE_NAME_RESULT);
}

bool MyDataBaseModule::out_db_table_resource_read(QMap<QString, QMap<QString, QVariant>>& table_content)
{
    return read_out_table(table_content, DB_TABLE_NAME_RESOURCE);
}

bool MyDataBaseModule::out_db_table_result_write(const QMap<QString, QMap<QString, QVariant>>& table_content)
{
    return write_map_to_table(table_content, m_task_out_db, DB_TABLE_NAME_RESULT);
}

bool MyDataBaseModule::out_db_create(QString out_db_path)
{
    if (QFile::exists(out_db_path)) {
        m_error = QString::fromUtf8(u8"数据库文件已存在，无法创建新的数据库，数据库路径：%1").arg(out_db_path);
        return false;
    }
    if (!out_db_open(out_db_path)) {
        return false;
    }
    QSqlQuery query(*m_task_out_db.get());
    query.exec(QString::fromUtf8(u8"CREATE TABLE db_detail(岗位名称 text);"));
    query.exec(QString::fromStdWString(LR"(CREATE TABLE [RefResults] (
                                              [编号] INT NOT NULL, 
                                              [批到岗时间] VARCHAR(23) NOT NULL, 
                                              [文章编号] VARCHAR(20) NOT NULL, 
                                              [引文编号] VARCHAR(20), 
                                              [标记到岗] VARCHAR(23) NOT NULL, 
                                              [作者] TEXT, 
                                              [文献题名] TEXT, 
                                              [文献出处] TEXT, 
                                              [母体出版_年] TEXT, 
                                              [母体出版_卷] TEXT, 
                                              [母体出版_期] TEXT, 
                                              [母体出版_页] TEXT, 
                                              [版次说明] TEXT, 
                                              [母体出版地] TEXT, 
                                              [母体出版社] TEXT, 
                                              [主编] TEXT, 
                                              [学位论文授予单位] TEXT, 
                                              [其它] TEXT, 
                                              [待发表] VARCHAR(50), 
                                              [母体出处] TEXT, 
                                              [电子版] TEXT, 
                                              [英文信息] TEXT, 
                                              [不做] TEXT, 
                                              [备注] TEXT, 
                                              [会议地点] TEXT, 
                                              [语种] TEXT, 
                                              [标记引文] TEXT, 
                                              [标记人员] VARCHAR(50), 
                                              [文献类型] TEXT, 
                                              [标记总数] INT, 
                                              [不会] TEXT, 
                                              [标记备注] TEXT, 
                                              [语言转换] TEXT, 
                                              [链接引文] TEXT, 
                                              [整本编号] VARCHAR(50), 
                                              [标准题名] varchar(200), 
                                              [标准长度] int, 
                                              [首字母] varchar(100), 
                                              [操作标识] CHAR(1), 
                                              [算法点数] int, 
                                              [人工点数] int, 
                                              [增加点数] int, 
                                              [删除点数] int, 
                                              [修改点数] int, 
                                              [任务性质] varchar(20), 
                                              [增加引文] TEXT, 
                                              [质检批次] VARCHAR(20), 
                                              CONSTRAINT [sqlite_autoindex_RefResults_1] PRIMARY KEY ([引文编号]));)"));
    query.exec(QString::fromUtf8(u8"CREATE TABLE YW_RESOURCE(编号 int,链接文件 varchar(50),引文编号 varchar(50),作者 varchar(50),题名 text,来源 varchar(30),年 text,期 text,卷 text,版次说明 text,出版地 text,出版社 text,授予单位 text,操作人员 varchar(50),ISBN varchar(50),析出文献作者 text,图书主编 text,相关丛书主编 text,校对 text,翻译 text,整理 text,其他责任 text,联合出版 text,沿革关系 text,从属关系 text,时间 varchar(23),其他 text);"));
    return true;
}

bool MyDataBaseModule::system_info_db_open(QString system_db_path)
{
    return open_db(system_db_path, m_system_info_db, DB_NAME_SYSTEM);
}

bool MyDataBaseModule::system_info_db_job_table_read(QMap<QString, QMap<QString, QVariant>>& table_content)
{
    return read_system_info_table(table_content, DB_TABLE_NAME_JOB);
}

bool MyDataBaseModule::system_info_db_location_table_read(QMap<QString, QMap<QString, QVariant>>& table_content)
{
    return read_system_info_table(table_content, DB_TABLE_NAME_LOCATION);
}

bool MyDataBaseModule::system_info_db_publish_table_read(QMap<QString, QMap<QString, QVariant>>& table_content)
{
    return read_system_info_table(table_content, DB_TABLE_NAME_PUBLISH);
}

bool MyDataBaseModule::system_info_db_literature_table_read(QMap<QString, QMap<QString, QVariant>>& table_content)
{
    return read_system_info_table(table_content, DB_TABLE_NAME_LITERATURE);
}

void MyDataBaseModule::system_info_db_close()
{
    close_db(m_system_info_db);
}

QMap<QString, QVariant> MyDataBaseModule::out_db_one_empty_line_create()
{
    QMap<QString, QVariant> result;
    auto field_names = get_table_header_list(m_task_out_db, DB_TABLE_NAME_RESULT);
    foreach (auto& name, field_names) {
        QVariant temp;
        result.insert(name, temp);
    }
    return result;
}

void MyDataBaseModule::input_db_close()
{
    close_db(m_task_input_db);
}

void MyDataBaseModule::out_db_close()
{
    close_db(m_task_out_db);
}

bool MyDataBaseModule::open_db(QString db_path, QScopedPointer<QSqlDatabase>& db, const QString& db_name)
{
    if (!QFile::exists(db_path)) {
        m_error = QString::fromUtf8(u8"数据库文件不存在：%1").arg(db_path);
        return false;
    }
    close_db(db);
    db.reset(new QSqlDatabase());
    if (!db->isOpen()) {
        *db = QSqlDatabase::addDatabase(DB_TYPE_SQLITE, db_name);
        db->setDatabaseName(db_path);
        if (db->open()) {
            if (is_db_null(db)) {
                m_error = QString::fromUtf8(u8"[%1]是空数据库！").arg(db_path);
                return false;
            }
            return true;
        } else {
            m_error = QString::fromUtf8(u8"打开数据库失败，数据库路径：%1").arg(db_path);
            return false;
        }
    } else {
        m_error = QString::fromUtf8(u8"数据库已经打开！");
        return false;
    }
}

bool MyDataBaseModule::read_system_info_table(QMap<QString, QMap<QString, QVariant>>& table_content, const QString& table_name)
{
    if (!is_db_open(m_system_info_db)) {
        return false;
    }
    if (!is_db_table_exist(m_system_info_db, table_name)) {
        m_error = QString::fromUtf8(u8"不存在[%1]表！").arg(table_name);
        return false;
    }
    QSqlQuery query(*m_system_info_db.get());
    return read_table_to_map(query, table_content, table_name);
}

bool MyDataBaseModule::read_input_table(QMap<QString, QMap<QString, QVariant>>& table_content, const QString& table_name)
{
    if (!is_db_open(m_task_input_db)) {
        return false;
    }
    if (!is_db_table_exist(m_task_input_db, table_name)) {
        m_error = QString::fromUtf8(u8"不存在[%1]表！").arg(table_name);
        return false;
    }
    QSqlQuery query(*m_task_input_db.get());
    return read_table_to_map(query, table_content, table_name);
}

bool MyDataBaseModule::read_out_table(QMap<QString, QMap<QString, QVariant>>& table_content, const QString& table_name)
{
    if (!is_db_open(m_task_out_db)) {
        return false;
    }
    if (!is_db_table_exist(m_task_out_db, table_name)) {
        m_error = QString::fromUtf8(u8"不存在[%1]表！").arg(table_name);
        return false;
    }
    QSqlQuery query(*m_task_out_db.get());
    return read_table_to_map(query, table_content, table_name);
}

bool MyDataBaseModule::write_map_to_table(const QMap<QString, QMap<QString, QVariant>>& table_content, QScopedPointer<QSqlDatabase>& db, const QString& table_name)
{
    if (!is_db_open(db)) {
        return false;
    }
    if (!is_db_table_exist(db, table_name)) {
        m_error = QString::fromUtf8(u8"不存在[%1]表！").arg(table_name);
        return false;
    }
    QSqlQuery query(*db.get());
    auto header_name = get_table_header_list(query, table_name);
    db->transaction();
    foreach (auto& line, table_content) {
        auto sql = QString::fromUtf8(u8"insert into %1 values(").arg(table_name);
        int size = header_name.size();
        for (int i = 0; i < size; ++i) {
            sql += "?";
            if (i != size - 1) {
                sql += ",";
            }
        }
        sql += ");";
        query.prepare(sql);
        for (int i = 0; i < size; ++i) {
            query.bindValue(i, line.value(header_name.at(i)));
        }
        qDebug() << sql;
        query.exec();
    }
    db->commit();
    return true;
}

bool MyDataBaseModule::read_table_to_map(QSqlQuery& query, QMap<QString, QMap<QString, QVariant>>& table_content, const QString& table_name)
{
    auto header_name = get_table_header_list(query, table_name);
    if (query.exec(QString::fromUtf8(u8"select * from %1;").arg(table_name))) {
        int i = 0;
        while (query.next()) {
            QMap<QString, QVariant> temp_map;
            foreach (auto& key, header_name) {
                temp_map.insert(key, query.value(key));
            }
            table_content.insert(QString::number(i++), temp_map);
        }
    }
    return true;
}

void MyDataBaseModule::close_db(QScopedPointer<QSqlDatabase>& db)
{
    if (db.isNull()) {
        return;
    }
    auto connection_name = db->connectionName();
    db->close();
    db.reset(nullptr);
    QSqlDatabase::removeDatabase(connection_name);
}

QStringList MyDataBaseModule::get_table_header_list(QScopedPointer<QSqlDatabase>& db, const QString& table_name)
{
    QSqlQuery query(*db.get());
    QStringList header_name;
    if (query.exec(QString::fromUtf8(u8"pragma table_info(%1)").arg(table_name))) {
        while (query.next()) {
            header_name.append(query.value(1).toString());
        }
    }
    return header_name;
}

QStringList MyDataBaseModule::get_table_header_list(QSqlQuery& query, const QString& table_name)
{
    QStringList header_name;
    if (query.exec(QString::fromUtf8(u8"pragma table_info(%1)").arg(table_name))) {
        while (query.next()) {
            header_name.append(query.value(1).toString());
        }
    }
    return header_name;
}

bool MyDataBaseModule::is_db_open(QScopedPointer<QSqlDatabase>& db)
{
    if (db.isNull() || !db->isOpen()) {
        m_error = QString::fromUtf8(u8"数据库尚未打开！");
        return false;
    }
    return true;
}

bool MyDataBaseModule::is_db_null(QScopedPointer<QSqlDatabase>& db)
{
    QSqlQuery query(*db);
    query.exec(QString::fromUtf8(u8"select name from sqlite_master where type = 'table';"));
    int i = 0;
    while (query.next()) {
        i++;
    }
    return i > 0 ? false : true;
}

bool MyDataBaseModule::is_db_table_exist(QScopedPointer<QSqlDatabase>& db, const QString& table_name)
{
    QSqlQuery query(*db);
    query.exec(QString::fromUtf8(u8"select name from sqlite_master where type = 'table';"));
    while (query.next()) {
        if (table_name == query.value(0).toString()) {
            return true;
        }
    }
    return false;
}

const QString& MyDataBaseModule::error() const
{
    return m_error;
}
