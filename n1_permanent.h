#ifndef N1_PERMANENT_H
#define N1_PERMANENT_H

#include <QDialog>
#include "frontpage.h"                        // Including class of main from which different function and variables will be called

namespace Ui {
class N1_permanent;
}

class N1_permanent : public QDialog
{
    Q_OBJECT

public:
    explicit N1_permanent(QWidget *parent = 0);
    ~N1_permanent();

private slots:
    void on_permanent_saveButton_clicked();

    void on_permanent_updateButton_clicked();

    void on_permaent_deleteButton_clicked();

    void on_permanent_loadButton_clicked();

private:
    Ui::N1_permanent *ui;
};

#endif // N1_PERMANENT_H
