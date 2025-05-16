#include <iostream>
using namespace std;

struct karyawan
{
    char nama, jabatan, gaji;
    int NIP;
};
karyawan kry;

int main(){
    int menu;
    char ulang = 'y';
    do
    {
        cout << " =================== " << endl;
        cout << "       MENU          " << endl;
        cout << " =================== " << endl; 
        cout << "1. Input Karyawan    " << endl;
        cout << "2. Output Karyawan   " << endl;
        cout << "3. EXIT              " << endl;
        cout << " =================== " << endl;
        cout << "Masukkan Menu : "; cin >> menu;
    } while (ulang == 'y');
    
}