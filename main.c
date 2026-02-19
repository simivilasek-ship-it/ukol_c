#include <stdio.h>
#include <stdlib.h>

#define UROKOVA_MIRA 0.05
#define DAN_Z_UROKU 0.03
#define MIN_CASTKA 100
#define MAX_CASTKA 10000000
#define ROK 2026
#define SOUBOR "vypisUctu.txt"
#define POCET_MESICU 12




int jePrestupny(int rok) {
    if ((rok % 4 == 0 && rok % 100 != 0) || (rok % 400 == 0))
        return 1;
    else
        return 0;
}



int pocet_dni(int mesic, int rok) {
    if (mesic==1 || mesic==3 || mesic==5 || mesic==7 || mesic==8 || mesic==10 || mesic==12)
        return 31;
    if (mesic==2 || mesic==4 || mesic==6 || mesic==9 || mesic==11)
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
        } while (x < min || x > max);

        return x;
    }


double nacti(double min, double max);
int jePrestupny(int rok);
int pocetDni(int mesic, int rok);
int main(void) {

    double pocatecni_stav;
    double mesicni_vklad;
    double stav;
    double urok;
    double dan;

    FILE *f;

    printf("Simulace sporiciho uctu\n");

    pocatecni_stav = nacti(1000, 10000000);
    mesicni_vklad = nacti(0, 1000000);

    stav = pocatecni_stav;

    f = fopen(SOUBOR, "w");

    fprintf(f, "Vypis uctu za rok %d\n\n", ROK);

    for (int mesic = 1; mesic <= 12; mesic++) {

        stav = stav + mesicni_vklad;

        urok = stav * (UROKOVA_MIRA / 12);
        dan = urok * DAN_Z_UROKU;

        stav = stav + urok - dan;

        fprintf(f, "Datum: %d.%d.%d\n",
                pocet_dni(mesic, ROK), mesic, ROK);
        fprintf(f, "Urok: %.2f\n", urok);
        fprintf(f, "Dan: %.2f\n", dan);
        fprintf(f, "Stav: %.2f\n\n", stav);
    }

    fprintf(f, "Konecny stav: %.2f\n", stav);
    fprintf(f, "Rozdil: %.2f\n", stav - pocatecni_stav);

    fclose(f);

    printf("Hotovo. Vypis je v souboru %s\n", SOUBOR);

    return 0;
}