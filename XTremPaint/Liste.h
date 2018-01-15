#ifndef LISTE_H
#define LISTE_H

#include "ListeBase.h"

template <class T>
class Liste: public ListeBase<T>
{
	public:
		Liste();
		
		Liste(const Liste&);
	
		T* insere(const T&);

		T* suppresion(const T&);
		
		Cellule<T>* Recherche(const T&);
		
		void Affiche();
		
		bool estVide();
		
		int getNombreElements() const;
		
		Cellule<T>& operator=(const T);
		
		Cellule<T>& operator=(Cellule<T>*);
};

#endif
