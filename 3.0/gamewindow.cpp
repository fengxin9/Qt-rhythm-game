#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "QMessageBox"
#include "QEvent"
#include "QDebug"
#include "QPushButton"
#include "QColor"
#include "QKeyEvent"
#include "QLCDNumber"

const int a=320;
const int b=590;
const int c=860;
const int d=1130;
bool ispaused=false;

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
            noteDataList.append({
 {0,a,0},{200, b,0},{400, c,0},{600,d,0},{800, a,0},{1400, b,0},{2000, c,0},{2200,d,0},{2600,c,0},{3000, b,0},{3400,a,0},//前奏第一句
 {5600,a,0},{5800, b,0},{6000, c,0},{6200,d,0},{6400, a,0},{7000, b,0},{7600, c,0},{7800,d,0},{8200,c,0},{8600, b,0},{9000,a,0},//第二句
 {9400,d,0},{9800,c,0},{10200, b,0},{10600,a,0},
 {11000,a,0},{11200,b,0},{11400,c,0},{11600,d,0},{11800, a,0},{12400, b,0},{13000, c,0},{13200,d,0},{13600,c,0},{14000, b,0},
 {14600, b,0},{14800,a,0},{15200, b,0},{15600, c,0}, //第三句
 {16800,d,0},{17000,c,0},{17200, b,0},{17400,a,0},{17600,b,0},{18200,d,0},{18800,a,0},{19000,b,0},{19600,c,0},
 {20200,a,0},{20400,b,0},{20600,d,0},{20800,b,0},{21000,c,0},{21200,a,0},{21400,d,0},{21600,b,0},
 {21700,c,0},{21900,a,0},{22100,d,0},{22300,b,0},{22500,c,0},{22700,a,0},{22900,d,0},{23100,b,0},//前奏结束
 {23300,d,0}, {24000,c,0}, {24400,b,0}, {25200,b,0}, {25600,a,0}, {26000,b,0}, {26500,c,0},//嘲笑谁恃美扬威
 {28600,d,0}, {29600,c,0}, {30000,b,0}, {30600,b,0}, {31000,a,0}, {31400,b,0}, {31900,c,0}, //没了心如何相配
 {33400,a,0}, {33800,d,0}, {34200,b,0}, {35400,c,0}, {35800,b,0},//盘铃声清脆
 {36200,b,0}, {36600,a,0}, {37000,b,0}, {37400,a,0}, {37600,b,0}, {38000,c,0}, {38200,d,0},  //帷幕间灯火幽微
 {39200,c,0}, {39600,d,0}, {39800,b,0}, {40400,c,0}, {40800,d,0}, {41000,b,0}, {41800,a,0},  {42600,b,0}, //我和你最天生一对
 {45300,d,0}, {46200,c,0}, {46800,b,0}, {47600,b,0}, {48000,a,0}, {48400,b,0}, {48800,c,0},//没了你才算原罪
 {51200,d,0}, {52200,c,0}, {52600,b,0}, {53200,b,0}, {53600,a,0}, {54000,b,0}, {54400,c,0}, //没了心才好相配
 {55800,a,0}, {56200,d,0}, {56600,b,0}, {57400,a,0}, {57700,d,0}, {57900,b,0},  //你褴褛我彩绘
 {58400,b,0}, {58800,a,0}, {59200,b,0}, {59600,a,0}, {60000,b,0}, {60400,c,0}, {60600,d,0},  //并肩行过山与水
 {61600,c,0}, {62000,d,0}, {62200,b,0}, {62800,c,0}, {63200,d,0}, {63400,b,0}, {64200,a,0},  {65000,b,0}, //你憔悴我替你明媚
 {67100,a,0}, {67500,b,0}, {67900,c,0}, {68400,d,0}, {68800,b,0}, {69200,c,0},  //是你吻开笔墨
 {69800,a,0}, {70200,d,0}, {70600,c,0}, {71100,b,0}, {71500,a,0}, {71900,c,0},  //染我眼角朱泪
 {72500,a,0}, {72900,b,0}, {73300,c,0}, {73800,b,0}, {74200,a,0}, {74600,b,0},{75100,c,0}, {75500,d,0}, {75900,c,0},  //演离合相遇悲喜为谁
 {78000,a,0}, {78400,d,0}, {78800,c,0}, {79300,b,0}, {79700,a,0}, {80000,c,0}, //他们迂回误会
 {80700,b,0}, {81100,a,0}, {81500,b,0}, {81900,a,0}, {82300,b,0},  {82800,c,0}, {83000,d,0},  //我却只由你支配
 {83800,c,0}, {84200,d,0}, {84400,b,0}, {85000,c,0}, {85400,d,0},  {85600,b,0}, {86600,a,0}, {87200,b,0}, //问世间哪有更完美
 {89000,c,0}, {89400,d,0}, {89800,b,0}, {90200,b,0}, {91200,c,0},  {91600,b,0}, {92200,a,0}, {93200,d,0}, //兰花指捻红尘似水
 {94600,c,0}, {95000,d,0}, {95400,b,0}, {95800,b,0}, {96800,c,0},  {97200,b,0}, {97800,a,0}, {98200,d,0},{98800,c,0}, //三尺红台万事如歌吹
 {100000,a,0}, {100400,b,0}, {100800,c,0}, {101200,d,0}, {101600,c,0},  {102000,b,0}, {102400,c,0}, {102800,b,0},//唱别久悲不成悲
 {103200,c,0}, {103600,b,0}, {104000,a,0}, {104300,b,0}, {104700,c,0},  {105100,d,0}, {105500,a,0}, //十分红处竟成灰
 {106100,a,0}, {106500,b,0}, {106900,c,0}, {107200,d,0}, {107500,a,0}, //愿谁记得谁
 {108000,b,0}, {108400,c,0}, {108800,d,0}, {109200,a,0}, {109800,b,0}, //最好的年岁
 {111200,b,0}, {111600,d,0}, {112000,c,0}, {112600,d,0}, {113200,a,0}, {113600,b,0},
 {114200,b,0}, {114600,d,0}, {115000,c,0}, {115600,d,0}, {116200,b,0}, {116600,a,0},
                                });


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
    startGame();
    musicplayer->play();
}//开始

