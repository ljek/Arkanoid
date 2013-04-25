#include "hiscoresdialog.h"
#include "mainwindow.h"

HiscoresDialog::HiscoresDialog(MainWindow *mainWindow) : QDialog(mainWindow), mainWindow(mainWindow), backButton(NULL), clearButton(NULL) {
    QVBoxLayout *layout = new QVBoxLayout();
    this->setLayout(layout);

    layout->addStretch();
    {
        QHBoxLayout *h_layout = new QHBoxLayout();
        layout->addLayout(h_layout);

        backButton = new QPushButton(tr("Back"));
        h_layout->addWidget(backButton);
        connect(backButton, SIGNAL(clicked()), this, SLOT(close()));

        clearButton = new QPushButton(tr("Clear"));
        h_layout->addWidget(clearButton);
        connect(clearButton, SIGNAL(clicked()), this, SLOT(clear()));
    }

    this->setAttribute(Qt::WA_LockLandscapeOrientation); // important for Symbian/Simulator!
    this->setWindowFlags( this->windowFlags() | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint );
}

void HiscoresDialog::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    //qDebug("%d x %d", width(), height());
    painter.fillRect(0, 0, width(), height(), Qt::black);
    painter.setBrush(QBrush(Qt::white));
    //const int name_x = 32, level_x = 300, score_x = 360;
    QFont font = painter.font();
    int button_h = this->backButton->height() + 4;
    //qDebug("button_h = %d", button_h);
    int ydiff = ( this->height() - button_h ) / 12;
    int font_height = ydiff-2;
    if( font_height <= 0 )
        font_height = 1;
    //qDebug("font height: %d", font_height);
    font.setPixelSize(font_height);
    painter.setFont(font);
    //const int ydiff = 24;

    //const int name_x = 32;
    const int name_x = 2 * font_height;
    const int level_x = 0.5 * width();
    const int score_x = 0.75 * width();

    int ypos = 0;
    painter.setPen(QPen(Qt::white));
    painter.drawText(name_x, ypos+ydiff, "NAME");
    //painter.drawText(name_x, ypos, level_x - name_x, ydiff, NULL, "NAME");
    painter.drawText(level_x, ypos+ydiff, "LEVEL");
    painter.drawText(score_x, ypos+ydiff, "SCORE");
    ypos += ydiff;
    int c=0;
    //qDebug("%d hiscores\n", mainWindow->getHiscores().size());
    foreach(Hiscore hiscore, mainWindow->getHiscores()) {
        painter.drawText(0, ypos, name_x - 4, ydiff, Qt::AlignRight, QString::number(c+1));
        painter.drawText(name_x, ypos, level_x - name_x - 4, ydiff, NULL, hiscore.getName()); // truncate long names
        painter.drawText(level_x, ypos, score_x - level_x - 4, ydiff, NULL, QString::number(hiscore.getLevel()));
        painter.drawText(score_x, ypos, width() - score_x - 4, ydiff, NULL, QString::number(hiscore.getScore()));
        ypos += ydiff;
        c++;
    }
}

void HiscoresDialog::clear() {
    qDebug("HiscoresDialog::clear\n");
    if( QMessageBox::question(this, "Clear Hiscores", "Are you sure you wish to clear the hiscores?", QMessageBox::Ok, QMessageBox::Cancel) == QMessageBox::Ok ) {
        mainWindow->clearHiscores();
        this->update();
    }
}
