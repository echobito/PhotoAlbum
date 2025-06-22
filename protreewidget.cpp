#include "protreewidget.h"
#include <QDir>
#include "protreeitem.h"
#include "const.h"
#include <QHeaderView>
#include <QGuiApplication>
#include <QMenu>
#include <QFileDialog>
#include "removeprodialog.h"
#include "slideshowdlg.h"

ProTreeWidget::ProTreeWidget(QWidget * parent)
    :QTreeWidget(parent),_right_btn_item(nullptr),_active_item(nullptr),_selected_item(nullptr),
    _dialog_progress(nullptr), _open_dialog_progress(nullptr), _thread_create_pro(nullptr), _thread_open_pro(nullptr)
{
    this->header()->hide();
    connect(this, &ProTreeWidget::itemPressed, this, &ProTreeWidget::SlotItemPressed);
    _action_import = new QAction(QIcon(":/icon/import.png"), tr("导入文件"), this);
    _action_setstart = new QAction(QIcon(":/icon/core.png"), tr("设置活动项目"), this);
    _action_closepro = new QAction(QIcon(":/icon/close.png"), tr("关闭项目"), this);
    _action_slideshow = new QAction(QIcon(":/icon/slideshow.png"), tr("轮播图播放"), this);
    connect(_action_import, &QAction::triggered, this, &ProTreeWidget::SlotImport);
    connect(_action_setstart, &QAction::triggered, this, &ProTreeWidget::SlotSetActive);
    connect(_action_closepro, &QAction::triggered, this, &ProTreeWidget::SlotClosePro);
    connect(this, &ProTreeWidget::itemDoubleClicked, this, &ProTreeWidget::SlotDoubleClickItem);
    connect(_action_slideshow, &QAction::triggered, this, &ProTreeWidget::SlotSlideShow);
}

void ProTreeWidget::AddProToTree(const QString &name, const QString &path)
{
    QDir dir(path);
    // 拼成一个新的路径
    QString file_path = dir.absoluteFilePath(name);
    if(_set_path.find(file_path) != _set_path.end()){
        return;
    }
    //创建文件夹
    QDir pro_dir(file_path);
    if(!pro_dir.exists()){
        bool enable = pro_dir.mkpath(file_path);
        //是否创建成功
        if(!enable){
            return;
        }
    }
    _set_path.insert(file_path);
    auto * item = new ProTreeItem(this, name, file_path, TreeItemPro);
    item->setData(0, Qt::DisplayRole, name);
    item->setData(0, Qt::DecorationRole, QIcon(":/icon/dir.png"));
    item->setData(0, Qt::ToolTipRole, file_path);
    this->addTopLevelItem(item);
}

void ProTreeWidget::SlotItemPressed(QTreeWidgetItem *pressedItem, int column)
{
    if(QGuiApplication::mouseButtons() == Qt::RightButton){
        QMenu menu(this);
        //添加动作
        int itemtype = pressedItem->type();
        if(itemtype == TreeItemPro){
            _right_btn_item = pressedItem;
            menu.addAction(_action_import);
            menu.addAction(_action_setstart);
            menu.addAction(_action_closepro);
            menu.addAction(_action_slideshow);
            menu.exec(QCursor::pos());
        }
    }
}

