#ifndef PAGE_H
#define PAGE_H

#include <QObject>

class NavigateResult : public QObject {

public:
    QString frameId;
    QString loaderId;
    QString errorText;
};

class Page : public QObject
{
    Q_OBJECT
public:
    explicit Page(QObject *parent = 0);
    enum TransitionType{
        none,
        link,
        typed,
        address_bar,
        auto_bookmark,
        auto_subframe,
        manual_subframe,
        generated,
        auto_toplevel,
        form_submit,
        reload,
        keyword,
        keyword_generated,
        other
    };
    NavigateResult navigate(const QString& url, const QString& referrer = QString(), const TransitionType transitionType = TransitionType::none, const QString& frameId = QString());

private:
    bool enable;

signals:

public slots:
};

#endif // PAGE_H
