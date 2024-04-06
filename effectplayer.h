#ifndef EFFECTPLAYER_H
#define EFFECTPLAYER_H

#include <QObject>
#include <QCoreApplication>
#include <QSoundEffect>
#include <QThread>
class EffectPlayer : public QObject
{
    Q_OBJECT
public:
    EffectPlayer(QObject* parent = nullptr)
        : QObject(parent)
    {
        m_thread = new QThread(this);
        moveToThread(m_thread);
        m_thread->start();
    }

    ~EffectPlayer()
    {
        m_thread->quit();
        m_thread->wait();
    }

public slots:
    void playSound(const QString& soundFilePath)
    {
        QSoundEffect soundEffect;
        soundEffect.setSource(QUrl::fromLocalFile(soundFilePath));
        soundEffect.setVolume(1.0);
        soundEffect.play();

        // 等待音效播放完成
        QThread::sleep(500);

        // 发送信号告知音效播放完成
        emit soundFinished();
    }

signals:
    void soundFinished();

private:
    QThread* m_thread;
};


#endif // EFFECTPLAYER_H
