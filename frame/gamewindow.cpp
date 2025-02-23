#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "QMessageBox"
#include "QEvent"
#include "QDebug"
#include "QPushButton"
#include "QColor"

gamewindow::gamewindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gamewindow)
{
    ui->setupUi(this);

    musicplayer=new QMediaPlayer;
    musicplayer->setMedia(QUrl("qrc:/opera.mp3"));
    musicplayer->setVolume(70);  
    //bgm

    // 初始化音符数据
        notes.append({320, 0, 70, 20,QColor(110, 120, 112, 255)}); // 添加一个音符
        notes.append({590, 0, 70, 20,QColor(110, 120, 112, 255)});  // 添加另一个音符
        notes.append({860, 0, 70, 20,QColor(110, 120, 112, 255)});
        notes.append({1130, 0, 70, 20,QColor(110, 120, 112, 255)});

        // 启动定时器
        gameTimer = new QTimer(this);
        connect(gameTimer, &QTimer::timeout, this, &gamewindow::updateGame);


}

gamewindow::~gamewindow()
{
    delete ui;
}


void gamewindow::on_pushButton_2_clicked()
{
    musicplayer->play();
    startGame();
}//开始

void gamewindow::on_pushButton_clicked()
{
   musicplayer->stop();
}//暂停

void gamewindow::startGame() {
    qDebug()<<"start";
     gameTimer->start(16); // 16ms 间隔，约 60 FPS
     updateGame();
    // 游戏启动逻辑
}

void gamewindow::updateGame() {
    updateGameLogic(); // 更新游戏逻辑
    update(); // 触发重绘
}

void gamewindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    // 只绘制音符
    drawNotes(&painter);
}

void gamewindow::updateGameLogic() {
    for (auto &note : notes) {
        note.y += 5; // 让音符下落

        // 如果音符超出屏幕范围，重置到顶部
        if (note.y > height()) {
            note.y = 0;
             qDebug()<<"updating";
        }
    }
}

void gamewindow::drawNotes(QPainter *painter) {
      // 创建线性渐变
        QLinearGradient gradient(0, 0, 0, height());
        gradient.setColorAt(0, Qt::white);   // 起始颜色
        gradient.setColorAt(1, QColor(149, 142, 108, 255));  // 结束颜色
        // 使用渐变填充背景
        painter->fillRect(rect(), gradient);

    for (const auto &note : notes) {
        QBrush noteBrush(note.color);
        painter->setBrush(noteBrush);
        QRect noteRect(note.x, note.y, note.width, note.height);
        painter->drawRect(noteRect);
    }
}


