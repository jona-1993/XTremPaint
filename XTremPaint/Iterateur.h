#ifndef ITERATEUR_H
#define ITERATEUR_H

#include <iostream>
#include "ListeBase.h"

template <class T>
class Iterateur: public ListeBase<T>
{
	virtual T* insere(const T&){};
	private: 
		Cellule<T> *ptemp;
		ListeBase<T>& liste;
	
	public :
		Iterateur(ListeBase<T>&);
	
		bool end() const;
		
		void reset ();
		
		T remove();
		
		bool operator++ ();
		
		bool operator++(int);
		
		T* operator&(void);
		
		operator T() const;
};

#endif
