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
    QPushButton *ImportOBJ;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *catmulClarkVLayout;
    QLabel *StepsLabel;
    QSpinBox *SubdivSteps;
    QLabel *positionModeLabel;
    QCheckBox *wireframeCheckbox;
    QCheckBox *limitPositionCheckbox;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *tessellationVLayout;
    QLabel *tessallationLabel;
    QCheckBox *tessellationEnabled;
    QSpinBox *tessallationLevelInner;
    QSpinBox *tessallationLevelOuter;
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
        ImportOBJ = new QPushButton(SettingsGB);
        ImportOBJ->setObjectName(QString::fromUtf8("ImportOBJ"));
        ImportOBJ->setGeometry(QRect(20, 40, 181, 28));
        verticalLayoutWidget = new QWidget(SettingsGB);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(19, 235, 181, 111));
        catmulClarkVLayout = new QVBoxLayout(verticalLayoutWidget);
        catmulClarkVLayout->setSpacing(6);
        catmulClarkVLayout->setContentsMargins(11, 11, 11, 11);
        catmulClarkVLayout->setObjectName(QString::fromUtf8("catmulClarkVLayout"));
        catmulClarkVLayout->setContentsMargins(0, 0, 0, 0);
        StepsLabel = new QLabel(verticalLayoutWidget);
        StepsLabel->setObjectName(QString::fromUtf8("StepsLabel"));

        catmulClarkVLayout->addWidget(StepsLabel);

        SubdivSteps = new QSpinBox(verticalLayoutWidget);
        SubdivSteps->setObjectName(QString::fromUtf8("SubdivSteps"));

        catmulClarkVLayout->addWidget(SubdivSteps);

        positionModeLabel = new QLabel(verticalLayoutWidget);
        positionModeLabel->setObjectName(QString::fromUtf8("positionModeLabel"));
        positionModeLabel->setMaximumSize(QSize(200, 20));
        positionModeLabel->setLayoutDirection(Qt::LeftToRight);
        positionModeLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        catmulClarkVLayout->addWidget(positionModeLabel);

        wireframeCheckbox = new QCheckBox(verticalLayoutWidget);
        wireframeCheckbox->setObjectName(QString::fromUtf8("wireframeCheckbox"));
        wireframeCheckbox->setChecked(true);

        catmulClarkVLayout->addWidget(wireframeCheckbox);

        limitPositionCheckbox = new QCheckBox(verticalLayoutWidget);
        limitPositionCheckbox->setObjectName(QString::fromUtf8("limitPositionCheckbox"));

        catmulClarkVLayout->addWidget(limitPositionCheckbox);

        verticalLayoutWidget_2 = new QWidget(SettingsGB);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(20, 360, 181, 86));
        tessellationVLayout = new QVBoxLayout(verticalLayoutWidget_2);
        tessellationVLayout->setSpacing(6);
        tessellationVLayout->setContentsMargins(11, 11, 11, 11);
        tessellationVLayout->setObjectName(QString::fromUtf8("tessellationVLayout"));
        tessellationVLayout->setContentsMargins(0, 0, 0, 0);
        tessallationLabel = new QLabel(verticalLayoutWidget_2);
        tessallationLabel->setObjectName(QString::fromUtf8("tessallationLabel"));
        tessallationLabel->setMaximumSize(QSize(200, 20));
        tessallationLabel->setLayoutDirection(Qt::LeftToRight);
        tessallationLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        tessellationVLayout->addWidget(tessallationLabel);

        tessellationEnabled = new QCheckBox(verticalLayoutWidget_2);
        tessellationEnabled->setObjectName(QString::fromUtf8("tessellationEnabled"));

        tessellationVLayout->addWidget(tessellationEnabled);

        tessallationLevelInner = new QSpinBox(verticalLayoutWidget_2);
        tessallationLevelInner->setObjectName(QString::fromUtf8("tessallationLevelInner"));
        tessallationLevelInner->setMinimum(1);
        tessallationLevelInner->setMaximum(10);
        tessallationLevelInner->setValue(2);

        tessellationVLayout->addWidget(tessallationLevelInner);

        tessallationLevelOuter = new QSpinBox(verticalLayoutWidget_2);
        tessallationLevelOuter->setObjectName(QString::fromUtf8("tessallationLevelOuter"));
        tessallationLevelOuter->setMinimum(1);
        tessallationLevelOuter->setMaximum(10);
        tessallationLevelOuter->setValue(2);

        tessellationVLayout->addWidget(tessallationLevelOuter);


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
        tessallationLabel->setText(QApplication::translate("MainWindow", "Tessallation Levels", nullptr));
        tessellationEnabled->setText(QApplication::translate("MainWindow", "Enable", nullptr));
        tessallationLevelInner->setSuffix(QApplication::translate("MainWindow", " levels", nullptr));
        tessallationLevelInner->setPrefix(QApplication::translate("MainWindow", "Inner: ", nullptr));
        tessallationLevelOuter->setSuffix(QApplication::translate("MainWindow", " levels", nullptr));
        tessallationLevelOuter->setPrefix(QApplication::translate("MainWindow", "Outer: ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
