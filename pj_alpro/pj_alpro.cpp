#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <cstring>
using namespace std;

struct karyawan
{
    char nama[50], jabatan[50];
    int NIP, jamKerja;
    karyawan *kanan, *kiri;
};

struct admin
{
    string username, password;
};

admin akun[3] = {{"algoy", "a123"},
                 {"progoy", "b124"},
                 {"strudoy", "c125"}};

karyawan *awal, *akhir, *bantu, *hapus, *NB, *list;
karyawan kry;

int data, dataBaru = 0;
int ownerada = 0, adajabatan = 0, adanip;

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

int rumusgaji(char jabatan[50], int jamKerja)
{
    int gajiperjam = 0, totalGaji;

    if (strcmp(jabatan, "Manager") == 0 || strcmp(jabatan, "manager") == 0)
    {
        gajiperjam = 50000;
    }
    else if (strcmp(jabatan, "Supervisor") == 0 || strcmp(jabatan, "supervisor") == 0)
    {
        gajiperjam = 30000;
    }
    else if (strcmp(jabatan, "Staff") == 0 || strcmp(jabatan, "staff") == 0)
    {
        gajiperjam = 20000;
    }
    else if (strcmp(jabatan, "Pemilik") == 0 || strcmp(jabatan, "pemilik") == 0)
    {
        return 0; // Pemilik tidak menerima gaji
    }
    return gajiperjam * jamKerja * 30;
}

int prioritasJabatan(char jabatan[50])
{
    if (strcmp(jabatan, "Pemilik") == 0 || strcmp(jabatan, "pemilik") == 0)
        return 1;
    if (strcmp(jabatan, "Manager") == 0 || strcmp(jabatan, "manager") == 0)
        return 2;
    if (strcmp(jabatan, "Supervisor") == 0 || strcmp(jabatan, "supervisor") == 0)
        return 3;
    if (strcmp(jabatan, "Staff") == 0 || strcmp(jabatan, "staff") == 0)
        return 4;
}

void sisipnode(char namaBaru[50], char jabatanBaru[50], int NIPBaru, int jamKerjaBaru)
{
    NB = new karyawan;
    strcpy(NB->nama, namaBaru);
    strcpy(NB->jabatan, jabatanBaru);
    NB->NIP = NIPBaru;
    NB->jamKerja = jamKerjaBaru;
    NB->kanan = NULL;
    NB->kiri = NULL;

    int priorNB = prioritasJabatan(jabatanBaru);

    if (listkosong())
    {
        awal = akhir = NB;
    }
    else if (priorNB < prioritasJabatan(awal->jabatan))
    {
        // Sisip di depan
        NB->kanan = awal;
        awal->kiri = NB;
        awal = NB;
    }
    else
    {
        bantu = awal;
        while (bantu->kanan != NULL && priorNB >= prioritasJabatan(bantu->kanan->jabatan))
        {
            bantu = bantu->kanan;
        }
        NB->kanan = bantu->kanan;
        if (bantu->kanan != NULL)
        {
            bantu->kanan->kiri = NB;
        }
        NB->kiri = bantu;
        bantu->kanan = NB;

        if (NB->kanan == NULL)
        {
            akhir = NB;
        }
    }
}

void bacaFile()
{
    management = fopen("karyawan.txt", "r");
    if (management == NULL)
    {
        cout << "[!] File tidak ditemukan atau kosong.\n";
        return;
    }

    char nama[50], jabatan[50];
    int i = 0, NIP, jamKerja;

    while (fscanf(management, " %[^\n]\n%[^\n]\n%d\n%d\n", nama, jabatan, &NIP, &jamKerja) != EOF)
    {
        if (strcmp(jabatan, "Pemilik") == 0 || strcmp(jabatan, "pemilik") == 0)
        {
            ownerada = 1;
        }
        sisipnode(nama, jabatan, NIP, jamKerja);
        i++;
    }
    dataBaru = i;
    fclose(management);
}

