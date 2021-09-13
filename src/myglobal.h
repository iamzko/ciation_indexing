#ifndef MYGLOBAL_H
#define MYGLOBAL_H
#include <QMap>
#include <QString>
#include <QStringList>

struct task_part_info {
    QString task_code;
    QString article_code;
    QString ciation_code;
    QString task_come_time;
};

class MyGlobal
{
public:
    MyGlobal();
    static const QString TASK_CODE;
    static const QString POST_NAME;
    static const QString TASK_CHARACTERISTICS;
    static const QString ARTICLE_CODE;
    static const QString CIATION_CODE;
    static const QString ARRIVE_TIME;
    static const QString START_TIME;
    static const QString CHECK_BATCH;
    static const QString CIATION_INDEXICAL;
    static const QString INDEXING_TOTAL_NUMBER;
    static const QString AUTHOR_NAME;
    static const QString ARTICLE_TITLE;
    static const QString ARTICLE_SOURCES;
    static const QString ARTICLE_TYPE;
    static const QString MOTHER_SOURCES;
    static const QString MOTHER_YEAR;
    static const QString MOTHER_VOLUME;
    static const QString MOTHER_PHASE;
    static const QString MOTHER_PAGE;
    static const QString EDITION_DESCRIPTION;
    static const QString MOTHER_LOCATION;
    static const QString MOTHER_PRESS;
    static const QString MEETING_LOCATION;
    static const QString CHIEF_EDITOR;
    static const QString CONFER_UNIT;
    static const QString PUBLISH_STATE;
    static const QString RESPONSIBILITY_TYPE;
    static const QString LANGUAGE;
    static const QString ELECTRONIC_EDITION;
    static const QString OTHER;
    static const QString DO_NOT;
    static const QString CAN_NOT;
    static const QString LANGUAGE_TRANS;
    static const QString ENGLISH_INFO;
    static const QString INDEXING_STAFF;
    static const QString OTHER_INFO;
    static const QString ALGORITHM_POINT;
    static const QString HUMAN_POINT;
    static const QString HUMAN_ADD;
    static const QString HUMAN_MODIFY;
    static const QString HUMAN_DELETE;
    static const QString WORK_PATH;
    static const QString ENGLISH_CIATION_TAG;
    static const QString MARK_ARRIVE_TIME;
    static const QString TOTAL_BOOK_CODE;

    static const QString PERIODICALS;
    static const QString BOOK;
    static const QString MEETING_PAPER;
    static const QString DISSERTATION;
    static const QString REPORT;
    static const QString PATENT;
    static const QString STANDARD;
    static const QString NEWSPAPER;
    static const QString YEARBOOKS;
    static const QString OTHER_TYPE;
    static const QString MINOR_LANG;
    static const QString CASE_JUDGMENT;
    static const QString LAW;
    static const QString ARCHIVES;

    static const QString DOUBLE_STAR;
    static const QMap<QString, QString> INDEXING_SYMBOLS_MAP;
    static const QMap<QString, QString> ARTICLE_TYPES_MAP;
};

#endif // MYGLOBAL_H
