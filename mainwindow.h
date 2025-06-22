#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QWidget* _protree;
    QWidget* _picshow;

private slots:
    void SlotCreatePro(bool);
    void SlotOpenPro(bool);
protected:
    virtual void resizeEvent(QResizeEvent * event);

signals:
    void SigOpenPro(const QString &path);

};
#endif // MAINWINDOW_H
