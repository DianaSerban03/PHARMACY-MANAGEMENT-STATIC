#include "Service.h"
#include "Errors.h"
#include <algorithm>

vector<medicament> medicamentService::getAll() {
	return repo.getAll();
}
vector<medicament> medicamentService::getAll_reteta() {
	return repo.getAll_reteta();
}

void medicamentService::undo() {
	if (undoActions.empty()) {
		throw Exception{ "Nu mai exista operatii" };
	}

	ActiuneUndo* act = undoActions.back();
	act->doUndo();
	undoActions.pop_back();
	delete act;
}

medicamentService::~medicamentService() {

}

void medicamentService::addmedicament(const string& denumire, const int& pret, const string& producator, const string& subst_activ) {
	valid.validateData(denumire, pret, producator, subst_activ);
	medicament newmedicament{ denumire, pret, producator, subst_activ };
	repo.addmedicament(newmedicament);
	//undoActions.push_back(std::make_unique<UndoAdauga>( repo, newmedicament ));
	undoActions.push_back(new UndoAdauga{ repo, newmedicament });
}


void medicamentService::modifymedicament(const string& denumire, const int& pret, const string& producator, const string& subst_activ) {
	medicament oldMed = repo.findmedicament(denumire);
	valid.validateData(denumire, pret, producator, subst_activ);
	medicament modifiedmedicament{ denumire, pret, producator, subst_activ };
	repo.modifymedicament(modifiedmedicament);
	undoActions.push_back(new UndoModify{ repo, oldMed, modifiedmedicament });
}

medicament medicamentService::findmedicament(const string& denumire) {
	valid.validateData(denumire, 1, "a", "a");
	return repo.findmedicament(denumire);
}

void medicamentService::deletemedicament(const string& denumire) {
	int validpret = 1;
	string validdenumire = "A";
	string validproducator = "T";
	valid.validateData(denumire, validpret, validproducator, validdenumire);
	medicament medSters = repo.findmedicament(denumire);
	repo.deletemedicament(denumire);
	undoActions.push_back(new UndoSterge{ repo, medSters });
}

vector<medicament> medicamentService::filtermedicaments(const string& filterParameter, Compare function, int i) {
	vector <medicament> result;
	if (i==1)
	{
		vector <medicament> list = repo.getAll();
		for (const auto m : list) {
			medicament currentD;
			currentD.set_pret(m.get_pret());
			currentD.set_denumire(m.get_denumire());
			currentD.set_producator(m.get_producator());
			currentD.set_subst_activ(m.get_subst_activ());
			if (function(currentD, filterParameter)) result.push_back(currentD);
		}
	}
	else
	{
		//vector<medicament> l;
		vector<medicament> sursa = repo.getAll();
		copy_if(sursa.begin(), sursa.end(), std::back_inserter(result), [&filterParameter](const medicament& e) {return e.get_subst_activ() == filterParameter; });
		//return l;
	}
	return result;
}

/*
* Used for sorting
*
bool sortBydenumire(medicament d1, medicament d2) {
	return d1.get_denumire().compare(d2.get_denumire());
}

bool sortBypret(medicament d1, medicament d2) {
	return d1.get_pret() > d2.get_pret();
}

 sortBysubst_activAndproducator(medicament d1, medicament d2) {
	if (d1.get_subst_activ().compare(d2.get_subst_activ()) == 0) {
		return (d1.get_producator().compare(d2.get_producator()));
	}
	else {
		return d1.get_subst_activ().compare(d2.get_subst_activ());
	}
}
*/
vector <medicament> medicamentService::sortmedicaments(Sort sortFunction, int i) {
	vector <medicament> result;
	vector<medicament> list = repo.getAll();
	/*if (i == 1 || i == 3)
	{ 
	 sort(list.begin(), list.end(), [&sortFunction](medicament e1, medicament e2) {return sortFunction(e1, e2); }); 
	}*/
	//else
	{
		if (i == 2 || i == 1 || i == 3)
		{
			for (const auto m : list) {
				result.push_back(medicament(m));
			}
			bool sorted = false;
			while (!sorted) {
				sorted = true;
				for (int i = 0; i < result.size() - 1; i++) {
					if (sortFunction(result.at(i), result.at(i + 1)) > 0) {
						//result.exchange(i, i + 1);
						{
							swap(result.at(i), result.at(i + 1));
						}
						sorted = false;
					}
				}
			}
		}
	}
	
	return result;
}

void medicamentService::createReteta(const string& denumire) {
	
	auto m=repo.findmedicament(denumire);
	repo.createReteta(m);
}
void medicamentService::deleteReteta()
{
	repo.deleteReteta();
}