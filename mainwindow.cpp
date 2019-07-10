#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    lRowNumber=0;
    UILoaded();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool CheckNomalClass(QString sClass)
{
    if (sClass=="Saber" or sClass=="Archer" or sClass=="Lancer" or sClass=="Rider" or sClass=="Caster" or sClass=="Assassin" or sClass=="Berserker")
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool IsDigitString(QString src)
{
    QByteArray bas=src.toLatin1();
    const char *s=bas.data();

    while(*s && *s>='0' && *s<='9') s++;

    if (*s)
    { //不是纯数字
        return false;
    }
    else
    { //纯数字
        return true;
    }
}

void DataBottomMove(QTableWidget *table)
{
    int i=0;
    int j=0;

    if (table->hasFocus()) //check focus
    {
        i=table->currentItem()->row(); //get row index
        for (j=table->rowCount()-1;j>=i;j--)
        {
            table->item(j,2)->setText(table->item(j-1,2)->text());
        }
    }
}

void MainWindow::UILoaded()
{
    bInit=true;
    InitWindow();
    InitTable();
    bInit=false;
    ReadConfig();
    if (!sFilePath.isEmpty())
    {
        ReadUserData(); //read .ini file
    }
}

void MainWindow::InitWindow()
{
    setWindowIcon(QIcon(":/image/AppICO")); //set window ico
    //setWindowFlags(this->windowFlags() | Qt::WindowMaximizeButtonHint); //disable maximize button
    //setFixedSize(1051,711); //disable change window size
    setMinimumSize(1051,711);
    //resize(1051,711);
    ui->lClassSelect->setCurrentIndex(0);
    ui->bMain->setChecked(true);
    ui->bBackup->setChecked(true);
    ui->bNoUse->setChecked(true);
    ui->bMain_2->setChecked(true);
    ui->bBackup_2->setChecked(true);
    ui->bNoUse_2->setChecked(true);
    //ui->sRowNumber->setVisible(false);
    //ui->pushButton->setVisible(false);
    //ui->pushButton_2->setVisible(false);
    //ui->label->setVisible(false);
    //ui->label_2->setVisible(false);
    ui->tabWidget->setCurrentIndex(0);
    ui->actionDataBottomMove->setEnabled(false);
    ui->sFilePathDisplay->setText("");
    ui->sFilePathDisplay->setVisible(true);
    bUserDataChanged=false;
    ui->sUserDataChanged->setVisible(bUserDataChanged);
    ui->tabWidget->removeTab(3); //hide calculation tab
}

void MainWindow::InitTable()
{
    ui->tServantData->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //disable horizon scroll
    ui->tServantData->setShowGrid(true);
    ui->tServantData->setSelectionMode(QAbstractItemView::SingleSelection); //single cell select at same time
    ui->tRequirementData_1->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tRequirementData_1->setShowGrid(true);
    ui->tRequirementData_1->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tRequirementData_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tRequirementData_2->setShowGrid(true);
    ui->tRequirementData_2->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tPlanShopData->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tPlanShopData->setShowGrid(true);
    ui->tPlanShopData->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tPlanUnlimitedPoolData->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tPlanUnlimitedPoolData->setShowGrid(true);
    ui->tPlanUnlimitedPoolData->setSelectionMode(QAbstractItemView::SingleSelection);
    InitColumnHeader();    
    InitQPRequirementArray();
    InitRowData();
    InitCalculationTabel();
    InitPlan();
}

void MainWindow::InitColumnHeader()
{
    int i=0;
    QStringList slColumnHeader;

    slColumnHeader.clear();
    slColumnHeader<<"编号"<<"名称"<<"星级"<<"职阶"<<"优先级"
                  <<"当前再临"<<"目标再临"
                  <<"当前技能1"<<"当前技能2"<<"当前技能3"
                  <<"目标技能1"<<"目标技能2"<<"目标技能3";

    ui->tServantData->setColumnCount(13); //set column number
    ui->tServantData->horizontalHeader()->setVisible(true); //show column width
    ui->tServantData->setHorizontalHeaderLabels(slColumnHeader); //set column header
    //ui->tServantData->setColumnWidth(0,40); //set column width
    //ui->tServantData->setColumnWidth(1,177);
    //ui->tServantData->setColumnWidth(2,40);
    //ui->tServantData->setColumnWidth(3,75);
    //ui->tServantData->setColumnWidth(4,50);
    //ui->tServantData->setColumnWidth(5,75);
    //ui->tServantData->setColumnWidth(6,75);
    //ui->tServantData->setColumnWidth(7,75);
    //ui->tServantData->setColumnWidth(8,75);
    //ui->tServantData->setColumnWidth(9,75);
    //ui->tServantData->setColumnWidth(10,75);
    //ui->tServantData->setColumnWidth(11,75);
    //ui->tServantData->setColumnWidth(12,75);
    //ui->tServantData->horizontalHeader()->setStretchLastSection(true); //set last column auto fix table width
    for (i=0;i<ui->tServantData->columnCount();i++)
    {
        if (i==1)
        {
            ui->tServantData->horizontalHeader()->setSectionResizeMode(i,QHeaderView::Fixed); //disable change column 2 width
        }
        else
        {
            ui->tServantData->horizontalHeader()->setSectionResizeMode(i,QHeaderView::Stretch);
        }
    }

    slColumnHeader.clear();
    slColumnHeader<<"编号"<<"名称"<<"已有"<<"总需"<<"缺口"<<"未来视";
    ui->tRequirementData_1->setColumnCount(6); //set column number
    ui->tRequirementData_1->horizontalHeader()->setVisible(true); //show column width
    ui->tRequirementData_1->setHorizontalHeaderLabels(slColumnHeader); //set column header
    //ui->tRequirementData_1->setColumnWidth(0,50); //set column width
    //ui->tRequirementData_1->setColumnWidth(1,127);
    //ui->tRequirementData_1->setColumnWidth(2,75);
    //ui->tRequirementData_1->setColumnWidth(3,75);
    //ui->tRequirementData_1->setColumnWidth(4,75);
    //ui->tRequirementData_1->setColumnWidth(5,75);
    //ui->tRequirementData_1->horizontalHeader()->setStretchLastSection(true); //set last column auto fix table width
    //ui->tRequirementData_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed); //disable change column width
    for (i=0;i<ui->tRequirementData_1->columnCount();i++)
    {
        if (i==1)
        {
            ui->tRequirementData_1->horizontalHeader()->setSectionResizeMode(i,QHeaderView::Fixed); //disable change column 2 width
        }
        else
        {
            ui->tRequirementData_1->horizontalHeader()->setSectionResizeMode(i,QHeaderView::Stretch);
        }
    }

    ui->tRequirementData_2->setColumnCount(6); //set column number
    ui->tRequirementData_2->horizontalHeader()->setVisible(true); //show column width
    ui->tRequirementData_2->setHorizontalHeaderLabels(slColumnHeader); //set column header
    //ui->tRequirementData_2->setColumnWidth(0,50); //set column width
    //ui->tRequirementData_2->setColumnWidth(1,87);
    //ui->tRequirementData_2->setColumnWidth(2,85);
    //ui->tRequirementData_2->setColumnWidth(3,85);
    //ui->tRequirementData_2->setColumnWidth(4,85);
    //ui->tRequirementData_2->setColumnWidth(5,85);
    //ui->tRequirementData_2->horizontalHeader()->setStretchLastSection(true); //set last column auto fix table width
    //ui->tRequirementData_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed); //disable change column width
    for (i=0;i<ui->tRequirementData_2->columnCount();i++)
    {
        if (i==1)
        {
            ui->tRequirementData_2->horizontalHeader()->setSectionResizeMode(i,QHeaderView::Fixed); //disable change column 2 width
        }
        else
        {
            ui->tRequirementData_2->horizontalHeader()->setSectionResizeMode(i,QHeaderView::Stretch);
        }
    }

    slColumnHeader.clear();
    slColumnHeader<<"编号"<<"活动名称"<<"参加";
    ui->tPlanShopData->setColumnCount(3); //set column number
    ui->tPlanShopData->horizontalHeader()->setVisible(true); //show column width
    ui->tPlanShopData->setHorizontalHeaderLabels(slColumnHeader); //set column header
    //ui->tPlanShopData->setColumnWidth(0,50); //set column width
    //ui->tPlanShopData->setColumnWidth(1,352);
    //ui->tPlanShopData->setColumnWidth(2,75);
    //ui->tPlanShopData->horizontalHeader()->setStretchLastSection(true); //set last column auto fix table width
    //ui->tPlanShopData->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed); //disable change column width
    for (i=0;i<ui->tPlanShopData->columnCount();i++)
    {
        if (i==1)
        {
            ui->tPlanShopData->horizontalHeader()->setSectionResizeMode(i,QHeaderView::Fixed); //disable change column 2 width
        }
        else
        {
            ui->tPlanShopData->horizontalHeader()->setSectionResizeMode(i,QHeaderView::Stretch);
        }
    }

    slColumnHeader.clear();
    slColumnHeader<<"编号"<<"活动名称"<<"池数";
    ui->tPlanUnlimitedPoolData->setColumnCount(3); //set column number
    ui->tPlanUnlimitedPoolData->horizontalHeader()->setVisible(true); //show column width
    ui->tPlanUnlimitedPoolData->setHorizontalHeaderLabels(slColumnHeader); //set column header
    //ui->tPlanUnlimitedPoolData->setColumnWidth(0,50); //set column width
    //ui->tPlanUnlimitedPoolData->setColumnWidth(1,352);
    //ui->tPlanUnlimitedPoolData->setColumnWidth(2,75);
    //ui->tPlanUnlimitedPoolData->horizontalHeader()->setStretchLastSection(true); //set last column auto fix table width
    //ui->tPlanUnlimitedPoolData->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed); //disable change column width
    for (i=0;i<ui->tPlanUnlimitedPoolData->columnCount();i++)
    {
        if (i==1)
        {
            ui->tPlanUnlimitedPoolData->horizontalHeader()->setSectionResizeMode(i,QHeaderView::Fixed); //disable change column 2 width
        }
        else
        {
            ui->tPlanUnlimitedPoolData->horizontalHeader()->setSectionResizeMode(i,QHeaderView::Stretch);
        }
    }

    ui->tServantRequirementData->setColumnCount(69); //69 is fixed number

    ui->tTrueNameData->setColumnCount(2); //2 is fixed number
}

void MainWindow::InitRowData()
{
    QString sString[512];
    QString sNo="";
    QString sName="";
    QString sTrueName="";
    QString sStars="";
    QString sClass="";
    QString sTip="";
    QTableWidgetItem *pCell;
    int i=0;
    int j=0;
    int k=0;

    sString->clear();
    i=0;
    QFile *fRowHeader2=new QFile(QString(":/data/RowHeader2"));
    if (!fRowHeader2->open(QIODevice::ReadOnly | QIODevice::Text)) //open file
    {
        QMessageBox::about(this,"Error","Can`t Read RowHeader 2");
    }
    else
    {
        QTextStream in2(fRowHeader2);
        while (!in2.atEnd())
        {
            sString[i]=in2.readLine(); //read line
            sNo=sString[i].section(",",0,0); //get No.
            if (sNo!="")
            {
                i++;
            }
        } //get how much line in the data file

        lRowNumber2=i;
        ui->label->setNum(lRowNumber2);
        ui->tRequirementData_1->setRowCount(lRowNumber2);
        fRowHeader2->close();

        for (j=0;j<lRowNumber2;j++)
        {
            sNo=sString[j].section(",",0,0); //get No.
            sName=sString[j].section(",",1,1); //get name
            //sTip=sString[j].section(",",2,2); //get tip

            pCell= new QTableWidgetItem;
            pCell->setText(sNo); //set No.
            pCell->setFlags(pCell->flags() & ~Qt::ItemIsEditable); //disable editable
            ui->tRequirementData_1->setItem(j,0,pCell);

            pCell= new QTableWidgetItem;            
            pCell->setText(sName); //set name
            //pCell->setToolTip(sTip); //set tip //tip is no use, tip is for servant requirement function
            pCell->setFlags(pCell->flags() & ~Qt::ItemIsEditable); //disable editable
            ui->tRequirementData_1->setItem(j,1,pCell);

            pCell= new QTableWidgetItem;
            pCell->setText("0"); //set data
            ui->tRequirementData_1->setItem(j,2,pCell);

            pCell= new QTableWidgetItem;
            pCell->setText("0"); //set requirement
            pCell->setFlags(pCell->flags() & ~Qt::ItemIsEditable); //disable editable
            ui->tRequirementData_1->setItem(j,3,pCell);

            pCell= new QTableWidgetItem;
            pCell->setText("0"); //set requirement
            pCell->setFlags(pCell->flags() & ~Qt::ItemIsEditable); //disable editable
            ui->tRequirementData_1->setItem(j,4,pCell);

            pCell= new QTableWidgetItem;
            pCell->setText("0"); //set plan
            pCell->setFlags(pCell->flags() & ~Qt::ItemIsEditable); //disable editable
            ui->tRequirementData_1->setItem(j,5,pCell);
        }
    }

    sString->clear();
    i=0;
    QFile *fRowHeader3=new QFile(QString(":/data/RowHeader3"));
    if (!fRowHeader3->open(QIODevice::ReadOnly | QIODevice::Text)) //open file
    {
        QMessageBox::about(this,"Error","Can`t Read RowHeader 3");
    }
    else
    {
        QTextStream in3(fRowHeader3);
        while (!in3.atEnd())
        {
            sString[i]=in3.readLine(); //read line
            sNo=sString[i].section(",",0,0); //get No.
            if (sNo!="")
            {
                i++;
            }
        } //get how much line in the data file

        lRowNumber3=i;
        ui->tRequirementData_2->setRowCount(lRowNumber3);
        fRowHeader3->close();

        for (j=0;j<lRowNumber3;j++)
        {
            sNo=sString[j].section(",",0,0); //get No.
            sName=sString[j].section(",",1,1); //get name
            //sTip=sString[j].section(",",2,2); //get tip

            pCell= new QTableWidgetItem;
            pCell->setText(sNo); //set No.
            pCell->setFlags(pCell->flags() & ~Qt::ItemIsEditable); //disable editable
            ui->tRequirementData_2->setItem(j,0,pCell);

            pCell= new QTableWidgetItem;
            pCell->setText(sName); //set name
            //pCell->setToolTip(sTip); //set tip //tip is no use, tip is for which servant requirement function
            pCell->setFlags(pCell->flags() & ~Qt::ItemIsEditable); //disable editable
            ui->tRequirementData_2->setItem(j,1,pCell);

            pCell= new QTableWidgetItem;
            pCell->setText("0"); //set data
            ui->tRequirementData_2->setItem(j,2,pCell);

            pCell= new QTableWidgetItem;
            pCell->setText("0"); //set requirement
            pCell->setFlags(pCell->flags() & ~Qt::ItemIsEditable); //disable editable
            ui->tRequirementData_2->setItem(j,3,pCell);

            pCell= new QTableWidgetItem;
            pCell->setText("0"); //set requirement
            pCell->setFlags(pCell->flags() & ~Qt::ItemIsEditable); //disable editable
            ui->tRequirementData_2->setItem(j,4,pCell);

            pCell= new QTableWidgetItem;
            pCell->setText("0"); //set plan
            pCell->setFlags(pCell->flags() & ~Qt::ItemIsEditable); //disable editable
            ui->tRequirementData_2->setItem(j,5,pCell);
        }
    }

    sString->clear();
    i=0;
    QFile *fRowData=new QFile(QString(":/data/Data"));
    if (!fRowData->open(QIODevice::ReadOnly | QIODevice::Text)) //open file
    {
        QMessageBox::about(this,"Error","Can`t Read RowHeader");
    }
    else
    {
        QTextStream in(fRowData);
        in.readLine(); //skip frist line
        while (!in.atEnd())
        {
            sString[i]=in.readLine(); //read line
            sNo=sString[i].section(",",0,0); //get No.
            if (sNo!="")
            {
                i++;
            }
        } //get how much line in the data file

        lRowNumber=i;
        ui->sRowNumber->setNum(lRowNumber);
        ui->tServantData->setRowCount(lRowNumber);
        ui->tServantRequirementData->setRowCount(lRowNumber);
        ui->tTrueNameData->setRowCount(lRowNumber);
        fRowData->close();

        for (j=0;j<lRowNumber;j++)
        {
            sNo=sString[j].section(",",0,0); //get No.
            sName=sString[j].section(",",1,1); //get name
            sTrueName=sName.section("|",1,1); //get true name
            sName=sName.section("|",0,0); //get nomal name
            sStars=sString[j].section(",",2,2); //get star
            sClass=sString[j].section(",",3,3); //get class

            pCell= new QTableWidgetItem;
            pCell->setText(sNo); //set No.
            pCell->setFlags(pCell->flags() & ~Qt::ItemIsEditable); //disable editable
            ui->tServantData->setItem(j,0,pCell);

            pCell= new QTableWidgetItem;
            pCell->setText(sName); //set name
            pCell->setFlags(pCell->flags() & ~Qt::ItemIsEditable); //disable editable
            ui->tServantData->setItem(j,1,pCell);

            pCell= new QTableWidgetItem;
            pCell->setText(sStars); //set stars
            pCell->setFlags(pCell->flags() & ~Qt::ItemIsEditable); //disable editable
            ui->tServantData->setItem(j,2,pCell);

            pCell= new QTableWidgetItem;
            pCell->setText(sClass); //set class
            pCell->setFlags(pCell->flags() & ~Qt::ItemIsEditable); //disable editable
            ui->tServantData->setItem(j,3,pCell);

            pCell= new QTableWidgetItem;
            pCell->setText("0"); //set PRI
            ui->tServantData->setItem(j,4,pCell);

            pCell= new QTableWidgetItem;
            pCell->setText("0"); //set now break
            ui->tServantData->setItem(j,5,pCell);

            pCell= new QTableWidgetItem;
            pCell->setText("0"); //set target break
            ui->tServantData->setItem(j,6,pCell);

            pCell= new QTableWidgetItem;
            pCell->setText("1"); //set now skill 1
            ui->tServantData->setItem(j,7,pCell);

            pCell= new QTableWidgetItem;
            pCell->setText("1"); //set now skill 2
            ui->tServantData->setItem(j,8,pCell);

            pCell= new QTableWidgetItem;
            pCell->setText("1"); //set now skill 3
            ui->tServantData->setItem(j,9,pCell);

            pCell= new QTableWidgetItem;
            pCell->setText("1"); //set target skill 1
            ui->tServantData->setItem(j,10,pCell);

            pCell= new QTableWidgetItem;
            pCell->setText("1"); //set target skill 2
            ui->tServantData->setItem(j,11,pCell);

            pCell= new QTableWidgetItem;
            pCell->setText("1"); //set target skill 3
            ui->tServantData->setItem(j,12,pCell);

            SetPRIColor(j);

            for (k=0;k<69;k++)
            {
                pCell= new QTableWidgetItem;
                pCell->setText(sString[j].section(",",k,k));
                ui->tServantRequirementData->setItem(j,k,pCell);
            }

            pCell=new QTableWidgetItem;
            pCell->setText(sName); //set nomal name
            ui->tTrueNameData->setItem(j,0,pCell);

            pCell=new QTableWidgetItem;
            pCell->setText(sTrueName); //set true name
            ui->tTrueNameData->setItem(j,1,pCell);
        }
    }
}

void MainWindow::InitCalculationTabel()
{
    int i=0;
    int j=0;
    QTableWidgetItem *pCell;

    ui->tCalculateData->setColumnCount(lRowNumber2+lRowNumber3+1);
    ui->tCalculateData->setRowCount(lRowNumber);
    for (i=0;i<ui->tCalculateData->rowCount();i++)
    {
        pCell=new QTableWidgetItem;
        pCell->setText(ui->tServantData->item(i,0)->text()); //table 5 1st column is no
        ui->tCalculateData->setItem(i,0,pCell);
        for (j=1;j<ui->tCalculateData->columnCount();j++)
        {
            pCell=new QTableWidgetItem;
            pCell->setText("0");
            ui->tCalculateData->setItem(i,j,pCell); //table 5 other column is servant requirement
        }
    }
}

void MainWindow::InitQPRequirementArray()
{
    int i=0;
    int j=0;
    QString s="";
    QString sQPFilePath=":/data/QP";
    QFile *fQPFile;
    QTableWidgetItem *pCell;

    ui->tQPRequirementData->setColumnCount(6);
    ui->tQPRequirementData->setRowCount(14);

    fQPFile= new QFile(sQPFilePath);
    if (!fQPFile->open(QIODevice::ReadOnly | QIODevice::Text)) //open file
    {
        QMessageBox::about(this,"Error","Can`t Read RowHeader");
    }
    else
    {
        QTextStream in(fQPFile);
        in.readLine();
        while (!in.atEnd())
        {
            s=in.readLine();
            for (j=1;j<6;j++)
            {
                pCell=new QTableWidgetItem;
                pCell->setText(s.section(",",j,j));
                ui->tQPRequirementData->setItem(i,j-1,pCell);
            }
            i++;
        }
    }
}

void MainWindow::InitPlan()
{
    QString sString="";
    QString sNo;
    QString sName;
    QString sData;
    QString s;
    int i=0;
    int j=0;
    QTableWidgetItem *pCell;
    QCheckBox *pCheckBox;

    i=0;
    ui->tPlanShopCalculateData->setColumnCount(lRowNumber2+lRowNumber3+2);
    ui->tPlanUnlimitedPoolCalculateData->setColumnCount(lRowNumber2+lRowNumber3+2);
    QFile *fFile=new QFile(QString(":/data/PlanShopData2")); //read shop data
    if (!fFile->open(QIODevice::ReadOnly | QIODevice::Text)) //open file
    {
        QMessageBox::about(this,"Error","Can`t Read Plan Shop Data");
    }
    else
    {
        QTextStream in(fFile);
        while (!in.atEnd())
        {
            sString=in.readLine(); //read line
            sNo=sString.section(",",0,0); //get No.
            if (!sNo.isEmpty())
            {
                sName=sString.section(",",1,1);
                ui->tPlanShopData->setRowCount(i+1);
                ui->tPlanShopCalculateData->setRowCount(i+1);

                pCell=new QTableWidgetItem;
                pCell->setText(sNo);
                pCell->setFlags(pCell->flags() & ~Qt::ItemIsEditable); //disable editable
                ui->tPlanShopData->setItem(i,0,pCell);

                pCell=new QTableWidgetItem;
                pCell->setText(sName);
                pCell->setFlags(pCell->flags() & ~Qt::ItemIsEditable); //disable editable
                ui->tPlanShopData->setItem(i,1,pCell);

                pCheckBox=new QCheckBox;
                pCheckBox->setText("");
                ui->tPlanShopData->setCellWidget(i,2,pCheckBox);

                pCell=new QTableWidgetItem;
                pCell->setText(sNo);
                ui->tPlanShopCalculateData->setItem(i,0,pCell);

                pCell=new QTableWidgetItem;
                pCell->setText(sName);
                ui->tPlanShopCalculateData->setItem(i,1,pCell);

                for (j=2;j<lRowNumber2+lRowNumber3+2;j++)
                {
                    pCell=new QTableWidgetItem;
                    s=sString.section(",",j,j);
                    pCell->setText(s);
                    ui->tPlanShopCalculateData->setItem(i,j,pCell);
                }

                i++;
            }
        } //get how much line in the data file
        fFile->close();
    }

    i=0;
    QFile *fFile2=new QFile(QString(":/data/PlanUnlimitedPoolData2")); //read shop data
    if (!fFile2->open(QIODevice::ReadOnly | QIODevice::Text)) //open file
    {
        QMessageBox::about(this,"Error","Can`t Read Plan Unlimited Pool Data");
    }
    else
    {
        QTextStream in(fFile2);
        while (!in.atEnd())
        {
            sString=in.readLine(); //read line
            sNo=sString.section(",",0,0); //get No.
            if (!sNo.isEmpty())
            {
                sName=sString.section(",",1,1);
                ui->tPlanUnlimitedPoolData->setRowCount(i+1);
                ui->tPlanUnlimitedPoolCalculateData->setRowCount(i+1);

                pCell=new QTableWidgetItem;
                pCell->setText(sNo);
                pCell->setFlags(pCell->flags() & ~Qt::ItemIsEditable); //disable editable
                ui->tPlanUnlimitedPoolData->setItem(i,0,pCell);


                pCell=new QTableWidgetItem;
                pCell->setText(sName);
                pCell->setFlags(pCell->flags() & ~Qt::ItemIsEditable); //disable editable
                ui->tPlanUnlimitedPoolData->setItem(i,1,pCell);

                pCell=new QTableWidgetItem;
                pCell->setText("0");
                ui->tPlanUnlimitedPoolData->setItem(i,2,pCell);

                pCell=new QTableWidgetItem;
                pCell->setText(sNo);
                ui->tPlanUnlimitedPoolCalculateData->setItem(i,0,pCell);

                pCell=new QTableWidgetItem;
                pCell->setText(sName);
                ui->tPlanUnlimitedPoolCalculateData->setItem(i,1,pCell);

                for (j=2;j<lRowNumber2+lRowNumber3+2;j++)
                {
                    pCell=new QTableWidgetItem;
                    s=sString.section(",",j,j);
                    pCell->setText(s);
                    ui->tPlanUnlimitedPoolCalculateData->setItem(i,j,pCell);
                }

                i++;
            }
        }
        fFile2->close();
    }
}

void MainWindow::ClassSelectChanged(QString sClassSelect) //show or hide table 1 row by class selector
{
    QString sClass="";
    QString sPRI="";
    bool bHidden=false;
    int i=0;

    for (i=0;i<lRowNumber;i++)
    {
        sPRI=ui->tServantData->item(i,4)->text();
        sClass=ui->tServantData->item(i,3)->text();
        if (sClassSelect=="All")
        {
            bHidden=PRICheckChanged2(sPRI);
        }
        if (CheckNomalClass(sClassSelect))
        {
            if (sClass==sClassSelect)
            {
                bHidden=PRICheckChanged2(sPRI);
            }
            else
            {
                bHidden=true;
            }
        }
        if (sClassSelect=="Other")
        {
            if (CheckNomalClass(sClass))
            {
                bHidden=true;
            }
            else
            {
                bHidden=PRICheckChanged2(sPRI);
            }
        }
        ui->tServantData->setRowHidden(i,bHidden);
    }
}

void MainWindow::PRICheckChanged(QString sPRISelect , bool bCheckState) //change table 1 color by PRI
{
    int i=0;
    QString sPRI="";

    for (i=0;i<lRowNumber;i++)
    {
        sPRI=ui->tServantData->item(i,4)->text();
        if (sPRI==sPRISelect)
        {
            ui->tServantData->setRowHidden(i,!bCheckState);
        }
    }
}

bool MainWindow::PRICheckChanged2(QString sPRI)
{
    bool bHidden;

    bHidden=((sPRI=="2") and ui->bMain->checkState())
            or ((sPRI=="1") and ui->bBackup->checkState())
            or ((sPRI=="0") and ui->bNoUse->checkState());
    bHidden=!bHidden;
    return bHidden;
}

void MainWindow::CheckUserData(int row) //check user data in table 1
{
    int lNowBreak=0;
    int lTargetBreak=0;
    int lNowSkill1=0;
    int lNowSkill2=0;
    int lNowSkill3=0;
    int lTargetSkill1=0;
    int lTargetSkill2=0;
    int lTargetSkill3=0;
    QString s="";

    lNowBreak=ui->tServantData->item(row,5)->text().toInt();
    lTargetBreak=ui->tServantData->item(row,6)->text().toInt();
    lNowSkill1=ui->tServantData->item(row,7)->text().toInt();
    lNowSkill2=ui->tServantData->item(row,8)->text().toInt();
    lNowSkill3=ui->tServantData->item(row,9)->text().toInt();
    lTargetSkill1=ui->tServantData->item(row,10)->text().toInt();
    lTargetSkill2=ui->tServantData->item(row,11)->text().toInt();
    lTargetSkill3=ui->tServantData->item(row,12)->text().toInt();

    if (lNowBreak>lTargetBreak)
    {
        lTargetBreak=lNowBreak;
        s.setNum(lTargetBreak);
        ui->tServantData->item(row,6)->setText(s);
    }
    if (lNowSkill1>lTargetSkill1)
    {
        lTargetSkill1=lNowSkill1;
        s.setNum(lTargetSkill1);
        ui->tServantData->item(row,10)->setText(s);
    }
    if (lNowSkill2>lTargetSkill2)
    {
        lTargetSkill2=lNowSkill2;
        s.setNum(lTargetSkill2);
        ui->tServantData->item(row,11)->setText(s);
    }
    if (lNowSkill3>lTargetSkill3)
    {
        lTargetSkill3=lNowSkill3;
        s.setNum(lTargetSkill3);
        ui->tServantData->item(row,12)->setText(s);
    }
}

void MainWindow::CheckSingleUserData(int row, int column) //check user data in table 1
{
    bool bCheckUserData=false;
    int lData=0;
    QString sData="";

    if (column>=4 and column<=12)
    {
        sData=ui->tServantData->item(row,column)->text();
        if (!IsDigitString(sData) or sData.isEmpty())
        {
            bCheckUserData=true;
        }
        else
        {
            lData=sData.toInt();
            if (column==4) //check PRI
            {
                if (lData<0 or lData>2)
                {
                    bCheckUserData=true;
                }
            }
            if (column==5 or column==6) //check break
            {
                if (lData<0 or lData>4)
                {
                    bCheckUserData=true;
                }
            }
            if (column>=7 and column<=12) //check skill
            {
                if (lData<1 or lData>10)
                {
                    bCheckUserData=true;
                }
            }
        }
        if (bCheckUserData)
        {
            if (bInit)
            {
                if (column>=4 and column<=6)
                {
                    sOldValue="0";
                }
                if (column>=7 and column<=12)
                {
                    sOldValue="1";
                }
            }
            ui->tServantData->item(row,column)->setText(sOldValue);
        }
    }
}

void MainWindow::CheckUserData2(int row, int column) //check user data in table 2
{
    bool bCheckUserData=false;
    int lData=0;
    QString sData="";

    sData=ui->tRequirementData_1->item(row,column)->text();
    if (column==2)
    {
        if (!IsDigitString(sData) or sData.isEmpty())
        {
            bCheckUserData=true;
        }
        else
        {
            lData=sData.toInt();
            if (lData<0)
            {
                bCheckUserData=true;
            }
        }
    }
    if (bCheckUserData)
    {
        if (bInit)
        {
            if (column==2)
            {
                sOldValue="0";
            }
        }
        ui->tRequirementData_1->item(row,column)->setText(sOldValue); //check data
    }
}

void MainWindow::CheckUserData3(int row, int column) //check user data in table 3
{
    bool bCheckUserData=false;
    int lData=0;
    QString sData="";

    sData=ui->tRequirementData_2->item(row,column)->text();
    if (column==2)
    {
        if (!IsDigitString(sData) or sData.isEmpty())
        {
            bCheckUserData=true;
        }
        else
        {
            lData=sData.toInt();
            if (lData<0)
            {
                bCheckUserData=true;
            }
            }
    }
    if (bCheckUserData)
    {
        if (bInit)
        {
            if (column==2)
            {
                sOldValue="0";
            }
        }
        ui->tRequirementData_2->item(row,column)->setText(sOldValue); //check data
    }
}

void MainWindow::CheckUserPlanData(int row, int column)
{
    bool bCheckUserData=false;
    int lData=0;
    QString sData="";

    sData=ui->tPlanUnlimitedPoolData->item(row,column)->text();
    if (column==2)
    {
        if (!IsDigitString(sData) or sData.isEmpty())
        {
            bCheckUserData=true;
        }
        else
        {
            lData=sData.toInt();
            if (lData<0)
            {
                bCheckUserData=true;
            }
            }
    }
    if (bCheckUserData)
    {
        if (bInit)
        {
            if (column==2)
            {
                sOldValue="0";
            }
        }
        ui->tPlanUnlimitedPoolData->item(row,column)->setText(sOldValue); //check data
    }
}

void MainWindow::SetPRIColor(int row) //set table 1 row color by PRI
{
    int i=0;
    int lPRI;
    QColor cPRIColor;

    cPRIColor=QColor(128,128,128);
    lPRI=ui->tServantData->item(row,4)->text().toInt();
    if (lPRI==2)
    {
        cPRIColor=ConfigColors.cPRIColor2;
    }
    if (lPRI==1)
    {
        cPRIColor=ConfigColors.cPRIColor1;
    }
    if (lPRI==0)
    {
        cPRIColor=ConfigColors.cPRIColor0;
    }
    for (i=0;i<ui->tServantData->columnCount();i++)
    {
        ui->tServantData->item(row,i)->setBackgroundColor(cPRIColor);
    }
}

void MainWindow::SetRequirementColor2(int row) //no use
{
    int lrequirement=0;
    QColor cRequirementColor;

    lrequirement=ui->tRequirementData_1->item(row,4)->text().toInt();
    if (lrequirement>0)
    {
        cRequirementColor=ConfigColors.cReqOKColor;
    }
    else
    {
        cRequirementColor=ConfigColors.cReqNGColor;
    }
    ui->tRequirementData_1->item(row,4)->setBackground(cRequirementColor);
}

void MainWindow::SetRequirementColor3(int row) //no use
{
    int lrequirement=0;
    QColor cRequirementColor;

    lrequirement=ui->tRequirementData_2->item(row,4)->text().toInt();
    if (lrequirement>0)
    {
        cRequirementColor=ConfigColors.cReqOKColor;
    }
    else
    {
        cRequirementColor=ConfigColors.cReqNGColor;
    }
    ui->tRequirementData_2->item(row,4)->setBackground(cRequirementColor);
}

void MainWindow::ReadUserData() //read user data (*.fgh2 file)
{
    int i=0;
    int j=0;
    QString s;
    QCheckBox *pCheckBox;

    if (sFilePath.isEmpty())
    {
        sFilePath = QFileDialog::getOpenFileName(this, tr("Open File"), "D:/",  tr("fgh2 file(*.fgh2);;all file(*.*)"));
    }
    if (!sFilePath.isEmpty())
    {
        QFile *fUserData=new QFile(QString(sFilePath));
        if (!fUserData->open(QIODevice::ReadOnly | QIODevice::Text)) //open file
        {
            QMessageBox::about(this,"Error","Can`t read " + sFilePath);
            sFilePath="";
        }
        else
        {
            bInit=true; //skip check step
            QTextStream in(fUserData);
            for (i=0;i<lRowNumber;i++) //for loop all servant
            {
                s=in.readLine();
                for (j=4;j<13;j++)
                {
                    ui->tServantData->item(i,j)->setText(s.section(",",j,j)); //read data of servant table
                }
                SetPRIColor(i);
                CheckUserData(i);
                CalculateServantRequirement(i);
                if (i<lRowNumber2)
                {
                    ui->tRequirementData_1->item(i,2)->setText(s.section(",",20,20)); //read data of requirement table 1
                }
                if (i<lRowNumber3)
                {
                    ui->tRequirementData_2->item(i,2)->setText(s.section(",",21,21)); //read data of requirement table 2
                }
                if (i<ui->tPlanShopData->rowCount())
                {
                    pCheckBox=static_cast<QCheckBox *>(ui->tPlanShopData->cellWidget(i,2));
                    if (s.section(",",22,22).toInt()!=0 and !s.section(",",22,22).isEmpty()) //read data of user plan shop table
                    {
                        pCheckBox->setChecked(true);
                    }
                    else
                    {
                        pCheckBox->setChecked(false);
                    }
                }
                if (i<ui->tPlanUnlimitedPoolData->rowCount())
                {
                    ui->tPlanUnlimitedPoolData->item(i,2)->setText(s.section(",",23,23)); //read data of user plan unlimited pool table
                }
            }
            fUserData->close();
            ui->sFilePathDisplay->setText(sFilePath);
            bUserDataChanged=false;
            ui->sUserDataChanged->setVisible(bUserDataChanged);
            CalculatePlan2();
            CalculateRequirement2();
            CalculateRequirement3();
            bInit=false;

            if (ui->actionRF1->text()!=sFilePath) //put fils path in menu
            {
                ui->actionRF5->setText(ui->actionRF4->text()); //move text
                ui->actionRF4->setText(ui->actionRF3->text());
                ui->actionRF3->setText(ui->actionRF2->text());
                ui->actionRF2->setText(ui->actionRF1->text());
                ui->actionRF1->setText(sFilePath);
            }
        }
    }
    else
    {
        sFilePath=ui->sFilePathDisplay->text();
    }
}

void MainWindow::SaveUserData() //write user data (*.fgh2 file)
{
    int i=0;
    int j=0;
    QCheckBox *pCheckBox;
    QString s;

    if (sFilePath.isEmpty())
    {
        sFilePath =QFileDialog::getSaveFileName(this,"Save","D:/","fgh2 file(*.fgh2);;all file(*.*)");
    }
    if (!sFilePath.isEmpty())
    {
        QFile *fUserData=new QFile(QString(sFilePath));
        if (!fUserData->open(QIODevice::WriteOnly | QIODevice::Text)) //open file
        {
            QMessageBox::about(this,"Error","Can`t write " + sFilePath);
        }
        else
        {
            QTextStream out(fUserData);
            for (i=0;i<lRowNumber;i++)
            {
                for (j=0;j<13;j++)
                {
                    out<<ui->tServantData->item(i,j)->text()<<","; //write data of servant table
                }
                for (j=13;j<20;j++)
                {
                    out<<",";
                }
                if (i<lRowNumber2)
                {
                    out<<ui->tRequirementData_1->item(i,2)->text(); //write data of requirement table 1
                }
                out<<",";
                if (i<lRowNumber3)
                {
                    out<<ui->tRequirementData_2->item(i,2)->text(); //write data of requirement table 2
                }
                out<<",";
                if (i<ui->tPlanShopData->rowCount())
                {
                    pCheckBox=static_cast<QCheckBox *>(ui->tPlanShopData->cellWidget(i,2)); //write data of plan shop table
                    out<<pCheckBox->checkState();
                }
                out<<",";
                if (i<ui->tPlanUnlimitedPoolData->rowCount())
                {
                    out<<ui->tPlanUnlimitedPoolData->item(i,2)->text(); //write data of plan unlimited pool table
                }
                out<<",";
                out<<endl;
            }
            out.flush();
            fUserData->close();            
            ui->sFilePathDisplay->setText(sFilePath);
            bUserDataChanged=false;
            ui->sUserDataChanged->setVisible(bUserDataChanged);
        }
    }
    else
    {
        sFilePath=ui->sFilePathDisplay->text();
    }
}

void MainWindow::CalculateRequirement2()
{
    int i=0;
    int j=0;
    int lRequirementCounter;
    int lPlanCounter;
    int lPRI=0;
    bool bEnable=false;
    bool bMain=false;
    bool bBackup=false;
    bool bNouse=false;
    QString s="";
    QString sRequirementTip="";
    QString sServantName="";

    bMain=ui->bMain_2->checkState();
    bBackup=ui->bBackup_2->checkState();
    bNouse=ui->bNoUse_2->checkState();

    for (i=0;i<lRowNumber2;i++) //for all requirement in table 2
    {
        lRequirementCounter=0;
        sRequirementTip.clear();
        for (j=0;j<lRowNumber;j++) //for all servant
        {
            lPRI=ui->tServantData->item(j,4)->text().toInt();
            bEnable=(lPRI==2 and bMain) or (lPRI==1 and bBackup) or (lPRI==0 and bNouse);
            if (bEnable)
            {
                s=ui->tCalculateData->item(j,i+1)->text();
                lRequirementCounter+=s.toInt();
                if (s.toInt()>0)
                {
                    sServantName=ui->tServantData->item(j,1)->text();
                    sRequirementTip+=sServantName+":"+s+",";
                    if (sRequirementTip.length()-sRequirementTip.lastIndexOf("\n")>100)
                    {
                        sRequirementTip+="\n";
                    }
                }
            }
        }
        s.setNum(lRequirementCounter);
        ui->tRequirementData_1->item(i,3)->setText(s); //set requirement
        s=ui->tRequirementData_1->item(i,2)->text(); //get user data
        lPlanCounter=ui->tRequirementData_1->item(i,5)->text().toInt(); //get plan
        s.setNum(lRequirementCounter-s.toInt());
        if (s.toInt()>0)
        {
            if (s.toInt()>lPlanCounter)
            {
                ui->tRequirementData_1->item(i,4)->setBackgroundColor(QColor(255,0,0)); //set Red
            }
            else
            {
                ui->tRequirementData_1->item(i,4)->setBackgroundColor(QColor(0,0,255)); //set Blue
            }
            ui->tRequirementData_1->item(i,4)->setText(s); //set still requirement
        }
        else
        {
            ui->tRequirementData_1->item(i,4)->setBackgroundColor(QColor(255,255,255)); //set white
            ui->tRequirementData_1->item(i,4)->setText("0"); //set still requirement
        }        
        if(sRequirementTip.right(1)=="\n")
        {
            sRequirementTip=sRequirementTip.left(sRequirementTip.length()-1);
        }
        if(sRequirementTip.right(1)==",")
        {
            sRequirementTip=sRequirementTip.left(sRequirementTip.length()-1);
        }
        ui->tRequirementData_1->item(i,1)->setToolTip(sRequirementTip);
    }
}

void MainWindow::CalculateRequirement3()
{
    int i=0;
    int j=0;
    unsigned long long int lRequirementCounter;
    int lPlanCounter;
    int lPRI=0;
    bool bEnable=false;
    bool bMain=false;
    bool bBackup=false;
    bool bNouse=false;
    //bool bBigInteger=false;
    QString s="";
    QString sRequirementTip="";
    QString sServantName="";

    bMain=ui->bMain_2->checkState();
    bBackup=ui->bBackup_2->checkState();
    bNouse=ui->bNoUse_2->checkState();

    for (i=0;i<lRowNumber3;i++) //for all requirement in table 3
    {
        lRequirementCounter=0;
        sRequirementTip.clear();
        for (j=0;j<lRowNumber;j++) //for all servant
        {
            lPRI=ui->tServantData->item(j,4)->text().toInt();
            bEnable=(lPRI==2 and bMain) or (lPRI==1 and bBackup) or (lPRI==0 and bNouse);
            if (bEnable)
            {
                s=ui->tCalculateData->item(j,i+1+lRowNumber2)->text();
                lRequirementCounter+=s.toULongLong();
                if (s.toInt()>0)
                {
                    sServantName=ui->tServantData->item(j,1)->text();
                    sRequirementTip+=sServantName+":"+s+",";
                    if (sRequirementTip.length()-sRequirementTip.lastIndexOf("\n")>100)
                    {
                        sRequirementTip+="\n";
                    }
                }
            }
        }
        s.setNum(lRequirementCounter);
        ui->tRequirementData_2->item(i,3)->setText(s); //set requirement
        lPlanCounter=ui->tRequirementData_1->item(i,5)->text().toInt(); //get plan
        s=ui->tRequirementData_2->item(i,2)->text(); //get user data
        s.setNum(lRequirementCounter-s.toULongLong());
        if (s.toInt()>0)
        {
            if (s.toInt()>lPlanCounter)
            {
                ui->tRequirementData_2->item(i,4)->setBackgroundColor(QColor(255,0,0)); //set Red
            }
            else
            {
                ui->tRequirementData_2->item(i,4)->setBackgroundColor(QColor(0,0,255)); //set Blue
            }
            ui->tRequirementData_2->item(i,4)->setText(s); //set still requirement
        }
        else
        {
            ui->tRequirementData_2->item(i,4)->setBackgroundColor(QColor(255,255,255)); //set white
            ui->tRequirementData_2->item(i,4)->setText("0"); //set still requirement
        }
        if(sRequirementTip.right(1)=="\n")
        {
            sRequirementTip=sRequirementTip.left(sRequirementTip.length()-1);
        }
        if(sRequirementTip.right(1)==",")
        {
            sRequirementTip=sRequirementTip.left(sRequirementTip.length()-1);
        }
        ui->tRequirementData_2->item(i,1)->setToolTip(sRequirementTip);
    }
}

void MainWindow::CalculateServantRequirement(int row)
{
    int lNowBreak=0;
    int lTargetBreak=0;
    int lNowSkill=0;
    int lTargetSkill=0;
    int i=0;    
    int j=0;
    int k=0;
    int l=0;
    int lStars=0;
    QString s="";
    QString sRequirementName="";
    QString sServantRequirementTip="";
    int lRequirementCounter=0;
    qint64 lQPCounter=0;
    bool bRequirementNameFound=false;    

    lStars=ui->tServantData->item(row,2)->text().toInt();
    lNowBreak=ui->tServantData->item(row,5)->text().toInt();
    lTargetBreak=ui->tServantData->item(row,6)->text().toInt();

    for (i=1;i<ui->tCalculateData->columnCount();i++)
    {
        ui->tCalculateData->item(row,i)->setText("0"); //clear requirement
    }

    if (lTargetBreak>lNowBreak) //calculate break requirement
    {
        for (i=lNowBreak+1;i<=lTargetBreak;i++) //for break level
        {
            for (j=1;j<=5;j++) //for requirement 1 to 5
            {
                k=(i-1)*5+j+3;
                s=ui->tServantRequirementData->item(row,k)->text(); //get requirement string
                if (!s.isEmpty())
                {
                    sRequirementName=s.section("*",0,0); //get break requirement object
                    lRequirementCounter=s.section("*",1,1).toInt(); //get object counter
                    bRequirementNameFound=false; //reset found
                    for (k=0;k<lRowNumber2;k++) //add requirement 2
                    {
                        s=ui->tRequirementData_1->item(k,1)->text();
                        if (sRequirementName==s)
                        {
                            s=ui->tCalculateData->item(row,k+1)->text();
                            s.setNum(s.toInt()+lRequirementCounter);
                            ui->tCalculateData->item(row,k+1)->setText(s);
                            bRequirementNameFound=true;
                            break;
                        }
                    }
                    if (!bRequirementNameFound)
                    {
                        for (k=0;k<lRowNumber3;k++) //add requirement 3
                        {
                            s=ui->tRequirementData_2->item(k,1)->text();
                            if (sRequirementName==s)
                            {
                                s=ui->tCalculateData->item(row,k+1+lRowNumber2)->text();
                                s.setNum(s.toInt()+lRequirementCounter);
                                ui->tCalculateData->item(row,k+1+lRowNumber2)->setText(s);
                                bRequirementNameFound=true;
                                break;
                            }
                        }
                    }
                    if (!bRequirementNameFound)
                    {
                        //QMessageBox::about(this,"Error","Can`t find "+sRequirementName);
                    }
                }
            }
            if (row==0 or row==82 or row==148 or row==150 or row==151) //some servant break require zero qp
            {
                lQPCounter=0;
            }
            else
            {
                if (row==106)
                {
                    lStars=2; //angela break cost qp is 2 star
                }
                lQPCounter+=ui->tQPRequirementData->item(i-1,lStars-1)->text().toInt(); //add break qp
            }
        }
    }

    for (l=0;l<3;l++) //calculate skill requirement
    {
        lNowSkill=ui->tServantData->item(row,l+7)->text().toInt();
        lTargetSkill=ui->tServantData->item(row,l+10)->text().toInt();
        if (lTargetSkill>lNowSkill)
        {
            for (i=lNowSkill+1;i<=lTargetSkill;i++) //for skill level
            {
                for (j=1;j<=5;j++) //for 5 requirement
                {
                    k=(i-2)*5+23+j; //all skill level is 9
                    s=ui->tServantRequirementData->item(row,k)->text();
                    if (!s.isEmpty())
                    {
                        sRequirementName=s.section("*",0,0); //get break requirement object
                        lRequirementCounter=s.section("*",1,1).toInt(); //get object counter
                        bRequirementNameFound=false; //reset found
                        for (k=0;k<lRowNumber2;k++) //add requirement 2
                        {
                            s=ui->tRequirementData_1->item(k,1)->text();
                            if (sRequirementName==s)
                            {
                                s=ui->tCalculateData->item(row,k+1)->text();
                                s.setNum(s.toInt()+lRequirementCounter);
                                ui->tCalculateData->item(row,k+1)->setText(s);
                                bRequirementNameFound=true;
                                break;
                            }
                        }
                        if (!bRequirementNameFound)
                        {
                            for (k=0;k<lRowNumber3;k++) //add requirement 3
                            {
                                s=ui->tRequirementData_2->item(k,1)->text();
                                if (sRequirementName==s)
                                {
                                    s=ui->tCalculateData->item(row,k+1+lRowNumber2)->text();
                                    s.setNum(s.toInt()+lRequirementCounter);
                                    ui->tCalculateData->item(row,k+1+lRowNumber2)->setText(s);
                                    bRequirementNameFound=true;
                                    break;
                                }
                            }
                        }
                        if (!bRequirementNameFound) //if no found error
                        {
                            QMessageBox::about(this,"Error","Can`t find "+sRequirementName);
                        }
                    }
                }
                if (row==82 or row==148 or row==150 or row==151) //some servant qp cost 0
                {
                    lQPCounter=0;
                }
                else
                {
                    if (row==0) //mash skill cost qp is 3 star
                    {
                        lStars=3;
                    }
                    if (row==106)
                    {
                        lStars=2; //angela skill cost qp is 2 star
                    }
                    lQPCounter+=ui->tQPRequirementData->item(i-2+4,lStars-1)->text().toInt(); //add skill qp
                }
            }
        }
    }

    ui->tCalculateData->item(row,lRowNumber2+1)->setText(s.setNum(lQPCounter)); //set qp requirement

    sServantRequirementTip.clear();
    for (i=1;i<lRowNumber2+lRowNumber3+1;i++)
    {
        if (i!=38) //jump qp
        {
            if (i<=lRowNumber2)
            {
                s=ui->tCalculateData->item(row,i)->text();
                if (s.toInt()>0)
                {
                    sRequirementName=ui->tRequirementData_1->item(i-1,1)->text();
                    sServantRequirementTip+=sRequirementName+"*"+s+",";
                }
            }
            else
            {
                s=ui->tCalculateData->item(row,i)->text();
                if (s.toInt()!=0)
                {
                    sRequirementName=ui->tRequirementData_2->item(i-lRowNumber2-1,1)->text();
                    sServantRequirementTip+=sRequirementName+"*"+s+",";
                }
            }
            if (sServantRequirementTip.length()-sServantRequirementTip.lastIndexOf("\n")>100)
            {
                sServantRequirementTip+="\n";
            }
        }
    }
    if(sServantRequirementTip.right(1)=="\n")
    {
        sServantRequirementTip=sServantRequirementTip.left(sServantRequirementTip.length()-1);
    }
    if(sServantRequirementTip.right(1)==",")
    {
        sServantRequirementTip=sServantRequirementTip.left(sServantRequirementTip.length()-1);
    }
    ui->tServantData->item(row,1)->setToolTip(sServantRequirementTip);
}

void MainWindow::CalculatePlan()
{
    int i=0;
    int j=0;
    int lPlanCounter;
    int lUnlimitedPoolCounter;
    QString s;
    QCheckBox *pCheckBox;

    for (i=0;i<lRowNumber2;i++)
    {
        lPlanCounter=0;
        for (j=0;j<ui->tPlanShopData->rowCount();j++)
        {
            pCheckBox=static_cast<QCheckBox *>(ui->tPlanShopData->cellWidget(j,2));
            if (pCheckBox->checkState())
            {
                if (!ui->tPlanShopCalculateData->item(j,i+2)->text().isEmpty())
                {
                    lPlanCounter+=ui->tPlanShopCalculateData->item(j,i+2)->text().toInt(); //calculate shop plan in table 2
                }
            }            
        }
        for (j=0;j<ui->tPlanUnlimitedPoolData->rowCount();j++)
        {
            lUnlimitedPoolCounter=ui->tPlanUnlimitedPoolData->item(j,2)->text().toInt();
            if (lUnlimitedPoolCounter>0)
            {
                if (!ui->tPlanUnlimitedPoolCalculateData->item(j,i+2)->text().isEmpty())
                {
                    lPlanCounter+=ui->tPlanUnlimitedPoolCalculateData->item(j,i+2)->text().toInt()*lUnlimitedPoolCounter; //calculate unlimited pool plan in table 2
                }
            }
        }
        ui->tRequirementData_1->item(i,5)->setText(s.setNum(lPlanCounter));
    }
    for (i=0;i<lRowNumber3;i++)
    {
        lPlanCounter=0;
        for (j=0;j<ui->tPlanShopData->rowCount();j++)
        {
            pCheckBox=static_cast<QCheckBox *>(ui->tPlanShopData->cellWidget(j,2));
            if (pCheckBox->checkState())
            {
                if (!ui->tPlanShopCalculateData->item(j,i+lRowNumber2+2)->text().isEmpty())
                {
                    lPlanCounter+=ui->tPlanShopCalculateData->item(j,i+lRowNumber2+2)->text().toInt(); //calculate shop plan in table 3
                }
            }
        }
        for (j=0;j<ui->tPlanUnlimitedPoolData->rowCount();j++)
        {
            lUnlimitedPoolCounter=ui->tPlanUnlimitedPoolData->item(j,2)->text().toInt();
            if (lUnlimitedPoolCounter>0)
            {
                if (!ui->tPlanUnlimitedPoolCalculateData->item(j,i+lRowNumber2+2)->text().isEmpty())
                {

                    lPlanCounter+=ui->tPlanUnlimitedPoolCalculateData->item(j,i+lRowNumber2+2)->text().toInt()*lUnlimitedPoolCounter; //calculate unlimited pool plan in table 2
                }
            }
        }
        ui->tRequirementData_2->item(i,5)->setText(s.setNum(lPlanCounter));
    }
}

void MainWindow::CalculatePlan2()
{
    int i=0;
    int j=0;
    int k=0;
    int lPlanCounter;
    int lUnlimitedPoolCounter;
    int lPlanCounter1;
    QString s;
    QCheckBox *pCheckBox;
    QString sPlanName;
    QString sObjectName;

    for (i=0;i<ui->tRequirementData_1->rowCount();i++)
    {
        lPlanCounter=0; //init plan counter
        for (j=0;j<ui->tPlanShopData->rowCount();j++) //for all shop data
        {
            pCheckBox=static_cast<QCheckBox *>(ui->tPlanShopData->cellWidget(j,2));
            if (pCheckBox->checkState())
            {
                for (k=2;k<ui->tPlanShopCalculateData->columnCount();k++)
                {
                    s=ui->tPlanShopCalculateData->item(j,k)->text();
                    if (!s.isEmpty())
                    {
                        sObjectName=ui->tRequirementData_1->item(i,1)->text();
                        sPlanName=s.section("*",0,0); //get break requirement object
                        lPlanCounter1=s.section("*",1,1).toInt(); //get object counter
                        if (sObjectName==sPlanName)
                        {
                            lPlanCounter+=lPlanCounter1;
                        }
                    }
                }
            }
        }
        for (j=0;j<ui->tPlanUnlimitedPoolData->rowCount();j++) //for all unlimited pool data
        {
            lUnlimitedPoolCounter=ui->tPlanUnlimitedPoolData->item(j,2)->text().toInt();
            if (lUnlimitedPoolCounter>0)
            {
                for (k=2;k<ui->tPlanUnlimitedPoolCalculateData->columnCount();k++)
                {
                    s=ui->tPlanUnlimitedPoolCalculateData->item(j,k)->text();
                    if (!s.isEmpty())
                    {
                        sObjectName=ui->tRequirementData_1->item(i,1)->text();
                        sPlanName=s.section("*",0,0); //get break requirement object
                        lPlanCounter1=s.section("*",1,1).toInt(); //get object counter
                        if (sObjectName==sPlanName)
                        {
                            lPlanCounter+=(lPlanCounter1*lUnlimitedPoolCounter);
                        }
                    }
                }
            }
        }
        ui->tRequirementData_1->item(i,5)->setText(s.setNum(lPlanCounter));
    }
    for (i=0;i<ui->tRequirementData_2->rowCount();i++)
    {
        lPlanCounter=0; //init plan counter
        for (j=0;j<ui->tPlanShopData->rowCount();j++) //for all shop data
        {
            pCheckBox=static_cast<QCheckBox *>(ui->tPlanShopData->cellWidget(j,2));
            if (pCheckBox->checkState())
            {
                for (k=2;k<ui->tPlanShopCalculateData->columnCount();k++)
                {
                    s=ui->tPlanShopCalculateData->item(j,k)->text();
                    if (!s.isEmpty())
                    {
                        sObjectName=ui->tRequirementData_2->item(i,1)->text();
                        sPlanName=s.section("*",0,0); //get break requirement object
                        lPlanCounter1=s.section("*",1,1).toInt(); //get object counter
                        if (sObjectName==sPlanName)
                        {
                            lPlanCounter+=lPlanCounter1;
                        }
                    }
                }
            }
        }
        for (j=0;j<ui->tPlanUnlimitedPoolData->rowCount();j++) //for all unlimited pool data
        {
            lUnlimitedPoolCounter=ui->tPlanUnlimitedPoolData->item(j,2)->text().toInt();
            if (lUnlimitedPoolCounter>0)
            {
                for (k=2;k<ui->tPlanUnlimitedPoolCalculateData->columnCount();k++)
                {
                    s=ui->tPlanUnlimitedPoolCalculateData->item(j,k)->text();
                    if (!s.isEmpty())
                    {
                        sObjectName=ui->tRequirementData_2->item(i,1)->text();
                        sPlanName=s.section("*",0,0); //get break requirement object
                        lPlanCounter1=s.section("*",1,1).toInt(); //get object counter
                        if (sObjectName==sPlanName)
                        {
                            lPlanCounter+=lPlanCounter1*lUnlimitedPoolCounter;
                        }
                    }
                }
            }
        }
        ui->tRequirementData_2->item(i,5)->setText(s.setNum(lPlanCounter));
    }


}

void MainWindow::ReadConfig()
{
    int lRed, lGreen, lBlue;
    QString sConfigFilPath;
    QFile *fConfigFile;
    QSettings *stConfigFile;

    sConfigFilPath=QDir::currentPath()+"/config.ini";
    fConfigFile= new QFile(sConfigFilPath);
    if (fConfigFile->exists())
    {
        stConfigFile=new QSettings(sConfigFilPath,QSettings::IniFormat);
        ui->actionRF1->setText(stConfigFile->value("File/Path1").toString()); //read path
        ui->actionRF2->setText(stConfigFile->value("File/Path2").toString());
        ui->actionRF3->setText(stConfigFile->value("File/Path3").toString());
        ui->actionRF4->setText(stConfigFile->value("File/Path4").toString());
        ui->actionRF5->setText(stConfigFile->value("File/Path5").toString());
        sFilePath=ui->actionRF1->text();

        bShowTrueName=stConfigFile->value("Function/Truename").toBool(); //read true name status

        lRed=stConfigFile->value("Config/PRIColor0Red").toInt(); //read colors
        lGreen=stConfigFile->value("Config/PRIColor0Green").toInt();
        lBlue=stConfigFile->value("Config/PRIColor0Blue").toInt();
        ConfigColors.cPRIColor0.setRgb(lRed,lGreen,lBlue,255);
        lRed=stConfigFile->value("Config/PRIColor1Red").toInt();
        lGreen=stConfigFile->value("Config/PRIColor1Green").toInt();
        lBlue=stConfigFile->value("Config/PRIColor1Blue").toInt();
        ConfigColors.cPRIColor1.setRgb(lRed,lGreen,lBlue,255);
        lRed=stConfigFile->value("Config/PRIColor2Red").toInt();
        lGreen=stConfigFile->value("Config/PRIColor2Green").toInt();
        lBlue=stConfigFile->value("Config/PRIColor2Blue").toInt();
        ConfigColors.cPRIColor2.setRgb(lRed,lGreen,lBlue,255);
        lRed=stConfigFile->value("Config/ReqOKColorRed").toInt();
        lGreen=stConfigFile->value("Config/ReqOKColorGreen").toInt();
        lBlue=stConfigFile->value("Config/ReqOKColorBlue").toInt();
        ConfigColors.cReqOKColor.setRgb(lRed,lGreen,lBlue,255);
        lRed=stConfigFile->value("Config/ReqNGColorRed").toInt();
        lGreen=stConfigFile->value("Config/ReqNGColorGreen").toInt();
        lBlue=stConfigFile->value("Config/ReqNGColorBlue").toInt();
        ConfigColors.cReqNGColor.setRgb(lRed,lGreen,lBlue,255);
    }
    else
    {
        sFilePath="";
        bShowTrueName=false;
    }
    ui->actionShowTrueName->setChecked(bShowTrueName);
    SetServantName();
}

void MainWindow::WriteConfig()
{    
    QString sConfigFilPath;
    QSettings *stConfigFile;

    sConfigFilPath=QDir::currentPath()+"/config.ini";
    stConfigFile=new QSettings(sConfigFilPath,QSettings::IniFormat);
    stConfigFile->setValue("File/Path1",ui->actionRF1->text()); //save path
    stConfigFile->setValue("File/Path2",ui->actionRF2->text());
    stConfigFile->setValue("File/Path3",ui->actionRF3->text());
    stConfigFile->setValue("File/Path4",ui->actionRF4->text());
    stConfigFile->setValue("File/Path5",ui->actionRF5->text());
    stConfigFile->setValue("Function/TrueName",bShowTrueName); //save trur name status
}

void MainWindow::NewUserData()
{
    sFilePath=":/data/New";
    ReadUserData();
    bUserDataChanged=true;
    ui->sUserDataChanged->setVisible(bUserDataChanged);
    ui->sFilePathDisplay->setText("");
    sFilePath="";
}

void MainWindow::ReadFGHFile() //import fgh file
{
    int i=0;
    int j=0;
    int i1=0;
    int i2=0;
    QString sRequirementTableIndex;
    QString sFGHFilePath;
    QString s;
    QString s1;
    QString s2;

    sRequirementTableIndex="1,2,3,4,5,10,11,12,13,14,15,16,17,18,19,20,25,26,27,28,29,30,"
                           "31,32,33,123,124,125,126,127,128,129,130,131,132,133,134,135,"
                           "136,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116"
                           ",117,118,119,120,121,122,37,6,34,35,7,36,21,8,101"; //requirement index in fgh file

    sFGHFilePath = QFileDialog::getOpenFileName(this, tr("Open File"), "D:/",  tr("fgh file(*.fgh);;all file(*.*)"));

    if (!sFGHFilePath.isEmpty())
    {
        QFile *fFGHData=new QFile(QString(sFGHFilePath));
        if (!fFGHData->open(QIODevice::ReadOnly | QIODevice::Text)) //open file
        {
            QMessageBox::about(this,"Error","Can`t read " + sFGHFilePath);
            sFGHFilePath.clear();
        }
        else
        {
            bInit=true;
            QTextStream in(fFGHData);

            s=in.readLine(); //read requirement line
            while (!s.isEmpty())
            {
                i1=s.indexOf("\t");
                s1=s.left(i1);
                if (s1.isEmpty())
                {
                    s1="0";
                }
                if (i1!=(-1))
                {
                    s=s.right(s.length()-i1-1);
                }
                else
                {
                    s.clear();
                }
                i2=sRequirementTableIndex.indexOf(",");
                s2=sRequirementTableIndex.left(i2);
                sRequirementTableIndex=sRequirementTableIndex.right(sRequirementTableIndex.length()-i2-1);
                if (!s.isEmpty())
                {
                    if (s2.toInt()<100)
                    {
                        ui->tRequirementData_1->item(s2.toInt()-1,2)->setText(s1); //set requirement in table 2
                    }
                    else
                    {
                        ui->tRequirementData_2->item(s2.toInt()-101,2)->setText(s1); //set requirement in table 3
                    }

                }
                else
                {
                    ui->tRequirementData_2->item(0,2)->setText(s1); //last value is qp
                }
            }

            i=0;
            while (!in.atEnd())
            {
                s=in.readLine(); //read servant line
                for (j=1;j<10;j++)
                {
                    ui->tServantData->item(i,j+3)->setText(s.section("\t",j,j)); //set servant data in table 1
                    CheckSingleUserData(i,j);
                }
                CheckUserData(i);
                SetPRIColor(i);
                CalculateServantRequirement(i);
                i++;
            }

            fFGHData->close();
            CalculateRequirement2();
            CalculateRequirement3();
            bInit=false;
        }
    }
}

void MainWindow::SetServantName()
{
    int i=0;
    QString sName;

    for (i=0;i<lRowNumber;i++)
    {
        sName=ui->tTrueNameData->item(i,1)->text();
        if (!sName.isEmpty())
        {
            if (bShowTrueName)
            {
                ui->tServantData->item(i,1)->setText(sName);
            }
            else
            {
                sName=ui->tTrueNameData->item(i,0)->text();
                ui->tServantData->item(i,1)->setText(sName);
            }
        }
    }
}

//ui slot

void MainWindow::on_actionExit_triggered()
{
    MainWindow::close();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this,"About","阿荣天下第一\n所有数据来源于Mooncell和NGA网友分享");
}

