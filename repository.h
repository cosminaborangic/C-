#pragma once
#include "domain.h"
//#include "vector_dinamic.h"
#include <vector>


using std::vector;
using std::unique_ptr;

/*
Clasa de exceptii a repozitoriului
*/
class RepoException {
private:
	std::string errors;
public:
	RepoException(std::string) :errors{ errors } {};
	std::string get_errors() {
		return this->errors;
	}
};

/*
Clasa repo a activitatii.
*/
class ActivitateRepository {
private:
	vector<Activitate> lista_activitati;

public:

	ActivitateRepository() {
		vector<Activitate> lst;
		lista_activitati = lst;
	}

	//nu se poate face copie
	ActivitateRepository(const ActivitateRepository& ot) = delete;

	//functia care adauga o activitate
	virtual void add(const Activitate& a);

	//functia care sterge o activitate
	virtual void dell(Activitate& a);

	//functia modifica o activitate
	virtual void modify(Activitate& a);

	//functia care returneaza lista de activitati
	virtual const vector<Activitate>& get_all_activities();

	//functia care cauta o activitate dupa titlu
	const Activitate& find(std::string titlu);

	//functia care returneaza dimensiunea listei de activitati
	size_t get_dim();

	//functia care verifica daca o activitate exista sau nu in lista
	bool exists(const Activitate& a);
};

class ActivitateRepoFile :public ActivitateRepository {
private:
	std::string fileName;

	//Ia activitatile din fisier
	void loadFromFile();

	//Salveaza lista curenta de activitati in fisier.
	void saveToFile();

public:
	ActivitateRepoFile(std::string fileName) :ActivitateRepository(), fileName{ fileName }{
		loadFromFile(); //incarca datele din fisier
	}

	void add(const Activitate& a) override;

	void dell(Activitate& a) override;

	void modify(Activitate& a) override;

};

void teste_repo();
void test_resize();