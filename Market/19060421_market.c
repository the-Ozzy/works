#include <stdio.h>
#include "cs50.h"
#include <ctype.h>
#include <stdlib.h>
#include <locale.h>
/**
 *      CS50 Kütüphanesi
 * string --> "typedef char* string" ifadesidir
 * get_char --> Kullanıcıdan char karakteri alır. Kullanıcının farklı birşey(karakter katarı vb.) girmesini engeller
 * get_string -->Kullanıcıdan bir karakter katarı alınmasını sağlar
 * get_int--> Kullanıcıdan integer bir değer alır
 * 
 * get_x --> Tüm get fonksiyonları x'in belirttiği veriyi kullanıcıdan kontrollü olarak alır.
 * 
 * Benim bilgisayarımda "gcc 19060421_market.c cs50.c -o market" ifadesi ek kütüphaneyi ekleyerek derledi
 * 
 */
typedef struct one_struct_to_rule_them_all
{
    string adi; int maliyet;
    char kategori; char tipi;
    string paketlenme_tarihi; string alinma_tarihi;
    string son_kullanma_tarihi;
    char reyon_tarafi;int reyon_no;
    struct one_struct_to_rule_them_all * next;
} urunler;
/**
 * urunler structında gerekli tüm bilgileri topladım
 * ardından, depo ve temp isminde birer ürün pointerı oluşturdum
 * depo pointerı tüm verileri depolamak için, temp ise farklı blokları depoya aktarmak için kullandığım pointer
 */
urunler* depo; urunler* temp;

void ekle(urunler* tmp);// fonksiyonları kendi alanlarında açıkladım
void print(char kategori);

