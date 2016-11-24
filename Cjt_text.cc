#include "Cjt_text.hh"

Cjt_Text::Cjt_Text(){
  textriat = false;
}

Cjt_Text::~Cjt_Text(){}

bool Cjt_Text::text_al_conjunt(string autor1, string titol1){
    if(cjt_textos.begin() == cjt_textos.end()) return false;
    else {
        map<string, map<string, Text> >::iterator i = cjt_textos.find(autor1);
        if(i != cjt_textos.end()) {
            map<string, Text>::iterator i2 = cjt_textos[i->first].find(titol1);
            if(i == cjt_textos.end() or i2 == cjt_textos[i->first].end()) return false;
            else return true;
        }
        else return false;
    }
}

void Cjt_Text::afegir_text(string titol1, string autor1, bool& error)
{
    string text;
    string fraseactual;
    int numfrase = 0;
    string actual;
    getline(cin,text);
    error = text_al_conjunt(autor1,titol1);
    if(text == "****" and not error){
        cjt_textos[autor1][titol1].afegir_buit(autor1,titol1);
    }
    while(text != "****") {
        istringstream iss(text);
        while(iss >> actual) {
            if(actual == "." or actual == "," or actual == ":" or actual == ";" or actual == "!" or actual == "?") fraseactual += actual;
            else fraseactual += " " + actual;
            if(actual[actual.length()-1] == '.' or actual[actual.length()-1] == '?' or actual[actual.length()-1] == '!') {
                if(fraseactual[0] == ' ') fraseactual.erase(0,1);
                if(not error) {
                    cjt_textos[autor1][titol1].afegir_frase(fraseactual);
                    cjt_textos[autor1][titol1].afegir_per_frase(fraseactual,autor1,titol1,numfrase);
                    fraseactual.erase(0);
                    ++numfrase;
                }
            }
        }
        getline(cin,text);
    }
}

void Cjt_Text::triar_text(string comanda)
{
    istringstream iss(comanda);
    string actual;
    map<string, map<string,int> >possibles_textos;
    int totalparaules = 0;
    while(iss >> actual) {
        ++totalparaules;
    }
    istringstream iss2(comanda);
    while(iss2 >> actual) {
        for(map<string, map<string, Text> >::iterator iautors = cjt_textos.begin(); iautors != cjt_textos.end(); ++iautors) {
            for(map<string, Text>::iterator ititols = cjt_textos[iautors->first].begin(); ititols != cjt_textos[iautors->first].end(); ++ititols) {
                if(cjt_textos[iautors->first][ititols->first].informacio_text_paraula(actual)){
                    ++possibles_textos[iautors->first][ititols->first];
                }
            }
        }
    }
    int numpossibles = 0;
    for(map<string, map<string, Text> >::iterator iautors2 = cjt_textos.begin(); iautors2 != cjt_textos.end(); ++iautors2) {
        for(map<string, Text>::iterator ititols2 = cjt_textos[iautors2->first].begin(); ititols2 != cjt_textos[iautors2->first].end(); ++ititols2) {
            if(possibles_textos[iautors2->first][ititols2->first] == totalparaules) {
                ulttxtautor = iautors2->first;
                ulttxttitol = ititols2->first;
                ++numpossibles;
            }
        }
    }
    if(numpossibles != 1) {
        cout << "error" << endl;
        textriat = false;
    }
    else textriat = true;
    
}

void Cjt_Text::substituex_en_text(string p1, string p2)
{
    cjt_textos[ulttxtautor][ulttxttitol].substitueix_contingut(p1,p2);
}

void Cjt_Text::info_afegir_cita(string& aut1, string& tit1, Text& subtext, int x, int y)
{
	aut1 = ulttxtautor;
	tit1 = ulttxttitol;
    for(int i = x - 1; i < y; ++i){
        subtext.afegir_frase(cjt_textos[ulttxtautor][ulttxttitol].frase_x(i));
    }
}

void Cjt_Text::info_texttriat(string& aut, string& tit)
{
    aut = ulttxtautor;
    tit = ulttxttitol;
}

