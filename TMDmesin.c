#include <stdio.h>
#include "header.h"

//deklarasi variabel global
int indeks;
int panjangkata; //wlen panjang current word
char ckata[51];

//menampilkan bagian amimasi selamat datang
void pembuka()
{
    printf("\nWilujeng Sumping di DBMS Swiper Jangan Mencuri....\n");
    char animasipembuka[6][66] = {
        "          $8$8$8$8$8$8$8$8$8$8$8$8$8$8$8$8$8$8$8$8$8$ ",
        "                 00000000000000000000000000000    ",
        "                <<SEMANGAT PAGI!! DONT GIVEUP>>",
        "                 00000000000000000000000000000    ",
        "          $8$8$8$8$8$8$8$8$8$8$8$8$8$8$8$8$8$8$8$8$8$ ",
        "                    DBMS Firda Ridzki Utami"};
        
        //looping untuk menampikan animasi pembuka
        for (int i = 0; i < 6; i++){
            for (int j = 0; j < 60; j++){
                printf("%c", animasipembuka[i][j]);
            }
            fflush(stdout); //
            //delay 1 detik
            sleep(1);
            printf("\n");
        } 
}
// nyalakan mesin
void STARTKATA(char pita[]){
    // set index dan panjang kata menjadi 0
    indeks = 0;
    panjangkata = 0;

    while (pita[indeks] == ' '){ // ignore blank
        indeks++;
    }

    // ambil kata masukkan dalam current word
    while ((pita[indeks] != ' ') && (eop(pita) == 0)){
        ckata[panjangkata] = pita[indeks];
        panjangkata++;
        indeks++;
    }
    ckata[panjangkata] = '\0'; // akhiri dengan null terminator
}

// reset current word
void RESETKATA(){
    panjangkata = 0; // kembalikan panjang kata menjadi 0
    ckata[panjangkata] = '\0'; // set current word menjadi null (siap diisi)
}

// pindah next kata
void INCKATA(char pita[]){
    panjangkata = 0; // set panjang kata jadi 0 (memastikan)
    //jika karakter dalam pita adalah spasi, maka indeks akan teris maju
    while (pita[indeks] == ' '){ // ignore blank
        indeks++;
    }

    // masukkan kata baru
    while ((pita[indeks] != ' ' && pita[indeks] != ';')){
        ckata[panjangkata] = pita[indeks];
        panjangkata++;
        indeks++;
    }
    ckata[panjangkata] = '\0'; // akhiri lagi
}

// mengembalikan current word
char* GETKATA(){
    return ckata;
}

// mengembalikan panjang current word
int GETPANJANGKATA(){
    return panjangkata;
}

// cek eop
int EOPKATA(char pita[]){
    if(pita[indeks] == ';'){ // jika ';' return 1
        return 1;
    }
    else{
        return 0; // jika bukan ';' kembalikan 0
    }
}

//Prosedur untuk membaca file Pelaku
void readFromFileNames(int *a, int *f, Pelaku PelakuComplete[], Kasus DataKasus[], char fileName[], char FILENAME[])
{
    FILE *Pelaku;
    FILE *Kasus;
    //Membuka kedua file yaitu file pelaku dan kasus
    Pelaku = fopen(fileName, "r"); // r untuk operator read file
    Kasus = fopen(FILENAME, "r"); // r untuk operator read file kasus
    
    //Membaca data dari file pelaku
    int returnVal1 = fscanf(Pelaku, "%s %s %s %s", PelakuComplete[*a].ID, PelakuComplete[*a].NAMA, PelakuComplete[*a].foreignkey, PelakuComplete[*a].KERUGIAN);
    
    //cek apakah data kosong atau dummy, maka menampilkan pesan file kosong
    if (strcmp(PelakuComplete[*a].ID, "####") == 0 || returnVal1 == EOF)
    {
        printf("File Kosong\n");
    }else{
        //Membaca seluruh data dari file pelakucomplete dan menyimpannya ke pelaku
        while (strcmp (PelakuComplete[*a].ID, "###") != 0)
        {
           *a = *a + 1;
           fscanf(Pelaku, "%s %s %s %s", PelakuComplete[*a].ID, PelakuComplete[*a].NAMA, PelakuComplete[*a].foreignkey, PelakuComplete[*a].KERUGIAN);   
        }
    }

    //Membaca Data file kasus
    int returnVal2 = fscanf(Kasus, "%s %s %s %s", DataKasus[*f].ID_kasus, DataKasus[*f].nama_Kasus, DataKasus[*f].tahun_kasus, DataKasus[*f].sangsi_kasus);
    
    //cek apakah data kosong atau dummy, maka menampilkan pesan file kosong
    if (strcmp(DataKasus[*f].ID_kasus, "####") == 0 || returnVal2 == EOF)
    {
        printf("File Kosong\n");
    }else{
        //Membaca seluruh data dari file pelakucomplete dan menyimpannya ke pelaku
        while (strcmp (DataKasus[*f].ID_kasus, "###") != 0)
        {
           *f = *f + 1;
           fscanf(Kasus, "%s %s %s %s", DataKasus[*f].ID_kasus, DataKasus[*f].nama_Kasus, DataKasus[*f].tahun_kasus, DataKasus[*f].sangsi_kasus);   
        }
    }
   fclose(Pelaku); //menutup file pelaku setelah selesai
   fclose(Kasus); //menutup file Kasus setelah selesai

}

