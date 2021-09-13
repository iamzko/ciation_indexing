#include "myciationeditor.h"
#include "myglobal.h"
#include "mytextobjectinterface.h"
#include <QSyntaxHighlighter>
#include <QtDebug>

MyCiationEditor::MyCiationEditor(QWidget* parent)
    : QPlainTextEdit(parent)
{
    auto text_object = new MyTextObjectInterface();
    text_object->setParent(this);
    document()->documentLayout()->registerHandler(MyTextObjectInterface::CIATION_SYMBOL, text_object);
}

void MyCiationEditor::keyPressEvent(QKeyEvent* e)
{
    auto cur_cursor = textCursor();
    QTextCharFormat temp;
    bool combo = false;
    switch (e->key() + e->modifiers()) {
    case Qt::Key_S + Qt::ControlModifier:
        cur_cursor.insertText(MyGlobal::INDEXING_SYMBOLS_MAP.value(MyGlobal::CHIEF_EDITOR));
        break;
    case Qt::Key_W + Qt::ControlModifier:
        cur_cursor.insertText(MyGlobal::INDEXING_SYMBOLS_MAP.value(MyGlobal::CONFER_UNIT));
        break;
    case Qt::Key_D + Qt::ControlModifier:
        cur_cursor.insertText(MyGlobal::INDEXING_SYMBOLS_MAP.value(MyGlobal::OTHER));
        break;
    case Qt::Key_Q + Qt::ControlModifier:
        cur_cursor.insertText(MyGlobal::INDEXING_SYMBOLS_MAP.value(MyGlobal::PUBLISH_STATE));
        break;
    case Qt::Key_F + Qt::ControlModifier:
        cur_cursor.insertText(MyGlobal::INDEXING_SYMBOLS_MAP.value(MyGlobal::MOTHER_SOURCES));
        break;
    case Qt::Key_P + Qt::ControlModifier:
        cur_cursor.insertText(MyGlobal::INDEXING_SYMBOLS_MAP.value(MyGlobal::ENGLISH_CIATION_TAG));
        break;
    case Qt::Key_G + Qt::ControlModifier:
        cur_cursor.insertText(MyGlobal::INDEXING_SYMBOLS_MAP.value(MyGlobal::ELECTRONIC_EDITION));
        break;
    case Qt::Key_T + Qt::ControlModifier:
        cur_cursor.insertText(MyGlobal::INDEXING_SYMBOLS_MAP.value(MyGlobal::DO_NOT));
        break;
    case Qt::Key_Y + Qt::ControlModifier:
        cur_cursor.insertText(MyGlobal::INDEXING_SYMBOLS_MAP.value(MyGlobal::CAN_NOT));
        break;
    case Qt::Key_U + Qt::ControlModifier:
        cur_cursor.insertText(MyGlobal::INDEXING_SYMBOLS_MAP.value(MyGlobal::OTHER_INFO));
        break;
    case Qt::Key_O + Qt::ControlModifier:
        cur_cursor.insertText(MyGlobal::INDEXING_SYMBOLS_MAP.value(MyGlobal::MEETING_LOCATION));
        break;
    case Qt::Key_H + Qt::ControlModifier:
        cur_cursor.insertText(MyGlobal::INDEXING_SYMBOLS_MAP.value(MyGlobal::LANGUAGE));
        break;
    case Qt::Key_1 + Qt::ControlModifier: {
        //        cur_cursor.insertText(MyGlobal::ARTICLE_TYPES_MAP.value(MyGlobal::PERIODICALS));
        temp.setObjectType(MyTextObjectInterface::CIATION_SYMBOL);
        temp.setProperty(MyTextObjectInterface::CIATION_SYMBOL_DATA, QVariant(MyGlobal::ARTICLE_TYPES_MAP.value(MyGlobal::PERIODICALS)));
        cur_cursor.insertText(QString(QChar::ObjectReplacementCharacter), temp);
    } break;
    case Qt::Key_2 + Qt::ControlModifier:
        cur_cursor.insertText(MyGlobal::ARTICLE_TYPES_MAP.value(MyGlobal::BOOK));
        break;
    case Qt::Key_3 + Qt::ControlModifier:
        cur_cursor.insertText(MyGlobal::ARTICLE_TYPES_MAP.value(MyGlobal::MEETING_PAPER));
        break;
    case Qt::Key_4 + Qt::ControlModifier:
        cur_cursor.insertText(MyGlobal::ARTICLE_TYPES_MAP.value(MyGlobal::DISSERTATION));
        break;
    case Qt::Key_5 + Qt::ControlModifier:
        cur_cursor.insertText(MyGlobal::ARTICLE_TYPES_MAP.value(MyGlobal::REPORT));
        break;
    case Qt::Key_6 + Qt::ControlModifier:
        cur_cursor.insertText(MyGlobal::ARTICLE_TYPES_MAP.value(MyGlobal::PATENT));
        break;
    case Qt::Key_7 + Qt::ControlModifier:
        cur_cursor.insertText(MyGlobal::ARTICLE_TYPES_MAP.value(MyGlobal::STANDARD));
        break;
    case Qt::Key_8 + Qt::ControlModifier:
        cur_cursor.insertText(MyGlobal::ARTICLE_TYPES_MAP.value(MyGlobal::NEWSPAPER));
        break;
    case Qt::Key_9 + Qt::ControlModifier:
        cur_cursor.insertText(MyGlobal::ARTICLE_TYPES_MAP.value(MyGlobal::YEARBOOKS));
        break;
    case Qt::Key_0 + Qt::ControlModifier:
        cur_cursor.insertText(MyGlobal::ARTICLE_TYPES_MAP.value(MyGlobal::OTHER_TYPE));
        break;
    case Qt::Key_QuoteLeft + Qt::ControlModifier:
        cur_cursor.insertText(MyGlobal::ARTICLE_TYPES_MAP.value(MyGlobal::MINOR_LANG));
        break;
    case Qt::Key_6 + Qt::AltModifier:
        combo = true;
        cur_cursor.insertText(MyGlobal::ARTICLE_TYPES_MAP.value(MyGlobal::CASE_JUDGMENT));
        break;
    case Qt::Key_7 + Qt::AltModifier:
        combo = true;
        cur_cursor.insertText(MyGlobal::ARTICLE_TYPES_MAP.value(MyGlobal::LAW));
        break;
    case Qt::Key_8 + Qt::AltModifier:
        combo = true;
        cur_cursor.insertText(MyGlobal::ARTICLE_TYPES_MAP.value(MyGlobal::ARCHIVES));
        break;
    }
    switch (e->key()) {
    case Qt::Key_F1:
        break;
    case Qt::Key_F2:
        cur_cursor.insertText(MyGlobal::INDEXING_SYMBOLS_MAP.value(MyGlobal::AUTHOR_NAME));
        break;
    case Qt::Key_F3:
        cur_cursor.insertText(MyGlobal::INDEXING_SYMBOLS_MAP.value(MyGlobal::ARTICLE_TITLE));
        break;
    case Qt::Key_F4:
        cur_cursor.insertText(MyGlobal::INDEXING_SYMBOLS_MAP.value(MyGlobal::ARTICLE_SOURCES));
        break;
    case Qt::Key_F5:
        cur_cursor.insertText(MyGlobal::INDEXING_SYMBOLS_MAP.value(MyGlobal::MOTHER_YEAR));
        break;
    case Qt::Key_F6:
        cur_cursor.insertText(MyGlobal::INDEXING_SYMBOLS_MAP.value(MyGlobal::MOTHER_VOLUME));
        break;
    case Qt::Key_F7:
        cur_cursor.insertText(MyGlobal::INDEXING_SYMBOLS_MAP.value(MyGlobal::MOTHER_PHASE));
        break;
    case Qt::Key_F8:
        cur_cursor.insertText(MyGlobal::INDEXING_SYMBOLS_MAP.value(MyGlobal::MOTHER_PAGE));
        break;
    case Qt::Key_F9:
        cur_cursor.insertText(MyGlobal::INDEXING_SYMBOLS_MAP.value(MyGlobal::EDITION_DESCRIPTION));
        break;
    case Qt::Key_F10:
        cur_cursor.insertText(MyGlobal::INDEXING_SYMBOLS_MAP.value(MyGlobal::MOTHER_LOCATION));
        break;
    case Qt::Key_F11:
        cur_cursor.insertText(MyGlobal::INDEXING_SYMBOLS_MAP.value(MyGlobal::LANGUAGE_TRANS));
        break;
    case Qt::Key_F12:
        cur_cursor.insertText(MyGlobal::INDEXING_SYMBOLS_MAP.value(MyGlobal::MOTHER_PRESS));
        break;
    }
    setTextCursor(cur_cursor);
    if (!combo) {
        QPlainTextEdit::keyPressEvent(e);
    }
}

void MyCiationEditor::mousePressEvent(QMouseEvent* e)
{
    if (e->button() == Qt::LeftButton) {
        auto cursor = textCursor();
        auto text = cursor.selectedText();
        if (text.size() == 1) {
            auto c = text.at(0);
            //            qDebug() << c.unicode();
            qDebug() << currentCharFormat().property(MyTextObjectInterface::CIATION_SYMBOL_DATA).toString();
            //65532 占位符的unicode值
        }
    }
    QPlainTextEdit::mousePressEvent(e);
}
