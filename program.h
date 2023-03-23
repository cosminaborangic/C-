#pragma once
#include "domain.h"
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using std::vector;

/*
Clasa de exceptii a programului
*/
//class ProgException {
//private:
//	std::string errors;
//public:
//	ProgException(std::string errors) : errors{ errors } {};
//	//std::string get_errors()
//	//{
//	//	return this->errors;
//	//} 
//};

class Program {

private:
	vector<Activitate> program;
public:
	Program() = default;

	//adauga o activitate in program
	void adauga_program(const Activitate& a);

	//sterge toate activitatile din program
	void goleste_program();

	//adauga un nr de activitati random
	void adauga_random(vector<Activitate> activities, int n);

	//vectorul cu toate activitatile din program
	const vector<Activitate>& get_all_from_program();

	//verfica daca activitatea este deja in program
	void valideaza_program(const Activitate& a);
};

void teste_program();