#include "domain.h"
#include <string>
#include <assert.h>

std::string Activitate::get_titlu() const {
	return this->titlu;
}

std::string Activitate::get_descriere() const {
	return this->descriere;
}

std::string Activitate::get_tip() const {
	return this->tip;
}

double Activitate::get_durata() const {
	return this->durata;
}

void Activitate::set_titlu(std::string titlu_nou) {
	this->titlu = titlu_nou;
}

void Activitate::set_descriere(std::string descriere_noua) {
	this->descriere = descriere_noua;
}

void Activitate::set_tip(std::string tip_nou) {
	this->tip = tip_nou;
}

void Activitate::set_durata(double durata_noua) {
	this->durata = durata_noua;
}

bool Activitate::eq(Activitate a) {
	if (this->titlu == a.get_titlu() && this->descriere == a.get_descriere() && this->tip == a.get_tip() && this->durata == a.get_durata())
		return true;
	return false;
}

bool cmpTitlu(const Activitate& a1, const Activitate& a2) {
	return a1.get_titlu() < a2.get_titlu();
}

bool cmpDescriere(const Activitate& a1, const Activitate& a2) {
	return a1.get_descriere() < a2.get_descriere();
}

bool cmpTipDurata(const Activitate& a1, const Activitate& a2) {
	if (a1.get_tip() == a2.get_tip())
		return a1.get_durata() < a2.get_durata();
	else return a1.get_tip() < a2.get_tip();
}

//std::string Activitate::str() {
//	//std::string durata = to_string(this->durata);
//	return "Titlu: " + this->titlu + " Descriere: " + this->descriere + " Tip: " + this->tip + " Durata: " + durata;
//}

//Teste

void test_get_set() {
	Activitate activity1{ "Zilele orasului", "In centrul orasului", "Concert", 72 };
	assert(activity1.get_titlu() == "Zilele orasului");
	assert(activity1.get_descriere() == "In centrul orasului");
	assert(activity1.get_tip() == "Concert");
	assert(activity1.get_durata() == 72);

	Activitate activity2{ "Stand-up Micutzu", "Casa de cultura", "Stand-up comedy", 3 };
	assert(activity2.get_titlu() == "Stand-up Micutzu");
	assert(activity2.get_descriere() == "Casa de cultura");
	assert(activity2.get_tip() == "Stand-up comedy");
	assert(activity2.get_durata() == 3);

	activity1.set_titlu("Stand-up Micutzu");
	activity1.set_descriere("Casa de cultura");
	activity1.set_tip("Stand-up comedy");
	activity1.set_durata(3);

	Activitate activity3{ "Stand-up Micutzu", "Casa de cultura", "Stand-up comedy", 3 };
	assert(activity3.get_titlu() == "Stand-up Micutzu");
	assert(activity3.get_descriere() == "Casa de cultura");
	assert(activity3.get_tip() == "Stand-up comedy");
	assert(activity3.get_durata() == 3);
}

void teste_domain() {
	test_get_set();
}

