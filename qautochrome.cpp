#include "qautochrome.h"

QAutoChrome::QAutoChrome(QObject *parent) : QObject(parent),
  host("127.0.0.1"),
  port(9222)
{

}

QAutoChrome::~QAutoChrome()
{

}

bool QAutoChrome::setChromePath(QString &chromePath) {
    if(chromePath.isNull() || chromePath.isEmpty()) {
        return false;
    }
    this->chromePath = chromePath;
    return true;
}

bool QAutoChrome::setHost(QString host) {
    if(host.isNull() || host.isNull()) {
        return false;
    }
    this->host = host;
    return true;
}

bool QAutoChrome::setPort(int port) {
    if(port <= 0) {
        return false;
    }
    this->port = port;
    return true;
}

void QAutoChrome::start() {
    launcher = new Launcher(this->chromePath, port, QStringList(), this);
    manager = new QNetworkAccessManager(this);
    QNetworkRequest request;
    QString url = QString("http://%1:%2/json").arg(host).arg(port);
    qDebug() << url;
    request.setUrl(QUrl(url));
    reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, this, &QAutoChrome::onReplyFinished);
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
            break;
        }
    }
    reply->deleteLater();
    reply = 0;
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
}
