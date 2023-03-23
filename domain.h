#pragma once
#include <string>
#include <iostream>

class Activitate {
private:
	std::string titlu;
	std::string descriere;
	std::string tip;
	double durata;

public:
	Activitate() = delete;
	Activitate(std::string titlu, std::string descriere, std::string tip, double durata) : titlu{ titlu }, descriere{ descriere }, tip{ tip }, durata{ durata }{};

	//constructor
	Activitate(const Activitate& ot) : titlu{ ot.titlu }, descriere{ ot.descriere }, tip{ ot.tip }, durata{ ot.durata }{}

	std::string get_titlu() const;
	std::string get_descriere() const;
	std::string get_tip() const;
	double get_durata() const;

	void set_titlu(std::string titlu_nou);
	void set_descriere(std::string descriere_noua);
	void set_tip(std::string tip_nou);
	void set_durata(double durata_noua);

	bool eq(Activitate a);

	//std::string str();
};

bool cmpTitlu(const Activitate& a1, const Activitate& a2);
bool cmpDescriere(const Activitate& a1, const Activitate& a2);
bool cmpTipDurata(const Activitate& a1, const Activitate& a2);

void teste_domain();