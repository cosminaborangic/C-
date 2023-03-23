#include "GUI.h"

void ConsoleGUI::initializeGUIComponents() {
	QHBoxLayout* lyMain = new QHBoxLayout;
	this->setLayout(lyMain);


	//COMPONENTA LEFT
	QWidget* left = new QWidget;
	QVBoxLayout* lyLeft = new QVBoxLayout;
	left->setLayout(lyLeft);

	//adaugare
	QWidget* form = new QWidget;
	QFormLayout* lyForm = new QFormLayout;
	form->setLayout(lyForm);
	this->editTitlu = new QLineEdit;
	this->editDescriere = new QLineEdit;
	this->editTip = new QLineEdit;
	this->editDurata = new QLineEdit;

	lyForm->addRow(lblTitlu, editTitlu);
	lyForm->addRow(lblDescriere, editDescriere);
	lyForm->addRow(lblTip, editTip);
	lyForm->addRow(lblDurata, editDurata);
	btnAddActivity = new QPushButton("Adauga activitate");

	lyLeft->addWidget(form);
	lyLeft->addWidget(btnAddActivity);

	//stergere
	btnDellActivity = new QPushButton("Sterge activitate");
	lyLeft->addWidget(btnDellActivity);

	//modificare
	btnModifyActivity = new QPushButton("Modifica activitate");
	lyLeft->addWidget(btnModifyActivity);

	//cautare
	btnFindActivity = new QPushButton("Cauta activitate");
	lyLeft->addWidget(btnFindActivity);

	//undo
	btnUndo = new QPushButton("Undo");
	lyLeft->addWidget(btnUndo);

	//filtrare
	QWidget* formFilter = new QWidget;
	QFormLayout* lyFormFilter = new QFormLayout;
	formFilter->setLayout(lyFormFilter);
	editFilterDescriere = new QLineEdit;
	lyFormFilter->addRow(lblFilterDescriere, editFilterDescriere);
	btnFilterDescriere = new QPushButton("Filtreaza dupa descriere");
	lyFormFilter->addWidget(btnFilterDescriere);
	
	editFilterTip = new QLineEdit;
	lyFormFilter->addRow(lblFilterTip, editFilterTip);
	btnFilterTip = new QPushButton("Filtreaza dupa tip");
	lyFormFilter->addWidget(btnFilterTip);

	lyLeft->addWidget(formFilter);


	//sortare
	QVBoxLayout* lyRadioBox = new QVBoxLayout;
	this->groupBoxSort->setLayout(lyRadioBox);
	lyRadioBox->addWidget(radioSortTitlu);
	lyRadioBox->addWidget(radioSortDescriere);
	lyRadioBox->addWidget(radioSortTipDurata);

	btnSortActivities = new QPushButton("Sorteaza activitati");
	lyRadioBox->addWidget(btnSortActivities);
	lyRadioBox->addWidget(groupBoxSort);

	lyLeft->addWidget(groupBoxSort); //adaugam in partea stanga.

	//reload data
	btnReloadData = new QPushButton("Reload data");
	lyLeft->addWidget(btnReloadData);


	//COMPONENTA RIGHT
	QWidget* right = new QWidget;
	QVBoxLayout* lyRight = new QVBoxLayout;
	right->setLayout(lyRight);

	int noLines = 10;
	int noColums = 4;
	this->tableActivities = new QTableWidget(noLines, noColums);

	//setez header-ul
	QStringList tblHeaderList;
	tblHeaderList << "Titlu" << "Descriere" << "Tip" << "Durata";
	this->tableActivities->setHorizontalHeaderLabels(tblHeaderList);

	//obtiune pentru a redimensiona celulele din tabel in functie de continut
	this->tableActivities->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	
	lyRight->addWidget(tableActivities);


	lyMain->addWidget(left);
	lyMain->addWidget(right);

	//tip
	QWidget* btn_widget = new QWidget;
	btn_layout = new QVBoxLayout;
	btn_widget->setLayout(btn_layout);
	lyMain->addWidget(btn_widget);
	gui_addTip();

}

