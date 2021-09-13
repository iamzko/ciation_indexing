#include "mydatatable.h"
#include <QHeaderView>
#include <QVBoxLayout>
#include <QtDebug>

MyDataTable::MyDataTable(QWidget *parent) : QWidget(parent)
{
    m_data_view = new QTableView(this);
    m_data_model = new MyDataModel(this);
    m_data_view->setModel(m_data_model);
    //    m_data_view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    auto layout = new QVBoxLayout(this);
    layout->addWidget(m_data_view);
    //    for (int i = 0; i < 2; ++i) {
    //        m_data_model->insertRow(i);
    //        m_data_model->setData(m_data_model->index(i, 0), QString("%1").arg(i), Qt::DisplayRole);
    //    }
    auto header_view = m_data_view->horizontalHeader();
    //    header_view->setSectionsMovable(true);
    header_view->setSectionsClickable(true);
    header_view->setStretchLastSection(true);
    m_data_view->setSortingEnabled(true);
    m_data_view->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_data_view->setSelectionMode(QAbstractItemView::SingleSelection);
    init_signals_and_slots();
}

bool MyDataTable::set_cur_data(QMap<QString, QMap<QString, QVariant>>& data)
{
    auto headers = get_table_headers();
    qDebug() << headers;
    foreach (auto& line, data) {
        qDebug() << m_data_model->rowCount();
        insert_one_line(line, m_data_model->rowCount() - 1);
    }
    m_data_view->resizeColumnsToContents();

    return true;
}

bool MyDataTable::insert_one_line(const QMap<QString, QVariant>& line_data, int row_location)
{
    if (row_location < 0) {
        m_data_model->insertRow(0);
        set_one_line_data(0, line_data);
    } else if (row_location < m_data_model->rowCount()) {
        m_data_model->insertRow(row_location);
        set_one_line_data(row_location, line_data);
    } else {
        m_data_model->insertRow(m_data_model->rowCount());
        set_one_line_data(m_data_model->rowCount() - 1, line_data);
    }
    return true;
}

QStringList MyDataTable::get_table_headers()
{
    QStringList result;
    for (int i = 0; i < m_data_model->columnCount(); ++i) {
        result << m_data_model->headerData(i, Qt::Horizontal).toString();
    }
    return result;
}

