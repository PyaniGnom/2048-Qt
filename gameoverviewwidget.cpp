#include "gameoverviewwidget.h"

GameOverviewWidget::GameOverviewWidget(QWidget *parent) : QWidget(parent), text("")
{
    //setAttribute(Qt::WA_TransparentForMouseEvents);     // делает прозрачным для событий мыши
    setAttribute(Qt::WA_AlwaysStackOnTop);
    setVisible(false);  // изначально невидим
}

void GameOverviewWidget::setText(const QString &newText)
{
    text = newText;
    update();
}

void GameOverviewWidget::setFillColor(const QColor &newFillColor)
{
    fillColor = newFillColor;
    update();
}

void GameOverviewWidget::setTextColor(const QColor &newTextColor)
{
    textColor = newTextColor;
    update();
}

void GameOverviewWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setBrush(fillColor);
    painter.setPen(Qt::NoPen);      // без внешней обводки

    QRect rect(0, 0, width(), height());
    painter.drawRoundedRect(rect, 13, 13);

    // Настраиваем шрифт и цвет текста
    painter.setPen(textColor);
    QFont font("Open Sans", 44, 69, false);
    painter.setFont(font);

    // Текст по центру
    painter.drawText(rect, Qt::AlignCenter, text);
}


