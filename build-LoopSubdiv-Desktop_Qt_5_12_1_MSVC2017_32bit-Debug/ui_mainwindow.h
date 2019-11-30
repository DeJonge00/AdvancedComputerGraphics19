/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDial>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>
#include "mainview.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QGroupBox *OptionsGB;
    QSpinBox *SubdivSteps;
    QLabel *SubdivLabel;
    QLabel *RotateLabel;
    QDial *RotateDial;
    QPushButton *LoadOBJ;
    QCheckBox *wireframeCheckBox;
    QCheckBox *reflectionLinesCheckBox;
    QSpinBox *reflectionLineNumber;
    QLabel *reflectionLinesLabel;
    QLabel *gaussianLabel;
    QCheckBox *gaussianCheckBox;
    MainView *MainDisplay;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1366, 768);
        MainWindow->setStyleSheet(QString::fromUtf8("/* Groupbox */\n"
"\n"
"QGroupBox {\n"
"    border: 1px solid #DDD;\n"
"    border-radius: 9px;\n"
"    margin-top: 9px;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    left: 10px;\n"
"    padding: 0 3px 0 3px;\n"
"}"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(6, 6, 6, 6);
        OptionsGB = new QGroupBox(centralWidget);
        OptionsGB->setObjectName(QString::fromUtf8("OptionsGB"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(OptionsGB->sizePolicy().hasHeightForWidth());
        OptionsGB->setSizePolicy(sizePolicy);
        OptionsGB->setMinimumSize(QSize(220, 0));
        SubdivSteps = new QSpinBox(OptionsGB);
        SubdivSteps->setObjectName(QString::fromUtf8("SubdivSteps"));
        SubdivSteps->setEnabled(false);
        SubdivSteps->setGeometry(QRect(20, 240, 181, 22));
        SubdivSteps->setMaximum(8);
        SubdivLabel = new QLabel(OptionsGB);
        SubdivLabel->setObjectName(QString::fromUtf8("SubdivLabel"));
        SubdivLabel->setGeometry(QRect(20, 220, 181, 16));
        RotateLabel = new QLabel(OptionsGB);
        RotateLabel->setObjectName(QString::fromUtf8("RotateLabel"));
        RotateLabel->setGeometry(QRect(20, 100, 181, 16));
        RotateDial = new QDial(OptionsGB);
        RotateDial->setObjectName(QString::fromUtf8("RotateDial"));
        RotateDial->setGeometry(QRect(20, 120, 50, 64));
        RotateDial->setMaximum(359);
        RotateDial->setValue(0);
        RotateDial->setSliderPosition(0);
        RotateDial->setTracking(true);
        RotateDial->setOrientation(Qt::Vertical);
        RotateDial->setInvertedAppearance(false);
        RotateDial->setInvertedControls(false);
        RotateDial->setWrapping(true);
        RotateDial->setNotchTarget(12.000000000000000);
        RotateDial->setNotchesVisible(true);
        LoadOBJ = new QPushButton(OptionsGB);
        LoadOBJ->setObjectName(QString::fromUtf8("LoadOBJ"));
        LoadOBJ->setGeometry(QRect(20, 30, 181, 21));
        LoadOBJ->setCheckable(false);
        wireframeCheckBox = new QCheckBox(OptionsGB);
        wireframeCheckBox->setObjectName(QString::fromUtf8("wireframeCheckBox"));
        wireframeCheckBox->setGeometry(QRect(20, 280, 181, 17));
        wireframeCheckBox->setChecked(true);
        reflectionLinesCheckBox = new QCheckBox(OptionsGB);
        reflectionLinesCheckBox->setObjectName(QString::fromUtf8("reflectionLinesCheckBox"));
        reflectionLinesCheckBox->setGeometry(QRect(20, 340, 181, 17));
        reflectionLinesCheckBox->setChecked(false);
        reflectionLineNumber = new QSpinBox(OptionsGB);
        reflectionLineNumber->setObjectName(QString::fromUtf8("reflectionLineNumber"));
        reflectionLineNumber->setEnabled(true);
        reflectionLineNumber->setGeometry(QRect(20, 360, 181, 22));
        reflectionLineNumber->setMinimum(2);
        reflectionLineNumber->setMaximum(20);
        reflectionLinesLabel = new QLabel(OptionsGB);
        reflectionLinesLabel->setObjectName(QString::fromUtf8("reflectionLinesLabel"));
        reflectionLinesLabel->setGeometry(QRect(20, 320, 181, 16));
        gaussianLabel = new QLabel(OptionsGB);
        gaussianLabel->setObjectName(QString::fromUtf8("gaussianLabel"));
        gaussianLabel->setGeometry(QRect(20, 410, 181, 16));
        gaussianCheckBox = new QCheckBox(OptionsGB);
        gaussianCheckBox->setObjectName(QString::fromUtf8("gaussianCheckBox"));
        gaussianCheckBox->setGeometry(QRect(20, 430, 181, 17));
        gaussianCheckBox->setChecked(false);

        horizontalLayout->addWidget(OptionsGB);

        MainDisplay = new MainView(centralWidget);
        MainDisplay->setObjectName(QString::fromUtf8("MainDisplay"));

        horizontalLayout->addWidget(MainDisplay);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        OptionsGB->setTitle(QApplication::translate("MainWindow", "Options", nullptr));
        SubdivLabel->setText(QApplication::translate("MainWindow", "Loop subdivision steps", nullptr));
        RotateLabel->setText(QApplication::translate("MainWindow", "Rotation around Y-axis", nullptr));
        LoadOBJ->setText(QApplication::translate("MainWindow", "Load OBJ file", nullptr));
        wireframeCheckBox->setText(QApplication::translate("MainWindow", "Wireframe", nullptr));
        reflectionLinesCheckBox->setText(QApplication::translate("MainWindow", "Enabled", nullptr));
        reflectionLinesLabel->setText(QApplication::translate("MainWindow", "Loop subdivision steps", nullptr));
        gaussianLabel->setText(QApplication::translate("MainWindow", "Gaussian curvature", nullptr));
        gaussianCheckBox->setText(QApplication::translate("MainWindow", "Enabled", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