void MainWindow::on_pushButton_clicked()
{
    ui->tServantData->setStyleSheet(QString("QTableWidget#tServantData::item{background-color:Red;}"));
}

void MainWindow::on_actionOpen_triggered()
{
    sFilePath="";
    ReadUserData();
}

void MainWindow::on_lClassSelect_activated(const QString &arg1)
{
    ClassSelectChanged(arg1);
}

void MainWindow::on_bMain_stateChanged(int)
{
    ClassSelectChanged(ui->lClassSelect->currentText());
}

void MainWindow::on_bBackup_stateChanged(int)
{
    ClassSelectChanged(ui->lClassSelect->currentText());
}

void MainWindow::on_bNoUse_stateChanged(int)
{
    ClassSelectChanged(ui->lClassSelect->currentText());
}

void MainWindow::on_pushButton_2_clicked()
{
    int a;
    a=ui->tRequirementData_1->columnWidth(1);
    a++;
    ui->tRequirementData_1->setColumnWidth(1,a);
    ui->label->setNum(a);
}

void MainWindow::on_tServantData_cellChanged(int row, int column)
{
    CheckSingleUserData(row,column);

    if (!bInit) //user change data
    {
        if (column>=4 and column<=12)
        {
            CheckUserData(row);
            if (column==4)
            {
                SetPRIColor(row); //user change pri
            }
            else
            {
                CalculateServantRequirement(row); //user change break or skill
            }
            //CalculateRequirement2();
            //CalculateRequirement3();
            bUserDataChanged=true;
            ui->sUserDataChanged->setVisible(bUserDataChanged);
        }
    }
}

