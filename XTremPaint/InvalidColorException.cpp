#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "InvalidColorException.h"

using namespace std;

InvalidColorException::InvalidColorException()
{
	#ifdef DEBUG
	cout << "Fin constructeur par défaut InvalidColorException" << endl;
	#endif
}

InvalidColorException::InvalidColorException(const char* m, const bool r, const bool v, const bool b)
{
	rouge = r;
	vert = v;
	bleu = b;
	
	if(m != NULL)
	{
		message = new char[strlen(m) + 1];
		strcpy(message, m);
	}
	
	#ifdef DEBUG
	cout << "Fin constructeur d'initialisation' InvalidColorException 1" << endl;
	#endif
}

const bool InvalidColorException::rougeValide()
{
	return rouge;
}

const bool InvalidColorException::vertValide()
{
	return vert;
}

const bool InvalidColorException::bleuValide()
{
	return bleu;
}

const char* InvalidColorException::getMessage()
{
	return message;
}


