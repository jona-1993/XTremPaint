#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>

using namespace std;


#include "ListeTriee.h"

#include "Couleur.h"
#include "Forme.h"
#include "Rectangle.h"
#include "SmartPointer.h"

template <class T>
ListeTriee<T>::ListeTriee()
{
	this->ptete = NULL;
}

template <class T>
ListeTriee<T>::ListeTriee(const ListeTriee& arg)
{
	this->ptete = NULL;
	
	for(int i = 0; i < arg.getNombreElements(); i+=1)
	{
		insere(arg.getElement(i)->valeur);
	}
	
}

template <class T>
T* ListeTriee<T>::insere(const T& a)
{

	if(this->ptete == NULL)
	{
		this->ptete = new Cellule<T>;
		
		this->ptete->valeur = a;
		
		this->ptete->suivant = NULL;
	}
	else
	{
		Cellule<T> *tempA, *tempB, *tempC;
		
		tempB = this->ptete;

		tempA = tempB;

		while(tempB != NULL && tempB->valeur < a)
		{
			if (tempB != NULL && tempB->valeur < a)
			{
				tempA = tempB;
			}
			tempB = tempB->suivant;
		}

		tempC = new Cellule<T>;
		tempC->valeur = a;
		tempC->suivant = tempB;

		if(tempB == this->ptete)
		{
			this->ptete = tempC;
		}
		else
		{
			tempA->suivant = tempC;
		}
		
	}
	
	return &(this->ptete->valeur);
}

template <class T>
T* ListeTriee<T>::suppresion(const T& a)
{
	Cellule<T> *temp, *tempPrevious = NULL;
	if(this->ptete != NULL)
	{
		temp = this->ptete;
		while(temp != NULL && a != temp->valeur)
		{
			tempPrevious = temp;
			temp = temp->suivant;
		}

		if(tempPrevious == NULL)
		{
			this->ptete=temp->suivant;
			if(this->ptete == NULL)// Liste vidée
				return NULL;
		}
		else if(tempPrevious != NULL && temp != NULL)// Pas au bout de la liste
		{
			tempPrevious->suivant = temp->suivant;
			cout << "Suppress: " << temp->valeur << endl;
			delete temp;
			cout << "Cet élément a été supprimé avec succès !" << endl;
			return &(temp->valeur);
		}
	}
	cout << "La liste est vide ou valeur non trouvée, aucune suppresion possible !" << endl;
	return NULL;
}

template <class T>
Cellule<T>* ListeTriee<T>::Recherche(const T& a)
{
	Cellule<T>* search;

	if(this->ptete != NULL)
	{
		search = this->ptete;
		while(search != NULL && a != search->valeur)
			search = search->suivant; 
		if(search== NULL)
			cout << "Aucun résultat trouvé" << endl;
		else	
			cout << "Trouvé :" << endl << search->valeur << endl;
		return search;
	}
	cout << "Il n'y a aucun élément trouvé dans la liste !" << endl;
	return NULL;
}

template <class T>
void ListeTriee<T>::Affiche()
{
	(*this).ListeBase<T>::Affiche();
}

template <class T>
bool ListeTriee<T>::estVide()
{
	return ListeBase<T>::estVide();
}

template <class T>
int ListeTriee<T>::getNombreElements() const
{
	return ListeBase<T>::getNombreElements();
}

template <class T>
Cellule<T>& ListeTriee<T>::operator=(const T a)
{
	(*this->ptete).valeur = a;
	
	return *this->ptete;

}

template <class T>
Cellule<T>& ListeTriee<T>::operator=(Cellule<T>* pt)
{
	this->ptete = pt;
	
	return *this->ptete;

}

template class ListeTriee<int>;
template class ListeTriee<int*>;
//template class ListeTriee<Forme>; // Error: Forme is abstract

template class ListeTriee<Couleur>;
template class ListeTriee<SmartPointer<int> >;
template class ListeTriee<SmartPointer<Forme> >;
//template class ListeTriee<SmartPointer<Couleur>>;

