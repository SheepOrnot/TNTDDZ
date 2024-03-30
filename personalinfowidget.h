#ifndef PERSONALINFOWIDGET_H
#define PERSONALINFOWIDGET_H

#include <QWidget>

namespace Ui {
class PersonalInfoWidget;
}

class PersonalInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PersonalInfoWidget(QWidget *parent = nullptr);
    ~PersonalInfoWidget();

private:
    Ui::PersonalInfoWidget *ui;
};

#endif // PERSONALINFOWIDGET_H
