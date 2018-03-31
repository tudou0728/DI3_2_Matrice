#pragma once
#include <iostream>

class Cexception
{
   private:
	   int eErreur;

   public:
	   Cexception();
	   Cexception(int arg);
	   
	   int &CEXLireErreur();
	   void CEXOuvreFile(); 
	   void CEXType(); 
	   void CEXFileType(); 
	   void CEXCalculer(); 
	   void CEXErreurGeneral(); 
};

