#pragma once
#include "repository.h"
#include "validators.h"
#include "program.h"
#include "undo.h"
#include <functional>
#include <vector>
using std::function;
using std::vector;

//class SrvException {
//private:
//	std::string errors;
//public:
//	SrvException(std::string) :errors{ errors } {};
//	std::string get_errors() {
//		return this->errors;
//	}
//};


class ActivitateStore {
private:
	ActivitateRepository& repo;
	ActivitateValidator& val;
	Program& program;

	//aici avem lista cu actiunile undo
	vector<unique_ptr<ActiuneUndo>> undoActions;

	//vector<Activitate> filter(function<bool(const Activitate&)> fct);

	//vector<Activitate> sortGenerala(bool(*maiMicF)(const Activitate&, const Activitate&));

public:
	ActivitateStore(ActivitateRepository& activitate_repo, ActivitateValidator& val, Program& prog) : repo{ activitate_repo }, val{ val }, program{ prog }{};

	ActivitateStore(const ActivitateStore& ot) = delete;

	void add_activity(std::string titlu, std::string descriere, std::string tip, double durata);

	//int find_poz(const Activitate& a);

	void delete_activity(std::string titlu);

	void modify_activity(std::string titlu, std::string descriere, std::string tip, double durata);

	Activitate find_activity(std::string titlu);

	vector<Activitate> filtrareDescriere(std::string descriere);

	vector<Activitate> filtrareTip(std::string tip);

	vector<Activitate> sortareTitlu();

	vector<Activitate> sortareDescriere();

	vector<Activitate> sortareTipDurata();

	const vector<Activitate>& get_all_activities() {
		return this->repo.get_all_activities();
	}

	size_t getSizeOfActivities();

	void undo();

	//	PROGRAM

	//adauga o activitate cu titlu titlu si descrierea descriere in program
	void adauga_program_srv(std::string titlu);

	//adauga un numar random de activitati in program
	size_t adauga_random_srv(int n);

	//sterge toate activitatile din program
	void goleste_program_srv();

	//vector cu toate activitatile din program
	const vector<Activitate>& get_all_program_srv();

	//functia salveaza programul intr-un fisier
	void saveProgramToFile(std::string filename);

	//returneaza dimensiunea programului
	size_t getSizeOfProgram();

	//incarca programul din fisier
	vector<Activitate> loadProgramFromFile(std::string filename);

};

void teste_srv();