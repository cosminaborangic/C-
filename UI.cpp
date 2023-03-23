#pragma once
#include "UI.h"
//#include "vector_dinamic.h"
#include <vector>
#include <iostream>

using namespace std;

void Console::print_meniu() {
	cout << "---------------------------------" << endl;
	cout << "Comenzile disponibile sunt:" << endl;
	cout << "1 - Adauga o activitate." << endl;
	cout << "2 - Modifica o activitate." << endl;
	cout << "3 - Sterge o activitate." << endl;
	cout << "4 - Cauta o activitate." << endl;
	cout << "5 - Filtrare activitati." << endl;
	cout << "6 - Sortare activitati." << endl;
	cout << "7 - Adauga activitate in program" << endl;
	cout << "8 - Adauga activitati random in program" << endl;
	cout << "9 - Goleste toate activitate din program" << endl;
	cout << "10 - Export. Salveaza lista de elemente in fisier." << endl;
	cout << "undo - Reface ultima operatie." << endl;
	cout << "print_program - Afiseaza toate activitatile din program." << endl;
	cout << "print - Afiseaza toate activitatile." << endl;
	cout << "exit - Iesi din aplicatie." << endl;
	cout << "---------------------------------" << endl;
}

void Console::ui_add() {
	string titlu, descriere, tip;
	double durata;

	cout << "Introduceti titlul activitatii: ";
	getline(cin >> ws, titlu);
	cout << "Introduceti descrierea activitatii: ";
	getline(cin >> ws, descriere);
	cout << "Introduceti tipul activitatii: ";
	getline(cin >> ws, tip);
	cout << "Introduceti durata activitatii (de tip HH.MM): ";
	cin >> durata;

	try {
		srv.add_activity(titlu, descriere, tip, durata);
	}
	catch (RepoException& re) {
		cout << re.get_errors();
	}
	catch (ValidationException& ve) {
		cout << "Activitatea este invalida!" << endl;
		cout << ve.get_errors();
	}
}

void Console::ui_delete() {
	string titlu;
	cout << "Introduceti titlul activitatii care doriti sa fie stearsa:";
	getline(cin >> ws, titlu);
	try {
		srv.delete_activity(titlu);
		cout << "Activitatea a fost stearsa!" << endl;
	}
	catch (RepoException& re) {
		cout << "Activitatea cu acest titlu nu se gaseste in lista!" << endl;
		cout << re.get_errors();
	}
}

void Console::ui_modify() {
	string titlu, descriere, tip;
	double durata;

	cout << "Introduceti titlul activitatii: ";
	getline(cin >> ws, titlu);
	cout << "Introduceti descrierea activitatii: ";
	getline(cin >> ws, descriere);
	cout << "Introduceti tipul activitatii: ";
	getline(cin >> ws, tip);
	cout << "Introduceti durata activitatii (de tip HH.MM): ";
	cin >> durata;

	try {
		srv.modify_activity(titlu, descriere, tip, durata);
		cout << "Activitatea a fost modificata!" << endl;
	}
	catch (RepoException& re) {
		cout << "Activitatea cu acest titlu nu se gaseste in lista!" << endl;
		cout << re.get_errors();
	}
}

void Console::ui_find() {
	string titlu;
	cout << "Introduceti titlul activitatii: ";
	getline(cin >> ws, titlu);
	try {
		Activitate activity = srv.find_activity(titlu);
		cout << "Activitatea cautata este: ";
		cout << "Titlu: " << activity.get_titlu() << " | Descriere: " << activity.get_descriere() << " | Tip: " << activity.get_tip() << " | Durata: " << activity.get_durata() << endl;
	}
	catch (RepoException& re) {
		cout << "Activitatea cu acest titlu nu se gaseste in lista!" << endl;
		cout << re.get_errors();
	}
}

void Console::ui_filter() {
	cout << "Introduceti criteriu dupa care doriti sa filtrati(descriere/tip):";
	string criteriu;
	cin >> criteriu;

	if (criteriu == "descriere") {
		cout << "Descrierea pentru care sa se afiseze activitatile: ";
		string descriere;
		cin >> descriere;
		if (srv.filtrareDescriere(descriere).size() > 0)
			print_all_activities(srv.filtrareDescriere(descriere));
		else cout << "Nu se gasesc activitati cu aceasta descriere!" << endl;
	}
	else if (criteriu == "tip") {
		cout << "Tipul pentru care sa se afiseze activitatile: ";
		string tip;
		cin >> tip;
		if (srv.filtrareTip(tip).size() > 0)
			print_all_activities(srv.filtrareTip(tip));
		else cout << "Nu se gasesc activitati cu acest tip!" << endl;
	}
	else cout << "Nu exista acest criteriu." << endl;
}

