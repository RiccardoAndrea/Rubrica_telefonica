#include <stdio.h>
#include <stdlib.h>
#include "string.h"


typedef char stringa[100];

struct archivio
{
    stringa cognome[30];
    stringa nome[30];
    int Numero_telefonico[30];
    int numero_chiamate[30];
    int n;
};
typedef struct archivio archivio_telefonico;

/*prende in ingresso l'archivio e nome, cognome e numero del contatto da inserire e lo inserisce in
  maniera ordinata restituisce un valore negativo se l'archivio ha raggiunto il numero massimo di contatti */
int inserisci_elemento(archivio_telefonico *, char *, char *, int);

/*Esegue la ricerca binaria ricorsiva dell'indice del contatto in base al nome e cognome
  in ingresso. se non ci sono contatti corrispondenti nell'archivio restituisce un valore negativo */
int ric_bin_ric(archivio_telefonico*  , stringa , stringa , int , int );

/*Prende in ingresso l'archivio e un numero telefonico di telefono e restituisce il numero di chiamate
  totali per quel numero. Se il numero non è presente nell'archivio restituisce un valore negativo */
int trova_chiamate(archivio_telefonico *, int);

/*Prende in ingresso un archivio e il nome e il cognome di un contatto. Restituisce il numero del
  contatto inserito se presente nell'archivio, altrimenti restituisce un valore negativo */
int trova_numero(archivio_telefonico *,stringa,stringa);

/*Prende in ingresso un archivio, il nome e il cognome di un contatto e rimuove il contatto
dall'archivio, restituisce un valore negativo se il contatto inserito non è presente nell'archivio */
int cancella_numero( archivio_telefonico *,stringa, stringa);

/*Prende in ingresso un archivio telefonico, un nome e un cognome e simula una chiamata incrementando
il numero di chiamate per il contatto inserito. Se presente nell'archivio, restituisce un valore negativo */
int chiamata(archivio_telefonico *,stringa,stringa);
