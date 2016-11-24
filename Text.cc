#include "Text.hh"

Text::Text(){}

Text::~Text(){}

bool Text::comp(Paraules a, Paraules b) {
    return ((a.numaparicions > b.numaparicions) or (a.numaparicions == b.numaparicions and
    a.paraula.length() < b.paraula.length()) or (a.numaparicions == b.numaparicions and
    a.paraula.length() == b.paraula.length() and a.paraula < b.paraula));
}

void Text::ordenar_taula()
{
    sort(dades.begin(), dades.end(), comp);
}

void Text::afegir_frase(string frase)
{
    contingut.push_back(frase);
}

void Text::substitueix_contingut(string p1, string p2)
{
    for(int i; i<contingut.size();++i){
        istringstream iss(contingut[i]);
            string actual,res;
            while(iss >> actual){
                bool signe = true;
                if((actual[actual.length()-1] >= 'a' and actual[actual.length()-1] <= 'z') or (actual[actual.length()-1] >= '0' and actual[actual.length()-1] <= '9')) signe = false;
                if(signe) {
                    char signe1 = actual[actual.length()-1];
                    actual.erase(actual.length()-1);
                    if(actual == p1){
                        actual = p2 + signe1;
                    }
                    else actual = actual + signe1;
                }
                else {
                    if(actual == p1){
                        actual = p2;
                    }
                }
                res += " " + actual;
            }
            res.erase(0,1);
            contingut[i] = res;
    }
    actualitza_taula(p1,p2);
}

void Text::actualitza_taula(string p1, string p2){
    int i = 0;
    int i1;
    int i2;
    bool t1 = false;
    bool t2 = false;
    int aux;
    int mida = dades.size();
    while(i < mida){
        if(dades[i].paraula == p1){
            t1 = true;
            i1 = i;
            aux = dades[i].numaparicions;
        }
        if(dades[i].paraula == p2){
            t2 = true;
            i2 = i;
        }
        ++i;
    }
    if(t1){
        if(t2 and p1!=p2){
            vector<int>vecp1, vecp2, vfinal;
            vecp1 = dades[i1].frases_apareix;
            vecp2 = dades[i2].frases_apareix;
            vfinal = unio(vecp1,vecp2);
            dades[i2].frases_apareix = vfinal;
            dades[i2].numaparicions += aux;
            dades.erase(dades.begin()+i1);
        }
        else if(p1!=p2){
            dades[i1].paraula = p2;
        }
    }
    ordenar_taula();
}
void Text::afegir_per_frase(string frase, string autor, string titol, int numfrase)
{
    string actual;
    istringstream issautor(autor);
    istringstream isstitol(titol);
    while(issautor >> actual) {
        llista.insert(actual);
    }
    while(isstitol >> actual) {
        if(actual[0] == '"') actual.erase(0,1);
        if(actual[actual.length()-1] == '"') actual.erase(actual.length()-1);
        if(actual[actual.length()-1] == '"' or actual[actual.length()-1] == '.' or actual[actual.length()-1] == ',' or actual[actual.length()-1] == '!' or actual[actual.length()-1] == ';' or actual[actual.length()-1] == ':' or actual[actual.length()-1] == '?') actual.erase(actual.length()-1);
        llista.insert(actual);
    }
    istringstream iss(frase);
    while(iss >> actual) {
        if(actual != "." or actual != "!" or actual != "?" or actual != ""){
            char c = actual[actual.length()-1];
            if(c == '?' or c == '!' or c == ',' or c == '.' or c == ':' or c == ';') actual.erase(actual.length()-1);
            llista.insert(actual);
            int i = 0;
            bool trobat = false;
            int n = dades.size();
            while(i < n and not trobat) {
                if(dades[i].paraula == actual) {
                    trobat = true;
                    ++dades[i].numaparicions;
                    if(dades[i].frases_apareix[dades[i].frases_apareix.size()-1] != numfrase) dades[i].frases_apareix.push_back(numfrase);
                }
                ++i;
            }
            if(not trobat and actual != "") {
                Paraules aux;
                aux.numaparicions = 1;
                aux.paraula = actual;
                aux.frases_apareix.push_back(numfrase);
                dades.push_back(aux);
            }   
        }
        ordenar_taula();
    }
}

