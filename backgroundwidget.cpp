#include "backgroundwidget.h"

BackgroundWidget::BackgroundWidget(QWidget *parent)
    : QWidget(parent), m_movie(nullptr), m_timer(nullptr)
{
}

void BackgroundWidget::setGifBackground(const QString &gifFilePath)
{
    if (m_movie) {
        delete m_movie;
        m_movie = nullptr;
    }

    m_movie = new QMovie(gifFilePath, QByteArray(), this);
    m_movie->start();

    if (m_timer) {
        delete m_timer;
        m_timer = nullptr;
    }

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, [this]() {
        update();
    });

    m_timer->start(30); // 每隔30毫秒更新一次
}

void BackgroundWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    if (m_movie && m_movie->isValid()) {
        QPainter painter(this);
        QRect rect(QPoint(0, 0), size());
        painter.drawPixmap(rect, m_movie->currentPixmap());
    }
}
