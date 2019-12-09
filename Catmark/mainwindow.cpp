#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :  QMainWindow(parent), ui(new Ui::MainWindow) {
    qDebug() << "✓✓ MainWindow constructor";
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    qDebug() << "✗✗ MainWindow destructor";
    delete ui;

    Meshes.clear();
    Meshes.squeeze();
}

void MainWindow::importOBJ() {
    OBJFile newModel = OBJFile(QFileDialog::getOpenFileName(this, "Import OBJ File", "models/", tr("Obj Files (*.obj)")));
    Meshes.clear();
    Meshes.squeeze();
    Meshes.append( Mesh(&newModel) );

    ui->MainDisplay->updateMeshBuffers( Meshes[0] );
    ui->MainDisplay->modelLoaded = true;

    ui->MainDisplay->update();
}

void MainWindow::on_ImportOBJ_clicked() {
    importOBJ();
    ui->SubdivSteps->setEnabled(true);
}

void MainWindow::on_RotationDial_valueChanged(int value) {
    ui->MainDisplay->rotAngle = value;
    ui->MainDisplay->updateMatrices();
}

void MainWindow::on_SubdivSteps_valueChanged(int value) {
    unsigned short k;

    for (k=Meshes.size(); k<value+1; k++) {
        Meshes.append(Mesh());
        Meshes[k-1].subdivideCatmullClark(Meshes[k]);
    }

    ui->MainDisplay->updateMeshBuffers( Meshes[value] );
}

void MainWindow::on_wireframeCheckbox_stateChanged(int state)
{
    ui->MainDisplay->wireframeMode = state == 2;
    ui->MainDisplay->update();
}

void MainWindow::on_limitPositionCheckbox_stateChanged(int state)
{
    ui->MainDisplay->positionModeLimit = state == 2;
    ui->MainDisplay->updateMeshBuffers( Meshes[ui->SubdivSteps->value()] );
    ui->MainDisplay->update();
}

void MainWindow::on_tessellationEnabled_stateChanged(int value)
{
    ui->MainDisplay->tessellation = value == 2;
    ui->MainDisplay->uniformUpdateRequired = true;
    ui->MainDisplay->setMatrices();
    ui->MainDisplay->updateMeshBuffers( Meshes[ui->SubdivSteps->value()] );
    ui->MainDisplay->update();
}

void MainWindow::on_tessallationLevelOuter_valueChanged(int value)
{
    ui->MainDisplay->outer_tessellation = value;
    ui->MainDisplay->uniformUpdateRequired = true;
    ui->MainDisplay->update();
}

void MainWindow::on_tessallationLevelInner_valueChanged(int value)
{
    ui->MainDisplay->inner_tessellation = value;
    ui->MainDisplay->uniformUpdateRequired = true;
    ui->MainDisplay->update();
}
