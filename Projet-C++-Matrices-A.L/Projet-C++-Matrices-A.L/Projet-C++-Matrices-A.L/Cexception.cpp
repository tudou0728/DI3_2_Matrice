#pragma once
#include"Cexception.h"

using namespace std;

Cexception::Cexception()
{
	eErreur=0;
}

Cexception::Cexception(int arg)
{
	eErreur=arg;
}

int &Cexception::CEXLireErreur()
{
	return eErreur;
}

void Cexception:: CEXOuvreFile()
{
	cout<<"Erreur:Ne peux pas ouvrir:le chemin de fichier n'est pas correct"<<"\n";
}

void Cexception::CEXType()
{
	cout<<"Erreur:Le type de matrice est incorrect,il faut <<double>>"<<"\n";
}

void Cexception::CEXFileType()
{
	cout<<"Erreur:Le contenu de fichier est incorrect,verifiez votre fichier,SVP"<<"\n";
}

void Cexception::CEXCalculer()
{
	cout<<"Erreur:Il est en contradiction avec les regles de math"<<"\n";
}
void Cexception::CEXErreurGeneral()
{
	cout<<"Erreur:Erreur de la memoire"<<"\n";
}