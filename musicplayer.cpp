#include "musicplayer.h"
#include "ui_musicplayer.h"
#include "signup.h"
#include "user.h"
#include "soundsky.h"

#include <iostream>
#include <string>
#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlQuery>
#include <QtSql>

using namespace std;


MusicPlayer::MusicPlayer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MusicPlayer)
{
    ui->setupUi(this);

    QObject::connect(ui->loginBtn, &QPushButton::clicked, this, &MusicPlayer::login);
    QObject::connect(ui->signupBtn, &QPushButton::clicked, this, &MusicPlayer::openSignup);
}

MusicPlayer::~MusicPlayer()
{
    delete ui;
}

void MusicPlayer::openSignup(){
    signup *signupWindow = new signup();
    signupWindow->setAttribute(Qt::WA_DeleteOnClose);
    signupWindow->show();
}

void MusicPlayer::login(){

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QString databasePath = "C:/Users/Wasif/Desktop/MusicPlayer/database/database.sqlite";
    db.setDatabaseName(databasePath);

    if (db.open()) {
        QString username = ui->username_field->text();
        QString password = ui->passwordField->text();

        QString queryStr = QString("SELECT * FROM users WHERE username = '%1' AND password = '%2'")
                                   .arg(username)
                                   .arg(password);

        QSqlQuery query(queryStr);

        if (query.exec()) {
            if (query.next()) {

                QString fetchedUsername = query.value("username").toString();
                QString fetchedPassword = query.value("password").toString();
                QString fetchedFirstname = query.value("firstname").toString();
                QString fetchedLastname = query.value("lastname").toString();
                QString fetchedGender = query.value("gender").toString();
                QString fetchedEmail = query.value("email").toString();
                QString fetchedAge = query.value("age").toString();
                QString fetchedFavGenre = query.value("favouriteGenre").toString();

                // Creating the user object
                User *user = new User(fetchedUsername, fetchedPassword, fetchedFirstname, fetchedLastname, fetchedGender, fetchedEmail, fetchedAge, fetchedFavGenre);

                SoundSky* mainWindow = new SoundSky();
                mainWindow->setUser(user);
                mainWindow->setAttribute(Qt::WA_DeleteOnClose);
                mainWindow->show();

                this->~MusicPlayer();

            } else {
                // Login failed, invalid username or password
                QMessageBox::critical(this, "Error", "Invalid username or password!");
            }
        } else {
            // Query execution failed
            QMessageBox::critical(this, "Error", "Query execution failed: " + query.lastError().text());
        }
    } else {
        // Connection failed
        QMessageBox::critical(nullptr, "Error", "Connection Failed with Database: " + db.lastError().text());
    }

    db.close();

}













