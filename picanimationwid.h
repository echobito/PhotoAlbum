#ifndef PICANIMATIONWID_H
#define PICANIMATIONWID_H
#include <QWidget>
#include <QTreeWidgetItem>
#include <QMap>

class PicAnimationWid : public QWidget
{
    Q_OBJECT
public:
    explicit PicAnimationWid(QWidget *parent = nullptr);
    ~PicAnimationWid();

    void SetPixmap(QTreeWidgetItem * item); // 设置第一张图片
    void Start();   // 开始动画
    void Stop();    // 停止动画
    void SlideNext();
    void SlidePre();
protected:
    virtual void paintEvent(QPaintEvent *event);

private:
    float _factor;                  // 动画因子
    QTimer* _timer;                 // 更新factor
    //双缓冲绘图
    QPixmap _pixmap1;               // 两张图片实现双缓冲绘图
    QPixmap _pixmap2;
    QTreeWidgetItem * _cur_item;    // 当前图片
    QMap<QString, QTreeWidgetItem*> _map_items; // 哪些播放过
    bool _b_start;  // 当前是否开始

    void UpSelectPixmap(QTreeWidgetItem* item);
public slots:
    void SlotUpSelectShow(QString path);
    void SlotStartOrStop();
private slots:
    void TimeOut();
signals:
    void SigUpPreList(QTreeWidgetItem* );
    void SigSelectItem(QTreeWidgetItem* );
    void SigStart();
    void SigStop();
};

#endif // PICANIMATIONWID_H
