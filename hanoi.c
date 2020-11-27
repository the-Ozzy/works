#include <stdio.h>
#include <stdlib.h>
int alarm;
typedef struct n{
  int data;
  struct n *next;
}hanoi;
hanoi * kule1;hanoi *kule2; hanoi*kule3;

int ekle(int alinacak, int verilecek, int taban);

hanoi *pop(hanoi *root); //bitti sayilir free()

hanoi *push(hanoi *root, int sayi); //bitti

void hanoi_doldur(hanoi * doldur, int disk);//bitti

void bastir();

int main (int argc, char* argv[])
{

  alarm = 0;
  if (argc != 2)
  {
    puts("Eksik ya da fazla arguman girdiniz: Beklenen format;");
    puts("./<hanoi><numerik olarak disk sayisi>");
    return(1);
  }
  else
  {
    kule1 = (hanoi*)malloc(sizeof(hanoi));
    kule2 = (hanoi*)malloc(sizeof(hanoi));
    kule3 = (hanoi*)malloc(sizeof(hanoi));
     hanoi_doldur(kule1,atoi(*++argv) +1);
    int taban =  atoi(argv[0])+1;
    kule2->data = taban;
    kule3->data = taban;
    bastir();
    puts("Hanoi Kulesi Oyununa Hos Geldiniz!");
    printf("Oyunun Kurallari/Kullanimi:\n1. Size soruldugu zaman; Ilk once diski hangi kuleden almak istediginizi sonra da hangi kuleye koymak istediginizi girin\n");
    printf("2. bir diski kendisinden kucuk bir diskin uzerine koyamazssiniz\n3. Eger cikmak istiyorsaniz size soruldugu zaman konsola '-1' girin, devam etmek istiyorsaniz 0 yada 0'dan buyuk bir sayi girin\n"); 
  
    int control = 0, alinacak,verilecek,kural;
    while (control != -1)
    {
      alarm = 0;
      bastir();
      printf("Diskin alinacagi kuleyi giriniz\n\t");scanf("%i",&alinacak);
      printf("Diskin koyulacagi kuleyi giriniz:\n\t");scanf("%i",&verilecek);
      kural =  ekle(alinacak,verilecek,taban);
      if (kural == -1)
      {
        puts("Bir diski kendisinden kucuk bir diskin uzerine koyamazssiniz");
        puts("Programdan cikmak istiyorsaniz -1 girin. devam etmek icin baska bir sayi girin");
        scanf("%i",&control);
      }
      else
      {
        bastir();
        puts("-------------------------------------------------");
      }
     if(alarm == 0)
     {
       puts("\nCikmak istiyorsaniz -1 giriniz, istemiyorsaniz baska bir sayi girin");
       scanf("%i",&control);
       alarm = 1;
     }
    }
  }
 
}
int ekle (int alinacak, int verilecek, int taban)
{
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
  hanoi* tmp = root->next;
  return tmp;// buraya free(root) gibi bisey ekle
}
hanoi * push(hanoi* root,int sayi)
{
  hanoi* tmp = (hanoi*)malloc(sizeof(hanoi));
  tmp->data = sayi;
  tmp->next = root;
  return tmp;
}
void hanoi_doldur(hanoi * doldur, int disk)
{
    hanoi * iter = doldur;
    int tmp = 1;
    iter ->data = tmp++;// burada -- leri ++ yapmamiz lazim buyukten kucuge yerlestiriyor su an
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
