// Gerekli kütüphanelerin eklenmesi
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// Veri Yapılarının Tanımlanması
typedef struct binary{
    int number;
    struct binary * left;
    struct binary * right;

}bintree1;
// Ödevin 1. kısmındaki binary tree yapısı
typedef struct bist{
    int number;
    int point;
    struct bist * right;
    struct bist * left;
}bst;
// Ödevin 2. kımındaki binary search tree yapısı

// Fonksiyonlerın Tanımlanması
void add_l(bintree1 * root, int number);
// Ağacın soluna ekleme yapacak olan fonsiyon
void add_r(bintree1 * root, int number);
// Ağacın sağına ekleme yapacak olan fonksiyon
void pre_order(bintree1 * root);
// Ağacın üzerinde kök-sol-sağ biçiminde gezinip ekrana yazdıracak olan fonksiyon
void in_order(bintree1 * root);
// Ağacın üzerinde sol-kök-sağ biçiminde gezinip ekrana yazdıracak olan fonksiyon
void post_order(bintree1 * root);
// Ağacın üzerinde sol-sağ-kök biçiminde gezinip ekrana yazdıracak olan fonksiyon

void bfs(bintree1 * root);
// Ağacın üzerinde gezinip seviye ya da yüksekliğe göre ekrana yazdıracak olan fonksiyon
int height_finder(bintree1* root);
// bfs fonksiyonu için ağacın yüksekliğini bulan fonksiyon
void bfs_level(bintree1* root, int level);
// Ağacın üzerinde belirtilen seviyelerdeki verileri ekrana yazdıracak olan fonksiyon (bfs'nin yazdırma işlem parçacığı)

void ind_creat(bst * root, int number, int point);
// index tablosunda verilen veri için doğru yeri bulup ekleyen fonsiyon
bst *ind_del(bst * root, int number, int point);
// index tablosundan istenen verinin silinmesini sağlayan fonksiyon
void ind_edit(bst * root, int number, int point,int npoint);
// index tablosunda istenen veriyi değiştiren fonksiyon
void ind_out(bst * root, int min, int reset);
// index tablosunu verilen kritere göre ekrana yansıtan fonksiyon

