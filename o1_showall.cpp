#include "o1_showall.h"
#include "ui_o1_showall.h"
#include "frontpage.h"

O1_showall::O1_showall(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::O1_showall)
{
    ui->setupUi(this);
    FrontPage conn;
    // condition -> to check if the connection with the database
    if(!conn.connectionOpen())
        ui->showall_connLabel->setText("Database Dissconnected ...");
    else
        ui->showall_connLabel->setText("Database Connected ...");
}

O1_showall::~O1_showall()
{
    delete ui;
}

void O1_showall::on_showall_loadButton_clicked()
{
    FrontPage conn;                                            // It is a custom function which connects and disconnects the UI to database
    QSqlQueryModel *modal = new QSqlQueryModel();              // The text in the bottom of screen shows it.
    conn.connectionOpen();
    QSqlQuery* Qry = new QSqlQuery(conn.employeeData);
    Qry->prepare("SELECT * FROM permanent");
    Qry->exec();
    modal->setQuery(*Qry);
    ui->permanent_tableView->setModel(modal);                  // Here using query to print all inforamtion from the table in the tableView
    qDebug() << (modal->rowCount());

    Qry->prepare("SELECT * FROM contract");
    Qry->exec();
    modal->setQuery(*Qry);
    ui->contract_tableView->setModel(modal);
    qDebug() << (modal->rowCount());

    Qry->prepare("SELECT * FROM sales");
    Qry->exec();
    modal->setQuery(*Qry);
    ui->sales_tableView->setModel(modal);
    conn.connectionClose();
    qDebug() << (modal->rowCount());
}

void O1_showall::on_showall_closeButton_clicked()
{
     this->close();
}
