#include "Cjt_cites.hh"

Cjt_cites::Cjt_cites() {}
  
Cjt_cites::~Cjt_cites() {}

void Cjt_cites::afegir_cita(string autor1, string titol1, Text subtext, int fraseini, int frasefi){
	vector<string>frases;
	int m = subtext.nombre_frases();
	for(int i = 0; i < m; ++i) frases.push_back(subtext.frase_x(i));
	istringstream iss(autor1);
	string actual;
	string ref;
	while(iss >> actual) {
		ref += actual[0];
	}
	map<string,int>::const_iterator i = indexs.find(ref);;
	if(i != indexs.end()) {
		stringstream stream; 
		int numero = indexs[ref];
		++numero;
		indexs[ref] = numero;
		string reffi;
		stream << numero;
		stream >> reffi;
		ref += reffi; 
	}
	else {
		indexs[ref] = 1;
		ref += "1";
	}
	cjt_cita[ref].autor = autor1;
	cjt_cita[ref].titol = titol1;
	cjt_cita[ref].referencia = ref;
	cjt_cita[ref].fraseinicial = fraseini;
	cjt_cita[ref].frasefinal = frasefi;
	int mida = frases.size();
	for(int s = 0; s < mida; ++s) cjt_cita[ref].contingutfrases.push_back(frases[s]);
}

void Cjt_cites::eliminar_cita(string referencia){
	cjt_cita.erase(referencia);
}

bool Cjt_cites::existeix_cita(string referencia) {
	map<string,Cita>::iterator i = cjt_cita.find(referencia);
	if(i == cjt_cita.end()) return false;
	else return true;
}

bool Cjt_cites::existeix_mateixa_cita(string autor1, string titol1, int numini, int numfi) {
	map<string,Cita>::iterator i = cjt_cita.begin();
	map<string,Cita>::iterator i2 = cjt_cita.end();
	bool trobat = false;
	while(i != i2 and not trobat) {
		if(cjt_cita[i->first].autor == autor1 and cjt_cita[i->first].titol == titol1 and cjt_cita[i->first].fraseinicial == numini and cjt_cita[i->first].frasefinal == numfi) trobat = true;
		++i; 
	}
	return trobat;
}

void Cjt_cites::info_cita(string referencia){
	Cita actual = cjt_cita[referencia];
	cout << actual.autor << " " << actual.titol << endl;
	cout << actual.fraseinicial << "-" << actual.frasefinal << endl;
	int aux = actual.fraseinicial;
	for(int j = 0; j < actual.contingutfrases.size(); ++j) {
			cout << aux << " " << actual.contingutfrases[j] << endl;
			++aux;
	}
}

void Cjt_cites::cites_autor(string autor1) {
	istringstream iss(autor1);
	string actual;
	string autorfinal;
	while(iss >> actual) {
		autorfinal += actual[0];
	}
	int numofpossibles;
	numofpossibles = indexs[autorfinal];
	vector<Cita>veccites;
	for(int i = 1; i <= numofpossibles; ++i) {
		stringstream ss;
		ss << i;
		string refstr;
		refstr = ss.str();
		autorfinal += refstr;
		if(cjt_cita[autorfinal].autor == autor1) {
			veccites.push_back(cjt_cita[autorfinal]);
			autorfinal.erase(autorfinal.length()-1);
		}
		else autorfinal.erase(autorfinal.length()-1);
	}
	for(int s = 0; s < veccites.size(); ++s) {
		cout << veccites[s].referencia << endl;
		int aux = veccites[s].fraseinicial;
		for(int j = 0; j < veccites[s].contingutfrases.size(); ++j) {
			cout << aux << " " << veccites[s].contingutfrases[j] << endl;
			++aux;
		}
		cout << veccites[s].titol << endl;
	}
}

void Cjt_cites::cites_ulttxt(bool cites_sol, string titol1, string autor1){
	istringstream iss(autor1);
	string actual;
	string autorfinal;
	while(iss >> actual) {
		autorfinal += actual[0];
	}
	int numofpossibles = indexs[autorfinal];
	vector<Cita>veccites;
	for(int i = 1; i <= numofpossibles; ++i) {
		stringstream ss;
		ss << i;
		string refstr;
		ss >> refstr;
		if(cjt_cita[autorfinal+refstr].autor ==  autor1 and cjt_cita[autorfinal+refstr].titol == titol1) {
			veccites.push_back(cjt_cita[autorfinal+refstr]);
		}
	}
	for(int s = 0; s < veccites.size(); ++s) {
		cout << veccites[s].referencia << endl;
		for(int j = 0; j < veccites[s].contingutfrases.size(); ++j) {
			cout << veccites[s].fraseinicial << " " << veccites[s].contingutfrases[j] << endl;
			++veccites[s].fraseinicial;
		}
		if(cites_sol) cout << autor1 << " " << titol1 << endl;
	}
	
}

void Cjt_cites::cites_info(string titol1, string autor1){
    istringstream iss(autor1);
    string actual;
    string autorfinal;
    while(iss >> actual) {
        autorfinal += actual[0];
    }
    int numofpossibles = indexs[autorfinal];
    vector<Cita>veccites;
    for(int i = 1; i <= numofpossibles; ++i) {
        stringstream ss;
        ss << i;
        string refstr;
        ss >> refstr;
        if(cjt_cita[autorfinal+refstr].autor ==  autor1 and cjt_cita[autorfinal+refstr].titol == titol1) {
            veccites.push_back(cjt_cita[autorfinal+refstr]);
        }
    }
    int mida = veccites.size();
    for(int s = 0; s < mida; ++s) {
        cout << veccites[s].referencia << endl;
        int aux = veccites[s].fraseinicial;
        int mida2 = veccites[s].contingutfrases.size();
        for(int j = 0; j < mida2; ++j) {
            cout << veccites[s].contingutfrases[j] << endl;
            ++aux;
        }
    }
}

bool Cjt_cites::cita_al_conjunt(string referencia){
	map<string,Cita>::const_iterator i = cjt_cita.find(referencia);
	if(i == cjt_cita.end()){
		return false;
		cjt_cita.erase(referencia);
	}
	else return true;
}

void Cjt_cites::totes_cites(){
	vector<Cita>veccites;
	for(map<string,Cita>::const_iterator i = cjt_cita.begin(); i != cjt_cita.end(); ++i) {
		if(i->second.autor != "") veccites.push_back(i->second);
	}
	for(int s = 0; s < veccites.size(); ++s) {
		cout << veccites[s].referencia << endl;
        int fraseinicial2 = veccites[s].fraseinicial;
		for(int j = 0; j < veccites[s].contingutfrases.size(); ++j) {
			cout << fraseinicial2 << " " << veccites[s].contingutfrases[j] << endl;
			++fraseinicial2;
		}
		cout << veccites[s].autor << " " << veccites[s].titol << endl;
	}
}