#ifndef ADDMAPDIALOG_H
#define ADDMAPDIALOG_H

#include <model/binaryModel/Map.h>
#include <model/MainModel.h>
#include <QDialog>

namespace Ui
{ class AddMapDialog; }

namespace FigaroEditor
{ class GuiController; }

class AddMapDialog : public QDialog
{
    Q_OBJECT
    
public:
	explicit AddMapDialog(QWidget *parent = 0);
	~AddMapDialog();

	void setUpWindow();
private slots:
	void on_btnAdd_clicked();

private:
	Ui::AddMapDialog *ui;
	FigaroEditor::Map mapData;
};

#endif // ADDMAPDIALOG_H
