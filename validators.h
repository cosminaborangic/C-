#pragma once

#include "domain.h"
#include <assert.h>
//#include "vector_dinamic.h"
#include <vector>
#include <string>

using std::vector;



class ValidationException {
	vector<std::string> errors;

public:
	ValidationException(vector<std::string> errors_msg) : errors{ errors_msg } {};

	std::string get_errors() {
		std::string full_msg = "";
		for (int i = 0; i < errors.size(); i++) {
			full_msg += errors[i] + "\n";
		}
		return full_msg;
	}
};

class ActivitateValidator {
public:
	void valideaza(const Activitate& a) {
		vector<std::string> errors;
		if (a.get_titlu().length() < 2)
			errors.push_back("Titlul trebuie sa aiba cel putin 2 caractere!");
		if (a.get_descriere().length() < 2)
			errors.push_back("Descrierea trebuie sa aiba cel putin 2 caractere!");
		if (a.get_tip().length() < 2)
			errors.push_back("Tipul trebuie sa aiba cel putin 2 caractere!");
		if (a.get_durata() - static_cast<int>(a.get_durata()) > 0.59)
			errors.push_back("Formatul duratei este HH.MM. Numarul de minute trebuie sa fie mai mic sau egal cu 59!");

		if (errors.size() > 0)
			throw ValidationException(errors);
	}
};
