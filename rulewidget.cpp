#include "rulewidget.h"
#include "ui_rulewidget.h"

RuleWidget::RuleWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RuleWidget)
{
    ui->setupUi(this);
    this->setFixedSize(450,540);
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    this->setWindowModality(Qt::ApplicationModal);
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setWindowTitle("游戏规则");
    ContentWidget = new QWidget;
    ContentWidget->setFixedSize(this->width(),1500);
    ui->scrollArea->setWidget(ContentWidget);
    RuleLabel = new QLabel(ContentWidget);
    RuleLabel->setGeometry(20,20,410,3000);
    RuleLabel->setStyleSheet("QLabel { border: 0.5px solid black; border-radius:10px;font: 10pt 微软雅黑;}");
    RuleLabel->setWordWrap(true);
    QString rules = "1）游戏人数：3人。\n\
\n\
2）游戏牌数：54张，带大小王，一人17张，三张作为底牌，地主\n\
未确定千万家不能看到底牌。\n\
\n\
3）出牌规则：\n\
1.发牌：一副牌54张，带大小王，一人17张，三张作为底牌，地主未确定前玩家不能看到底牌。\n\
2.叫地主（叫地主和抢地主）：叫地主时可以选择“叫地主”、“不叫”，直到有一位玩家选择叫地主，其它玩家可以轮流抢地主，直到第一个叫地主的玩家选择叫地主或者不叫后确定地主和农民。\n\
3.第一轮叫牌的玩家由系统随机选择。\n\
4.如果都选择不叫，则本局流局，直接结束并进入下一局游戏。\n\
5.加倍玩法：在叫分规则下，玩家叫完地主后，会多一轮加倍环节，所有玩家选择是否加倍。\n\
6.出牌：由地主先出牌，然后按逆时针依次出牌，轮到玩家跟牌时，玩家可以选择“不出”或者出比上一家打的牌。\n\
7.胜负判定：地主打完牌为地主获胜，某一个农民打完牌则为所有农民获胜。\n\
\n\
4）牌型：\n\
火箭：即双王（大王和小王），最大的牌\n\
炸弹：四张相同的数值牌（如四个7）\n\
单牌：单个牌（如红桃5）\n\
对牌：数值相同的牌（如梅花4加方块4）\n\
三张牌：数值相同的三张牌（如3个J）\n\
三带一（三带二）：数值相同的三张牌+一张单牌或一对牌。例如：333+6,333+99\n\
单顺：五张或更多的连续单牌。不包括2和大小王（如34567、10JQK1）\n\
双顺：三对或更多的连续对牌。不包括2和大小王（如334455、JJQQKK11）\n\
三顺：两个或更多的连续三张牌。不包括2点和双王（如333444,333444555）\n\
飞机带翅膀：三顺+同数量的单牌或对牌（如333444+7+9、333444+66+77）\n\
四带二：四张数值相同的牌+两个单牌或对牌（如5555+3+8、5555+44+77）\n\
注意：当玩家所出的牌为最后一手牌时，也必须符合以上出牌规则，不能出现444555+6的牌型。\n\
\n\
5）牌型大小：\n\
1.火箭最大，可以打任意其他的牌。\n\
2.炸弹比火箭小，比其他的牌打。都是炸弹时牌牌的分值比大小。 \n\
3.除火箭和炸弹外，其他牌必须要牌型相同且张数相同才能比大小。\n\
4.单牌按分值比大小，依次是大王>小王>2>1>K>Q>J>10>9>8>7>6>5>4>3。\n\
5.对牌，三张牌都是按比分值比大小。\n\
6.顺子按最大的一张比大小。\n\
7.飞机带翅膀和四带二按其中的三顺和四张部分比较大小，带的牌不影响大小。\n\
8.注意：以上牌型比较均不分花色。\n\
\n\
6）积分规则：\n\
1.倍数：叫地主玩法初始分为1分（叫分玩法初始分为最大叫分，乘以加倍的倍数）每出一个炸弹或者火箭翻一倍。（留在手里没有出去的火箭和炸弹不算）\n\
2.春天：地主所有牌出完，而其余两家一张未出，分数X2。\n\
3.反春天：农民其中一家先出完牌，而地主只出过一手牌，分数X2。\n\
4.炸弹：每打出一个炸弹，分数X2。\n\
5.火箭：火箭打出后，分数X2。\n\
\n\
7)记牌器开启方法\n\
CTRL+. 开启记牌器，再按关闭";
    RuleLabel->setText(rules);
    RuleLabel->setAlignment(Qt::AlignLeft|Qt::AlignTop);

}

RuleWidget::~RuleWidget()
{
    delete ui;
}
