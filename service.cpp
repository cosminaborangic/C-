#pragma once
#include "service.h"
#include <assert.h>
#include <functional>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>
using std::sort;

//ACTIVITATI

void ActivitateStore::add_activity(std::string titlu, std::string descriere, std::string tip, double durata) {
	Activitate a{ titlu, descriere, tip, durata };
	val.valideaza(a);
	repo.add(a);
	undoActions.push_back(std::make_unique<UndoAdd>(repo, a));
}

//int ActivitateStore::find_poz(const Activitate& a) {
//	const VectorDinamic<Activitate>& activitati = repo.get_all_activities();
//	for (int i = 0; i < activitati.size(); i++) {
//		if (activitati[i].get_titlu() == a.get_titlu())
//			return i;
//	}
//	return -1;
//}

void ActivitateStore::delete_activity(std::string titlu) {
	Activitate a = repo.find(titlu);
	repo.dell(a);
	undoActions.push_back(std::make_unique<UndoDelete>(repo, a));
}

void ActivitateStore::modify_activity(std::string titlu, std::string descriere, std::string tip, double durata) {
	Activitate a{ titlu, descriere, tip, durata };
	val.valideaza(a);
	undoActions.push_back(std::make_unique<UndoModify>(repo, a, repo.find(titlu)));
	repo.modify(a);
}

Activitate ActivitateStore::find_activity(std::string titlu) {
	Activitate a = repo.find(titlu);
	return a;
}

void ActivitateStore::undo() {
	if (undoActions.empty())
		throw std::exception();

	undoActions.back()->doUndo();
	undoActions.pop_back();
}

//vector<Activitate> ActivitateStore::filter(function<bool(const Activitate&)> fct) {
//	vector<Activitate> filteredActivities;
//	vector<Activitate> lst = repo.get_all_activities();
//	for (int i = 0;i< repo.get_dim();i++) {
//		if (fct(lst[i])) {
//			filteredActivities.push_back(lst[i]);
//		}
//	}
//	return filteredActivities;
//}


vector<Activitate> ActivitateStore::filtrareDescriere(std::string descriere) {
	/*return filter([descriere](const Activitate& a) {
		return a.get_descriere() == descriere;
		});*/
	const vector<Activitate> activities = this->repo.get_all_activities();
	vector<Activitate> filteredActivities;
	std::copy_if(activities.begin(), activities.end(), back_inserter(filteredActivities),
		[descriere](const Activitate& a) {
			return a.get_descriere() == descriere;
		});
	return filteredActivities;
}

vector<Activitate> ActivitateStore::filtrareTip(std::string tip) {
	//return filter([tip](const Activitate& a) {
	//	return a.get_tip() == tip;
	//	});
	const vector<Activitate> activities = this->repo.get_all_activities();
	vector<Activitate> filteredActivitie;
	std::copy_if(activities.begin(), activities.end(), back_inserter(filteredActivitie),
		[tip](const Activitate& a) {
			return a.get_tip() == tip;
		});
	return filteredActivitie;
}

//vector<Activitate> ActivitateStore::sortGenerala(bool(*maiMicF)(const Activitate&, const Activitate&)) {
//	vector<Activitate> v{ repo.get_all_activities() };
//	for (int i = 0; i < v.size(); i++) {
//		for (int j = i + 1; j < v.size(); j++) {
//			if (!maiMicF(v[i], v[j])) {
//				Activitate aux = v[i];
//				v[i] = v[j];
//				v[j] = aux;
//			}
//		}
//	}
//	return v;
//}

vector<Activitate> ActivitateStore::sortareTitlu() {
	vector<Activitate> sortedActivities = repo.get_all_activities();
	sort(sortedActivities.begin(), sortedActivities.end(), cmpTitlu);
	return sortedActivities;
}

vector<Activitate> ActivitateStore::sortareDescriere() {
	vector<Activitate> sortedActivities = repo.get_all_activities();
	sort(sortedActivities.begin(), sortedActivities.end(), cmpDescriere);
	return sortedActivities;
}

vector<Activitate> ActivitateStore::sortareTipDurata() {
	vector<Activitate> sortedActivities = repo.get_all_activities();
	sort(sortedActivities.begin(), sortedActivities.end(), cmpTipDurata);
	return sortedActivities;
}

size_t ActivitateStore::getSizeOfActivities() {
	return repo.get_dim();
}

//PROGRAM

void ActivitateStore::adauga_program_srv(std::string titlu) {
	Activitate a = repo.find(titlu);
	program.valideaza_program(a);
	program.adauga_program(a);
}

size_t ActivitateStore::adauga_random_srv(int n) {
	program.adauga_random(this->repo.get_all_activities(), n);
	return program.get_all_from_program().size();
}

void ActivitateStore::goleste_program_srv() {
	program.goleste_program();
}

const vector<Activitate>& ActivitateStore::get_all_program_srv() {
	return program.get_all_from_program();
}

