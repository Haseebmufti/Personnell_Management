#include "n1_permanent.h"
#include "ui_n1_permanent.h"

N1_permanent::N1_permanent(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::N1_permanent)
{
    ui->setupUi(this);
    FrontPage conn;
    // condition -> to check if the connection with the database
    if(!conn.connectionOpen())
        ui->permanent_connLabel->setText("Database Disconnected ...");
    else
        ui->permanent_connLabel->setText("Database Connected ...");
}

N1_permanent::~N1_permanent()
{
    delete ui;
}

void N1_permanent::on_permanent_saveButton_clicked()                 // Here the functionality of the Save button is defined after it takes input from user
{                                                                    // after converting the element to the required configuration.
    FrontPage conn;
    int employID;
    double employSalary;
    QString employFamily,employFirst,employSSN;

    employID = ui->lineEdit_employID->text().toInt();                 // Input data is obtained here where it is defined the Data Type to them.
    employFamily = ui->lineEdit_famName->text();
    employFirst = ui->lineEdit_fstName->text();
    employSSN = ui->lineEdit_SSN->text();
    employSalary = ui->lineEdit_salary->text().toDouble();

    if(!conn.connectionOpen()){
            qDebug()<<"Failed to connect to database save";
            return; }

        conn.connectionOpen();                                         // Query is made to here to save input data to table
        QSqlQuery Qry;
        Qry.prepare("INSERT INTO permanent (EmployeeID,FamilyName,FirstName,SSNumber,MonthlySalary) VALUES (?,?,?,?,?)");
        Qry.addBindValue(employID);
        Qry.addBindValue(employFamily);
        Qry.addBindValue(employFirst);
        Qry.addBindValue(employSSN);
        Qry.addBindValue(employSalary);

            if(Qry.exec()){                                                           // check fubnction to see if the application is working or ot
            QMessageBox::information(this,tr("SAVE"),tr("Entry successfully saved !"));
            conn.connectionClose();
            }
        else {
            QMessageBox::critical(this,tr("ERROR..."),Qry.lastError().text());
        }
}

void N1_permanent::on_permanent_updateButton_clicked()
{                                                                         // the update function is defined here
    FrontPage conn;
    QString employFamily,employFirst,employSSN;

    if(!conn.connectionOpen()){
            qDebug()<<"Failed to connect to database update";
            return; }
                                                                          // update query is made here
    conn.connectionOpen();
    QSqlQuery Qry;
    Qry.prepare("UPDATE permanent SET FamilyName=:employFamily, FirstName=:employFirst, SSNumber=:employSSN, MonthlySalary=:employSalary WHERE EmployeeID=:employID");

    Qry.bindValue(":employID",ui->lineEdit_employID->text().toInt());
    Qry.bindValue(":employFamily",ui->lineEdit_famName->text());
    Qry.bindValue(":employFirst", ui->lineEdit_fstName->text());
    Qry.bindValue(":employSSN", ui->lineEdit_SSN->text());
    Qry.bindValue(":employSalary" ,ui->lineEdit_salary->text().toDouble());

    if(Qry.exec()){
        QMessageBox::information(this,tr("EDIT"),tr("Updated successfully !"));
        conn.connectionClose();
        }
    else {
        QMessageBox::critical(this,tr("ERROR..."),Qry.lastError().text());
    }
}

void N1_permanent::on_permaent_deleteButton_clicked()                          // lastly the delete utton to deleted the selected entry
{
    FrontPage conn;
    QString employFamily,employFirst,employSSN,employID,employSalary;
    employID = ui->lineEdit_employID->text();

    if(!conn.connectionOpen()){
            qDebug()<<"Failed to connect to database update";
            return; }

    conn.connectionOpen();
    QSqlQuery Qry;
    Qry.prepare("DELETE FROM permanent WHERE EmployeeID='"+employID+"'");

    if(Qry.exec()){
        QMessageBox::information(this,tr("DELETE"),tr("Information Deleted !"));
        conn.connectionClose();
        }
    else {
        QMessageBox::critical(this,tr("ERROR..."),Qry.lastError().text());
    }
}

void N1_permanent::on_permanent_loadButton_clicked()                        // funtion to show data in the table view
{
    FrontPage conn;
    QSqlQueryModel *modal = new QSqlQueryModel();
    conn.connectionOpen();
    QSqlQuery* Qry = new QSqlQuery(conn.employeeData);
    Qry->prepare("select * from permanent");
    Qry->exec();
    modal->setQuery(*Qry);
    ui->tableView_permanent->setModel(modal);
    qDebug() << (modal->rowCount());
}