void ConsoleGUI::reloadActivityList(vector<Activitate> activities) {
	this->tableActivities->clearContents();
	this->tableActivities->setRowCount(activities.size());

	int lineNumber = 0;
	for (auto& activity : activities) {
		this->tableActivities->setItem(lineNumber, 0, new QTableWidgetItem(QString::fromStdString(activity.get_titlu())));
		this->tableActivities->setItem(lineNumber, 1, new QTableWidgetItem(QString::fromStdString(activity.get_descriere())));
		this->tableActivities->setItem(lineNumber, 2, new QTableWidgetItem(QString::fromStdString(activity.get_tip())));
		this->tableActivities->setItem(lineNumber, 3, new QTableWidgetItem(QString::number(activity.get_durata())));
		lineNumber++;
	}
}

void ConsoleGUI::connectSignalsSlots() {
	QObject::connect(btnAddActivity, &QPushButton::clicked, this, &ConsoleGUI::gui_AddActivity);

	QObject::connect(btnDellActivity, &QPushButton::clicked, this, &ConsoleGUI::gui_DellActivity);

	QObject::connect(btnModifyActivity, &QPushButton::clicked, this, &ConsoleGUI::gui_ModifyActivity);

	QObject::connect(btnUndo, &QPushButton::clicked, this, &ConsoleGUI::gui_undo);

	QObject::connect(btnFindActivity, &QPushButton::clicked, [&]() {
		string find = this->editTitlu->text().toStdString();
		Activitate activity = srv.find_activity(find);
		vector<Activitate> foundActivity;
		foundActivity.push_back(activity);
		reloadActivityList(foundActivity);
		editTitlu->clear();
		});

	QObject::connect(btnFilterDescriere, &QPushButton::clicked, [&]() {
		string filterC = this->editFilterDescriere->text().toStdString();
		reloadActivityList(srv.filtrareDescriere(filterC));
		editFilterDescriere->clear();
		});

	QObject::connect(btnFilterTip, &QPushButton::clicked, [&]() {
		string filterC = this->editFilterTip->text().toStdString();
		reloadActivityList(srv.filtrareTip(filterC));
		editFilterTip->clear();
		});

	QObject::connect(btnSortActivities, &QPushButton::clicked, [&]() {
		if (radioSortTitlu->isChecked())
			reloadActivityList(srv.sortareTitlu());
		else if (radioSortDescriere->isChecked())
			reloadActivityList(srv.sortareDescriere());
		else if (radioSortTipDurata->isChecked())
			reloadActivityList(srv.sortareTipDurata());
		});

	QObject::connect(btnReloadData, &QPushButton::clicked, [&]() {
		reloadActivityList(srv.get_all_activities());
		});

}

void ConsoleGUI::gui_AddActivity() {
	try {
		string titlu = editTitlu->text().toStdString();
		string descriere = editDescriere->text().toStdString();
		string tip = editTip->text().toStdString();
		double durata = editDurata->text().toDouble();

		editTitlu->clear();
		editDescriere->clear();
		editTip->clear();
		editDurata->clear();

		srv.add_activity(titlu, descriere, tip, durata);
		reloadActivityList(this->srv.get_all_activities());

		QMessageBox::information(this, "Info", QString::fromStdString("Activitate adaugata cu succes!"));
		gui_addTip();
	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.get_errors()));
	}
	catch (ValidationException& ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString("Activitatea este invalida!"));
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.get_errors()));
	}
}

void ConsoleGUI::gui_DellActivity() {
	try {
		//QMessageBox::information(this, "Info", QString::fromStdString("Introduceti titul activitatii pe care doriti sa o stergeti!"));
		string titlu = editTitlu->text().toStdString();

		editTitlu->clear();

		srv.delete_activity(titlu);
		reloadActivityList(srv.get_all_activities());

		QMessageBox::information(this, "Info", QString::fromStdString("Activitatea stearsa cu succes!"));
		gui_addTip();
	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString("Activitatea cu acest titlu nu se gaseste in lista!"));
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.get_errors()));
	}

}

