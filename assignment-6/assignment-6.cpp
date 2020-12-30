/******************************************************
** Program: assignment6.cpp

** Author: Jia Hao

** Date: 03/17/2019

** Description: simulate the diffusion of heat through a 1-D or 2-D object, such as a wire or plate, using the explicit method to solve for new time instances

** Input: thermal conductivity, material density, specific heat capacity of material, object, location, time, temp 

** Output:  the rate of change in heat over time.	
******************************************************/ 
#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>

using namespace std;


//error handle 1 or 2
int check(){
	bool error;
	int z;
	string x;
	do{
		error=false;
		cin>>x;
		for(int i=0;i<x.size();i++){
			if(!(x.at(i)=='1' || x.at(i)=='2')){
				cout<<"error number!"<<endl;
				error=true;
				i=x.size();
			}
		}
	}while(error);
	z=atoi(x.c_str());
	return z;
}


//error handle integer number 
int check_int(){
	bool error;
	string x;
	int w;
	do{
		error=false;
		cin>>x;
		for(int i=0;i<x.size();i++){
			if(!(x.at(i)>='0' && x.at(i)<='9')){
				cout<<"error number!"<<endl;
				error=true;
				i=x.size();
			}
		}	
	}while(error);
	w=atoi(x.c_str());
	return w;
}


//error handle the number of points
bool point(string x){
	int count=0;
	for(int i=0;i<x.size();i++){
		if(x.at(i)=='.')
			count++;
	}
	if(count>1)
		return false;
	else
		return true;
}


//error handle double number 
double  check_double(){
	bool error;
	double y;
	string x;
	int count=0,z=0;
	do{
		error=false;
		cin>>x;
		for(int i=0;i<x.size();i++){
			if(!((x.at(i)>='0' && x.at(i)<='9') || x.at(i)=='.')){
				cout<<"error number!"<<endl;
				error=true;
				i=x.size();
			}
		}
		z=point(x);
		if(z==0){
			error=true;
			cout<<"error number!"<<endl;
		}
	}while(error);
	y=atof(x.c_str());
	return y;	
}


//check the wire stable or unstable 
bool check_stable_1(int interval,int sec, float k,float rho, float c,float len,float time){
	float result;
	result=fabs((k*(time/interval))/((pow((len/sec),2))*c*rho));
	if(result>=0.5){
		cout<<"material is unstable"<<endl;
		return false;
	}
	else{
		cout<<"material is stable"<<endl;
		return true;
	}
	
}


//check the plate stable or unstable 
bool check_stable_2(int interval,int sec, float k,float rho, float c,float len,float time){
	float result,s;
	s=time/interval;
	result=((pow((len/sec),2))*c*rho)/(4*k);
	if(result>=s){
		cout<<"material is stable"<<endl;
		return true;
	}
	else{
		cout<<"material is unstable"<<endl;
		return false;
	}
	
}


//calculate the heat transfer model of wire
void wire(float *a,int interval,int sec,float k,float rho,float c,float len,float time){
	float b[interval][sec];
	for(int i=0;i<sec;i++){
		b[0][i]=a[i];
	}
	for(int i=0;i<interval;i++)
		b[i][0]=0;

	for(int i=0;i<interval;i++)
		b[i][sec-1]=100;

	for(int i=1;i<interval;i++){
		for(int j=1;j<sec-1;j++){
			b[i][j]=(k*(time/interval)*(b[i-1][j+1]-2*b[i-1][j]+b[i-1][j-1])) / (pow((len/sec),2)*c*rho)+b[i-1][j];
		}
	}
	for(int i=0;i<interval;i++){
		for(int j=0;j<sec;j++){
			cout<<b[i][j]<<" ";
		}
	cout<<endl;
	}
}


