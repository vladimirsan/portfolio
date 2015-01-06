#ifndef ENGINECONFIGDIALOG_H
#define ENGINECONFIGDIALOG_H

#include <QDialog>
#include <QStringList>
#include <model/MainModel.h>


namespace Ui
{class EngineConfigDialog;}

namespace FigaroEditor
{class GuiController;}

class EngineConfigDialog : public QDialog
{
    Q_OBJECT
    
public:
	explicit EngineConfigDialog(QWidget *parent = 0);
	void setUpWindow();
	~EngineConfigDialog();
    
private slots:
    void on_pushButton_clicked();

private:
    Ui::EngineConfigDialog *ui;
    QStringList headers;
};

#endif // ENGINECONFIGDIALOG_H