void gamewindow::on_pushButton_clicked()
{
    if(ispaused){
        musicplayer->play();
        gameTimer->start();
        ispaused=false;
  }
    else
    {
       musicplayer->pause();
       gameTimer->stop();
       ispaused=true;
    }
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
     ui->scorenumber->display(score);
}

void gamewindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    // 只绘制音符
    drawNotes(&painter);
}

void gamewindow::keyPressEvent(QKeyEvent *event) {
    int key = event->key(); // 获取按下的按键

    // 遍历音符，检查是否匹配按键
    for (auto it = notes.begin(); it != notes.end(); ) {
        if (key == Qt::Key_A && (it->x == a&&it->y>=800&&it->y<=1100)) { // 按下 A 键对应 x=100 的音符
            it = notes.erase(it); // 移除音符
            score++;
            qDebug()<<"A";
        } else if (key == Qt::Key_S && (it->x == b&&it->y>=800&&it->y<=1100)) { // 按下 S 键对应 x=200 的音符
            it = notes.erase(it); // 移除音符
            score++;
            qDebug()<<"S";
        } else {
            if (key == Qt::Key_K && (it->x == c&&it->y>=800&&it->y<=1100)) {
                        it = notes.erase(it); // 移除音符
                        score++;
                        qDebug()<<"K";
                    }
            else{
                if (key == Qt::Key_L &&(it->x == d&&it->y>=800&&it->y<=1100)) {
                            it = notes.erase(it); // 移除音符
                            score++;
                            qDebug()<<"L";
                        }
                else{
                   ++it;
                }
            }
        }
    }

    update(); // 触发重绘
}

void gamewindow::updateGameLogic() {
    qint64 currentTime = musicplayer->position(); // 获取当前播放时间

    // 遍历音符数据，生成音符
    for (auto &noteData : noteDataList) {
        if (noteData.time <= currentTime && !noteData.generated) {
            notes.append({noteData.x, 0, 70, 20,QColor(110, 120, 112, 255)}); // 生成音符
            noteData.generated = true; // 标记为已生成
        }
    }
    // 更新音符位置
    for (auto &note : notes) {
        note.y += 10; // 让音符下落
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



void gamewindow::on_pushButton_3_clicked()
{
    this->close();
}
