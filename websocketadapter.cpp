#include "websocketadapter.h"

WebSocketAdapter::WebSocketAdapter(const QString &origin, QWebSocketProtocol::Version version, QObject *parent) :
    QWebSocket(origin, version, parent)
{

}

WebSocketAdapter::~WebSocketAdapter()
{

}

