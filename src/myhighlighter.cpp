#include "myhighlighter.h"
#include "myglobal.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>
#include <QtDebug>

MyHighlighter::MyHighlighter(QTextDocument* parent)
    : QSyntaxHighlighter(parent)
{
    init_rules_regular_pattern();
}

bool MyHighlighter::set_format_rules(FORMAT_TEXT_TYPE type, QTextCharFormat format)
{
    for (auto& rule : m_rules) {
        if (rule.rule_type == type) {
            rule.format = format;
        }
    }
    return true;
}

void MyHighlighter::init_rules_regular_pattern()
{
    HighlightRule normal_text_rule;
    normal_text_rule.rule_type = FORMAT_TEXT_TYPE::NORMAL_TEXT;
    normal_text_rule.regular_pattern = QString(".*");
    normal_text_rule.format = QTextCharFormat();
    m_rules.append(normal_text_rule);
    HighlightRule indexing_symbol_rule;
    indexing_symbol_rule.rule_type = FORMAT_TEXT_TYPE::INDEXING_SYMBOLS;
    for (auto key_word : MyGlobal::INDEXING_SYMBOLS_MAP) {
        if (key_word == MyGlobal::INDEXING_SYMBOLS_MAP.value(MyGlobal::ARTICLE_SOURCES)) {
            key_word.insert(1, "\\");
            key_word.insert(0, "\\");
        }
        indexing_symbol_rule.regular_pattern.append(QString::fromUtf8(u8"(%1)").arg(key_word));
        indexing_symbol_rule.regular_pattern.append("|");
    }
    indexing_symbol_rule.regular_pattern.chop(1);
    //    qDebug() << "regular_pattern:" << indexing_symbol_rule.regular_pattern;
    indexing_symbol_rule.format = QTextCharFormat();
    m_rules.append(indexing_symbol_rule);
    HighlightRule ciation_type_rule;
    ciation_type_rule.rule_type = FORMAT_TEXT_TYPE::ARTICLE_TYPES;
    for (auto key_word : MyGlobal::ARTICLE_TYPES_MAP) {
        ciation_type_rule.regular_pattern.append(QString::fromUtf8(u8"(%1)").arg(key_word));
        ciation_type_rule.regular_pattern.append("|");
    }
    ciation_type_rule.regular_pattern.chop(1);
    //    qDebug() << "ciation_type_rule:" << ciation_type_rule.regular_pattern;
    ciation_type_rule.format = QTextCharFormat();
    m_rules.append(ciation_type_rule);
}

void MyHighlighter::highlightBlock(const QString& text)
{
//    qDebug() << text;
#if 0
    QTextCharFormat temp_format; temp_format.setFontWeight(QFont::Bold);
    temp_format.setForeground(Qt::green);
    temp_format.setBackground(Qt::yellow);
    QRegularExpression expression(QString::fromUtf8(u8"(%1)").arg(MyGlobal::INDEXING_SYMBOLS_MAP.value(MyGlobal::ARTICLE_TITLE)));
    qDebug() << QString::fromUtf8(u8"(%1)").arg(MyGlobal::INDEXING_SYMBOLS_MAP.value(MyGlobal::ARTICLE_TITLE));
    QRegularExpressionMatchIterator it = expression.globalMatch(text);
    while (it.hasNext()) {
        QRegularExpressionMatch match = it.next();
        setFormat(match.capturedStart(), match.capturedLength(), temp_format);
    }
#endif
    for (auto rule : m_rules) {
        QRegularExpression expression(rule.regular_pattern);
        auto it = expression.globalMatch(text);
        while (it.hasNext()) {
            auto match = it.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
}
