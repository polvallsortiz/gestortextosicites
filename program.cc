#include "Cjt_text.hh"
#include "Cjt_cites.hh"
#include "Text.hh"
#include <sstream>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

string norm(string& comandes) {			//Bitch better have my money. Ya va 
	istringstream issnorm(comandes);
	string strnorm,aux2; 
	bool primercom = true;
	while(issnorm >> strnorm) {
		if(strnorm == "{" or strnorm == "(") {
			string aux = strnorm;
			issnorm >> strnorm;
			aux2 += aux + strnorm;
		}
		else if(strnorm == "}" or strnorm == ")") {
			if(aux2[aux2.length()-1] == ' ') aux2.erase(aux2.length()-1);
			aux2 += strnorm;
		}
		else if(strnorm[0] == '"'){      // Varios casos:
			if(strnorm.length() != 1){ 			//Comillas + palabra Ej: "Patata
				primercom = false;				//Entonces primeras comillas se pone a false
				aux2 += strnorm + " ";
			}
			else if(strnorm.length() == 1){		//Comillas solas
				if(primercom){ 							//Si son las primeras, coge la siguiente palabra y las une Ej: " + Patata -> "Patata
					primercom = false;
					string aux = strnorm;
					issnorm >> strnorm;
					aux2 += aux + strnorm;
				}
				else {									//Si son las del final
					if(aux2[aux2.length()-1] == ' ') aux2.erase(aux2.length()-1); 	//Como despues de la palabra se añade espacio y tienen que ir pegadas, se quita
					aux2 += strnorm;
				}
			}
		}
		else aux2 += strnorm + " ";            //Si no hay nah, se añade la palabra y un espacio
	}
	if(aux2[aux2.length()-1] == ' ') aux2.erase(aux2.length()-1); //Si queda un espacio al final, se elimin
	return aux2;
}												//PODRIAMOS TRATAR YA AQUI LOS INTERROGANTES Y ELIMINARLOS