//prosedur Write untuk menulis data kasus ke dalam file pelaku
void writeToFilePelaku(int *a, Pelaku PelakuComplete[], char fileName[]) {
    //Membuka file pelaku
    FILE *Pelaku = fopen(fileName, "w");
    
    // Menulis setiap data Pelaku ke dalam file
    for (int i = 0; i < *a; i++) {
        fprintf(Pelaku, "%s %s %s %s\n", PelakuComplete[i].ID, PelakuComplete[i].NAMA, PelakuComplete[i].foreignkey, PelakuComplete[i].KERUGIAN);
    }  
    // Menulis tanda akhir data
    fprintf(Pelaku, "####\n");

    fclose(Pelaku); // Menutup file setelah selesai
    printf("Data Pelaku berhasil disimpan ke dalam file\n"); 
}

// Prosedur untuk menulis data Kasus ke dalam file
void writeToFileKasus(int *f, Kasus DataKasus[], char FILENAME[]) {
    //Membuka file pelaku
    FILE *Kasus = fopen(FILENAME, "w");
    
    // Menulis setiap data Pelaku ke dalam file
    for (int i = 0; i < *f; i++) {
        fprintf(Kasus, "%s %s %s %s\n", DataKasus[i].ID_kasus, DataKasus[i].nama_Kasus, DataKasus[i].tahun_kasus, DataKasus[i].sangsi_kasus);
    }  
    // Menulis tanda akhir data
    fprintf(Kasus, "####\n");

    fclose(Kasus); // Menutup file setelah selesai
    printf("Data kasus berhasil disimpan ke dalam file\n"); 
}

//Insert atau bagain mengisi data file Pelaku
// Fungsi untuk menambahkan data baru pelaku 
void insertDataPelaku(Pelaku PelakuComplete[], int *a, char ID[], char NAMA[], char foreignkey[], char KERUGIAN[])
{
    if (*a >= 40) {
        printf("Kapasitas Data file Pelaku penuh\n");
        return;
    }
    //Menambahkan data ke array
    strcpy(PelakuComplete[*a].ID, ID);
    strcpy(PelakuComplete[*a].NAMA, NAMA);
    strcpy(PelakuComplete[*a].foreignkey, foreignkey);
    strcpy(PelakuComplete[*a].KERUGIAN, KERUGIAN);
    (*a)++;

    writeToFilePelaku(&*a, PelakuComplete, "PelakuComplete.txt"); //menuliskan kembali ke file pelaku
    printf("Data Pelaku berhasil ditambahkan\n");
}
// Prosedur untuk menambahkan data kasus
void insertDataKasus(Kasus DataKasus[], int *f, char ID_kasus[], char nama_Kasus[], char tahun_kasus[], char sangsi_kasus[]) {
    if (*f >= 40) {
        printf("Kapasitas data kasus penuh!\n");
        return;
    }
    
    // Menambahkan data ke array
    strcpy(DataKasus[*f].ID_kasus, ID_kasus);
    strcpy(DataKasus[*f].nama_Kasus, nama_Kasus);
    strcpy(DataKasus[*f].tahun_kasus, tahun_kasus);
    strcpy(DataKasus[*f].sangsi_kasus, sangsi_kasus);
    (*f)++;
    
    writeToFileKasus(&*f, DataKasus, "DataKasus.txt"); //menuliskan kembali ke file kasus
    printf("Data kasus berhasil ditambahkan\n");
}

