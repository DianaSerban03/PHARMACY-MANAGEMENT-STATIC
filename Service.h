#pragma once
#include "Domain.h"
#include "Repository.h"
#include "Validator.h"
#include <vector>
#include "Undo.h"
using std::unique_ptr; 

 
typedef bool(*Compare)(const medicament&, const string&);
typedef int(*Sort)(const medicament&, const medicament&);

using std::vector;


class medicamentService {

private:
	medicamentRepoFile repo;
	Validator valid;
	std::vector<ActiuneUndo*>undoActions;

public:

	medicamentService(const medicamentRepoFile& repo, const Validator& valid) : repo{ repo }, valid{ valid } {

	}
	~medicamentService();
	vector<medicament> getAll();
	vector<medicament> getAll_reteta();

	void undo();

	void addmedicament(const string& denumire, const int& pret, const string& producator, const string& subst_activ);

	void modifymedicament(const string& denumire, const int& pret, const string& producator, const string& subst_activ);

	medicament findmedicament(const string& denumire);

	void deletemedicament(const string& denumire);

	vector<medicament> filtermedicaments(const string& filterParameter, Compare function, int i);

	vector<medicament> sortmedicaments(Sort sortFunction, int i);

	void createReteta(const string& denumire);
	void deleteReteta();
};