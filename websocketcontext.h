#ifndef WEBSOCKETCONTEXT_H
#define WEBSOCKETCONTEXT_H

#include <QObject>
#include <QJsonObject>
#include <QTimer>
#include <QEventLoop>

class WebsocketContext : public QObject
{
    Q_OBJECT
public:
    explicit WebsocketContext(QObject *parent = 0);
    ~WebsocketContext();
    QJsonObject data;

private:
    QTimer timer;
    QEventLoop loop;

signals:

public slots:
};

#endif // WEBSOCKETCONTEXT_H