//Prosedur untuk mengubah mengUPDATE data file Pelaku berdasarkan Foreign key
void updateFilePelaku(Pelaku PelakuComplete[], int a, char ID[], char add1[], char add2[], char add3[], char add4[]) {
    int stop = 0; //untuk penanda pencarian dihentikan
    int sesuai; //variabel jika sudah menemukan data yang sesuai

    //looping untuk mencari data foreignkey yang sesuai
    for (int i = 0; i < a; i++) {
        //Kondisi jika ID yang dicari telah sesuai
        if(strcmp(PelakuComplete[i].ID, ID) == 0 && stop != 1 ) {
            stop = 1; //agar hanya mencari satu data saja
            sesuai = i; //untuk menyimpan data yang sesuai 
        }
    }
    //Kondisi jika data tidak ditemukan dan menampilkan pesan 
    if (stop == 0) {
        printf("Data Tidak Ada\n");
    }
    else //Kondisi jika foreignkey ditemukan
    {
        //Memperbarui data dengan yang baru
        strcpy(PelakuComplete[sesuai].ID, add1);
        strcpy(PelakuComplete[sesuai].NAMA, add2);
        strcpy(PelakuComplete[sesuai].foreignkey, add3);
        strcpy(PelakuComplete[sesuai].KERUGIAN, add4);

        //Tuliskan kembali data ke file pelaku
        writeToFilePelaku(&a, PelakuComplete, "PelakuComplete.txt");
        //Menampilkan pesan bahwa data file pelaku berhasil di update
        printf("SELAMAT DATA BERHASIL DI UPDATE\n");
    }
}

//Prosedur untuk mengubah mengUPDATE data file Pelaku berdasarkan ID
void updateFileKasus(Kasus DataKasus[], int f, char ID_kasus[], char add1[], char add2[], char add3[], char add4[]) {
    int stop = 0; //untuk penanda pencarian dihentikan
    int sesuai; //variabel jika sudah menemukan data yang sesuai

    //looping untuk mencari data foreignkey yang sesuai
    for (int i = 0; i < f; i++) {
        //Kondisi jika ID yang dicari telah sesuai
        if(strcmp(DataKasus[i].ID_kasus, ID_kasus) == 0 && stop != 1 ) {
            stop = 1; //agar hanya mencari satu data saja
            sesuai = i; //untuk menyimpan data yang sesuai 
        }
    }
    //Kondisi jika data tidak ditemukan dan menampilkan pesan 
    if (stop == 0) {
        printf("Data Tidak Ada\n");
    }
    else //Kondisi jika foreignkey ditemukan
    {
        //Memperbarui data dengan yang baru
        strcpy(DataKasus[sesuai].ID_kasus, add1);
        strcpy(DataKasus[sesuai].nama_Kasus, add2);
        strcpy(DataKasus[sesuai].tahun_kasus, add3);
        strcpy(DataKasus[sesuai].sangsi_kasus, add4);

        //Tuliskan kembali data ke file pelaku
        writeToFilePelaku(&f, DataKasus, "DataKasus.txt");
        //Menampilkan pesan bahwa data file pelaku berhasil di update
        printf("SELAMAT DATA BERHASIL DI UPDATE\n");
    }
}

