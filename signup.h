#ifndef SIGNUP_H
#define SIGNUP_H

#include <QFrame>

namespace Ui {
class signup;
}

class signup : public QFrame
{
    Q_OBJECT

public:
    explicit signup(QWidget *parent = nullptr);

    void registerUser();

    ~signup();

private:
    Ui::signup *ui;
};

#endif // SIGNUP_H
