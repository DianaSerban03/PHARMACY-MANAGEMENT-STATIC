#pragma warning(disable : 4996)
#include "Console.h"
#include "Errors.h"
#include <iostream>
#include <random>
#include <algorithm>
#include <stdlib.h>
#include <cstring>
#include <fstream>

//Lambda functions
int sortBydenumire(const medicament& d1, const medicament& d2) {
	return d1.get_denumire().compare(d2.get_denumire());
}

int sortBypret(const medicament& d1, const medicament& d2) {
	return d1.get_pret() > d2.get_pret();
}

int sortBysubst_activAndproducator(const medicament& d1, const medicament& d2) {
	if (d1.get_subst_activ().compare(d2.get_subst_activ()) == 0) {
		return (d1.get_producator().compare(d2.get_producator()));
	}
	else {
		return d1.get_subst_activ().compare(d2.get_subst_activ());
	}
}

bool Equalpret(const medicament& medicament, const string& pret) {
	return to_string(medicament.get_pret()) == pret;
}

bool Equalsubst_activs(const medicament& medicament, const string& subst_activ) {
	return medicament.get_subst_activ() == subst_activ;
}

string toString(const medicament& m) {
	string text;
	text.append("Denumire: ");
	text.append(m.get_denumire());
	text.append(" | Pret: ");
	text.append(to_string(m.get_pret()));
	text.append(" | Producator: ");
	text.append(m.get_producator());
	text.append(" | Substanta activa: ");
	text.append(m.get_subst_activ());
	return text;
}

void printList(vector <medicament> list) {
	if (list.size() == 0) std::cout << "Empty!\n";
	else {
		for (int i = 0; i < list.size(); i++) {
			std::cout << toString(list.at(i)) << endl;
		}
	}
	std::cout << endl;
}

void UI::UI_printOptions() const {
	std::cout << "\n";
	std::cout << "Console menu\n";
	std::cout << "1. Add medicament\n";
	std::cout << "2. Modify medicament\n";
	std::cout << "3. Delete medicament\n";
	std::cout << "4. Search medicament\n";
	std::cout << "5. Filter medicaments\n";
	std::cout << "6. Sort medicaments\n";
	std::cout << "7. Print data\n";
	std::cout << "8. Creeaza reteta\n";
	std::cout << "9. Sterge reteta\n";
	std::cout << "10. Random reteta\n";
	std::cout << "11. Cerinte generate in avans\n";
	std::cout << "12. Undo\n";
	std::cout << "0. Exit\n";
	std::cout << "\n";
}

void UI::UI_addmedicament() {
	string denumire, producator, subst_activ, pret;
	std::cout << "denumire: ";
	std::cin >> denumire;
	std::cout << "pret: ";
	std::cin >> pret;
	std::cout << "producator: ";
	std::cin >> producator;
	std::cout << "subst_activ: ";
	std::cin >> subst_activ; 
	int p;
	try 
	{
		 p = stoi(pret);
	}
	catch(...)
	{
		std::cout << "Valoare invalida";
	}
	try {
		service.addmedicament(denumire, p, producator, subst_activ);
		std::cout << "Added!\n";
	}
	catch (Exception ex) {
		std::cout << ex.getMessage() << endl;
	}
}

void UI::UI_modifymedicament() {
	string denumire, producator, subst_activ;
	int pret;
	std::cout << "denumire: ";
	std::cin >> denumire;
	std::cout << "New pret: ";
	std::cin >> pret;
	std::cout << "New producator: ";
	std::cin >> producator;
	std::cout << "New subst_activ: ";
	std::cin >> subst_activ;
	try {
		service.modifymedicament(denumire, pret, producator, subst_activ);
		std::cout << "Modified!\n";
	}
	catch (Exception ex) {
		std::cout << ex.getMessage() << endl;
	}
}

void UI::UI_deletemedicament() {
	string denumire;
	std::cout << "denumire: ";
	std::cin >> denumire;
	try {
		service.deletemedicament(denumire);
		std::cout << "Deleted!\n";
	}
	catch (Exception ex) {
		std::cout << ex.getMessage() << endl;
	}
}

void UI::UI_searchmedicament() {
	string denumire;
	std::cout << "denumire: ";
	std::cin >> denumire;
	try {
		medicament found = service.findmedicament(denumire);
		std::cout << toString(found) << endl;
	}
	catch (Exception ex) {
		std::cout << ex.getMessage() << endl;
	}
}

void UI::UI_filtermedicaments() {
	std::cout << "Filter by:\n1.pret\n2.subst_activ\n>>> ";
	string command;
	cin >> command;
	if (command == "1") {
		string pret;
		int i=1;
		cout << "Pret: ";
		cin >> pret;
		auto list = service.filtermedicaments(pret, Equalpret, i);
		printList(list);
	}
	else if (command == "2") {
		string subst_activ;
		int i = 2;
		cout << "subst_activ: ";
		cin >> subst_activ;
		auto list = service.filtermedicaments(subst_activ, Equalsubst_activs, i);
		printList(list);
	}
	else {
		std::cout << "Invalid command!\n";
	}
}

