#pragma once
#include <iostream>
#include <fstream>
#include "stdlib.h"
#include "Matrice.h"
#include "Cexception.h"
#include <cmath>

using namespace std;


int main(int argc, char *argv[])
{
	try{
	char pcBoucle[100]={'a'};
	CMatrice<double> *Matrice=new CMatrice<double>();
	
	while(!ComparerAvecString(pcBoucle,"quitter"))
   {
	  for(int i=1;i<argc;i++)
	  {
		  //matrice originale
	    cout<<"La  matrice originale est:"<<"\n";
		Matrice=&(Matrice->MATLire(argv[i]));
	    Matrice->MATAffichier();
		cout<<"------------------------------------------"<<"\n";
	    CMatrice<double> *MATTemp=new CMatrice<double>(*Matrice);
	  //transposer
	    
	    cout<<"Transposer:le resultat de Matrice est:"<<"\n";
		MATTemp=&(MATTemp->MATTransposer());
	    MATTemp->MATAffichier();
		cout<<"------------------------------------------"<<"\n";
	 }
	  cout<<"Ecrir une constante pour multipier et diviser:"<<"\n";
	  double a;
	  cin>>a;
	  for(int i=1;i<argc;i++)
	   {
		Matrice=&(Matrice->MATLire(argv[i]));
	    CMatrice<double> *MATTemp=new CMatrice<double>(*Matrice);
	  //Multiplier
	    cout<<"Multiplier:le resultat de Matrice est:"<<"\n";
		MATTemp=&(Matrice->MATMultiplier(a));
	    MATTemp->MATAffichier();
		cout<<"------------------------------------------"<<"\n";
	  //Diviser
	    cout<<"Diviser:le resultat de Matrice est:"<<"\n";
		MATTemp=&(Matrice->MATDiviser(a));
	    MATTemp->MATAffichier();
		cout<<"------------------------------------------"<<"\n";
	   }
	   //L'addition
	  if(argc == 2)
	  {
		  Matrice=&(Matrice->MATLire(argv[1]));
		  CMatrice<double> *MATTemp=new CMatrice<double>(*Matrice);
		  MATTemp=&(*Matrice + *MATTemp);
		  cout<<"l'addition:le resultat de Matrice est£º"<<"\n";
	      MATTemp->MATAffichier();
		  cout<<"------------------------------------------"<<"\n";
	  }
	  else
	  {
	    cout<<"L'addition:le resultat de Matrice est:"<<"\n";
		  Matrice=&(Matrice->MATLire(argv[1]));
		CMatrice<double> *MATTemp=new CMatrice<double>(*Matrice);
		for(int j=2;j<argc;j++)
	    {
		  Matrice=&(Matrice->MATLire(argv[j]));
		  MATTemp=&(*Matrice + *MATTemp);
	    }
	    MATTemp->MATAffichier();
		cout<<"------------------------------------------"<<"\n";
	  }
	  //soustraction
	  cout<<"L'addition et soustraction:le resultat de Matrice est:"<<"\n";
	  Matrice=&(Matrice->MATLire(argv[1]));
	  CMatrice<double> *MATTemp=new CMatrice<double>(*Matrice);
	  if(argc==2)
	  {
		  MATTemp=&(*MATTemp - *Matrice);
	  }	  
      else  
	  { 
		  for(int m=2;m<argc;m++)
	    {
		  Matrice=&(Matrice->MATLire(argv[m]));
		  if(m%2==0)
		  {
		     MATTemp=&(*MATTemp - *Matrice);
		  }
		  else
		  {
			  MATTemp=&(*MATTemp + *Matrice);
		  }
	    }
	    MATTemp->MATAffichier();
		cout<<"------------------------------------------"<<"\n";
	  }
		//Le produit
	  cout<<"Le produit:le resultat de Matrice est:"<<"\n";
	  Matrice=&(Matrice->MATLire(argv[1]));
	  MATTemp=Matrice;
	  //CMatrice<double> *MATTemp=new CMatrice<double>(*Matrice);
	  if(argc==2)
	  {
		  Cexception a(4);
		  throw a;
	  }	  
      else  
	  { 
		 for(int m=2;m<argc;m++)
	    {
		  Matrice=&(Matrice->MATLire(argv[m]));
		  MATTemp=&((*MATTemp)*(*Matrice));
	    }
	    MATTemp->MATAffichier();
		cout<<"------------------------------------------"<<"\n";
	  }
	  cout<<"continuer ou quitter?"<<"\n";
	  cin>>pcBoucle;
  }
}
	catch(Cexception a)
	{
		//char *erreur=&(Erreur.CEXLireErreur());
		if(a.CEXLireErreur() == 1)
		{ a.CEXOuvreFile();}
		if(a.CEXLireErreur() == 2)
		{ a.CEXType();}
		if(a.CEXLireErreur() == 3)
		{ a.CEXFileType();}
		if(a.CEXLireErreur() == 4)
		{ a.CEXCalculer();}
		if(a.CEXLireErreur() == 5)
		{ a.CEXErreurGeneral();}
	}
	exit(1);
}