#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <cstring>
using namespace std;

struct karyawan // Deklarasi struct untuk data karyawan
{
    char nama[50], jabatan[50];
    int NIP, jamKerja;
    karyawan *kanan, *kiri;
};

struct admin // Deklarasi struct untuk data admin
{
    string username, password;
};

admin akun[3] = {{"algoy", "a123"}, // Array akun untuk keperluan login
                 {"progoy", "b124"},
                 {"strudoy", "c125"}};

karyawan *awal, *akhir, *bantu, *hapus, *NB, *list, *cek; // Deklarasi pointer linked-list
karyawan kry; // Penampung sementara sebelum ke linked-list dan file

int data, dataBaru = 0; // Menyimpan nilai banyaknya data di terminal
int ownerada = 0, adajabatan = 0, adanip; // Boolean

FILE *management; // Deklarasi File

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

int rumusgaji(char jabatan[50], int jamKerja) // Fungsi hitung gaji perbulan
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

int prioritasJabatan(char jabatan[50]) // Fungsi menentukan prioritas jabatan dari urutan nilai angka
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

void sisipnode(char namaBaru[50], char jabatanBaru[50], int NIPBaru, int jamKerjaBaru) // Fungsi sisip node linked-list
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
            bantu->kanan->kiri = NB;  // Sisip di tengah
        }
        NB->kiri = bantu;
        bantu->kanan = NB;

        if (NB->kanan == NULL)
        {
            akhir = NB; // Sisip akhir
        }
    }
}

void bacaFile() // Fungsi baca data dari file
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

void kirimfile() // Fungsi kirim data ke file
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

void input() // Fungsi input data
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
                if (kry.NIP == bantu->NIP)  // Error handling NIP tidak boleh sama
                {
                    cout << "NIP tidak boleh sama!" << endl; 
                    adanip = 0;
                    break;
                }
                bantu = bantu->kanan;
            }
        } while (adanip == 0);

        cin.ignore();
        cout << "Jabatan hanya (Pemilik, Manager, Supervisor, dan Staff)\n"; // Pendefinisian jabatan hanya ada 4

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
                    cout << "Pemilik hanya boleh ada 1! Masukkan jabatan lain." << endl; // Error handling pemilik hanya boleh 1
                    adajabatan = 0; 
                }
                else
                {
                    if (strcmp(kry.jabatan, "Pemilik") == 0 || strcmp(kry.jabatan, "pemilik") == 0)
                    {
                        kry.jamKerja = 0;  // Pemilik tidak memiliki jam kerja
                        ownerada = 1;
                    }
                    adajabatan = 1;
                }
            }
            else
            {
                cout << "Masukkan jabatan yang benar." << endl; // Error handling user memasukkan jabatan di luar 4 ketentuan
                adajabatan = 0;
            }
        } while (adajabatan == 0);

        if (strcmp(kry.jabatan, "Pemilik") != 0 && strcmp(kry.jabatan, "pemilik") != 0)  // Selain pemilik harus menginput jam kerja
        {
            cout << "Masukkan jam kerja : ";
            cin >> kry.jamKerja;
            cin.ignore();
        }
        sisipnode(kry.nama, kry.jabatan, kry.NIP, kry.jamKerja); // Mengirim data sementara ke fungsi sisipnode untuk dibuat nodenya
        fprintf(management, "%s\n%s\n%d\n%d\n", kry.nama, kry.jabatan, kry.NIP, kry.jamKerja); // Mengirim ke file
    }

    dataBaru = dataBaru + data; // Mengupdate jumlah banyaknya data
    cout << "\nData berhasil disimpan.\n";
    fclose(management);
}

void bacamaju() // Fungsi output data 
{

    if (listkosong())
    {
        cout << "List masih kosong\n"; // cek list kosng
    }
    else
    {
        bantu = awal;
        while (bantu != NULL)
        {
            cout << "Nama      : " << bantu->nama << endl
                 << "NIP       : " << bantu->NIP
                 << endl
                 << "Jabatan   : " << bantu->jabatan << endl
                 << "Jam Kerja : " << bantu->jamKerja << endl;
            int gaji = rumusgaji(bantu->jabatan, bantu->jamKerja);
            cout << "Gaji      : " << gaji << endl;
            cout << endl;
            bantu = bantu->kanan;
        }
    }
}

void bacamundur() // Fungsi output data
{
    if (listkosong())
    {
        cout << "List masih kosong\n"; // cek list kosng
    }
    else
    {
        bantu = akhir;
        while (bantu != NULL)
        {
            cout << "Nama      : " << bantu->nama << endl
                 << "NIP       : " << bantu->NIP << endl
                 << "Jabatan   : " << bantu->jabatan << endl
                 << "Jam Kerja : " << bantu->jamKerja << endl;
            int gaji = rumusgaji(bantu->jabatan, bantu->jamKerja);
            cout << "Gaji      : " << gaji << endl;
            cout << endl;
            bantu = bantu->kiri;
        }
    }
}

