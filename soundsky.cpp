#include "soundsky.h"
#include "ui_soundsky.h"
#include "user.h"
#include "AVLTree.h"

#include <QPushButton>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>
#include <QListWidgetItem>
#include <QDesktopServices>
#include <QUrl>
#include <QSqlError>

SoundSky::SoundSky(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SoundSky)
{
    ui->setupUi(this);
    QObject::connect(ui->searchSongsBtn, &QPushButton::clicked, this, &SoundSky::getData);
    connect(ui->songsContainer, &QListWidget::itemDoubleClicked, this, &SoundSky::openYoutubeSearch, Qt::UniqueConnection);

}

void SoundSky::setUser(User* user){
    this->user = user;
}

void SoundSky::getData()
{
    AVLTree songTree;

    // Connect to the SQLite database
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/Wasif/Desktop/MusicPlayer/database/database.sqlite");

    // Get UI components Data
    QString filter = ui->filterSearch->currentText();
    QString search = ui->searchBar->text();

    if (db.open()) {
        // Prepare and execute the SQL query to fetch songs from the database
        QString queryStr;
        QSqlQuery query;

        if (filter == "Artist") {
            queryStr = QString("SELECT trackName, genre, artist FROM songs WHERE artist LIKE '%%1%' ")
                            .arg(search);
        } else if (filter == "Track") {
            queryStr = QString("SELECT trackName, genre, artist FROM songs WHERE trackName LIKE '%%1%' ")
                            .arg(search);
        } else if (filter == "Genre") {
            queryStr = QString("SELECT trackName, genre, artist FROM songs WHERE genre LIKE '%%1%' ")
                            .arg(search);
        }

        if (query.exec(queryStr)) {
            // Fetch and insert each song into the AVL tree
            while (query.next()) {
                QString trackName = query.value(0).toString();
                QString genre = query.value(1).toString();
                QString artist = query.value(2).toString();

                Song song{ trackName.toStdString(), genre.toStdString(), artist.toStdString() };
                songTree.insert(song);
            }

            // Clear the existing items in the songsContainer list widget
             ui->songsContainer->clear();

            // Display the songs in the AVL tree in the songsContainer list widget
            QListWidgetItem* item;
            std::vector<Song> songs = songTree.getAllSongs();
            for (const Song& song : songs) {
                QString songName = QString::fromStdString(song.trackName);
                item = new QListWidgetItem(songName);
                ui->songsContainer->addItem(item);
            }
        } else {
            qDebug() << "Query execution failed:" << query.lastError().text();
        }

        db.close();
    } else {
        qDebug() << "Failed to connect to the database.";
    }
}

void SoundSky::openYoutubeSearch(QListWidgetItem* item)
{
    // Retrieve the text of the double-clicked item
    QString songName = item->text();

    // Construct the URL for the YouTube search query
    QString searchQuery = songName + " official music video"; // Add any additional keywords if desired
    QString url = "https://www.youtube.com/results?search_query=" + QUrl::toPercentEncoding(searchQuery);

    // Open the URL in the default browser
    QDesktopServices::openUrl(QUrl(url));
}



SoundSky::~SoundSky()
{
    delete ui;
}
