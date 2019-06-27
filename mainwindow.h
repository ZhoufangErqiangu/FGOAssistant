#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QString>
#include <QFlags>
#include <QCoreApplication>
#include <QTextStream>
#include <QSettings>
#include <QCloseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();

    void on_actionAbout_triggered();

    void on_pushButton_clicked();

    void on_actionOpen_triggered();

    void on_lClassSelect_activated(const QString &arg1);

    void on_bMain_stateChanged(int arg1);

    void on_bBackup_stateChanged(int arg1);

    void on_bNoUse_stateChanged(int arg1);

    void on_pushButton_2_clicked();

    void on_tServantData_cellChanged(int row, int column);

    void on_tServantData_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

    void on_tRequirementData_1_cellChanged(int row, int column);

    void on_tRequirementData_1_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

    void on_tRequirementData_2_cellChanged(int row, int column);

    void on_tRequirementData_2_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

    void on_actionSave_triggered();

    void on_actionSave_As_triggered();

    void on_bMain_2_stateChanged(int arg1);

    void on_bBackup_2_stateChanged(int arg1);

    void on_bNoUse_2_stateChanged(int arg1);

    void on_actionAboutQt_triggered();

    void on_actionNew_triggered();

    void on_actionImport_triggered();

    void on_actionShowTrueName_triggered();

    void on_tabWidget_currentChanged(int index);

    void on_tPlanUnlimitedPoolData_cellChanged(int row, int column);

    void on_tPlanUnlimitedPoolData_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

    void on_actionDataBottomMove_triggered();

    void on_actionRF1_triggered();

    void on_actionRF2_triggered();

    void on_actionRF3_triggered();

    void on_actionRF4_triggered();

    void on_actionRF5_triggered();

private:
    Ui::MainWindow *ui;

    int lRowNumber;
    int lRowNumber2;
    int lRowNumber3;
    bool bInit;
    bool bUserDataChanged;
    bool bShowTrueName;
    QString sFilePath;
    QString sOldValue;
    struct ConfigColors
    {
        QColor cPRIColor0;
        QColor cPRIColor1;
        QColor cPRIColor2;
        QColor cReqOKColor;
        QColor cReqNGColor;
    };
    ConfigColors ConfigColors;
    //bool bContinusReadUserData;

    void InitWindow();
    void InitTable();
    void InitRowData();
    void InitColumnHeader();
    void InitCalculationTabel();
    void InitQPRequirementArray();
    void InitPlan();
    void UILoaded();
    void ClassSelectChanged(QString sClassSelect);
    void PRICheckChanged(QString sPRI, bool bCheckState);
    bool PRICheckChanged2(QString sPRI);
    void CheckUserData(int row);
    void CheckSingleUserData(int row, int column);
    void CheckUserData2(int row, int column);
    void CheckUserData3(int row, int column);
    void CheckUserPlanData(int row,int column);
    void SetPRIColor(int row);
    void SetRequirementColor2(int row);
    void SetRequirementColor3(int row);
    void ReadUserData();
    void SaveUserData();
    void CalculateRequirement2();
    void CalculateRequirement3();
    void CalculateServantRequirement(int row);
    void CalculatePlan();
    void CalculatePlan2();
    void ReadConfig();
    void WriteConfig();
    void NewUserData();
    void ReadFGHFile();
    void SetServantName();

protected:
    void closeEvent(QCloseEvent *event);
    void resizeEvent(QResizeEvent *event);
};

#endif // MAINWINDOW_H
