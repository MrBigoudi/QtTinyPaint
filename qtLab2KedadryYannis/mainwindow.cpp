#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFileDialog>
#include <QPushButton>
#include <QButtonGroup>
#include <QLabel>
#include <iostream>
#include <QMessageBox>

void MainWindow::setThickness(int newThickness){
    _DrawCanvas->setThickness(newThickness);
}

void MainWindow::setShape(QAbstractButton *sender){
    if(sender == _DrawLineShape){
        _DrawCanvas->setShape(LINE_SHAPE);
    } else if(sender == _DrawRectangleShape){
        _DrawCanvas->setShape(RECTANGLE_SHAPE);
    } else if(sender == _DrawEllipseShape){
        _DrawCanvas->setShape(ELLIPSE_SHAPE);
    }
}

void MainWindow::setStyle(QAbstractButton *sender){
    if(sender == _DrawLine){
        _DrawCanvas->setStyle(LINE);
    } else if(sender == _DrawDashLine){
        _DrawCanvas->setStyle(DASH_LINE);
    } else if(sender == _DrawDotLine){
        _DrawCanvas->setStyle(DOT_LINE);
    } else if(sender == _DrawDashDotLine){
        _DrawCanvas->setStyle(DASH_DOT_LINE);
    }
}

void MainWindow::setColor(QAbstractButton* sender){
    if(sender == _DrawWhite){
        _DrawCanvas->setColor(WHITE);
    } else if(sender == _DrawBlack){
        _DrawCanvas->setColor(BLACK);
    } else if(sender == _DrawRed){
        _DrawCanvas->setColor(RED);
    } else if(sender == _DrawGreen){
        _DrawCanvas->setColor(GREEN);
    } else if(sender == _DrawBlue){
        _DrawCanvas->setColor(BLUE);
    }
}

QString MainWindow::openFileDialog(){
    return
        QFileDialog::getOpenFileName(this,
                                     tr("Open file"), //title
                                     "/home", // directory
                                     tr("Html file (*.html *.txt)") // filter
                                     );
}

void MainWindow::fileOpen(){
    QString fileName = openFileDialog();
    std::cout << "Open file: " << qPrintable(fileName) << std::endl;
}

void MainWindow::fileSave(){
    QString fileName = openFileDialog();
    QFile file(fileName);
    std::cout << "Save file: " << qPrintable(fileName) << std::endl;
}

