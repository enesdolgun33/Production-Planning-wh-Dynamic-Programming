#include <stdio.h>
#include <limits.h>
#include <locale.h>

#define MAKS 100

int en_kucuk(int a, int b) { return (a < b) ? a : b; }

int main() {
    setlocale(LC_ALL, "Turkish");
    
    int is_sayisi, makine_sayisi;
    int is_maliyetleri[MAKS][MAKS], gecis_maliyetleri[MAKS][MAKS];
    int dp[MAKS][MAKS];
    int i, j, k;

    printf("Üretim hattý planlama programý\n\n");
    
    printf("Ýþ sayýsýný girin (n): ");
    scanf("%d", &is_sayisi);
    printf("Makine sayýsýný girin (m): ");
    scanf("%d", &makine_sayisi);

    printf("\nHer iþin makine iþlem sürelerini girin:\n");
    for (i = 0; i < is_sayisi; i++) {
        for (j = 0; j < makine_sayisi; j++) {
            printf("%d. iþin %d. makinedeki süresi: ", i+1, j+1);
            scanf("%d", &is_maliyetleri[i][j]);
        }
    }

    printf("\nMakine geçiþ maliyetlerini girin (sadece farklý makineler için):\n");
    for (i = 0; i < makine_sayisi; i++) {
        for (j = 0; j < makine_sayisi; j++) {
            if (i == j) {
                gecis_maliyetleri[i][j] = 0; 
            } else {
                printf("%d. makineden %d. makineye geçiþ maliyeti: ", i+1, j+1);
                scanf("%d", &gecis_maliyetleri[i][j]);
            }
        }
    }

    for (j = 0; j < makine_sayisi; j++)
        dp[0][j] = is_maliyetleri[0][j];

    for (i = 1; i < is_sayisi; i++) {
        for (j = 0; j < makine_sayisi; j++) {
            dp[i][j] = INT_MAX;
            for (k = 0; k < makine_sayisi; k++) {
                int toplam = dp[i-1][k] + gecis_maliyetleri[k][j] + is_maliyetleri[i][j];
                if (toplam < dp[i][j])
                    dp[i][j] = toplam;
            }
        }
    }

    int sonuc = INT_MAX;
    for (j = 0; j < makine_sayisi; j++)
        sonuc = en_kucuk(sonuc, dp[is_sayisi-1][j]);

    printf("\nMinimum toplam süre: %d\n", sonuc);
    return 0;
}