void Console::ui_sort() {
	cout << "Introduceti criteriu dupa care doriti sa sortati(titlu/descriere/tip+durata):";
	string criteriu;
	cin >> criteriu;

	if (criteriu == "titlu")
		print_all_activities(srv.sortareTitlu());
	else if (criteriu == "descriere")
		print_all_activities(srv.sortareDescriere());
	else if (criteriu == "tip+durata")
		print_all_activities(srv.sortareTipDurata());
	else cout << "Nu se poate sorta dupa acest criteriu." << endl;
}

void Console::print_all_activities(vector<Activitate> activities) {
	//const VectorDinamic<Activitate>& activities = srv.get_all_activities();
	if (activities.size() == 0)
		cout << "Nu exista activitati in lista." << endl;
	else
		cout << "Lista de activitati este: " << endl;
	for (const auto activity : activities) {
		cout << "Titlu: " << activity.get_titlu() << " | Descriere: " << activity.get_descriere() << " | Tip: " << activity.get_tip() << " | Durata: " << activity.get_durata() << endl;
	}
}

void Console::ui_undo() {
	try {
		srv.undo();
		cout << "Undo realizat cu succes!" << endl;
	}
	catch (std::exception()) {
		cout << "Nu se mai poate face undo!" << endl;
	}
}

//PROGRAM

void Console::ui_adauga_program() {
	string titlu;
	cout << "Introduceti titlul: ";
	getline(cin >> ws, titlu);
	try {
		this->srv.adauga_program_srv(titlu);
		cout << "Activitatea a fost adaugata in program" << endl;
	}
	catch (RepoException& re) {
		cout << re.get_errors();
	}
	catch (std::exception()) {
		//cout << pe.get_errors();
		cout << "Activitatea se afla deja in program!" << endl;
	}
}

void Console::ui_adauga_random() {
	string n;
	int nr;
	cout << "Introduceti nr de activitati de adaugat: ";
	getline(cin >> ws, n);
	try {
		nr = stoi(n);
		this->srv.adauga_random_srv(nr);
		cout << "Activitatile au fost adaugate cu succes in program!" << endl;
	}
	catch (RepoException& re) {
		cout << re.get_errors();
	}
}

void Console::print_program() {
	print_all_activities(srv.get_all_program_srv());
}

void Console::ui_goleste_program() {
	this->srv.goleste_program_srv();
	cout << "Programul a fost golit!" << endl;
}

void Console::ui_export() {
	cout << "Introduceti numele fisierului:";
	string fileName;
	cin >> fileName;
	try {
		srv.saveProgramToFile(fileName);
		cout << "Programul a fost adaugat in fisier!" << endl;
	}
	catch (RepoException&) {
		cout << "Fisierul nu se poate deschide!" << endl;
	}
}

void Console::run() {
	int ok = 1;
	string cmd;
	print_meniu();
	while (ok) {
		cout << "Introduceti comanda: ";
		getline(cin >> ws, cmd);
		if (cmd == "1") {
			ui_add();
		}
		else if (cmd == "2") {
			ui_modify();
		}
		else if (cmd == "3") {
			ui_delete();
		}
		else if (cmd == "4") {
			ui_find();
		}
		else if (cmd == "5") {
			ui_filter();
		}
		else if (cmd == "6") {
			ui_sort();
		}
		else if (cmd == "7") {
			ui_adauga_program();
		}
		else if (cmd == "8") {
			ui_adauga_random();
		}
		else if (cmd == "9") {
			ui_goleste_program();
		}
		else if (cmd == "10") {
			ui_export();
		}
		else if (cmd == "undo") {
			ui_undo();
		}
		else if (cmd == "print_program") {
			print_program();
		}
		else if (cmd == "print") {
			print_all_activities(srv.get_all_activities());
		}
		else if (cmd == "exit") {
			break;
		}
		else {
			cout << "Comanda indisponibila!" << endl;
		}
		cout << "Lista de activitati contine: " << srv.getSizeOfActivities() << " activitati!" << endl;
		cout << "Programul contine: " << srv.getSizeOfProgram() << " activitati!" << endl;
	}
}