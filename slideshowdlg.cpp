#include "slideshowdlg.h"
#include "ui_slideshowdlg.h"
#include <QDebug>
#include "prelistwid.h"

SlideShowDlg::SlideShowDlg(QWidget *parent, QTreeWidgetItem *first_item, QTreeWidgetItem *last_item)
    :QDialog(parent),ui(new Ui::SlideShowDlg),_first_item(first_item),
    _last_item(last_item)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint);
    ui->slidepreBtn->SetIcons(":/icon/previous.png",
                              ":/icon/previous_hover.png",
                              ":/icon/previous_press.png");

    ui->slidenextBtn->SetIcons(":/icon/next.png",
                              ":/icon/next_hover.png",
                              ":/icon/next_press.png");

    ui->closeBtn->SetIcons(":/icon/closeshow.png",
                            ":/icon/closeshow_hover.png",
                            ":/icon/closeshow_press.png");

    ui->playBtn->SetIcons(":/icon/play.png",
                          ":/icon/play_hover.png",
                          ":/icon/play_press.png",
                          ":/icon/pause.png",
                          ":/icon/pause_hover.png",
                          ":/icon/pause_press.png");
    connect(ui->closeBtn, &QPushButton::clicked, this, &SlideShowDlg::close);
    connect(ui->slidenextBtn, &QPushButton::clicked, this, &SlideShowDlg::SlotSlideNext);
    connect(ui->slidepreBtn, &QPushButton::clicked, this, &SlideShowDlg::SlotSlidePre);

    auto * preListWid = dynamic_cast<PreListWid*>(ui->preListWidget);
    connect(ui->picAnimation, &PicAnimationWid::SigUpPreList,
            preListWid, &PreListWid::SlotUpPreList);
    connect(ui->picAnimation, &PicAnimationWid::SigSelectItem,
            preListWid, &PreListWid::SlotUpSelect);

    connect(preListWid, &PreListWid::SigUpSelectShow, ui->picAnimation, &PicAnimationWid::SlotUpSelectShow);

    //播放
    connect(ui->playBtn, &PicStateBtn::clicked, ui->picAnimation, &PicAnimationWid::SlotStartOrStop);

    //刷新播放按钮
    connect(ui->picAnimation, &PicAnimationWid::SigStart,
            ui->playBtn, &PicStateBtn::SlotStart);
    connect(ui->picAnimation, &PicAnimationWid::SigStop,
            ui->playBtn, &PicStateBtn::SlotStop);

    ui->picAnimation->SetPixmap(_first_item);

    ui->picAnimation->Start();
}

SlideShowDlg::~SlideShowDlg()
{
    delete ui;
}

void SlideShowDlg::SlotSlideNext()
{
    ui->picAnimation->SlideNext();
}

void SlideShowDlg::SlotSlidePre()
{
    ui->picAnimation->SlidePre();
}
