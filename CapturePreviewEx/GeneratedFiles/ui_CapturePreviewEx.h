/********************************************************************************
** Form generated from reading UI file 'CapturePreviewEx.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAPTUREPREVIEWEX_H
#define UI_CAPTUREPREVIEWEX_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QOpenGLWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CapturePreviewExClass
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout1;
    QLabel *LoomLogoBox;
    QLabel *label_25;
    QHBoxLayout *horizontalLayout_2;
    QLabel *deviceLabel;
    QComboBox *deviceListComboBox;
    QLabel *signalInfoLabel;
    QGroupBox *propertiesGroupBox;
    QWidget *formLayoutWidget_2;
    QFormLayout *formLayout_2;
    QLabel *applyDetectedInputForwardLabel;
    QCheckBox *applyDetectedInputForwardCheckBox;
    QLabel *videoFormatLabel;
    QComboBox *videoFormatComboBox;
    QPushButton *startStopButton;
    QGroupBox *anciliaryDataGroupBox;
    QHBoxLayout *horizontalLayout_5;
    QFormLayout *formLayout;
    QLabel *vITCTimecodeField1Label;
    QLabel *vitcTcF1;
    QLabel *vITCUserbitsField1Label;
    QLabel *vitcUbF1;
    QLabel *vITCTimecodeField2Label;
    QLabel *vitcTcF2;
    QLabel *vITCUserbitsField2Label;
    QLabel *vitcUbF2;
    QLabel *rP188VITC1TimecodeLabel;
    QLabel *rp188Vitc1Tc;
    QLabel *rP188VITC1UserbitsLabel;
    QLabel *rp188Vitc1Ub;
    QLabel *rP188VITC2TimecodeLabel;
    QLabel *rp188Vitc2Tc;
    QLabel *rP188VITC2UserbitsLabel;
    QLabel *rp188Vitc2Ub;
    QLabel *rP188LTCTimecodeLabel;
    QLabel *rp188LtcTc;
    QLabel *rP188LTCUsebitsLabel;
    QLabel *rp188LtcUb;
    QPushButton *startStopButton2;
    QPushButton *startStopButton3;
    QPushButton *startStopButton4;
    QLabel *label;
    QVBoxLayout *verticalLayout2;
    QTabWidget *previewTab;
    QWidget *tab;
    QHBoxLayout *horizontalLayout_4;
    QGridLayout *gridLayout_2;
    QOpenGLWidget *openGLWidget;
    QLabel *label_23;
    QLabel *label_3;
    QOpenGLWidget *openGLWidget3;
    QOpenGLWidget *openGLWidget4;
    QOpenGLWidget *openGLWidget2;
    QLabel *label_24;
    QLabel *label_27;
    QWidget *tab_2;

    void setupUi(QMainWindow *CapturePreviewExClass)
    {
        if (CapturePreviewExClass->objectName().isEmpty())
            CapturePreviewExClass->setObjectName(QStringLiteral("CapturePreviewExClass"));
        CapturePreviewExClass->resize(1211, 747);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CapturePreviewExClass->sizePolicy().hasHeightForWidth());
        CapturePreviewExClass->setSizePolicy(sizePolicy);
        CapturePreviewExClass->setMinimumSize(QSize(1211, 727));
        QIcon icon;
        icon.addFile(QStringLiteral("Resources/amd_logo.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        CapturePreviewExClass->setWindowIcon(icon);
        CapturePreviewExClass->setDocumentMode(false);
        centralWidget = new QWidget(CapturePreviewExClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_3 = new QHBoxLayout(centralWidget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout1 = new QVBoxLayout();
        verticalLayout1->setSpacing(6);
        verticalLayout1->setObjectName(QStringLiteral("verticalLayout1"));
        verticalLayout1->setSizeConstraint(QLayout::SetFixedSize);
        LoomLogoBox = new QLabel(centralWidget);
        LoomLogoBox->setObjectName(QStringLiteral("LoomLogoBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(LoomLogoBox->sizePolicy().hasHeightForWidth());
        LoomLogoBox->setSizePolicy(sizePolicy1);
        LoomLogoBox->setMinimumSize(QSize(375, 190));
        LoomLogoBox->setMaximumSize(QSize(375, 190));

        verticalLayout1->addWidget(LoomLogoBox);

        label_25 = new QLabel(centralWidget);
        label_25->setObjectName(QStringLiteral("label_25"));
        sizePolicy1.setHeightForWidth(label_25->sizePolicy().hasHeightForWidth());
        label_25->setSizePolicy(sizePolicy1);
        label_25->setMinimumSize(QSize(380, 10));

        verticalLayout1->addWidget(label_25);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        deviceLabel = new QLabel(centralWidget);
        deviceLabel->setObjectName(QStringLiteral("deviceLabel"));
        sizePolicy1.setHeightForWidth(deviceLabel->sizePolicy().hasHeightForWidth());
        deviceLabel->setSizePolicy(sizePolicy1);
        deviceLabel->setMinimumSize(QSize(80, 0));

        horizontalLayout_2->addWidget(deviceLabel);

        deviceListComboBox = new QComboBox(centralWidget);
        deviceListComboBox->setObjectName(QStringLiteral("deviceListComboBox"));
        sizePolicy1.setHeightForWidth(deviceListComboBox->sizePolicy().hasHeightForWidth());
        deviceListComboBox->setSizePolicy(sizePolicy1);
        deviceListComboBox->setMinimumSize(QSize(130, 0));

        horizontalLayout_2->addWidget(deviceListComboBox);

        signalInfoLabel = new QLabel(centralWidget);
        signalInfoLabel->setObjectName(QStringLiteral("signalInfoLabel"));
        sizePolicy1.setHeightForWidth(signalInfoLabel->sizePolicy().hasHeightForWidth());
        signalInfoLabel->setSizePolicy(sizePolicy1);
        signalInfoLabel->setMinimumSize(QSize(130, 0));

        horizontalLayout_2->addWidget(signalInfoLabel);


        verticalLayout1->addLayout(horizontalLayout_2);

        propertiesGroupBox = new QGroupBox(centralWidget);
        propertiesGroupBox->setObjectName(QStringLiteral("propertiesGroupBox"));
        sizePolicy1.setHeightForWidth(propertiesGroupBox->sizePolicy().hasHeightForWidth());
        propertiesGroupBox->setSizePolicy(sizePolicy1);
        propertiesGroupBox->setMinimumSize(QSize(375, 80));
        propertiesGroupBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        formLayoutWidget_2 = new QWidget(propertiesGroupBox);
        formLayoutWidget_2->setObjectName(QStringLiteral("formLayoutWidget_2"));
        formLayoutWidget_2->setGeometry(QRect(20, 20, 341, 51));
        formLayout_2 = new QFormLayout(formLayoutWidget_2);
        formLayout_2->setSpacing(6);
        formLayout_2->setContentsMargins(11, 11, 11, 11);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        applyDetectedInputForwardLabel = new QLabel(formLayoutWidget_2);
        applyDetectedInputForwardLabel->setObjectName(QStringLiteral("applyDetectedInputForwardLabel"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, applyDetectedInputForwardLabel);

        applyDetectedInputForwardCheckBox = new QCheckBox(formLayoutWidget_2);
        applyDetectedInputForwardCheckBox->setObjectName(QStringLiteral("applyDetectedInputForwardCheckBox"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, applyDetectedInputForwardCheckBox);

        videoFormatLabel = new QLabel(formLayoutWidget_2);
        videoFormatLabel->setObjectName(QStringLiteral("videoFormatLabel"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, videoFormatLabel);

        videoFormatComboBox = new QComboBox(formLayoutWidget_2);
        videoFormatComboBox->setObjectName(QStringLiteral("videoFormatComboBox"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, videoFormatComboBox);

        formLayoutWidget_2->raise();
        deviceLabel->raise();

        verticalLayout1->addWidget(propertiesGroupBox);

        startStopButton = new QPushButton(centralWidget);
        startStopButton->setObjectName(QStringLiteral("startStopButton"));
        startStopButton->setEnabled(false);
        sizePolicy1.setHeightForWidth(startStopButton->sizePolicy().hasHeightForWidth());
        startStopButton->setSizePolicy(sizePolicy1);
        startStopButton->setMinimumSize(QSize(200, 0));
        startStopButton->setCheckable(false);

        verticalLayout1->addWidget(startStopButton);

        anciliaryDataGroupBox = new QGroupBox(centralWidget);
        anciliaryDataGroupBox->setObjectName(QStringLiteral("anciliaryDataGroupBox"));
        sizePolicy1.setHeightForWidth(anciliaryDataGroupBox->sizePolicy().hasHeightForWidth());
        anciliaryDataGroupBox->setSizePolicy(sizePolicy1);
        anciliaryDataGroupBox->setMinimumSize(QSize(375, 220));
        horizontalLayout_5 = new QHBoxLayout(anciliaryDataGroupBox);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setLabelAlignment(Qt::AlignJustify|Qt::AlignVCenter);
        formLayout->setFormAlignment(Qt::AlignCenter);
        vITCTimecodeField1Label = new QLabel(anciliaryDataGroupBox);
        vITCTimecodeField1Label->setObjectName(QStringLiteral("vITCTimecodeField1Label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, vITCTimecodeField1Label);

        vitcTcF1 = new QLabel(anciliaryDataGroupBox);
        vitcTcF1->setObjectName(QStringLiteral("vitcTcF1"));
        vitcTcF1->setAlignment(Qt::AlignCenter);

        formLayout->setWidget(0, QFormLayout::FieldRole, vitcTcF1);

        vITCUserbitsField1Label = new QLabel(anciliaryDataGroupBox);
        vITCUserbitsField1Label->setObjectName(QStringLiteral("vITCUserbitsField1Label"));

        formLayout->setWidget(1, QFormLayout::LabelRole, vITCUserbitsField1Label);

        vitcUbF1 = new QLabel(anciliaryDataGroupBox);
        vitcUbF1->setObjectName(QStringLiteral("vitcUbF1"));
        vitcUbF1->setAlignment(Qt::AlignCenter);

        formLayout->setWidget(1, QFormLayout::FieldRole, vitcUbF1);

        vITCTimecodeField2Label = new QLabel(anciliaryDataGroupBox);
        vITCTimecodeField2Label->setObjectName(QStringLiteral("vITCTimecodeField2Label"));

        formLayout->setWidget(2, QFormLayout::LabelRole, vITCTimecodeField2Label);

        vitcTcF2 = new QLabel(anciliaryDataGroupBox);
        vitcTcF2->setObjectName(QStringLiteral("vitcTcF2"));
        vitcTcF2->setAlignment(Qt::AlignCenter);

        formLayout->setWidget(2, QFormLayout::FieldRole, vitcTcF2);

        vITCUserbitsField2Label = new QLabel(anciliaryDataGroupBox);
        vITCUserbitsField2Label->setObjectName(QStringLiteral("vITCUserbitsField2Label"));

        formLayout->setWidget(3, QFormLayout::LabelRole, vITCUserbitsField2Label);

        vitcUbF2 = new QLabel(anciliaryDataGroupBox);
        vitcUbF2->setObjectName(QStringLiteral("vitcUbF2"));
        vitcUbF2->setAlignment(Qt::AlignCenter);

        formLayout->setWidget(3, QFormLayout::FieldRole, vitcUbF2);

        rP188VITC1TimecodeLabel = new QLabel(anciliaryDataGroupBox);
        rP188VITC1TimecodeLabel->setObjectName(QStringLiteral("rP188VITC1TimecodeLabel"));

        formLayout->setWidget(4, QFormLayout::LabelRole, rP188VITC1TimecodeLabel);

        rp188Vitc1Tc = new QLabel(anciliaryDataGroupBox);
        rp188Vitc1Tc->setObjectName(QStringLiteral("rp188Vitc1Tc"));
        rp188Vitc1Tc->setAlignment(Qt::AlignCenter);

        formLayout->setWidget(4, QFormLayout::FieldRole, rp188Vitc1Tc);

        rP188VITC1UserbitsLabel = new QLabel(anciliaryDataGroupBox);
        rP188VITC1UserbitsLabel->setObjectName(QStringLiteral("rP188VITC1UserbitsLabel"));

        formLayout->setWidget(5, QFormLayout::LabelRole, rP188VITC1UserbitsLabel);

        rp188Vitc1Ub = new QLabel(anciliaryDataGroupBox);
        rp188Vitc1Ub->setObjectName(QStringLiteral("rp188Vitc1Ub"));
        rp188Vitc1Ub->setAlignment(Qt::AlignCenter);

        formLayout->setWidget(5, QFormLayout::FieldRole, rp188Vitc1Ub);

        rP188VITC2TimecodeLabel = new QLabel(anciliaryDataGroupBox);
        rP188VITC2TimecodeLabel->setObjectName(QStringLiteral("rP188VITC2TimecodeLabel"));

        formLayout->setWidget(6, QFormLayout::LabelRole, rP188VITC2TimecodeLabel);

        rp188Vitc2Tc = new QLabel(anciliaryDataGroupBox);
        rp188Vitc2Tc->setObjectName(QStringLiteral("rp188Vitc2Tc"));
        rp188Vitc2Tc->setAlignment(Qt::AlignCenter);

        formLayout->setWidget(6, QFormLayout::FieldRole, rp188Vitc2Tc);

        rP188VITC2UserbitsLabel = new QLabel(anciliaryDataGroupBox);
        rP188VITC2UserbitsLabel->setObjectName(QStringLiteral("rP188VITC2UserbitsLabel"));

        formLayout->setWidget(7, QFormLayout::LabelRole, rP188VITC2UserbitsLabel);

        rp188Vitc2Ub = new QLabel(anciliaryDataGroupBox);
        rp188Vitc2Ub->setObjectName(QStringLiteral("rp188Vitc2Ub"));
        rp188Vitc2Ub->setAlignment(Qt::AlignCenter);

        formLayout->setWidget(7, QFormLayout::FieldRole, rp188Vitc2Ub);

        rP188LTCTimecodeLabel = new QLabel(anciliaryDataGroupBox);
        rP188LTCTimecodeLabel->setObjectName(QStringLiteral("rP188LTCTimecodeLabel"));

        formLayout->setWidget(8, QFormLayout::LabelRole, rP188LTCTimecodeLabel);

        rp188LtcTc = new QLabel(anciliaryDataGroupBox);
        rp188LtcTc->setObjectName(QStringLiteral("rp188LtcTc"));
        rp188LtcTc->setAlignment(Qt::AlignCenter);

        formLayout->setWidget(8, QFormLayout::FieldRole, rp188LtcTc);

        rP188LTCUsebitsLabel = new QLabel(anciliaryDataGroupBox);
        rP188LTCUsebitsLabel->setObjectName(QStringLiteral("rP188LTCUsebitsLabel"));

        formLayout->setWidget(9, QFormLayout::LabelRole, rP188LTCUsebitsLabel);

        rp188LtcUb = new QLabel(anciliaryDataGroupBox);
        rp188LtcUb->setObjectName(QStringLiteral("rp188LtcUb"));
        rp188LtcUb->setAlignment(Qt::AlignCenter);

        formLayout->setWidget(9, QFormLayout::FieldRole, rp188LtcUb);


        horizontalLayout_5->addLayout(formLayout);


        verticalLayout1->addWidget(anciliaryDataGroupBox);

        startStopButton2 = new QPushButton(centralWidget);
        startStopButton2->setObjectName(QStringLiteral("startStopButton2"));
        startStopButton2->setEnabled(false);
        sizePolicy1.setHeightForWidth(startStopButton2->sizePolicy().hasHeightForWidth());
        startStopButton2->setSizePolicy(sizePolicy1);
        startStopButton2->setMinimumSize(QSize(200, 0));

        verticalLayout1->addWidget(startStopButton2);

        startStopButton3 = new QPushButton(centralWidget);
        startStopButton3->setObjectName(QStringLiteral("startStopButton3"));
        startStopButton3->setEnabled(false);
        sizePolicy1.setHeightForWidth(startStopButton3->sizePolicy().hasHeightForWidth());
        startStopButton3->setSizePolicy(sizePolicy1);
        startStopButton3->setMinimumSize(QSize(200, 0));

        verticalLayout1->addWidget(startStopButton3);

        startStopButton4 = new QPushButton(centralWidget);
        startStopButton4->setObjectName(QStringLiteral("startStopButton4"));
        startStopButton4->setEnabled(false);
        sizePolicy1.setHeightForWidth(startStopButton4->sizePolicy().hasHeightForWidth());
        startStopButton4->setSizePolicy(sizePolicy1);
        startStopButton4->setMinimumSize(QSize(200, 0));

        verticalLayout1->addWidget(startStopButton4);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout1->addWidget(label);


        horizontalLayout->addLayout(verticalLayout1);

        verticalLayout2 = new QVBoxLayout();
        verticalLayout2->setSpacing(6);
        verticalLayout2->setObjectName(QStringLiteral("verticalLayout2"));
        previewTab = new QTabWidget(centralWidget);
        previewTab->setObjectName(QStringLiteral("previewTab"));
        previewTab->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(previewTab->sizePolicy().hasHeightForWidth());
        previewTab->setSizePolicy(sizePolicy2);
        previewTab->setMinimumSize(QSize(780, 580));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        sizePolicy2.setHeightForWidth(tab->sizePolicy().hasHeightForWidth());
        tab->setSizePolicy(sizePolicy2);
        horizontalLayout_4 = new QHBoxLayout(tab);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        openGLWidget = new QOpenGLWidget(tab);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        openGLWidget->setEnabled(true);
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(openGLWidget->sizePolicy().hasHeightForWidth());
        openGLWidget->setSizePolicy(sizePolicy3);
        openGLWidget->setMinimumSize(QSize(380, 300));

        gridLayout_2->addWidget(openGLWidget, 1, 0, 1, 1);

        label_23 = new QLabel(tab);
        label_23->setObjectName(QStringLiteral("label_23"));
        sizePolicy.setHeightForWidth(label_23->sizePolicy().hasHeightForWidth());
        label_23->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(label_23, 0, 1, 1, 1);

        label_3 = new QLabel(tab);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(label_3, 0, 0, 1, 1);

        openGLWidget3 = new QOpenGLWidget(tab);
        openGLWidget3->setObjectName(QStringLiteral("openGLWidget3"));
        openGLWidget3->setMinimumSize(QSize(380, 300));

        gridLayout_2->addWidget(openGLWidget3, 3, 0, 1, 1);

        openGLWidget4 = new QOpenGLWidget(tab);
        openGLWidget4->setObjectName(QStringLiteral("openGLWidget4"));
        openGLWidget4->setMinimumSize(QSize(380, 300));

        gridLayout_2->addWidget(openGLWidget4, 3, 1, 1, 1);

        openGLWidget2 = new QOpenGLWidget(tab);
        openGLWidget2->setObjectName(QStringLiteral("openGLWidget2"));
        openGLWidget2->setMinimumSize(QSize(380, 300));

        gridLayout_2->addWidget(openGLWidget2, 1, 1, 1, 1);

        label_24 = new QLabel(tab);
        label_24->setObjectName(QStringLiteral("label_24"));
        sizePolicy.setHeightForWidth(label_24->sizePolicy().hasHeightForWidth());
        label_24->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(label_24, 2, 0, 1, 1);

        label_27 = new QLabel(tab);
        label_27->setObjectName(QStringLiteral("label_27"));
        sizePolicy.setHeightForWidth(label_27->sizePolicy().hasHeightForWidth());
        label_27->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(label_27, 2, 1, 1, 1);


        horizontalLayout_4->addLayout(gridLayout_2);

        previewTab->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        previewTab->addTab(tab_2, QString());

        verticalLayout2->addWidget(previewTab);


        horizontalLayout->addLayout(verticalLayout2);


        horizontalLayout_3->addLayout(horizontalLayout);

        CapturePreviewExClass->setCentralWidget(centralWidget);

        retranslateUi(CapturePreviewExClass);

        previewTab->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(CapturePreviewExClass);
    } // setupUi

    void retranslateUi(QMainWindow *CapturePreviewExClass)
    {
        CapturePreviewExClass->setWindowTitle(QApplication::translate("CapturePreviewExClass", "Loom Stitching Demo", Q_NULLPTR));
        LoomLogoBox->setText(QApplication::translate("CapturePreviewExClass", "TextLabel", Q_NULLPTR));
        label_25->setText(QString());
        deviceLabel->setText(QApplication::translate("CapturePreviewExClass", "Input device", Q_NULLPTR));
        signalInfoLabel->setText(QApplication::translate("CapturePreviewExClass", "No valid input signal", Q_NULLPTR));
        propertiesGroupBox->setTitle(QApplication::translate("CapturePreviewExClass", "Capture properties", Q_NULLPTR));
        applyDetectedInputForwardLabel->setText(QApplication::translate("CapturePreviewExClass", "Apply Detected Input Forward", Q_NULLPTR));
        videoFormatLabel->setText(QApplication::translate("CapturePreviewExClass", "Video Format", Q_NULLPTR));
        startStopButton->setText(QApplication::translate("CapturePreviewExClass", "Capture And Stitching", Q_NULLPTR));
        anciliaryDataGroupBox->setTitle(QApplication::translate("CapturePreviewExClass", "Anciliary Data", Q_NULLPTR));
        vITCTimecodeField1Label->setText(QApplication::translate("CapturePreviewExClass", "VITC Timecode field 1", Q_NULLPTR));
        vitcTcF1->setText(QApplication::translate("CapturePreviewExClass", "TextLabel", Q_NULLPTR));
        vITCUserbitsField1Label->setText(QApplication::translate("CapturePreviewExClass", "VITC Userbits field 1", Q_NULLPTR));
        vitcUbF1->setText(QApplication::translate("CapturePreviewExClass", "TextLabel", Q_NULLPTR));
        vITCTimecodeField2Label->setText(QApplication::translate("CapturePreviewExClass", "VITC Timecode field 2", Q_NULLPTR));
        vitcTcF2->setText(QApplication::translate("CapturePreviewExClass", "TextLabel", Q_NULLPTR));
        vITCUserbitsField2Label->setText(QApplication::translate("CapturePreviewExClass", "VITC Userbits field 2", Q_NULLPTR));
        vitcUbF2->setText(QApplication::translate("CapturePreviewExClass", "TextLabel", Q_NULLPTR));
        rP188VITC1TimecodeLabel->setText(QApplication::translate("CapturePreviewExClass", "RP 188 VITC1 Timecode", Q_NULLPTR));
        rp188Vitc1Tc->setText(QApplication::translate("CapturePreviewExClass", "TextLabel", Q_NULLPTR));
        rP188VITC1UserbitsLabel->setText(QApplication::translate("CapturePreviewExClass", "RP 188 VITC1 Userbits", Q_NULLPTR));
        rp188Vitc1Ub->setText(QApplication::translate("CapturePreviewExClass", "TextLabel", Q_NULLPTR));
        rP188VITC2TimecodeLabel->setText(QApplication::translate("CapturePreviewExClass", "RP 188 VITC2 Timecode", Q_NULLPTR));
        rp188Vitc2Tc->setText(QApplication::translate("CapturePreviewExClass", "TextLabel", Q_NULLPTR));
        rP188VITC2UserbitsLabel->setText(QApplication::translate("CapturePreviewExClass", "RP 188 VITC2 Userbits", Q_NULLPTR));
        rp188Vitc2Ub->setText(QApplication::translate("CapturePreviewExClass", "TextLabel", Q_NULLPTR));
        rP188LTCTimecodeLabel->setText(QApplication::translate("CapturePreviewExClass", "RP 188 LTC Timecode", Q_NULLPTR));
        rp188LtcTc->setText(QApplication::translate("CapturePreviewExClass", "TextLabel", Q_NULLPTR));
        rP188LTCUsebitsLabel->setText(QApplication::translate("CapturePreviewExClass", "RP 188 LTC Usebits", Q_NULLPTR));
        rp188LtcUb->setText(QApplication::translate("CapturePreviewExClass", "TextLabel", Q_NULLPTR));
        startStopButton2->setText(QApplication::translate("CapturePreviewExClass", "2 Capture And Stitching", Q_NULLPTR));
        startStopButton3->setText(QApplication::translate("CapturePreviewExClass", "3 Capture And Stitching", Q_NULLPTR));
        startStopButton4->setText(QApplication::translate("CapturePreviewExClass", "4 Capture And Stitching", Q_NULLPTR));
        label->setText(QString());
        label_23->setText(QApplication::translate("CapturePreviewExClass", "Preview 2", Q_NULLPTR));
        label_3->setText(QApplication::translate("CapturePreviewExClass", "Preview 1", Q_NULLPTR));
        label_24->setText(QApplication::translate("CapturePreviewExClass", "Preview 3", Q_NULLPTR));
        label_27->setText(QApplication::translate("CapturePreviewExClass", "Preview 4", Q_NULLPTR));
        previewTab->setTabText(previewTab->indexOf(tab), QApplication::translate("CapturePreviewExClass", "First 4 Previews", Q_NULLPTR));
        previewTab->setTabText(previewTab->indexOf(tab_2), QApplication::translate("CapturePreviewExClass", "Next Previews...", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CapturePreviewExClass: public Ui_CapturePreviewExClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAPTUREPREVIEWEX_H
