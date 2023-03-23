#include "program.h"
#include <assert.h>
#include <exception>
#include "repository.h"

using std::shuffle;

void Program::valideaza_program(const Activitate& a) {
	vector<Activitate> activities = this->program;
	std::string titlu = a.get_titlu();
	if (std::any_of(activities.begin(), activities.end(),
		[&](Activitate& activitate) {return activitate.get_titlu() == titlu; }))
		throw std::exception();
}

void Program::adauga_program(const Activitate& a) {
	this->program.push_back(a);
}

void Program::goleste_program() {
	this->program.clear();
}

void Program::adauga_random(vector<Activitate> activities, int n) {
	shuffle(activities.begin(), activities.end(), std::default_random_engine(std::random_device{}()));
	size_t init_size = program.size();
	while (program.size() < n + init_size && activities.size() > 0) {
		program.push_back(activities.back());
		activities.pop_back();
	}
}

const vector<Activitate>& Program::get_all_from_program() {
	return this->program;
}


void test_adauga_program() {
	Program program;
	Activitate activity1{ "Zilele orasului", "In centrul orasului", "Concert", 72 };
	program.adauga_program(activity1);
	assert(program.get_all_from_program().size() == 1);

	Activitate activity2{ "Stand-up Micutzu", "Casa de cultura", "Stand-ul comedy", 3 };
	//try {
	//	program.adauga_program(activity2);
	//}
	//catch (ProgException& ve) {
	//	std::cout << ve.get_errors();
	//	assert(ve.get_errors() == "");
	//}
	program.adauga_program(activity2);
	assert(program.get_all_from_program().size() == 2);

	try {
		program.adauga_program(activity2);
	}
	catch (std::exception) {
		assert(false);
	}

	program.goleste_program();
	assert(program.get_all_from_program().size() == 0);
}


void test_adauga_random() {
	Program program;
	ActivitateRepository repo;
	Activitate activity1{ "Zilele orasului", "In centrul orasului", "Concert", 72 };
	repo.add(activity1);

	Activitate activity2{ "Stand-up Micutzu", "Casa de cultura", "Stand-ul comedy", 3 };
	repo.add(activity2);

	Activitate activity3{ "Zilele", "In parc", "Muzica", 24 };
	repo.add(activity3);

	vector<Activitate> activities;

	program.adauga_random(activities, 2);
	assert(program.get_all_from_program().size() == 0);

	program.goleste_program();
	assert(program.get_all_from_program().size() == 0);
}

void teste_program() {
	test_adauga_program();
	test_adauga_random();
}

