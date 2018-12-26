#include "launcher.h"

Launcher::Launcher(QString path, int port, QStringList otherArgs, QObject *parent) : QObject(parent)
{
    if(path.isNull() || path.isEmpty()) {
        return;
    }
    chromeProcess = new QProcess(this);
    QStringList args;
    args << QString("--remote-debugging-port=%1").arg(port) << DEFAULT_ARGS << otherArgs;
    chromeProcess->setArguments(args);
    chromeProcess->start(path, args, QIODevice::NotOpen);
    chromeProcess->waitForStarted(-1);
}

QStringList Launcher::DEFAULT_ARGS = QStringList()
        << "--disable-translate" << "--disable-extensions" << "--disable-background-networking"
        << "--safebrowsing-disable-auto-update" << "--disable-sync" << "--metrics-recording-only"
        << "--disable-default-apps" << "--mute-audio" << "--no-first-run" << "--no-default-browser-check"
        << "--disable-plugin-power-saver" << "--disable-popup-blocking" << "--disable-background-timer-throttling"
        << "--disable-breakpad" << "--disable-dev-shm-usage" << "--disable-hang-monitor"
        << "--disable-client-side-phishing-detection" << "--disable-ipc-flooding-protection"
        << "--disable-prompt-on-repost" << "--disable-renderer-backgrounding"
        << "--password-store=basic" << "--use-mock-keychain" << "--disable-infobars" << "--process-per-tab"
        << "about:blank" << "--remote-debugging-address=127.0.0.1";
