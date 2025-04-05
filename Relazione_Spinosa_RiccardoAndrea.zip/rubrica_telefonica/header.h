#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <gtk/gtk.h>
#include <stdint.h>
#include "levenshtein.h"

//
extern GtkWidget *global_vbox_contatti; // Declare as extern


// DEFINIZIONE DELLA STRUTTURA PER PASSARE I WIDGET
typedef struct {
  GtkWidget *input_nome;      // WIDGET PER IL NOME
  GtkWidget *input_cognome;   // WIDGET PER IL COGNOME
  GtkWidget *input_numero;    // WIDGET PER IL NUMERO
  GtkWidget *vbox;            // CONTAINER (VBOX) DELLA FINESTRA
  GtkWidget *main_window;      //SCHERMATA INIZIALE
} ContactData;



typedef char stringa[30];

struct archivio
{
    stringa cognome[30];
    stringa nome[30];
    stringa numero_telefonico[30];
    int numero_chiamate[30];
    int n;
};

typedef struct archivio archivio_telefonico;

/*prende in ingresso l'archivio e nome, cognome e numero del contatto da inserire e lo inserisce in
  maniera ordinata restituisce un valore negativo se l'archivio ha raggiunto il numero massimo di contatti */
int inserisci_elemento(archivio_telefonico *, const char *,const char *,const char *);

/*Esegue la ricerca binaria ricorsiva dell'indice del contatto in base al nome e cognome
  in ingresso. se non ci sono contatti corrispondenti nell'archivio restituisce un valore negativo */
int ric_bin_ric(archivio_telefonico*  , stringa , stringa , int , int );

/*Prende in ingresso l'archivio e un numero telefonico di telefono e restituisce il numero di chiamate
  totali per quel numero. Se il numero non � presente nell'archivio restituisce un valore negativo */
int trova_chiamate(archivio_telefonico *, char *);

/*Prende in ingresso un archivio e il nome e il cognome di un contatto. Restituisce il numero del
  contatto inserito se presente nell'archivio, altrimenti restituisce un valore negativo */
char * trova_numero(archivio_telefonico *,stringa,stringa);

/*Prende in ingresso un archivio, il nome e il cognome di un contatto e rimuove il contatto
dall'archivio, restituisce un valore negativo se il contatto inserito non � presente nell'archivio */
int cancella_numero( archivio_telefonico *,stringa, stringa);

/*Prende in ingresso un archivio telefonico, un nome e un cognome e simula una chiamata incrementando
il numero di chiamate per il contatto inserito. Se presente nell'archivio, restituisce un valore negativo */
int chiamata(archivio_telefonico *,stringa,stringa);


void crittografare(char testo[], char chiave[]);
void decrittografare(char testo[], char chiave[]);
char * genera_chiave(char * );

void leggi_contatti(const char * , archivio_telefonico * );
void scrivi_contatti(const char * , archivio_telefonico * );


void create_window(GtkApplication *app);
void contatto_aggiunto(GtkWidget *widget, gpointer data);
void aggiungi_contatto(GtkWidget *widget, gpointer data);
void on_back_passed(GtkWidget *widget, gpointer data);
void aggiungi_barra_ricerca(GtkWidget *fixed, GtkWidget *main_window);
void on_button_clicked(GtkButton *button, gpointer user_data);
void ricerca_contatti(GtkEntry *entry, gpointer user_data);
void inoltra_chiamata(GtkWidget *widget, gpointer data);
void cancella_contatto(GtkWidget *widget, gpointer data);