#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QToolButton>
#include <QRadioButton>
#include <QSlider>
#include <QCloseEvent>

#include "drawCanvas.h"
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow(){
        delete _FileOpen;
        delete _FileSave;
        delete _FileQuit;

        delete _Menubar;
        delete _Toolbar;

        delete _DrawCanvas;
        delete _DrawWhite;
        delete _DrawBlack;
        delete _DrawRed;
        delete _DrawGreen;
        delete _DrawBlue;

        delete _DrawThicknessSlider;

        delete _DrawLine;
        delete _DrawDashLine;
        delete _DrawDashDotLine;
        delete _DrawDotLine;
        delete _DrawLineShape;
        delete _DrawRectangleShape;
        delete _DrawEllipseShape;
    }

private:
    Ui::MainWindow *ui;
    DrawCanvas* _DrawCanvas{};
    QAction* _FileOpen;
    QAction* _FileSave;
    QAction* _FileQuit;

    QMenuBar* _Menubar;
    QToolBar* _Toolbar;

    QRadioButton* _DrawWhite{};
    QRadioButton* _DrawBlack{};
    QRadioButton* _DrawRed{};
    QRadioButton* _DrawGreen{};
    QRadioButton* _DrawBlue{};
    QSlider* _DrawThicknessSlider{};
    QRadioButton* _DrawLine{};
    QRadioButton* _DrawDashLine{};
    QRadioButton* _DrawDashDotLine{};
    QRadioButton* _DrawDotLine{};
    QRadioButton* _DrawLineShape{};
    QRadioButton* _DrawRectangleShape{};
    QRadioButton* _DrawEllipseShape{};

    QString openFileDialog();
    void createToolBar();
    void createDrawToolBar();
    void createMenuBar();
    void initActions();

protected:
    void closeEvent(QCloseEvent* event);

public slots:
    void fileOpen();
    void fileSave();
    void fileQuit();

    void setColor(QAbstractButton* sender);
    void setThickness(int newThickness);
    void setStyle(QAbstractButton* sender);
    void setShape(QAbstractButton* sender);
};
#endif // MAINWINDOW_H
