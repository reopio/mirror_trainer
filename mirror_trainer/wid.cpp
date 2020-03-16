#include"wid.h"



void processinfo::getPidFromName(string name) {
    //cout << 1 << endl;
    HWND hnd = FindWindowA(NULL, name.c_str());
    if (hnd == NULL) {
        cout << "cannot find window!" << endl;
        system("pause");
        exit(-1);
    }

    GetWindowThreadProcessId(hnd, &(this->pid));
    //cout << pid << endl;

    CloseHandle(hnd);



}

void processinfo::setall() {
    this->getPidFromName(this->windowname);
    this->hnd = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->pid);

}

DWORD processinfo::getModuleBaseAddress(wchar_t* name) {
    DWORD baseaddress;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, this->pid);
    MODULEENTRY32 ModuleEntry32 = { 0 };
    ModuleEntry32.dwSize = sizeof(MODULEENTRY32);

    if (Module32First(hSnapshot, &ModuleEntry32))
    {
        do {
            if (_tcscmp(ModuleEntry32.szModule, name) == 0)
            {
                baseaddress = (DWORD)ModuleEntry32.modBaseAddr;
                return baseaddress;
                //this->size = ModuleEntry32.modBaseSize;
                break;
            }
        } while (Module32Next(hSnapshot, &ModuleEntry32));


    }
    CloseHandle(hSnapshot);
    cout << "cannot find Module BaseAddress!" << endl;

    exit(-1);
}


DWORD processinfo::getAOB_Address(unsigned char* arrayofbytes) {

    unsigned char buffer[40960];
    DWORD baseaddress1, oldprotect, pattern;
    wchar_t temp[] = L"game.exe";


    baseaddress1 = this->getModuleBaseAddress(temp);
    VirtualProtectEx(this->hnd, (LPVOID)baseaddress1, 0x7fbf0000, PROCESS_ALL_ACCESS, &oldprotect);
    for (unsigned i = 0; i < 0x7FBF; ++i) {
        ReadProcessMemory(this->hnd, (PBYTE*)baseaddress1, buffer, sizeof(buffer), 0);
        baseaddress1 = baseaddress1 + 40960;
        for (unsigned j = 0; j < 40947; ++j) {///////////////////sizeof(buffer)-sizeof(arrayofbytes)
            for (unsigned k = 0; k < 13; ++k) {//////////////////////////sizeof(arrayofbytes)
                if (arrayofbytes[k] != buffer[j + k]) {
                    //std::cout << std::hex << signature1.at(j) << std::hex << memBuffer[i + j] << std::endl;
                    break;
                }
                if (arrayofbytes[k] == buffer[j + k]) {
                    if (k + 1 == 13) {
                        //cout << baseaddress1 + i - 40960 << endl;
                        pattern = baseaddress1 + j - 40960;
                        //cout << pattern << endl;
                        return pattern;
                    }
                }
            }
        }







    }

    cout << "cannot find AOB_Address!" << endl;
    cout << "请至少对人物进行一次攻击后再尝试！" << endl;
    system("pause");
    exit(-1);


    //return -1;


}
