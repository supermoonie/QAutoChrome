#include "qautochrome.h"
#include <QTimer>
#include <QEventLoop>

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

QJsonObject QAutoChrome::send(QJsonObject& json) {
    qint64 id = count->fetchAndAddOrdered(1);
    json.insert("id", id);
    QJsonDocument jsonDoc;
    jsonDoc.setObject(json);
    QString text = jsonDoc.toJson();
    qDebug() << text;
    webSocket->sendTextMessage(text);

}

void QAutoChrome::start() {
    launcher = new Launcher(this->chromePath, port, QStringList(), this);
    QNetworkAccessManager manager;
    QNetworkRequest request;
    QString url = QString("http://%1:%2/json").arg(host).arg(port);
    qDebug() << url;
    request.setUrl(QUrl(url));
    QNetworkReply *reply = manager.get(request);
    QTimer timer;
    timer.setInterval(5000);
    timer.setSingleShot(true);
    QEventLoop loop;
    connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    timer.start();
    loop.exec();
    if(timer.isActive()) {
        timer.stop();
        QString jsonText = QString(reply->readAll());
        reply->deleteLater();
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
        if(webSocketDebuggerUrl.isNull() || webSocketDebuggerUrl.isEmpty()) {
            return;
        }
        webSocket = new QWebSocket(QString(), QWebSocketProtocol::Version13, this);
        webSocket->open(QUrl(webSocketDebuggerUrl));
        connect(webSocket, &QWebSocket::connected, &loop, &QEventLoop::quit);
        connect(webSocket, &QWebSocket::disconnected, [=](){
            qDebug() << "websocket disconnected";
            webSocket->deleteLater();
        });
        timer.start();
        loop.exec();
        if(timer.isActive()) {
            timer.stop();
            count = new QAtomicInteger<qint64>(0);
            qDebug() << "connect successed!";
        }
    } else {
        disconnect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
        reply->abort();
        reply->deleteLater();
        qDebug() << "timeout";
    }
}

