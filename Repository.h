#pragma once
#include "Domain.h"
#include <vector>
using std::vector;


class medicamentRepo {

private:
	vector<medicament> medicamentList;
	vector<medicament>retetaList;

public:

	vector<medicament> getAll() {
		return medicamentList;
	}
	vector<medicament> getAll_reteta() {
		return retetaList;
	}
	medicament findmedicament(const string& denumire);

	void addmedicament(const medicament& medicament);

	void deletemedicament(const string& denumire);

	void modifymedicament(const medicament& medicament);

	int length() {
		return int(medicamentList.size());
	}
	int lenght_reteta() {
		return int(retetaList.size());
	}

	virtual void createReteta(const medicament& medicament);
	virtual void deleteReteta();

};

class medicamentRepoFile :public medicamentRepo {
private:
	std::string FileName;
	//void loadFromFile();
	void writeToFile();

public:
	/*
	medicamentRepoFile(std::string FileName) :medicamentRepo(), FileName{ FileName } {
		loadFromFile(); //incarcam datele din fisier
	}*/
	void createReteta(const medicament& m) override {
		medicamentRepo::createReteta(m);//apelam metoda din clasa de baza
		writeToFile();
	}
	void deleteReteta() override {
		medicamentRepo::deleteReteta();
		writeToFile();
	}
};