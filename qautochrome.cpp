#include "qautochrome.h"

QAutoChrome::QAutoChrome(QString host, int port, QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager(this);
    QNetworkRequest request;
    QString url = QString("http://%1:%2/json").arg(host).arg(port);
    qDebug() << url;
    request.setUrl(QUrl(url));
    reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, this, &QAutoChrome::onReplyFinished);
    connect(reply, &QNetworkReply::finished, [=](){
        reply->deleteLater();
        reply = 0;
    });
}

QAutoChrome::~QAutoChrome()
{

}

void QAutoChrome::onReplyFinished() {
    QString jsonText = QString(reply->readAll());
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonText.toUtf8());
    QJsonArray tabArray = jsonDoc.array();
    for(int i = 0; i < tabArray.size(); i ++) {
        QJsonObject tabJson = tabArray.at(i).toObject();
        if (tabJson.value("type").toString() == "page" &&
                tabJson.value("url").toString() == "about:blank") {
            webSocketDebuggerUrl = tabJson.value("webSocketDebuggerUrl").toString();
            targetId = tabJson.value("id").toString();
            webSocket = new QWebSocket(QString(), QWebSocketProtocol::Version13, this);
            connect(webSocket, &QWebSocket::connected, [=](){
                qDebug() << "websocket connected";
            });
            connect(webSocket, &QWebSocket::disconnected, [=](){
                qDebug() << "websocket disconnected";
                webSocket->deleteLater();
                webSocket = 0;
            });
            webSocket->open(QUrl(webSocketDebuggerUrl));
            break;
        }
    }
}
