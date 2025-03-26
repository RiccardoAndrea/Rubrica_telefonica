#include "libreria.h"
/*Il programma legge da tastiera un testo e una chiave (composti esclusivamente da lettere maiuscole) e utilizza due funzioni: la prima, crittografare,
trasforma il testo inserito in un testo criptato in base alla chiave scelta, mentre la seconda, decodifica, riporta il testo criptato a quello originale.
Le funzioni, rispettivamente, incrementano e decrementano il valore in codice ASCII di ogni carattere del testo di un valore pari alla posizione
nell'alfabeto del corrispondente carattere della chiave (a meno che questo non sia il carattere 'A'). I caratteri del testo sono gestiti in modo circolare: se il valore in codice ASCII scende al di
sotto di quello del carattere 'A' o al di sopra di quello del carattere 'Z', viene incrementato o decrementato di 26*/

// variante del main distribuzione casuale

int main()
{
    int i;
    char testo[6], chiave[6];
    srand(time(NULL));

    for(i=0; i<5; i++)
        testo[i] = rand()%26 + 65;
    for(i=0; i<5; i++)
        chiave[i] = rand()%26 + 65;

    printf("Il testo e': %s\n", testo);
    printf("La chiave e': %s\n", chiave);

    crittografare(testo, chiave);
    printf("Il testo criptato e': %s\n", testo);

    decrittografare(testo, chiave);
    printf("Il testo decriptato e': %s\n", testo);

    return 0;
}


/*
int main()
{
    char testo[100]; //dichiarazione del testo
    char chiave[100]; //dichiarazione della chiave da cifrare

    printf("attenzione il TESTO e la CHIAVE devono essere maiuscoli\n");
    printf("dammi il testo\n");
    gets(testo);// inserimento del testo da crittografare
    printf("dammi la chiave\n");
    gets(chiave); //inserimento della chiave con cuo si crittografera' il messaggio

    printf("il testo e': %s\n", testo); //visualizzazione testo
    printf("la chiave e': %s\n", chiave); //visualizzazione chiave

    crittografare(testo,chiave);//chiamata per la crittografia
    printf("il testo crittografato e': %s\n", testo); //testo crittografato

    decrittografare(testo,chiave);//chiamata alla function della decrittografazione
    printf("il testo decrittografato e': %s\n", testo); //testo decrittografato

    return 0;

}
*/
/*
int main()
{
char testo[13]="THEPRESIDENT", chiave[13]="CODECODECODE";
crittografare(testo,chiave);
printf("il testo crittografato e:\n");
puts(testo);
decrittografare(testo,chiave);
printf("il testo decrittografato e:\n");
puts(testo);
return 0;
}
*/
