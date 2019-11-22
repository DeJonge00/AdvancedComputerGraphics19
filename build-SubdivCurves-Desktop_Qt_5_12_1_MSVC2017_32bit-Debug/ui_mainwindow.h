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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>
#include "mainview.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QGroupBox *mainGB;
    QGroupBox *renderGB;
    QCheckBox *controlNet;
    QCheckBox *curvePoints;
    QSpinBox *subdivSteps;
    QLabel *maskLabel;
    QLabel *stepsLabel;
    QLabel *presetLabel;
    QComboBox *netPresets;
    QLineEdit *subdivMask;
    MainView *mainView;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1356, 768);
        MainWindow->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    border: 1px solid #CCCCCC;\n"
"    border-radius: 9px;\n"
"    margin-top: 8px;\n"
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
        mainGB = new QGroupBox(centralWidget);
        mainGB->setObjectName(QString::fromUtf8("mainGB"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mainGB->sizePolicy().hasHeightForWidth());
        mainGB->setSizePolicy(sizePolicy);
        mainGB->setMinimumSize(QSize(230, 0));
        mainGB->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    margin-top: 0px;\n"
"}"));
        renderGB = new QGroupBox(mainGB);
        renderGB->setObjectName(QString::fromUtf8("renderGB"));
        renderGB->setGeometry(QRect(20, 20, 191, 91));
        controlNet = new QCheckBox(renderGB);
        controlNet->setObjectName(QString::fromUtf8("controlNet"));
        controlNet->setGeometry(QRect(20, 30, 151, 24));
        curvePoints = new QCheckBox(renderGB);
        curvePoints->setObjectName(QString::fromUtf8("curvePoints"));
        curvePoints->setGeometry(QRect(20, 60, 151, 24));
        subdivSteps = new QSpinBox(mainGB);
        subdivSteps->setObjectName(QString::fromUtf8("subdivSteps"));
        subdivSteps->setGeometry(QRect(40, 330, 151, 27));
        maskLabel = new QLabel(mainGB);
        maskLabel->setObjectName(QString::fromUtf8("maskLabel"));
        maskLabel->setGeometry(QRect(40, 220, 151, 18));
        stepsLabel = new QLabel(mainGB);
        stepsLabel->setObjectName(QString::fromUtf8("stepsLabel"));
        stepsLabel->setGeometry(QRect(40, 300, 151, 18));
        presetLabel = new QLabel(mainGB);
        presetLabel->setObjectName(QString::fromUtf8("presetLabel"));
        presetLabel->setGeometry(QRect(40, 140, 151, 18));
        netPresets = new QComboBox(mainGB);
        netPresets->setObjectName(QString::fromUtf8("netPresets"));
        netPresets->setGeometry(QRect(40, 170, 151, 26));
        subdivMask = new QLineEdit(mainGB);
        subdivMask->setObjectName(QString::fromUtf8("subdivMask"));
        subdivMask->setGeometry(QRect(40, 250, 151, 26));

        horizontalLayout->addWidget(mainGB);

        mainView = new MainView(centralWidget);
        mainView->setObjectName(QString::fromUtf8("mainView"));

        horizontalLayout->addWidget(mainView);

        MainWindow->setCentralWidget(centralWidget);
        QWidget::setTabOrder(controlNet, curvePoints);
        QWidget::setTabOrder(curvePoints, netPresets);
        QWidget::setTabOrder(netPresets, subdivMask);
        QWidget::setTabOrder(subdivMask, subdivSteps);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        mainGB->setTitle(QString());
        renderGB->setTitle(QApplication::translate("MainWindow", "Render", nullptr));
        controlNet->setText(QApplication::translate("MainWindow", "Control net", nullptr));
        curvePoints->setText(QApplication::translate("MainWindow", "Curve points", nullptr));
        maskLabel->setText(QApplication::translate("MainWindow", "Mask", nullptr));
        stepsLabel->setText(QApplication::translate("MainWindow", "Steps", nullptr));
        presetLabel->setText(QApplication::translate("MainWindow", "Preset", nullptr));
        subdivMask->setText(QApplication::translate("MainWindow", "1 4 6 4 1", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
