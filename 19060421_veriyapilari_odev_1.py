class students:# tablodaki her bir ogrenciyi saklamak icin olusturdugum sinif
    ilk_index = 0 #odevde verilen sirada ogrencinin ilk inexini saklamak icin bir degisgen
    numarasi = 0 #ogrencinin numarasini saklayacak degisgen
    notu = 0 #ogrencinin notunu saklayacak degisgen
    
    def goster(self):#ihtiyac halinde bir studet sinifindan bir birimin tum ozelliklerini ekrana bastiran foksiyon
        print("Giris Indexi: " , self.ilk_index)
        print("Numarasi:" , self.numarasi)
        print("Notu:" , self.notu)
def sirala(dizi,n):
        """
            bu fonksiyonu programin geri kalaninda programin ihtiyac duymasi halinde ogrenci listesini
            ilk once notlarina gore sonrada notu ayni olan ogrencileri ise numaralarina gore
            BUYUKTEN KUCUGE olacak sekilde siralayan bir algoritma.
            Temelinde baloncuk siralamasini kullandim, gerekliliklere gore uyarladim. 
        """
        for i in range(n):
            for j in range ( n - i - 1):# listenin notlara gore siralanmasi
                if dizi[j + 1].notu > dizi[j].notu:
                    dizi[j], dizi[j+1] = dizi[j + 1], dizi [j]
                    pass 
        for m in range(n):# listenin numaraya gore secici bir sekilde siralanmasi             
            for k in range(n - m - 2):
                if dizi[k].notu == dizi[k+1].notu:# k. elemanin k+1. elemanla ayni nota sahip olup olmadigini kontol ettim
                    if (dizi[k-1].numarasi >= dizi[k].numarasi) and (dizi[k-1].notu == dizi[k].notu):
                        dizi[k-1], dizi[k] = dizi[k], dizi [k - 1] #hem notlarin esitligini test edip hem de numaranin farkini test eden kisim
                    if dizi[k].numarasi > dizi[k+1].numarasi:  #numaralari test edip siralayan kisim
                        dizi[k], dizi[k + 1] = dizi[k + 1], dizi [k]
                    if dizi[n-2].numarasi > dizi[n-1].numarasi:# bu kisimi ustteki algoritmalar dizinin son elamanlarinda hata verdigi icin ekledim 
                        dizi[n-2], dizi[n-1] = dizi[n-1], dizi [n-2]                       
        return dizi
def ekle(dizi, index_tablosu,n):
        sirala(dizi,n)# odevde istenen program. sirala fonksiyonuna ogrnci dizisini gonderir ve ciktiyi
        i = 0         # kullanarak index tablosunu olusturur ve dondurur
        while i < n:
            index_tablosu[i] = dizi[i].ilk_index
            i = i + 1
            pass
        return index_tablosu
def sil(dizi, index_tablosu, index):# odevde istnilen sil fonksiyonu. silinmesi istenen veri haric listenin geri kalanini geri gonderir
        shot = False# silinmesi istenen verinin silinip silinmedigini kontrol edrn degisgen
        yenidizi = [students(),students(),students(),students(),students(),
                    students(),students(),students(),students(),students(),
                    students(),students(),students(),students()]        #dizinin geri kalaninin saklanacagi liste
        for i in range(14):
            if dizi[i].ilk_index == index:#istenen veriyi kontrol eden if yapisi
                shot = True
            if shot == False:
                yenidizi[i]= dizi[i]# istenen veriye kadar eski listedeki verileri yeni listeye aktran kisim
            else:
                yenidizi[i]= dizi[i+1]# istenen veriyle karsilasildiktan sonra onu alayarak yeni listeye aktaran yapi
        return ekle(yenidizi, index_tablosu,14)
def degistir(dizi,index_tablosu,numara, not_degistir):
        for i in range(15):# odevde istenilen degistir fonksiyonu. verilen numaranin notunu guncelleyip tekrardan ekle fonksiyonuna gonderir 
            if dizi[i].numarasi == numara:#ilk once dizideki istenen ogrenci bulunur
                dizi[i].notu = not_degistir#sonra not degistirilir
                pass
            pass
        index_tablosu = ekle (dizi, index_tablosu,15)#index tablosu yeni degerlere gore guncellenir
        return index_tablosu
