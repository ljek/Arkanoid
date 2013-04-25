#include <QtGui/QApplication>
#include "mainwindow.h"

#if defined(Q_WS_QWS)
// for Qt Embedded (e.g., Ben NanoNote)
#include <QtGui/QWSServer>
#endif

#include <QtGui/QApplication>

class MyApplication : public QApplication {

protected:
    MainWindow *mainWindow;

    bool event(QEvent *event);

public:
    MyApplication(int argc, char *argv[]) : QApplication(argc, argv), mainWindow(NULL) {
    }

    void setMainWindow(MainWindow *mainWindow) {
        this->mainWindow = mainWindow;
    }
};

bool MyApplication::event(QEvent *event) {
    if( event->type() == QEvent::ApplicationActivate ) {
        qDebug("application activated");
        if( mainWindow != NULL ) {
            mainWindow->startTimer();
        }
    }
    else if( event->type() == QEvent::ApplicationDeactivate ) {
        qDebug("application deactivated");
        if( mainWindow != NULL ) {
            mainWindow->stopTimer();
            mainWindow->pause(); // automatically pause when application goes inactive
        }
    }
    return QApplication::event(event);
}

int main(int argc, char *argv[])
{
    MyApplication a(argc, argv);
    QCoreApplication::setOrganizationName("1363_Team");
    QCoreApplication::setApplicationName("Arkanoid Game");
    MainWindow w;
    w.setOrientation(MainWindow::ScreenOrientationLockLandscape);
    w.showExpanded();
#if defined(Q_WS_QWS)
    QWSServer::setCursorVisible(false);
#endif
    Gamestate *gamestate = new OptionsGamestate(&w);
    w.setGamestate(gamestate);

    a.setMainWindow(&w);

    return a.exec();
}
