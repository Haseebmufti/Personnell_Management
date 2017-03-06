#ifndef O1_SHOWALL_H
#define O1_SHOWALL_H

#include <QDialog>
#include "frontpage.h"
#include "n1_permanent.h"                       // For class named permanent (monthly salary)
#include "n2_contract.h"                        // For class named contract  (hourly salary)
#include "n3_salesman.h"                        // For class named salesman  (bonus based salary)

namespace Ui {
class O1_showall;
}

class O1_showall : public QDialog
{
    Q_OBJECT

public:
    explicit O1_showall(QWidget *parent = 0);
    ~O1_showall();

private slots:
    void on_showall_loadButton_clicked();

    void on_showall_closeButton_clicked();

private:
    Ui::O1_showall *ui;
};

#endif // O1_SHOWALL_H
