/********************************************************************************
** Form generated from reading UI file 'QtSocketClient.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTSOCKETCLIENT_H
#define UI_QTSOCKETCLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_QtSocketClientClass
{
public:

    void setupUi(QDialog *QtSocketClientClass)
    {
        if (QtSocketClientClass->objectName().isEmpty())
            QtSocketClientClass->setObjectName(QStringLiteral("QtSocketClientClass"));
        QtSocketClientClass->resize(600, 400);

        retranslateUi(QtSocketClientClass);

        QMetaObject::connectSlotsByName(QtSocketClientClass);
    } // setupUi

    void retranslateUi(QDialog *QtSocketClientClass)
    {
        QtSocketClientClass->setWindowTitle(QApplication::translate("QtSocketClientClass", "QtSocketClient", 0));
    } // retranslateUi

};

namespace Ui {
    class QtSocketClientClass: public Ui_QtSocketClientClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTSOCKETCLIENT_H
