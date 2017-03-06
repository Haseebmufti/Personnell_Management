#ifndef N3_SALESMAN_H
#define N3_SALESMAN_H

#include <QDialog>
#include "frontpage.h"                        // Including class of main from which different function and variables will be called


namespace Ui {
class N3_salesman;
}

class N3_salesman : public QDialog
{
    Q_OBJECT

public:
    explicit N3_salesman(QWidget *parent = 0);
    ~N3_salesman();

private slots:
    void on_sales_saveButton_clicked();

    void on_sales_updateButton_clicked();

    void on_sales_deleteButton_clicked();

    void on_sales_loadButton_clicked();

private:
    Ui::N3_salesman *ui;
};

#endif // N3_SALESMAN_H
