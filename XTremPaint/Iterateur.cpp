#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>

using namespace std;

#include "Couleur.h"
#include "Forme.h"
#include "Rectangle.h"
#include "SmartPointer.h"
#include "Iterateur.h"

template <class T> 
Iterateur<T>::Iterateur(ListeBase<T>& list):liste(list), ptemp(list.ptete){};


template <class T>
bool Iterateur<T>::end() const
{
	if (ptemp->suivant == NULL)
		return true;
	return false;
}

template <class T>
void Iterateur<T>::reset()
{ 
	ptemp = liste.ptete;
}


template <class T> T Iterateur<T>::remove() 
{
	T valeur;
	Cellule<T> *pt = ptemp;
	
	reset();

	if(pt == ptemp)
		liste.ptete = pt->suivant;
	else 
	{
		while(ptemp->suivant != pt)
			ptemp = ptemp->suivant;
	}
	
	ptemp->suivant = pt->suivant;
	valeur = pt->valeur;

	delete pt;

	return valeur;
}


template <class T>
bool Iterateur<T>::operator++ ()
{
	if (!end())
	{
		ptemp = ptemp->suivant;
		
		return true;
	}
	return false;
}

template <class T>
bool Iterateur<T>::operator++(int t)
{
	return operator++();
}

template <class T>
Iterateur<T>::operator T() const
{
	return ptemp->valeur;
}

template <class T> T* Iterateur<T>::operator&() 
{
	return &(ptemp->valeur);
}


template struct Iterateur<int>;
template struct Iterateur<int*>;
template class Iterateur<Couleur>;
template class Iterateur<SmartPointer<int> >;
template class Iterateur<SmartPointer<Forme> >;
