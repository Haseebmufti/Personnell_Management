#include "n3_salesman.h"
#include "ui_n3_salesman.h"

N3_salesman::N3_salesman(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::N3_salesman)
{
    ui->setupUi(this);
    FrontPage conn;
    // condition -> to check if the connection with the database
    if(!conn.connectionOpen())
        ui->sales_connLabel->setText("Database Dissconnected ...");
    else
        ui->sales_connLabel->setText("Database Connected ...");
}

N3_salesman::~N3_salesman()
{
    delete ui;
}

void N3_salesman::on_sales_saveButton_clicked()
{
    FrontPage conn;
    int employID,employWrkHrs,employPsold;
    double employSalary,X,Y;
    QString employFamily,employFirst,employSSN;

    employID = ui->lineEdit_employIDsals->text().toInt();
    employFamily = ui->lineEdit_famName->text();
    employFirst = ui->lineEdit_fstName->text();
    employSSN = ui->lineEdit_SSN->text();
    employPsold = ui->lineEdit_prdSold->text().toInt();
    employWrkHrs = ui->lineEdit_wrkHrs->text().toInt();

    //  Calcuation to decide wage where 22 = days, 10.3 = per hour income  //
    //   1% bonus per Product, work hour per day * product sold percentage //
    X = ((employWrkHrs*10.3)*22);
    Y = ((X*employPsold)/100);
    employSalary = (X+Y);
    // =================================================================== //

    if(!conn.connectionOpen()){
            qDebug()<<"Failed to connect to database save";                    // the contract and sales section are almost identically same
                                                                                // the only few calculation differncess are already highlighted
            return; }

        conn.connectionOpen();
        QSqlQuery Qry;
        Qry.prepare("INSERT INTO sales (EmployeeID,FamilyName,FirstName,SSNumber,PrdtSold,WorkHrsDay,MonthlySalary) VALUES (?,?,?,?,?,?,?)");
        Qry.addBindValue(employID);
        Qry.addBindValue(employFamily);
        Qry.addBindValue(employFirst);
        Qry.addBindValue(employSSN);
        Qry.addBindValue(employPsold);
        Qry.addBindValue(employWrkHrs);
        Qry.addBindValue(employSalary);

        if(Qry.exec()){
        QMessageBox::information(this,tr("SAVE"),tr("Entry successfully saved !"));
        conn.connectionClose();}
        else {
        QMessageBox::critical(this,tr("ERROR..."),Qry.lastError().text());
        }

}

void N3_salesman::on_sales_updateButton_clicked()
{
    FrontPage conn;

    QString employFamily,employFirst,employSSN;

    if(!conn.connectionOpen()){
            qDebug()<<"Failed to connect to database update";
            return; }

    conn.connectionOpen();
    QSqlQuery Qry;
    Qry.prepare("UPDATE sales SET FamilyName=:employFamily, FirstName=:employFirst, SSNumber=:employSSN, PrdtSold=:employPsold, WorkHrsDay=:employWrkHrs WHERE EmployeeID=:employID");

    Qry.bindValue(":employID",ui->lineEdit_employIDsals->text().toInt());
    Qry.bindValue(":employFamily",ui->lineEdit_famName->text());
    Qry.bindValue(":employFirst", ui->lineEdit_fstName->text());
    Qry.bindValue(":employSSN", ui->lineEdit_SSN->text());
    Qry.bindValue(":employPsold" ,ui->lineEdit_prdSold->text().toInt());
    Qry.bindValue(":employWrkHrs" ,ui->lineEdit_wrkHrs->text().toInt());


    if(Qry.exec()){
        QMessageBox::information(this,tr("EDIT"),tr("Updated successfully !"));
        conn.connectionClose();
        }
    else {
        QMessageBox::critical(this,tr("ERROR..."),Qry.lastError().text());
    }

}

void N3_salesman::on_sales_deleteButton_clicked()
{
    FrontPage conn;
    QString employFamily,employFirst,employSSN,employID,employWrkHrs;
    employID = ui->lineEdit_employIDsals->text();

    if(!conn.connectionOpen()){
            qDebug()<<"Failed to connect to database update";
            return; }

    conn.connectionOpen();
    QSqlQuery Qry;
    Qry.prepare("DELETE FROM sales WHERE EmployeeID='"+employID+"'");

    if(Qry.exec()){
        QMessageBox::information(this,tr("DELETE"),tr("Information Deleted !"));
        conn.connectionClose();
        }
    else {
        QMessageBox::critical(this,tr("ERROR..."),Qry.lastError().text());
    }

}

void N3_salesman::on_sales_loadButton_clicked()
{
    FrontPage conn;
    QSqlQueryModel *modal = new QSqlQueryModel();
    conn.connectionOpen();
    QSqlQuery* Qry = new QSqlQuery(conn.employeeData);
    Qry->prepare("select * from sales");
    Qry->exec();
    modal->setQuery(*Qry);
    ui->tableView_sales->setModel(modal);
    qDebug() << (modal->rowCount());
}
