#ifndef N2_CONTRACT_H
#define N2_CONTRACT_H

#include <QDialog>
#include "frontpage.h"                        // Including class of main from which different function and variables will be called


namespace Ui {
class N2_contract;
}

class N2_contract : public QDialog
{
    Q_OBJECT

public:
    explicit N2_contract(QWidget *parent = 0);
    ~N2_contract();

private slots:
    void on_contract_saveButton_clicked();

    void on_contract_updateButton_clicked();

    void on_contract_deleteButton_clicked();

    void on_ontract_loadButton_clicked();

private:
    Ui::N2_contract *ui;
};

#endif // N2_CONTRACT_H