void ActivitateStore::saveProgramToFile(std::string fileName) {
	std::ofstream out(fileName);
	if (!out.is_open())
		throw RepoException("Fisierul nu se poate deschide!");
	for (auto& activity : get_all_program_srv()) {
		out << activity.get_titlu() << ";" << activity.get_descriere() << ";";
		out << activity.get_tip() << ";" << activity.get_durata() << std::endl;
	}
	out.close();
}

size_t ActivitateStore::getSizeOfProgram() {
	return get_all_program_srv().size();
}

//TESTE PROGRAM

void test_save_to_file_srv() {
	ActivitateRepoFile test_repo{ "test.txt" };
	ActivitateValidator test_val;
	Program program;
	ActivitateStore test_srv{ test_repo, test_val,program };

	test_srv.add_activity("Zilele orasului", "In centrul orasului", "Concert", 72);
	test_srv.adauga_program_srv("Zilele orasului");

	test_srv.saveProgramToFile("test_program.txt");

	std::ifstream in("test_program.txt");
	std::string line;
	while (getline(in, line)) {
		std::string titlu, descriere;
		std::stringstream linestream(line);
		std::string current_item;
		int no = 0;
		while (std::getline(linestream, current_item, ';')) {
			if (no == 0)
				titlu = current_item;
			if (no == 1)
				descriere = current_item;
			no++;
		}
		/*std::cout << titlu <<" "<< descriere;*/
		assert(titlu == "Zilele orasului");
		assert(descriere == "In centrul orasului");
	}
	in.close();

	test_srv.goleste_program_srv();
	test_srv.saveProgramToFile("test_program.txt");

	test_srv.delete_activity("Zilele orasului");
}

void test_adauga_program_srv() {
	ActivitateRepository test_repo;
	ActivitateValidator test_val;
	Program program;
	ActivitateStore test_srv{ test_repo, test_val,program };

	test_srv.add_activity("Zilele orasului", "In centrul orasului", "Concert", 72);
	test_srv.add_activity("Stand-up Micutzu", "Casa de cultura", "Stand-ul comedy", 3);
	test_srv.adauga_program_srv("Zilele orasului");

	//vector<Activitate>v = test_srv.get_all_program_srv();
	assert(test_srv.getSizeOfProgram() == 1);

	test_srv.goleste_program_srv();
	//v = test_srv.get_all_program_srv();
	assert(test_srv.getSizeOfProgram() == 0);
}

void test_adauga_random_srv() {
	ActivitateRepository test_repo;
	ActivitateValidator test_val;
	Program program;
	ActivitateStore test_srv{ test_repo, test_val,program };

	test_srv.add_activity("Zilele orasului", "In centrul orasului", "Concert", 72);
	test_srv.add_activity("Stand-up Micutzu", "Casa de cultura", "Stand-ul comedy", 3);
	test_srv.add_activity("Stand-up", "Casa de cultura", "Stand-ul comedy", 3);

	test_srv.adauga_random_srv(2);
	vector<Activitate>v = test_srv.get_all_program_srv();
	assert(v.size() == 2);

	test_srv.goleste_program_srv();
	v = test_srv.get_all_program_srv();
	assert(v.size() == 0);
}


//TESTE

void test_add_srv() {
	ActivitateRepository test_repo;
	ActivitateValidator test_val;
	Program program;
	ActivitateStore test_srv{ test_repo, test_val,program };

	test_srv.add_activity("Zilele orasului", "In centrul orasului", "Concert", 72);
	test_srv.add_activity("Stand-up Micutzu", "Casa de cultura", "Stand-ul comedy", 3);
	vector<Activitate>v = test_srv.get_all_activities();
	assert(test_srv.getSizeOfActivities() == 2);

	test_srv.undo();
	v = test_srv.get_all_activities();
	assert(v.size() == 1);

	try {
		test_srv.add_activity("Zilele orasului", "In centrul orasului", "Concert", 72);
	}
	catch (RepoException&) {
		assert(true);
	}

	try {
		test_srv.add_activity("", "In centrul orasului", "Concert", 72);
	}
	catch (ValidationException& ve) {
		assert(ve.get_errors() == "Titlul trebuie sa aiba cel putin 2 caractere!\n");
	}

	try {
		test_srv.add_activity("Zilele orasului", "", "Concert", 72);
	}
	catch (ValidationException&) {
		assert(true);
	}

	try {
		test_srv.add_activity("Zilele orasului", "In centru", "", 72);
	}
	catch (ValidationException&) {
		assert(true);
	}

	try {
		test_srv.add_activity("Zilele orasului", "In centru", "Concert", 72.80);
	}
	catch (ValidationException&) {
		assert(true);
	}
}

void test_dell_srv() {
	ActivitateRepository test_repo;
	ActivitateValidator test_val;
	Program program;
	ActivitateStore test_srv{ test_repo, test_val, program };

	test_srv.add_activity("Zilele orasului", "In centrul orasului", "Concert", 72);
	test_srv.add_activity("Stand-up Micutzu", "Casa de cultura", "Stand-ul comedy", 3);

	assert(test_repo.get_dim() == 2);
	test_srv.delete_activity("Zilele orasului");
	assert(test_repo.get_dim() == 1);

	test_srv.delete_activity("Stand-up Micutzu");
	assert(test_repo.get_dim() == 0);

	test_srv.undo();
	assert(test_repo.get_dim() == 1);

	test_srv.undo();
	assert(test_repo.get_dim() == 2);
}

