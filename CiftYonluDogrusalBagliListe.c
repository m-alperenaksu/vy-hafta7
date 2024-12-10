//Çift Yönlü Doğrusal Bağlı Liste

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>


struct node{
    int data;
    struct node * next;
    struct node * prev;
};


struct node * basaEkle(struct node * head, int data){
    struct node * temp = (struct node * ) malloc(sizeof(struct node));
    temp->data = data;
    temp->next = head;
    temp->prev = NULL;
    if (head == NULL){
        head->prev = temp;
    }
    head = temp;
    return head;
}

//Üstteki kod daha optimize olabilir mi?


void sonaEkle(struct node * head, int data){
    if(head == NULL){
        printf("Boş bir listenin sonuna eleman ekleyemezsiniz.\n");
        return;
    }
    struct node * last = head;
    while(last->next != NULL) last = last->next;
    struct node * temp = (struct node *) malloc(sizeof(struct node));
    last->next = temp;
    temp->data = data;
    temp->next = NULL;
    temp->prev = last;
}


void ortayaEkle(struct node * head, int data, int index){
    if(head == NULL){
        printf("Boş bir listenin ortasına eleman ekleyemezsiniz.\n");
        return;
    }
    struct node * temp = head;
    while(temp->data != index) temp = temp->next;
    struct node * temp2 = (struct node *) malloc(sizeof(struct node));
    temp2->data = data;
    temp2->next = temp->next;
    temp2->prev = temp;
    temp->next = temp2;
    (temp2->next)->prev = temp2;
}


void listeyiYazdir(struct node * head){
    if(head == NULL){
        printf("Boş liste.\n");
        return;
    }
    struct node * temp = head;
    while(temp != NULL){
        printf("%d ",temp->data);
        temp = temp->next;
    }
}


void listeBilgisiYazdir(struct node * head){
    if(head == NULL){
        printf("Liste boş.\n");
        return;
    }
    int sayac = 1;
    struct node * temp = head;
    do{
        printf("%d.elemandan önceki node'un adresi = %p", sayac, temp->prev);
        printf("%d.elemanın adresi = %p", sayac, temp);
        printf("%d.elemanın değeri %d", sayac, temp->data);
        printf("%d.elemandan önceki node'un adresi = %p", sayac, temp->next);
        sayac++;
        temp = temp->next;
    }while(temp != head);
}


void elemanDuzenle(struct node * head, int data, int index){
    if(head == NULL){
        printf("Boş bir listede eleman düzenleyemezsiniz.\n");
        return;
    }
    struct node * temp = head;
    while(temp->data != index) temp = temp->next;
    temp->data = data;
}


int elemanSayisi (struct node * head){
    if(head == NULL){
        return 0;
    }
    int sayac = 0;
    struct node * temp = head;
    do{
        sayac++;
        temp = temp->next;
    }while(temp != head);
}


struct node * elemanSil(struct node * head, int data){
    if(head == NULL){
        printf("Boş bir listeden eleman silemezsiniz.\n");
        return head;
    }
    struct node * temp = head;
    if(head->data == data){
        if(head->next == NULL){
            head = NULL;
            return head;
        }
        head = head->next;
        head->prev = NULL;
        free(temp);
    }else{
        while(temp->next->data != data){
            if(temp->next->next == NULL){
                printf("Silmek istediğiniz eleman bulunamadı.");
                return head;
            }
            temp = temp->next;
        }
        struct node * temp2 = temp->next;
        temp->next = temp2->next;
        if(temp->next != NULL){
            (temp->next)->prev = temp; // parantez kullanmasak hata mı olurdu?
        }
        free(temp2);
    }
    return head;
}

struct node * listeyiBosalt(struct node * head){
    if(head == NULL){
        printf("Listeyi boş.\n");
    }
    while(head != NULL){
         head = elemanSil(head,head->data);
    }
    return head;
}

void listeyiTerstenYazdir(struct node * head){
    if(head == NULL){
        printf("Boş bir listeyi tersten yazdıramazsınız.\n");
        return;
    }
    struct node * last = head;
    while(last->next != NULL) last = last->next;
    while(last != NULL){
        printf("%d ", last->data);
        last = last->prev;
    }
}



int main() {
    setlocale(LC_ALL, "Turkish");
    int secim, data, index;
    struct node *head = NULL;
    struct node *head2 = NULL;

    while (1) {
        printf("-----Aşağıdaki işlemlerden birini seçiniz...---\n");
        printf("1-Listenin Başına Eleman Ekleme\n");
        printf("2-Listenin Sonuna Eleman Ekleme\n");
        printf("3-Listenin Ortasına Eleman Ekleme\n");
        printf("4-Elemanları Listele\n");
        printf("5-Verilen Adresteki elemanı Düzenle\n");
        printf("6-Listenden İstenilen Elemanı Sil\n");
        printf("7-Listeyi Sil\n");
        printf("8-Listenin Eleman Sayısı\n");
        printf("9-Listenin Tüm elemanlarının Bilgilerini Yazdır\n");
        printf("10-Listeyi Tersten Yazdır.\n");
        printf("11-İki Listeyi Birleştir.\n");
        printf("12-Listeyi Kopyala\n");
        printf("13-Programdan Çık\n");
        scanf("%d", &secim);

        switch (secim) {
            case 1:
                printf("Lütfen Eklemek İstediğiniz Değeri Giriniz...\n");
                scanf("%d", &data);
                head = basaEkle(head, data);
                break;
            case 2:
                printf("Lütfen Eklemek İstediğiniz Değeri Giriniz...\n");
                scanf("%d", &data);
                sonaEkle(head, data);
                break;
            case 3:
                printf("Lütfen Eklemek İstediğiniz Değeri Giriniz...\n");
                scanf("%d", &data);
                printf("Lütfen Ekleme Yapılacak Pozisyon Bilgisini Giriniz.....\n");
                scanf("%d", &index);
                ortayaEkle(head, data, index);
                break;
            case 4:
                listeyiYazdir(head);
                break;
            case 5:
                printf("Lütfen Değiştirmek İstediğiniz Yeni Değeri Giriniz...\n");
                scanf("%d", &data);
                printf("Lütfen Değeri Değiştirilmek İsteyen Pozisyon Bilgisini Giriniz.....\n");
                scanf("%d", &index);
                elemanDuzenle(head, data, index);
                break;
            case 6:
                printf("Lütfen Silmek İstediğiniz Elemanın Değerini Giriniz...\n");
                scanf("%d", &data);
                head = elemanSil(head, data);
                break;
            case 7:
                head = listeyiBosalt(head);
                break;
            case 8:
                printf("Listenin Eleman Sayısı = %d\n", elemanSayisi(head));
                break;
            case 9:
                listeBilgisiYazdir(head);
                break;
            case 10:
                listeyiTerstenYazdir(head);
                break;
            case 11:
                ikiListeyiBirlestir(head,head2);
            case 13:
                exit(0);
                break;
            default:
                printf("Yanlış seçim\n");
        }
    }

    return 0;
}

