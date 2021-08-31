#include "mydatamodel.h"
#include <QDebug>

MyDataModel::MyDataModel(QObject *parent) : QAbstractItemModel(parent)
{
    m_table_header << QString::fromUtf8(u8"编号");
    m_table_header << QString::fromUtf8(u8"岗位名称");
    m_table_header << QString::fromUtf8(u8"任务性质");
    m_table_header << QString::fromUtf8(u8"文章编号");
    m_table_header << QString::fromUtf8(u8"引文编号");
    m_table_header << QString::fromUtf8(u8"到岗时间");
    m_table_header << QString::fromUtf8(u8"开始时间");
    m_table_header << QString::fromUtf8(u8"质检批次");
    m_table_header << QString::fromUtf8(u8"标记引文");
    m_table_header << QString::fromUtf8(u8"标记总数");
    m_table_header << QString::fromUtf8(u8"作者");
    m_table_header << QString::fromUtf8(u8"文献题名");
    m_table_header << QString::fromUtf8(u8"文献出处");
    m_table_header << QString::fromUtf8(u8"文献类型");
    m_table_header << QString::fromUtf8(u8"母体出处");
    m_table_header << QString::fromUtf8(u8"母体出版_年");
    m_table_header << QString::fromUtf8(u8"母体出版_卷");
    m_table_header << QString::fromUtf8(u8"母体出版_期");
    m_table_header << QString::fromUtf8(u8"母体出版_页");
    m_table_header << QString::fromUtf8(u8"版次说明");
    m_table_header << QString::fromUtf8(u8"母体出版地");
    m_table_header << QString::fromUtf8(u8"母体出版社");
    m_table_header << QString::fromUtf8(u8"会议地点");
    m_table_header << QString::fromUtf8(u8"主编");
    m_table_header << QString::fromUtf8(u8"学位论文授予单位");
    m_table_header << QString::fromUtf8(u8"待发表");
    m_table_header << QString::fromUtf8(u8"责任方式");
    m_table_header << QString::fromUtf8(u8"语种");
    m_table_header << QString::fromUtf8(u8"电子版");
    m_table_header << QString::fromUtf8(u8"其它");
    m_table_header << QString::fromUtf8(u8"不做");
    m_table_header << QString::fromUtf8(u8"不会");
    m_table_header << QString::fromUtf8(u8"语言转换");
    m_table_header << QString::fromUtf8(u8"英文信息");
    m_table_header << QString::fromUtf8(u8"标记人员");
    m_table_header << QString::fromUtf8(u8"备注");
    m_table_header << QString::fromUtf8(u8"算法点数");
    m_table_header << QString::fromUtf8(u8"人工点数");
    m_table_header << QString::fromUtf8(u8"人工增加");
    m_table_header << QString::fromUtf8(u8"人工修改");
    m_table_header << QString::fromUtf8(u8"人工删除");
    m_table_header << QString::fromUtf8(u8"工作路径");
    m_col = m_table_header.size();
}

QModelIndex MyDataModel::index(int row, int column, const QModelIndex& parent) const
{
    if (!hasIndex(row, column, parent)) {
        return QModelIndex();
    }
    return createIndex(row, column, (void*)&m_data.at(row).at(column));
}

QModelIndex MyDataModel::parent(const QModelIndex& index) const
{
    return QModelIndex();
}

int MyDataModel::rowCount(const QModelIndex& parent) const
{
    return m_data.size();
}

int MyDataModel::columnCount(const QModelIndex& parent) const
{
    return m_col;
}

QVariant MyDataModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::CheckStateRole) {
        return QVariant();
    }
    if (role == Qt::TextAlignmentRole) {
        return int(Qt::AlignCenter | Qt::AlignVCenter);
    }
    if (role == Qt::DisplayRole) {
        return m_data.at(index.row()).at(index.column());
    }
    return QVariant();
}

bool MyDataModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        m_data[index.row()][index.column()] = value;
        emit dataChanged(index, index);
        return true;
    }
    if (index.isValid() && role == Qt::DisplayRole) {
        m_data[index.row()][index.column()] = value;
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

bool MyDataModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant& value, int role)
{
    if (orientation == Qt::Horizontal && section >= 0 && section < m_table_header.size()) {
        m_table_header[section] = value.toString();
        emit headerDataChanged(orientation, section, section);
        return true;
    }
    return false;
}

QVariant MyDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal) {
        if (role == Qt::DisplayRole) {
            if (section >= 0 && section < m_table_header.count()) {
                return m_table_header.at(section);
            }
            return m_table_header.at(section);
        }
        if (role == Qt::TextAlignmentRole) {
            return int(Qt::AlignCenter | Qt::AlignVCenter);
        }
    } else {
        if (role == Qt::DisplayRole) {
            return QString("%1").arg(section + 1);
        }
        if (role == Qt::TextAlignmentRole) {
            return int(Qt::AlignCenter | Qt::AlignVCenter);
        }
    }
    return QVariant();
}

bool MyDataModel::insertRows(int row, int count, const QModelIndex& parent)
{
    beginInsertRows(parent, row, row);
    for (int i = 0; i < count; ++i) {
        QVector<QVariant> temp;
        for (int j = 0; j < m_table_header.size(); ++j) {
            temp.push_back(QVariant());
        }
        m_data.insert(row + i, temp);
    }
    endInsertRows();
    return true;
}

void MyDataModel::sort(int column, Qt::SortOrder order)
{
    std::sort(m_data.begin(), m_data.end(), [column, order](const QVector<QVariant>& a, const QVector<QVariant>& b) {
        if (order == Qt::AscendingOrder) {
            switch (column) {
            case int(COL_NAME::TASK_CODE): {
                return a.at(column).toInt() < b.at(column).toInt();
            } break;
            }

        } else {
            switch (column) {
            case int(COL_NAME::TASK_CODE): {
                return a.at(column).toInt() > b.at(column).toInt();
            } break;
            }
        }
        return order == Qt::AscendingOrder ? a.at(int(COL_NAME::TASK_CODE)).toInt() < b.at(int(COL_NAME::TASK_CODE)).toInt() : a.at(int(COL_NAME::TASK_CODE)).toInt() > b.at(int(COL_NAME::TASK_CODE)).toInt();
    });
    emit dataChanged(index(0, 0), index(m_data.size() - 1, m_table_header.size() - 1));
}
