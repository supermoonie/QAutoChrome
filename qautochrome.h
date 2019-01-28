#ifndef QAUTOCHROME_H
#define QAUTOCHROME_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtWebSockets/QWebSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QAtomicInteger>
#include "launcher.h"

class QAutoChrome : public QObject
{
    Q_OBJECT
public:
    explicit QAutoChrome(QObject *parent = 0);
    ~QAutoChrome();
    bool setChromePath(QString & chromePath);
    bool setHost(QString host = "127.0.0.1");
    bool setPort(int port = 9222);
    void start();
    QJsonObject send(QJsonObject& json);

private:
    QAtomicInteger<qint64>* count;
    QString chromePath;
    QString host;
    int port;
    QString webSocketDebuggerUrl;
    QString targetId;
    QWebSocket* webSocket;
    Launcher* launcher;

signals:

public slots:

private slots:

};

#endif // QAUTOCHROME_H