def yazdir( dizi, index_tablosu, yuksek_not):# odevde istenilen yazdir fonksiyonu.
        index_tablosu = ekle(dizi,index_tablosu,15)
        for i in range(15):
            for j in range(15):
                if (index_tablosu[i] == dizi[j].ilk_index) and (dizi[j].notu >= yuksek_not):#istenilen nottan yuksek ogrencileri ayristiran kisim
                    print(index_tablosu[i],"\tNumarasi = ", dizi[j].numarasi," Notu = ",dizi[j].notu)#yazdirir
                    pass
                pass
            pass
#################################################################
numaralar = [18060311,20060045,19061091,20060134,20060678,18061086,
              20060032,20060067,19060456,18060245,20060110,20060234,
              20060141,20060011,20060012]
#tabloda verilen sirada ogrenci numaralari
notlar = [40,50,75,90,40,75,50,60,60,75,40,90,60,50,60]
#tabloda verilen sirada ogrenci notlaei
giris_listesi = [students(),students(),students(),students(),students(),
                 students(),students(),students(),students(),students(),
                 students(),students(),students(),students(),students()]
#tablodaki verileri students objeleri olarak yerlestirecegim dizi
# her indexteki 'students()' ifadesi;
# dizinin o indexinde birer students sinifinda bir obje saklanacagini belirtir 
for i in range(15):# odevdeki veriler sirayla giris listesine yerlestirilir
    giris_listesi[i].ilk_index = i
    giris_listesi[i].numarasi = numaralar[i]
    giris_listesi[i].notu = notlar[i]
index_tablosu = [None,None,None,None,None,
                None,None,None,None,None,
                None,None,None,None,None]
# odevde olusturlumasi istenen index tablosu, her indexteki None ifadesi 
# o indexin bos oldugunu belirtir
dizi = giris_listesi# giris listesi uzerinde islemler uygulanacagindan ilk listeyi korumak amacli esdeger bir degisgen olusturdum
index_tablosu = ekle(dizi, index_tablosu,15)
################################################

control = -1
while control != 0: #programin kullanici arayuzu
    print('''Veri Yapıları dersi ilk görevlendirmesinin cevabına hoşgeldiniz")
             Programın çalışma şekli şöyledir:
             Program ana menüde 0 a basmadığınız sürece çalışır
             
             1.Ekle fonksiyonunun kullanımı için 1'e:
             2.Sil fonksiyonu için ilk önce 2`ye basiniz ardından silmek istediğiniz indexi giriniz
             3.Değiştir fonksiyonu için sırasıyla: 3`e basın sonra numarayı ve ardından notu girin
             4.Yazdır fonksiyonu için ilk önce 4`e ardından da minimum notu girin ''')
    control = int(input("Giriniz: "))
    if control == 0:
        break
    elif control == 1:# ekle fonksiyonu
        index_tablosu = ekle(dizi,index_tablosu,15)
        for i in range(15):
            print(index_tablosu[i], end = " ")
            if i == 14:
                print("")
            
    elif control == 2:# sil fonksiyonu
        kucuk_index_tablosu = sil(dizi,index_tablosu,int(input("Indexi giriniz: ")))#yeni ve bir birim eksik index tablosunun atanmasi
        for i in range(14):
            print(kucuk_index_tablosu[i],end=" ")#her elemanin yazdirimasi
            if i == 13:
                print(" ")
    elif control == 3:#degistir fonksiyonu
        index_tablosu = degistir(dizi,index_tablosu,int(input("Numarayi giriniz: ")),int(input("Yeni notunu giriniz : ")))
        dizi = sirala(dizi,15)
        for i in range(15):
            print(index_tablosu[i] ,"\tNumarasi:",dizi[i].numarasi,"\tNotu",dizi[i].notu)
            if i == 14:
                print("")
    elif control == 4:#yazdir fonksiyonu
        yazdir(dizi,index_tablosu,int(input("minimum notu giriniz: ")))
    else:#hata kontrolu
        control = int(input('''yanlış bir numara girdiniz, programdan çıkmak istiyorsanız 0 a basınız.
                               menüye dönmek için  0 hariç bir sayı girin'''))
