#include "Domain.h"
#include "Repository.h"

class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	//destructorul e virtual pentru a ne asigura ca daca dau delete pe un pointer, se apeleleaza destructorul din clasa care trebuie
	virtual ~ActiuneUndo()=default;
};

class UndoAdauga : public ActiuneUndo {
	medicament medAdaugat;
	medicamentRepo& repo;
public:
	UndoAdauga(medicamentRepo& repo, medicament& m) :repo{repo}, medAdaugat{ m } {}
	void doUndo() override {
		repo.deletemedicament(medAdaugat.get_denumire());
	}
};

class UndoSterge : public ActiuneUndo {
	medicament MedSters;
	medicamentRepo& repo;
public:
	UndoSterge(medicamentRepo& repo, medicament& MedSters) :repo{repo}, MedSters{ MedSters } {}
	void doUndo() override {
		repo.addmedicament(MedSters);
	}
};

class UndoModify : public ActiuneUndo {
	medicament oldMed, newMed;
	medicamentRepo& repo;
public:
	UndoModify(medicamentRepo& repo, medicament& oldMed, medicament& newMed) :repo{ repo }, oldMed{ oldMed }, newMed{ newMed } {}
	void doUndo() override {
		repo.deletemedicament(newMed.get_denumire());
		repo.addmedicament(oldMed);
	}
};