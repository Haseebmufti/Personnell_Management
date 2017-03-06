#include "n2_contract.h"
#include "ui_n2_contract.h"                     // the contract and sales section are almost identically same
                                                // the only few calculation differncess are already highlighted
N2_contract::N2_contract(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::N2_contract)
{
    ui->setupUi(this);
    FrontPage conn;
    // condition -> to check if the connection with the database
    if(!conn.connectionOpen())
        ui->contract_connLabel->setText("Database Dissconnected ...");
    else
        ui->contract_connLabel->setText("Database Connected ...");
}

N2_contract::~N2_contract()
{
    delete ui;
}

void N2_contract::on_contract_saveButton_clicked()
{
    FrontPage conn;
    int employID,employWrkHrs;
    double employSalary;
    QString employFamily,employFirst,employSSN;

    employID = ui->lineEdit_employIDcont->text().toInt();
    employFamily = ui->lineEdit_famName->text();
    employFirst = ui->lineEdit_fstName->text();
    employSSN = ui->lineEdit_SSN->text();
    employWrkHrs = ui->lineEdit_Workhrs->text().toInt();

    //  Calcuation to decide wage where 22 = days, 10.3 = per hour income //
    employSalary = ((employWrkHrs*10.3)*22);
    // ============================================== //

    if(!conn.connectionOpen()){
            qDebug()<<"Failed to connect to database save";
            return; }

        conn.connectionOpen();
        QSqlQuery Qry;
        Qry.prepare("INSERT INTO contract (EmployeeID,FamilyName,FirstName,SSNumber,WorkHrsDay,MonthlySalary) VALUES (?,?,?,?,?,?)");
        Qry.addBindValue(employID);
        Qry.addBindValue(employFamily);
        Qry.addBindValue(employFirst);
        Qry.addBindValue(employSSN);
        Qry.addBindValue(employWrkHrs);
        Qry.addBindValue(employSalary);

        if(Qry.exec()){
        QMessageBox::information(this,tr("SAVE"),tr("Entry successfully saved !"));
        conn.connectionClose();}
        else {
        QMessageBox::critical(this,tr("ERROR..."),Qry.lastError().text());
        }

}

void N2_contract::on_contract_updateButton_clicked()
{
    FrontPage conn;

    QString employFamily,employFirst,employSSN;

    if(!conn.connectionOpen()){
            qDebug()<<"Failed to connect to database update";
            return; }

    conn.connectionOpen();
    QSqlQuery Qry;
    Qry.prepare("UPDATE contract SET FamilyName=:employFamily, FirstName=:employFirst, SSNumber=:employSSN, WorkHrsDay=:employWrkHrs WHERE EmployeeID=:employID");

    Qry.bindValue(":employID",ui->lineEdit_employIDcont->text().toInt());
    Qry.bindValue(":employFamily",ui->lineEdit_famName->text());
    Qry.bindValue(":employFirst", ui->lineEdit_fstName->text());
    Qry.bindValue(":employSSN", ui->lineEdit_SSN->text());
    Qry.bindValue(":employWrkHrs" ,ui->lineEdit_Workhrs->text().toInt());


    if(Qry.exec()){
        QMessageBox::information(this,tr("EDIT"),tr("Updated successfully !"));
        conn.connectionClose();
        }
    else {
        QMessageBox::critical(this,tr("ERROR..."),Qry.lastError().text());
    }

}

void N2_contract::on_contract_deleteButton_clicked()
{
    FrontPage conn;
    QString employFamily,employFirst,employSSN,employID,employWrkHrs;
    employID = ui->lineEdit_employIDcont->text();

    if(!conn.connectionOpen()){
            qDebug()<<"Failed to connect to database update";
            return; }

    conn.connectionOpen();
    QSqlQuery Qry;
    Qry.prepare("DELETE FROM contract WHERE EmployeeID='"+employID+"'");

    if(Qry.exec()){
        QMessageBox::information(this,tr("DELETE"),tr("Information Deleted !"));
        conn.connectionClose();
        }
    else {
        QMessageBox::critical(this,tr("ERROR..."),Qry.lastError().text());
    }

}

void N2_contract::on_ontract_loadButton_clicked()
{
    FrontPage conn;
    QSqlQueryModel *modal = new QSqlQueryModel();
    conn.connectionOpen();
    QSqlQuery* Qry = new QSqlQuery(conn.employeeData);
    Qry->prepare("select * from contract");
    Qry->exec();
    modal->setQuery(*Qry);
    ui->tableView_contract->setModel(modal);
    qDebug() << (modal->rowCount());

}
