#include <stdio.h>  // knihovna pro vstup a výstup (printf, scanf)

// definice konstant programu
#define ROK 2025
#define MIN_ZUSTATEK 100
#define MAX_ZUSTATEK 10000000
#define MIN_VKLAD 100
#define MAX_VKLAD 100000

int main(void) {

    // proměnná pro kontrolu špatného vstupu
    int buffer;

    // proměnné pro finanční výpočty (double = vyšší přesnost než float)
    double stav_uctu;        // aktuální stav účtu
    double mesicni_vklad;    // kolik se každý měsíc vloží
    double mesicni_urok;     // měsíční úroková sazba
    double rocni_urok = 3.5; // roční úroková sazba v procentech
    double urok;             // vypočítaný úrok před zdaněním
    double konecny_urok;     // úrok po odečtení daně
    double celkovy_urok = 0; // součet všech úroků za rok
    double dan;              // daň z úroku (15 %)

    // pole obsahující počet dní v jednotlivých měsících
    // používá se pouze pro výpis datumu
    int dny[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // =========================
    // ZADÁNÍ POČÁTEČNÍHO STAVU
    // =========================
    do {
        buffer = 0;

        // výzva pro uživatele
        printf("Zadejte svuj zustatek v rozmezi %d - %d: ", MIN_ZUSTATEK, MAX_ZUSTATEK);

        // načtení čísla
        scanf("%lf", &stav_uctu);

        // kontrola, jestli uživatel nezadal další znaky
        while (getchar() != '\n') {
            buffer++;
        }

        // pokud byl vstup špatný
        if (buffer != 0) {
            printf("Byl zadan spatny vstup. Zadejte znovu.\n");
        }

        // cyklus se opakuje dokud není vstup správný
    } while (buffer != 0 || stav_uctu > MAX_ZUSTATEK || stav_uctu < MIN_ZUSTATEK);


    // =========================
    // ZADÁNÍ MĚSÍČNÍHO VKLADU
    // =========================
    do {
        buffer = 0;

        printf("Zadejte, kolik chcete pravidelne mesicne vkladat v rozmezi %d - %d: ", MIN_VKLAD, MAX_VKLAD);

        scanf("%lf", &mesicni_vklad);

        // kontrola špatného vstupu
        while (getchar() != '\n') {
            buffer++;
        }

        if (buffer != 0) {
            printf("Byl zadan spatny vstup. Zadejte znovu.\n");
        }
        else if (mesicni_vklad < MIN_VKLAD) {
            printf("Zadejte vetsi pravidelny vklad.\n");
        }
        else if (mesicni_vklad > MAX_VKLAD) {
            printf("Zadejte nizsi pravidelny vklad.\n");
        }

    } while (buffer != 0 || mesicni_vklad < MIN_VKLAD || mesicni_vklad > MAX_VKLAD);


    // =====================================
    // VÝPOČET MĚSÍČNÍ ÚROKOVÉ SAZBY
    // =====================================
    // roční úrok převedeme na desetinné číslo a vydělíme 12 měsíci
    mesicni_urok = rocni_urok / 100 / 12;


    // =========================
    // VÝPIS HLAVIČKY TABULKY
    // =========================
    printf("-----------------------------------------------------------------------------------------------\n");
    printf("Rocni uroky jsou %.2lf%%\n", rocni_urok);
    printf("Stav uctu byl na pocatku roku %.2lf Kc.\n", stav_uctu);
    printf("-----------------------------------------------------------------------------------------------\n");

    printf("   datum         na pocatku mesice     vklad           urok          dan(15%%)    na konci mesice\n");


    // =========================
    // CYKLUS PRO 12 MĚSÍCŮ
    // =========================
    for (int i = 0; i < 12; i++) {

        // uloží stav účtu na začátku měsíce
        double zacatek = stav_uctu;

        // přidání pravidelného měsíčního vkladu
        stav_uctu = stav_uctu + mesicni_vklad;

        // výpočet úroku z aktuálního stavu
        urok = stav_uctu * mesicni_urok;

        // výpočet daně z úroku (15 %)
        dan = urok * 0.15;

        // skutečný úrok po odečtení daně
        konecny_urok = urok - dan;

        // přičtení úroku na účet
        stav_uctu = stav_uctu + konecny_urok;

        // přičtení úroku do celkového součtu za rok
        celkovy_urok = celkovy_urok + konecny_urok;

        // výpis jednoho řádku tabulky pro daný měsíc
        printf("%2d.%2d.%d      %12.2lf Kc  %10.2lf Kc  %10.2lf Kc  %10.2lf Kc   %12.2lf Kc\n",
               dny[i], i + 1, ROK,
               zacatek,
               mesicni_vklad,
               urok,
               dan,
               stav_uctu);
    }


    // =========================
    // KONEČNÝ VÝSLEDEK
    // =========================
    printf("-----------------------------------------------------------------------------------------------\n");

    printf("Stav na konci roku %d je %.2lf Kc. Uroky bylo za rok %d nasporeno %.2lf Kc.\n",
           ROK,
           stav_uctu,
           ROK,
           celkovy_urok);

    printf("-----------------------------------------------------------------------------------------------\n");

    return 0; // konec programu
} 
#include <stdio.h>

#define ROK 2025
#define MIN_ZUSTATEK 100
#define MAX_ZUSTATEK 10000000
#define MIN_VKLAD 100
#define MAX_VKLAD 100000

// funkce pro načtení počátečního stavu účtu
double nacti_zustatek() {

    double stav_uctu;
    int buffer;

    do {
        buffer = 0;

        printf("Zadejte svuj zustatek v rozmezi %d - %d: ", MIN_ZUSTATEK, MAX_ZUSTATEK);
        scanf("%lf", &stav_uctu);

        while (getchar() != '\n') {
            buffer++;
        }

        if (buffer != 0) {
            printf("Byl zadan spatny vstup. Zadejte znovu.\n");
        }

    } while (buffer != 0 || stav_uctu > MAX_ZUSTATEK || stav_uctu < MIN_ZUSTATEK);

    return stav_uctu;
}


// funkce pro načtení měsíčního vkladu
double nacti_vklad() {

    double mesicni_vklad;
    int buffer;

    do {
        buffer = 0;

        printf("Zadejte, kolik chcete pravidelne mesicne vkladat v rozmezi %d - %d: ", MIN_VKLAD, MAX_VKLAD);
        scanf("%lf", &mesicni_vklad);

        while (getchar() != '\n') {
            buffer++;
        }

        if (buffer != 0) {
            printf("Byl zadan spatny vstup. Zadejte znovu.\n");
        }
        else if (mesicni_vklad < MIN_VKLAD) {
            printf("Zadejte vetsi pravidelny vklad.\n");
        }
        else if (mesicni_vklad > MAX_VKLAD) {
            printf("Zadejte nizsi pravidelny vklad.\n");
        }

    } while (buffer != 0 || mesicni_vklad < MIN_VKLAD || mesicni_vklad > MAX_VKLAD);

    return mesicni_vklad;
}


// funkce pro výpis hlavičky tabulky
void vypis_hlavicku(double stav_uctu, double rocni_urok) {

    printf("-----------------------------------------------------------------------------------------------\n");
    printf("Rocni uroky jsou %.2lf%%\n", rocni_urok);
    printf("Stav uctu byl na pocatku roku %.2lf Kc.\n", stav_uctu);
    printf("-----------------------------------------------------------------------------------------------\n");

    printf("   datum         na pocatku mesice     vklad           urok          dan(15%%)    na konci mesice\n");
}


// funkce pro výpočet
void vypocet(double stav_uctu, double mesicni_vklad) {

    double rocni_urok = 3.5;
    double mesicni_urok = rocni_urok / 100 / 12;

    double urok;
    double konecny_urok;
    double celkovy_urok = 0;
    double dan;

    int dny[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

    for (int i = 0; i < 12; i++) {

        double zacatek = stav_uctu;

        stav_uctu = stav_uctu + mesicni_vklad;

        urok = stav_uctu * mesicni_urok;

        dan = urok * 0.15;

        konecny_urok = urok - dan;

        stav_uctu = stav_uctu + konecny_urok;

        celkovy_urok = celkovy_urok + konecny_urok;

        printf("%2d.%2d.%d      %12.2lf Kc  %10.2lf Kc  %10.2lf Kc  %10.2lf Kc   %12.2lf Kc\n",
               dny[i], i + 1, ROK,
               zacatek,
               mesicni_vklad,
               urok,
               dan,
               stav_uctu);
    }

    printf("-----------------------------------------------------------------------------------------------\n");

    printf("Stav na konci roku %d je %.2lf Kc. Uroky bylo za rok %d nasporeno %.2lf Kc.\n",
           ROK,
           stav_uctu,
           ROK,
           celkovy_urok);

    printf("-----------------------------------------------------------------------------------------------\n");
}


// hlavní funkce
int main() {

    double stav_uctu;
    double mesicni_vklad;

    stav_uctu = nacti_zustatek();
    mesicni_vklad = nacti_vklad();

    vypis_hlavicku(stav_uctu, 3.5);

    vypocet(stav_uctu, mesicni_vklad);

    return 0;
} #include <stdio.h>

#define ROK 2026
#define MIN_ZUSTATEK 100
#define MAX_ZUSTATEK 10000000
#define MIN_VKLAD 100
#define MAX_VKLAD 100000

// funkce pro načtení počátečního stavu účtu
double nacti_zustatek() {

    double stav_uctu;
    int buffer;

    do {
        buffer = 0;

        printf("Zadejte svuj zustatek v rozmezi %d - %d: ", MIN_ZUSTATEK, MAX_ZUSTATEK);
        scanf("%lf", &stav_uctu);

        while (getchar() != '\n') {
            buffer++;
        }

        if (buffer != 0) {
            printf("Byl zadan spatny vstup. Zadejte znovu.\n");
        }

    } while (buffer != 0 || stav_uctu > MAX_ZUSTATEK || stav_uctu < MIN_ZUSTATEK);

    return stav_uctu;
}


// funkce pro načtení měsíčního vkladu
double nacti_vklad() {

    double mesicni_vklad;
    int buffer;

    do {
        buffer = 0;

        printf("Zadejte, kolik chcete pravidelne mesicne vkladat v rozmezi %d - %d: ", MIN_VKLAD, MAX_VKLAD);
        scanf("%lf", &mesicni_vklad);

        while (getchar() != '\n') {
            buffer++;
        }

        if (buffer != 0) {
            printf("Byl zadan spatny vstup. Zadejte znovu.\n");
        }
        else if (mesicni_vklad < MIN_VKLAD) {
            printf("Zadejte vetsi pravidelny vklad.\n");
        }
        else if (mesicni_vklad > MAX_VKLAD) {
            printf("Zadejte nizsi pravidelny vklad.\n");
        }

    } while (buffer != 0 || mesicni_vklad < MIN_VKLAD || mesicni_vklad > MAX_VKLAD);

    return mesicni_vklad;
}


// funkce pro výpis hlavičky tabulky
void vypis_hlavicku(double stav_uctu, double rocni_urok) {

    printf("-----------------------------------------------------------------------------------------------\n");
    printf("Rocni uroky jsou %.2lf%%\n", rocni_urok);
    printf("Stav uctu byl na pocatku roku %.2lf Kc.\n", stav_uctu);
    printf("-----------------------------------------------------------------------------------------------\n");

    printf("   datum         na pocatku mesice     vklad           urok          dan(15%%)    na konci mesice\n");
}


// funkce pro výpočet
void vypocet(double stav_uctu, double mesicni_vklad) {

    double rocni_urok = 5.61;
    double mesicni_urok = rocni_urok / 100 / 12;

    double urok;
    double konecny_urok;
    double celkovy_urok = 0;
    double dan;

    int dny[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

    for (int i = 0; i < 12; i++) {

        double zacatek = stav_uctu;

        stav_uctu = stav_uctu + mesicni_vklad;

        urok = stav_uctu * mesicni_urok;

        dan = urok * 0.15;

        konecny_urok = urok - dan;

        stav_uctu = stav_uctu + konecny_urok;

        celkovy_urok = celkovy_urok + konecny_urok;

        printf("%2d.%2d.%d      %12.2lf Kc  %10.2lf Kc  %10.2lf Kc  %10.2lf Kc   %12.2lf Kc\n",
               dny[i], i + 1, ROK,
               zacatek,
               mesicni_vklad,
               urok,
               dan,
               stav_uctu);
    }

    printf("-----------------------------------------------------------------------------------------------\n");

    printf("Stav na konci roku %d je %.2lf Kc. Uroky byly za rok %d nasporeno %.2lf Kc.\n",
           ROK,
           stav_uctu,
           ROK,
           celkovy_urok);

    printf("-----------------------------------------------------------------------------------------------\n");
}


// hlavní funkce
int main() {

    double stav_uctu;
    double mesicni_vklad;

    stav_uctu = nacti_zustatek();
    mesicni_vklad = nacti_vklad();

    vypis_hlavicku(stav_uctu, 5.61);

    vypocet(stav_uctu, mesicni_vklad);

    return 0;
}

