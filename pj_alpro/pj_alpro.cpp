#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <cstring>
using namespace std;

struct karyawan
{
    char nama[50], jabatan[50];
    int NIP, gaji;
    karyawan *kanan, *kiri;
};

karyawan *awal, *akhir, *bantu, *hapus, *NB, *list;
karyawan kry;

int data, dataBaru = 0;

FILE *management;

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

void sisipnode(char namaBaru[50], char jabatanBaru[50], int NIPBaru, int gajiBaru)
{

    NB = new karyawan;
    NB->NIP = NIPBaru;
    NB->gaji = gajiBaru;
    strcpy(NB->nama, namaBaru);
    strcpy(NB->jabatan, jabatanBaru);
    NB->kanan = NULL;
    NB->kiri = NULL;

    if (listkosong())
    {
        awal = akhir = NB;
    }
    else if (NIPBaru <= awal->NIP)
    { // Sisip di depan
        NB->kanan = awal;
        awal->kiri = NB;
        awal = NB;
    }
    else
    {
        bantu = awal;
        while (bantu->kanan != NULL && NIPBaru > bantu->kanan->NIP)
            bantu = bantu->kanan;

        NB->kanan = bantu->kanan; // Sisip di tengah/akhir
        if (bantu->kanan != NULL)
        {
            bantu->kanan->kiri = NB;
        }
        NB->kiri = bantu;
        bantu->kanan = NB;

        if (NIPBaru > akhir->NIP)
            akhir = NB;
    }
}

void bacaFile() {
    management = fopen("karyawan.txt", "r");
    if (management == NULL) {
        cout << "[!] File tidak ditemukan atau kosong.\n";
        return;
    }

    char nama[50], jabatan[50];
    int i = 0, NIP, gaji;

    while (fscanf(management, " %[^\n]\n%[^\n]\n%d\n%d\n", nama, jabatan, &NIP, &gaji) != EOF) {
        sisipnode(nama, jabatan, NIP, gaji);
        i++;
    }
    dataBaru = i;
    fclose(management);
}

void input()
{

    management = fopen("karyawan.txt", "a"); //Mode a agar bisa menambahkan data dan penyimpanan dinamis
    if (management == NULL)
    {
        cout << "Error membuka file!";
        exit(1);
    }

    char nama[50], jabatan[50];
    int NIP, gaji;

    system("cls");
    cout << " ========================" << endl;
    cout << " | >> Input Karyawan >> |" << endl;
    cout << " ========================" << endl;
    cout << " Ingin Masukkan berapa data? ";
    cin >> data;
    cin.ignore();

    for (int i = 0; i < data; i++)
    {
        cout << "\nData ke-" << i + 1 << endl;

        cout << " Masukkan Nama    : ";
        cin.getline(kry.nama, sizeof(kry.nama));
        cout << " Masukkan NIP     : ";
        cin >> kry.NIP;
        cin.ignore(); // bersihkan buffer

        cout << " Masukkan Jabatan : ";
        cin.getline(kry.jabatan, sizeof(kry.jabatan));
        cout << " Masukkan Gaji    : ";
        cin >> kry.gaji;
        cin.ignore();

        sisipnode(kry.nama, kry.jabatan, kry.NIP, kry.gaji);
        fprintf(management, "%s\n%s\n%d\n%d\n", kry.nama, kry.jabatan, kry.NIP, kry.gaji);
    }

    dataBaru += data;

    cout << "\nData berhasil disimpan.\n";
    system("pause");
    fclose(management);
}

void bacamaju()
{
    bantu = awal;
    while (bantu != NULL)
    {
        cout << "Nama : " << bantu->nama << endl
             << "NIP : " << bantu->NIP
             << endl
             << "Jabatan: " << bantu->jabatan << endl
             << "Gaji: " << bantu->gaji << endl;
        cout << endl;
        bantu = bantu->kanan;
    }
}

void bacamundur()
{
    bantu = akhir;
    while (bantu != NULL)
    {
        cout << "Nama : " << bantu->nama << endl
             << "NIP : " << bantu->NIP
             << endl
             << "Jabatan: " << bantu->jabatan << endl
             << "Gaji: " << bantu->gaji << endl;
        cout << endl;
        bantu = bantu->kiri;
    }
}

void searchNIP()
{
    system("cls");
    int search;
    bool found = false;

    cout << "Masukkan NIP yang akan dicari: ";
    cin >> search;

    bantu = awal;
    while (bantu != NULL)
    {
        if (bantu->NIP == search)
        {
            cout << "Nama : " << bantu->nama << endl;
            cout << "NIP : " << bantu->NIP << endl;
            cout << "Jabatan: " << bantu->jabatan << endl;
            cout << "Gaji: " << bantu->gaji << endl;
            cout << endl;
            found = true;
            break; 
        }
        bantu = bantu->kanan;
    }

    if (!found)
    {
        cout << "[!] Data dengan NIP " << search << " Tidak Ditemukan [!]" << endl;
    }

    system("pause");
}


