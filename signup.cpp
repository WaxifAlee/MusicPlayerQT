#include "signup.h"
#include "ui_signup.h"
#include <QSqlDatabase>
#include <QString>
#include <QSql>
#include <QString>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include <QRegularExpressionMatch>

signup::signup(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::signup)
{
    ui->setupUi(this);
    QObject::connect(ui->signUpBtn, &QPushButton::clicked, this, &signup::registerUser);
}

void signup::registerUser(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QString databasePath = "C:/Users/Wasif/Desktop/MusicPlayer/database/database.sqlite";
    db.setDatabaseName(databasePath);

    // Getting data from form
    QString userID;

    // userID, FirstN, LN, Gender, username, password, age, favGenre


    QString firstname = ui->fNameField->text();
    QString lastname = ui->lNameField->text();
    bool isMale = ui->mRB->isChecked();
    QString gender = isMale ? "M" : "F";
    QString username = ui->usernameField->text();
    QString password = ui->passwordField->text();
    QString email = ui->emailField->text();

    QString age = ui->ageBox->text();
    QString favGenre = ui->genreDropDown->currentText();

    bool formFilled;
    formFilled = firstname != NULL && lastname != NULL && gender != NULL && username != NULL
                 && password != NULL && email != NULL && age != NULL && favGenre != NULL;

    QRegularExpression emailRegex("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$");
    QRegularExpressionMatch match = emailRegex.match(email);

    if(db.open()){

        QString queryStrValidation = QString("SELECT * FROM users WHERE username = '%1';").arg(username);
        QSqlQuery validationQuery(queryStrValidation);

        if (validationQuery.exec()) {
            if (validationQuery.next()) {

                QMessageBox::warning(this, "Warning", "Username Already Taken");

            } else {
                if(formFilled){

                    if(match.hasMatch()){
                        QString queryStrRegistration = QString("INSERT INTO users (firstname, lastname, gender, username, password, email, age, favouriteGenre) "
                                                               "VALUES ('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8');")
                                                               .arg(firstname)
                                                               .arg(lastname)
                                                               .arg(gender)
                                                               .arg(username)
                                                               .arg(password)
                                                               .arg(email)
                                                               .arg(age)
                                                               .arg(favGenre);


                        QSqlQuery registrationQuery(queryStrRegistration);
                        registrationQuery.exec();
                        QMessageBox::information(this, "Success", "User registered successfully!");
                    } else {
                        QMessageBox::warning(this, "Error", "Invalid Email Address Entered");
                    }

                } else {
                    QMessageBox::information(this, "Error", "Please Fill Out The Form Completely!");
                }
            }
        } else {
            QMessageBox::critical(this, "Error", "Query execution failed: " + validationQuery.lastError().text());
        }

    } else {
        QMessageBox::warning(this, "Error", "Connection With Database Failed!");
    }

}

signup::~signup()
{
    delete ui;
}