void Text::afegir_buit(string autor1, string titol1)
{
    string actual;
    istringstream issautor(autor1);
    istringstream isstitol(titol1);
    while(issautor >> actual) {
        llista.insert(actual);
    }
    while(isstitol >> actual) {
        if(actual[0] == '"') actual.erase(0,1);
        if(actual[actual.length()-1] == '"') actual.erase(actual.length()-1);
        if(actual[actual.length()-1] == '"' or actual[actual.length()-1] == '.' or actual[actual.length()-1] == ',' or actual[actual.length()-1] == '!' or actual[actual.length()-1] == ';' or actual[actual.length()-1] == ':' or actual[actual.length()-1] == '?') actual.erase(actual.length()-1);
        llista.insert(actual);
    }
}

void Text::interseccio_paraules(string paraules, vector<int>& vec)
{
    istringstream buffercount(paraules);
    string aux;
    int count = 0;
    while(buffercount>>aux) ++count;
    vector<int> v1, v2;
    string actual;
    istringstream iss(paraules);
    bool first = true;
    int size = dades.size();
    if(first){
        iss>>actual;
        first = false;
        bool trobatfirst = false;
        int i = 0;
        while(i < size and not trobatfirst){
            if(dades[i].paraula == actual) {
                trobatfirst = true;
                v1 = dades[i].frases_apareix;
            }
            ++i;
        }
    }
    if(count == 1) vec = v1;
    else{
        while(iss >> actual){
            bool trobat = false;
            int j = 0;
            while(j < size and not trobat){
                if(dades[j].paraula == actual){
                    trobat = true;
                    int n = v1.size();
                    v2 = dades[j].frases_apareix;
                    int m = v2.size();
                    int it1,it2;
                    it1 = it2 = 0;
                    vec.clear();
                    while(it1 < n and it2 < m){
                        if(v1[it1] == v2[it2]){
                            vec.push_back(v1[it1]);
                            ++it1;
                            ++it2;
                        }
                        else if (v1[it1] < v2[it2]) ++it1;
                        else ++it2;
                    }
                    v1 = vec;
                }
                ++j;
            }
        }    
    }
}

bool Text::informacio_text_paraula(string paraula)
{
    set<string>::iterator i = llista.find(paraula);
    if(i != llista.end()) return true;
    else return false;
}

void Text::contingut_xy(int x, int y)
{
    for(int i = x; i <= y; ++i) escriure_frase(i);
}

string Text::frase_x(int x)
{
    return contingut[x];
}

int Text::nombre_frases()
{
    return contingut.size();
}

int Text::nombre_paraules()
{
    int count = 0;
    int mida = dades.size();
    for(int i = 0; i < mida; ++i) {
        count += dades[i].numaparicions;
    }
    return count;
}

vector<int> Text::evaluacio(string expressio)
{
    int blancs = 0;
    while(expressio[blancs] == ' ') ++blancs;
    expressio.erase(0,blancs);
    int pos = 0;
    if(expressio[pos] == '{') { //Cas base
        normalitzar(expressio); //esborra els espais inutils
        vector<int> frases;
        interseccio_paraules(expressio,frases);
        return frases;
    }
    else {
        expressio.erase(0,1);
        string fill_esquerra = extreure(expressio,pos); //extreu part esquerra
        expressio.erase(0,pos);
        pos = 0;
        char eval = op(expressio,pos);//treu el & o el | central
        expressio.erase(0,pos);
        pos = 0;
        string fill_dret = extreure(expressio,pos);//treu la part dreta de lexpressio
        vector<int> esq = evaluacio(fill_esquerra); //ho fa recursiu
        vector<int> dre = evaluacio(fill_dret);//ho fa recursiu
        vector<int> res;
        if(eval == '|') res = unio(esq,dre);
        if(eval == '&') res = interseccio(esq,dre);
        return res;
    }
}

vector <int> Text::unio(const vector<int>& esquerra, const vector<int>& dreta)
{
    vector<int> resultat;
    int esq = esquerra.size();
    int dr = dreta.size();
    int ie = 0;
    int id = 0;
    while(ie < esq and id < dr){
        if(esquerra[ie] == dreta[id]){
            resultat.push_back(esquerra[ie]);
            ++ie;
            ++id;
        }
        else if (esquerra[ie] < dreta[id]){
            resultat.push_back(esquerra[ie]);
            ++ie;
        }
        else{
            resultat.push_back(dreta[id]);
            ++id;
        }
    }
    while(id<dr){
        resultat.push_back(dreta[id]);
        ++id;
    }
    while(ie<esq){
        resultat.push_back(esquerra[ie]);
        ++ie;
    }
    return resultat;
}

