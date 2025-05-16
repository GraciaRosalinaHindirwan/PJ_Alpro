#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <string.h>
using namespace std;

struct karyawan
{
    char nama, jabatan, gaji;
    int NIP;
};
karyawan kry[1000];


void input(){
    int data;
    system("cls");
    cout << " ========================" << endl;
    cout << " | >> Input Karyawan >> |" << endl;
    cout << " ========================" << endl;
    cout << " Ingin Masukkan berapa data? "; cin >> data;
    system("pause");
    
    for (int i = 0; i < data; i++)
    {
        cout << "Data ke-" << i+1 << endl;
        cin.ignore();
        cout << " Masukkan Nama    :     "; gets(kry[i].nama);
        cout << " Masukkan NIP     :     "; gets(kry[i].NIP);
        cout << " Masukkan Jabatan :     "; gets(kry[i].jabatan);
        cout << " Masukkan Gaji    :     "; cin >> kry[i].gaji;
        cin.ignore();
        cout << " ========================" << endl;
    }
}

int main(){
    int menu;
    char ulang = 'y';
    system("cls");
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

        if (menu == 1)
        {
            input();
        } if (menu == 2)
        {
            
        }
        
        
    } while (ulang == 'y');

}