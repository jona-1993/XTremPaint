#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
//#include "Couleur.h"
#include "Forme.h"
#include "Rectangle.h"
#include "Ligne.h"
#include "SmartPointer.h"

using namespace std;

template <class T>
SmartPointer<T>::SmartPointer()
{
	val = NULL;
	
	#ifdef DEBUG
		cerr << "Fin Constructeur par défaut SmartPointer" << endl;
	#endif
}

template <class T>
SmartPointer<T>::SmartPointer(T* arg)
{
	val = arg;
	
	#ifdef DEBUG
		cerr << "Fin Constructeur d'init 1 SmartPointer" << endl;
	#endif
}

template <class T>
SmartPointer<T>::SmartPointer(T& arg)
{
	val = &arg;
	
	#ifdef DEBUG
		cerr << "Fin Constructeur Copie SmartPointer" << endl;
	#endif
}

template <class T>
SmartPointer<T>::~SmartPointer()
{
	
	#ifdef DEBUG
		cerr << "Fin Destructeur SmartPointer" << endl;
	#endif
}

template <class T>
void SmartPointer<T>::Delete()
{
	if(val != NULL)
		delete val;
}

template <class T>
T* SmartPointer<T>::getVal() const
{
	return val;
}


template <class T>
T& SmartPointer<T>::operator=(const T& arg)
{
	
	*val = arg;
	
	return *val;
}

template <class T>
SmartPointer<T>& SmartPointer<T>::operator=(const SmartPointer<T>& arg)
{
	val = arg.getVal();
	
	return *this;
}

template <class T>
bool operator==(const SmartPointer<T>& a, const SmartPointer<T>& b)
{
	if(*(a.getVal()) == *(b.getVal()))
	{
		return 1;
	}
	
	return 0;
}

template <class T>
bool operator!=(const SmartPointer<T>& a, const SmartPointer<T>& b)
{
	if(*(a.getVal()) != *(b.getVal()))
	{
		return 1;
	}
	
	return 0;
}

template <class T>
bool operator<(const SmartPointer<T>& a, const SmartPointer<T>& b)
{
	if(*(a.getVal()) < *(b.getVal()))                           /////////////////////////////////////////////
	{
		return true;
	}
	
	return false;


}


template <class T>
bool operator>(const SmartPointer<T>& a, const SmartPointer<T>& b)
{
	if(!(*(a.getVal()) < *(b.getVal())))
	{
		return 1;
	}
	
	return 0;


}

template <class T>
T& SmartPointer<T>::operator*()
{
	return *val;
}

template <class T>
T* SmartPointer<T>::operator->() const
{
	return val;
}

template <class T>
ostream& operator<<(ostream& s, const SmartPointer<T>& a)
{
	s << *(a.getVal());
	return s;
}


template class SmartPointer<int>;
template class SmartPointer<Ligne>;
template class SmartPointer<Rectangle>;
template class SmartPointer<Forme>;
template class SmartPointer<Couleur>;

template bool operator==(const SmartPointer<int>&, const SmartPointer<int>&);
template bool operator!=(const SmartPointer<int>&, const SmartPointer<int>&);
template bool operator<(const SmartPointer<int>&, const SmartPointer<int>&);
template bool operator>(const SmartPointer<int>&, const SmartPointer<int>&);
template std::ostream& operator<<(std::ostream&, const SmartPointer<int>&);

template bool operator==(const SmartPointer<Forme>&, const SmartPointer<Forme>&);
template bool operator!=(const SmartPointer<Forme>&, const SmartPointer<Forme>&);
template bool operator<(const SmartPointer<Forme>&, const SmartPointer<Forme>&);
template bool operator>(const SmartPointer<Forme>&, const SmartPointer<Forme>&);
template std::ostream& operator<<(std::ostream&, const SmartPointer<Forme>&);
