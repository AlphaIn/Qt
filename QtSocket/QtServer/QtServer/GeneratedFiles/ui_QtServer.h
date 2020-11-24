/********************************************************************************
** Form generated from reading UI file 'QtServer.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTSERVER_H
#define UI_QTSERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_QtServerClass
{
public:

    void setupUi(QDialog *QtServerClass)
    {
        if (QtServerClass->objectName().isEmpty())
            QtServerClass->setObjectName(QStringLiteral("QtServerClass"));
        QtServerClass->resize(600, 400);

        retranslateUi(QtServerClass);

        QMetaObject::connectSlotsByName(QtServerClass);
    } // setupUi

    void retranslateUi(QDialog *QtServerClass)
    {
        QtServerClass->setWindowTitle(QApplication::translate("QtServerClass", "QtServer", 0));
    } // retranslateUi

};

namespace Ui {
    class QtServerClass: public Ui_QtServerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTSERVER_H
