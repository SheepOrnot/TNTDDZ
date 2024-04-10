#include "personalinfowidget.h"
#include "ui_personalinfowidget.h"

PersonalInfoWidget::PersonalInfoWidget(int _Width,int _Height,QWidget *parent) :
    QWidget(parent),Width(_Width),Height(_Height),
    ui(new Ui::PersonalInfoWidget)
{
    ui->setupUi(this);
    this->setFixedSize(888,735);
//********测试*********
    ProfileIndex = 0;
//********end*********
    QStringList resolutionOptions;
    resolutionOptions <<"经典马嘉祺"<<"经典丁程鑫"<< "经典宋亚轩"<<"经典刘耀文"<<"经典张真源"
                      <<"经典严浩翔"<<"经典贺俊霖"<<"马嘉祺2"<<"马嘉祺3"<<"马嘉祺4";
    ui->ChooseProfile->addItems(resolutionOptions);
    ui->ChooseProfile->setMaxVisibleItems(5);
    ui->ChooseProfile->setCurrentIndex(ProfileIndex);
    ui->ChooseProfile->setMinimumWidth(150);

    ui->ChooseProfile->setGeometry(0.400*Width, 0.285*Height, 0.107*Width, 0.037*Height);
    ui->NameLabel    ->setGeometry(0.029*Width, 0.052*Height, 0.155*Width, 0.064*Height);
    ui->UIDLabel     ->setGeometry(0.029*Width, 0.126*Height, 0.154*Width, 0.063*Height);
    ui->EmailLabel   ->setGeometry(0.029*Width, 0.201*Height, 0.154*Width, 0.063*Height);
    ui->Matches      ->setGeometry(0.400*Width, 0.402*Height, 0.155*Width, 0.064*Height);
    ui->Rate         ->setGeometry(0.400*Width, 0.550*Height, 0.154*Width, 0.063*Height);
    ui->KD           ->setGeometry(0.400*Width, 0.476*Height, 0.154*Width, 0.063*Height);
    ui->ProfileLabel ->setGeometry(0.400*Width, 0.074*Height, 0.107*Width, 0.190*Height);
    ui->ExitBtn      ->setGeometry(0.642*Width, 0.010*Height, 0.036*Width, 0.064*Height);
    ui->scrollArea   ->setGeometry(0.029*Width, 0.300*Height, 0.300*Width, 0.300*Height);

    ProfilePixmap = QPixmap(":image/image/Profile/"+QString::number(ProfileIndex)+".jpg");
    ProfilePixmap = ProfilePixmap.scaled(ui->ProfileLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation); // 将图片缩放到QLabel的尺寸
    ui->ProfileLabel->setPixmap(ProfilePixmap);
    ui->ProfileLabel->setScaledContents(true);
    connect(ui->ChooseProfile,&QComboBox::currentIndexChanged,this,&PersonalInfoWidget::onProfileChanged);

    ui->EmailLabel->setMinimumWidth(200);
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ContentWidget = new QWidget;
    ContentWidget->setFixedSize(500,ScrollWidgetHeight);
    ContentWidget->setObjectName("ContentWidget");
    ContentWidget->setStyleSheet("QWidget#ContentWidget{border:1px solid black; border-radius:10px;}");
    ui->scrollArea->setWidget(ContentWidget);

    connect(ui->scrollArea->verticalScrollBar(), &QScrollBar::valueChanged,this,&PersonalInfoWidget::onScrollBarValueChanged);
    connect(this,&PersonalInfoWidget::scrollBarAtBotton,this,&PersonalInfoWidget::onRecordToBottom);
    std::vector<Record> tenrcords;
    for(int i = 0;i<10;i++)
    {
        Record oneRecord;
        oneRecord.Mode = "经典";
        oneRecord.Score = 5000;
        oneRecord.WinorLose = "胜利";
        oneRecord.identity = "农民";
        oneRecord.time = "2024/4/4 22:15:32";
        tenrcords.push_back(oneRecord);
    }
    UpdataRecords(0,tenrcords);
}

