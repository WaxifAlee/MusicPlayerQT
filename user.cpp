#include "user.h"
#include <iostream>

using namespace std;

User::User(const QString& username, const QString& password, const QString& firstname, const QString& lastname, const QString& gender, const QString& email, const QString& age, const QString& favGenre)
    : username(username), password(password), firstname(firstname), lastname(lastname), gender(gender), email(email), age(age), favGenre(favGenre) {
}

void User::showData() {

    cout << this->username.toStdString() << endl;
    cout << this->firstname.toStdString() << endl;
    cout << this->lastname.toStdString() << endl;
    cout << this->gender.toStdString() << endl;
    cout << this->password.toStdString() << endl;

}
