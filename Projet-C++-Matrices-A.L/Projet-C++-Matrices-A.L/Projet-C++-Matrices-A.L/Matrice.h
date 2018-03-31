#pragma once
#include<iostream>
#include"stdio.h"
#include"Cexception.h"
#include<fstream>
#include <stdlib.h>
#include <cmath>
#include "mystring.h"
#include <iomanip>
#pragma once

using namespace std;

template <typename MType>class CMatrice{

private:
	char *pcMATTypeMatrice; 
	int eMATLignes;
	int eMATColonnes;
	MType **pMATMatrice;

public:
	CMatrice<MType>();
	~CMatrice<MType>();
	CMatrice<MType>(CMatrice<MType> &MATarg);

	void MATModifierType(char* pcTypeArg);
	void MATModifierLigne(int eLigne);
	void MATModifierColonne(int eColonne);
	void MATModifierMatrice(MType **MTYMatrice);
	
	 
	typename CMatrice<MType>& MATMultiplier(MType &MTYvalue);
	typename CMatrice<MType>& MATDiviser(MType &MTYvalue);
	typename CMatrice<MType>& MATTransposer();
	typename CMatrice<MType>& operator+(CMatrice<MType> &MATarg);
	typename CMatrice<MType>& operator-(CMatrice<MType> &MATarg);
	typename CMatrice<MType>& operator*(CMatrice<MType> &MATarg);

    void MATAffichier(); 
	CMatrice<double>& MATLire(char *pcFileNom);
};


template <typename MType> CMatrice<MType>::CMatrice(){
	pcMATTypeMatrice=NULL;
	eMATLignes=0;
	eMATColonnes=0;
	pMATMatrice=NULL;
}

template <typename MType> CMatrice<MType>::~CMatrice(){
	for(int i=0;i<eMATLignes;i++)
	{
		delete pMATMatrice[i];
	}
	delete pMATMatrice;
	delete pcMATTypeMatrice;
}

template <typename MType> CMatrice<MType>::CMatrice( CMatrice<MType> &MATarg){
	eMATLignes=MATarg.eMATLignes;//private成员不可访问 这里写错了
	eMATColonnes=MATarg.eMATColonnes;//private成员不可访问 这里写错了
	pcMATTypeMatrice=MATarg.pcMATTypeMatrice;//private成员不可访问 这里写错了
	if(MATarg.pMATMatrice!=NULL)
	{
		pMATMatrice=new MType*[MATarg.eMATLignes];//深拷贝
		for(int i=0;i<MATarg.eMATLignes;i++){
			pMATMatrice[i]=new MType[MATarg.eMATColonnes];
			for(int j=0;j<eMATColonnes;j++){
				(pMATMatrice[i][j])=(MATarg.pMATMatrice[i][j]);}
		}
		
	} 
	else
	{
		Cexception a(5);
		throw a;
	}
}

template <typename MType> void CMatrice<MType>::MATModifierType(char*pcTypeArg)
{
	pcMATTypeMatrice=pcTypeArg;
}

template <typename MType> void CMatrice<MType>::MATModifierLigne(int eLigne)
{
	eMATLignes=eLigne;
}

template <typename MType> void CMatrice<MType>::MATModifierColonne(int eColonne)
{
	eMATColonnes=eColonne;
}

template <typename MType> void CMatrice<MType>::MATModifierMatrice(MType **MTYMatrice)
{
	pMATMatrice=MTYMatrice; //这里写错了，应该采用深拷贝，但是程序中采用了浅拷贝。
}


//加法
template <typename MType> CMatrice<MType>
typename& CMatrice<MType>::MATMultiplier(MType &MTYvalue){
	CMatrice<MType> *MATTemp=new CMatrice<MType>(*this);
	int i;
	for(i=0;i<eMATLignes;i++){
		int j;
		for(j=0;j<eMATColonnes;j++){
			(MATTemp->pMATMatrice[i][j])=(MATTemp->pMATMatrice[i][j])*MTYvalue;
		}
	}
	return *MATTemp;
}	
//除法
template <typename MType> CMatrice<MType>
typename &CMatrice<MType>::MATDiviser(MType &MTYvalue){
	CMatrice *MATTemp=new CMatrice<MType>(*this);
	if(MTYvalue!=0)
	{
	   int i;
	   for(i=0;i<eMATLignes;i++)
	   {
		int j;
		for(j=0;j<eMATColonnes;j++)
		{
			MATTemp->pMATMatrice[i][j]=MATTemp->pMATMatrice[i][j]/MTYvalue;
		}
	   }
	}
	else
	{
		Cexception a(4);
		throw a;
	}
	return *MATTemp;
}	
//转置
template <typename MType> CMatrice<MType>
typename &CMatrice<MType>::MATTransposer(){
	CMatrice *MATTemp=new CMatrice<MType>();
	MATTemp->MATModifierLigne(eMATColonnes);
	MATTemp->MATModifierColonne(eMATLignes);
	MATTemp->MATModifierType(pcMATTypeMatrice);
	if(pMATMatrice!=NULL)
	{
		MATTemp->pMATMatrice=new MType*[eMATColonnes];
		for(int i=0;i<eMATColonnes;i++)
		{
			MATTemp->pMATMatrice[i]=new MType[eMATLignes];
			for(int j=0;j<eMATLignes;j++)
			{
				(MATTemp->pMATMatrice[i][j])=(pMATMatrice[j][i]);
			}
		}	
	}
	return *MATTemp;
}


