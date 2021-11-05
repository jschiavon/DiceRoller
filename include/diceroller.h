#ifndef DICEROLLER_H
#define DICEROLLER_H

#include <QWidget>
#include <QClipboard>
#include <QMessageBox>
#include <QFile>
#include <QString>
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
    void process_options(Roller &);
    void execute_roll();
    void execute_expectation();

    void on_rollButton_clicked();

    void on_copyButton_clicked();

    void on_Rollstring_returnPressed();

    void on_helpButton_clicked();

    void on_expectationButton_clicked();

private:
    Ui::DiceRoller *ui;
};
#endif // DICEROLLER_H