void test_modify_srv() {
	ActivitateRepository test_repo;
	ActivitateValidator test_val;
	Program program;
	ActivitateStore test_srv{ test_repo, test_val, program };

	test_srv.add_activity("Zilele orasului", "In centrul orasului", "Concert", 72);
	test_srv.add_activity("Stand-up Micutzu", "Casa de cultura", "Stand-ul comedy", 3);

	Activitate a1 = test_repo.find("Zilele orasului");
	assert(a1.get_descriere() == "In centrul orasului");
	assert(a1.get_durata() == 72);

	test_srv.modify_activity("Zilele orasului", "In parc", "Muzica", 24);
	Activitate a1_modificat = test_repo.find("Zilele orasului");
	assert(a1_modificat.get_descriere() == "In parc");
	assert(a1_modificat.get_durata() == 24);

	test_srv.undo();
	Activitate a2 = test_repo.find("Zilele orasului");
	assert(a2.get_descriere() == "In centrul orasului");
	assert(a2.get_durata() == 72);
}

void test_find_srv() {
	ActivitateRepository test_repo;
	ActivitateValidator test_val;
	Program program;
	ActivitateStore test_srv{ test_repo, test_val, program };

	test_srv.add_activity("Zilele orasului", "In centrul orasului", "Concert", 72);
	test_srv.add_activity("Stand-up Micutzu", "Casa de cultura", "Stand-ul comedy", 3);

	Activitate a = test_srv.find_activity("Zilele orasului");
	assert(a.get_titlu() == "Zilele orasului");
	assert(a.get_descriere() == "In centrul orasului");
	assert(a.get_tip() == "Concert");
	assert(a.get_durata() == 72);
}


void test_filter_srv() {
	ActivitateRepository test_repo;
	ActivitateValidator test_val;
	Program program;
	ActivitateStore testService{ test_repo,test_val,program };

	testService.add_activity("titlu1", "descriere1", "tip1", 3.42);
	testService.add_activity("titlu2", "descriere2", "tip1", 8.31);
	testService.add_activity("titlu3", "descriere2", "tip3", 5.27);
	testService.add_activity("titlu4", "descriere4", "tip4", 4.52);
	testService.add_activity("titlu5", "descriere5", "tip5", 3.45);
	testService.add_activity("titlu6", "descriere6", "tip6", 3.2);

	vector<Activitate> activitati1 = testService.filtrareDescriere("descriere2");
	assert(activitati1.size() == 2);
	vector<Activitate> activitati2 = testService.filtrareDescriere("descriere0");
	assert(activitati2.size() == 0);


	vector<Activitate> activitati3 = testService.filtrareTip("tip1");
	assert(activitati3[0].get_titlu() == "titlu1");
	assert(activitati3[1].get_titlu() == "titlu2");

}

void test_sort_srv() {
	ActivitateRepository testRepo;
	ActivitateValidator testVal;
	Program program;
	ActivitateStore testService{ testRepo,testVal,program };

	testService.add_activity("Zilele orasului", "In centrul orasului", "Concert", 72);
	testService.add_activity("Stand-up Micutzu", "Casa de cultura", "Stand-up comedy", 3);
	testService.add_activity("Teambuilding", "La cabana", "Teambuilding", 72);
	testService.add_activity("Titlu4", "Descriere4", "Teambuilding", 4.52);

	vector<Activitate> sortedByTitlu = testService.sortareTitlu();
	assert(sortedByTitlu[0].get_titlu() == "Stand-up Micutzu");
	assert(sortedByTitlu[1].get_titlu() == "Teambuilding");
	assert(sortedByTitlu[2].get_titlu() == "Titlu4");
	assert(sortedByTitlu[3].get_titlu() == "Zilele orasului");

	vector<Activitate> sortedByDescriere = testService.sortareDescriere();
	assert(sortedByDescriere[0].get_descriere() == "Casa de cultura");
	assert(sortedByDescriere[2].get_descriere() == "In centrul orasului");

	vector<Activitate> sortedByTipDurata = testService.sortareTipDurata();
	assert(sortedByTipDurata[0].get_tip() == "Concert");
	assert(sortedByTipDurata[0].get_durata() == 72);
	assert(sortedByTipDurata[2].get_tip() == "Teambuilding");
	assert(sortedByTipDurata[2].get_durata() == 4.52);
	assert(sortedByTipDurata[3].get_tip() == "Teambuilding");
	assert(sortedByTipDurata[3].get_durata() == 72);
}

void teste_srv() {
	test_add_srv();
	test_dell_srv();
	test_modify_srv();
	test_find_srv();
	test_filter_srv();
	test_sort_srv();

	test_save_to_file_srv();
	test_adauga_program_srv();
	test_adauga_random_srv();
}