#include "removeprodialog.h"
#include "ui_removeprodialog.h"

RemoveProDialog::RemoveProDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RemoveProDialog)
{
    ui->setupUi(this);
}

RemoveProDialog::~RemoveProDialog()
{
    delete ui;
}

bool RemoveProDialog::IsRemoved()
{
    //返回勾选状态
    bool bChecked = ui->checkBox->isChecked();
    return bChecked;
}
