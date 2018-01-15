#ifndef INVALIDCOLOREXCEPTION_H
#define INVALIDCOLOREXCEPTION_H

#include "BaseException.h"

class InvalidColorException
{
	private:
		char* message;
		bool rouge;
		bool vert;
		bool bleu;
	public:
		InvalidColorException();
		
		InvalidColorException(const char*,const bool,const bool,const bool);
		
		
		const bool rougeValide();
		const bool vertValide();
		const bool bleuValide();
		
		const char* getMessage();

};

#endif
