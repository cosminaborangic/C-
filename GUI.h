#include <vector>
#include <string>
#include <QtWidgets/QApplication>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QTableWidget>
#include <QMessageBox>
#include <QHeaderView>
#include <QGroupBox>
#include <QRadioButton>
#include "service.h"

using std::vector;
using std::string;

class ConsoleGUI : public QWidget {
private:
	QVBoxLayout* btn_layout;
	ActivitateStore& srv;

	//add
	//QGroupBox* groupBoxAdd = new QGroupBox(tr("Adaugare"));

	QLabel* lblTitlu = new QLabel("Titlu:");
	QLabel* lblDescriere = new QLabel("Descriere:");
	QLabel* lblTip = new QLabel("Tip:");
	QLabel* lblDurata = new QLabel("Durata:");

	QLineEdit* editTitlu;
	QLineEdit* editDescriere;
	QLineEdit* editTip;
	QLineEdit* editDurata;

	QPushButton* btnAddActivity;

	//dell
	QPushButton* btnDellActivity;

	//modify
	QPushButton* btnModifyActivity;
	
	//find
	QPushButton* btnFindActivity;

	//filter
	QGroupBox* groupBoxFilter = new QGroupBox(tr("Filtrare"));

	QLabel* lblFilterDescriere = new QLabel{ "Descriere dupa care se filtreaza:" };
	QLineEdit* editFilterDescriere;
	QLabel* lblFilterTip = new QLabel{ "Tipul dupa care se filtreaza:" };
	QLineEdit* editFilterTip;
	QPushButton* btnFilterDescriere;
	QPushButton* btnFilterTip;

	//sort
	QGroupBox* groupBoxSort = new QGroupBox(tr("Tip sortare"));

	QRadioButton* radioSortTitlu = new QRadioButton(QString::fromStdString("Titlu"));
	QRadioButton* radioSortDescriere = new QRadioButton(QString::fromStdString("Descriere"));
	QRadioButton* radioSortTipDurata = new QRadioButton(QString::fromStdString("Tip+Durata"));
	QPushButton* btnSortActivities;

	QPushButton* btnReloadData;

	QTableWidget* tableActivities;

	//undo
	QPushButton* btnUndo;

	//tip
	QPushButton* btnTip;

	void initializeGUIComponents();

	void connectSignalsSlots();

	void reloadActivityList(vector<Activitate> activities);

public:
	ConsoleGUI(ActivitateStore& srv) : srv{ srv } {
		initializeGUIComponents();
		connectSignalsSlots();
		reloadActivityList(srv.get_all_activities());
	}

	void gui_AddActivity();
	void gui_DellActivity();
	void gui_ModifyActivity();
	void gui_undo();
	void gui_addTip();
};


class ConsoleGUIProgram :public QWidget {
private:
	ActivitateStore& srv;

	//add
	QLabel* lblTitluP = new QLabel("Titlu:");
	QLineEdit* editTitluP;
	QPushButton* btnAddProgram;

	//add random
	QLabel* lblNr = new QLabel("Numar:");
	QLineEdit* editNr;
	QPushButton* btnAddRandom;

	//goleste program
	QPushButton* btnGoleste;

	//export
	QLabel* lblFile = new QLabel("Fisier:");
	QLineEdit* editFile;
	QPushButton* btnExport;


	QTableWidget* tableActivities;


	void initializeGUIProgComponents();
	void connectSignalsSlotsProg();
	void reloadActivityListFromProg(vector<Activitate> activities);

public:
	ConsoleGUIProgram(ActivitateStore& srv) : srv{ srv } {
		initializeGUIProgComponents();
		connectSignalsSlotsProg();
		reloadActivityListFromProg(srv.get_all_program_srv());
	}

	void gui_AddProgram();
	void gui_AddProgramRandom();
	void gui_Export();
};