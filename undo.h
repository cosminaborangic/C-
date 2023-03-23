#pragma once
//#include "domain.h"
#include "repository.h"

class ActiuneUndo {
public:
	virtual void doUndo() = 0;

	virtual ~ActiuneUndo() = default;
};

class UndoAdd : public ActiuneUndo {
	Activitate activity;
	ActivitateRepository& repo;
public:
	UndoAdd(ActivitateRepository& repo, const Activitate& a) : repo{ repo }, activity{ a }{}

	void doUndo() override {
		repo.dell(activity);
	}

};

class UndoDelete : public ActiuneUndo {
	Activitate activity;
	ActivitateRepository& repo;
public:
	UndoDelete(ActivitateRepository& repo, const Activitate& a) : repo{ repo }, activity{ a }{};

	void doUndo() override {
		repo.add(activity);
	}
};

class UndoModify : public ActiuneUndo {
	Activitate a1, a2;
	ActivitateRepository& repo;

public:
	UndoModify(ActivitateRepository& repo, const Activitate& noua, const Activitate& veche) :repo{ repo }, a1{ noua }, a2{ veche }{};

	void doUndo() override {
		repo.dell(a1);
		repo.add(a2);
	}
};