void kirimfile()
{
    management = fopen("karyawan.txt", "w");
    if (management == NULL)
    {
        cout << "Gagal membuka file untuk menyimpan!\n";
        return;
    }

    bantu = awal;
    while (bantu != NULL)
    {
        fprintf(management, "%s\n%s\n%d\n%d\n", bantu->nama, bantu->jabatan, bantu->NIP, bantu->jamKerja);
        bantu = bantu->kanan;
    }

    fclose(management);
}

void input()
{
    management = fopen("karyawan.txt", "a"); 
    if (management == NULL)
    {
        cout << "Error membuka file!";
        exit(1);
    }

    char nama[50], jabatan[50];
    int NIP, jamKerja;

    system("cls");
    cout << " ========================" << endl;
    cout << " | >> Input Karyawan >> |" << endl;
    cout << " ========================" << endl;
    cout << " Ingin Masukkan berapa data? ";
    cin >> data;
    cin.ignore();

    for (int i = 0; i < data; i++)
    {
        cout << "\nData ke-" << dataBaru + i + 1 << endl;

        cout << " Masukkan Nama    : ";
        cin.getline(kry.nama, sizeof(kry.nama));

        do
        {
            cout << " Masukkan NIP     : ";
            cin >> kry.NIP;

            adanip = 1; 
            bantu = awal;
            while (bantu != NULL)
            {
                if (kry.NIP == bantu->NIP)
                {
                    cout << "NIP tidak boleh sama!" << endl;
                    adanip = 0; 
                    break;      
                }
                bantu = bantu->kanan;
            }
        } while (adanip == 0);

        cin.ignore(); // bersihkan buffer
        cout << "Jabatan hanya (Pemilik, Manager, Supervisor, dan Staff)\n";

        do
        {
            cout << " Masukkan Jabatan : ";
            cin.getline(kry.jabatan, sizeof(kry.jabatan));

            if (strcmp(kry.jabatan, "Pemilik") == 0 || strcmp(kry.jabatan, "pemilik") == 0 ||
                strcmp(kry.jabatan, "Supervisor") == 0 || strcmp(kry.jabatan, "supervisor") == 0 ||
                strcmp(kry.jabatan, "Staff") == 0 || strcmp(kry.jabatan, "staff") == 0 ||
                strcmp(kry.jabatan, "Manager") == 0 || strcmp(kry.jabatan, "manager") == 0)
            {

                if ((strcmp(kry.jabatan, "Pemilik") == 0 || strcmp(kry.jabatan, "pemilik") == 0) && ownerada)
                {
                    cout << "Pemilik hanya boleh ada 1! Masukkan jabatan lain." << endl;
                    adajabatan = 0;
                }
                else
                {
                    if (strcmp(kry.jabatan, "Pemilik") == 0 || strcmp(kry.jabatan, "pemilik") == 0)
                    {
                        kry.jamKerja = 0;
                        ownerada = 1;
                    }
                    adajabatan = 1;
                }
            }
            else
            {
                cout << "Masukkan jabatan yang benar." << endl;
                adajabatan = 0;
            }
        } while (adajabatan == 0);

        if (strcmp(kry.jabatan, "Pemilik") != 0 && strcmp(kry.jabatan, "pemilik") != 0)
        {
            cout << "Masukkan jam kerja : ";
            cin >> kry.jamKerja;
            cin.ignore();
        }
        sisipnode(kry.nama, kry.jabatan, kry.NIP, kry.jamKerja);
        fprintf(management, "%s\n%s\n%d\n%d\n", kry.nama, kry.jabatan, kry.NIP, kry.jamKerja);
    }

    dataBaru = dataBaru + data;
    cout << "\nData berhasil disimpan.\n";
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
             << "Jam Kerja: " << bantu->jamKerja << endl;
        int gaji = rumusgaji(bantu->jabatan, bantu->jamKerja);
        cout << "Gaji: " << gaji << endl;
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
             << "NIP : " << bantu->NIP << endl
             << "Jabatan: " << bantu->jabatan << endl
             << "Jam Kerja: " << bantu->jamKerja << endl;
        int gaji = rumusgaji(bantu->jabatan, bantu->jamKerja);
        cout << "Gaji: " << gaji << endl;
        cout << endl;
        bantu = bantu->kiri;
    }
}

