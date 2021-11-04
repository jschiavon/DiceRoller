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

void DiceRoller::on_helpButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setTextFormat(Qt::MarkdownText);
    msgBox.setText("The format for the rollstring is as follows "
                   "(not mandatory options are between square brackets):\n\n"
                   "### [Rx]NdD[+M]\n"
                   "where:\n"
                   "* **R** : Number of _repetitions_. If present, repeat R times the roll\n"
                   "* **N** : _Number_ of dice to roll\n"
                   "* **D** : Number of _sides_ of the dice to roll\n"
                   "* **M** : _Modifier_. If present, add M to the result of rolling\n\n"
                   "*Example*: 3x2d20+2 roll for 3 times 2 20-sided dice and adds 2 to each result.\n\n"
                   "The options _Reroll 1s_ and _expectation_ do as they say: the first allows to reroll (once)"
                   "each result of 1 that appears in the roll, "
                   "while the second does not roll at all but simply returns the expected result obtained.");
    msgBox.exec();
}

