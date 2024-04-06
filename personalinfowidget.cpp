#include "personalinfowidget.h"
#include "ui_personalinfowidget.h"

PersonalInfoWidget::PersonalInfoWidget(int _Width,int _Height,QWidget *parent) :
    QWidget(parent),Width(_Width),Height(_Height),
    ui(new Ui::PersonalInfoWidget)
{
    ui->setupUi(this);
    this->setFixedSize(0.6*Width,0.7*Height);
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

    ui->ChooseProfile->setGeometry(0.422*Width, 0.285*Height, 0.107*Width, 0.037*Height);
    ui->NameLabel    ->setGeometry(0.029*Width, 0.052*Height, 0.155*Width, 0.064*Height);
    ui->UIDLabel     ->setGeometry(0.029*Width, 0.126*Height, 0.154*Width, 0.063*Height);
    ui->EmailLabel   ->setGeometry(0.029*Width, 0.201*Height, 0.154*Width, 0.063*Height);
    ui->Matches      ->setGeometry(0.422*Width, 0.402*Height, 0.155*Width, 0.064*Height);
    ui->Rate         ->setGeometry(0.422*Width, 0.550*Height, 0.154*Width, 0.063*Height);
    ui->KD           ->setGeometry(0.422*Width, 0.476*Height, 0.154*Width, 0.063*Height);
    ui->ProfileLabel ->setGeometry(0.422*Width, 0.074*Height, 0.107*Width, 0.190*Height);
    ui->ExitBtn      ->setGeometry(0.642*Width, 0.010*Height, 0.036*Width, 0.064*Height);

    ProfilePixmap = QPixmap(":image/image/Profile/"+QString::number(ProfileIndex)+".jpg");
    ProfilePixmap = ProfilePixmap.scaled(ui->ProfileLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation); // 将图片缩放到QLabel的尺寸
    ui->ProfileLabel->setPixmap(ProfilePixmap);
    ui->ProfileLabel->setScaledContents(true);
    connect(ui->ChooseProfile,&QComboBox::currentIndexChanged,this,&PersonalInfoWidget::onProfileChanged);

    QTextDocument doc;
    QSizeF boxSize(400, 70);
    QMarginsF margins(10, 10, 10, 10);
    // 设置方框内容
    QString text = "<p style=\"font-size:20pt;\">上行文本</p><p style=\"font-size:8pt;\">下行文本</p>";
    doc.setDefaultStyleSheet("body { color: black; }");
    doc.setPageSize(boxSize - QSize(2 * margins.left(), 2 * margins.top()));
    doc.setDocumentMargin(0);
    doc.setHtml(text);

    // 渲染文本内容到QPainter
    QPainter painter(this); // 将要绘制的设备
    painter.setRenderHint(QPainter::Antialiasing);
    doc.setPageSize(boxSize);
    QRectF marginsRect(margins.left(), margins.top(), boxSize.width() - margins.left() - margins.right(), boxSize.height() - margins.top() - margins.bottom());
    doc.setDocumentMargin(0);
    doc.drawContents(&painter, marginsRect);

    QString html = doc.toHtml();

    // 创建一个QLabel对象，并设置文本内容
    QLabel *label = new QLabel(this);
    label->setWordWrap(true); // 设置自动换行
    label->setAlignment(Qt::AlignCenter); // 设置文本居中对齐
    label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    label->setText(html); // 将HTML文本设置给QLabel
    label->setGeometry(50,300,400,70);
    label->setStyleSheet("QLabel { "
                         "   border: 1px solid black; "
                         "   border-radius: 10px; "
                         "   padding: 10px; "
                         "   background-color: transparent; "
                         "}");
    label->hide();

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
