#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H


#include <QMainWindow>
#include <QMessageBox>
#include <QMediaPlayer>
#include <QPushButton>
#include <QTimer>
#include <QPainter>
#include <QList>

struct Note {
    int x;
    int y;
    int width;
    int height;
    QColor color;
};

struct NoteData {
    qint64 time; // 音符出现的时间（毫秒）
    int x;       // 音符的横坐标
    bool generated; // 是否已生成
};

namespace Ui {
class gamewindow;
}

class gamewindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit gamewindow(QWidget *parent = nullptr);
     QMediaPlayer *musicplayer=new QMediaPlayer;
    ~gamewindow();

private:
    Ui::gamewindow *ui;

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void startGame();
    void updateGame();


protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    QTimer *gameTimer;
    QList<Note> notes;   
    QList<NoteData> noteDataList; // 音符数据


    void updateGameLogic();
    void drawNotes(QPainter *painter);

};

#endif // GAMEWINDOW_H
