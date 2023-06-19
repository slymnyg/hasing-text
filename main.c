#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLO_BOYUTU 1000
#define DOLULUK_FAKTORU 0.6

#define MAX_LINE_LENGTH 100
#define MAX_ROWS 100
#define MAX_WORDS 100
void dosyaOku(const char* dosyaAdi) {
    FILE* dosya = fopen(dosyaAdi, "r");
    if (dosya == NULL) {
        printf("Dosya açılamadı.\n");
        return;
    }
    
    char satir[MAX_LINE_LENGTH];
    char kelimeler[MAX_ROWS][MAX_WORDS][MAX_LINE_LENGTH];
    int satirSayisi = 0;
    
    while (fgets(satir, MAX_LINE_LENGTH, dosya) != NULL && satirSayisi < MAX_ROWS) {
        char* kelime = strtok(satir, " \t\n");
        int kelimeSayisi = 0;
        
        while (kelime != NULL && kelimeSayisi < MAX_WORDS) {
            strcpy(kelimeler[satirSayisi][kelimeSayisi], kelime);
            kelime = strtok(NULL, " \t\n");
            kelimeSayisi++;
        }
        
        satirSayisi++;
    }
    
    fclose(dosya);
    
    // Örnek olarak, kelimeleri ekrana yazdıralım
    for (int i = 0; i < satirSayisi; i++) {
        printf("Satır %d: ", i+1);
        for (int j = 0; j < MAX_WORDS && kelimeler[i][j][0] != '\0'; j++) {
            printf("%s ", kelimeler[i][j]);
        }
        printf("\n");
    }
 }
/*
    FILE* dosya = fopen(dosyaAdi, "r");
    if (dosya == NULL) {
        printf("Dosya açılamadı.\n");
        return;
    }
    
    char satir[MAX_LINE_LENGTH];
    char* kelimeler[MAX_ROWS][MAX_WORDS];
    int satirSayisi = 0;
    
    while (fgets(satir, MAX_LINE_LENGTH, dosya) != NULL && satirSayisi < MAX_ROWS) {
        char* kelime = strtok(satir, " \t\n");
        int kelimeSayisi = 0;
        
        while (kelime != NULL && kelimeSayisi < MAX_WORDS) {
            kelimeler[satirSayisi][kelimeSayisi] = strdup(kelime);
            
            kelime = strtok(NULL, " \t\n");
            kelimeSayisi++;
        }
        
        satirSayisi++;
    }
    
    fclose(dosya);
    
    // Örnek olarak, kelimeleri ekrana yazdıralım
    for (int i = 0; i < satirSayisi; i++) {
        printf("Satır %d: ", i+1);
        for (int j = 0; j < MAX_WORDS && kelimeler[i][j] != NULL; j++) {
          char* kelime = kelimeler[i][j];
        printf("%s ", kelime);
        }
        printf("\n");
    }
    
    // Bellekten ayrılması gereken kelimeleri temizleyelim
    for (int i = 0; i < satirSayisi; i++) {
        for (int j = 0; j < MAX_WORDS && kelimeler[i][j] != NULL; j++) {
         //   free(kelimeler[i][j].toString());
        }
    }
}
typedef struct {
    char kelime[100];
} Kelime;

typedef struct {
    Kelime* tablo;
    int boyut;
    int sayac;
} HashTablosu;

unsigned long hashFonksiyonu(char* str) {
    unsigned long anahtar = 0;
    for (int i = 0; i < strlen(str); i++) {
        anahtar = 61 * anahtar + str[i];
    }
    return anahtar;
}

unsigned long ciftHashFonksiyonu(char* str, int i) {
    unsigned long h1 = hashFonksiyonu(str);
    unsigned long h2 = 1 + (hashFonksiyonu(str) % (TABLO_BOYUTU - 1));
    return (h1 + i * h2) % TABLO_BOYUTU;
}

void tabloyuBaslat(HashTablosu* hashTablosu) {
    hashTablosu->tablo = (Kelime*)malloc(TABLO_BOYUTU * sizeof(Kelime));
    hashTablosu->boyut = TABLO_BOYUTU;
    hashTablosu->sayac = 0;
}

void kelimeEkle(HashTablosu* hashTablosu, char* kelime) {
    int indeks = hashFonksiyonu(kelime) % hashTablosu->boyut;
    int i = 1;
    while (hashTablosu->tablo[indeks].kelime[0] != '\0') {
        indeks = ciftHashFonksiyonu(kelime, i) % hashTablosu->boyut;
        i++;
    }
    strcpy(hashTablosu->tablo[indeks].kelime, kelime);
    hashTablosu->sayac++;
}

int kelimeAra(HashTablosu* hashTablosu, char* kelime) {
    int indeks = hashFonksiyonu(kelime) % hashTablosu->boyut;
    int i = 1;
    while (strcmp(hashTablosu->tablo[indeks].kelime, kelime) != 0) {
        if (hashTablosu->tablo[indeks].kelime[0] == '\0') {
            return -1;  // Kelime tabloda yok
        }
        indeks = ciftHashFonksiyonu(kelime, i) % hashTablosu->boyut;
        i++;
    }
    return indeks;  // Kelime tabloda bulundu
}

void tabloyuTemizle(HashTablosu* hashTablosu) {
    free(hashTablosu->tablo);
    hashTablosu->boyut = 0;
    hashTablosu->sayac = 0;
} */

int main() {
  /*   FILE* dosya = fopen("kelimeler.json", "r");
    if (dosya == NULL) {
        printf("Dosya acilamadi.\n");
        return 1;
    }

    HashTablosu hashTablosu;
    tabloyuBaslat(&hashTablosu);

    char kelime[100];
    while (fscanf(dosya, "%s", kelime) != EOF) {
        kelimeEkle(&hashTablosu, kelime);
    }
    fclose(dosya);

    char kullaniciGirisi[100];
    while (1) {
        printf("Bir kelime girin (Cikis icin 'q' ya da 'Q' tusuna basin): ");
        scanf("%s", kullaniciGirisi);

        if (strcmp(kullaniciGirisi, "q") == 0 || strcmp(kullaniciGirisi, "Q") == 0) {
            break;
        }

        int indeks = kelimeAra(&hashTablosu, kullaniciGirisi);
        if (indeks != -1) {
            printf("Kelime tabloda bulundu. Sirada: %d\n", indeks + 1);
        } else {
            printf("Kelime tabloda bulunamadi.\n");
        }
    }

    tabloyuTemizle(&hashTablosu);
 */

    dosyaOku("/Users/suleymanyag/development/c_projeler/hasing_projesi/kelimeler.text");
    return 0;
}