//calculate the heat transfer model of plate 
void plate(float **a,int interval,int sec,float k,float rho,float c,float len,float time){
	float b[interval][sec][sec];
	for(int i=1;i<sec-1;i++)
		for(int j=0;j<sec-1;j++)
		b[0][i][j]=a[i][j];
	
	for(int i=0;i<sec;i++){
		b[0][i][0]=100;
		b[0][i][sec-1]=100;
		b[0][0][i]=100;
		b[0][sec-1][i]=100;
	}
	for(int l=1;l<interval;l++){
		for(int i=0;i<sec;i++){
			b[l][i][0]=100;
			b[l][i][sec-1]=100;
			b[l][0][i]=100;
			b[l][sec-1][i]=100;
		}
	}
	for(int l=1;l<interval;l++){
		for(int i=1;i<sec-1;i++){
			for(int j=1;j<sec-1;j++){
				b[l][i][j]=((k*(time/interval)*(b[l-1][i+1][j]-2*b[l-1][i][j]+b[l-1][i-1][j]+b[l-1][i][j+1]-2*b[l-1][i][j]+b[l-1][i][j-1])) / (pow((len/sec),2)*c*rho))+b[l-1][i][j];
			}
		}
	}
	for(int l=0;l<interval;l++){
		for(int i=0;i<sec;i++){
			for(int j=0;j<sec;j++){
				cout<<b[l][i][j]<<" ";
			}
			cout<<endl;
		}
	}
}


//get wire tempterature  
void gettemp_1(float k,float rho,float c,float len,int sec,int interval,float time){
	float temp;
	int s;
	float *a=new float [sec];
	cout<<"right temp"<<endl;
	a[sec-1]=check_double();
	cout<<"left temp"<<endl;
	a[0]=check_double();
	cout<<"initial temp"<<endl;
	temp=check_double();
	for(int i=1;i<sec-1;i++)
		a[i]=temp;
	wire(a,interval,sec,k,rho,c,len,time);
	delete [] a;
}


//get plate temperature 
void gettemp_2(float k,float rho,float c,float len,int sec,int interval,float time){
	float t1,t2,temp;
	int s;
	float **a = new float *[interval];
	for(int i=0;i<interval;i++)
		a[i]= new float [sec];
	cout<<"left/right column temp"<<endl;
		t1=check_double();
	for(int i=0;i<interval;i++){
		a[i][0]=t1;
		a[i][sec-1]=t1;
	}
	cout<<"bottom/top row temp"<<endl;
		t2=check_double();
	for(int i=0;i<sec;i++){
		a[0][i]=t2;
		a[sec-1][i]=t2;

	}
	cout<<"initial temp"<<endl;
		temp=check_double();
	
	for(int i=1;i<sec-1;i++)
		for(int j=1;j<sec-1;j++)
		a[i][j]=temp;
	plate(a,interval,sec,k,rho,c,len,time);
	for(int i=0;i<sec;i++)
		delete [] a[i];
	delete [] a; 
}


//declare a function 
void stable(int &s);


//get inputer of wire 
void getline_1(){
	float k,rho,c,len,time,temp;
	int sec,interval,s;
    
	cout<<"enter the themal conductivity:"<<endl;
	k=check_double();
    
	cout<<"enter the material density:"<<endl;
	rho=check_double();
    
	cout<<"specific heat capcaity of material"<<endl;
	c=check_double();
    
	cout<<"the length of material"<<endl;
	len=check_double();
    
	cout<<"section"<<endl;
	sec=check_int();
    
	cout<<"time intervals"<<endl;
	interval=check_int();
    
	cout<<"time of simulation"<<endl;
	time=check_double();
	
	s=check_stable_1(interval,sec,k,rho,c,len,time);
	stable(s);
	gettemp_1(k,rho,c,len,sec,interval,time);
}


//get inputer of plate 
void getline_2(){
	float k,rho,c,len,time,temp;
	int sec,interval,s;
	cout<<"enter the themal conductivity:"<<endl;
	k=check_double();
	cout<<"enter the material density:"<<endl;
	rho=check_double();
	cout<<"specific heat capcaity of material"<<endl;
	c=check_double();
	cout<<"the height and width of material"<<endl;
	len=check_double();
	cout<<"sections across hight/width"<<endl;
	sec=check_int();
	cout<<"time intervals"<<endl;
	interval=check_int();
	cout<<"time of simulation"<<endl;
	time=check_double();
	
	s=check_stable_2(interval,sec,k,rho,c,len,time);
	stable(s);
	gettemp_2(k,rho,c,len,sec,interval,time);
}


//choose 1-D or 2-D
void choose(){
	int u;
	cout<<"Do you want caluculate wire or plate?\n1-wire 2-plate"<<endl;
	u=check();

	if(u==1)
		getline_1();
	if(u==2)
		getline_2();
}


//Determine if the program need to start from scratch
void stable(int &s){
	if(s==0)
		choose();
}

	
int main(){
	int x;
	do{
		choose();	
		cout<<"Do you want to calcualte again?\n1-Yes 2-No"<<endl;
		x=check();
	}while(x==1);
}

