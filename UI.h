#pragma once
#include "service.h"

class Console {
private:
	TaskStore& srv;

public:
	Console(ActivitateStore& srv) : srv{ srv } {};

	Console(const Console& ot) = delete;

	void print_meniu();
	void ui_add();
	void ui_delete();
	void ui_modify();
	void ui_find();
	void ui_filter();
	void ui_sort();
	void print_all_activities(vector<Activitate> allActivities);
	void ui_export();
	void ui_undo();

	void ui_adauga_program();
	void ui_adauga_random();
	void ui_goleste_program();
	void print_program();

	void run();
};