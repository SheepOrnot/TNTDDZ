#ifndef BACKGROUNDWIDGET_H
#define BACKGROUNDWIDGET_H

#include <QWidget>
#include <QMovie>
#include <QTimer>
#include <QPainter>

class BackgroundWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BackgroundWidget(QWidget *parent = nullptr);
    void setGifBackground(const QString &gifFilePath);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QMovie *m_movie;
    QTimer *m_timer;
};
#endif // BACKGROUNDWIDGET_H

/*调用方法*/
//BackgroundWidget *backgroundWidget = new BackgroundWidget(this);
//backgroundWidget->setGifBackground(":/path/to/background/image.gif");
