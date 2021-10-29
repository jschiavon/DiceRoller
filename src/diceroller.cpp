#include "headers/diceroller.h"
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


void DiceRoller::execute_roll()
{
    std::string rollstring = ui->Rollstring->text().toStdString();
    Roller roll_data = Roller(rollstring);

    if (ui->rerollButton->isChecked()){
        roll_data.activate_reroll();
    }

    if (ui->expectationButton->isChecked()){
        double result = roll_data.expectation();
        ui->result->setText(QString::number(result));
    } else {
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
}


void DiceRoller::on_rollButton_clicked()
{
    DiceRoller::execute_roll();
}

void DiceRoller::on_Rollstring_returnPressed()
{
    DiceRoller::execute_roll();
}

void DiceRoller::on_copyButton_clicked()
{
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(ui->result->toPlainText());
}



