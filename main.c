#include <stdio.h>
#include <stdlib.h>

#define UROKOVA_MIRA 0.05
#define DAN_Z_UROKU 0.15
#define MIN_VKLAD 1000
#define MAX_VKLAD 10000000
#define MIN_MESICNI_VKLAD 0
#define MAX_MESICNI_VKLAD 1000000
#define ROK 2026
#define POCET_MESICU 12

int jePrestupny(int rok) {
    if ((rok % 4 == 0 && rok % 100 != 0) || (rok % 400 == 0))
        return 1;
    else
        return 0;
}

int pocetDni(int mesic, int rok) {
    if (mesic == 1 || mesic == 3 || mesic == 5 || mesic == 7 ||
        mesic == 8 || mesic == 10 || mesic == 12)
        return 31;

    if (mesic == 4 || mesic == 6 || mesic == 9 || mesic == 11)
        return 30;

    if (mesic == 2) {
        if (jePrestupny(rok))
            return 29;
        else
            return 28;
    }

    return 0;
}

double nacti(double min, double max) {
    double x;

    do {
        printf("Zadej hodnotu (%.2f - %.2f): ", min, max);
        scanf("%lf", &x);

        if (x < min || x > max) {
            printf("Hodnota mimo povoleny rozsah!\n");
        }
    } while (x < min || x > max);

    return x;
}

int main(void) {
    double pocatecni_stav;
    double mesicni_vklad;
    double stav;
    double urok;
    double dan;

    printf("Simulace sporiciho uctu\n\n");

    pocatecni_stav = nacti(MIN_VKLAD, MAX_VKLAD);
    mesicni_vklad = nacti(MIN_MESICNI_VKLAD, MAX_MESICNI_VKLAD);

    stav = pocatecni_stav;

    printf("\nVypis uctu za rok %d\n", ROK);
    printf("Rocni urokova mira: %.2f %%\n\n", UROKOVA_MIRA * 100);

    for (int mesic = 1; mesic <= POCET_MESICU; mesic++) {
        stav += mesicni_vklad;

        urok = stav * (UROKOVA_MIRA / 12);
        dan = urok * DAN_Z_UROKU;
        stav = stav + urok - dan;

        printf("Datum: %d.%d.%d\n", pocetDni(mesic, ROK), mesic, ROK);
        printf("Vklad: %.2f Kc\n", mesicni_vklad);
        printf("Urok: %.2f Kc\n", urok);
        printf("Dan: %.2f Kc\n", dan);
        printf("Stav na konci mesice: %.2f Kc\n\n", stav);
    }

    printf("=====================================\n");
    printf("Pocatecni stav: %.2f Kc\n", pocatecni_stav);
    printf("Konecny stav: %.2f Kc\n", stav);
    printf("Rozdil: %.2f Kc\n", stav - pocatecni_stav);

    return 0;
}
#include <stdio.h>

#define ROK 2025
#define MIN_ZUSTATEK 100
#define MAX_ZUSTATEK 10000000
#define MIN_VKLAD 100
#define MAX_VKLAD 100000

int main(void) {
    int buffer;
    float stav_uctu;
    float mesicni_vklad;
    float mesicni_urok;
    float rocni_urok = 3.5;
    float urok;
    float konecny_urok;
    float celkovy_urok = 0;
    float dan;

    int dny[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    do {
        buffer = 0;
        printf("Zadejte svuj zustatek v rozmezi %d - %d:", MIN_ZUSTATEK, MAX_ZUSTATEK);
        scanf("%f", &stav_uctu);
        while (getchar() != '\n') {
            buffer++;
        }
        if (buffer != 0) {
            printf("Byl zadan spatny vstup. Zadejte znovu.\n");
        }
    } while (buffer != 0 || stav_uctu > MAX_ZUSTATEK || stav_uctu < MIN_ZUSTATEK);

    do {
        buffer = 0;
        printf("Zadejte, kolik chcete pravidelne mesicne vkladat v rozmezi %d - %d:", MIN_VKLAD, MAX_VKLAD);
        scanf("%f", &mesicni_vklad);
        while (getchar() != '\n') {
            buffer++;
        }
        if (buffer != 0) {
            printf("Byl zadan spatny vstup. Zadejte znovu.\n");
        } else if (mesicni_vklad < MIN_VKLAD) {
            printf("Zadejte vetsi pravidelny vklad.\n");
        } else if (mesicni_vklad > MAX_VKLAD) {
            printf("Zadejte nizsi pravidelny vklad.\n");
        }
    } while (buffer != 0 || mesicni_vklad < MIN_VKLAD || mesicni_vklad > MAX_VKLAD);

    mesicni_urok = rocni_urok / 100 / 12;

    printf("-----------------------------------------------------------------------------------------------\n");
    printf("Rocni uroky jsou %.2f%%\n", rocni_urok);
    printf("Stav uctu byl na pocatku roku %.2f.\n", stav_uctu);
    printf("-----------------------------------------------------------------------------------------------\n");
    printf("   datum         na pocatku mesice     vklad           urok          dan(15%%)    na konci mesice\n");

    for (int i = 0; i < 12; i++) {
        float zacatek = stav_uctu;
        stav_uctu = stav_uctu + mesicni_vklad;
        urok = stav_uctu * mesicni_urok;
        dan = urok * 0.15;
        konecny_urok = urok - dan;
        stav_uctu = stav_uctu + konecny_urok;
        celkovy_urok = celkovy_urok + konecny_urok;

        printf("%2d.%2d.%d      %12.2f Kc  %10.2f Kc  %10.2f Kc  %10.2f Kc   %12.2f Kc\n", dny[i], i + 1, ROK, zacatek,
               mesicni_vklad,
               urok, dan, stav_uctu);
    }
    printf("-----------------------------------------------------------------------------------------------\n");
    printf("Stav na konci roku 2025 je %.2f Kc. Uroky bylo za rok 2025 nasporeno %.2f Kc.\n", stav_uctu, celkovy_urok);
    printf("-----------------------------------------------------------------------------------------------\n");
    return 0;
}
