#include "boolean.h"
#include "listrek.h"
#include <stdio.h>
#include <stdlib.h>

/* *** Manajemen Memori *** */
address Alokasi(infotype X)
{
    address P;
    P = malloc(sizeof(infotype));
    if (P != Nil)
    {
        Info(P) = X;
        Next(P) = Nil;
    }
    return P;
}
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak Nil, dan misalnya menghasilkan P, 
  maka Info(P) = X, Next(P) = Nil */
/* Jika alokasi gagal, mengirimkan Nil */
void Dealokasi(address P)
{
    free(P);
}
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */

/* *** Primitif-primitif yang harus direalisasikan *** */

/* Pemeriksaan Kondisi List */
int IsEmpty(List L)
{
    return (L == Nil);
}
/* Mengirimkan 1 jika L kosong dan 0 jika L tidak kosong */
int IsOneElmt(List L)
{
    address P;
    P = L;
    return (L != Nil && Next(P) == Nil);
}
/* Mengirimkan 1 jika L berisi 1 elemen dan 0 jika > 1 elemen atau kosong */

/* *** Selektor *** */
infotype FirstElmt(List L)
{
    address P;
    P = L;
    return (Info(P));
}
/* Mengirimkan elemen pertama sebuah list L yang tidak kosong */
List Tail(List L)
{
    return (Next(L));
}
/* Mengirimkan list L tanpa elemen pertamanya, mungkin menjadi list kosong */

/* *** Konstruktor *** */
List Konso(infotype e, List L)
{
    List P = Alokasi(e);
    if (P != Nil)
    {
        Next(P) = L;
    }

    return P;
}
/* Mengirimkan list L dengan tambahan e sebagai elemen pertamanya. 
e dialokasi terlebih dahulu. Jika alokasi gagal, mengirimkan L. */
List KonsB(List L, infotype e)
{
    List P = Alokasi(e);
    if (P == Nil)
    {
        return L;
    }
    else if (IsEmpty(L))
    {
        return P;
    }
    Next(L) = KonsB(Tail(L), e);
    return L;
}
/* Mengirimkan list L dengan tambahan e sebagai elemen terakhirnya */
/* e harus dialokasi terlebih dahulu */
/* Jika alokasi e gagal, mengirimkan L */

/* *** Operasi Lain *** */
List Copy(List L)
{
    if (IsEmpty(L))
    {
        return Nil;
    }
    else
    {
        return Konso(FirstElmt(L), Copy(Tail(L)));
    }
}
/* Mengirimkan salinan list L (menjadi list baru) */
/* Jika ada alokasi gagal, mengirimkan L */
void MCopy(List Lin, List *Lout)
{
    *Lout = Copy(Lin);
}
/* I.S. Lin terdefinisi */
/* F.S. Lout berisi salinan dari Lin */
/* Proses : menyalin Lin ke Lout */
List Concat(List L1, List L2)
{
    if (IsEmpty(L1))
    {
        return Copy(L2);
    }
    else
    {
        return (Konso(FirstElmt(L1), Concat(Tail(L1), L2)));
    }
}
/* Mengirimkan salinan hasil konkatenasi list L1 dan L2 (menjadi list baru) */
/* Jika ada alokasi gagal, menghasilkan Nil */
void MConcat(List L1, List L2, List *LHsl)
{
    *LHsl = Concat(L1, L2);
}
/* I.S. L1, L2 terdefinisi */
/* F.S. LHsl adalah hasil melakukan konkatenasi L1 dan L2 dengan cara "disalin" */
/* Proses : Menghasilkan salinan hasil konkatenasi list L1 dan L2 */
void PrintList(List L)
{
    if (IsEmpty(L))
    {
        return;
    }
    else
    {
        printf("%d", Info(L));
        printf("\n");
        PrintList(Tail(L));
    }
}
/* I.S. L terdefinisi. */
/* F.S. Setiap elemen list dicetak. */
int NbElmtList(List L)
{
    if (IsEmpty(L))
    {
        return 0;
    }
    else
    {
        return 1 + NbElmtList(Tail(L));
    }
}
/* Mengirimkan banyaknya elemen list L, Nol jika L kosong */
boolean Search(List L, infotype X)
{
    if (IsEmpty(L))
    {
        return false;
    }
    else
    {
        if (Info(L) == X)
        {
            return true;
        }
    }
    return Search(Tail(L), X);
}
/* Mengirim true jika X adalah anggota list, false jika tidak */