int main(void) {
    setlocale(LC_ALL,"Turkish");
    bintree1 * root = (bintree1*)malloc(sizeof(bintree1));
    root->number = 42;
    root->left = NULL;
    root->right = NULL;
    // 1. kısmın uygulanması
    add_r(root,64);
    add_l(root,43);
    add_r(root->left,23);
    add_l(root->left,67);
    add_l(root->right,55);
    add_r(root->right,12);
    add_l(root->right->right,69);
    add_l(root->left->left,97);
    printf("Pre-Order(root-sol-sağ) sıralamalı:\t");
    pre_order(root);
    puts("\n************************************************************************************************************************");//20
    printf("In-Order(sol-root-sağ) sıralamalı:\t");
    in_order(root);
    puts("\n************************************************************************************************************************");//20
    printf("Post-Order(sol-sağ-root) sıralamalı:\t");
    post_order(root);
    puts("\n************************************************************************************************************************");//20
    printf("BFS (seviyeye göre) sıralamalı:\t\t");
    bfs(root);
    puts("\n************************************************************************************************************************");//20

    bst * indtable1;
    indtable1 = (bst*) malloc(sizeof(bst));
    indtable1->left = NULL;
    indtable1->right =NULL;
    indtable1->number = 1;
    indtable1->point = 40;
    // 2. kısım foksiyonlarının çalışmasına ek örnek olması için benim verdiğim veri seti
    ind_creat(indtable1,2,50);
    ind_creat(indtable1,3,75);
    ind_creat(indtable1,4,90);
    ind_creat(indtable1,5,40);
    ind_creat(indtable1,6,34);
    ind_creat(indtable1,7,53);
    ind_creat(indtable1,8,60);
    ind_creat(indtable1,9,36);
    ind_creat(indtable1,10,35);
    ind_creat(indtable1,11,25);
    ind_creat(indtable1,12,85);
    ind_creat(indtable1,13,66);
    ind_creat(indtable1,14,52);
    ind_creat(indtable1,15,69);
    puts("Listenin ilk hali;");
    ind_out(indtable1,0,1);
    puts("\n************************************************************************************************************************");//20

    ind_del(indtable1,8,60);
    
    puts("Listeden 8 numaralı ve 60 puanlı öğrencinin silinmiş hali;");
    ind_out(indtable1,15,1);
    puts("\n************************************************************************************************************************");//20

    ind_edit(indtable1,10,35,41);
    puts("Listedeki 10 numaralı 35 puanlı öğrencinin puanının 41 yapılmış hali;");
    ind_out(indtable1,10,1);
    puts("\n************************************************************************************************************************");//20
    puts("Listedeki 80 puandan yüksek almış öğrenciler;");
    ind_out(indtable1,80,1);
    puts("\n************************************************************************************************************************");//20
    bst * indtable2;
    indtable2 = (bst*) malloc(sizeof(bst));
    indtable2->left = NULL;
    indtable2->right =NULL;
    indtable2->number = 18060311;
    indtable2->point = 40;

    // 2. kısım foksiyonlarının ödevdeki veri setiyle çalışması

    ind_creat(indtable2,20060045,50);
    ind_creat(indtable2,19061091,75);
    ind_creat(indtable2,20060134,90);
    ind_creat(indtable2,20060678,40);
    ind_creat(indtable2,18061086,75);
    ind_creat(indtable2,20060032,50);
    ind_creat(indtable2,20060067,60);
    ind_creat(indtable2,19060456,60);
    ind_creat(indtable2,18060245,75);
    ind_creat(indtable2,20060110,40);
    ind_creat(indtable2,20060234,90);
    ind_creat(indtable2,20060141,60);
    ind_creat(indtable2,20060011,50);
    ind_creat(indtable2,20060012,60);
    
    puts("Listenin ilk hali;");
    ind_out(indtable2,0,1);
    puts("\n************************************************************************************************************************");//20

    ind_del(indtable2,20060067,60);
    puts("Listeden 20060067 numaralı ve 60 puanlı öğrencinin silinmiş hali;");
    ind_out(indtable2,15,1);
    puts("\n************************************************************************************************************************");//20

    ind_edit(indtable2,20060141,60,89);
    puts("Listedeki 20060141 numaralı 60 puanlı öğrencinin puanının 89 yapılmış hali;");
    ind_out(indtable2,10,1);
    puts("\n************************************************************************************************************************");//20
    puts("Listedeki 80 puandan yüksek almış öğrenciler;");
    ind_out(indtable2,80,1);
}

void add_l(bintree1 * root, int number){
    bintree1 *iter = root;
    if (iter == NULL)
    {
        iter = (bintree1*)malloc(sizeof(bintree1));
        iter->number = number;
        iter->left = NULL;
        iter->right = NULL;
        return;
    }
    if (iter->left == NULL)
    {
        iter->left = (bintree1*)malloc(sizeof(bintree1));
        iter->left->number = number;
        iter->left->left = NULL;
        iter->left->right = NULL;
        return;
    }
    else{
        add_l(iter->left, number);
    }
}
void add_r(bintree1 * root, int number){
    bintree1 *iter = root;
    if (iter == NULL)
    {
        iter = (bintree1*)malloc(sizeof(bintree1));
        iter->number = number;
        iter->left = NULL;
        iter->right = NULL;
    }
    if (iter->right == NULL)
    {
        iter->right = (bintree1*)malloc(sizeof(bintree1));
        iter->right->number = number;
        iter->right->left = NULL;
        iter->right->right = NULL;
    }
    else{
        add_l(iter->right, number);
    }
}


void pre_order(bintree1 * root){
    bintree1 *iter = root;
    printf("%d\t",iter->number);
    if(iter ->left != NULL)
        pre_order(iter->left);
    if(iter->right != NULL)
        pre_order(iter->right);
}
void in_order(bintree1 * root){
    bintree1 *iter = root;
    if(iter ->left != NULL)
        in_order(iter->left);
    printf("%d\t",iter->number);
    if(iter->right != NULL)
        in_order(iter->right);
}
void post_order(bintree1 * root){
    bintree1 *iter = root;
    if(iter ->left != NULL)
        post_order(iter->left);
    if(iter->right != NULL)
        post_order(iter->right);
    printf("%d\t",iter->number);
}


