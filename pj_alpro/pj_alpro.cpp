#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <string.h>
using namespace std;

struct karyawan
{
    char nama[50], jabatan[50];
    int NIP, gaji;
    karyawan *kanan, *kiri;
};

karyawan *awal, *akhir, *bantu, *hapus, *NB, *list;

void buatlistbaru()
{
    list = NULL;
    awal = list;
    akhir = list;
}

int listkosong()
{
    if (awal == NULL)
        return (1);
    else
        return (false);
}

void sisipnode(char namaBaru[50], char jabatanBaru[50], int NIPBaru, int gajiBaru) {
    NB = new karyawan;
    NB->NIP = NIPBaru;
    NB->gaji = gajiBaru;
    strcpy(NB->nama, namaBaru);
    strcpy(NB->jabatan, jabatanBaru);
    NB->kanan = NULL;
    NB->kiri = NULL;

    if (listkosong()) {
        awal = akhir = NB;
    } else if (NIPBaru <= awal->NIP) { // Sisip di depan
        NB->kanan = awal;
        awal->kiri = NB;
        awal = NB;
    } else {
        bantu = awal;
        while (bantu->kanan != NULL && NIPBaru > bantu->kanan->NIP)
            bantu = bantu->kanan;

        NB->kanan = bantu->kanan; // Sisip di tengah/akhir
        if (bantu->kanan != NULL) {
            bantu->kanan->kiri = NB;
        }
        NB->kiri = bantu;
        bantu->kanan = NB;

        if (NIPBaru > akhir->NIP)
            akhir = NB;
    }
}

void input() {
    int data;
    char nama[50], jabatan[50];
    int NIP, gaji;

    system("cls");
    cout << " ========================" << endl;
    cout << " | >> Input Karyawan >> |" << endl;
    cout << " ========================" << endl;
    cout << " Ingin Masukkan berapa data? ";
    cin >> data;
    cin.ignore(); 

    for (int i = 0; i < data; i++) {
        cout << "\nData ke-" << i + 1 << endl;

        cout << " Masukkan Nama    : ";
        cin.getline(nama, 50);
        cout << " Masukkan NIP     : ";
        cin >> NIP;
        cin.ignore(); // bersihkan buffer

        cout << " Masukkan Jabatan : ";
        cin.getline(jabatan, 50);
        cout << " Masukkan Gaji    : ";
        cin >> gaji;
        cin.ignore();

        sisipnode(nama, jabatan, NIP, gaji);
    }

    cout << "\nData berhasil disimpan.\n";
    system("pause");
}

void bacamaju()
{
  bantu=awal;
  while (bantu!=NULL)
  {
	 cout << "NIM : " << bantu->NIP << endl << "Nama : " << bantu->nama;
	 cout << endl;
	 bantu=bantu->kanan;
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
            system("cls");
            int pilih;
            cout << "==================" << endl;
            cout << "   Tampilan Data  "<< endl;
            cout << "==================" << endl;
            cout << "   1. Ascending    " << endl;
            cout << "   2. Descending   " << endl;
            cout << "==================" << endl;
            cout << "Masukkan Pilihan : "; cin >> pilih;

            if (pilih == 1)
            {
                bacamaju();
            } else if (pilih == 2)
            {
                /* code */
            }
        }

        cout << "Kembali ke Menu?(y/n) "; cin >> ulang;
        
        
    } while (ulang == 'y');

}