#ifndef WEBSOCKETADAPTER_H
#define WEBSOCKETADAPTER_H

#include <QObject>
#include <QWebSocket>
#include <QtConcurrent/QtConcurrentMap>

class WebSocketAdapter : public QWebSocket
{
    Q_OBJECT
public:
    explicit WebSocketAdapter(const QString &origin = QString(), QWebSocketProtocol::Version version = QWebSocketProtocol::VersionLatest, QObject *parent = nullptr);
    ~WebSocketAdapter();

signals:

public slots:
};

#endif // WEBSOCKETADAPTER_H
