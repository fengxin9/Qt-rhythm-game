#ifndef MODE_H
#define MODE_H

#include <QDialog>
#include <gamewindow.h>

namespace Ui {
class mode;
}

class mode : public QDialog
{
    Q_OBJECT

public:
    explicit mode(QWidget *parent = nullptr);
    ~mode();

private slots:
    void on_pushButton_clicked();

    void on_radioButton_toggled(bool checked);

    void on_radioButton_2_toggled(bool checked);

private:
    Ui::mode *ui;
    gamewindow *g=new gamewindow;
};

#endif // MODE_H
