/*Saya Firda Ridzki Utami mengerjakan evaluasi Tugas Masa Depan dalam 
mata kuliah Dasar-dasar pemograman untuk keberkahan-Nya maka saya tidak
melakukan kecurangan seperti yang telah dispesifikasikan. Aamiin. */

#include <stdio.h>
#include <string.h>
#include <unistd.h>

//struct KasusKorupVonis untuk menyimpan data kasus-kasus koruptor yang telah divonis
typedef struct 
{
    char ID[10]; //primary key atau kode unik yang hanya dimiliki oleh satu orang saja
    char NAMA[100]; //atribut data, nama-nama dari terdakwa
    char foreignkey[10]; //kode unik untuk menggabungkan dengan tabel kasus dalam proses
    char KERUGIAN[100]; //status terdakwa
}Pelaku;

//struct KasusKorupProses untuk menyimpan data kasus-kasus koruptor yang masih dalam proses
typedef struct 
{
    char ID_kasus[10]; //primary key atau kode unik yang hanya dimiliki oleh satu orang saja
    char nama_Kasus[100]; //atribut data, nama-nama dari terdakwa
    char tahun_kasus[10]; //tahun kasus
    char sangsi_kasus[100]; //status terdakwa
}Kasus;

//Deklarasi variabel global
int indeks;
int panjangkata;
char ckata[51];

//Deklarasi mesin kata
void STARTKATA(char pita[]);
void RESETKATA();
void INCKATA(char pita[]);
void *GETKATA();
int GETPANJANGKATA();
int EOPKATA(char pita[]);

//Mendeklarasikan bagian animasi selamat datang
void pembuka(); //prosedur untuk bagian animasi pembuka


//Mendeklarasikan bagian READ dari file Pelaku dan Kasus
void readFromFileNames(int *a, int *f, Pelaku PelakuComplete[], Kasus DataKasus[], char fileName[], char FILENAME[]);
//Mendeklarasikan bagian Write dari file Pelaku dan kasus
void writeToFilePelaku(int *a, Pelaku PelakuComplete[], char fileName[]);
void writeToFileKasus(int *f, Kasus DataKasus[], char FILENAME[]);
//Insert
void insertDataPelaku(Pelaku PelakuComplete[], int *a, char ID[], char NAMA[], char foreignkey[], char KERUGIAN[]);
void insertDataKasus(Kasus DataKasus[], int *f, char ID_kasus[], char nama_Kasus[], char tahun_kasus[], char sangsi_kasus[]);
//UPDATE
void updateFilePelaku(Pelaku PelakuComplete[], int a, char ID[], char add1[], char add2[], char add3[], char add4[]);
void updateFileKasus(Kasus DataKasus[], int f, char ID_kasus[], char add1[], char add2[], char add3[], char add4[]);
//SHOW CETAK TABEL
//prosedur untuk menampilkan  data file pelaku
void showFromFilePelaku(Pelaku PelakuComplete[], int a);
//SHOW CETAK TABEL
//prosedur untuk menampilkan  data file Kasus
void showFromFileKasus(Kasus DataKasus[], int f);

//prosedur untuk JOINT, menggabungkan dua data file dengan foreign key yang sama
void joinDataPelakuKasus(Pelaku PelakuComplete[], int a, Kasus DataKasus[], int f)
