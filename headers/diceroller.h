#ifndef DICEROLLER_H
#define DICEROLLER_H

#include <QWidget>
#include <QClipboard>
#include "roller.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DiceRoller; }
QT_END_NAMESPACE

class DiceRoller : public QWidget
{
    Q_OBJECT

public:
    DiceRoller(QWidget *parent = nullptr);
    ~DiceRoller();

private slots:
    void execute_roll();

    void on_rollButton_clicked();

    void on_copyButton_clicked();

    void on_Rollstring_returnPressed();

private:
    Ui::DiceRoller *ui;
};
#endif // DICEROLLER_H
