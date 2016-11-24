/** @file Cjt_cites.hh
    @brief Especificació de la classe Cites
*/

#ifndef _CJT_CITES_HH
#define _CJT_CITES_HH
    
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include <sstream>
#include "Cjt_cites.hh"
#include "Text.hh"
using namespace std;

/** @class Cjt_cites
    @brief Representa un conjunt de cites 
    
*/

class Cjt_cites 
{
private:
  struct Cita{
	  string autor,titol,referencia;
	  int fraseinicial,frasefinal;
	  vector<string>contingutfrases;
  };
	
  map<string,Cita> cjt_cita;
  map<string,int> indexs;
  
  // 1er Map:
  // Indexat per referència completa i amb contingut Cita
  // 2on Map:
  // Indexat per inicials dels autors que han estat al conjunt algun cop
  // Amb int de l'ultima referencia
   
  
public: 

  //Constructores
  
  /** @brief Crea un conjunt de cites
     
	\pre <em> cert </em>
	\post El sistema te un conjunt de cites
    */
    
    Cjt_cites();
    
    //Destructores
    
    /** @brief Elimina el conjunt de cites
     
	\pre <em> cert </em>
	\post Conjunt destruit
    */
    
    ~Cjt_cites();
  
	//Modificadores
  
    /** @brief Afegeix una cita al conjunt
     
	\pre x <= y
	\post El conjunt resultant és el conjunt de cites amb la última cita afegida al final
    */
     
    void afegir_cita(string autor1, string titol1, Text subtext, int fraseini, int frasefi);
    
    /** @brief Elimina una cita del conjunt
     
	\pre <em> cert </em>
	\post El conjunt resultant és el conjunt de cites amb la cita escollida eliminada
    */
    
    void eliminar_cita(string referencia);
    
	//Consultores
	
	bool existeix_cita(string referencia);
	
	bool existeix_mateixa_cita(string autor1, string titol1, int numini, int numfi);
    
    /** @brief Mostra la informació d'una cita
     
	\pre <em> cert </em>
	\post Mostra l'autor, el titol, el número de frase inicial i de la final i el contingut que compon la cita
    */
    
    void info_cita(string referencia);
    
    /** @brief Mostra les cites d'un autor
     
	\pre <em> cert </em>
	\post Mostra totes les cites d'un determinat autor ordenades per referència. Per cada cita mostra la referència, el contingut de les frases, l'autor i el títol del text d'on provenen
    */
    
    void cites_autor(string autor1);
    
    /** @brief Mostra totes les cites de l'ultim text triat
     
	\pre <em> cert </em>
	\post Mostra totes les cites de l'últim text triat ordenades per referència. Per cada cita mostra la referència, el contingut de les frases, l'autor i el títol del text d'on provenen
    */
   
    void cites_ulttxt(bool cites_sol, string titol1, string autor1);
    
    /** @brief Mostra totes la informació de les cites de l'ultim text triat
     
     \pre <em> cert </em>
     \post Mostra la informació de les cites de l'ultim text triat
     */
    
    void cites_info(string titol1, string autor1);
    
    /** @brief Mostra totes les cites del conjunt
     
	\pre <em> cert </em>
	\post Mostra totes les cites del conjunt ordenades per referència. Per cada cita mostra la referència, el contingut de les frases, l'autor i el títol del text d'on provenen
    */
    
    void totes_cites();
    
    /** @brief Mostra si la cita ja pertany al conjunt
     
     \pre <em> cert </em>
     \post Retorna un booleà amb false si la cita no hi és al conjunt
     */
    
    bool cita_al_conjunt(string referencia);
    
    
};

#endif
