#pragma once

#include<iostream>
#include<string>



#include<windows.h>
#include<tlhelp32.h>
#include<psapi.h>
#include<tchar.h>


using std::cout;
using std::cin;
using std::endl;
using std::string;


class processinfo {

public:
	string windowname;



	DWORD pid;

	HANDLE hnd;

	//unsigned char[]

	DWORD getModuleBaseAddress(wchar_t* name);

	//int setModuleBaseAddress(char* name);



	DWORD getAOB_Address(unsigned char* arrayofbytes);

	void setall();


private:

	void getPidFromName(string name);



	//DWORD pid;





};