void MainWindow::fileQuit(){
    QMessageBox msgBox;
    msgBox.setInformativeText("Do you want to quit the app?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int ret = msgBox.exec();
    switch(ret){
        case QMessageBox::Cancel:
            break;
        case QMessageBox::Yes:
            qApp->quit();
            break;
    }
}

void MainWindow::closeEvent(QCloseEvent* event){
    event->ignore();
    fileQuit();
}

void MainWindow::initActions(){
    // add the actions to the file menu
    _FileOpen = new QAction(QIcon(":/Media/images/open.png"), tr("&Open..."), this);
    _FileSave = new QAction(QIcon(":/Media/images/save.png"), tr("&Save..."), this);
    _FileQuit = new QAction(QIcon(":/Media/images/quit.png"), tr("&Quit..."), this);

    // add the connections
    connect(_FileOpen, &QAction::triggered, this, &MainWindow::fileOpen);
    connect(_FileSave, &QAction::triggered, this, &MainWindow::fileSave);
    connect(_FileQuit, &QAction::triggered, this, &MainWindow::fileQuit);

    // add the actions for the draw color
    auto* group = new QButtonGroup(this);
    connect(group, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(setColor(QAbstractButton*)));
    //_DrawWhite = new QRadioButton(tr("WHITE"));
    //_DrawBlack = new QRadioButton(tr("BLACK"));
    //_DrawRed   = new QRadioButton(tr("RED"));
    //_DrawGreen = new QRadioButton(tr("GREEN"));
    //_DrawBlue  = new QRadioButton(tr("BLUE"));

    group->addButton(_DrawWhite);
    group->addButton(_DrawBlack);
    group->addButton(_DrawRed);
    group->addButton(_DrawGreen);
    group->addButton(_DrawBlue);
    _DrawBlack->setChecked(true);

    // add the action for the draw thickness
    //_DrawThicknessSlider = new QSlider(Qt::Horizontal, this);

    _DrawThicknessSlider->setRange(1,20);
    _DrawThicknessSlider->setValue(2);
    connect(_DrawThicknessSlider, SIGNAL(valueChanged(int)), this, SLOT(setThickness(int)));

    // add the actions for the draw style
    auto* groupStyle = new QButtonGroup(this);
    connect(groupStyle, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(setStyle(QAbstractButton*)));
    //_DrawLine        = new QRadioButton(tr("LINE"));
    //_DrawDashLine    = new QRadioButton(tr("DASH"));
    //_DrawDotLine     = new QRadioButton(tr("DOT"));
    //_DrawDashDotLine = new QRadioButton(tr("DASH_DOT"));

    groupStyle->addButton(_DrawLine);
    groupStyle->addButton(_DrawDashLine);
    groupStyle->addButton(_DrawDotLine);
    groupStyle->addButton(_DrawDashDotLine);
    _DrawLine->setChecked(true);

    // add the actions for the draw shape
    auto* groupShape = new QButtonGroup(this);
    connect(groupShape, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(setShape(QAbstractButton*)));
    //_DrawLineShape      = new QRadioButton(tr("LINE"));
    //_DrawRectangleShape = new QRadioButton(tr("RECT"));
    //_DrawEllipseShape   = new QRadioButton(tr("ELLIPSE"));

    groupShape->addButton(_DrawLineShape);
    groupShape->addButton(_DrawRectangleShape);
    groupShape->addButton(_DrawEllipseShape);
    _DrawLineShape->setChecked(true);
}

void MainWindow::createToolBar(){
    // create the tool bar
    _Toolbar = new QToolBar(this);
    _Toolbar->addAction(_FileOpen);
    _Toolbar->addAction(_FileSave);
    _Toolbar->addAction(_FileQuit);

    addToolBar(_Toolbar);
}

void MainWindow::createDrawToolBar(){
    // add the color buttons to the toolbar
    QWidget* w = new QWidget;
    QHBoxLayout* layout = new QHBoxLayout(w);
    // color layout
    QVBoxLayout* lColor = new QVBoxLayout();
    QLabel* cLabel = new QLabel("Color",this);
    cLabel->setAlignment(Qt::AlignCenter);
    QHBoxLayout* l1 = new QHBoxLayout();
    l1->addWidget(_DrawWhite);
    l1->addWidget(_DrawBlack);
    l1->addWidget(_DrawRed);
    l1->addWidget(_DrawGreen);
    l1->addWidget(_DrawBlue);
    lColor->addLayout(l1);
    lColor->addWidget(cLabel);

    // thickness layout
    QVBoxLayout* lThickness = new QVBoxLayout();
    QLabel* tLabel = new QLabel("Thickness",this);
    tLabel->setAlignment(Qt::AlignCenter);
    _DrawThicknessSlider->setFixedWidth(100);
    lThickness->addWidget(_DrawThicknessSlider);
    lThickness->addWidget(tLabel);

    // style layout
    QVBoxLayout* lStyle = new QVBoxLayout();
    QLabel* sLabel = new QLabel("Style",this);
    sLabel->setAlignment(Qt::AlignCenter);
    QHBoxLayout* l2 = new QHBoxLayout();
    l2->addWidget(_DrawLine);
    l2->addWidget(_DrawDashLine);
    l2->addWidget(_DrawDotLine);
    l2->addWidget(_DrawDashDotLine);
    lStyle->addLayout(l2);
    lStyle->addWidget(sLabel);

    // shape layout
    QVBoxLayout* lShape = new QVBoxLayout();
    QLabel* shLabel = new QLabel("Shape",this);
    shLabel->setAlignment(Qt::AlignCenter);
    QHBoxLayout* l3 = new QHBoxLayout();
    l3->addWidget(_DrawLineShape);
    l3->addWidget(_DrawRectangleShape);
    l3->addWidget(_DrawEllipseShape);
    lShape->addLayout(l3);
    lShape->addWidget(shLabel);

    // merge the layouts
    layout->addLayout(lColor, 1);
    layout->addLayout(lThickness, 2);
    layout->addLayout(lStyle, 1);
    layout->addLayout(lShape,1);

    _Toolbar->addWidget(w);
}

void MainWindow::createMenuBar(){
    // create the menu bar
    _Menubar = this->menuBar();
    // add a file menu to the menubar
    QMenu fMenu(_Menubar->addMenu(tr("&File")));

    fMenu.addAction(_FileOpen);
    fMenu.addAction(_FileSave);
    fMenu.addAction(_FileQuit);
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){

    ui->setupUi(this);

    // create the status bar
    this->statusBar();

    _DrawCanvas = findChild<DrawCanvas*>("drawingCanvas");

    _DrawWhite = findChild<QRadioButton*>("radioButton_white");
    _DrawBlack = findChild<QRadioButton*>("radioButton_black");
    _DrawRed   = findChild<QRadioButton*>("radioButton_red");
    _DrawGreen = findChild<QRadioButton*>("radioButton_green");
    _DrawBlue  = findChild<QRadioButton*>("radioButton_blue");

    _DrawThicknessSlider = findChild<QSlider*>("horizontalSlider_thick");

    _DrawLine        = findChild<QRadioButton*>("radioButton_type_line");
    _DrawDashLine    = findChild<QRadioButton*>("radioButton_type_dash");
    _DrawDotLine     = findChild<QRadioButton*>("radioButton_type_dot");
    _DrawDashDotLine = findChild<QRadioButton*>("radioButton_type_dashdot");

    _DrawLineShape      = findChild<QRadioButton*>("radioButton_line");
    _DrawRectangleShape = findChild<QRadioButton*>("radioButton_rectangle");
    _DrawEllipseShape   = findChild<QRadioButton*>("radioButton_ellipse");

    initActions();
    createMenuBar();
    createToolBar();
}