void UI::UI_sortmedicaments() {
	std::cout << "Sort by:\n1.Denumire\n2.Pret\n3.subst_activ+producator\n>>> ";
	string command;
	std::cin >> command;
	if (command == "1") {
		int i = 1;
		auto list = service.sortmedicaments(sortBydenumire, i);
		printList(list);
	}
	else if (command == "2") {
		int i = 2;
		auto list = service.sortmedicaments(sortBypret, 2);
		printList(list);
	}
	else if (command == "3") {
		int i = 3;
		auto list = service.sortmedicaments(sortBysubst_activAndproducator, 3);
		printList(list);
	}
	else {
		std::cout << "Invalid command!\n";
	}
}

void UI::UI_printData() {
	auto list = service.getAll();
	for (int i = 0; i < list.size(); i++) {
		std::cout << toString(list.at(i)) << endl;
	}
}

void UI::UI_createReteta()
{
	std::cout << "Cate medicamente doriti sa contina reteta?  ";
	int n;
	string denumire;
	std::cin >> n;
	std::cout << "Scrieti denumirile medicamentelor pe care doriti sa le adaugati: ";
	try {
		for (int i = 1; i <= n; i++)
		{
			std::cin >> denumire;
			service.createReteta(denumire);
		}
		std::cout << "Created!\n";
		std::cout << "Reteta medicamente: \n";
		auto list = service.getAll_reteta();
		for (int i = 0; i < list.size(); i++) {
			std::cout << toString(list.at(i)) << endl;
		}
	}
	catch (Exception ex) {
		std::cout << ex.getMessage() << endl;
	}
}

void UI::UI_deleteReteta() {
	try {
		service.deleteReteta();
		std::cout << "Deleted!\n";
		std::cout << "Reteta medicamente: \n";
		auto list = service.getAll_reteta();
		for (int i = 0; i < list.size(); i++) {
			std::cout << toString(list.at(i)) << "Medicament sters"<<endl;
		}
	}
	catch (Exception ex) {
		std::cout << ex.getMessage() << endl;
	}
}

void UI::UI_randomReteta()
{
	//Functia genereaza aleatoriu reteta cu medicamente 
	using std::shuffle;
	std::cout << "Cate medicamente doriti sa contina reteta?  ";
	int n;
	std::cin >> n;
	auto list = service.getAll_reteta();
	auto list_meds = service.getAll();
	shuffle(list_meds.begin(), list_meds.end(), std::default_random_engine(std::random_device{}()));
	while (list.size() < n && list_meds.size() > 0) {
		list.push_back(list_meds.back());
		list_meds.pop_back();
	}
		std::cout << "Created!\n";
		std::cout << "Reteta medicamente: \n";
		for (int i = 0; i < list.size(); i++) {
			std::cout << toString(list.at(i)) << endl;
		}
	
}

void UI::UI_comenzi_vect(std::string filename)
{
	//Functie implementata pentru cerinta laborator
	//Functia preia comenzi dintr-un fisier si le executa
	std::string line, cmd;
	std::ifstream fin("text.txt");
	const std::string del= " ";
	while (fin >> cmd)
	{
		if (cmd == "print")
		{
			UI_printData();
		}
		else {
			std::getline(fin, line);
			line.erase(0, 1);
			std::vector <std::string> v;
			std::string token = line.substr(0, line.find(del));
			size_t pos = 0;
			while ((pos = line.find(del)) != std::string::npos)
			{
				token = line.substr(0, pos);
				v.push_back(token);
				line.erase(0, pos + del.length());
			}
			if (line != "")
				v.push_back(line);
			if (cmd == "add") {
				
				try {
					service.addmedicament(v[0], stoi(v[1]), v[2], v[3]);
					std::cout << "Added!\n";
				}
				catch (Exception ex) {
					std::cout << ex.getMessage() << endl;
				}
			}
			if (cmd == "delete") {
				try {
					service.deletemedicament(v[0]);
					std::cout << "Deleted!\n";
				}
				catch (Exception ex) {
					std::cout << ex.getMessage() << endl;
				}
			}
			if (cmd == "modify") {
				try {
					service.modifymedicament(v[0], stoi(v[1]), v[2], v[3]);
					std::cout << "Modified!\n";
				}
				catch (Exception ex) {
					std::cout << ex.getMessage() << endl;
				}
			}
		}
	}

}

void UI::runApplication() {
	bool runProgram = true;
	string command;
	service.deleteReteta();
	while (runProgram) {
		UI_printOptions();
		std::cout << ">>>";
		std::cin >> command;
		if (command == "0") {
			std::cout << "Program ended!\n";
			runProgram = false;
		}
		else if (command == "1") {
			UI_addmedicament();
		}
		else if (command == "2") {
			UI_modifymedicament();
		}
		else if (command == "3") {
			UI_deletemedicament();
		}
		else if (command == "4") {
			UI_searchmedicament();
		}
		else if (command == "5") {
			UI_filtermedicaments();
		}
		else if (command == "6") {
			UI_sortmedicaments();
		}
		else if (command == "7") {
			UI_printData();
		}
		else if (command == "8") {
			UI_createReteta();
		}
		else if (command == "9") {
			UI_deleteReteta();
		}
		else if (command == "10") {
			UI_randomReteta();
		}
		else if (command == "11") {
			UI_comenzi_vect("text.txt");
		}
		else if (command == "12") {
			service.undo();
		}
		else {
			std::cout << "Invalid command!\n";
		}

	}
}