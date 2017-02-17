#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <vector>
#include "abstractconversion.h"
#include "conversions.h"
#include "conffile.h"
#include "conversiontool.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    ConversionTool getConvTool() const;

private slots:
    void openFile();
    void saveFile();
    void openConf();
    void saveConf();
    void editImage();
    void changeMode();
    void about();
    void aboutQt();
    void help();
private:

    void setEnableRange(const bool b);
    void setEnableDuotone(const bool b);
    void setConf(const QDomDocument &doc);
    Ui::MainWindow *ui;

    QImage orginal,orginal500;
    QGraphicsScene scene;
};

#endif // MAINWINDOW_H