void searchNama()
{
    system("cls");
    char searchName[50];
    bool found = false;

    cout << "Masukkan nama yang akan dicari: ";
    cin.ignore(); 
    cin.getline(searchName, sizeof(searchName));

    bantu = awal;
    while (bantu != NULL)
    {
        if (strcmp(bantu->nama, searchName) == 0)
        {
            cout << "Nama : " << bantu->nama << endl;
            cout << "NIP : " << bantu->NIP << endl;
            cout << "Jabatan: " << bantu->jabatan << endl;
            cout << "Gaji: " << bantu->gaji << endl;
            cout << endl;
            found = true;
        }
        bantu = bantu->kanan;
    }

    if (!found)
    {
        cout << "[!] Data dengan Nama " << searchName << " Tidak Ditemukan [!]" << endl;
    }

    system("pause");
}


int main()
{
    bacaFile();
    int menu;
    char ulang = 'y';
    int pilih;
    system("cls");
    do
    {
        cout << " =================== " << endl;
        cout << "       MENU          " << endl;
        cout << " =================== " << endl;
        cout << "1. Input Karyawan    " << endl;
        cout << "2. Sorting Karyawan   " << endl;
        cout << "3. Search Karyawan     " << endl;
        cout << "4. Delete Karyawan     " << endl;
        cout << " =================== " << endl;
        cout << "Masukkan Menu : ";
        cin >> menu;

        switch (menu)
        {
        case 1:
            input();
            break;
        case 2:
            system("cls");
            cout << "===================" << endl;
            cout << " Sort Data by NIP :  " << endl;
            cout << "===================" << endl;
            cout << " 1. Ascending     " << endl;
            cout << " 2. Descending    " << endl;
            cout << "==================" << endl;
            cout << "Masukkan Pilihan : ";
            cin >> pilih;

            switch (pilih)
            {
            case 1:
                cout << "=======================" << endl;
                cout << " Data secara Ascending " << endl;
                cout << "=======================" << endl;
                bacamaju();
                break;
            case 2:
            cout << "=======================" << endl;
                cout << " Data secara Descending " << endl;
                cout << "=======================" << endl;
                bacamundur();
            break;
            
            default:
                break;
            }
        break;
        
        case 3:
        cout << "==================" << endl;
            cout << " Searching Data by:  " << endl;
            cout << "==================" << endl;
            cout << " 1. Nama    " << endl;
            cout << " 2. NIP   " << endl;
            cout << "=======================" << endl;
            cout << "Masukkan Pilihan : ";
            cin >> pilih;

            switch (pilih)
            {
            case 1:
                searchNama();
                break;
            case 2:
            searchNIP();
            break;
            
            default:
                break;
            }
        break;
        
        default:
            break;
        }

        // if (menu == 1)
        // {
        //     input();
        // }
        // if (menu == 2)
        // {
        //     system("cls");
        //     cout << "===================" << endl;
        //     cout << " Sort Data by NIP :  " << endl;
        //     cout << "===================" << endl;
        //     cout << " 1. Ascending     " << endl;
        //     cout << " 2. Descending    " << endl;
        //     cout << "==================" << endl;
        //     cout << "Masukkan Pilihan : ";
        //     cin >> pilih;

        //     if (pilih == 1)
        //     {
        //         cout << "=======================" << endl;
        //         cout << " Data secara Ascending " << endl;
        //         cout << "=======================" << endl;
        //         bacamaju();
        //     }
        //     if (pilih == 2)
        //     {
        //         cout << "=======================" << endl;
        //         cout << " Data secara Descending " << endl;
        //         cout << "=======================" << endl;
        //         bacamundur();
        //     }
        // }
        // if (menu == 3)
        // {
        //     cout << "==================" << endl;
        //     cout << " Searching Data by:  " << endl;
        //     cout << "==================" << endl;
        //     cout << " 1. Nama    " << endl;
        //     cout << " 2. NIP   " << endl;
        //     cout << "=======================" << endl;
        //     cout << "Masukkan Pilihan : ";
        //     cin >> pilih;

        //     if (pilih == 1)
        //     {
        //         searchNama();
        //     }
        //     if (pilih == 2)
        //     {
        //         searchNIP();
        //     }
        // }

        cout << "Kembali ke Menu?(y/n) ";
        cin >> ulang;

    } while (ulang == 'y');
}
