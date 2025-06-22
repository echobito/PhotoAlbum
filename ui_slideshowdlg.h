/********************************************************************************
** Form generated from reading UI file 'slideshowdlg.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SLIDESHOWDLG_H
#define UI_SLIDESHOWDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <picanimationwid.h>
#include <picbutton.h>
#include <picstatebtn.h>
#include <prelistwid.h>

QT_BEGIN_NAMESPACE

class Ui_SlideShowDlg
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *slideShow;
    QGridLayout *gridLayout;
    QWidget *slidenextwid;
    QHBoxLayout *horizontalLayout_3;
    PicButton *slidenextBtn;
    QWidget *slideprewid;
    QHBoxLayout *horizontalLayout_4;
    PicButton *slidepreBtn;
    PicAnimationWid *picAnimation;
    QHBoxLayout *horizontalLayout_2;
    PicStateBtn *playBtn;
    PicButton *closeBtn;
    QWidget *preShow;
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    PreListWid *preListWidget;

    void setupUi(QDialog *SlideShowDlg)
    {
        if (SlideShowDlg->objectName().isEmpty())
            SlideShowDlg->setObjectName("SlideShowDlg");
        SlideShowDlg->resize(570, 426);
        verticalLayout = new QVBoxLayout(SlideShowDlg);
        verticalLayout->setObjectName("verticalLayout");
        slideShow = new QWidget(SlideShowDlg);
        slideShow->setObjectName("slideShow");
        gridLayout = new QGridLayout(slideShow);
        gridLayout->setObjectName("gridLayout");
        slidenextwid = new QWidget(slideShow);
        slidenextwid->setObjectName("slidenextwid");
        slidenextwid->setMinimumSize(QSize(80, 0));
        slidenextwid->setMaximumSize(QSize(80, 16777215));
        horizontalLayout_3 = new QHBoxLayout(slidenextwid);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        slidenextBtn = new PicButton(slidenextwid);
        slidenextBtn->setObjectName("slidenextBtn");

        horizontalLayout_3->addWidget(slidenextBtn);


        gridLayout->addWidget(slidenextwid, 1, 2, 1, 1);

        slideprewid = new QWidget(slideShow);
        slideprewid->setObjectName("slideprewid");
        slideprewid->setMinimumSize(QSize(80, 0));
        slideprewid->setMaximumSize(QSize(80, 16777215));
        horizontalLayout_4 = new QHBoxLayout(slideprewid);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        slidepreBtn = new PicButton(slideprewid);
        slidepreBtn->setObjectName("slidepreBtn");

        horizontalLayout_4->addWidget(slidepreBtn);


        gridLayout->addWidget(slideprewid, 1, 0, 1, 1);

        picAnimation = new PicAnimationWid(slideShow);
        picAnimation->setObjectName("picAnimation");

        gridLayout->addWidget(picAnimation, 1, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        playBtn = new PicStateBtn(slideShow);
        playBtn->setObjectName("playBtn");

        horizontalLayout_2->addWidget(playBtn);

        closeBtn = new PicButton(slideShow);
        closeBtn->setObjectName("closeBtn");

        horizontalLayout_2->addWidget(closeBtn);


        gridLayout->addLayout(horizontalLayout_2, 0, 2, 1, 1);


        verticalLayout->addWidget(slideShow);

        preShow = new QWidget(SlideShowDlg);
        preShow->setObjectName("preShow");
        horizontalLayout = new QHBoxLayout(preShow);
        horizontalLayout->setObjectName("horizontalLayout");
        widget = new QWidget(preShow);
        widget->setObjectName("widget");
        widget->setMinimumSize(QSize(0, 120));
        widget->setMaximumSize(QSize(16777215, 120));
        preListWidget = new PreListWid(widget);
        preListWidget->setObjectName("preListWidget");
        preListWidget->setGeometry(QRect(10, 10, 16777215, 110));
        preListWidget->setMinimumSize(QSize(0, 110));
        preListWidget->setMaximumSize(QSize(16777215, 110));
        preListWidget->setFlow(QListView::LeftToRight);

        horizontalLayout->addWidget(widget);


        verticalLayout->addWidget(preShow);

        verticalLayout->setStretch(0, 7);
        verticalLayout->setStretch(1, 1);

        retranslateUi(SlideShowDlg);

        QMetaObject::connectSlotsByName(SlideShowDlg);
    } // setupUi

    void retranslateUi(QDialog *SlideShowDlg)
    {
        SlideShowDlg->setWindowTitle(QCoreApplication::translate("SlideShowDlg", "Dialog", nullptr));
        slidenextBtn->setText(QString());
        slidepreBtn->setText(QString());
        playBtn->setText(QString());
        closeBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SlideShowDlg: public Ui_SlideShowDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SLIDESHOWDLG_H
