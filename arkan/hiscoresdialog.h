#ifndef HISCORESDIALOG_H
#define HISCORESDIALOG_H

#include <QtGui>

class MainWindow;

class HiscoresDialog : public QDialog {
    Q_OBJECT

    MainWindow *mainWindow;
    QPushButton *backButton;
    QPushButton *clearButton;

    void paintEvent(QPaintEvent *event);

private slots:
    void clear();

public:
    HiscoresDialog(MainWindow *mainWindow);
};

#endif // HISCORESDIALOG_H
