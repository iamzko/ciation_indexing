#ifndef MYHIGHLIGHTER_H
#define MYHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QTextDocument>
#include <QVector>

class MyHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    enum FORMAT_TEXT_TYPE {
        INDEXING_SYMBOLS,
        NORMAL_TEXT,
        ARTICLE_TYPES,
    };
    explicit MyHighlighter(QTextDocument* parent = nullptr);
    bool set_format_rules(FORMAT_TEXT_TYPE type, QTextCharFormat format);

private:
    void init_rules_regular_pattern();

protected:
    void highlightBlock(const QString& text) override;

private:
    struct HighlightRule {
        FORMAT_TEXT_TYPE rule_type;
        QString regular_pattern;
        QTextCharFormat format;
    };
    QVector<HighlightRule> m_rules;
};

#endif // MYHIGHLIGHTER_H