void ProTreeWidget::SlotImport()
{
    QFileDialog file_dialog;
    file_dialog.setFileMode(QFileDialog::Directory);
    file_dialog.setWindowTitle(tr("选择导入的文件夹"));
    QString path = "";
    if(!_right_btn_item){
        qDebug() << "_right_btn_item is empty" << Qt::endl;
        //path = QDir::currentPath();
        return;
    }
    path = dynamic_cast<ProTreeItem*>(_right_btn_item)->GetPath();
    file_dialog.setDirectory(path);
    file_dialog.setViewMode(QFileDialog::Detail);
    //StringList缓存文件名
    QStringList fileNames;
    if(file_dialog.exec()){
        fileNames = file_dialog.selectedFiles();
    }
    //什么都没选
    if(fileNames.length() <= 0){
        return;
    }

    QString improt_path = fileNames.at(0);
    int file_count = 0;
    _dialog_progress = new QProgressDialog(this);
    //启动线程
    _thread_create_pro = std::make_shared<ProTreeThread>(std::ref(improt_path),std::ref(path), std::ref(_right_btn_item),
                                                         file_count, this, _right_btn_item, nullptr);
    connect(_thread_create_pro.get(), &ProTreeThread::SigUpdateProgress,
            this, &ProTreeWidget::SlotUpdateProgress);

    connect(_thread_create_pro.get(), &ProTreeThread::SigFinishProgress,
            this, &ProTreeWidget::SlotFinishProgress);

    connect(_dialog_progress, &QProgressDialog::canceled,
            this, &ProTreeWidget::SlotCancelProgress);

    connect(this, &ProTreeWidget::SigCancelProgress,
            _thread_create_pro.get(), &ProTreeThread::SlotCancelProgress);

    _thread_create_pro->start();
    //初始化对话框
    _dialog_progress->setWindowTitle("Please wait...");
    _dialog_progress->setFixedWidth(PROGRESS_WIDTH);
    _dialog_progress->setRange(0, PROGRESS_WIDTH);
    _dialog_progress->exec();
}

void ProTreeWidget::SlotSetActive()
{
    if(!_right_btn_item){
        return;
    }
    QFont nullFont;
    nullFont.setBold(false);

    //上一个激活的项目字体设置为正常的 新激活的设置为加粗
    if(_active_item){
        _active_item->setFont(0, nullFont);
    }
    //当前右击的设置为当前项目
    _active_item = _right_btn_item;
    nullFont.setBold(true);
    _active_item->setFont(0, nullFont);
}

void ProTreeWidget::SlotUpdateProgress(int count)
{
    if(!_dialog_progress){
        return;
    }

    if(count >= PROGRESS_MAX){
        _dialog_progress->setValue(count%PROGRESS_MAX);
    }else{
        _dialog_progress->setValue(count);
    }
}

void ProTreeWidget::SlotFinishProgress()
{
    _dialog_progress->setValue(PROGRESS_MAX);
    _dialog_progress->deleteLater();
}

void ProTreeWidget::SlotCancelProgress(){
    emit SigCancelProgress();
    delete _dialog_progress;
    _dialog_progress = nullptr;
}

void ProTreeWidget::SlotUpOpenProgress(int count)
{
    if(!_open_dialog_progress){
        return;
    }

    if(count >= PROGRESS_MAX){
        _open_dialog_progress->setValue(count%PROGRESS_MAX);
    }else{
        _open_dialog_progress->setValue(count);
    }
}

void ProTreeWidget::SlotFinishOpenProgress()
{
    if(!_open_dialog_progress){
        return;
    }
    _open_dialog_progress->setValue(PROGRESS_MAX);
    delete _open_dialog_progress;
    _open_dialog_progress = nullptr;
}

void ProTreeWidget::SlotCancelOpenProgress()
{
    emit SigCancelOpenProgress();
    delete _open_dialog_progress;
    _open_dialog_progress = nullptr;
}

void ProTreeWidget::SlotClosePro()
{
    RemoveProDialog remove_pro_dialog;
    auto res = remove_pro_dialog.exec();
    if(res != QDialog::Accepted){
        return;
    }

    bool b_remove = remove_pro_dialog.IsRemoved();
    //返回右键点击的项目的索引
    auto index_right_btn = this->indexOfTopLevelItem(_right_btn_item);
    auto * protreeitem = dynamic_cast<ProTreeItem*>(_right_btn_item);
    auto * selecteditem = dynamic_cast<ProTreeItem*>(_selected_item);
    auto delete_path = protreeitem->GetPath();
    _set_path.remove(delete_path);
    if(b_remove){
        QDir delete_dir(delete_path);
        delete_dir.removeRecursively();
    }
    //删除条目和当前条目是同一个
    if(protreeitem == _active_item){
        _active_item = nullptr;
    }
    if(selecteditem && protreeitem == selecteditem->GetRoot()){
        selecteditem = nullptr;
        _selected_item = nullptr;
        emit SigClearSelected();
    }

    //从目录树里移除
    delete this->takeTopLevelItem(index_right_btn);
    _right_btn_item = nullptr;
}

