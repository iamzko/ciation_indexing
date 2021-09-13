#include "myglobal.h"
const QString MyGlobal::TASK_CODE = QString::fromUtf8(u8"编号");
const QString MyGlobal::POST_NAME = QString::fromUtf8(u8"岗位名称");
const QString MyGlobal::TASK_CHARACTERISTICS = QString::fromUtf8(u8"任务性质");
const QString MyGlobal::ARTICLE_CODE = QString::fromUtf8(u8"文章编号");
const QString MyGlobal::CIATION_CODE = QString::fromUtf8(u8"引文编号");
const QString MyGlobal::TOTAL_BOOK_CODE = QString::fromUtf8(u8"整本编号");
const QString MyGlobal::ARRIVE_TIME = QString::fromUtf8(u8"到岗时间");
const QString MyGlobal::MARK_ARRIVE_TIME = QString::fromUtf8(u8"标记到岗");
const QString MyGlobal::START_TIME = QString::fromUtf8(u8"开始时间");
const QString MyGlobal::CHECK_BATCH = QString::fromUtf8(u8"质检批次");
const QString MyGlobal::CIATION_INDEXICAL = QString::fromUtf8(u8"标记引文");
const QString MyGlobal::INDEXING_TOTAL_NUMBER = QString::fromUtf8(u8"标记总数");
const QString MyGlobal::AUTHOR_NAME = QString::fromUtf8(u8"作者");
const QString MyGlobal::ARTICLE_TITLE = QString::fromUtf8(u8"文献题名");
const QString MyGlobal::ARTICLE_SOURCES = QString::fromUtf8(u8"文献出处");
const QString MyGlobal::ARTICLE_TYPE = QString::fromUtf8(u8"文献类型");
const QString MyGlobal::MOTHER_SOURCES = QString::fromUtf8(u8"母体出处");
const QString MyGlobal::MOTHER_YEAR = QString::fromUtf8(u8"母体出版_年");
const QString MyGlobal::MOTHER_VOLUME = QString::fromUtf8(u8"母体出版_卷");
const QString MyGlobal::MOTHER_PHASE = QString::fromUtf8(u8"母体出版_期");
const QString MyGlobal::MOTHER_PAGE = QString::fromUtf8(u8"母体出版_页");
const QString MyGlobal::EDITION_DESCRIPTION = QString::fromUtf8(u8"版次说明");
const QString MyGlobal::MOTHER_LOCATION = QString::fromUtf8(u8"母体出版地");
const QString MyGlobal::MOTHER_PRESS = QString::fromUtf8(u8"母体出版社");
const QString MyGlobal::MEETING_LOCATION = QString::fromUtf8(u8"会议地点");
const QString MyGlobal::CHIEF_EDITOR = QString::fromUtf8(u8"主编");
const QString MyGlobal::CONFER_UNIT = QString::fromUtf8(u8"学位论文授予单位");
const QString MyGlobal::PUBLISH_STATE = QString::fromUtf8(u8"待发表");
const QString MyGlobal::RESPONSIBILITY_TYPE = QString::fromUtf8(u8"责任方式");
const QString MyGlobal::LANGUAGE = QString::fromUtf8(u8"语种");
const QString MyGlobal::ELECTRONIC_EDITION = QString::fromUtf8(u8"电子版");
const QString MyGlobal::OTHER = QString::fromUtf8(u8"其它");
const QString MyGlobal::DO_NOT = QString::fromUtf8(u8"不做");
const QString MyGlobal::CAN_NOT = QString::fromUtf8(u8"不会");
const QString MyGlobal::LANGUAGE_TRANS = QString::fromUtf8(u8"语言转换");
const QString MyGlobal::ENGLISH_INFO = QString::fromUtf8(u8"英文信息");
const QString MyGlobal::INDEXING_STAFF = QString::fromUtf8(u8"标记人员");
const QString MyGlobal::OTHER_INFO = QString::fromUtf8(u8"备注");
const QString MyGlobal::ALGORITHM_POINT = QString::fromUtf8(u8"算法点数");
const QString MyGlobal::HUMAN_POINT = QString::fromUtf8(u8"人工点数");
const QString MyGlobal::HUMAN_ADD = QString::fromUtf8(u8"人工增加");
const QString MyGlobal::HUMAN_MODIFY = QString::fromUtf8(u8"人工修改");
const QString MyGlobal::HUMAN_DELETE = QString::fromUtf8(u8"人工删除");
const QString MyGlobal::WORK_PATH = QString::fromUtf8(u8"工作路径");
const QString MyGlobal::ENGLISH_CIATION_TAG = QString::fromUtf8(u8"英文引文标志");
const QString MyGlobal::PERIODICALS = QString::fromUtf8(u8"期刊");
const QString MyGlobal::BOOK = QString::fromUtf8(u8"图书");
const QString MyGlobal::MEETING_PAPER = QString::fromUtf8(u8"会议论文");
const QString MyGlobal::DISSERTATION = QString::fromUtf8(u8"学位论文");
const QString MyGlobal::REPORT = QString::fromUtf8(u8"报告");
const QString MyGlobal::PATENT = QString::fromUtf8(u8"专利");
const QString MyGlobal::STANDARD = QString::fromUtf8(u8"标准");
const QString MyGlobal::NEWSPAPER = QString::fromUtf8(u8"报纸");
const QString MyGlobal::YEARBOOKS = QString::fromUtf8(u8"年鉴");
const QString MyGlobal::OTHER_TYPE = QString::fromUtf8(u8"其它_");
const QString MyGlobal::MINOR_LANG = QString::fromUtf8(u8"小语种");
const QString MyGlobal::CASE_JUDGMENT = QString::fromUtf8(u8"案例判决");
const QString MyGlobal::LAW = QString::fromUtf8(u8"法律法规");
const QString MyGlobal::ARCHIVES = QString::fromUtf8(u8"档案");
const QString MyGlobal::DOUBLE_STAR = QString::fromUtf8(u8"★★");
const QMap<QString, QString> MyGlobal::INDEXING_SYMBOLS_MAP = {
    { MyGlobal::AUTHOR_NAME, "@@" },
    { ARTICLE_TITLE, "##" },
    { ARTICLE_SOURCES, "$$" },
    { MOTHER_YEAR, u8"『『" },
    { MOTHER_VOLUME, u8"』』" },
    { MOTHER_PHASE, u8"〖〖" },
    { MOTHER_PAGE, u8"〗〗" },
    { EDITION_DESCRIPTION, u8"【【" },
    { MOTHER_LOCATION, u8"!!" },
    { LANGUAGE_TRANS, u8"●●" },
    { MOTHER_PRESS, u8"::" },
    { CHIEF_EDITOR, u8"】】" },
    { CONFER_UNIT, u8"%%" },
    { OTHER, u8"<<" },
    { PUBLISH_STATE, u8"☆☆" },
    { MOTHER_SOURCES, u8"」」" },
    { ENGLISH_CIATION_TAG, u8"■■" },
    { ELECTRONIC_EDITION, u8"‖‖" },
    { DO_NOT, u8"△△" },
    { CAN_NOT, u8"▲▲" },
    { OTHER_INFO, u8"◎◎" },
    { MEETING_LOCATION, u8"◇◇" },
    { LANGUAGE, u8"◆◆" },
};
const QMap<QString, QString> MyGlobal::ARTICLE_TYPES_MAP = {
    { PERIODICALS, DOUBLE_STAR + PERIODICALS + DOUBLE_STAR },
    { BOOK, DOUBLE_STAR + BOOK + DOUBLE_STAR },
    { MEETING_PAPER, DOUBLE_STAR + MEETING_PAPER + DOUBLE_STAR },
    { DISSERTATION, DOUBLE_STAR + DISSERTATION + DOUBLE_STAR },
    { REPORT, DOUBLE_STAR + REPORT + DOUBLE_STAR },
    { PATENT, DOUBLE_STAR + PATENT + DOUBLE_STAR },
    { STANDARD, DOUBLE_STAR + STANDARD + DOUBLE_STAR },
    { NEWSPAPER, DOUBLE_STAR + NEWSPAPER + DOUBLE_STAR },
    { YEARBOOKS, DOUBLE_STAR + YEARBOOKS + DOUBLE_STAR },
    { OTHER_TYPE, DOUBLE_STAR + OTHER + DOUBLE_STAR },
    { MINOR_LANG, DOUBLE_STAR + MINOR_LANG + DOUBLE_STAR },
    { CASE_JUDGMENT, DOUBLE_STAR + CASE_JUDGMENT + DOUBLE_STAR },
    { LAW, DOUBLE_STAR + LAW + DOUBLE_STAR },
    { ARCHIVES, DOUBLE_STAR + ARCHIVES + DOUBLE_STAR },
};
MyGlobal::MyGlobal()
{

}
