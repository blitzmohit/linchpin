#ifndef TIMER
#define TIMER

#include <QObject>
#include <QElapsedTimer>
#include <QDebug>
class Timer : public QObject {
    Q_OBJECT
public:
    explicit Timer(QObject *parent = 0): QObject(parent) {}
public slots:
    void start() {
        time.start();
    }
    void stop() {
        qCritical()<<"time is "<<time.elapsed();
        emit elapsed(time.elapsed());
    }
signals:
    void elapsed(int msec);

private:
    QElapsedTimer time;
};
#endif // TIMER
