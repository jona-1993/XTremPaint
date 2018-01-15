#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BaseException.h"

using namespace std;

BaseException::BaseException()
{
	message = new char[20];
	strcpy(message, "Id Invalide !");
	#ifdef DEBUG
	cout << "Fin constructeur par défaut BaseException" << endl;
	#endif
}

BaseException::BaseException(const char* m)
{
	message = new char[strlen(m) + 1];
	strcpy(message, m);
	#ifdef DEBUG
	cout << "Fin constructeur d'initialisation' BaseException 1" << endl;
	#endif
}

const char* BaseException::getMessage()
{
	return message;
}


