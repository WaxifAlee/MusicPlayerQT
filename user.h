#ifndef USER_H
#define USER_H

#include <QString>

class User {
public:
    QString username, firstname, lastname, password, email, age, gender, favGenre;

    User(const QString& username, const QString& password, const QString& firstName, const QString& lastName, const QString& gender, const QString& email, const QString& age, const QString& favGenre);
    void showData();
};

#endif // USER_H
