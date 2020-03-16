#include<iostream>
#include<string>





#include<windows.h>
#include<tlhelp32.h>



#include"wid.h"


using std::cout;
using std::cin;
using std::endl;
using std::string;

void modify_gold(processinfo* pmirror) {
	wchar_t modulename[] = L"mono.dll";
	DWORD modulebaseaddress, baseaddress, temp;
	unsigned curr_gold, gold;


	modulebaseaddress = pmirror->getModuleBaseAddress(modulename);
	baseaddress = modulebaseaddress + 0x001F8BC8;
	//cout << baseaddress << endl;

	ReadProcessMemory(pmirror->hnd, (PBYTE*)baseaddress, &temp, sizeof(temp), 0);
	//cout << std::hex << temp << endl;
	//ReadProcessMemory(pmirror->hnd, (PBYTE*)temp, &temp, sizeof(temp), 0);
	ReadProcessMemory(pmirror->hnd, (PBYTE*)(temp + 0xa4), &temp, sizeof(temp), 0);
	ReadProcessMemory(pmirror->hnd, (PBYTE*)(temp + 0x4), &temp, sizeof(temp), 0);
	ReadProcessMemory(pmirror->hnd, (PBYTE*)(temp + 0xe4), &temp, sizeof(temp), 0);
	//cout << std::hex << temp << endl;
	ReadProcessMemory(pmirror->hnd, (PBYTE*)(temp + 0x30), &temp, sizeof(temp), 0);
	ReadProcessMemory(pmirror->hnd, (PBYTE*)(temp + 0x610), &temp, sizeof(temp), 0);
	ReadProcessMemory(pmirror->hnd, (PBYTE*)(temp + 0x130), &temp, sizeof(temp), 0);
	temp = temp + 0x4c;
	//cout << std::hex << temp << endl;
	//ReadProcessMemory(hnd, (PBYTE*)(temp + 8), &temp, sizeof(temp), 0);
	ReadProcessMemory(pmirror->hnd, (PBYTE*)temp, &curr_gold, sizeof(curr_gold), 0);
	cout << "当前金钱为：" << curr_gold << endl;
	//system("pause");
	cout << "请输入修改数值：" << endl;
	cin >> gold;
	cout << "正在修改....." << endl;
	WriteProcessMemory(pmirror->hnd, (PBYTE*)temp, &gold, sizeof(gold), 0);
	cout << "修改完毕！数值暂时不会改变，请立即消费，否则修改不会生效！" << endl;




}


void torn(processinfo* pmirror) {

	unsigned char arrayofbytes[] = { 0x83,0xC4,0x10,0x8B,0xC8,0x8B,0x45,0xDC,0x3B,0xC1,0x0F,0x8D,0xBC };
	DWORD writem1, writem2, writem3, writem4, address_m;



	address_m = pmirror->getAOB_Address(arrayofbytes);
	writem1 = 0xE9;
	writem2 = 0xBD;
	writem3 = 0x00;
	writem4 = 0x90;

	cout << "正在修改...." << endl;

	WriteProcessMemory(pmirror->hnd, (PBYTE*)(address_m + 10), &writem1, 1, 0);
	WriteProcessMemory(pmirror->hnd, (PBYTE*)(address_m + 11), &writem2, 1, 0);
	WriteProcessMemory(pmirror->hnd, (PBYTE*)(address_m + 12), &writem3, 1, 0);
	WriteProcessMemory(pmirror->hnd, (PBYTE*)(address_m + 15), &writem4, 1, 0);
	cout << "修改完成！若要恢复原本的游戏规则，请重启游戏！" << endl;

	system("pause");



}

void kill_in_one_hit(processinfo* pmirror) {

	wchar_t modulename[] = L"mono.dll";
	DWORD add, temp, i = 1;
	add = pmirror->getModuleBaseAddress(modulename);
	//cout << std::hex << add << endl;
	add = add + 0x001F4680;

	ReadProcessMemory(pmirror->hnd, (PBYTE*)add, &temp, sizeof(temp), 0);
	ReadProcessMemory(pmirror->hnd, (PBYTE*)(temp + 0x28), &temp, sizeof(temp), 0);
	ReadProcessMemory(pmirror->hnd, (PBYTE*)(temp + 0x34), &temp, sizeof(temp), 0);
	ReadProcessMemory(pmirror->hnd, (PBYTE*)(temp + 0x8), &temp, sizeof(temp), 0);
	ReadProcessMemory(pmirror->hnd, (PBYTE*)(temp + 0x5c), &temp, sizeof(temp), 0);
	ReadProcessMemory(pmirror->hnd, (PBYTE*)(temp + 0x18), &temp, sizeof(temp), 0);
	ReadProcessMemory(pmirror->hnd, (PBYTE*)(temp + 0x48), &temp, sizeof(temp), 0);
	temp = temp + 0x24;
	WriteProcessMemory(pmirror->hnd, (PBYTE*)temp, &i, sizeof(i), 0);
	cout << "修改完成，下次攻击秒杀！只能生效一次！若要继续秒杀请继续使用本选项！" << endl;
	//system("pause");
}

int main() {



	string windowname = "mirror";
	processinfo pmirror;
	//HANDLE hnd;
	int op;





	pmirror.windowname = windowname;
	pmirror.setall();





	cout << "successfully open process!" << endl;
	system("pause");
	system("cls");

	while (1) {
		cout << "菜单（请在打开游戏后再启动本程序！）" << endl;
		cout << "1、修改金钱（请进入存档后再进行修改！）" << endl;
		cout << "2、一击爆衣（请保证在战斗界面并至少对人物至少进行一次攻击后再尝试！）" << endl;
		cout << "3、一击必杀（请保证在战斗界面！下一次攻击秒杀！只能生效一次！）" << endl;
		cout << "4、退出" << endl;
		cout << "！！！！！！注意！！！！！！" << endl;
		cout << "请一定按照提示来，否则出错概不负责!" << endl;
		cout << "请一定按照提示来，否则出错概不负责!" << endl;
		cout << "请一定按照提示来，否则出错概不负责!" << endl;


		cout << "请输入操作数字并回车：" << endl;
		cin >> op;
		switch (op) {
		case 1: {


			modify_gold(&pmirror);

		}; break;

		case 2: {

			torn(&pmirror);
		}; break;

		case 3: {kill_in_one_hit(&pmirror); }; break;

		case 4: {exit(0); }; break;

		default:break;

		}

		system("pause");
		system("cls");




	}
	CloseHandle(pmirror.hnd);



	//cout << 1 << endl;

	return 0;
}