#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>

using namespace std;

#include "Couleur.h"
#include "Forme.h"
#include "Rectangle.h"
#include "SmartPointer.h"
#include "ListeBase.h"

template <class T>
ListeBase<T>::ListeBase()
{
	ptete = NULL;
}

template <class T>
ListeBase<T>::~ListeBase()
{
		
	Cellule<T>* save = ptete;
	
	while(save != NULL)
	{
		ptete = save;
		save = save->suivant;
		delete ptete;
	}
	
}


template <class T>
ListeBase<T>::ListeBase(const ListeBase& arg)
{
	ptete = NULL;
	for(int i = 0; i < arg.getNombreElements(); i+=1)
	{
		if(this->ptete == NULL)
		{
			this->ptete = new Cellule<T>;
			this->ptete->valeur = arg.getElement(i)->valeur;
			this->ptete->suivant = NULL;
		}
		else
		{
			Cellule<T>* temp;
			temp = new Cellule<T>;
			temp->valeur = arg.getElement(i)->valeur;
			temp->suivant = this->ptete;
			this->ptete = temp;
		}
	}
	
}

template <class T>
ListeBase<T>& ListeBase<T>::operator=(const ListeBase& arg)
{
	
	for(int i = 0; i < arg.getNombreElements(); i+=1)
	{
		
		if(this->ptete == NULL)
		{
			this->ptete = new Cellule<T>;
			this->ptete->valeur = arg.getElement(i)->valeur;
			this->ptete->suivant = NULL;
		}
		else
		{
			Cellule<T>* temp;
			temp = new Cellule<T>;
			temp->valeur = arg.getElement(i)->valeur;
			temp->suivant = this->ptete;
			this->ptete = temp;
		}
	}
	
	return *this;
	
}

template <class T>
bool ListeBase<T>::estVide()
{
	if(ptete != NULL)
		return 1;
	return 0;
}

template <class T>
void ListeBase<T>::Affiche()
{

	Cellule<T>* save;

	save = ptete;
	
	while(save != NULL)
	{
		cout << save->valeur << endl;
		save = save->suivant; 
	}
}

template <class T>
Cellule<T>* ListeBase<T>::getElement(int i) const
{
	Cellule<T>* search = ptete;
	
	for(int j = 0; search != NULL && j < i; j+=1)
	{
		search = search->suivant;
	}
	
	return search;
}


template <class T>
int ListeBase<T>::getNombreElements() const
{
	Cellule<T>* save;
	int i = 0;
	
	save = ptete;
	while(save != NULL)
	{
		i++;
		save = save->suivant; 
	}
	return i;
}

template <class T>
void ListeBase<T>::Purge()
{
	Cellule<T>* save = ptete;
		
	while(save != NULL)
	{
		save = ptete->suivant;
		delete ptete;
		ptete = save;
	}
}

template class ListeBase<int>;
template class ListeBase<int*>;
template class ListeBase<Couleur>;
template class ListeBase<SmartPointer<int> >;
template class ListeBase<SmartPointer<Forme> >;
