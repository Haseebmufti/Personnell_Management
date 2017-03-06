#include "frontpage.h"
#include "ui_frontpage.h"

FrontPage::FrontPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FrontPage)
{
    ui->setupUi(this);

    // Function call from header file
    // condition -> to check if the connection with the database
    if(!connectionOpen())
        ui->connectionLabel->setText("Database Dissconnected ...");
    else
        ui->connectionLabel->setText("Database Connected ...");
}

FrontPage::~FrontPage()
{
    delete ui;
}

void FrontPage::on_nextButton_clicked()                         // action when Next button is clicked in cominatiob with the radio button
// Condition for when the radio button is used in the combination

{

    if(ui->permanent_radioButton->isChecked()){
        this->hide();                                          // to hide the prevoius window when the new window is open
        N1_permanent ptrPermanent;                             // N1_permanent opens new window for permanent category
        ptrPermanent.setModal(true);
        ptrPermanent.exec();
    }
    else if(ui->contract_radioButton->isChecked()){
        this->hide();
        N2_contract ptrContract;                               // N2_contractt opens new window for contract category
        ptrContract.setModal(true);
        ptrContract.exec();
    }
    else if(ui->sales_radioButton->isChecked()){
        this->hide();
        N3_salesman ptrSalesman;                               // N3_salesman opens new window for salesperson category
        ptrSalesman.setModal(true);
        ptrSalesman.exec();
    }
    else if(ui->showall_radioButton->isChecked()){
        this->hide();
        O1_showall ptrShowall;                                 // O1_showall opens new window for showing all tables
        ptrShowall.setModal(true);
        ptrShowall.exec();
    }
    else {QMessageBox::critical(this,"ERROR","No option is selected");   // for the case when Next is clicked without seleting an option
    }
}

void FrontPage::on_quitButton_clicked()                        // action when Quit button is clicked
{
    this->close();                                             // closes the program when Quit button is clicked
}