void MainWindow::on_tServantData_currentCellChanged(int row, int column, int, int)
{
    sOldValue=ui->tServantData->item(row,column)->text();
}

void MainWindow::on_tRequirementData_1_cellChanged(int row, int column)
{
    CheckUserData2(row,column);    
    if (column==2 and !bInit)
    {
        CalculateRequirement2();
        bUserDataChanged=true;
        ui->sUserDataChanged->setVisible(bUserDataChanged);
    }
}

void MainWindow::on_tRequirementData_1_currentCellChanged(int row, int column, int , int)
{
    sOldValue=ui->tRequirementData_1->item(row,column)->text();
}

void MainWindow::on_tRequirementData_2_cellChanged(int row, int column)
{
    CheckUserData3(row,column);    
    if (column==2 and !bInit)
    {
        CalculateRequirement3();
        bUserDataChanged=true;
        ui->sUserDataChanged->setVisible(bUserDataChanged);
    }
}

void MainWindow::on_tRequirementData_2_currentCellChanged(int row, int column, int, int)
{
    sOldValue=ui->tRequirementData_2->item(row,column)->text();
}

void MainWindow::on_actionSave_triggered()
{
    SaveUserData();
}

void MainWindow::on_actionSave_As_triggered()
{
    sFilePath="";
    SaveUserData();
}