int main(void)
{
    setlocale(LC_ALL,"Turkish");// stringlerde türkçe karakterler kullanabilmek için türkçe karakterleri ekledim
    char secenek =(char)toupper(get_char("Varsayılan değerlerle programın demosunu çalıştırmak istiyorsanız D, programa girmek istiyorsanız S girin: "));
    //
    temp = (urunler*)malloc(sizeof(urunler));//
    if (secenek == 'D')
    {
        temp->adi = "Biftek"; temp->maliyet = 42; temp->kategori = 'E'; temp->tipi = 'R';
        temp->paketlenme_tarihi = "12-10-2020";temp->son_kullanma_tarihi = "12-11-2020"; temp->next = NULL;
        ekle(temp);//
        temp = (urunler*)malloc(sizeof(urunler));
        temp->adi = "Elma";temp->maliyet = 5;temp->kategori = 'T';temp->tipi= 'S';temp->alinma_tarihi = "20-09-2020",temp->next = NULL;
        ekle(temp);//
        print('H');
    }
    else
    {
        while (true)// Kullanıcının istediği kadar veri girebilmesini sağlamak için sonsuz döngü
        {
            temp = (urunler*)malloc(sizeof(urunler));
            temp->kategori =(char)toupper(get_char("Kategoriyi Giriniz: Et: E\tTarım Ürünleri: T\tSüt Ürünleri: S\tKonserveler: K\tGıda Dışı: G: "));
            if ((temp->kategori != 'E') && (temp->kategori != 'S') && (temp->kategori != 'T') && (temp->kategori != 'K') && (temp->kategori != 'G'))
            {
                puts("Böyle bir kategori bulunmamaktadır");
                continue;// kullanıcının hatalı bir kategori seçmeye çalışması durumunda kullanıcıyı uyarır
            }
            temp->adi  = get_string("Ürünün adını giriniz(En fazla 20 karakter): ");
            temp->maliyet = get_int("Ürünün maliyetini TL olarak giriniz: ");
            temp->next = NULL;
            if ((temp->kategori == 'E')|| (temp->kategori == 'e'))// Kullanıcının et kategorisini seçmesini kontrol eder
            {
                temp->paketlenme_tarihi = get_string("Ürünün paketleme tarihini giriniz: ");
                temp->son_kullanma_tarihi = get_string("Ürünün son kullanma tarihini giriniz: ");
                temp->tipi = (char)toupper(get_char("Ürünün tipini giriniz(R: Kırmızı Et, B: Balık,P: Tavuk: "));
                ekle(temp);
            }
            else if ((temp->kategori == 'T')|| (temp->kategori == 't'))// Kullanıcının tarım ürünleri kategorisini seçmesini kontrol eder
            {
                temp->alinma_tarihi = get_string("Ürünün alınma tarihini giriniz :");
                temp->tipi = (char)toupper(get_char("Ürünün tipini giriniz(M: Meyve, S: Sebze):"));
                ekle(temp);
            }
            else if ((temp->kategori == 'S')|| (temp->kategori == 's'))// Kullanıcının süt ürünleri kategorisini seçmesini kontrol eder
            {
                temp->son_kullanma_tarihi = get_string("Ürünün son kullanma tarihini giriniz: ");
                ekle(temp);
            }
            else if ((temp->kategori == 'K')|| (temp->kategori == 'k'))// Kullanıcının konserve kategorisini seçmesini kontrol eder
            {
                temp->reyon_tarafi = (char)toupper(get_char("Reyon tarafını giriniz(A/B):"));
                temp->reyon_no = get_int("Reyon numarasını giriniz: ");
                temp->son_kullanma_tarihi = get_string("Ürünün son kullanma tarihini AY ve YIL olarak giriniz :");
                ekle(temp);
            }
            else// Kullanıcının gıda dışı kategorisini seçmesini kontrol eder
            {
                temp->reyon_no = get_int("Reyon numarasını giriniz: ");
                temp->reyon_tarafi = (char)toupper(get_char("Reyon tarafını giriniz(A/B): "));
                temp->tipi = (char)toupper(get_char("Ürünün tipini giriniz(C:Temizlik Ürünleri P:Eczane D:Diğer)"));
                ekle(temp);
            }
            char ask = (char)toupper(get_char("Envanteri kontrol etmek istermisiniz? (E/H)\nEnvanteri kontrol etmeniz durumunda envanter gösterildikten sonra programdan çıkılır:\t"));
            if (ask == 'H')// kullanıcın yeni veri girmesi için başa döner
                continue;
            else if (ask == 'E')// kullanıcının istediği verilerin basılacağı kısma geçer
            {
            
                ask = (char)toupper(get_char("Hangi ürünleri görmek istiyorsunuz?\t(E-T-S-K-G)\t Hepsini görmek için H: "));
                if ((ask != 'E') && (ask != 'S') &&(ask != 'T') &&(ask != 'K') && (ask != 'G') && (ask != 'H'))
                {// kullanıcının hatalı bir kategori karakteri girmesine karşın tüm verileri bastırır
                    puts("Böyle bir seçenek yok. Hepsi gösteriliyor...");
                    print('H');
                    return 0;
                }
                else// kullanıcının isteği veri/verileri ekrana bastırır
                {
                    ask = (char)toupper(ask);
                    print(ask);
                    return 0;
                }
            }
            else //diğer durumda başa dönülür
                continue;        
        }
        
    }
    
}
 
