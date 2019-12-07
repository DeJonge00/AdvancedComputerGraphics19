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
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "mainview.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QGroupBox *SettingsGB;
    QLabel *RotationLabel;
    QDial *RotationDial;
    QSpinBox *SubdivSteps;
    QPushButton *ImportOBJ;
    QLabel *StepsLabel;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *positionModeLabel;
    QCheckBox *wireframeCheckbox;
    QCheckBox *limitPositionCheckbox;
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
        SettingsGB = new QGroupBox(centralWidget);
        SettingsGB->setObjectName(QString::fromUtf8("SettingsGB"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SettingsGB->sizePolicy().hasHeightForWidth());
        SettingsGB->setSizePolicy(sizePolicy);
        SettingsGB->setMinimumSize(QSize(220, 0));
        RotationLabel = new QLabel(SettingsGB);
        RotationLabel->setObjectName(QString::fromUtf8("RotationLabel"));
        RotationLabel->setGeometry(QRect(20, 110, 181, 20));
        RotationDial = new QDial(SettingsGB);
        RotationDial->setObjectName(QString::fromUtf8("RotationDial"));
        RotationDial->setGeometry(QRect(70, 140, 71, 71));
        RotationDial->setMaximum(359);
        RotationDial->setWrapping(true);
        RotationDial->setNotchTarget(12.000000000000000);
        RotationDial->setNotchesVisible(true);
        SubdivSteps = new QSpinBox(SettingsGB);
        SubdivSteps->setObjectName(QString::fromUtf8("SubdivSteps"));
        SubdivSteps->setGeometry(QRect(20, 260, 181, 29));
        ImportOBJ = new QPushButton(SettingsGB);
        ImportOBJ->setObjectName(QString::fromUtf8("ImportOBJ"));
        ImportOBJ->setGeometry(QRect(20, 40, 181, 28));
        StepsLabel = new QLabel(SettingsGB);
        StepsLabel->setObjectName(QString::fromUtf8("StepsLabel"));
        StepsLabel->setGeometry(QRect(20, 230, 181, 20));
        verticalLayoutWidget = new QWidget(SettingsGB);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(19, 319, 181, 101));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        positionModeLabel = new QLabel(verticalLayoutWidget);
        positionModeLabel->setObjectName(QString::fromUtf8("positionModeLabel"));
        positionModeLabel->setMaximumSize(QSize(200, 20));
        positionModeLabel->setLayoutDirection(Qt::LeftToRight);
        positionModeLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout->addWidget(positionModeLabel);

        wireframeCheckbox = new QCheckBox(verticalLayoutWidget);
        wireframeCheckbox->setObjectName(QString::fromUtf8("wireframeCheckbox"));
        wireframeCheckbox->setChecked(true);

        verticalLayout->addWidget(wireframeCheckbox);

        limitPositionCheckbox = new QCheckBox(verticalLayoutWidget);
        limitPositionCheckbox->setObjectName(QString::fromUtf8("limitPositionCheckbox"));

        verticalLayout->addWidget(limitPositionCheckbox);


        horizontalLayout->addWidget(SettingsGB);

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
        SettingsGB->setTitle(QApplication::translate("MainWindow", "Settings", nullptr));
        RotationLabel->setText(QApplication::translate("MainWindow", "Rotation around Y-axis", nullptr));
        ImportOBJ->setText(QApplication::translate("MainWindow", "Import OBJ file", nullptr));
        StepsLabel->setText(QApplication::translate("MainWindow", "Catmull-Clark steps", nullptr));
        positionModeLabel->setText(QApplication::translate("MainWindow", "Mode", nullptr));
        wireframeCheckbox->setText(QApplication::translate("MainWindow", "Wireframe", nullptr));
        limitPositionCheckbox->setText(QApplication::translate("MainWindow", "Limit position", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
