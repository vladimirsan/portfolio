#ifndef MAPPROPERTIES_H
#define MAPPROPERTIES_H

#include <QDialog>
#include <model/binaryModel/Map.h>
#include <model/MainModel.h>


namespace Ui {
class MapProperties;
}

namespace FigaroEditor
{ class GuiController; }

class MapPropertiesDialog : public QDialog
{
    Q_OBJECT
    
public:
	explicit MapPropertiesDialog(QWidget *parent = 0);
	~MapPropertiesDialog();

	void setUpWindow();

private slots:
    void on_btnSave_clicked();

private:
    Ui::MapProperties *ui;
};

#endif // MAPPROPERTIES_H
