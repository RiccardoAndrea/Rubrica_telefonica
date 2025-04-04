#include "header.h"

void scrivi_contatti(const char * nome_file, archivio_telefonico * a){
    if(a->n == 100)
    {
        printf("impossibile aggiungere contatti memoria piena");
        return;
    }
    int n = a->n;
    

    
    FILE *file = fopen(nome_file, "w");
    FILE *file_chiave = fopen("chiavi_contatti_criptate.txt", "w");
    FILE *file_chiave_criptata = fopen("chiavi_delle_chiavi.txt", "w");

    if (!file || !file_chiave || !file_chiave_criptata) 
    {
        printf("Errore nell'aprire il file\n");
        return;
    }


    char *chiave_nome[n+1];
    char *chiave_cognome[n+1];
    char *chiave_numero[n+1];  
    for (int i = 0; i < n+1; i++) {
        chiave_nome[i] = malloc(30 * sizeof(char));
        chiave_cognome[i] = malloc(30 * sizeof(char));
        chiave_numero[i] = malloc(30 * sizeof(char));

        // Verifica se malloc ha avuto successo
        if (!chiave_nome[i] || !chiave_cognome[i] || !chiave_numero[i]) 
        {
            printf("Errore nell'allocazione della memoria\n");
            return; 
            // Esci se c'è un errore nell'allocazione
        }
    }
   
    for(int i = 0; i < n; i++)
    {
        char *temp_nome = genera_chiave(a->nome[i]);
        strcpy(chiave_nome[i], temp_nome);
        free(temp_nome);
    
        char *temp_cognome = genera_chiave(a->cognome[i]);
        strcpy(chiave_cognome[i], temp_cognome);
        free(temp_cognome);
    
        char *temp_numero = genera_chiave(a->numero_telefonico[i]);
        strcpy(chiave_numero[i], temp_numero);
        free(temp_numero);
    }
    


    
    for(int i = 0; i < n; i++)
    {
        crittografare(a->nome[i], chiave_nome[i]);
        crittografare(a->cognome[i], chiave_cognome[i]);
        crittografare(a->numero_telefonico[i], chiave_numero[i]);
    }
    

    for(int i = 0; i < n; i++)
    {
        fprintf(file, "%s\n", a->nome[i]);
        fprintf(file, "%s\n", a->cognome[i]);
        fprintf(file, "%s\n", a->numero_telefonico[i]);
    }

    //alloco lo spazio per le chiavi criptate
    char *chiave_nome_criptata[n+1];
    char *chiave_cognome_criptata[n+1];
    char *chiave_numero_criptata[n+1];  
    for (int i = 0; i < n+1; i++) {
        chiave_nome_criptata[i] = malloc(30 * sizeof(char));
        chiave_cognome_criptata[i] = malloc(30 * sizeof(char));
        chiave_numero_criptata[i] = malloc(30 * sizeof(char));

        // Verifica se malloc ha avuto successo
        if (!chiave_nome_criptata[i] || !chiave_cognome_criptata[i] || !chiave_numero_criptata[i]) 
        {
            printf("Errore nell'allocazione della memoria\n");
            return; 
            // Esci se c'è un errore nell'allocazione
        }
    }
    
    //genero le chiavi criptate
    for(int i = 0; i < n; i++)
    {
        char *temp_nome = genera_chiave(chiave_nome[i]);
        strcpy(chiave_nome_criptata[i], temp_nome);
        free(temp_nome);
    
        char *temp_cognome = genera_chiave(chiave_cognome[i]);
        strcpy(chiave_cognome_criptata[i], temp_cognome);
        free(temp_cognome);
    
        char *temp_numero = genera_chiave(chiave_numero[i]);
        strcpy(chiave_numero_criptata[i], temp_numero);
        free(temp_numero);
    }

     // Salva le chiavi criptate in un file separato
     for(int i = 0; i < n; i++)
     {
         fprintf(file_chiave_criptata, "%s\n", chiave_nome_criptata[i]);
         fprintf(file_chiave_criptata, "%s\n", chiave_cognome_criptata[i]);
         fprintf(file_chiave_criptata, "%s\n", chiave_numero_criptata[i]);
     }

    // criptiamo le chiavi
    for(int i = 0; i < n; i++)
    {
        crittografare(chiave_nome[i], chiave_nome_criptata[i]);
        crittografare(chiave_cognome[i], chiave_cognome_criptata[i]);
        crittografare(chiave_numero[i], chiave_numero_criptata[i]);
    }

    // Salva le chiavi criptate in un file separato
    for(int i = 0; i < n; i++)
    {
        fprintf(file_chiave, "%s\n", chiave_nome[i]);
        fprintf(file_chiave, "%s\n", chiave_cognome[i]);
        fprintf(file_chiave, "%s\n", chiave_numero[i]);
    }


    //decrittografiamo per ottenere le info decriptate
    for(int i = 0; i < n; i++)
    {
        decrittografare(chiave_nome[i], chiave_nome_criptata[i]);
        decrittografare(chiave_cognome[i], chiave_cognome_criptata[i]);
        decrittografare(chiave_numero[i], chiave_numero_criptata[i]);
    }

    for(int i = 0; i < n; i++)
    {
        decrittografare(a->nome[i], chiave_nome[i]);
        decrittografare(a->cognome[i], chiave_cognome[i]);
        decrittografare(a->numero_telefonico[i], chiave_numero[i]);
    }
    
    // Libero la memoria allocata
    for (int i = 0; i < n+1; i++) 
    {
        free(chiave_nome[i]);
        free(chiave_cognome[i]);
        free(chiave_numero[i]);
    }

    for (int i = 0; i < n+1; i++) 
    {
        free(chiave_nome_criptata[i]);
        free(chiave_cognome_criptata[i]);
        free(chiave_numero_criptata[i]);
    }

    // chiudo i file aperti
    fclose(file);
    fclose(file_chiave);
    fclose(file_chiave_criptata);

}