//矩阵相加
template <typename MType> CMatrice<MType>
typename &CMatrice<MType>:: operator+(CMatrice<MType> &MATarg){
	CMatrice *MATTemp=new CMatrice<MType>(*this);
	if(MATTemp->eMATLignes==MATarg.eMATLignes && MATTemp->eMATColonnes==MATarg.eMATColonnes)
	{
	int i;
	for(i=0;i<eMATLignes;i++){
		int j;
		for(j=0;j<eMATColonnes;j++){
			MATTemp->pMATMatrice[i][j]=MATTemp->pMATMatrice[i][j]+MATarg.pMATMatrice[i][j];
		}
	}
	return *MATTemp;
	}
	else
	{
		Cexception a(4);
		throw a;
	}  
}

//矩阵相减
template <typename MType> CMatrice<MType>
typename &CMatrice<MType>:: operator-(CMatrice<MType> &MATarg){
	CMatrice *MATTemp=new CMatrice<MType>(*this);
	//MATTemp=CMatrice<MType>(this);
	if(MATTemp->eMATLignes==MATarg.eMATLignes&&MATTemp->eMATColonnes==MATarg.eMATColonnes)
	{
	int i;
	for(i=0;i<eMATLignes;i++)
	{
		int j;
		for(j=0;j<eMATColonnes;j++)
		{
			MATTemp->pMATMatrice[i][j]=MATTemp->pMATMatrice[i][j]-MATarg.pMATMatrice[i][j];
		}
	}
	return *MATTemp;
	} 
	else
	{
		Cexception a(4);
		throw a;
	}
}

