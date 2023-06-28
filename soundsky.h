#ifndef SOUNDSKY_H
#define SOUNDSKY_H

#include <QListWidgetItem>
#include <QFrame>
#include "user.h"

namespace Ui {
class SoundSky;
}

class SoundSky : public QFrame
{
    Q_OBJECT

public:

    explicit SoundSky(QWidget *parent = nullptr);
    void getData();
    void setUser(User *user);
    void openYoutubeSearch(QListWidgetItem* item);
    ~SoundSky();
    User *user;

private:
    Ui::SoundSky *ui;
};

#endif // SOUNDSKY_H
