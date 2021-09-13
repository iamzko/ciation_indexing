#ifndef MYTEXTOBJECTINTERFACE_H
#define MYTEXTOBJECTINTERFACE_H

#include <QFont>
#include <QFontMetricsF>
#include <QObject>
#include <QTextObjectInterface>

class MyTextObjectInterface : public QObject, public QTextObjectInterface {
    Q_OBJECT
    Q_INTERFACES(QTextObjectInterface)
public:
    enum {
        CIATION_SYMBOL = QTextCharFormat::UserObject + 1,
    };
    enum OBjectProperties {
        CIATION_SYMBOL_DATA = 1,
    };
    MyTextObjectInterface();
    QSizeF intrinsicSize(QTextDocument* doc, int posInDocument, const QTextFormat& format) override;
    void drawObject(QPainter* painter, const QRectF& rect, QTextDocument* doc, int posInDocument, const QTextFormat& format) override;

private:
    QFontMetricsF* m_font_mf;
    QFont m_font;
    QColor m_back_color;
    QColor m_front_color;
};

#endif // MYTEXTOBJECTINTERFACE_H
