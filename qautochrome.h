#ifndef QAUTOCHROME_H
#define QAUTOCHROME_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

class QAutoChrome : public QObject
{
    Q_OBJECT
public:
    explicit QAutoChrome(QString host = "127.0.0.1", int port = 9222, QObject *parent = 0);
    ~QAutoChrome();

private:
    QNetworkAccessManager* manager;
    QNetworkReply *reply;
    QString webSocketDebuggerUrl;
    QString targetId;

signals:

public slots:
};

#endif // QAUTOCHROME_H