void MyDataTable::set_one_line_data(int line, const QMap<QString, QVariant>& line_data)
{
    m_data_model->setData(m_data_model->index(line, static_cast<int>(MyDataModel::COL_NAME::TASK_CODE)), line_data.value(QString::fromUtf8(u8"编号")), Qt::DisplayRole);
    m_data_model->setData(m_data_model->index(line, static_cast<int>(MyDataModel::COL_NAME::POST_NAME)), line_data.value(QString::fromUtf8(u8"岗位名称"))); //岗位名称
    m_data_model->setData(m_data_model->index(line, static_cast<int>(MyDataModel::COL_NAME::TASK_CHARACTERISTICS)), line_data.value(QString::fromUtf8(u8"任务性质")), Qt::DisplayRole);
    m_data_model->setData(m_data_model->index(line, static_cast<int>(MyDataModel::COL_NAME::ARTICLE_CODE)), line_data.value(QString::fromUtf8(u8"文章编号")), Qt::DisplayRole);
    m_data_model->setData(m_data_model->index(line, static_cast<int>(MyDataModel::COL_NAME::CIATION_CODE)), line_data.value(QString::fromUtf8(u8"引文编号")), Qt::DisplayRole);
    m_data_model->setData(m_data_model->index(line, static_cast<int>(MyDataModel::COL_NAME::ARRIVE_TIME)), line_data.value(QString::fromUtf8(u8"标记到岗")), Qt::DisplayRole);
    m_data_model->setData(m_data_model->index(line, static_cast<int>(MyDataModel::COL_NAME::START_TIME)), line_data.value(QString::fromUtf8(u8"批到岗时间")), Qt::DisplayRole);
    m_data_model->setData(m_data_model->index(line, static_cast<int>(MyDataModel::COL_NAME::CHECK_BATCH)), line_data.value(QString::fromUtf8(u8"质检批次")), Qt::DisplayRole);
    m_data_model->setData(m_data_model->index(line, static_cast<int>(MyDataModel::COL_NAME::CIATION_INDEXICAL)), line_data.value(QString::fromUtf8(u8"标记引文")), Qt::DisplayRole);
    m_data_model->setData(m_data_model->index(line, static_cast<int>(MyDataModel::COL_NAME::INDEXING_TOTAL_NUMBER)), line_data.value(QString::fromUtf8(u8"标记总数")), Qt::DisplayRole);
    m_data_model->setData(m_data_model->index(line, static_cast<int>(MyDataModel::COL_NAME::AUTOR_NAME)), line_data.value(QString::fromUtf8(u8"作者")), Qt::DisplayRole);
    m_data_model->setData(m_data_model->index(line, static_cast<int>(MyDataModel::COL_NAME::ARTICLE_TITLE)), line_data.value(QString::fromUtf8(u8"文献题名")), Qt::DisplayRole);
    m_data_model->setData(m_data_model->index(line, static_cast<int>(MyDataModel::COL_NAME::ARTICLE_SOURCES)), line_data.value(QString::fromUtf8(u8"文献出处")), Qt::DisplayRole);
    m_data_model->setData(m_data_model->index(line, static_cast<int>(MyDataModel::COL_NAME::ARTICLE_TYPE)), line_data.value(QString::fromUtf8(u8"文献类型")), Qt::DisplayRole);
    m_data_model->setData(m_data_model->index(line, static_cast<int>(MyDataModel::COL_NAME::MOTHER_SOURCES)), line_data.value(QString::fromUtf8(u8"母体出处")), Qt::DisplayRole);
    m_data_model->setData(m_data_model->index(line, static_cast<int>(MyDataModel::COL_NAME::MOTHER_YEAR)), line_data.value(QString::fromUtf8(u8"母体出版_年")), Qt::DisplayRole);
    m_data_model->setData(m_data_model->index(line, static_cast<int>(MyDataModel::COL_NAME::MOTHER_VOLUME)), line_data.value(QString::fromUtf8(u8"母体出版_卷")), Qt::DisplayRole);
    m_data_model->setData(m_data_model->index(line, static_cast<int>(MyDataModel::COL_NAME::MOTHER_PHASE)), line_data.value(QString::fromUtf8(u8"母体出版_期")), Qt::DisplayRole);
    m_data_model->setData(m_data_model->index(line, static_cast<int>(MyDataModel::COL_NAME::MOTHER_PAGE)), line_data.value(QString::fromUtf8(u8"母体出版_页")), Qt::DisplayRole);
    m_data_model->setData(m_data_model->index(line, static_cast<int>(MyDataModel::COL_NAME::EDITION_DESCRIPTION)), line_data.value(QString::fromUtf8(u8"版次说明")), Qt::DisplayRole);
    m_data_model->setData(m_data_model->index(line, static_cast<int>(MyDataModel::COL_NAME::MOTHER_LOCATION)), line_data.value(QString::fromUtf8(u8"母体出版地")), Qt::DisplayRole);
    m_data_model->setData(m_data_model->index(line, static_cast<int>(MyDataModel::COL_NAME::MOTHER_PRESS)), line_data.value(QString::fromUtf8(u8"母体出版社")), Qt::DisplayRole);
    m_data_model->setData(m_data_model->index(line, static_cast<int>(MyDataModel::COL_NAME::MEETING_LOCATION)), line_data.value(QString::fromUtf8(u8"会议地点")), Qt::DisplayRole);
    m_data_model->setData(m_data_model->index(line, static_cast<int>(MyDataModel::COL_NAME::CHIEF_EDITOR)), line_data.value(QString::fromUtf8(u8"主编")), Qt::DisplayRole);
    m_data_model->setData(m_data_model->index(line, static_cast<int>(MyDataModel::COL_NAME::CONFER_UNIT)), line_data.value(QString::fromUtf8(u8"学位论文授予单位")), Qt::DisplayRole);
    m_data_model->setData(m_data_model->index(line, static_cast<int>(MyDataModel::COL_NAME::PUBLISH_STATE)), line_data.value(QString::fromUtf8(u8"待发表")), Qt::DisplayRole);
    m_data_model->setData(m_data_model->index(line, static_cast<int>(MyDataModel::COL_NAME::RESPONSIBILITY_TYPE)), line_data.value(QString::fromUtf8(u8"责任方式")), Qt::DisplayRole); //责任方式
    m_data_model->setData(m_data_model->index(line, static_cast<int>(MyDataModel::COL_NAME::LANGUAGE)), line_data.value(QString::fromUtf8(u8"语种")), Qt::DisplayRole);
    m_data_model->setData(m_data_model->index(line, static_cast<int>(MyDataModel::COL_NAME::ELECTRONIC_EDITION)), line_data.value(QString::fromUtf8(u8"电子版")), Qt::DisplayRole);
    m_data_model->setData(m_data_model->index(line, static_cast<int>(MyDataModel::COL_NAME::OTHER)), line_data.value(QString::fromUtf8(u8"其它")), Qt::DisplayRole);
    m_data_model->setData(m_data_model->index(line, static_cast<int>(MyDataModel::COL_NAME::DO_NOT)), line_data.value(QString::fromUtf8(u8"不做")), Qt::DisplayRole);
    m_data_model->setData(m_data_model->index(line, static_cast<int>(MyDataModel::COL_NAME::CAN_NOT)), line_data.value(QString::fromUtf8(u8"不会")), Qt::DisplayRole);
    m_data_model->setData(m_data_model->index(line, static_cast<int>(MyDataModel::COL_NAME::LANGUAGE_TRANS)), line_data.value(QString::fromUtf8(u8"语言转换")), Qt::DisplayRole);
    m_data_model->setData(m_data_model->index(line, static_cast<int>(MyDataModel::COL_NAME::ENGLISH_INFO)), line_data.value(QString::fromUtf8(u8"英文信息")), Qt::DisplayRole); //英文信息
    m_data_model->setData(m_data_model->index(line, static_cast<int>(MyDataModel::COL_NAME::INDEXING_STAFF)), line_data.value(QString::fromUtf8(u8"标记人员")), Qt::DisplayRole);
    m_data_model->setData(m_data_model->index(line, static_cast<int>(MyDataModel::COL_NAME::OTHER_INFO)), line_data.value(QString::fromUtf8(u8"备注")), Qt::DisplayRole);
    m_data_model->setData(m_data_model->index(line, static_cast<int>(MyDataModel::COL_NAME::ALGORITHM_POINT)), line_data.value(QString::fromUtf8(u8"算法点数")), Qt::DisplayRole);
    m_data_model->setData(m_data_model->index(line, static_cast<int>(MyDataModel::COL_NAME::HUMAN_POINT)), line_data.value(QString::fromUtf8(u8"人工点数")), Qt::DisplayRole);
    m_data_model->setData(m_data_model->index(line, static_cast<int>(MyDataModel::COL_NAME::HUMAN_ADD)), line_data.value(QString::fromUtf8(u8"增加点数")), Qt::DisplayRole);
    m_data_model->setData(m_data_model->index(line, static_cast<int>(MyDataModel::COL_NAME::HUMAN_MODIFY)), line_data.value(QString::fromUtf8(u8"修改点数")), Qt::DisplayRole);
    m_data_model->setData(m_data_model->index(line, static_cast<int>(MyDataModel::COL_NAME::HUMAN_DELETE)), line_data.value(QString::fromUtf8(u8"删除点数")), Qt::DisplayRole);
    m_data_model->setData(m_data_model->index(line, static_cast<int>(MyDataModel::COL_NAME::WORK_PATH)), line_data.value(QString::fromUtf8(u8"工作路径")), Qt::DisplayRole); //db路径
}