void bfs(bintree1 * root){
    bintree1 * iter = root;
    int height = height_finder(root);
    if (height == 0)
    {
        return;
    }
    else{
        for (size_t i = 1; i <= height; i++)
        {
            bfs_level(iter,i);
        }
    }
        
}
int height_finder(bintree1* root){
    if (root == NULL)
    {
        return 0;
    }
    else
    {
        int left_h = height_finder(root->left);
        int right_h = height_finder(root->right);

        if(left_h > right_h)
            return(left_h + 1);
        else
            return(right_h + 1);
    }
    
}
void bfs_level(bintree1* root, int level){
    bintree1 * iter = root;
    if (root == NULL)
        return;
    if(level == 1)
        printf("%d\t",iter->number);
    else if (level > 1)
    {
        bfs_level(root->left, level -1);
        bfs_level(root->right, level -1);
    } 
}

void ind_creat(bst * root, int number, int point){
    bst * iter = root;

    if (iter == NULL)
    {
        iter = (bst*) malloc(sizeof(bst));
        iter->left = NULL;
        iter->right =NULL;
        iter->number = number;
        iter->point = point;
        return;
    }
    if ((iter->left == NULL) && (iter->right == NULL))
    {
        if(point > iter->point)
        {
            iter->right = (bst*) malloc(sizeof(bst));
            iter->right->left = NULL;
            iter->right->right =NULL;
            iter->right->number = number;
            iter->right->point = point;
        }
        else {
            iter->left = (bst *) malloc(sizeof(bst));
            iter->left->left = NULL;
            iter->left->right = NULL;
            iter->left->number = number;
            iter->left->point = point;
        }
    }
    else if ((iter->left != NULL) && (iter->right == NULL))
    {
        if(iter->point <= point) {
            iter->right = (bst*) malloc(sizeof(bst));
            iter->right->left = NULL;
            iter->right->right =NULL;
            iter->right->number = number;
            iter->right->point = point;
        }
        else
        {
            ind_creat(iter->left,number,point);
        }
    }
    else if ((iter->left == NULL) && (iter->right != NULL))
    {
        if(point > iter->point){
            ind_creat(iter->right,number,point);
        }
        else
        {
                iter->left = (bst*) malloc(sizeof(bst));
                iter->left->left = NULL;
                iter->left->right =NULL;
                iter->left->number = number;
                iter->left->point = point;
        }
    }
    else
    {
        if (point > iter->point)
            ind_creat(iter->right,number,point);
        else
            ind_creat(iter->left,number,point);
    }
}
bst *ind_del(bst * root, int number, int point){
    bst* iter = root;
    if(iter == NULL)
        return iter;
    if(iter->point > point)
    {
        iter->left = ind_del(iter->left,number,point);
    }
    else if (iter->point < point)
    {
        iter->right = ind_del(iter->right,number,point);
    }
    else
    {
        if(iter->left == NULL){
            bst * temp = iter->right;
            free(iter);
            return temp;
        }
        else if (iter->right == NULL)
        {
            bst* temp = iter->left;
            free(iter);
            return temp;
        }
        bst* min= iter;
        while(min && min->left != NULL)
            min = min->left;
        iter->point = min->point;
        iter->number = min->number;

        iter->right = ind_del(iter->right,min->number,min->point);
    }
    return iter;  
}
void ind_edit(bst * root, int number, int point,int npoint){
    ind_del(root,number,point);
    ind_creat(root,number,npoint);
}
void ind_out(bst * root, int min, int reset) {
    static int i = 1;
    if (reset == 1)
        i = reset--;
        static int varmi = 0;
        bst *iter = root;
        if (iter == NULL) {
            if (varmi == 0)
                printf("Hiç öğrenciniz bulunmamaktadır\n");
            return;
        }
        else
        {
            varmi++;
            ind_out(iter->right, min, reset);
            if (iter->point >= min)
                printf("%i.\tÖğrencinin Numarası:\t%i\tÖğrencinin Notu:\t%i\n", i++, iter->number, iter->point);
            ind_out(iter->left, min, reset);
        }
    }