//SHOW CETAK TABEL
//prosedur untuk menampilkan  data file pelaku
void showFromFilePelaku(Pelaku PelakuComplete[], int a)
{
    //variabel untuk menghitung panjang kolom tabel pelaku
    int ukuranKID = 0;
    int ukuranKNAMA = 0;
    int ukuranKforeignkey = 0;
    int ukuranKKERUGIAN = 0;

    //looping untuk mencari panjang kolom tabel pelaku
    for (int i = 0; i < a; i++) {
        if (ukuranKID < strlen(PelakuComplete[i].ID))//jika panjang ID lebih kecil dari strlen
        {
         ukuranKID = strlen(PelakuComplete[i].ID); 
        }
        if (ukuranKNAMA < strlen(PelakuComplete[i].NAMA))//
        {
            ukuranKNAMA = strlen(PelakuComplete[i].NAMA);
        }
        if (ukuranKforeignkey < strlen(PelakuComplete[i].foreignkey))//
        {
            ukuranKforeignkey = strlen(PelakuComplete[i].foreignkey);
        }
        if (ukuranKKERUGIAN < strlen(PelakuComplete[i].KERUGIAN))//
        {
            ukuranKKERUGIAN = strlen(PelakuComplete[i].KERUGIAN);
        }
    }
    //Menghitung total panjang perbaris
    int totalpanjang = ukuranKID + ukuranKNAMA + ukuranKforeignkey + ukuranKKERUGIAN;

    //looping untuk MENCETAK BARIS data file pelaku
    for (int i = 0; i < a; i++) {

        printf("| %s ", PelakuComplete[i].ID);
        for (int j = 0; j < ukuranKID - strlen(PelakuComplete[i].ID); j++) {
            printf(" ");
        }
        printf("| %s ", PelakuComplete[i].NAMA);
        for (int j = 0; j < ukuranKNAMA - strlen(PelakuComplete[i].NAMA); j++) {
            printf(" ");
        }
        printf("| %s ", PelakuComplete[i].foreignkey);
        for (int j = 0; j < ukuranKforeignkey - strlen(PelakuComplete[i].foreignkey); j++) {
            printf(" ");
        }
        printf("| %s ", PelakuComplete[i].KERUGIAN);
        for (int j = 0; j < ukuranKKERUGIAN - strlen(PelakuComplete[i].KERUGIAN); j++) {
            printf(" ");
        }
        printf("|\n");   
    }

    //looping untuk mencetak PEMBATAS BAWAH tabel file pelaku
    for (int j = 0; j < totalpanjang + 16; j++) {
        printf("-");
    }
    printf("\n");
}

//SHOW CETAK TABEL
//prosedur untuk menampilkan  data file Kasus
void showFromFileKasus(Kasus DataKasus[], int f)
{
    //variabel untuk menghitung panjang kolom tabel pelaku
    int ukuranKid_kasus = 0;
    int ukuranKnama_Kasus = 0;
    int ukuranKtahun_kasus = 0;
    int ukuranKsangsi_kasus = 0;

    //looping untuk mencari panjang kolom tabel pelaku
    for (int i = 0; i < f; i++) {
        if (ukuranKid_kasus < strlen(DataKasus[i].ID_kasus))//jika panjang ID lebih kecil dari strlen
        {
         ukuranKid_kasus = strlen(DataKasus[i].ID_kasus); 
        }
        if (ukuranKnama_Kasus < strlen(DataKasus[i].nama_Kasus))//
        {
            ukuranKnama_Kasus = strlen(DataKasus[i].nama_Kasus);
        }
        if (ukuranKtahun_kasus < strlen(DataKasus[i].tahun_kasus))//
        {
            ukuranKtahun_kasus = strlen(DataKasus[i].tahun_kasus);
        }
        if (ukuranKsangsi_kasus < strlen(DataKasus[i].sangsi_kasus))//
        {
            ukuranKsangsi_kasus = strlen(DataKasus[i].sangsi_kasus);
        }
    }
    //Menghitung total panjang perbaris
    int totalpanjang = ukuranKid_kasus + ukuranKnama_Kasus + ukuranKtahun_kasus + ukuranKsangsi_kasus;

    //looping untuk MENCETAK BARIS data file Kasus
    for (int i = 0; i < f; i++) {

        printf("| %s ", DataKasus[i].ID_kasus);
        for (int j = 0; j < ukuranKid_kasus - strlen(DataKasus[i].ID_kasus); j++) {
            printf(" ");
        }
        printf("| %s ", DataKasus[i].nama_Kasus);
        for (int j = 0; j < ukuranKnama_Kasus - strlen(DataKasus[i].nama_Kasus); j++) {
            printf(" ");
        }
        printf("| %s ", DataKasus[i].tahun_kasus);
        for (int j = 0; j < ukuranKtahun_kasus - strlen(DataKasus[i].tahun_kasus); j++) {
            printf(" ");
        }
        printf("| %s ", DataKasus[i].sangsi_kasus);
        for (int j = 0; j < ukuranKsangsi_kasus- strlen(DataKasus[i].sangsi_kasus); j++) {
            printf(" ");
        }
        printf("|\n");   
    }

    //looping untuk mencetak PEMBATAS BAWAH tabel file pelaku
    for (int j = 0; j < totalpanjang + 16; j++) {
        printf("-");
    }
    printf("\n");
}