void MyDataTable::init_signals_and_slots()
{
    connect(m_data_view, SIGNAL(clicked(const QModelIndex&)), this, SLOT(on_tableview_clicked(const QModelIndex&)));
    connect(m_data_view, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(on_tableview_double_clicked(const QModelIndex&)));
}

void MyDataTable::on_tableview_clicked(const QModelIndex& index)
{
    //    qDebug() << m_data_model->data(m_data_model->index(index.row(), static_cast<int>(MyDataModel::COL_NAME::CIATION_INDEXICAL))).toString();
    auto ciation_content = (m_data_model->data(m_data_model->index(index.row(), static_cast<int>(MyDataModel::COL_NAME::CIATION_INDEXICAL))).toString());
    emit current_clicked_index(ciation_content);
}

void MyDataTable::on_tableview_double_clicked(const QModelIndex& index)
{
    task_part_info temp;
    temp.task_code = m_data_model->data(m_data_model->index(index.row(), static_cast<int>(MyDataModel::COL_NAME::TASK_CODE))).toString();
    temp.article_code = m_data_model->data(m_data_model->index(index.row(), static_cast<int>(MyDataModel::COL_NAME::ARTICLE_CODE))).toString();
    temp.ciation_code = m_data_model->data(m_data_model->index(index.row(), static_cast<int>(MyDataModel::COL_NAME::CIATION_CODE))).toString();
    temp.task_come_time = m_data_model->data(m_data_model->index(index.row(), static_cast<int>(MyDataModel::COL_NAME::START_TIME))).toString();
    emit current_double_clicked_index(temp);
}
