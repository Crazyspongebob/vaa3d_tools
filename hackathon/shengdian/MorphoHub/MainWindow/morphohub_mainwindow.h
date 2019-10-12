#ifndef MORPHOHUB_MAINWINDOW_H
#define MORPHOHUB_MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include "../MainDialog/maindialog.h"
#include "../MainDialog/sourcedatamanagement.h"
#include "../MainDialog/annotatormanagement.h"
#include "../BasicInfo.h"
#include "v3d_interface.h"
using namespace std;

class MorphoHub_MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MorphoHub_MainWindow(QWidget *parent = 0);
public:
    QList<ReconstructionInfo> getReconstuctionsFromLevel(const QString& levelid);

    //store the basic init folder list for db.
    QStringList DBBasicConf;
    QStringList workingspaceConf;
    QList<Annotationlevel> workingspacelevellist;
    QList<Annotationlevel> finishedlevellist;
    QStringList finishedConf;
    QStringList workingspaceContentConf;
    QStringList initworkingspaceTablist;
    QStringList datatitle;//for tab data
    //status lable
    QLabel *statusLabel;
    QLabel *userStatusLabel;

    MorphoHub_MainWindow();
    ~MorphoHub_MainWindow();
private:
    QWidget *originparent;
    QString dbpath;
     /*..............For Annotation ............*/
    AnnotationProtocol seuallenAP;
    Annotator curOperator;
    AnnotationProtocolLevel curLevel;

    QMenu *file;
    QMenu *managementMenu;
    //QMenu *funcs;
    QMenu *levelControlMenu;
    QMenu *menuWindow;
    QMenu *helpMenu;
    QToolBar *dbToolbar;
//    QToolBar *funcsToolbar;
    QToolBar *levelControlToolbar;

    /*..............Database layout ............*/
    QWidget *mainWidget;
    QHBoxLayout *mainlayout;

    /*..............MainLog dock windows............*/
    QDockWidget *MainLogwidget;
    QTextEdit *logtextedit;//for log
    void toLogWindow(const QString& logtext);
    //help
    QAction *helpAction;

    /*Initialization*/
    void MorphoHub_Init();
    void InitofAnnotationProtocol();
    void createActions();
    void createMenus();
    void createStatusBar();
    void createToolBar();
    void updateStatusBar(const QString& showtext);
    void setMainLayout();
    /*..............Database basic action............*/
    QAction *NewDBAction;
    QAction *SetDBAction;
    QAction *SettingAction;
    QDialog *SettingDialog;
    QTabWidget *SettingsTabwidget;
    QGridLayout *basictabQGridLayout;
    QHBoxLayout *mainlayoutforSettings;
    QWidget *mainWidgetforSettings;
    QPushButton *setdbpath_pushbutton;
    QLineEdit *dbpath_LineEdit;
    QPushButton* setting_Apply_Qpushbutton;
    QPushButton* setting_Cancel_Qpushbutton;
    QPushButton* setting_Reset_Qpushbutton;
    QLineEdit *userID_QLineEdit;
    QLineEdit *Inittab_LineEdit;
    /*..............Management dialog............*/
    SourceDataManagement *sdconf_dialog;
    AnnotatorManagement *userManagementDialog;
    /*..............Management actions............*/
    QAction *sdconfAction;
    QAction *userManagementAction;

    QString contentindex;
    QTabWidget *dataTabwidget;
    QList<QTableWidget*> datatablelist;//all the created qtable will have a pointer here.
    QStringList datatabletitlelist;//all the tab name of the created qtable
    QTableWidget* createTableDataLevel(QList<ReconstructionInfo> levelres);
    void updateTableDataLevel(QTableWidget* t,QList<ReconstructionInfo> levelres);

    /*Qtreewidget for content*/
    void createContentTreeWidget(bool init);
    void createTabWindow(bool init);
    QTreeWidget *contentTreewidget;
    QTreeWidgetItem *content_workingspace;
    QTreeWidgetItem *content_basicData;

    /****************Protocol functions*************************/
    void setProtocolFunctionEnabled(bool en);
    ReconstructionInfo curRecon;//This is current reconstruction. you can get info from here.
    /*..............Protocol actions............*/
    QAction *commitAction;
    QAction *checkAction;
    QAction *skipAction;
    QAction *rollbackAction;
    QAction *reassignAction;
    QAction *releaseAction;
    MainDialog *commitDialog;

    /*..............Login or out Dialog............*/
    QToolBar *loginToolbar;
    QDialog *loginDialog;
    QGridLayout *loginMainlayout;
    QAction *loginAction;
    QLineEdit *loginUserIDQLineEdit;
    QLineEdit *loginPasswordQlineedit;
    QPushButton *loginCancelButton;
    QPushButton *loginOkayButton;
    QAction *logoutAction;

private slots:
    void NewDB_slot();
    void SetDB_slot();
    void SettingAction_slot();
    void setdbpath_pushbutton_slot();
    void settingsValueChanges_slot(const QString& text);
    void setting_Apply_Qpushbutton_slot();
    void setting_Cancel_Qpushbutton_slot();
    void setting_Reset_Qpushbutton_slot();

    void removeSubTab(int subindex);
    void dataTabChange(int tabindex);
    void contentValueChange(QTreeWidgetItem *item,int column);
    void celltableInfoUpdate(int row,int column);
    void loginAction_slot();
    void loginOkayButton_slot();
    void loginCancelButton_slot();
    void logoutAction_slot();
    void helpAction_slot();

signals:
    
public slots:
    //Source data management
    void sourceDataMAction();
    //annotator management
    void userManagementAction_slot();
    /*..............Protocol slots............*/
    void commitAction_slot();
    void checkAction_slot();
    void skipAction_slot();
    void rollbackAction_slot();
    void reassignAction_slot();
};

#endif // MORPHOHUB_MAINWINDOW_H