//prosedur untuk JOINT, menggabungkan dua data file dengan foreign key yang sama
void joinDataPelaku(Pelaku PelakuComplete[], int a, Kasus DataKasus[], int f) {
    //Variabel untuk mencetak hasil gabungan data dari file Pelaku dan kasus
    int ukuranKID = 0;
    int ukuranKNAMA = 0;
    int ukuranKforeignkey = 0;
    int ukuranKKERUGIAN = 0;
    int ukuranKnama_Kasus = 0;
    int ukuranKtahun_kasus = 0;
    int ukuranKsangsi_kasus = 0;

    //Looping untuk mencari panjang kolom masing masing tabel 
    for (int i = 0; i < a; i++) {
        if (ukuranKID < strlen(PelakuComplete[i].ID)) {
            ukuranKID = strlen(PelakuComplete[i].ID);
        }
        if (ukuranKNAMA < strlen(PelakuComplete[i].NAMA)) {
            ukuranKNAMA = strlen(PelakuComplete[i].NAMA);
        }    
        if (ukuranKforeignkey < strlen(PelakuComplete[i].foreignkey)) {
            ukuranKforeignkey = strlen(PelakuComplete[i].foreignkey);
        }    
        if (ukuranKKERUGIAN < strlen(PelakuComplete[i].KERUGIAN)){
            ukuranKKERUGIAN = strlen(PelakuComplete[i].KERUGIAN);
        }
    }  

    // Loop untuk menentukan panjang maksimum setiap kolom di tabel Kasus
    for (int i = 0; i < f; i++) {
        if (ukuranKnama_Kasus < strlen(DataKasus[i].nama_Kasus)) {
            ukuranKnama_Kasus = strlen(DataKasus[i].nama_Kasus);
        }    
        if (ukuranKtahun_kasus < strlen(DataKasus[i].tahun_kasus)) {
            ukuranKtahun_kasus = strlen(DataKasus[i].tahun_kasus);
        }    
        if (ukuranKsangsi_kasus < strlen(DataKasus[i].sangsi_kasus)) {
            ukuranKsangsi_kasus = strlen(DataKasus[i].sangsi_kasus);
        }
    }
    // Menghitung total panjang per baris tabel
    int totalpanjang = ukuranKID + ukuranKNAMA + ukuranKforeignkey + ukuranKKERUGIAN + ukuranKnama_Kasus + ukuranKtahun_kasus + ukuranKsangsi_kasus + 7 * 3; //7 kolom

    // Mencetak bagian atas tabel
    printf("|");
    printf(" %-*s |", ukuranKID, "ID Pelaku");
    printf(" %-*s |", ukuranKNAMA, "Nama Pelaku");
    printf(" %-*s |", ukuranKforeignkey, "Foreign Key");
    printf(" %-*s |", ukuranKKERUGIAN, "Kerugian");
    printf(" %-*s |", ukuranKnama_Kasus, "Nama Kasus");
    printf(" %-*s |", ukuranKtahun_kasus, "Tahun Kasus");
    printf(" %-*s |\n", ukuranKsangsi_kasus, "Sangsi Kasus");

     // Mencetak garis pemisah header
    for (int j = 0; j < totalpanjang; j++) {
        printf("-");
    }
    printf("\n");

    // Loop untuk mencocokkan foreignkey dari PelakuComplete dan DataKasus
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < f; j++) {
            if (strcmp(PelakuComplete[i].foreignkey, DataKasus[j].ID_kasus) == 0) {
                //string akan dicetak rata kiri dengan panjang kolom yang sesuai nilai
                // jika sesuai maka akan mencetak data gabungan
                printf("| %-*s |", ukuranKID, PelakuComplete[i].ID);
                printf(" %-*s |", ukuranKNAMA, PelakuComplete[i].NAMA);
                printf(" %-*s |", ukuranKforeignkey, PelakuComplete[i].foreignkey);
                printf(" %-*s |", ukuranKKERUGIAN, PelakuComplete[i].KERUGIAN);
                printf(" %-*s |", ukuranKnama_Kasus, DataKasus[j].nama_Kasus);
                printf(" %-*s |", ukuranKtahun_kasus, DataKasus[j].tahun_kasus);
                printf(" %-*s |\n", ukuranKsangsi_kasus, DataKasus[j].sangsi_kasus);
            }
        }
    }
     // Mencetak garis pemisah bawah tabel
    for (int j = 0; j < totalpanjang; j++) {
        printf("-");
    }
    printf("\n"); 
}
//DELETE





                       