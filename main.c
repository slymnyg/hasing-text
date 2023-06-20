#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>

#define MAX_WORD_LENGTH 100
#define TABLE_SIZE 10000
#define LOAD_FACTOR 0.6

typedef struct Node
{
    char word[MAX_WORD_LENGTH];
    struct Node *next;
} Node;

typedef struct HashTablo
{
    Node *table[TABLE_SIZE];
} HashTablo;

unsigned int hashFonksiyonu(const char *str)
{
    unsigned int key = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        key = 61 * key + str[i];
    }
    return key % TABLE_SIZE;
}

unsigned int hashFonksiyonu2(const char *str)
{
    unsigned int key = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        key = 67 * key + str[i];
    }
    return 1 + (key % (TABLE_SIZE - 1));
}

Node *create_node(const char *word)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    strcpy(new_node->word, word);
    new_node->next = NULL;
    return new_node;
}

HashTablo *hashTablosuOlustur()
{
    HashTablo
        *hash_table = (HashTablo
                           *)malloc(sizeof(HashTablo));
    memset(hash_table->table, 0, sizeof(hash_table->table));
    return hash_table;
}

void kelimeEkle(HashTablo *hash_table, const char *word)
{
    unsigned int index = hashFonksiyonu(word);
    unsigned int index2 =hashFonksiyonu2(word);
    unsigned int i = 0;

    while (hash_table->table[index] != NULL)
    {
        index = (index + i * index2) % TABLE_SIZE;
        i++;
    }

    Node *new_node = create_node(word);
    hash_table->table[index] = new_node;
}

bool anagramMi(const char* kelime1, const char* kelime2) {
    int histogram1[26] = {0};
    int histogram2[26] = {0};

    // İlk kelimenin karakter histogramını oluştur
    int i = 0;
    while (kelime1[i] != '\0') {
        if (isalpha(kelime1[i])) {
            int index = tolower(kelime1[i]) - 'a';
            histogram1[index]++;
        }
        i++;
    }

    // İkinci kelimenin karakter histogramını oluştur
    i = 0;
    while (kelime2[i] != '\0') {
        if (isalpha(kelime2[i])) {
            int index = tolower(kelime2[i]) - 'a';
            histogram2[index]++;
        }
        i++;
    }

    // Histogramları karşılaştır ve anagram olup olmadığını kontrol et
    for (int j = 0; j < 26; j++) {
        if (histogram1[j] != histogram2[j]) {
            return false;
        }
    }

    return true;
}
Node* kelimeAra(HashTablo* hash_table, const char* word) {
    unsigned int index = hashFonksiyonu(word);
    unsigned int index2 = hashFonksiyonu2(word);
    unsigned int i = 0;

    while (hash_table->table[index] != NULL) {
        if (strcasecmp(hash_table->table[index]->word, word) == 0) {
            return hash_table->table[index];
        } else if (anagramMi(hash_table->table[index]->word, word)) {
            return hash_table->table[index];
        }
        index = (index + i * index2) % TABLE_SIZE;
        i++;
    }

    return NULL;
}

void dosyadakiKelimeleriHasle(HashTablo *hash_table, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Failed to open file: %s\n", filename);
        exit(1);
    }

    char word[MAX_WORD_LENGTH];
    while (fscanf(file, "%s", word) != EOF)
    {
        kelimeEkle(hash_table, word);
    }
    fclose(file);
}
/* 
int anagramMi(const char *word1, const char *word2)
{
    if (strlen(word1) != strlen(word2))
    {
        return 0;
    }

    int count[26] = {0};
    int len = strlen(word1);

    for (int i = 0; i < len; i++)
    {
        count[tolower(word1[i]) - 'a']++;
        count[tolower(word2[i]) - 'a']--;
    }

    for (int i = 0; i < 26; i++)
    {
        if (count[i] != 0)
        {
            return 0;
        }
    }

    return 1;
}
 */
Node *randomKelimeGetir(HashTablo *hash_table)
{
    Node *random_node = NULL;
    while (random_node == NULL)
    {
        unsigned int random_index = rand() % TABLE_SIZE;
        random_node = hash_table->table[random_index];
    }
    return random_node;
}

int main()
{
    HashTablo
        *hash_table = hashTablosuOlustur();
    dosyadakiKelimeleriHasle(hash_table, "kelimeler.txt");

    srand(time(NULL));

    char kelime[MAX_WORD_LENGTH];
    int cikisMi = 0;
    int yeniKelimeMi= 1;

    while (!cikisMi)
    {
        if (yeniKelimeMi)
        {
            Node *random_node = randomKelimeGetir(hash_table);
            if (random_node != NULL)
            {
                strcpy(kelime, random_node->word);
                printf("Rasgele Kelime : %s\n", kelime);
            }
            yeniKelimeMi= 0;
        }

        printf("Anagrami girin (çıkmak için - ): ");
        scanf("%s", kelime);

        if (strcmp(kelime, "-") == 0 || strcmp(kelime, "-") == 0)
        {
            cikisMi = 1;
            continue;
        }

        // Büyük harfe dönüştürme
        for (int i = 0; kelime[i] != '\0'; i++)
        {
            kelime[i] = toupper(kelime[i]);
        }

        Node *result = kelimeAra(hash_table, kelime);
        if (result != NULL)
        {
            unsigned int index = hashFonksiyonu(kelime);
            printf("✅ '%s' kelimesi  hash tablosununda %u. indexte\n", kelime, index);
        }
        else
        {
            printf("❌'%s' kelimesi hash tablosunda mevcut değil\n", kelime);
        }

        yeniKelimeMi= 1;
    }

    return 0;
}