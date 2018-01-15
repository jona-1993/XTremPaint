#ifndef LISTETRIEE_H
#define LISTETRIEE_H

#include "ListeBase.h"

template <class T>
class ListeTriee: public ListeBase<T>
{
	public:
		ListeTriee();
		
		ListeTriee(const ListeTriee&);
	
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