void ConsoleGUI::gui_ModifyActivity() {
	try {
		string titlu = editTitlu->text().toStdString();
		string descriere = editDescriere->text().toStdString();
		string tip = editTip->text().toStdString();
		double durata = editDurata->text().toDouble();

		editTitlu->clear();
		editDescriere->clear();
		editTip->clear();
		editDurata->clear();

		srv.modify_activity(titlu, descriere, tip, durata);
		reloadActivityList(srv.get_all_activities());

		QMessageBox::information(this, "Info", QString::fromStdString("Activitatea modificata cu succes!"));
		gui_addTip();
	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString("Activitatea cu acest titlu nu se gaseste in lista!"));
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.get_errors()));
	}
}

void ConsoleGUI::gui_undo() {
	try {
		srv.undo();
		reloadActivityList(srv.get_all_activities());
		QMessageBox::information(this, "Info", QString::fromStdString("Undo realizat cu succes!"));
		gui_addTip();
	}
	catch (std::exception()) {
		QMessageBox::warning(this, "Warning", QString::fromStdString("Nu se mai poate face undo!"));
	}
}

void ConsoleGUI::gui_addTip() {
	vector<Activitate> activities = srv.get_all_activities();
	vector<std::pair<string, int>> tipuri;
	for (const auto& a : activities) {
		bool ok = false;
		int i = 0;
		for (const auto& t : tipuri) {
			if (t.first == a.get_tip()) {
				ok = true;
				break;
			}
		}
		if (ok == true)
			tipuri[i].second++;
		else tipuri.emplace_back(a.get_tip(), 1);
	}
	QLayoutItem* item;
	while ((item = btn_layout->takeAt(0)) != NULL)
	{
		delete item->widget();
		delete item;
	}


	for (const auto& t : tipuri) {
		const string& tip = t.first;
		const int& nr = t.second;
		auto item = new QPushButton(QString::fromStdString(tip));

		QObject::connect(item, &QPushButton::clicked, [nr] {
			string n = std::to_string(nr);
			auto* lbl = new QLabel(QString::fromStdString(n));
			lbl->show();
			//QMessageBox::information(this, "Info", QString::fromStdString(n));
			});
		btn_layout->addWidget(item);
	}
}


//PROGRAM*********************************************************************************

void ConsoleGUIProgram::initializeGUIProgComponents() {
	QHBoxLayout* lyMain = new QHBoxLayout;
	this->setLayout(lyMain);


	//COMPONENTA LEFT
	QWidget* left = new QWidget;
	QVBoxLayout* lyLeft = new QVBoxLayout;
	left->setLayout(lyLeft);

	//adaugare
	QWidget* form = new QWidget;
	QFormLayout* lyForm = new QFormLayout;
	form->setLayout(lyForm);
	this->editTitluP = new QLineEdit;

	lyForm->addRow(lblTitluP, editTitluP);
	btnAddProgram = new QPushButton("Adauga activitate in program");
	lyForm->addWidget(btnAddProgram);

	lyLeft->addWidget(form);

	//adaugare random
	QWidget* formAddR = new QWidget;
	QFormLayout* lyFormAddR = new QFormLayout;
	formAddR->setLayout(lyFormAddR);
	this->editNr = new QLineEdit;

	lyFormAddR->addRow(lblNr, editNr);
	btnAddRandom = new QPushButton("Adauga activitati random in program");
	lyFormAddR->addWidget(btnAddRandom);

	lyLeft->addWidget(formAddR);

	//export
	QWidget* formEx = new QWidget;
	QFormLayout* lyFormEx = new QFormLayout;
	formEx->setLayout(lyFormEx);
	this->editFile = new QLineEdit;

	lyFormEx->addRow(lblFile, editFile);
	btnExport = new QPushButton("Export");
	lyFormEx->addWidget(btnExport);

	lyLeft->addWidget(formEx);

	//goleste program
	btnGoleste = new QPushButton("Goleste lista activitati!");
	lyLeft->addWidget(btnGoleste);

	//COMPONENTA RIGHT
	QWidget* right = new QWidget;
	QVBoxLayout* lyRight = new QVBoxLayout;
	right->setLayout(lyRight);

	int noLines = 10;
	int noColums = 4;
	this->tableActivities = new QTableWidget(noLines, noColums);

	//setez header-ul
	QStringList tblHeaderList;
	tblHeaderList << "Titlu" << "Descriere" << "Tip" << "Durata";
	this->tableActivities->setHorizontalHeaderLabels(tblHeaderList);

	//obtiune pentru a redimensiona celulele din tabel in functie de continut
	this->tableActivities->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

	lyRight->addWidget(tableActivities);

	lyMain->addWidget(left);
	lyMain->addWidget(right);

}

