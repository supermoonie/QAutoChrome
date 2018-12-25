#include "qautochrome.h"

QAutoChrome::QAutoChrome(QString host, int port, QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager(this);
    QNetworkRequest request;
    QString url = QString("http://%1:%2/json").arg(host).arg(port);
    qDebug() << url;
    request.setUrl(QUrl(url));
    reply = manager->get(request);
    connect(reply, &QNetworkReply::readyRead, [=](){
        QString jsonText = QString(reply->readAll());
        qDebug() << jsonText;
    });
    connect(reply, &QNetworkReply::finished, [=](){
        reply->deleteLater();
        reply = 0;
    });
}

QAutoChrome::~QAutoChrome()
{

}