void MainWindow::on_bMain_2_stateChanged(int)
{
    if (bInit==false)
    {
        CalculateRequirement2();
        CalculateRequirement3();
    }
}

void MainWindow::on_bBackup_2_stateChanged(int)
{
    if (bInit==false)
    {
        CalculateRequirement2();
        CalculateRequirement3();
    }
}

void MainWindow::on_bNoUse_2_stateChanged(int)
{
    if (bInit==false)
    {
        CalculateRequirement2();
        CalculateRequirement3();
    }
}

void MainWindow::on_actionAboutQt_triggered()
{
    QMessageBox::aboutQt(this,"About Qt");
}

void MainWindow::on_actionNew_triggered()
{
    sFilePath="";
    NewUserData();
}

void MainWindow::on_actionImport_triggered()
{
    //QMessageBox::about(this,"Import fgh file.","Gugugu");
    sFilePath="";
    NewUserData();
    ReadFGHFile();
}

void MainWindow::on_actionShowTrueName_triggered()
{
    bShowTrueName=ui->actionShowTrueName->isChecked();
    SetServantName();
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    switch (index)
    {
    case 0:
    {
        ui->actionDataBottomMove->setEnabled(false);
        break;
    }
    case 1:
    {
        CalculatePlan2();
        CalculateRequirement2();
        CalculateRequirement3();
        ui->actionDataBottomMove->setEnabled(true);
        break;
    }
    case 2:
    {
        ui->actionDataBottomMove->setEnabled(true);
        break;
    }
    default:
    {
        break;
    }
    }

}