void sortNIP() // Fungsi sort data
{
    if (listkosong())
    {
        cout << "List masih kosong\n"; // cek list kosng
    }
    else
    {
        bool swapped;
        do
        {
            swapped = false;
            bantu = awal;

            while (bantu->kanan != NULL)
            {
                if (bantu->NIP > bantu->kanan->NIP) // Mengurutkan data berdasarkan NIP
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
        kirimfile(); // Mengirim data yang baru di sort ke fille
        bacamaju();
    }
}

void sortNama() // Fungsi sort data
{
    if (listkosong())
    {
        cout << "List masih kosong\n"; // cek list kosng
    }
    else
    {
        bool swapped; // Boolean swapped
        do
        {
            swapped = false;
            bantu = awal;

            while (bantu->kanan != NULL)
            {
                if (strcmp(bantu->nama, bantu->kanan->nama) > 0) // Mengurutkan data berdasarkan nama
                {
                    swap(bantu->nama, bantu->kanan->nama);
                    swap(bantu->NIP, bantu->kanan->NIP);
                    swap(bantu->jabatan, bantu->kanan->jabatan);
                    swap(bantu->jamKerja, bantu->kanan->jamKerja);
                    swapped = true;
                }
                bantu = bantu->kanan; 
            }
        } while (swapped); // Akan berhenti jika true
        cout << "Berhasil diurutkan" << endl;
        kirimfile();
        bacamaju();
    }
}

void searchNIP() // Fungsi search data
{
    system("cls");
    if (listkosong())
    {
        cout << "List masih kosong\n"; // cek list kosng
    }
    else
    {
        int search;
        bool found = false;

        cout << "Masukkan NIP yang akan dicari: "; // Cari data berdasarkan NIP
        cin >> search;

        bantu = awal;
        while (bantu != NULL)
        {
            if (bantu->NIP == search) // Membandingkan input cari dengan data yang tersimpan
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
            cout << "[!] Data dengan NIP " << search << " Tidak Ditemukan [!]" << endl; // Error message jika tidak deitemukan
        }

        system("pause");
    }
}

void searchNama() // Fungsi search data
{
    system("cls");
    if (listkosong())
    {
        cout << "List masih kosong\n"; // cek list kosng
    }
    else
    {
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
    }
}

void hapusnode(char namaHapus[50]) // Fungsi hapus data
{
    if (listkosong())
    {
        cout << "List masih kosong\n"; // cek list kosng
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
    kirimfile(); // Mengirim data yang sudah diupdate setelah dihapus
}

void editData() // Fungsi edit data
{
    if (listkosong())
    {
        cout << "List masih kosong\n";
        return;
    }

    char namaEdit[50];
    cout << "Masukkan nama karyawan yang ingin diedit: ";
    cin.ignore();
    cin.getline(namaEdit, sizeof(namaEdit));

    bantu = awal;
    bool ketemu = false;
    while (bantu != NULL)
    {
        if (strcmp(namaEdit, bantu->nama) == 0) // Membandingkan nama yang diinput dengan data yang tersimpan
        {
            ketemu = true; // Jika ketemu boolean diupdate true
            break;
        }
        bantu = bantu->kanan;
    }

    if (!ketemu)
    {
        cout << "Data dengan nama tersebut tidak ditemukan.\n";
        return;
    }

    cout << "\nData lama:\n";
    cout << "Nama    : " << bantu->nama << endl;
    cout << "NIP     : " << bantu->NIP << endl;
    cout << "Jabatan : " << bantu->jabatan << endl;
    cout << "Jam Kerja: " << bantu->jamKerja << endl
         << endl;

    cout << "Masukkan data baru:\n";
    cout << "Nama    : ";
    cin.getline(bantu->nama, sizeof(bantu->nama));

    // Validasi NIP unik
    do
    {
        cout << "NIP     : ";
        cin >> bantu->NIP;
        adanip = 1;
        cek = awal;
        while (cek != NULL)
        {
            if (cek != bantu && cek->NIP == bantu->NIP) // Error handling NIP sama
            {
                cout << "NIP sudah digunakan oleh karyawan lain!\n";
                adanip = 0;
                break;
            }
            cek = cek->kanan;
        }
    } while (adanip == 0);
    cin.ignore();

    cout << "Jabatan hanya (Pemilik, Manager, Supervisor, dan Staff)\n";

    do
    {
        cout << "Jabatan : ";
        cin.getline(bantu->jabatan, sizeof(bantu->jabatan));

        if (strcmp(bantu->jabatan, "Pemilik") == 0 || strcmp(bantu->jabatan, "pemilik") == 0 ||
            strcmp(bantu->jabatan, "Manager") == 0 || strcmp(bantu->jabatan, "manager") == 0 ||
            strcmp(bantu->jabatan, "Supervisor") == 0 || strcmp(bantu->jabatan, "supervisor") == 0 ||
            strcmp(bantu->jabatan, "Staff") == 0 || strcmp(bantu->jabatan, "staff") == 0)
        {
            if ((strcmp(bantu->jabatan, "Pemilik") == 0 || strcmp(bantu->jabatan, "pemilik") == 0))
            {
                ownerada = 0; // rReset nilai owner ada menjadi 0

                cek = awal;
                while (cek != NULL)
                {
                    if (cek != bantu &&
                        (strcmp(cek->jabatan, "Pemilik") == 0 || strcmp(cek->jabatan, "pemilik") == 0))
                    {
                        ownerada = 1; // Mendefinisikan ownerada 1 jika ketemu jabatan pemilik di data tersimpan
                        break;
                    }
                    cek = cek->kanan;
                }

                if (ownerada == 1)
                {
                    cout << "Pemilik hanya boleh ada 1! Masukkan jabatan lain.\n"; // Error handling
                    adajabatan = 0;
                }
                else
                {
                    bantu->jamKerja = 0; // Pemilik tidak punya jam kerja
                    ownerada = 1; // Mengupdate nilai true pemilik
                    adajabatan = 1; // Boolean loop
                }
            }
            else
            {
                adajabatan = 1; // Boolean loop
            }
        }
        else
        {
            cout << "Masukkan jabatan yang benar.\n"; // Error handling
            adajabatan = 0;
        }
    } while (adajabatan == 0); // Akan terus mengulang jika adajabatan 0

    if (strcmp(bantu->jabatan, "Pemilik") != 0 && strcmp(bantu->jabatan, "pemilik") != 0) // Selain pemilik wajib menginput jam kerja 
    {
        cout << "Masukkan jam kerja : ";
        cin >> bantu->jamKerja;
        cin.ignore();
    }

    kirimfile();
    cout << "\nData berhasil diedit.\n"; // Update data kirim file
}

int main()
{  // Login
    bool login = false;
    string nama, username, password; // Mendeklarasikan penggunaan string untuk akun
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
        kesempatan--; // Kesempatan
        for (int i = 0; i < kesempatan; i++)
        {
            if (username == akun[i].username && password == akun[i].password) // Membandingkan username dan password yang diinput dan yang tersimpan
            {
                nama = akun[i].username;
                login = true;
            }
        }
        if (!login) // Menampilkan kesempatan yang tersisa
        {
            cout << "Nama atau password yang dimasukkan salah! Kesempatan yang tersisa " << kesempatan << endl;
        }
    } while ((!login) && (kesempatan > 0)); // Akan mengulang sampai nilai login terupdate dan kesempatan lebih dari 0

    if (!login)
    {
        cout << "Kesempatan login habis, kembali lagi nanti\n"; 
        system("pause"); // User akan keluar jika kesempatan login habis
    }
    else
    {
        buatlistbaru(); // Program buat list
        bacaFile(); // Mengambil data yang sudah tersimpan dari file
        int menu;
        char ulang;
        int pilih;
        do
        {                      // Menu aplikasi
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
                cout << "=========================" << endl;
                cout << " Output Data by Jabatan :  " << endl;
                cout << "=========================" << endl;
                cout << " 1. Ascending      " << endl;
                cout << " 2. Descending    " << endl;
                cout << "=========================" << endl;
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
                cout << "====================" << endl;
                cout << " Sorting Data by NIP :  " << endl;
                cout << "====================" << endl;
                cout << " 1. Sort by NIP     " << endl;
                cout << " 2. Sort by Name   " << endl;
                cout << "===================" << endl;
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
                hapusnode(namaHapus); // Mengirim data nama yang ingin dihapus ke fungsi hapusnode
                break;
            case 6:
                editData();
                break;
            case 7:
                system("cls");
                cout << "Sampai bertemu kembali " << nama << ", selamat istirahat!\n"; // Keluar
                system("pause");
                return 0;
                break;
            default:
                cout << "Menu invalid!\n"; // Error handling user input invalid menu
                break;
            }

            cout << "Kembali ke Menu? (y/n) "; // Looping
            cin >> ulang;

        } while (ulang == 'y' || ulang == 'Y'); // Case sensitive error handling 
    }
}

// Done.