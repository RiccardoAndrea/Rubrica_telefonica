#include "libreria.h"

/*
il programma simula una rubrica telefonica nella quale �' possibile inserire un contatto,
visualizzarne il numero di chiamate e il numero telefonico o rimuoverlo.
*/


void main()
{
    
    char nome_ins[100], cognome_ins[100];

    archivio_telefonico a;
    a.n = 0;
    int x=-1;
    long int num;

    while(x<5)
    {

        printf("\n\npremi 0 se vuoi inserire un numero in rubrica\n premi 1 se vuoi cancellarlo\n premi 2 se vuoi vedere il numero di chiamate effettuate\n");
        printf("premi 3 se vuoi  chiamare\n premi 4 se vuoi cercare un numero in rubrica\n premi 5 se vuoi uscire dalla rubrica\n");
        scanf("%d",&x);
        switch(x)
        {
            case 0:
            printf("inserisci il nome della persona\n");
            scanf("%s",nome_ins);
            printf("inserisci il cognome della persona\n");
            scanf("%s",cognome_ins);

            printf("inserisci numero di telefono\n");
            scanf("%ld",&num);
            num = inserisci_elemento(&a,nome_ins,cognome_ins,num);


            if(num < 0)
                printf("Impossibile inserire un nuovo contatto, raggiunto il numero massimo di contatti in rubrica\n");
            else
                printf("Contatto aggiunto correttamente\n");
            break;

            case 1:
            printf("inserisci il nome della persona\n");
            scanf("%s", nome_ins);
            printf("inserisci il cognome della persona\n");
            scanf("%s", cognome_ins);
            num = cancella_numero (&a,nome_ins, cognome_ins);
            if(num<0)
                printf("contatto eliminato dalla rubrica\n\n");
            else
                printf("Contatto rimosso dalla rubrica\n\n");
            break;

            case 2:
            printf("inserisci numero di telefono\n");
            scanf("%ld",&num);
            num = trova_chiamate(&a, num);
            if(num<0)
                printf("Il contatto non e' presente in rubrica\n\n");
            else
                printf("Il numero di chiamate e': %ld\n", num);
            break;

            case 3:
            printf("inserisci il nome della persona\n");
            scanf("%s", nome_ins);
            printf("inserisci il cognome della persona\n");
            scanf("%s", cognome_ins);
            num = chiamata(&a , nome_ins, cognome_ins);
            if(num<0)
                printf("Il contatto non e' presente in rubrica\n\n");
            else
                printf("Chiamata effettuata\n\n");
            break;

            case 4:
            printf("inserisci il nome della persona\n");
            scanf("%s", nome_ins);
            printf("inserisci il cognome della persona\n");
            scanf("%s", cognome_ins);
            num = trova_numero(&a,nome_ins,cognome_ins);
            if(num<0)
                printf("Il contatto inserito non e' presente in rubrica\n\n");
            else
                printf("Il numero di %s e': %ld\n", nome_ins, num);
            break;

            case 5:
                break;

            default:
                printf("Il numero inserito e' errato\n");
                break;

        }
    }
}