void sortNIP()
{
    if (awal == NULL || awal->kanan == NULL)
    {
        cout << "List Kosong atau data hanya satu";
        system("pause");
        return;
    }
    bool swapped;

    do
    {
        swapped = false;
        bantu = awal;

        while (bantu->kanan != NULL)
        {
            if (bantu->NIP > bantu->kanan->NIP)
            {
                swap(bantu->nama, bantu->kanan->nama);
                swap(bantu->NIP, bantu->kanan->NIP);
                swap(bantu->jabatan, bantu->kanan->jabatan);
                swap(bantu->jamKerja, bantu->kanan->jamKerja);
                swapped = true;
            }
            bantu = bantu->kanan;
        }
    } while (swapped);
    cout << "Berhasil diurutkan" << endl;
    kirimfile();
    bacamaju();
}

void sortNama()
{
    if (awal == NULL || awal->kanan == NULL)
    {
        cout << "List Kosong atau data hanya satu";
        system("pause");
        return;
    }
    bool swapped;

    do
    {
        swapped = false;
        bantu = awal;

        while (bantu->kanan != NULL)
        {
            if (strcmp(bantu->nama, bantu->kanan->nama) > 0)
            {
                swap(bantu->nama, bantu->kanan->nama);
                swap(bantu->NIP, bantu->kanan->NIP);
                swap(bantu->jabatan, bantu->kanan->jabatan);
                swap(bantu->jamKerja, bantu->kanan->jamKerja);
                swapped = true;
            }
            bantu = bantu->kanan;
        }
    } while (swapped);
    cout << "Berhasil diurutkan" << endl;
    kirimfile();
    bacamaju();
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
            cout << "Jam Kerja: " << bantu->jamKerja << endl;
            int gaji = rumusgaji(bantu->jabatan, bantu->jamKerja);
            cout << "Gaji: " << gaji << endl;
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
            cout << "Jam Kerja: " << bantu->jamKerja << endl;
            int gaji = rumusgaji(bantu->jabatan, bantu->jamKerja);
            cout << "Gaji: " << gaji << endl;
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

void cekNIP()
{
    bantu = awal;
    while (bantu != NULL)
    {
        if (kry.NIP = bantu->NIP)
        {
            adanip = 1;
        }
        bantu = bantu->kanan;
    }
}

void hapusnode(char namaHapus[50])
{
    if (listkosong())
    {
        cout << "List masih kosong"; // cek list kosng
    }
    else if (awal == akhir)
    {
        // Hapus jika hanya ada satu node
        free(awal);
        cout << "Node dengan info " << namaHapus << " telah dihapus\n";
        awal = akhir = NULL;
        cout << "list sudah kosong";
    }
    else if (strcmp(awal->nama, namaHapus) == 0)
    {
        hapus = awal; // Hapus di awal
        awal = hapus->kanan;
        if (awal != NULL)
        {
            awal->kiri = NULL;
        }
        free(hapus);
        cout << "Node dengan info " << namaHapus << " telah dihapus\n";
    }
    else
    {
        bantu = awal;
        while (bantu->kanan != NULL && strcmp(namaHapus, bantu->kanan->nama) != 0)
        {
            bantu = bantu->kanan;
        }
        if (bantu->kanan != NULL && strcmp(namaHapus, bantu->kanan->nama) == 0)
        {
            hapus = bantu->kanan;
            if (hapus == akhir)
            { // Hapus di akhir
                akhir = bantu;
                akhir->kanan = NULL;
            }
            else
            { // Hapus di tengah
                bantu->kanan = hapus->kanan;
                hapus->kanan->kiri = bantu;
            }
            free(hapus);
            cout << "Node dengan info " << namaHapus << " telah dihapus\n";
        }
        else
        {
            cout << "list tidak di temukan\n";
        }
    }
    kirimfile();
}

void editData()
{
    int indexEdit;
    cout << "Edit karyawan nomor berapa? (1-" << dataBaru << ") = ";
    cin >> indexEdit;
    cin.ignore();

    // Nyari data yang diedit pake index data edit
    bantu = awal;
    for (int i = 1; i < indexEdit; i++)
    {
        bantu = bantu->kanan;
    }

    cout << "Data lama:\n";
    cout << "Nama    : " << bantu->nama << endl;
    cout << "NIP     : " << bantu->NIP << endl;
    cout << "Jabatan : " << bantu->jabatan << endl;
    cout << "jamKerja    : " << bantu->jamKerja << endl
         << endl;

    cout << "Masukkan data baru:\n";
    cout << "Nama    : ";
    cin.getline(bantu->nama, sizeof(bantu->nama));
    cout << "NIP     : ";
    cin >> bantu->NIP;
    cin.ignore();
    cout << "Jabatan : ";
    cin.getline(bantu->jabatan, sizeof(bantu->jabatan));
    cout << "jamKerja    : ";
    cin >> bantu->jamKerja;
    cin.ignore();

    kirimfile(); // Kiwrim data baru ke file

    cout << "\nData berhasil diedit.\n";
    system("pause");
}

int main()
{
    bool login = false;
    string nama, username, password;
    int kesempatan = 3;
    system("cls");
    cout << "Selamat datang di Aplikasi Manajemen Karyawan!\nSilahkan login terlebih dahulu.\n";
    cout << "=============================\n";
    do
    {
        cout << "username : ";
        cin >> username;
        cout << "password : ";
        cin >> password;
        kesempatan--;
        for (int i = 0; i < kesempatan; i++)
        {
            if (username == akun[i].username && password == akun[i].password)
            {
                nama = akun[i].username;
                login = true;
            }
        }
        if (!login)
        {
            cout << "Nama atau password yang dimasukkan salah! Kesempatan yang tersisa " << kesempatan << endl;
        }
    } while ((!login) && (kesempatan > 0));

    if (!login)
    {
        cout << "Kesempatan login habis, kembali lagi nanti\n";
        system("pause");
    }
    else
    {
        buatlistbaru();
        bacaFile();
        int menu;
        char ulang;
        int pilih;
        do
        {
            system("cls");
            cout << "Selamat datang dan selamat bekerja, " << nama << "!\n";
            cout << "==================== " << endl;
            cout << "       MENU          " << endl;
            cout << "==================== " << endl;
            cout << "1. Input Karyawan    " << endl;
            cout << "2. Output Karyawan   " << endl;
            cout << "3. Sorting Karyawan   " << endl;
            cout << "4. Search Karyawan     " << endl;
            cout << "5. Delete Karyawan     " << endl;
            cout << "6. Edit Karyawan       " << endl;
            cout << "7. Keluar       " << endl;
            cout << "==================== " << endl;
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
                cout << " Output Data by NIP :  " << endl;
                cout << "===================" << endl;
                cout << " 1. Ascending (Z-A)     " << endl;
                cout << " 2. Descending (A-Z)   " << endl;
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
                cout << "===================" << endl;
                cout << " Sorting Data by NIP :  " << endl;
                cout << "===================" << endl;
                cout << " 1. Sort by NIP     " << endl;
                cout << " 2. Sort by Name   " << endl;
                cout << "==================" << endl;
                cout << "Masukkan Pilihan : ";
                cin >> pilih;

                switch (pilih)
                {
                case 1:
                    cout << "=======================" << endl;
                    cout << "     Sorting by NIP    " << endl;
                    cout << "=======================" << endl;
                    sortNIP();
                    break;

                case 2:
                    cout << "=======================" << endl;
                    cout << "     Sorting by Name   " << endl;
                    cout << "=======================" << endl;
                    sortNama();
                    break;
                }
                break;

            case 4:
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
            case 5:
                char namaHapus[50];
                cout << "==================" << endl;
                cout << " Delete Data by:  " << endl;
                cout << "==================" << endl;
                cin.ignore();
                cout << "Masukkan nama yang ingin dihapus = ";
                cin.getline(namaHapus, sizeof(namaHapus));
                hapusnode(namaHapus);
                break;
            case 6:
                editData();
                break;
            case 7:
                return 0;
                break;
            default:
                cout << "Menu invalid";
                break;
            }

            cout << "Kembali ke Menu?(y/n) ";
            cin >> ulang;

        } while (ulang == 'y' || ulang == 'Y');
    }
}
