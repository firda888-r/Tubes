#include <stdio.h>
#include "header.h"

int main() {
    char pita[500]; //untuk menyimpan input dari user
    char temp1[51]; //untuk menyimpan kata pertama dari masukan
    char temp2[51]; //untuk menyimpan kata kedua dari masukan
    int a = 0; int f = 0; //variabel untuk menyimpan jumlah dari data file pelaku dan kasus 

    //Deklarasi array untuk menyimpan data pelaku
    Pelaku PelakuComplete[100];
    Kasus  DataKasus[100];
    
    readFromFileNames(&a, &f, PelakuComplete, DataKasus, "PelakuComplete.txt", "DataKasus.txt");

    //memanggil animasi pembuka
    pembuka();

    //looping  program utama
    do {
        scanf(" %500[^\n]s", &pita);
        STARTKATA(pita);

        
        
    }
}