#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "objfile.h"
#include <QFileDialog>
#include "mesh.h"
#include "meshtools.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {

    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void loadOBJ();
    QVector<Mesh> meshes;

private slots:
    void on_RotateDial_valueChanged(int value);
    void on_SubdivSteps_valueChanged(int value);
    void on_LoadOBJ_clicked();
    void on_wireframeCheckBox_stateChanged(int enabled);
    void on_reflectionLinesCheckBox_stateChanged(int enabled);

    void on_reflectionLineNumber_valueChanged(int number);

    void on_gaussianCheckBox_stateChanged(int enabled);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
