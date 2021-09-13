#include "mytextobjectinterface.h"
#include <QPainter>

MyTextObjectInterface::MyTextObjectInterface()
{
    m_font.setFamily(u8"宋体");
    m_font.setPointSize(9);
    m_font_mf = new QFontMetricsF(m_font);
    m_back_color = QColor(Qt::black);
    m_front_color = QColor(Qt::green);
}

QSizeF MyTextObjectInterface::intrinsicSize(QTextDocument* doc, int posInDocument, const QTextFormat& format)
{
    Q_UNUSED(doc)
    Q_UNUSED(posInDocument)
    auto text = format.property(CIATION_SYMBOL_DATA).toString();
    return QSizeF(m_font_mf->horizontalAdvance(text), m_font_mf->height());
}

void MyTextObjectInterface::drawObject(QPainter* painter, const QRectF& rect, QTextDocument* doc, int posInDocument, const QTextFormat& format)
{
    Q_UNUSED(doc)
    Q_UNUSED(posInDocument)
    QString text = format.property(CIATION_SYMBOL_DATA).toString();
    painter->fillRect(rect, QBrush(m_back_color));
    painter->setPen(m_front_color);
    painter->drawText(rect, text);
}
