#ifndef FRONTPAGE_H
#define FRONTPAGE_H

#include <QMainWindow>
#include <QtSql>                                // For using the SQL database
#include <QDebug>                               // For using the qDebug function
#include <QFileInfo>                            // For using the function to access the path and database file
#include <QMessageBox>                          // For using the message box to give acknowledge or warnings

#include "n1_permanent.h"                       // For class named permanent (monthly salary)
#include "n2_contract.h"                        // For class named contract  (hourly salary)
#include "n3_salesman.h"                        // For class named salesman  (bonus based salary)
#include "o1_showall.h"                         // For class named showall   (show all tables)

namespace Ui {
class FrontPage;
}

class FrontPage : public QMainWindow
{
    Q_OBJECT

// Declaring an object accessible by all windows to check the connectivity of the application with the database
public:
    QSqlDatabase employeeData;
    // employeeData -> name of the database file where data from here is stored

    void connectionClose()
    // function to close the connection with the database
    {
        employeeData.close();
        employeeData.removeDatabase(QSqlDatabase::defaultConnection);
    }

    bool connectionOpen()
    // function to open the connection to the database
    {
        employeeData = QSqlDatabase::addDatabase("QSQLITE");                        // add the database into the project
        employeeData.setHostName("localhost");
        employeeData.setDatabaseName("C:/ePersonnell_Managment/mployeeData.sqlite");   // sets the database name in the file destintaion

        //Condition  -> for the messages to print when the onnection is made with the database
        if(!employeeData.open()){
            qDebug()<<("Database Disconnected ...");
            return false;
        }
        else {
            qDebug()<<("Database Connected ...");
            return true;
        }
        }

public:
    explicit FrontPage(QWidget *parent = 0);
    ~FrontPage();

private slots:
    void on_nextButton_clicked();

    void on_quitButton_clicked();

private:
    Ui::FrontPage *ui;
};

#endif // FRONTPAGE_H
