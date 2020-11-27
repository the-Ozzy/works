#include <stdio.h>
#include <stdlib.h>
int alarm;
typedef struct n{
  int data;
  struct n *next;
}hanoi;// Hanoi yapisinin temeli olan linked list yapisi

hanoi * kule1;hanoi *kule2; hanoi*kule3;// Hanoi kulelerinin tanimlanmasi

int ekle(int alinacak, int verilecek, int taban);// pop ve push fonksiyonlarini yonetecek fonksiyon

hanoi *pop(hanoi *root); // rootun gosterdigi kuleden FIFO kuralina gore bir disk cikaran fonksiyon

hanoi *push(hanoi *root, int sayi); // rootun gosterdigi kuleye disk ekleyen  fonksiyon

void hanoi_doldur(hanoi * doldur, int disk);// 1. kuleyi istenen sayida diskle dolduran fonksiyon

void bastir();// kuleleri ekrana yazdiracak fonksiyon
// main disindaki fonksiyonlar  detayli bir sekilde kendi alanlarinda aciklanmistir
int main (void)
{// kullanicidan argumanlar alan main fonksiyonumuz
  alarm = 0;// programdan cikis icin yazdigim yapilari kontrol icin bir degisgen
    kule1 = (hanoi*)malloc(sizeof(hanoi)); //kuleler icin gerekli alani ramdan ayirilmasi
    kule2 = (hanoi*)malloc(sizeof(hanoi));
    kule3 = (hanoi*)malloc(sizeof(hanoi));
     hanoi_doldur(kule1,4);// 1. kuleyi diskle doldurulmasi
    int taban = 5;// diger kulelerin bos olup olmadigini anlamak icin 
    kule2->data = taban;        // bos kulelerin icine birer tane taban sayisi koydum
    kule3->data = taban;       // bunlar kullaniciya gozukmez
    bastir();// kulelerin durumunun ekrana bastirilmasi
    puts("Hanoi Kulesi Oyununa Hos Geldiniz!");
    printf("Oyunun Kurallari/Kullanimi:\n1. Size soruldugu zaman; Ilk once diski hangi kuleden almak istediginizi sonra da hangi kuleye koymak istediginizi girin\n");
    printf("2. bir diski kendisinden kucuk bir diskin uzerine koyamazssiniz\n3. Eger cikmak istiyorsaniz size soruldugu zaman konsola '-1' girin, devam etmek istiyorsaniz 0 yada 0'dan buyuk bir sayi girin\n"); 
  
    int control = 0, alinacak,verilecek,kural;
    while (control != -1)
    {// kullanici -1 girene kadar durmayacak olan dongu
      alarm = 0;//alarmin sifirlanmasi
      bastir();
      printf("Diskin alinacagi kuleyi giriniz\n\t");scanf("%i",&alinacak);
      printf("Diskin koyulacagi kuleyi giriniz:\n\t");scanf("%i",&verilecek);
      kural =  ekle(alinacak,verilecek,taban);// kullanicinin kurallara uyup uymadigini kontrol eden yapi detaylari ekle fonksiyonunda
      if (kural == -1)
      {// eger ekle fonksiyonu -1 gonderirse kural ihlali kullaniciya biliren yapi
        puts("Bir diski kendisinden kucuk bir diskin uzerine koyamazssiniz");
        puts("Programdan cikmak istiyorsaniz -1 girin. devam etmek icin baska bir sayi girin");
        scanf("%i",&control);// kullanicinin programdan cikmak isteyip istemedigini sorgulanir
      }
      else
      {
        bastir();//eger kural ihlali yoksa ekrana kulelerin yeni hali bastirilir
        puts("-------------------------------------------------");
      }
     if(alarm == 0)
     {// eger ekle fonksiyonu -1 gondermediyse kullanicinin programdan cikmak isteyip istememesini sorgulayan yapi
       puts("\nCikmak istiyorsaniz -1 giriniz, istemiyorsaniz baska bir sayi girin");
       scanf("%i",&control);
       alarm = 1;
     }
  }
}
int ekle (int alinacak, int verilecek, int taban)
{
  /*
   *  ekle fonksiyonu ilk once kullanicinin degistirmek istedigi diskin istedigi kuleye uyumlu
   *  olup olmadigini kontrol eder. Bu durum Switch case yapisi ve onun icindeki if zincirleriyle
   *  kontrol edilir. Bu kontrol edilirken ayni zamanda pop ve push fonksiyonlarina gonderilecek
   *  argumanlar da balirlenmis olur. Ardindan diskin koyulacagi disk push() fonksiyonuyla
   *  yeni kulesine eklenir. Ardindan diskin eski kulesinden pop() fonksiyonu yardimiyla
   *  eski veri silinir. Ardindan main fonksionuna 0 gonderilir. Fakat eger switch yapisi 
   *  kural disi bir duruma denk gelirse pop() ve push() fonksiyonlari pas gecilir ve 
   *  main fonksiyonuna -1 degeri gonderilir.
   */
  switch (alinacak)
  {
    case 1:
      if(verilecek == 2)
      {
        if(kule1->data <  kule2->data|| kule2->data == taban)
        {
            kule2 = push(kule2,kule1->data);
            kule1 = pop(kule1);
            return 0;
        }
        else{alarm = 1; return -1;}
      }
      else if(verilecek == 3){
        if(kule1->data <  kule3->data || kule3->data == taban){
          kule3  = push(kule3,kule1->data);
          kule1 = pop(kule1);
          return 0; 
        }
        else{alarm = 1; return -1;}
      }
      break;
    case 2:
      if(verilecek == 1)
      {
        if(kule2->data < kule1->data || kule1->data == taban)
        {
            kule1 = push(kule1,kule2->data);
            kule2 = pop(kule2);
            return 0;
        }
        else{alarm =1 ;return -1;}
      }
      else if(verilecek == 3){
        if(kule2->data <  kule3->data || kule3->data == taban){
          kule3 = push(kule3,kule2->data);
          kule2 = pop(kule2);
          return 0; 
        }
        break;
      }
      case 3:
      if(verilecek == 2)
      {
        if(kule3->data < kule2->data || kule2->data == taban)
        {
            kule2 = push(kule2,kule3->data);
            kule3 = pop(kule3);
            return 0;
        }
        else{alarm = 1;return -1;}}
      else if(verilecek == 1){
        if(kule3->data <  kule1->data || kule1->data == taban){
          kule1  = push(kule1,kule3->data);
          kule3 = pop(kule3);
          return 0; 
        }
        else{alarm =1 ; return -1;}
      }
      break;
  }
  return 0;
}
hanoi * pop(hanoi *root)
{
  /*
   * bu fonksiyon arguman olarak alinan kulenin ardresini bir sonraki diskin adresine 
   * esiltliyor ve geri gonderiyor. bu sekilde bir onceki disk kuleden atilmis oluyor
   */
  hanoi* tmp = root->next;
  root->next = NULL;
  free(root);
  return tmp;// buraya free(root) gibi bisey ekle
}
hanoi * push(hanoi* root,int sayi)
{
  /*
   * bu fonksiyon hafizada bir disklik alan acip, o diskin bir alttaki diski gosteren 
   * pointerini arguman olarak gelen adrese esitliyor, ardindan arguman olarak gelen sayiyi
   * datasina atiyor ve en son bu pointeri geri gonderiyor
   */
  hanoi* tmp = (hanoi*)malloc(sizeof(hanoi));
  tmp->data = sayi;
  tmp->next = root;
  return tmp;
}
void hanoi_doldur(hanoi * doldur, int disk)
{
    /* 
     * bu fonksiyon; iter isminde bir hanoi ponteri tanimliyor .
     * ardindan bu pointer a argumandan gelen adresi yaziyor.
     * sonra tmp isimli 1 esit bir degisgen tanimliyor. bu degisgen datasi 1 den baslayaraktan
     * argumandan gelen sayiya kadar diskleri 1. kuleye yerlestirirken her diskin datasini belirliyor
     * tmp nin tanimlanmasindan sonra iterin ilk datasi ve nexti belirlenir ardindan digerleri yerlestirilir
     */
    hanoi * iter = doldur;
    int tmp = 1;
    iter ->data = tmp++;
    iter ->next = NULL;
    while(disk >= tmp)
    {
      while(iter->next != NULL){ iter = iter->next;}
      iter->next = (hanoi*)malloc(sizeof(hanoi));
      iter->next->data = tmp++;
      iter->next->next = NULL;
    }
}
void bastir()
{
  /*
   * Bu fonksiyon her kuleyi ekrana bastiracak bir fonksiyondur
   * bunun icin ilk once hanoi * iterator tanimlariz ardindan onu kullanarak 
   * ilk kuleyibastiririz. sonra iteratoru sonraki kuleye esitleriz ve ayni 
   * islemle onlarida ekrana bastiririz
   */
  hanoi * iter;
  puts(" Yukaridan Asagiya -----> "); 
  iter = kule1;
  printf("\tkule 1 =[");
  while(iter->next != NULL){
    if (iter->next->next != NULL)
        printf("%i, ",iter->data);
    else
        printf("%i",iter->data);
    iter = iter->next;
  }
  printf("]\n");

  iter = kule2;
  printf("\tkule 2 =[");
  while(iter->next != NULL){
    if (iter->next->next != NULL)
        printf("%i, ",iter->data);
    else
        printf("%i",iter->data);
    iter = iter->next;
  }
  printf("]\n");

  iter = kule3;
  printf("\tkule 3 =[");
  while(iter->next != NULL){
    if (iter->next->next != NULL)
        printf("%i, ",iter->data);
    else
        printf("%i",iter->data);
    iter = iter->next;
  }
  printf("]\n");
}
