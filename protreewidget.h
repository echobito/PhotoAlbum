#ifndef PROTREEWIDGET_H
#define PROTREEWIDGET_H

#include <QTreeWidget>
#include <QAction>
#include <QProgressDialog>
#include "protreethread.h"
#include "opentreethread.h"
#include <QtMultimedia/QMediaPlayer>
#include <QUrl>

class SlideShowDlg;

class ProTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    ProTreeWidget(QWidget * parent = nullptr);
    void AddProToTree(const QString& name, const QString& path);
private:
    QSet<QString> _set_path;
    //右键单击某个item之后弹出来菜单
    QTreeWidgetItem * _right_btn_item;
    QTreeWidgetItem * _active_item;
    QTreeWidgetItem * _selected_item;
    QAction * _action_import;
    QAction * _action_setstart;
    QAction * _action_closepro;
    QAction * _action_slideshow;
    QProgressDialog * _dialog_progress;
    QProgressDialog * _open_dialog_progress;
    std::shared_ptr<ProTreeThread> _thread_create_pro;
    std::shared_ptr<OpenTreeThread> _thread_open_pro;
    std::shared_ptr<SlideShowDlg> _slide_show_dlg;
    QMediaPlayer * _player;
private slots:
    void SlotItemPressed(QTreeWidgetItem *item, int column);
    void SlotImport();
    void SlotSetActive();
    void SlotUpdateProgress(int count);
    void SlotFinishProgress();
    void SlotCancelProgress();
    void SlotUpOpenProgress(int count);
    void SlotFinishOpenProgress();
    void SlotCancelOpenProgress();
    void SlotClosePro();
    void SlotDoubleClickItem(QTreeWidgetItem * doubleItem, int col);

    void SlotSlideShow();
public slots:
    void SlotOpenPro(const QString& path);
    void SlotNextShow();
    void SlotPreShow();
    void SlotSetMusic();

signals:
    void SigCancelProgress();
    void SigCancelOpenProgress();
    void SigUpdateSelected(const QString& );
    void SigUpdatePic(const QString& );
    void SigClearSelected();
};

#endif // PROTREEWIDGET_H