void Cjt_Text::eliminar_text()
{
    map<string,Text>::iterator i2;
    i2 = cjt_textos[ulttxtautor].find(ulttxttitol);
    cjt_textos[ulttxtautor].erase(i2);
    map<string, map<string, Text> >::iterator i = cjt_textos.find(ulttxtautor);
    if(i->second.begin() == i->second.end()) cjt_textos.erase(i);
    textriat = false;
}

void Cjt_Text::textos_per_autor(string autor1)
{
    vector<string>titols;
    map<string,map<string,Text> >::iterator i = cjt_textos.find(autor1);    
    for(map<string,Text>::iterator i2 = i->second.begin(); i2 != i->second.end(); ++i2) {
        cout << i2->first << endl;
    }
}

void Cjt_Text::tots_textos()
{
    for(map<string,map<string,Text> >::iterator i = cjt_textos.begin(); i != cjt_textos.end(); ++i) {
        for(map<string,Text>::iterator i2 = i->second.begin(); i2 != i->second.end(); ++i2) {
            cout << i->first << " " << i2->first << endl;
        }
    }
}

void Cjt_Text::tots_autors()
{
  map<string,map<string,Text> >::iterator i = cjt_textos.begin(); 
  map<string, Text>::iterator i2;
  int counttextos,countfrases,countparaules;
  while(i != cjt_textos.end()){
        cout << i->first << " ";
        counttextos = countfrases = countparaules = 0;
        i2 = cjt_textos[i->first].begin();
        while(i2 != cjt_textos[i->first].end()) {
            ++counttextos;
            countfrases += cjt_textos[i->first][i2->first].nombre_frases();
            countparaules += cjt_textos[i->first][i2->first].nombre_paraules();
            ++i2;
        }
        cout << counttextos << " " << countfrases << " " << countparaules << endl;
        ++i;
  }
}

int Cjt_Text::nombre_frases_textos()
{
    return cjt_textos[ulttxtautor][ulttxttitol].nombre_frases();
}

int Cjt_Text::nombre_paraules_textos()
{
   return cjt_textos[ulttxtautor][ulttxttitol].nombre_paraules();
}

void Cjt_Text::info(string& autorultim, string& titolultim)
{
    cout << ulttxtautor << " " << ulttxttitol << " " << cjt_textos[ulttxtautor][ulttxttitol].nombre_frases() << " " << cjt_textos[ulttxtautor][ulttxttitol].nombre_paraules() << endl;
    cout << "Cites Associades:" << endl;
    autorultim = ulttxtautor;
    titolultim = ulttxttitol;
}

void Cjt_Text::autor()
{
  cout << ulttxtautor << endl;
}

void Cjt_Text::escriu_contingut()
{
    int n = cjt_textos[ulttxtautor][ulttxttitol].nombre_frases();
    --n;
    cjt_textos[ulttxtautor][ulttxttitol].contingut_xy(0,n);
}

void Cjt_Text::frases_x_y(int x, int y)
{
    cjt_textos[ulttxtautor][ulttxttitol].contingut_xy(x,y);
}

void Cjt_Text::frases_base(string expressio)
{
    vector<int>frases;
    cjt_textos[ulttxtautor][ulttxttitol].interseccio_paraules(expressio,frases);
    for(int i = 0; i < frases.size(); ++i) {
        cjt_textos[ulttxtautor][ulttxttitol].escriure_frase(frases[i]);
    }
}

void Cjt_Text::frases_evaluar(string expressio)
{
    int blancs = 0;
    while(expressio[blancs] == ' ') ++blancs;
    expressio.erase(0,blancs);
    vector<int> resultat;
    resultat = cjt_textos[ulttxtautor][ulttxttitol].evaluacio(expressio);
    for(int i = 0; i < resultat.size(); ++i) {
        cjt_textos[ulttxtautor][ulttxttitol].escriure_frase(resultat[i]);
    }
}

void Cjt_Text::frases_per_paraules(string paraules)
{
    cjt_textos[ulttxtautor][ulttxttitol].escriure_per_frase(paraules);
}

bool Cjt_Text::text_triat()
{
    return textriat;
}

void Cjt_Text::escriure_taula_text()
{
    cjt_textos[ulttxtautor][ulttxttitol].escriure_taula();
}
