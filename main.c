#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#define TABLE_SIZE 1000
#define LOAD_FACTOR 0.6
#define MAX_WORD_LENGTH 1000

unsigned long long hashTable[TABLE_SIZE]; // Hashing tablosu

unsigned long long hashFunction(const char* str) {
    unsigned long long key = 0;
    int length = strlen(str);
    for (int i = 0; i < length; i++) {
        key = 61 * key + str[i];
    }
    return key;
}

unsigned long long doubleHash(const char* str, int i) {
    unsigned long long h1 = hashFunction(str);
    unsigned long long h2 = 1 + (hashFunction(str) % (TABLE_SIZE - 1));
    return (h1 + i * h2) % TABLE_SIZE;
}

void createHashTable() {
    FILE* dosya = fopen("/Users/suleymanyag/development/c_projeler/hasing_projesi/kelimeler.text", "r");
    if (dosya == NULL) {
        printf("Dosya açılamadı.\n");
        return;
    }

    char kelime[100];
    while (fgets(kelime, sizeof(kelime), dosya)) {
        kelime[strcspn(kelime, "\n")] = '\0'; // Satır sonu karakterini kaldır
        int i = 0;
        while (i < TABLE_SIZE) {
            unsigned long long index = doubleHash(kelime, i);
            if (hashTable[index] == 0) {
                hashTable[index] = hashFunction(kelime);
                break;
            }
            i++;
        }
    }

    fclose(dosya);
}
char* getRandomWord() {
    FILE* dosya = fopen("/Users/suleymanyag/development/c_projeler/hasing_projesi/kelimeler.text", "r");
    if (dosya == NULL) {
        printf("Dosya açılamadı.\n");
        return NULL;
    }

    // Dosyanın sonuna kadar okuyarak kelime sayısını bulma
    int kelimeSayisi = 0;
    char kelime[MAX_WORD_LENGTH];
    while (fgets(kelime, MAX_WORD_LENGTH, dosya) != NULL) {
        kelimeSayisi++;
    }

    // Rastgele kelimeyi seçme
    time_t t;
    srand((unsigned)time(&t));
    int rastgeleIndex = rand() % kelimeSayisi;

    // Dosyanın başına geri dönme ve rastgele kelimeyi seçme
    rewind(dosya);
    int currentIndex = 0;
    while (fgets(kelime, MAX_WORD_LENGTH, dosya) != NULL) {
        if (currentIndex == rastgeleIndex) {
            fclose(dosya);
            kelime[strcspn(kelime, "\n")] = '\0'; // Satır sonu karakterini kaldır
            char* randomWord = malloc((strlen(kelime) + 1) * sizeof(char));
            strcpy(randomWord, kelime);
            return randomWord;
        }
        currentIndex++;
    }

    fclose(dosya);
    printf("Kelime bulunamadı.\n");
    return NULL;
}

bool isAnagramInHashTable(const char* anagram) {
    unsigned long long key = hashFunction(anagram);
    int i = 0;
    while (i < TABLE_SIZE) {
        unsigned long long index = doubleHash(anagram, i);
        if (hashTable[index] == key) {
            return true;
        } else if (hashTable[index] == 0) {
            return false;
        }
        i++;
    }
    return false;
}

int main() {
    createHashTable();

    // Rasgele kelimeyi ekrana yazdırma
    char* randomWord = getRandomWord();
    if (randomWord != NULL) {
        printf("Rasgele Kelime: %s\n", randomWord);

        // Kullanıcıdan anagramı isteme
        char anagram[100];
        printf("Anagrami giriniz: ");
        scanf("%s", anagram);

        // Anagramın hash tablosunda olup olmadığını kontrol etme
        if (isAnagramInHashTable(anagram)) {
            printf("Anagram hash tablosunda bulunuyor.\n");
        } else {
            printf("Anagram hash tablosunda bulunmuyor.\n");
        }

        free(randomWord);
    }

    return 0;
}