void MainWindow::on_tPlanUnlimitedPoolData_cellChanged(int row, int column)
{
    CheckUserPlanData(row,column);
}

void MainWindow::on_tPlanUnlimitedPoolData_currentCellChanged(int row, int column, int, int)
{
    sOldValue=ui->tRequirementData_2->item(row,column)->text();
}

void MainWindow::on_actionDataBottomMove_triggered()
{
    int i=0;
    int j=0;

    DataBottomMove(ui->tRequirementData_1);
    DataBottomMove(ui->tRequirementData_2);
    DataBottomMove(ui->tPlanUnlimitedPoolData);
    if (ui->tPlanShopData->hasFocus()) //check focus
    {
        i=ui->tPlanShopData->currentItem()->row(); //get row index
        for (j=ui->tPlanShopData->rowCount()-1;j>=i;j--)
        {
            QCheckBox *pCheckBox1= static_cast<QCheckBox *>(ui->tPlanShopData->cellWidget(j,2));
            QCheckBox *pCheckBox2= static_cast<QCheckBox *>(ui->tPlanShopData->cellWidget(j-1,2));
            pCheckBox1->setChecked(pCheckBox2->isChecked());
        }
    }
}

//ui event

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton bConfirm;

    WriteConfig();
    if (bUserDataChanged)
    {
        Confirm:
        bConfirm=QMessageBox::question(this,"Confirm","User data changed, do you want to save?",QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
        if (bConfirm==QMessageBox::Yes)
        {
            SaveUserData();
            if (!sFilePath.isEmpty())
            {
                event->accept();
            }
            else
            {
                goto Confirm;
            }
        }
        if (bConfirm==QMessageBox::No)
        {
            event->accept();
        }
        if (bConfirm==QMessageBox::Cancel)
        {
            event->ignore();
        }
    }
    else
    {
        event->accept();
    }
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    double dTableWidth=0;
    double dColumnWidth=0;

    dTableWidth=ui->tServantData->width();
    dColumnWidth=177*((dTableWidth+25)/1007);
    //ui->label->setNum(dColumnWidth);
    ui->tServantData->setColumnWidth(1,qRound(dColumnWidth));

    dTableWidth=ui->tRequirementData_1->width();
    dColumnWidth=127*((dTableWidth+25)/501);
    ui->tRequirementData_1->setColumnWidth(1,qRound(dColumnWidth));

    dTableWidth=ui->tRequirementData_2->width();
    dColumnWidth=127*((dTableWidth+25)/500);
    ui->tRequirementData_2->setColumnWidth(1,qRound(dColumnWidth));

    dTableWidth=ui->tPlanShopData->width();
    dColumnWidth=352*((dTableWidth+25)/501);
    ui->tPlanShopData->setColumnWidth(1,qRound(dColumnWidth));

    dTableWidth=ui->tPlanUnlimitedPoolData->width();
    dColumnWidth=352*((dTableWidth+25)/500);
    ui->tPlanUnlimitedPoolData->setColumnWidth(1,qRound(dColumnWidth));
}

void MainWindow::on_actionRF1_triggered()
{
    sFilePath=ui->actionRF1->text();
    ReadUserData();
}

void MainWindow::on_actionRF2_triggered()
{
    sFilePath=ui->actionRF2->text();
    ReadUserData();
}

void MainWindow::on_actionRF3_triggered()
{
    sFilePath=ui->actionRF3->text();
    ReadUserData();
}

void MainWindow::on_actionRF4_triggered()
{
    sFilePath=ui->actionRF4->text();
    ReadUserData();
}

void MainWindow::on_actionRF5_triggered()
{
    sFilePath=ui->actionRF5->text();
    ReadUserData();
}
