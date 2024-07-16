#include "phonebook.h"
#include "./ui_phonebook.h"

PhoneBook::PhoneBook(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PhoneBook)
{
    ui->setupUi(this);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

PhoneBook::~PhoneBook()
{
    delete ui;
}

void PhoneBook::on_addButton_clicked()
{
    QString name = ui->LineEditName->text();
    QString phone = ui->LineEditPhone->text();
    QString email = ui->LineEditemail->text();

    int row = ui->tableWidget->rowCount();
    if((!isValidName(name)) && (!isValidNumber(phone))){
        QMessageBox::warning(this,"Message","Name/phone should contain only alphabetical/numerical characters");
    }
    else if(isDuplicateNumber(phone)){
        QMessageBox::warning(this,"Message","Phone Number is already available");
    }
    else{
        ui->tableWidget->insertRow(row);
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(name));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(phone));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(email));
    }

    ui->LineEditName->clear();
    ui->LineEditPhone->clear();
    ui->LineEditemail->clear();
}


void PhoneBook::on_searchButton_clicked() {
    QString searchText = ui->lineEditSearch->text();
    Qt::MatchFlags matchFlags = Qt::MatchExactly;
    QList<QTableWidgetItem *> foundItems = ui->tableWidget->findItems(searchText, matchFlags);

    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        for (int column = 0; column < ui->tableWidget->columnCount(); ++column) {
            QTableWidgetItem *item = ui->tableWidget->item(row, column);
            if (item) {
                item->setBackground(Qt::white);
            }
        }
    }

    // Highlight found items
    foreach (QTableWidgetItem *item, foundItems) {
        item->setBackground(Qt::yellow);
    }
}

void PhoneBook::on_removeButton_clicked()
{
    int row = ui->tableWidget->currentRow();
    if (row >= 0) {
        ui->tableWidget->removeRow(row);
    }
}


void PhoneBook::on_saveButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save Phonebook", "", "Phonebook Files (*.pbk);;All Files (*)");
    if (!fileName.isEmpty()) {
        saveToFile(fileName);
    }
}


void PhoneBook::on_loadButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Load Phonebook", "", "Phonebook Files (*.pbk);;All Files (*)");
    if (!fileName.isEmpty()) {
        loadFromFile(fileName);
    }
}

bool PhoneBook::isValidName(QString name)
{
    static QRegularExpression re("^[A-Za-z\\s]+$");
    return re.match(name).hasMatch();
}

bool PhoneBook::isValidNumber(QString phone){
    static QRegularExpression re("^\\d+$");
    return re.match(phone).hasMatch();
}

bool PhoneBook::isDuplicateNumber(QString phone){
    // Check if the table widget is not null
     if (!ui->tableWidget) {
     return false; // Or handle the error appropriately
    }

// Iterate through each row of the table
    for (int i = 0; i < ui->tableWidget->rowCount(); i++){
    // Get the item from the second column (index 1)
        QTableWidgetItem *item = ui->tableWidget->item(i, 1);
            if (item) { // Check if the item is not null
         // Compare the item's text with the phone number
            if (item->text() == phone) {
             return true;
         }
     }
}
// No duplicate number found
 return false;
}

void PhoneBook::saveToFile(const QString &fileName)
{
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream out(&file);
        for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
            for (int col = 0; col < ui->tableWidget->columnCount(); ++col) {
                QTableWidgetItem *item = ui->tableWidget->item(row, col);
                out << (item ? item->text() : "") << ",";
            }
            out << "\n";
        }
        file.close();
    }
}

void PhoneBook::loadFromFile(const QString &fileName)
{
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        ui->tableWidget->setRowCount(0);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split(",");
            if (fields.size() >= 3) {
                int row = ui->tableWidget->rowCount();
                ui->tableWidget->insertRow(row);
                for (int col = 0; col < 3; ++col) {
                    ui->tableWidget->setItem(row, col, new QTableWidgetItem(fields[col]));
                }
            }
        }
        file.close();
    }
}

void PhoneBook::on_pushButton_clicked()
{
    QMessageBox::about(this,"Closure","Thanks for using PhoneBook!!");
    this->close();
}

