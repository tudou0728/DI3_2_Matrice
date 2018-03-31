#pragma once
#include <iostream>
#include "stdio.h"
#include "Cexception.h"
#include <fstream>
#include <stdlib.h>
#include <cmath>


using namespace std;

bool ComparerStringAvecLong(char*str1, char*str2,int eLength){
     if(str1==NULL||str2==NULL)
	 {
		 cout<<"ne peut pas utiliser cette function"<<"\n";
	 }
	 else
	 {
		int i=0;
		while(str1[i]!='\0' && str2[i]!='\0' &&  i<=eLength-1)
        {
            if(str1[i] != str2[i])
			{
				return false;
				break;
			}
			i++;
        }
		return true;
	 }
}

int TailleDeString(char* str);
bool ComparerAvecString(char*str1, char*str2)
{ 
	if(str1==NULL||str2==NULL)
	 {
		 cout<<"Ne peut pas utiliser cette function"<<"\n";
	 }
	 else
	 {
		 if(TailleDeString(str1) != TailleDeString(str2))
		 {
			 return false;
		 }
		int i=0;
		while(str1[i]!='\0' && str2[i]!='\0')
        {
            if(str1[i] != str2[i])
			{
				return false;
				break;
			}
			i++;
	   }
		return true;
	}
}

int TailleDeString(char* str){
	int count=0;
	int i=0;
	while(str[i] != '\0')
	{count++;
	i++;}
	return count;
}
