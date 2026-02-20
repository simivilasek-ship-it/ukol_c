#include <stdio.h>
#include <stdlib.h>

/* ===== Symbolické konstanty ===== */
#define UROKOVA_MIRA 0.05     // roční úroková míra (např. 5,61 %)
#define DAN_Z_UROKU 0.15         // daň z úroku 15 %
#define MIN_VKLAD 1000           // minimální počáteční stav
#define MAX_VKLAD 10000000       // maximální počáteční stav
#define MIN_MESICNI_VKLAD 0      // minimální měsíční vklad
#define MAX_MESICNI_VKLAD 1000000// maximální měsíční vklad
#define ROK 2026                 // rok simulace
#define POCET_MESICU 12          // počet měsíců v roce

/* ===== Funkce pro zjištění přestupného roku ===== */
int jePrestupny(int rok) {
    /* Rok je přestupný pokud:
       - je dělitelný 4 a není dělitelný 100
       - nebo je dělitelný 400 */
    if ((rok % 4 == 0 && rok % 100 != 0) || (rok % 400 == 0))
        return 1;
    else
        return 0;
}

/* ===== Funkce pro zjištění počtu dní v měsíci ===== */
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

    return 0; // neplatný měsíc
}

/* ===== Funkce pro načtení čísla v daném intervalu ===== */
double nacti(double min, double max) {
    double x;

    do {
        printf("Zadej hodnotu (%.2f - %.2f): ", min, max);
        scanf("%lf", &x);

        // kontrola, zda je hodnota v povoleném rozsahu
        if (x < min || x > max) {
            printf("Hodnota mimo povoleny rozsah!\n");
        }

    } while (x < min || x > max);

    return x;
}

/* ===== Hlavní program ===== */
int main(void) {

    double pocatecni_stav;   // stav účtu na začátku roku
    double mesicni_vklad;    // pravidelný měsíční vklad
    double stav;             // aktuální stav účtu
    double urok;             // vypočítaný měsíční úrok
    double dan;              // daň z úroku

    printf("Simulace sporiciho uctu\n\n");

    // načtení počátečního stavu
    pocatecni_stav = nacti(MIN_VKLAD, MAX_VKLAD);

    // načtení pravidelného měsíčního vkladu
    mesicni_vklad = nacti(MIN_MESICNI_VKLAD, MAX_MESICNI_VKLAD);

    stav = pocatecni_stav;

    printf("\nVypis uctu za rok %d\n", ROK);
    printf("Rocni urokova mira: %.2f %%\n\n", UROKOVA_MIRA * 100);

    /* ===== Cyklus přes jednotlivé měsíce ===== */
    for (int mesic = 1; mesic <= POCET_MESICU; mesic++) {

        // Přičtení měsíčního vkladu
        stav += mesicni_vklad;

        // Výpočet měsíčního úroku (ročni úrok / 12)
        urok = stav * (UROKOVA_MIRA / 12);

        // Výpočet daně z úroku
        dan = urok * DAN_Z_UROKU;

        // Aktualizace stavu (stav + úrok - daň)
        stav = stav + urok - dan;

        // Výpis údajů za daný měsíc
        printf("Datum: %d.%d.%d\n",
               pocetDni(mesic, ROK), mesic, ROK);

        printf("Vklad: %.2f Kc\n", mesicni_vklad);
        printf("Urok: %.2f Kc\n", urok);
        printf("Dan: %.2f Kc\n", dan);
        printf("Stav na konci mesice: %.2f Kc\n\n", stav);
    }

    /* ===== Závěrečný výpis ===== */
    printf("=====================================\n");
    printf("Pocatecni stav: %.2f Kc\n", pocatecni_stav);
    printf("Konecny stav: %.2f Kc\n", stav);
    printf("Rozdil: %.2f Kc\n", stav - pocatecni_stav);

    return 0;
}