//矩阵相乘
template <typename MType> CMatrice<MType>
typename &CMatrice<MType>:: operator*(CMatrice<MType> &MATarg)
{
	CMatrice *MATTemp=new CMatrice<MType>();
	MATTemp->MATModifierType(this->pcMATTypeMatrice);
	MATTemp->MATModifierLigne(this->eMATLignes);
	MATTemp->MATModifierColonne(MATarg.eMATColonnes);//这里写错了 私有成员不可访问
	MATTemp->pMATMatrice=new MType*[MATTemp->eMATLignes];//这里写错了 私有成员不可访问
	if(this->eMATColonnes==MATarg.eMATLignes)//这里写错了 私有成员不可访问
	{
		int i;
		for(i=0;i<MATTemp->eMATLignes;i++)
		{
			int j;
			MATTemp->pMATMatrice[i]=new MType[MATTemp->eMATColonnes];
			for(j=0;j<MATTemp->eMATColonnes;j++)
			{
				MType dtemp=0;
				int n;
				for(n=0;n<this->eMATColonnes;n++)
				{
					dtemp=dtemp + this->pMATMatrice[i][n] * MATarg.pMATMatrice[n][j];
				}
				MATTemp->pMATMatrice[i][j]=dtemp;
		     }
	     }
		return  *MATTemp;
	}
	else
	{
		Cexception a(4);
		throw a;
	}
}
//打印矩阵
template <typename MType> void CMatrice<MType>::MATAffichier(){
	int i;
	for(i=0;i<eMATLignes;i++){
		int j;
		for(j=0;j<eMATColonnes;j++){
			cout.width(20);
			cout<<std::left<<setw(15)<<setprecision(8)<<this->pMATMatrice[i][j]<<"\t";
			
		}		
		cout<<"\n";
	}
}
//读文件
template <typename MType> CMatrice<double> &CMatrice<MType>:: MATLire(char* pcFileNom)
{
	fstream file(pcFileNom,ios::in|ios::out);//初始化
	if (!file.is_open())//打开文件
	{ 
		Cexception a(1);
		throw a;
	} 
	else
	{
		char cTemp[10000]={'a'};
		file.seekg(0,ios::beg);
		file.getline(cTemp,90,'\n');
		if(!ComparerStringAvecLong(cTemp,"TypeMatrice=",TailleDeString("TypeMatrice=")))
		{ 
			Cexception a(3);
		    throw a;
		}
		if(!ComparerStringAvecLong(cTemp,"TypeMatrice=double",TailleDeString("TypeMatrice=double")))
		{ 
			Cexception a(2);
		    throw a;
		}
		else
		{
			//type 只可接收double型的矩阵
			this->MATModifierType("double");
			//lignes
			file.getline(cTemp,90,'\n');
			if(!ComparerStringAvecLong(cTemp,"NBLignes=",TailleDeString("NBLignes=")-1))
	        { 
		      Cexception a(3);
		      throw a;  
	        }
			int i=0;
	        while(cTemp[i] != '=')
	       {
	  	      i++;	
	        }
	        i++;
	        int eLigneTemp=0;
	        int eCompte=i;
	        while(cTemp[eCompte] != '\0')
	       {
	          eCompte++;
	        }
	        eCompte=eCompte-i;
	        for(int x=0;x<eCompte;x++)
	       { 
		      eLigneTemp=eLigneTemp+(int(cTemp[i])-48)*pow(10,eCompte-1-x);
		      i++;
	        }
	        this->MATModifierLigne(eLigneTemp);
			//colonnes
			file.getline(cTemp,50,'\n');
	        if(!ComparerStringAvecLong(cTemp,"NBColonnes=",TailleDeString("NBColonnes=")-1))
	        { 
		       Cexception a(3);
		      throw a;
	         }
	          int j=0;
	          while(cTemp[j] != '=')
	        {
		       j++;	
	         }
	           j++;
	         int eColonneTemp=0;
	         int eCompte2=j;
	         while(cTemp[eCompte2] != '\0')
	         {
	            eCompte2++;
	         }
	          eCompte2=eCompte2-j;
	         for(int y=0;y<eCompte2;y++)
	         { 
		       eColonneTemp=eColonneTemp+(int(cTemp[j])-48)*pow(10,eCompte2-1-y);
		       j++;
	         }
	         this->MATModifierColonne(eColonneTemp);
			 //lire le contenu de matrice
			 file.getline(cTemp,100,'\n');
	         if(!ComparerStringAvecLong(cTemp,"Matrice=[",TailleDeString("Matrice=[")-1))
	        { 
		        Cexception a(3);
		        throw a; 
	        }
			 pMATMatrice=new double*[eMATLignes];
			 for(int m=0;m<eMATLignes;m++)
			 {
				 file.getline(cTemp,10000,'\n');
				 pMATMatrice[m]=new double[eMATLignes];
				 if(cTemp[0] == ']')
	            {
		           Cexception a(3);
		           throw a;
	             }
                  int p=0;//pour temp
	              for(int n=0;n<eMATColonnes;n++)
				  {
					  pMATMatrice[m][n]=0;
					  int q=0;//pour pcTempDouble
					  char pcTempDouble[10000]={'a'};
		              while(cTemp[p] != char(32) && cTemp[p] != '\0' && cTemp[p] != '\n')
		              {
			             pcTempDouble[q]=cTemp[p];
			               q++;
			               p++;
		              }
		               pcTempDouble[q]='\0';
		               p++;
		               if((pcTempDouble[0]<char(48) && pcTempDouble[0]>char(45)) || pcTempDouble[0]>char(57) || pcTempDouble[0]<char(45))
		              {
			              Cexception a(3);
		                  throw a;
		               }
					   int c=0;//pour point
		               int s=0;
		               if(pcTempDouble[0] !='-' )
                       {	  
			              while(pcTempDouble[s] != char(46) && pcTempDouble[s] != '\0')
		                {
			               c++;
		                   s++;
		                 }
		                 int w=0;
		                 while(pcTempDouble[w] != char(46) && pcTempDouble[w] != '\0')
		                {
			              pMATMatrice[m][n]= pMATMatrice[m][n]+(double(pcTempDouble[w])-48) * pow(10,c-1-w);
			              w++;
		                }
		                w++;
		                while(w<q)
		               {
			             pMATMatrice[m][n]= pMATMatrice[m][n]+(double(pcTempDouble[w])-48) * pow(10,c-w);
			             w++;
		                }
		              }
					   else
					   {
		                      s++;
		                      while(pcTempDouble[s] != char(46) && pcTempDouble[s] != '\0')
		                     {
			                      c++;
		                          s++;
		                      }
		                      int w=1;
		                      while(pcTempDouble[w] != char(46) && pcTempDouble[w] != '\0')
		                     {
			                    pMATMatrice[m][n]= pMATMatrice[m][n]+(double(pcTempDouble[w])-48) * pow(10,c-w);
			                    w++;
		                      }
		                      w++;
		                      while(w<q)
		                     {
			                  pMATMatrice[m][n]= pMATMatrice[m][n]+(double(pcTempDouble[w])-48) * pow(10,c+1-w);
			                  w++;
		                     }
		                      pMATMatrice[m][n]=pMATMatrice[m][n]*(-1);
		                 }
				    }
				   // pMATMatrice[m]=(dMATTemp);
				  }
			 }
			 //cout <<"reussir"<<"\n";
			 file.close();
			 return *this;
	}
	
}



