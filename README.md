Üretim Hattı Planlama Programı
Bu proje, dinamik programlama kullanarak bir üretim hattındaki işleri minimum toplam süreyle tamamlamak için geliştirilmiştir. Projede, her işin her makinedeki tamamlanma süresi ve makineler arası geçiş maliyetleri göz önünde bulundurularak, tüm işler sırayla tamamlanacak şekilde planlanmaktadır.

Problem Tanımı
Bir üretim hattında, n adet iş (örneğin, bir ürünün parçalarının işlenmesi) sırayla tamamlanmalıdır. Bu işler, m farklı makinede yapılabilir. Her işin her makinedeki tamamlanma süresi farklıdır ve makineler arasında geçiş yapılması durumunda bir geçiş maliyeti (örneğin, makine ayar süresi veya taşıma maliyeti) ortaya çıkar. Buradaki amaç, tüm işleri sırayla tamamlamak için minimum toplam süreyi bulmaktır. Toplam süre, işlerin tamamlanma süreleri ve makineler arası geçiş maliyetlerinin toplamıdır.

Matris Zinciri Çarpımı İle İlişkisi
Bu problem, matris zinciri çarpımı problemine benzer şekilde dinamik programlama yaklaşımıyla çözülür. Her işin ve makinenin belirli bir sıralamada yer alması gerektiğinden, en uygun çözüm için adım adım seçim yapılır. Bu tür bir problemde, geçişlerin ve sürelerin hesaplanmasında kullanılan dinamik programlama yöntemi, alt problemleri çözerek ana probleme yaklaşır.

Tablolama ve Hafızalama Algoritmaları
Tablolama (Bottom-Up Approach): Bu yöntem, küçük alt problemlerin çözülmesini sağlayarak tüm problemi çözmek için kullanılır. Her adımda, önceki adımlardan elde edilen sonuçlar kullanılarak çözüm genişletilir.

Hafızalama (Top-Down Approach): Bu yöntemde, çözüm süreci sırasında her alt problem yalnızca bir kez hesaplanır ve sonuçlar hafızada saklanarak tekrar hesaplamaların önüne geçilir.

Adım adım uygulanan algoritmaların açıklamaları:

İşlerin sıralanması: İlk adımda, her işin her makinedeki işlem süresi ve geçiş maliyetleri göz önüne alınarak, hangi makinelerde hangi işlerin yapılacağı belirlenir.

Geçiş Maliyetlerinin Hesaplanması: Makine değişimi durumunda ortaya çıkan geçiş maliyetleri hesaplanır ve toplam süreyi minimize etmek için bu maliyetler göz önünde bulundurulur.

Kod Açıklamaları ve Test Sonuçları
Kod Açıklamaları
Kod, dinamik programlama ile en düşük toplam süreyi hesaplamak için aşağıdaki adımları izler:

Girdi Alma: Kullanıcıdan iş sayısı, makine sayısı, her işin her makinedeki işlem süresi ve makineler arası geçiş maliyetleri alınır.

Dinamik Programlama Tablosu Oluşturma: Her işin her makineye ait maliyetini depolayan bir dinamik programlama tablosu (dp) oluşturulur. Bu tablo, önceki işlerin çözümünü kullanarak her işin çözümünü adım adım hesaplar.

Geçiş Maliyetlerinin Hesaplanması: Dinamik programlama tablosunda, bir işten diğerine geçerken kullanılan geçiş maliyetleri ve her işin tamamlanma süreleri dikkate alınarak toplam süre hesaplanır.

Sonuç Hesaplama: Son işin tamamlanması için minimum toplam süre, dinamik programlama tablosundaki sonuçlardan seçilir.

c
Kopyala
Düzenle
// En küçük değeri döndüren yardımcı fonksiyon
int en_kucuk(int a, int b) { return (a < b) ? a : b; }

int main() {
    setlocale(LC_ALL, "Turkish");
    
    int is_sayisi, makine_sayisi;
    int is_maliyetleri[MAKS][MAKS], gecis_maliyetleri[MAKS][MAKS];
    int dp[MAKS][MAKS];
    int i, j, k;

    // Girdi alma ve işlemler
    printf("Üretim hattı planlama programı\n\n");
    printf("İş sayısını girin (n): ");
    scanf("%d", &is_sayisi);
    printf("Makine sayısını girin (m): ");
    scanf("%d", &makine_sayisi);

    // İşlerin işlem süreleri
    printf("\nHer işin makine işlem sürelerini girin:\n");
    for (i = 0; i < is_sayisi; i++) {
        for (j = 0; j < makine_sayisi; j++) {
            printf("%d. işin %d. makinedeki süresi: ", i+1, j+1);
            scanf("%d", &is_maliyetleri[i][j]);
        }
    }

    // Geçiş maliyetlerini alma
    printf("\nMakine geçiş maliyetlerini girin (sadece farklı makineler için):\n");
    for (i = 0; i < makine_sayisi; i++) {
        for (j = 0; j < makine_sayisi; j++) {
            if (i == j) {
                gecis_maliyetleri[i][j] = 0; 
            } else {
                printf("%d. makineden %d. makineye geçiş maliyeti: ", i+1, j+1);
                scanf("%d", &gecis_maliyetleri[i][j]);
            }
        }
    }

    // Dinamik programlama tablosu ile çözüm hesaplama
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

    // Sonucu yazdırma
    printf("\nMinimum toplam süre: %d\n", sonuc);
    return 0;
}
Test Sonuçları
Testlerde, farklı iş sayıları ve makineler kullanılarak, her senaryo için minimum toplam süre hesaplanmıştır. Örnek girdi:

less
Kopyala
Düzenle
İş sayısını girin (n): 3
Makine sayısını girin (m): 2

Her işin makine işlem sürelerini girin:
1. işin 1. makinedeki süresi: 7
1. işin 2. makinedeki süresi: 5
2. işin 1. makinedeki süresi: 2
2. işin 2. makinedeki süresi: 3
3. işin 1. makinedeki süresi: 4
3. işin 2. makinedeki süresi: 1

Makine geçiş maliyetlerini girin (sadece farklı makineler için):
1. makineden 2. makineye geçiş maliyeti: 2
2. makineden 1. makineye geçiş maliyeti: 1
Çıktı:

nginx
Kopyala
Düzenle
Minimum toplam süre: 9
Zaman ve Uzay Karmaşıklığı
Zaman Karmaşıklığı: Algoritmanın zaman karmaşıklığı, iş sayısı (n) ve makine sayısı (m) ile doğru orantılıdır. Her iş ve makine için geçiş hesaplamaları yapılır, bu nedenle karmaşıklık 
𝑂
(
𝑛
×
𝑚
2
)
O(n×m 
2
 ) olacaktır.

Uzay Karmaşıklığı: Dinamik programlama tablosu, her iş için her makineye ait bir değer saklar. Bu nedenle, uzay karmaşıklığı da 
𝑂
(
𝑛
×
𝑚
)
O(n×m) olarak hesaplanır.