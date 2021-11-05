#include "include/diceroller.h"
#include "ui_diceroller.h"

DiceRoller::DiceRoller(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DiceRoller)
{
    ui->setupUi(this);
}

DiceRoller::~DiceRoller()
{
    delete ui;
}


void DiceRoller::process_options(Roller& roll)
{
    roll.set_reroll(ui->rerollButton->isChecked());

    roll.set_boon_bane(ui->boonBox->value(), ui->baneBox->value());

    roll.set_advantages(ui->advBox->isChecked(), ui->disBox->isChecked());
}


void DiceRoller::execute_roll()
{
    std::string rollstring = ui->Rollstring->text().toStdString();
    Roller roll_data = Roller(rollstring);

    process_options(roll_data);

    std::vector<int> result = roll_data.roll();
    if (result.size() == 0){
        double result = roll_data.expectation();
        ui->result->setText(QString::number(result));
    } else if (result.size() == 1){
        ui->result->setText(QString::number(result[0]));
    } else {
        QString res = "";
        for (size_t i = 0; i < result.size(); i++){
            res += QString::number(result[i]);
            if (i < result.size() - 1) res += " ";
        }
        ui->result->setText(res);
    }
}


void DiceRoller::execute_expectation()
{
    std::string rollstring = ui->Rollstring->text().toStdString();
    Roller roll_data = Roller(rollstring);

    process_options(roll_data);

    double result = roll_data.expectation();
    ui->result->setText(QString::number(result));
}


void DiceRoller::on_rollButton_clicked()
{
    DiceRoller::execute_roll();
}


void DiceRoller::on_Rollstring_returnPressed()
{
    DiceRoller::execute_roll();
}


void DiceRoller::on_expectationButton_clicked()
{
    DiceRoller::execute_expectation();
}


void DiceRoller::on_copyButton_clicked()
{
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(ui->result->toPlainText());
}


void DiceRoller::on_helpButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setTextFormat(Qt::MarkdownText);
    QFile *file = new QFile (":/help.md");
    QString help = "";
    if (file->open (QIODevice::ReadOnly) == true)
    {
        help = QString(file->readAll());
        file->close ();
    }

    msgBox.setText(help);
    msgBox.setWindowTitle("Help");

    msgBox.exec();
}