/*** Pencarian nilai ekstrim ***/
/* Prekondisi untuk Max/Min/Sum/Average : List tidak kosong */
infotype MaxList(List L)
{
    if (IsOneElmt(L))
    {
        return FirstElmt(L);
    }
    else
    {
        if (FirstElmt(L) > MaxList(L))
        {
            return FirstElmt(L);
        }
    }
}
/* Mengirimkan nilai info(P) yang maksimum */

infotype MinList(List L)
{
    if (IsOneElmt(L))
    {
        return FirstElmt(L);
    }
    else
    {
        if (FirstElmt(L) < MinList(L))
        {
            return FirstElmt(L);
        }
    }
}
/* Mengirimkan nilai info(P) yang minimum */

infotype SumList(List L)
{
    if (IsOneElmt(L))
    {
        FirstElmt(L);
    }
    else
    {
        return (FirstElmt(L) + SumList(Tail(L)));
    }
}
/* Mengirimkan total jumlah elemen List L */

float AverageList(List L)
{
    int count = 0;
    float total = 0;
    if (IsOneElmt(L))
    {
        FirstElmt(L);
    }
    else
    {
        count += 1;
        total = (FirstElmt(L) + SumList(Tail(L)));
    }

    return (total / count);
}
/* Mengirimkan nilai rata-rata elemen list L */

/*** Operasi-Operasi Lain ***/
List InverseList(List L)
{
    if (IsOneElmt(L))
    {
        return (Alokasi(FirstElmt(L)));
    }
    else
    {
        return KonsB((InverseList(Tail(L))), FirstElmt(L));
    }
}
/* Mengirimkan list baru, hasil invers dari L dengan menyalin semua elemen list.
Semua elemen list baru harus dialokasi */
/* Jika alokasi gagal, hasilnya list kosong */

void SplitPosNeg(List L, List *L1, List *L2)
{
    if (IsEmpty(L))
    {
        *L1 = Nil;
        *L2 = Nil;
        return;
    }
}
/* I.S. L mungkin kosong */
/* F.S. Berdasarkan L, dibentuk dua buah list L1 dan L2 */
/* L1 berisi semua elemen L yang positif atau 0, sedangkan L2 berisi
semua elemen L yang negatif; semua dengan urutan yang sama seperti di L */
/* L tidak berubah: Semua elemen L1 dan L2 harus dialokasi */
/* Jika L kosong, maka L1 dan L2 kosong */

void SplitOnX(List L, infotype X, List *L1, List *L2)
{
    if (IsEmpty(L))
    {
        *L1 = Nil;
        *L2 = Nil;
        return;
    }
}
/* I.S. L dan X terdefinisi, L1 dan L2 sembarang. */
/* F.S. L1 berisi semua elemen L yang lebih kecil dari X, dengan urutan
kemunculan yang sama, L2 berisi semua elemen L yang tidak masuk ke
L1, dengan urutan kemunculan yang sama. */

int ListCompare(List L1, List L2)
{
    if (IsEmpty(L1) && IsEmpty(L2))
    {
        return 0;
    }
    if (IsEmpty(L1))
    {
        return -1;
    }
    if (IsEmpty(L2))
    {
        return 1;
    }

    if (FirstElmt(L1) < FirstElmt(L2))
    {
        return -1;
    }
    else if (FirstElmt(L1) > FirstElmt(L2))
    {
        return 1;
    }

    return (ListCompare(Tail(L1), Tail(L2)));
}
/* Menghasilkan: -1 jika L1 < L2, 0 jika L1 = L2, dan 1 jika L1 > L2 */
/* Jika L[i] adalah elemen L pada urutan ke-i dan |L| adalah panjang L: */
/* L1 = L2: |L1| = |L2| dan untuk semua i, L1[i] = L2[i] */
/* L1 < L2: Jika i adalah urutan elemen yang berbeda yang terkecil
dari L1 dan L2, L1[i]<L2[i] atau: Jika pada semua elemen pada
urutan i yang sama, L1[i]=L2[i], namun |L1|<|L2| */
/* Contoh: [3,5,6,7] < [4,4,5,6]; [1,2,3]<[1,2,3,4] */
/* L1>L2: kebalikan dari L1<L2 */

boolean IsAllExist(List L1, List L2)
{
    if (IsEmpty(L1))
    {
        return false;
    }
    else
    {
        return (Search(L2, FirstElmt(L1)));
    }

    return true;
}
/* Menghasilkan true jika semua elemen dalam L1 terdapat dalam L2 (tanpa
memperhatikan urutan ataupun banyaknya elemen).
Kedua list mungkin kosong. Jika L1 kosong, maka hasilnya false. */