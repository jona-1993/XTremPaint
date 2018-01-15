#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>

using namespace std;

#include "Couleur.h"
#include "SmartPointer.h"
#include "Liste.h"

template <class T>
Liste<T>::Liste()
{
	this->ptete = NULL;
}

template <class T>
Liste<T>::Liste(const Liste& arg)
{
	this->ptete = NULL;
	for(int i = 0; i < arg.getNombreElements(); i+=1)
	{
		insere(arg.getElement(i)->valeur);
	}
	
}


template <class T>
T* Liste<T>::insere(const T& a)
{
	if(this->ptete == NULL)
	{
		this->ptete = new Cellule<T>;
		this->ptete->valeur = a;
		this->ptete->suivant = NULL;
	}
	else
	{
		Cellule<T>* temp;
		temp = new Cellule<T>;
		temp->valeur = a;
		temp->suivant = this->ptete;
		this->ptete = temp;
	}
	return &(this->ptete->valeur);
}

template <class T>
T* Liste<T>::suppresion(const T& a)
{
	Cellule<T> *temp, *tempPrevious = NULL;
	if(this->ptete != NULL)
	{
		temp = this->ptete;
		
		if(a == temp->valeur)
		{
			this->ptete = temp->suivant;
			delete temp;
			cout << "Cet élément a été supprimé avec succès !" << endl;
			return &(temp->valeur);
		}
		
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
Cellule<T>* Liste<T>::Recherche(const T& a)
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
	cout << "Il n'y a rien dans la liste !" << endl;
	return NULL;
}

template <class T>
void Liste<T>::Affiche()
{
	Cellule<T>* save;

	save = this->ptete;
	if(save == NULL)
		cout << "Il n'y a rien a afficher !" << endl;
	while(save != NULL)
	{
		cout << save->valeur << endl;
		save = save->suivant; 
	}
}

template <class T>
bool Liste<T>::estVide()
{
	return ListeBase<T>::estVide();
}

template <class T>
int Liste<T>::getNombreElements() const
{
	return ListeBase<T>::getNombreElements();
}

template <class T>
Cellule<T>& Liste<T>::operator=(const T a)
{
	(*this->ptete).valeur = a;
	return *this->ptete;
}

template <class T>
Cellule<T>& Liste<T>::operator=(Cellule<T>* pt)
{
	this->ptete = pt;
	return *this->ptete;
}

template class Liste<int>;
template class Liste<Couleur>;
template class Liste<SmartPointer<int> >;
