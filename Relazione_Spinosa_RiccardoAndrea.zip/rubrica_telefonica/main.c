#include "header.h"
#define MAX_CONTACTS 30

void mostra_menu() {
    printf("Seleziona un'opzione:\n");
    printf("1. Inserisci contatto\n");
    printf("2. Cerca contatto\n");
    printf("3. Effettua chiamata\n");
    printf("4. Cancella contatto\n");
    printf("5. Visualizza numero chiamate\n");
    printf("6. Esci\n");
    printf("7. Visualizza tutti i contatti\n"); 
}

void visualizza_tutti_contatti(archivio_telefonico *rubrica) {
    if (rubrica->n == 0) {
        printf("Rubrica vuota!\n\n");
        return;
    }

    printf("\nLista contatti:\n");
    for (int i = 0; i < rubrica->n; i++) {
        printf("%d. %s %s - %s\n", i + 1, rubrica->nome[i], rubrica->cognome[i], rubrica->numero_telefonico[i]);
    }
    printf("\n");
}


int main() {
    archivio_telefonico rubrica;
    rubrica.n = 0; // inizializza il numero di contatti a 0
    char nome[30], cognome[30], numero[30];
    int scelta;

    // Carica i contatti da file all'avvio (se presenti)
    leggi_contatti("contatti.txt", &rubrica);

    while (1) {
        mostra_menu();
        printf("Scelta: ");
        scanf("%d", &scelta);

        switch (scelta) {
            case 1: // Inserisci contatto
                printf("Inserisci nome: ");
                scanf("%s", nome);
                printf("Inserisci cognome: ");
                scanf("%s", cognome);
                printf("Inserisci numero: ");
                scanf("%s", numero);

                if (inserisci_elemento(&rubrica, nome, cognome, numero) == 1) {
                    printf("Contatto inserito con successo.\n");
                    printf("\n\n");
                } else {
                    printf("Memoria piena! Impossibile aggiungere il contatto.\n");
                }
                break;

            case 2: // Cerca contatto
                printf("Inserisci nome da cercare: ");
                scanf("%s", nome);
                printf("Inserisci cognome da cercare: ");
                scanf("%s", cognome);

                char *numero_ricercato = trova_numero(&rubrica, nome, cognome);
                if (numero_ricercato != NULL) {
                    printf("Numero trovato: %s\n", numero_ricercato);
                    printf("\n\n");
                } else {
                    printf("Contatto non trovato.\n");
                    printf("\n\n");
                }
                break;

            case 3: // Effettua chiamata
                printf("Inserisci nome: ");
                scanf("%s", nome);
                printf("Inserisci cognome: ");
                scanf("%s", cognome);

                if (chiamata(&rubrica, nome, cognome) == 1) {
                    printf("Chiamata effettuata.\n");
                    printf("\n\n");
                } else {
                    printf("Contatto non trovato.\n");
                    printf("\n\n");
                }
                break;

            case 4: // Cancella contatto
                printf("Inserisci nome da cancellare: ");
                scanf("%s", nome);
                printf("Inserisci cognome da cancellare: ");
                scanf("%s", cognome);

                if (cancella_numero(&rubrica, nome, cognome) == 1) {
                    printf("Contatto cancellato con successo.\n");
                    printf("\n\n");
                    
                } else {
                    printf("Contatto non trovato.\n");
                    printf("\n\n");
                }
                break;

            case 5: // Visualizza numero chiamate
                printf("Inserisci numero da cercare: ");
                scanf("%s", numero);

                int num_chiamate = trova_chiamate(&rubrica, numero);
                if (num_chiamate >= 0) {
                    printf("Numero di chiamate: %d\n", num_chiamate);
                    printf("\n\n");
                } else {
                    printf("Numero non trovato.\n");
                    printf("\n\n");
                }
                break;


            case 6: // Esci
                scrivi_contatti("contatti.txt", &rubrica);  // Salva i contatti prima di uscire
                printf("Uscita...\n");
                return 0;
            case 7: // Visualizza tutti i contatti
                visualizza_tutti_contatti(&rubrica);
                break;
                
            default:
                printf("Scelta non valida. Riprova.\n");
        }
    }

    return 0;
}
