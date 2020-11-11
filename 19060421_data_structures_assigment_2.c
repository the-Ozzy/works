#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COUNT 15
// Gerekli headerlerin eklemesi ve global anahtarlarin tanimi
typedef char *string; // okunabilirligin artmasi icin tanimladigim string veri yapisi
					  // gorulcegi uzere sadece her char dizisi icin char*
					  // ifadesi kullanmak yerine basitce string yazmak icin yazdim
typedef struct linked_list
{
	string isim;
	int fatura;
	struct linked_list *next;	
}
linked_list;

typedef struct tablo
{
	linked_list *index;
	struct tablo *next;
}
tablo;
// Programin akisi icin gerekli olan veri yapilarinin tanimlanmasi

string isimler[COUNT] = {"Ahmet","Bilal","Cemal", "Adem", "Yasin","Esin","Emel","Mustafa","Ayten",
				 		 "Ceylan","Nesrin","Bekir","Emin","Hakan","Hatice"};
int faturalar[COUNT] ={100,1000,600,650,350,270,410,750,600,1000,900,850,790,610,550};
int ad_index[COUNT]= {NULL};
int fatura_index[COUNT] = {NULL};

void linked_list_olustur(linked_list *list, int i);
// linked list'i olusturacak olan EKLE fonksiyonu

int ada_gore_index_tablosu_olustur(int *array, linked_list *list, int  node);
// ada gore index tablosu olusturacak EKLE fonksiyonu

int faturaya_gore_index_tablosu_olustur(int *array, linked_list *list, int  node);
// faturaya gore index tablosu olusturacak olan EKLE fonksiyonu

void ada_gore_yazdir(char harf, linked_list *list, int index);
// ada gore yazdiran YAZDIR fonksiyonu

void faturaya_gore_yazdir(int pass, linked_list *list, int index);
// faturaya gore yazdiran YAZDIR fonksiyonu

//fonksiyon prototiplerinin bitimi
int main(int argc, string argv)
{
	linked_list *list = NULL;
	
	for(int i =0 ; i == COUNT; i++)
	{
		linked_list_olustur(list,i);
	}
		
	printf("%s\t\t\t%i\n",list->isim,list->fatura);
	printf("%s\t\t\t%i\n", list->next->isim, list->next->fatura);

	for(int i = 0; i< COUNT; i++)
	{
		ada_gore_index_tablosu_olustur(*ad_index, &list, i);
	}
	for(int i = 0; i< COUNT; i++)
	{
		faturaya_gore_index_tablosu_olustur(*fatura_index, &list, i);
	}
	for (int i = 0; i < NULL; i++)
	{
		char harf = scanf("%c", &harf);
		ada_gore_yazdir(harf,list,i);
	}
			

}
void linked_list_olustur(linked_list *list,int i)// yap
{	
	linked_list *n = malloc(sizeof(linked_list));
	if ((n == NULL) && (i == 0 ))
	{
		printf("%s\n","Bilgisayarinizda yeteri kadar bos RAM yok,sonra deneyiniz");
		return 1;
	}
	if ( ( n == NULL ) && ( i != 0 ))
	{
		printf("%s\n", "Bilgisayarinizda yeteri kadar bos RAM yok,sonra deneyiniz");
		linked_list *temper;
		for (linked_list *temp = list; temp->next == NULL; temp = temp->next )
		{
			temper = temp->next;
			free(temp);
			temp = temper;
			if (temp->next == NULL)
			{
				free(temper);
			}
		}
	}
	n->isim = isimler[0];
	n->fatura =  faturalar[0];
	n->next = NULL;
	list = n;
	int j = 0;
	for (linked_list *tmp = list; j == i; tmp = tmp->next)
	{
		if (i == j)
		{
			tmp = n;
		}
		j++;
	}
	

}
int ada_gore_index_tablosu_olustur(int *array, linked_list *list, int  node)
{
	int i = 0;
	string ad = NULL;
	for (linked_list *tmp = list; i != node;tmp = tmp->next)
	{
		if (i == node)
		{
			ad = tmp->isim;
		}
		i++;
	}
	if (ad == NULL)
	{
		printf("Something went wrong\n");
		return 1;
	}
	
	i = 0;
	for(linked_list *tmp = list; i< COUNT;tmp = tmp->next)
	{
		if ((array[i] == NULL) || (strcmp(ad,tmp->isim) < 0)||((strcmp(ad,tmp->isim) == 0)))
			break;
		i++;
	}
	
	for (int j = COUNT - 1; j > i; j--)
	{
		if (array[j-1] == NULL)
		{	
			continue;
		}
		array[j]=array[j-1];
	}
	array[i] = node;
	
	return *array;
}
int faturaya_gore_index_tablosu_olustur(int *array, linked_list *list, int  node)
{
	int i = 0;
	int odenecek = NULL;
	for (linked_list *tmp = list; i != node;tmp = tmp->next)
	{
		if (i == node)
		{
			odenecek = tmp->fatura;
		}
		i++;
	}
	if (odenecek == NULL)
	{
		printf("FAILED\n");
		return 1;
	}
	i = 0;
	for(linked_list *tmp = list; i< COUNT;tmp = tmp->next)
	{
		if ((array[i] == NULL) || (odenecek > tmp->fatura)||(odenecek == tmp->fatura))
			break;
		i++;
	}
	
	for (int j = COUNT - 1; j > i; j--)
	{
		if (array[j-1] == NULL)
		{	
			continue;
		}
		array[j]=array[j-1];
	}
	array[i] = node;
	

}
void ada_gore_yazdir(char harf, linked_list *list, int index)
{
	int node_index = 0;
	for (linked_list *tmp = list; node_index == index; tmp = tmp->next)
	{
		if (tmp->isim[0] == harf)
		{
			printf("Adi:\t%s\t\tFaturasi:\t%i\n",tmp->isim,tmp->fatura);
		}
		node_index++;
	}
}
void faturaya_gore_yazdir(int pass, linked_list *list, int index)
{
	int node_index = 0;
	for (linked_list *tmp = list; node_index == index; tmp = tmp->next)
	{
		if (tmp->fatura >= pass)
		{
			printf("Adi:\t%s\t\tFaturasi:\t%i\n", tmp->isim, tmp->fatura);
		}
	}
}
