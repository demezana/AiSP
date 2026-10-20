#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Osoba {
    char ime[30];
    char prezime[30];
    int godinaRodjenja;
    struct Osoba* sljedeci;
} Osoba;


Osoba* unosOsobe(void) {
    Osoba* nova = (Osoba*)malloc(sizeof(Osoba));

    if (nova == NULL) {
        printf("Greska pri alokaciji memorije!\n");
        return NULL;
    }

    printf("Unesite ime: ");
    scanf("%29s", nova->ime);

    printf("Unesite prezime: ");
    scanf("%29s", nova->prezime);

    printf("Unesite godinu rodenja: ");
    scanf("%d", &nova->godinaRodjenja);

    nova->sljedeci = NULL;

    return nova;
}


void dodajNaPocetak(Osoba** glava) {
    Osoba* nova = unosOsobe();

    if (nova == NULL)
        return;

    nova->sljedeci = *glava;
    *glava = nova;
}


void ispisiListu(Osoba* glava) {
    Osoba* tekuci = glava;

    if (tekuci == NULL) {
        printf("Lista je prazna.\n");
        return;
    }

    while (tekuci != NULL) {
        printf("%s %s, godina rodenja: %d\n",
            tekuci->ime,
            tekuci->prezime,
            tekuci->godinaRodjenja);

            tekuci = tekuci->sljedeci;
    }
}


void dodajNaKraj(Osoba** glava) {
    Osoba* nova = unosOsobe();

    if (nova == NULL)
        return;

    if (*glava == NULL) {
        *glava = nova;
        return;
    }

    Osoba* tekuci = *glava;

    while (tekuci->sljedeci != NULL) {
        tekuci = tekuci->sljedeci;
    }

    tekuci->sljedeci = nova;
}


Osoba* pronadjiOsobu(Osoba* glava, const char* prezime) {
    Osoba* tekuci = glava;

    while (tekuci != NULL) {
        if (strcmp(tekuci->prezime, prezime) == 0) {
            return tekuci;
        }

        tekuci = tekuci->sljedeci;
    }

    return NULL;
}


void obrisiOsobu(Osoba** glava, const char* prezime) {
    Osoba* tekuci = *glava;
    Osoba* prethodni = NULL;

    while (tekuci != NULL &&
        strcmp(tekuci->prezime, prezime) != 0) {
        prethodni = tekuci;
        tekuci = tekuci->sljedeci;
    }

    if (tekuci == NULL) {
        printf("Osoba nije pronadena.\n");
        return;
    }

    if (prethodni == NULL) {
        *glava = tekuci->sljedeci;
    }
    else {
        prethodni->sljedeci = tekuci->sljedeci;
    }

    free(tekuci);
    printf("Osoba je uspjesno obrisana.\n");
}


void oslobodiListu(Osoba** glava) {
    Osoba* tekuci = *glava;

    while (tekuci != NULL) {
        Osoba* zaBrisanje = tekuci;
        tekuci = tekuci->sljedeci;
        free(zaBrisanje);
    }

    *glava = NULL;
}

int main(void) {
    Osoba* glava = NULL;
    int izbor;
    char prezime[30];
    Osoba* pronadjena;

    do {
        printf("\n--- IZBORNIK ---\n");
        printf("1. Dodaj osobu na pocetak\n");
        printf("2. Ispisi listu\n");
        printf("3. Dodaj osobu na kraj\n");
        printf("4. Pronadi osobu po prezimenu\n");
        printf("5. Obrisi osobu po prezimenu\n");
        printf("0. Izlaz\n");
        printf("Odabir: ");
        scanf("%d", &izbor);

        switch (izbor) {
        case 1:
            dodajNaPocetak(&glava);
            break;

        case 2:
            ispisiListu(glava);
            break;

        case 3:
            dodajNaKraj(&glava);
            break;

        case 4:
            printf("Unesite prezime za pretragu: ");
            scanf("%29s", prezime);

            pronadjena = pronadjiOsobu(glava, prezime);

            if (pronadjena != NULL) {
                printf("Pronadena osoba: %s %s, "
                    "godina rodenja: %d\n",
                    pronadjena->ime,
                    pronadjena->prezime,
                    pronadjena->godinaRodjenja);
            }
            else {
                printf("Osoba nije pronadena.\n");
            }
            break;

        case 5:
            printf("Unesite prezime osobe za brisanje: ");
            scanf("%29s", prezime);
            obrisiOsobu(&glava, prezime);
            break;

        case 0:
            printf("Kraj programa.\n");
            break;

        default:
            printf("Neispravan odabir!\n");
        }

    } while (izbor != 0);

    oslobodiListu(&glava);

    return 0;
}