PersonalInfoWidget::~PersonalInfoWidget()
{
    delete ui;
}
void PersonalInfoWidget::onProfileChanged(int index)
{
    ProfileIndex = index;
    ProfilePixmap = QPixmap(":image/image/Profile/"+QString::number(ProfileIndex)+".jpg");
    ui->ProfileLabel->setPixmap(ProfilePixmap);
}
void PersonalInfoWidget::onScrollBarValueChanged()
{
    if(ui->scrollArea->verticalScrollBar()->value()==ui->scrollArea->verticalScrollBar()->maximum())
    {
        Q_EMIT scrollBarAtBotton();
    }
}
void PersonalInfoWidget::UpdataRecords(bool isLast,std::vector<Record> TenRecords)
{
    QString WinorLose;
    QString Mode;
    QString Identity;
    QString Score;
    QString Time;
    for(unsigned i = 0; i< TenRecords.size();i++)
    {
        records.push_back(TenRecords[i]);
    }
    for(unsigned i = 0;i<recordLabels.size();i++)
    {
        if(recordLabels[i]) delete recordLabels[i];
    }
    for(unsigned i = 0;i<records.size();i++)
    {
        QLabel *label = new QLabel(ContentWidget);
        label->setGeometry(7,i*85+10,0.280*Width,80);
        WinorLose = QString::fromStdString(records[i].WinorLose);
        WinorLose=WinorLose.leftJustified(8, ' ');
        Mode =  QString::fromStdString(records[i].Mode);
        Mode=Mode.leftJustified(15, ' ');
        Time =  QString::fromStdString(records[i].time);
        Time=Time.leftJustified(15, ' ');
        Score =  QString::number(records[i].Score);
        Score=Score.leftJustified(8, ' ');
        Identity =  QString::fromStdString(records[i].identity);
        Identity=Identity.leftJustified(27, ' ');
        QString text = QString("<html>"
                       "<pre><font size='6'><b>%1</b></font><font size='5'>%2%3</font></pre>"
                       "<pre><font size='4'>%4%5</font></pre>"
                               "</html>").arg(WinorLose).arg(Mode).arg(Score).arg(Identity).arg(Time);
        label->setText(text);

        // 设置Label允许解析和显示HTML标记
        label->setOpenExternalLinks(true);
        label->setTextFormat(Qt::RichText);
        label->setAlignment(Qt::AlignCenter);
        label->setStyleSheet("QLabel{border-radius:10px ; border: 1px solid black;}");
        label->show();
        recordLabels.push_back(label);
    }
    if(!isLast)
    {
        ScrollWidgetHeight = records.size()*85+20;
        ContentWidget->setFixedSize(0.287*Width,ScrollWidgetHeight);
        CanGetRecord = 1;
    }
    else
    {
        ScrollWidgetHeight = records.size()*85+25;
        ContentWidget->setFixedSize(0.287*Width,ScrollWidgetHeight);
        QLabel *BottomLabel = new QLabel(ContentWidget);
        BottomLabel->setText("拉满了，实在拉不出来了...");
        BottomLabel->setAlignment(Qt::AlignCenter);
        BottomLabel->setGeometry(7,ScrollWidgetHeight-20,400,20);
        BottomLabel->show();
        BottomLabel->setStyleSheet("font:10px;");
        CanGetRecord = 0;
    }
}
void PersonalInfoWidget::onRecordToBottom()
{
 std::vector<Record> tenrcords;
    if(CanGetRecord == 1)
    {
//***********test***************
        for(int i = 0;i<10;i++)
        {
            Record oneRecord;
            oneRecord.Mode = "经典";
            oneRecord.Score = 5000;
            oneRecord.WinorLose = "胜利";
            oneRecord.identity = "地主";
            oneRecord.time = "2024/4/4 22:15:32";
            tenrcords.push_back(oneRecord);
        }
        UpdataRecords(1,tenrcords);
//**************end***************
    }
    CanGetRecord = 0;
}
