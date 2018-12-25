#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QObject>
#include <QProcess>

class Launcher : public QObject
{
    Q_OBJECT
public:
    explicit Launcher(QString path = QString(), int port = 9222, QStringList otherArgs = QStringList(), QObject *parent = 0);

public:
    static QStringList DEFAULT_ARGS;

private:
    QProcess* chromeProcess;

signals:

public slots:
};

#endif // LAUNCHER_H
