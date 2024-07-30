#ifndef GAMEOVERVIEWWIDGET_H
#define GAMEOVERVIEWWIDGET_H

#include <QWidget>
#include <QPainter>

class GameOverviewWidget : public QWidget
{
    Q_OBJECT

public:
    GameOverviewWidget(QWidget *parent = nullptr);
    void setText(const QString &newText);
    void setFillColor(const QColor &newFillColor);
    void setTextColor(const QColor &newTextColor);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QString text;
    QColor fillColor;
    QColor textColor;
};

#endif // GAMEOVERVIEWWIDGET_H
