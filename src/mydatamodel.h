#ifndef MYDATAMODEL_H
#define MYDATAMODEL_H

#include <QAbstractItemModel>
#include <QList>
#include <QVariant>

class MyDataModel : public QAbstractItemModel
{
    enum class COL_NAME {
        TASK_CODE = 0,
        POST_NAME,
        TASK_CHARACTERISTICS,
        ARTICLE_CODE,
        CIATION_CODE,
        ARRIVE_TIME,
        START_TIME,
        CHECK_BATCH,
        CIATION_INDEXICAL,
        INDEXING_TOTAL_NUMBER,
        AUTOR_NAME,
        ARTICLE_TITLE,
        ARTICLE_SOURCES,
        ARTICLE_TYPE,
        MOTHER_SOURCES,
        MOTHER_YEAR,
        MOTHER_VOLUME,
        MOTHER_PHASE,
        MOTHER_PAGE,
        EDITION_DESCRIPTION,
        MOTHER_LOCATION,
        MOTHER_PRESS,
        CHIEF_EDITOR,
        CONFER_UNIT,
        PUBLISH_STATE,
        RESPONSIBILITY_TYPE,
        LANGUAGE,
        ELECTRONIC_EDITION,
        OTHER,
        DO_NOT,
        CAN_NOT,
        LANGUAGE_TRANS,
        ENGLISH_INFO,
        INDEXING_STAFF,
        OTHER_INFO,
        ALGORITHM_POINT,
        HUMAN_POINT,
        HUMAN_ADD,
        HUMAN_MODIFY,
        HUMAN_DELETE,
        WORK_PATH,
    };

    Q_OBJECT
public:
    explicit MyDataModel(QObject *parent = nullptr);
    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex& index) const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant& value, int role = Qt::EditRole) override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;
    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override;

public:
private:
    int m_row;
    int m_col;
    QList<QVector<QVariant>> m_data;
    QStringList m_table_header;
};

#endif // MYDATAMODEL_H
