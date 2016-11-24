/** @file Cjt_text.hh
    @brief Especificació de la classe ConjuntText
*/

#ifndef _CJT_TEXT_HH
#define _CJT_TEXT_HH

#include "Text.hh"  
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <set>
using namespace std;

/** @class Cjt_Text
    @brief Representa un conjunt de textos indexats per autor
    
*/

class Cjt_Text 
{
private:

	map <string,map<string,Text> > cjt_textos;
    string ulttxtautor;
    string ulttxttitol;
    bool textriat;
    
public:
  //Constructores
  
   /** @brief Crea el conjunt de textos
     
	\pre <em> cert </em>
	\post El resultant és el conjunt de textos
    */
    Cjt_Text();
   
  //Destructores
  
   /** @brief Elimina un el conjunt de textos
	 
	\pre <em> cert </em>
	\post El conjunt resultant es l'original sense el conjunt de textos a eliminar
    */
    ~Cjt_Text();
      
   //Modificadores
   
   /** @brief Mostra si el text ja pertany al conjunt
     
     \pre <em> cert </em>
     \post Retorna un booleà amb false si el text no hi és al conjunt
     */
    
    bool text_al_conjunt(string autor, string titol);
    
    /** @brief Afegeix un text al conjunt
     
	\pre <em> cert </em>
	\post El conjunt resultant és cjt_textos amb el text a afegir
    */
    void afegir_text(string titol,string autor,bool& error);
    
    /** @brief Tria un text del conjunt
	
	\pre El text es troba al conjunt
	\post Retorna l'iterador ulttxt
    */
    void triar_text(string comanda);
    
    /** @brief Substitueix una paraula per una altra en el text triat
	
	\pre El text es troba al conjunt
	\post El text triat ha estat substituit
    */
    void substituex_en_text(string p1, string p2);
   
      /** @brief Elimina el text triat del conjunt
	 
	\pre 
	\post El conjunt resultant es l'original sense el text triat a eliminar
    */
    
    void eliminar_text();
    
   //Consultores
    
    /** @brief Modifica l'informació amb l'informació necessaria per afegir una cita en el sistema
     
     \pre <em> cert </em>
     \post Informació modificada
     */
    
    void info_afegir_cita(string& aut1, string& tit1, Text& subtext, int x, int y);
    
    /** @brief Modifica l'informació amb l'informació de l'ultim text;
     
     \pre <em> cert </em>
     \post Informació modificada
     */
    
    void info_texttriat(string& aut, string& tit);
    
    /** @brief Mostra tots els textos d'un autor
	
	\pre <em> cert </em>
	\post Escriu els titols de cada text de l'autor ordenats alfabèticament 
    */
    
    void textos_per_autor(string autor);
    
    /** @brief Mostra tots els textos del conjunt
	
	\pre <em> cert </em>
	\post Escriu l'autor i títol de cada text del conjunt ordenats alfabèticament per títol 
    */
    
    void tots_textos();
    
       /** @brief Mostra tots els autors i la seva informació del conjunt
	
	\pre <em> cert </em>
	\post Escriu el nom de l'autor,nombre de textos, nombre de frases i nombre de paraules de paraules de cada autor 
    */
    
    void tots_autors();

      /** @brief Retorna la quantitat de frases del ultim text triat
       
    \pre <em> cert </em>
    \post Retorna el numero de frases de l'ultim text triat
    */
       
    int nombre_frases_textos();
    
    /** @brief Retorna la quantitat de paraules del ultim text triat
     
     \pre <em> cert </em>
     \post Retorna el numero de paraules de l'ultim text triat
     */
    
    int nombre_paraules_textos();
    
    
    /** @brief Mostra tota la informació de l'últim text triat 
	
	\pre <em> cert </em>
	\post Escriu l'autor, el títol, el nombre de frases, el nombre de paraules i les cites associades de l'últim text triat
    */
    
    void info(string& autorultim, string& titolultim);
    
    /** @brief Mostra l'autor de l'últim text triat
	
	\pre <em> cert </em>
	\post Escriu el nom de l'autor del text triat 
    */
    
    void autor();
    
    /** @brief Mostra les frases del text triat
	
	\pre <em> cert </em>
	\post Escriu totes les frases del contingut del text triat a partir de l'1 
    */
    
    void escriu_contingut();
    
    /** @brief Escriu del text seleccionat les frases entre x i y
     
     \pre <em> cert </em>
     \post Escriu les frases entre x i y
	*/
	
	void frases_x_y(int x, int y);
    
    /** @brief Mostra les frases del text triat que continguin les paraules de l'expressió
	
	\pre <em> cert </em>
	\post Escriu totes les frases del contingut que continguin les paraules donades per l'expressió
    */
	
    void frases_evaluar(string expressio);
    
    /** @brief Mostra les frases on hi apareix les paraules citades en el últim text triat
	
	\pre <em> cert </em>
	\post Frases escrites per el canal estandard de sortida (cout)
    */
	
    void frases_per_paraules(string paraules);
    
    /** @brief Mostra si hi ha text triat
     
     \pre <em> cert </em>
     \post Retorna un booleà amb true si hi ha text triat, i false altrament
     */
    
    bool text_triat();
    
    /** @brief Mostra les frases on hi apareix les paraules citades en el últim text triat
	
	\pre <em> cert </em>
	\post Frases escrites per el canal estandard de sortida (cout)
    */
    
    void frases_base(string expressio);
    
    /** @brief Escriu la taula de freqüència de l'últim text triat
     
     \pre <em> cert </em>
     \post Taula escrita per el canal estandard de sortida (cout)
     */
     
     void escriure_taula_text();
};

#endif
