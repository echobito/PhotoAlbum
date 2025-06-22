/********************************************************************************
** Form generated from reading UI file 'prosetpage.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROSETPAGE_H
#define UI_PROSETPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWizardPage>

QT_BEGIN_NAMESPACE

class Ui_ProSetPage
{
public:
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_2;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton;
    QLabel *label_2;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *tips;

    void setupUi(QWizardPage *ProSetPage)
    {
        if (ProSetPage->objectName().isEmpty())
            ProSetPage->setObjectName("ProSetPage");
        ProSetPage->resize(632, 522);
        gridLayout_3 = new QGridLayout(ProSetPage);
        gridLayout_3->setObjectName("gridLayout_3");
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(5, 5, 5, 5);
        lineEdit_2 = new QLineEdit(ProSetPage);
        lineEdit_2->setObjectName("lineEdit_2");

        gridLayout_2->addWidget(lineEdit_2, 1, 2, 1, 1);

        pushButton = new QPushButton(ProSetPage);
        pushButton->setObjectName("pushButton");

        gridLayout_2->addWidget(pushButton, 1, 3, 1, 1);

        label_2 = new QLabel(ProSetPage);
        label_2->setObjectName("label_2");

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        label = new QLabel(ProSetPage);
        label->setObjectName("label");

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        lineEdit = new QLineEdit(ProSetPage);
        lineEdit->setObjectName("lineEdit");

        gridLayout_2->addWidget(lineEdit, 0, 2, 1, 1);

        tips = new QLabel(ProSetPage);
        tips->setObjectName("tips");

        gridLayout_2->addWidget(tips, 2, 2, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 0, 0, 1, 1);


        retranslateUi(ProSetPage);

        QMetaObject::connectSlotsByName(ProSetPage);
    } // setupUi

    void retranslateUi(QWizardPage *ProSetPage)
    {
        ProSetPage->setWindowTitle(QCoreApplication::translate("ProSetPage", "WizardPage", nullptr));
        pushButton->setText(QCoreApplication::translate("ProSetPage", "browse", nullptr));
        label_2->setText(QCoreApplication::translate("ProSetPage", "Path:", nullptr));
        label->setText(QCoreApplication::translate("ProSetPage", "Name:", nullptr));
        tips->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ProSetPage: public Ui_ProSetPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROSETPAGE_H