vector <int> Text::interseccio(const vector<int>& esquerra, const vector<int>& dreta)
{
    vector<int> resultat;
    int esq = esquerra.size();
    int dr = dreta.size();
    int ie = 0;
    int id = 0;
    while(ie < esq and id < dr){
        if(esquerra[ie] == dreta[id]){
            resultat.push_back(esquerra[ie]);                   //Ho he canviat per veure si era aixo el que fallava, demà ho tornem a ficar com ho tenies si vols
            ++ie;
            ++id;
        }
        else if (esquerra[ie] < dreta[id]){
            ++ie;
        }
        else{
            ++id;
        }
    }
    return resultat;
}

string Text::extreure(string frase, int& i)
{
    string result;
    int parentesis,claudators;
    parentesis = claudators = 0;
    while(frase[i] != '(' and frase[i] != '{') ++i;
    frase.erase(0,i);
    i = 0;
    if(frase[i] == '(') {
        ++parentesis;
        ++i;
        while(parentesis != 0) {
            if(frase[i] == '(') ++parentesis;
            if(frase[i] == ')') --parentesis;
            ++i;
        }
        result = frase.substr(0,i);
    }
    if(frase[i] == '{') {
        ++claudators;
        ++i;
        while(claudators != 0) {
            if(frase[i] == '{') ++claudators;
            if(frase[i] == '}') --claudators;
            ++i;
        }
        result = frase.substr(0,i);
    }
    return result;
}

char Text::op(string expressio, int& i)
{
    char result;
    while(expressio[i] != '|' and expressio[i] != '&') ++i;
    if(expressio[i] == '|') result = '|';
    if(expressio[i] == '&') result = '&';
    return result;
}

void Text::normalitzar(string& frase)
{
    int pos = 0;
    while(frase[pos] != '{') ++pos;
    ++pos;
    frase.erase(0,pos);
    pos = frase.length();
    while(frase[pos] != '}') --pos;
    frase.erase(pos);
}

void Text::escriure_per_paraula(string p1)
{
    int m = contingut.size();
    for(int i = 0; i < m; ++i) {
        bool trobat = false;
        string actual;
        istringstream iss(contingut[i]);
        while(iss >> actual and not trobat) {
            if(actual == p1) trobat = true;
        }
        if(trobat) escriure_frase(i);
    }
}

void Text::escriure_per_frase(string paraules)
{
    //COMPTADOR PARAULES
    int num_paraules = 0;
    istringstream iss(paraules);
    string per_paraules,primera_paraula;
    iss >> primera_paraula;
    ++num_paraules;
    while(iss >> per_paraules) ++num_paraules;
    vector<int>vec;
    interseccio_paraules(paraules,vec);
    for(int i = 0; i < vec.size(); ++i) {
        string fraseactual = frase_x(vec[i]);
        istringstream iss_frase(fraseactual);
        int num_paraules_frase = 0;
        istringstream iss_compt_frase(fraseactual);
        string frase_aux;
        while(iss_compt_frase >> frase_aux) ++num_paraules_frase;
        //FINS AQUÍ COMPTA BÉ
        bool primer_trobat = false;
        bool stop = false;
        int pos = 0;
        string actual;
        while(iss_frase >> actual and not stop) {
            if(actual[actual.length()-1] == '.' or actual[actual.length()-1] == ',' or actual[actual.length()-1] == ';' or actual[actual.length()-1] == ':' or actual[actual.length()-1] == '!' or actual[actual.length()-1] == '?') actual.erase(actual.length()-1);
            if(actual == primera_paraula) primer_trobat = true;
            if(primer_trobat){
                string possible_conjunt = primera_paraula;
                if(pos + num_paraules > num_paraules_frase){
                    stop = true;
                }
                while(pos < num_paraules_frase and primer_trobat and not stop) {                
                    string actual2;
                    int auxnum = num_paraules-1;
                    while(auxnum != 0){                                               
                        iss_frase >> actual2;
                        if(actual2[actual2.length()-1] == '.' or actual2[actual2.length()-1] == ',' or actual2[actual2.length()-1] == ';' or actual2[actual2.length()-1] == ':' or actual2[actual2.length()-1] == '!' or actual2[actual2.length()-1] == '?') actual2.erase(actual2.length()-1);
                        possible_conjunt += " " + actual2;
                        --auxnum;
                    }
                    if(possible_conjunt == paraules) {
                        stop = true;
                        escriure_frase(vec[i]);
                    }
                    else primer_trobat = false;
                    ++pos;
                    
                    }
                }
            }
        }
}

void Text::escriure_frase(int i)
{
    cout << i+1 << " " << frase_x(i) << endl;
}

void Text::escriure_taula()
{
    int m = dades.size();
    for(int i = 0; i < m; ++i) {
        if(dades[i].numaparicions > 0){
            cout << dades[i].paraula << " " << dades[i].numaparicions << endl;
        }
    }
}