void ProTreeWidget::SlotDoubleClickItem(QTreeWidgetItem *doubleItem, int col)
{
    if(QGuiApplication::mouseButtons() == Qt::LeftButton){
        auto* tree_doubleItem = dynamic_cast<ProTreeItem*>(doubleItem);
        if(!tree_doubleItem){
            return;
        }
        int itemtype = tree_doubleItem->type();
        if(itemtype == TreeItemPic){
            emit SigUpdateSelected(tree_doubleItem->GetPath());
            _selected_item = doubleItem;

        }
    }
}

void ProTreeWidget::SlotSlideShow()
{
    if(!_right_btn_item){
        return;
    }
    auto * right_pro_item = dynamic_cast<ProTreeItem*>(_right_btn_item);
    auto * last_child_item = right_pro_item->GetLastPicChild();
    if(!last_child_item){
        return;
    }

    auto * first_child_item = right_pro_item->GetFirstPicChild();
    if(!first_child_item){
        return;
    }
    _slide_show_dlg = std::make_shared<SlideShowDlg>(this, first_child_item, last_child_item);
    _slide_show_dlg->setModal(true);
    _slide_show_dlg->showMaximized();
}

void ProTreeWidget::SlotOpenPro(const QString &path)
{
    //判断是否打开过
    if(_set_path.find(path) != _set_path.end()){
        return;
    }

    _set_path.insert(path);
    int file_count = 0;
    QDir pro_dir(path);
    QString proname = pro_dir.dirName();
    _thread_open_pro = std::make_shared<OpenTreeThread>(path, file_count, this, nullptr);


    _open_dialog_progress = new QProgressDialog(this);

    connect(_thread_open_pro.get(), &OpenTreeThread::SigUpdateProgress,
            this, &ProTreeWidget::SlotUpOpenProgress);

    connect(_thread_open_pro.get(), &OpenTreeThread::SigFinishProgress,
            this, &ProTreeWidget::SlotFinishOpenProgress);

    connect(_open_dialog_progress, &QProgressDialog::canceled,
            this, &ProTreeWidget::SlotCancelOpenProgress);

    connect(this, &ProTreeWidget::SigCancelOpenProgress,
            _thread_open_pro.get(), &OpenTreeThread::SlotCancelProgress);

    _thread_open_pro->start();
    //初始化对话框
    _open_dialog_progress->setWindowTitle("Please wait...");
    _open_dialog_progress->setFixedWidth(PROGRESS_WIDTH);
    _open_dialog_progress->setRange(0, PROGRESS_WIDTH);
    _open_dialog_progress->exec();
}

void ProTreeWidget::SlotNextShow()
{
    if(!_selected_item){
        return;
    }
    auto *curItem = dynamic_cast<ProTreeItem*>(_selected_item)->GetNextItem();
    if(!curItem){
        return;
    }

    emit SigUpdatePic(curItem->GetPath());
    _selected_item = curItem;
    this->setCurrentItem(curItem);
}

void ProTreeWidget::SlotPreShow()
{
    if(!_selected_item){
        return;
    }
    auto *curItem = dynamic_cast<ProTreeItem*>(_selected_item)->GetPreItem();
    if(!curItem){
        return;
    }

    emit SigUpdatePic(curItem->GetPath());
    _selected_item = curItem;
    this->setCurrentItem(curItem);
}

void ProTreeWidget::SlotSetMusic()
{
    QFileDialog file_dialog;
    file_dialog.setFileMode(QFileDialog::ExistingFiles);
    file_dialog.setWindowTitle(tr("选择音频文件"));
    file_dialog.setDirectory(QDir::currentPath());
    file_dialog.setViewMode(QFileDialog::Detail);
    file_dialog.setNameFilter("(*.mp3)");
    QStringList fileNames;
    if(file_dialog.exec()){
        fileNames = file_dialog.selectedFiles();
    }else{
        return;
    }

    if(fileNames.length() <=0){
        return;
    }


}