void leggi_contatti(const char * nome_file, archivio_telefonico * rubrica){
    FILE *file = fopen(nome_file, "r");
    FILE *file_chiave = fopen("chiavi_contatti_criptate.txt", "r");
    FILE *file_chiave_criptata = fopen("chiavi_delle_chiavi.txt", "r");

    if (!file || !file_chiave || !file_chiave_criptata) {
        printf("Errore nell'aprire il file\n");
        return;
    }

    char parola[100];
    int cont = 0;

    //leggo il file criptato
    
    while (fgets(parola, sizeof(parola), file)) {
        rubrica->n = cont + 1;
        // Rimuovi eventuale newline alla fine della riga
        parola[strcspn(parola, "\n")] = 0;  // Rimuove il newline
        
        strcpy(rubrica->nome[cont], parola);
        
        fgets(parola, sizeof(parola), file);
        parola[strcspn(parola, "\n")] = 0;
       
        strcpy(rubrica->cognome[cont], parola);
    
        fgets(parola, sizeof(parola), file);
        parola[strcspn(parola, "\n")] = 0;
        strcpy(rubrica->numero_telefonico[cont], parola);
    
        cont++;
       
    }




    int n = rubrica->n;
    //alloco lo spazio per le chiavi delle chiavi
    char *chiave_nome_criptata[n+1];
    char *chiave_cognome_criptata[n+1];
    char *chiave_numero_criptata[n+1];  
    for (int i = 0; i < n+1; i++) {
        chiave_nome_criptata[i] = malloc(30 * sizeof(char));
        chiave_cognome_criptata[i] = malloc(30 * sizeof(char));
        chiave_numero_criptata[i] = malloc(30 * sizeof(char));

        // Verifica se malloc ha avuto successo
        if (!chiave_nome_criptata[i] || !chiave_cognome_criptata[i] || !chiave_numero_criptata[i]) 
        {
            printf("Errore nell'allocazione della memoria\n");
            return; 
            // Esci se c'è un errore nell'allocazione
        }
    }

    // recupero le chiavi delle chiavi
    cont = 0;
    while (fgets(parola, sizeof(parola), file_chiave_criptata)) {
        parola[strcspn(parola, "\n")] = 0;  // Rimuove il newline
        strcpy(chiave_nome_criptata[cont], parola);
    
        fgets(parola, sizeof(parola), file_chiave_criptata);
        parola[strcspn(parola, "\n")] = 0;
        strcpy(chiave_cognome_criptata[cont], parola);
    
        fgets(parola, sizeof(parola), file_chiave_criptata);
        parola[strcspn(parola, "\n")] = 0;
        strcpy(chiave_numero_criptata[cont], parola);
    
        cont++;
    }
   
    //alloco spazio per le chiavi
    char *chiave_nome[n+1];
    char *chiave_cognome[n+1];
    char *chiave_numero[n+1];  

    

    for (int i = 0; i < n+1; i++) {
        chiave_nome[i] = malloc(30 * sizeof(char));
        chiave_cognome[i] = malloc(30 * sizeof(char));
        chiave_numero[i] = malloc(30 * sizeof(char));

        // Verifica se malloc ha avuto successo
        if (!chiave_nome[i] || !chiave_cognome[i] || !chiave_numero[i]) {
            printf("Errore nell'allocazione della memoria\n");
            return; // Esci se c'è un errore nell'allocazione
        }
    }


    //recupero le chiavi
    cont = 0;
    while (fgets(parola, sizeof(parola), file_chiave)) {
        parola[strcspn(parola, "\n")] = 0;  // Rimuove il newline
        strcpy(chiave_nome[cont], parola);
    
        fgets(parola, sizeof(parola), file_chiave);
        parola[strcspn(parola, "\n")] = 0;
        strcpy(chiave_cognome[cont], parola);
    
        fgets(parola, sizeof(parola), file_chiave);
        parola[strcspn(parola, "\n")] = 0;
        strcpy(chiave_numero[cont], parola);
    
        cont++;
    }


    // decripto le chiavi
    for(int i = 0; i < rubrica->n; i++)
    {
        decrittografare(chiave_nome[i], chiave_nome_criptata[i]);
        decrittografare(chiave_cognome[i], chiave_cognome_criptata[i]);
        decrittografare(chiave_numero[i], chiave_numero_criptata[i]);
    }

   
    

    // decripto i contatti
    for(int i = 0; i < rubrica->n; i++)
    {
        decrittografare(rubrica->nome[i], chiave_nome[i]);
        decrittografare(rubrica->cognome[i], chiave_cognome[i]);
        decrittografare(rubrica->numero_telefonico[i], chiave_numero[i]);
    }


   // Libero la memoria allocata
   for (int i = 0; i < n+1; i++) {
        free(chiave_nome[i]);
        free(chiave_cognome[i]);
        free(chiave_numero[i]);
    }

    for (int i = 0; i < n+1; i++) 
    {
        free(chiave_nome_criptata[i]);
        free(chiave_cognome_criptata[i]);
        free(chiave_numero_criptata[i]);
    }


    fclose(file);
    fclose(file_chiave);
    fclose(file_chiave_criptata);
    
}