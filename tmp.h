#ifndef TMP_H
#define TMP_H

#include <QDialog>

namespace Ui {
class tmp;
}

class tmp : public QDialog
{
    Q_OBJECT
    
public:
    explicit tmp(QWidget *parent = 0);
    ~tmp();
    
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::tmp *ui;
};

#endif // TMP_H
