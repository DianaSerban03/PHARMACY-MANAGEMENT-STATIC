#include "Repository.h"
#include "Errors.h"
#include <algorithm>
#include <fstream>

//FUNCTII prelucrare medicamente

void medicamentRepo::addmedicament(const medicament& m) {
	/*for (int i = 0; i < medicamentList.size(); i++) {
		if (medicamentList.at(i).get_denumire() == m.get_denumire()) {
			throw Exception("Already added!\n");
		}
	}*/
	for (const auto m1: getAll()) {
		if (m1.get_denumire() == m.get_denumire()) {
			throw Exception("Already added!\n");
		}
	}
	medicamentList.push_back(medicament(m));
}

void medicamentRepo::deletemedicament(const string& denumire) {
	int i = 0;
	while (i < medicamentList.size() && medicamentList.at(i).get_denumire() != denumire) {
		i++;
	}
	if (i < medicamentList.size()) //medicamentList.erase(i);
	{
		medicamentList.erase(medicamentList.begin()+i);
	}
	else throw Exception("medicament not found!\n");
}

void medicamentRepo::modifymedicament(const medicament& medicament) {
	int i = 0;
	while (i < medicamentList.size() && !(medicamentList.at(i) == medicament)) i++;
	if (i < medicamentList.size()) {
		medicamentList.at(i).set_subst_activ(medicament.get_subst_activ());
		medicamentList.at(i).set_pret(medicament.get_pret());
		medicamentList.at(i).set_producator(medicament.get_producator());
	}
	else throw Exception("medicament not found!\n");
}

medicament medicamentRepo::findmedicament(const string& denumire) {
	for (const auto m : getAll()) {
		if (m.get_denumire() == denumire) return m;
	}
	throw Exception("medicament not found!\n");
}


//Functie pentru lucrul cu fisiere
void medicamentRepoFile::writeToFile() {
	std::ofstream out("reteta.out");
	for (auto& m : getAll_reteta())
	{
		out << m.get_denumire();
		out << " ";
		out << m.get_pret();
		out << " ";
		out << m.get_producator();
		out << " ";
		out << m.get_subst_activ();
		out << std::endl;
	}
	out.close();
}

//Functii pentru reteta de medicamente
void medicamentRepo::createReteta(const medicament& m) {

	for (const auto m1 : getAll_reteta()) {
		if (m1.get_denumire() == m.get_denumire()) {
			throw Exception("Already added!\n");
		}
	}
	retetaList.push_back(medicament(m));
}

void medicamentRepo::deleteReteta()
{
	retetaList.clear();
}