int main(){
	Cjt_Text textos;
	Cjt_cites cites;
	bool primera_iteracio = true;
	string comandes,actual,aux4;
	getline(cin,comandes);
	aux4 = comandes;
	comandes = norm(comandes);
	while(comandes != "sortir") {
			istringstream iss(comandes);
			if(comandes != "") {
				if(primera_iteracio) primera_iteracio = false;
				else cout << endl;
				iss >> actual;
			}
			else actual = "passar";
			if(actual == "afegir") {
                string aux = aux4;
				iss >> actual;
				if(actual == "text") {
					comandes.erase(0,12);
					string titol = comandes;
					getline(cin,comandes);
					if(comandes != "") comandes = norm(comandes);
					comandes.erase(0,7);
					comandes.erase(comandes.length()-1);
					string autor = comandes;
					bool error;
					textos.afegir_text(titol,autor,error); //Correcte
					if(error) cout << aux4 << endl << "error" << endl;
					else cout << aux4 << endl;
				}
				if(actual == "cita") {
					string n,m;
                    int x,y;
                    string aut1,tit1;
					Text subtext;
                    iss >> n >> m;
                    comandes.erase(0,12);
                    if(isdigit(n[0]) and isdigit(m[0])){
                    	istringstream iss2(comandes);
                    	iss2 >> x >> y;
                    	if(x>0 and x<=y and y<=textos.nombre_frases_textos()){
                    		cout << aux4 << endl;
                    		textos.info_afegir_cita(aut1,tit1,subtext,x,y); //Correcte
                    		if(not cites.existeix_mateixa_cita(aut1,tit1,x,y)) cites.afegir_cita(aut1,tit1,subtext,x,y); //Correcte
                    		else cout << "error" << endl;
                     	}
                     	else {
                     		cout << aux4 << endl;
                     		cout << "error" << endl;
                     	}
                    } 	
                    else {
                    	cout << aux4 << endl;
                    	cout << "error" << endl;
                    }
				}
			}
			if(actual == "triar") {
				cout << aux4 << endl;
				comandes.erase(0,12);
				comandes.erase(comandes.length()-1);
				textos.triar_text(comandes); //CORRECTE
			}
			if(actual == "eliminar") {
				cout << aux4 << endl;
				iss >> actual;
				if(actual == "text") {
                    if(textos.text_triat()) {
                        textos.eliminar_text(); //Correcte
					}
                    else cout << "error" << endl;
                }
				if(actual == "cita") {
					comandes.erase(0,15);
					comandes.erase(comandes.length()-1);
					//if (not cites.cita_al_conjunt(comandes)) 
					if(cites.existeix_cita(comandes)) cites.eliminar_cita(comandes); //Correcte
					else cout << "error" << endl;
				}
			}
			if(actual == "substitueix") {
				cout << aux4 << endl;
                if(textos.text_triat()) {
                    iss >> actual;
                    string p1 = actual;
                    p1.erase(0,1);
                    p1.erase(p1.length() - 1);
                    iss >> actual;
                    iss >> actual;
                    string p2 = actual;
                    p2.erase(0,1);
                    p2.erase(p2.length() - 1);
                    textos.substituex_en_text(p1,p2); //Correcte
                }
                else cout << "error" << endl;
			}
			if(actual == "textos") { 
				cout << aux4 << endl;
				comandes.erase(0,14);
				comandes.erase(comandes.length()-3);
				textos.textos_per_autor(comandes); //Correcte
			}
			if(actual == "tots") {
				cout << aux4 << endl;
				iss >> actual;
				if(actual == "textos") textos.tots_textos(); //Correcte
				if(actual == "autors") textos.tots_autors(); //Correcte
			}
			if(actual == "info") {
				cout << aux4 << endl;
				iss >> actual;
                if(actual == "?") {
                    if(textos.text_triat()) {
                        string autorfi,titolfi;
                        textos.info(autorfi,titolfi); //Correcte
                        cites.cites_ulttxt(false,titolfi,autorfi); //Correcte
                    }
                    else cout << "error" << endl;
                }
				if(actual == "cita") {
					comandes.erase(0,11);
					comandes.erase(comandes.length()-3);
					if(cites.existeix_cita(comandes)) cites.info_cita(comandes);
					else cout << "error" << endl;
				}
			}
			if(actual == "autor") {
				cout << aux4 << endl;
                if(textos.text_triat()) textos.autor(); //Correcte
                else cout << "error" << endl;
			}
			if(actual == "contingut") {
				cout << aux4 << endl;
                if(textos.text_triat()) textos.escriu_contingut(); //Correcte
                else cout << "error" << endl;
			}
			if(actual == "frases") {
				cout << aux4 << endl;
				comandes.erase(0,7);
                if(textos.text_triat()){
                    if(comandes[0] == '(') {
                    	comandes.erase(comandes.length()-2);
                    	textos.frases_evaluar(comandes); //Va si no es molt llarg :(
                    }
                    if(comandes[0] == '{') {
                    	comandes.erase(0,1);
                    	comandes.erase (comandes.length()-3);
                    	textos.frases_base(comandes);
                    }
                    else {
                    	if(comandes[0] == '"'){
                    		comandes.erase(0,1);
                    		comandes.erase(comandes.length()-3);
                   			textos.frases_per_paraules(comandes); //Correcte
                		 }
                    	else {
                    	 	string n,m;
                    	 	int x,y;
                    	 	iss >> n >> m;
                    	 	if(isdigit(n[0]) and isdigit(m[0])){
                    	 		istringstream iss2(comandes);
                    	 		iss2 >> x >> y;
                    	 		if(x>0 and x<=y and y<=textos.nombre_frases_textos()){
                        			textos.frases_x_y(x-1,y-1); //Correcte
                    	 		}
                    	 		else cout << "error" << endl;
                    	 	} else if(n[0] != '(') cout << "error" << endl;
                    	}
                    }
                } else cout << "error" << endl;
			}
			if(actual =="nombre") {
				cout << aux4 << endl;
				comandes.erase(0,10);
                if(textos.text_triat()) {
                    if(comandes == "frases ?") cout << textos.nombre_frases_textos() << endl;//Correcte
                    if(comandes == "paraules ?") cout << textos.nombre_paraules_textos() << endl; //Correcte
                }
                else cout << "error" << endl;
			}
			if(actual == "taula") {
				cout << aux4 << endl;
                if(textos.text_triat()) textos.escriure_taula_text(); //Correcte
                else cout << "error" << endl;
			}
			if(actual == "cites") {
				cout << aux4 << endl;
				iss >> actual;
				if(actual == "autor") {
					comandes.erase(0,13);
					comandes.erase(comandes.length() - 3);
					cites.cites_autor(comandes); //Correcte
				}	
                else {
                    string aut,tit;
                    if(textos.text_triat()) {
                        textos.info_texttriat(aut,tit); //Correcte
                        cites.cites_ulttxt(true,tit,aut); //Correcte
                    }
                    else cout << "error" << endl;
                }
			}
			if(actual == "totes") {
				cout << aux4 << endl;
				cites.totes_cites(); //Correcte
			}
			getline(cin,comandes);
			aux4 = comandes;
			if(comandes != "") comandes = norm(comandes);
			if(comandes == "sortir") cout << endl;
		}
}

