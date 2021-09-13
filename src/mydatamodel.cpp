#include "mydatamodel.h"
#include "myglobal.h"
#include <QDebug>

MyDataModel::MyDataModel(QObject *parent) : QAbstractItemModel(parent)
{
    m_table_header << MyGlobal::TASK_CODE;
    m_table_header << MyGlobal::POST_NAME;
    m_table_header << MyGlobal::TASK_CHARACTERISTICS;
    m_table_header << MyGlobal::ARTICLE_CODE;
    m_table_header << MyGlobal::CIATION_CODE;
    m_table_header << MyGlobal::ARRIVE_TIME;
    m_table_header << MyGlobal::START_TIME;
    m_table_header << MyGlobal::CHECK_BATCH;
    m_table_header << MyGlobal::CIATION_INDEXICAL;
    m_table_header << MyGlobal::INDEXING_TOTAL_NUMBER;
    m_table_header << MyGlobal::AUTHOR_NAME;
    m_table_header << MyGlobal::ARTICLE_TITLE;
    m_table_header << MyGlobal::ARTICLE_SOURCES;
    m_table_header << MyGlobal::ARTICLE_TYPE;
    m_table_header << MyGlobal::MOTHER_SOURCES;
    m_table_header << MyGlobal::MOTHER_YEAR;
    m_table_header << MyGlobal::MOTHER_VOLUME;
    m_table_header << MyGlobal::MOTHER_PHASE;
    m_table_header << MyGlobal::MOTHER_PAGE;
    m_table_header << MyGlobal::EDITION_DESCRIPTION;
    m_table_header << MyGlobal::MOTHER_LOCATION;
    m_table_header << MyGlobal::MOTHER_PRESS;
    m_table_header << MyGlobal::MEETING_LOCATION;
    m_table_header << MyGlobal::CHIEF_EDITOR;
    m_table_header << MyGlobal::CONFER_UNIT;
    m_table_header << MyGlobal::PUBLISH_STATE;
    m_table_header << MyGlobal::RESPONSIBILITY_TYPE;
    m_table_header << MyGlobal::LANGUAGE;
    m_table_header << MyGlobal::ELECTRONIC_EDITION;
    m_table_header << MyGlobal::OTHER;
    m_table_header << MyGlobal::DO_NOT;
    m_table_header << MyGlobal::CAN_NOT;
    m_table_header << MyGlobal::LANGUAGE_TRANS;
    m_table_header << MyGlobal::ENGLISH_INFO;
    m_table_header << MyGlobal::INDEXING_STAFF;
    m_table_header << MyGlobal::OTHER_INFO;
    m_table_header << MyGlobal::ALGORITHM_POINT;
    m_table_header << MyGlobal::HUMAN_POINT;
    m_table_header << MyGlobal::HUMAN_ADD;
    m_table_header << MyGlobal::HUMAN_MODIFY;
    m_table_header << MyGlobal::HUMAN_DELETE;
    m_table_header << MyGlobal::WORK_PATH;
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
        return int(Qt::AlignLeft | Qt::AlignVCenter);
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
