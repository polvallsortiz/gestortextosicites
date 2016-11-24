/** @file Text.hh
 @brief Especificació de la classe Contingut
 */

#ifndef _TEXT_HH
#define _TEXT_HH

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <set>
using namespace std;

/** @class Text
 @brief Representa el contingut d'un text (conjunt de frases)
 
 */

class Text
{
private:
    struct Paraules {
        int numaparicions;
        string paraula;
        vector<int>frases_apareix;
    };
    vector<string> contingut;
    vector<Paraules> dades;
    set<string> llista;
    
    /** @brief Ordena la taula de freqüències
     
     \pre <em> cert </em>
     \post Retorna la taula de freqüències ordenada per número d'aparicions, després per llargaria de les paraules i desprès alfabèticament
     */
    
    void ordenar_taula();
    
    /** @brief Component de comparació per a ordenar la taula de freqüències
     
     
     \pre <em> cert </em>
     \post Retorna l'ordre en el qual s'han d'ordenar els components de la taula
     */
     
    static bool comp(Paraules a, Paraules b);
    
    
public:
    //Constructores
    
    /** @brief Crea el contingut d'un text
     
     \pre <em> cert </em>
     \post El conjunt resultant és el contingut d'un text
     */
    Text();
    
    //Destructores
    
    /** @brief Elimina un text del conjunt
     
     \pre <em> cert </em>
     \post El conjunt resultant es l'original sense el text a eliminar
     */
    ~Text();
    
    //Modificadores
    /** @brief Afegeix frase al text seleccionat
     
     \pre <em> cert </em>
     \post El conjunt de frases s'ha actualitzat
     */
    
    void afegir_frase(string frase);
    
    /** @brief Substitueix una paraula per una altra tots els cops que hi apareix al text
     
     \pre <em> cert </em>
     \post El text resultant és l'original amb la paraula
     */
    
    void substitueix_contingut(string p1, string p2);
    
    void actualitza_taula(string p1, string p2);
    
    /** @brief Afegeix totes les paraules per frase durant l'introduccio de text en Cjt_text
     
     \pre <em> cert </em>
     \post Taula de frequencia actualitzada
     */
    
    void afegir_per_frase(string frase, string autor, string titol, int numfrase);
    
    void afegir_buit(string autor1, string titol1);
    
    /** @brief Al vector frasesvalides escriu les frases del titol i autor citats que contenen totes les paraules
     
     \pre <em> cert </em>
     \post Retorna el vector amb les frases vàlides
     
     */
    
    void interseccio_paraules(string paraules, vector<int>& interseccio);
    
    /** @brief Retorna la informació de la paraula
     
     \pre <em> cert </em>
     \post Retorna la informació actualitzada
     
     */
    
    bool informacio_text_paraula(string paraula);
    
    //Consultores
    
    /** @brief Mostra totes les frases entre x i y
     
     \pre <em> cert </em>; x i y dintre del contingut
     \post Escriu totes les frases entre x i y, x i y incloses
     */
    
    void contingut_xy(int x, int y);
    
    /** @brief Retorna la frase x
     
     \pre <em> cert </em>;
     \post Retorna la frase x
     */
    
    string frase_x(int x);
    
    /** @brief Mostra el nombre de frases
     
     \pre <em> cert </em>
     \post Escriu el nombre de frases del contingut
     */
    
    int nombre_frases();
    
    /** @brief Mostra el nombre de paraules
     
     \pre <em> cert </em>
     \post Escriu el nombre de paraules del contingut
     */
    
    int nombre_paraules();
    
    /** @brief Evalua la expressió recursivament
     
     \pre <em> cert </em>
     \post Retorna les frases que compleixen l'expressió
      */
      
     vector<int> evaluacio(string expressio);
     
     vector <int> unio(const vector<int>& esquerra, const vector<int>& dreta);
     
     vector <int> interseccio(const vector<int>& esquerra, const vector<int>& dreta);
     
     string extreure(string frase, int& i);
     
     char op(string expressio, int& i);
     
     void normalitzar(string& frase);
    
    /** @brief Mostra les frases que contenen una paraula
     
     \pre <em> cert </em>
     \post Escriu totes les frases del contingut que contenen la paraula
     */
    void escriure_per_paraula(string p1);
    
    /** @brief Mostra les frases que contenen un conjunt de paraules
     
     \pre <em> cert </em>
     \post Escriu totes les frases del contingut que contenen la frase
     */
    
    void escriure_per_frase(string paraules);
    
    /** @brief Escriu la frase i-éssima del text
     
     \pre <em> cert </em>
     \post Escriu el número de frase seguit de la frase i-éssima del text
     */
    
    void escriure_frase(int i);
    
    /** @brief Escriu la taula de freqüències pel canal de sortida estandard
     
     \pre <em> cert </em>
     \post Taula escrita en el cout
     
     */
    void escriure_taula();
    
};

#endif 

