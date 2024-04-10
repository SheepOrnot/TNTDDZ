#ifndef RULEWIDGET_H
#define RULEWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
namespace Ui {
class RuleWidget;
}

class RuleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RuleWidget(QWidget *parent = nullptr);
    ~RuleWidget();

private:
    Ui::RuleWidget *ui;
    QLabel *RuleLabel;
    QWidget *ContentWidget;
};

#endif // RULEWIDGET_H