void ekle(urunler* tmp)//
{
    /**
     * mainde oluşturulmuş ve doldurulmuş olan hafıza kısımını depoya eklendiği fonksiyon
     * depo boşsa zaten depoyla tmp aynı veri yapısı olduğundan depoyu tmp değişkenine eşitleriz
     * bu şekilde bağlantılı listenin ilk zinciri oluşur
     * diğer durumda tmp yi deponun sonuna ekler
     */
    if (depo == NULL)
    {
        depo = tmp;
    }
    else
    {
        urunler* iter = depo;
        while(iter->next != NULL){ iter = iter->next;}
        iter->next = tmp;
    }
    
}
void print(char kategori)
{
    urunler* iter = depo;
    if (depo == NULL)// deponun boş olması durumunu  belirtir
    {
        puts("Depoda hiç ürününüz bulunmamaktadır");
        return;
    }
    
    if (kategori == 'E')//Et Ürünlerini ekrana yazdırır
    {
        while(iter->next != NULL)
        {
            if (iter->kategori == kategori)
            {
                printf("Ürün Adı: %s\tMaliyeti: %iTL\tKategorisi: Et\tTipi: %c\tPaketlenme Tarihi: %s\tSon Kullanma Tarihi: %s\n",iter->adi,iter->maliyet,iter->tipi,iter->paketlenme_tarihi,iter->son_kullanma_tarihi);
            }
            iter = iter->next;
        }
        if (iter->kategori == kategori)
            printf("Ürün Adı: %s\tMaliyeti: %iTL\tKategorisi: Et\tTipi: %c\tPaketlenme Tarihi: %s\tSon Kullanma Tarihi: %s\n",iter->adi,iter->maliyet,iter->tipi,iter->paketlenme_tarihi,iter->son_kullanma_tarihi);
        return;
    }
    else if (kategori == 'T')//Tarım Ürünlerini ekrana yazdırır
    {
        while (iter->next != NULL)
        {
            if (iter->kategori == kategori)
            {
                printf("ÜrÜn Adı: %s\tMaliyeti: %iTL\tKategorisi: Tarım\tTipi: %c\tAlınma Tarihi: %s\n",iter->adi,iter->maliyet,iter->tipi,iter->alinma_tarihi) ;   
            }
            iter = iter->next;
        }
        if (iter->kategori == kategori)
            printf("ÜrÜn Adı: %s\tMaliyeti: %iTL\tKategorisi: Tarım\tTipi: %c\tAlınma Tarihi: %s\n",iter->adi,iter->maliyet,iter->tipi,iter->alinma_tarihi) ;   
        return;
    }
    else if (kategori == 'S')//Süt Ürünlerini ekrana yazdırır
    {
        while (iter->next != NULL)
        {
            if (iter->kategori == kategori)
            {
            printf("Ürün Adı: %s\tMaliyeti: %iTL\tKategorisi: Süt Ürünleri\tSon Kullanma Tarihi: %s\n",iter->adi,iter->maliyet,iter->son_kullanma_tarihi);
            }
            iter = iter->next;
        }
        if (iter->kategori == kategori)
            printf("Ürün Adı: %s\tMaliyeti: %iTL\tKategorisi: Süt Ürünleri\tSon Kullanma Tarihi: %s\n",iter->adi,iter->maliyet,iter->son_kullanma_tarihi);
        return;
    }
    else if (kategori == 'K')//Konserve Ürünlerini ekrana yazdırır
    {
        while (iter->next != NULL)
        {
            if (iter->kategori == kategori)
            {
                printf("Ürün Adı: %s\tMaliyeti: %iTL\tKategorisi: Konserve\tReyon Numarası: %i\tReyon Tarafı: %c\tSon Kullanma Tarihi: %s\n",iter->adi,iter->maliyet,iter->reyon_no,iter->reyon_tarafi,iter->son_kullanma_tarihi);
            }
            iter = iter->next;
        }
        if (iter->kategori == kategori)
            printf("Ürün Adı: %s\tMaliyeti: %iTL\tKategorisi: Konserve\tReyon Numarası: %i\tReyon Tarafı: %c\tSon Kullanma Tarihi: %s\n",iter->adi,iter->maliyet,iter->reyon_no,iter->reyon_tarafi,iter->son_kullanma_tarihi);
        return;
    }
    else if (kategori == 'G')//Gıda Dışı Ürünleri ekrana yazdırır
    {
        while (iter->next != NULL)
        {
            if (iter->kategori == kategori)
            {
                printf("Ürün Adı: %s\tMaliyeti: %iTL\tKategorisi: Gıda Dışı\tTipi: %c\tReyon No: %i\tReyon Tarafı: %c\n",iter->adi,iter->maliyet,iter->tipi,iter->reyon_no,iter->reyon_tarafi);
            }
            iter = iter->next;
        }
        if (iter->kategori == kategori)
            printf("Ürün Adı: %s\tMaliyeti: %iTL\tKategorisi: Gıda Dışı\tTipi: %c\tReyon No: %i\tReyon Tarafı: %c\n",iter->adi,iter->maliyet,iter->tipi,iter->reyon_no,iter->reyon_tarafi);
        return;
    }
    else//Bütün Ürünleri ekrana yazdırır
    {
       
        while (iter->next != NULL)
        {
            if (iter->kategori == 'E')
            {
                printf("Ürün Adı: %s\tMaliyeti: %iTL\tKategorisi: Et\tTipi: %c\tPaketlenme Tarihi: %s\tSon Kullanma Tarihi: %s\n",iter->adi,iter->maliyet,iter->tipi,iter->paketlenme_tarihi,iter->son_kullanma_tarihi);
                iter = iter->next;
            }
            else if (iter->kategori == 'T')
            {
                printf("ÜrÜn Adı: %s\tMaliyeti: %iTL\tKategorisi: Tarım\tTipi: %c\tAlınma Tarihi: %s\n",iter->adi,iter->maliyet,iter->tipi,iter->alinma_tarihi) ;   
                iter = iter->next;
            }
            else if (iter->kategori == 'S')
            {
                printf("Ürün Adı: %s\tMaliyeti: %iTL\tKategorisi: Süt Ürünleri\tSon Kullanma Tarihi: %s\n",iter->adi,iter->maliyet,iter->son_kullanma_tarihi);
                iter = iter->next;
            }
            else if (iter->kategori == 'K')
            {
                printf("Ürün Adı: %s\tMaliyeti: %iTL\tKategorisi: Konserve\tReyon Numarası: %i\tReyon Tarafı: %c\tSon Kullanma Tarihi: %s\n",iter->adi,iter->maliyet,iter->reyon_no,iter->reyon_tarafi,iter->son_kullanma_tarihi);
                iter = iter->next;
            }
            else
            {
                printf("Ürün Adı: %s\tMaliyeti: %iTL\tKategorisi: Gıda Dışı\tTipi: %c\tReyon No: %i\tReyon Tarafı: %c\n",iter->adi,iter->maliyet,iter->tipi,iter->reyon_no,iter->reyon_tarafi);
                iter = iter->next;
            }
        }
        if (iter->kategori == 'E')
        {
            printf("Ürün Adı: %s\tMaliyeti: %iTL\tKategorisi: Et\tTipi: %c\tPaketlenme Tarihi: %s\tSon Kullanma Tarihi: %s\n",iter->adi,iter->maliyet,iter->tipi,iter->paketlenme_tarihi,iter->son_kullanma_tarihi);
        }
        else if (iter->kategori == 'T')
        {
            printf("ÜrÜn Adı: %s\tMaliyeti: %iTL\tKategorisi: Tarım\tTipi: %c\tAlınma Tarihi: %s\n",iter->adi,iter->maliyet,iter->tipi,iter->alinma_tarihi) ;   
        }
        else if (iter->kategori == 'S')
        {
            printf("Ürün Adı: %s\tMaliyeti: %iTL\tKategorisi: Süt Ürünleri\tSon Kullanma Tarihi: %s\n",iter->adi,iter->maliyet,iter->son_kullanma_tarihi);
        }
        else if (iter->kategori == 'K')
        {
            printf("Ürün Adı: %s\tMaliyeti: %iTL\tKategorisi: Konserve\tReyon Numarası: %i\tReyon Tarafı: %c\tSon Kullanma Tarihi: %s\n",iter->adi,iter->maliyet,iter->reyon_no,iter->reyon_tarafi,iter->son_kullanma_tarihi);
        }
        else
        {
            printf("Ürün Adı: %s\tMaliyeti: %iTL\tKategorisi: Gıda Dışı\tTipi: %c\tReyon No: %i\tReyon Tarafı: %c\n",iter->adi,iter->maliyet,iter->tipi,iter->reyon_no,iter->reyon_tarafi);
        }
    }   
}