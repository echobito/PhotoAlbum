#include "prosetpage.h"
#include "ui_prosetpage.h"
#include <QLineEdit>
#include <QDir>
#include <QFileDialog>

ProSetPage::ProSetPage(QWidget *parent)
    : QWizardPage(parent)
    , ui(new Ui::ProSetPage)
{
    ui->setupUi(this);
    //绑定域 不输入无法下一步
    registerField("proPath", ui->lineEdit_2);
    registerField("proName*", ui->lineEdit);
    //输入时触发槽函数
    connect(ui->lineEdit, &QLineEdit::textEdited, this, &ProSetPage::completeChanged);
    connect(ui->lineEdit_2, &QLineEdit::textEdited, this, &ProSetPage::completeChanged);
    //设置默认显示路径为当前路径
    QString curPath = QDir::currentPath();
    ui->lineEdit_2->setText(curPath);
    ui->lineEdit_2->setCursorPosition(ui->lineEdit_2->text().size());
    ui->lineEdit_2->setClearButtonEnabled(true);
    ui->lineEdit->setClearButtonEnabled(true);
}

ProSetPage::~ProSetPage()
{
    delete ui;
}

void ProSetPage::GetProSettings(QString &name, QString path)
{
    name = ui->lineEdit->text();
    path = ui->lineEdit_2->text();
}

bool ProSetPage::isComplete() const
{
    //判断输入是否为空
    if(ui->lineEdit->text() == "" || ui->lineEdit_2->text() == ""){
        ui->tips->setText("project path or name is void");
        return false;
    }
    //判断输入是否有效
    QDir dir(ui->lineEdit_2->text());
    if(!dir.exists()){
        ui->tips->setText("project path is not exists");
        return false;
    }
    // 判断路径是否存在
    QString absFilePath = dir.absoluteFilePath(ui->lineEdit->text());
    QDir dist_dir(absFilePath);
    //不能在已经存在的目录里创建项目
    if(dist_dir.exists()){
        ui->tips->setText("project has exists, change path or name");
        return false;
    }

    ui->tips->setText("");
    //如果重写了基类的函数，如果还想用基类的功能，再调用一遍
    return QWizardPage::isComplete();
}

void ProSetPage::on_pushButton_clicked()
{
    QFileDialog file_dialog;
    //设置打开目录模式
    file_dialog.setFileMode(QFileDialog::Directory);
    file_dialog.setWindowTitle("选择导入的文件夹");
    auto path = QDir::currentPath();
    //打开当前目录
    file_dialog.setDirectory(path);
    file_dialog.setViewMode(QFileDialog::Detail);

    QStringList fileNames;
    if(file_dialog.exec()){
        fileNames = file_dialog.selectedFiles();
    }

    if(fileNames.length() <= 0){
        return;
    }

    QString import_path = fileNames.at(0);
    ui->lineEdit_2->setText(import_path);
}

