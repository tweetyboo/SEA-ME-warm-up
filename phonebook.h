#ifndef PHONEBOOK_H
#define PHONEBOOK_H

#include <QMainWindow>
#include "QLineEdit"
#include "QWidget"
#include "QLayout"
#include "QFile"
#include "QFileDialog"
#include "QMessageBox"
#include <QTableWidget>
#include "qdebug.h"
#include "QList"

QT_BEGIN_NAMESPACE
namespace Ui {
class PhoneBook;
}
QT_END_NAMESPACE

class PhoneBook : public QMainWindow
{
    Q_OBJECT

public:
    PhoneBook(QWidget *parent = nullptr);
    ~PhoneBook();

private slots:


    void on_addButton_clicked();

    void on_removeButton_clicked();

    void on_saveButton_clicked();

    void on_loadButton_clicked();

    void on_searchButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::PhoneBook *ui;
    void saveToFile(const QString &fileName);
    void loadFromFile(const QString &fileName);
    bool isValidName(QString(name));
    bool isValidNumber(QString(phone));
    bool isDuplicateNumber(QString phone);

};
#endif // PHONEBOOK_H