void ConsoleGUIProgram::reloadActivityListFromProg(vector<Activitate> activities) {
	this->tableActivities->clearContents();
	this->tableActivities->setRowCount(activities.size());

	int lineNumber = 0;
	for (auto& activity : activities) {
		this->tableActivities->setItem(lineNumber, 0, new QTableWidgetItem(QString::fromStdString(activity.get_titlu())));
		this->tableActivities->setItem(lineNumber, 1, new QTableWidgetItem(QString::fromStdString(activity.get_descriere())));
		this->tableActivities->setItem(lineNumber, 2, new QTableWidgetItem(QString::fromStdString(activity.get_tip())));
		this->tableActivities->setItem(lineNumber, 3, new QTableWidgetItem(QString::number(activity.get_durata())));
		lineNumber++;
	}
}

void ConsoleGUIProgram::connectSignalsSlotsProg() {
	QObject::connect(btnAddProgram, &QPushButton::clicked, this, &ConsoleGUIProgram::gui_AddProgram);
	QObject::connect(btnAddRandom, &QPushButton::clicked, this, &ConsoleGUIProgram::gui_AddProgramRandom);

	QObject::connect(btnGoleste, &QPushButton::clicked, [&]() {
		srv.goleste_program_srv();
		QMessageBox::information(this, "Info", QString::fromStdString("Lista de activitati din program a fost golita!"));
		reloadActivityListFromProg(srv.get_all_program_srv());
		});

	QObject::connect(btnExport, &QPushButton::clicked, this, &ConsoleGUIProgram::gui_Export);
}


void ConsoleGUIProgram::gui_AddProgram() {
	try {
		string titlu = editTitluP->text().toStdString();

		editTitluP->clear();

		srv.adauga_program_srv(titlu);
		reloadActivityListFromProg(this->srv.get_all_program_srv());

		QMessageBox::information(this, "Info", QString::fromStdString("Activitate adaugata cu succes in program!"));
	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.get_errors()));
	}
	catch (std::exception) {
		QMessageBox::warning(this, "Warning", QString::fromStdString("Activitatea se afla deja in program!"));
	}
}

void ConsoleGUIProgram::gui_AddProgramRandom() {
	try {
		string n = editNr->text().toStdString();
		int nr;

		editNr->clear();

		nr = stoi(n);
		srv.adauga_random_srv(nr);
		reloadActivityListFromProg(this->srv.get_all_program_srv());

		QMessageBox::information(this, "Info", QString::fromStdString("Activitati adaugate random cu succes in program!"));
	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.get_errors()));
	}
}

void ConsoleGUIProgram::gui_Export() {
	try {
		string fileName = editFile->text().toStdString();

		editFile->clear();

		srv.saveProgramToFile(fileName);
		reloadActivityListFromProg(this->srv.get_all_program_srv());

		QMessageBox::information(this, "Info", QString::fromStdString("Programul a fost adaugat in fisier!"));
	}
	catch (RepoException&) {
		QMessageBox::warning(this, "Warning", QString::fromStdString("Fisierul nu se poate deschide"));
	}
}