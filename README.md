# Rubrica Telefonica con Criptografia

Questo progetto implementa un sistema di gestione di una rubrica telefonica in C su Linux, con funzionalità di crittografia dei dati sensibili. La rubrica permette di memorizzare, cercare, modificare e cancellare contatti telefonici. I contatti sono protetti da una crittografia a più livelli, e le chiavi di crittografia vengono gestite separatamente per garantire la sicurezza dei dati.

## Funzionalità

1. **Aggiunta di contatti**: Inserimento di nuovi contatti nella rubrica. I contatti vengono ordinati automaticamente in ordine alfabetico.
2. **Ricerca contatti**: Ricerca autocomplete mediante distanza di Levenshtein.
3. **Visualizzazione delle chiamate**: Ogni contatto ha un contatore che tiene traccia del numero di chiamate effettuate da o verso quel contatto.
4. **Effettuare chiamate**: Incremento del contatore delle chiamate per ogni chiamata effettuata a un contatto.
5. **Cancellazione di contatti**: Rimozione di un contatto dalla rubrica. Utilizzo della ricerca binaria per cercare un contatto con nome e cognome.
6. **Criptografia dei dati**: Tutti i dati sensibili (nome, cognome, numero di telefono) sono criptati con una chiave generata e gestita separatamente.


## Come funziona

### Archiviazione dei dati

I contatti vengono memorizzati in file separati:

- **contatti.txt**: Contiene i dati dei contatti, come nome, cognome e numero di telefono, criptati.
- **chiavi_contatti_criptate.txt**: Contiene le chiavi per la crittografia dei contatti.
- **chiavi_delle_chiavi.txt**: Contiene le chiavi per la crittografia delle chiavi.

### Crittografia

La crittografia viene realizzata tramite una semplice cifra basata sul codice ASCII dei caratteri. I contatti e le chiavi sono criptati in modo circolare per impedire la visualizzazione diretta dei dati.

### Funzioni principali
implementa le funzionalità di una rubrica telefoni.
Supponiamo che un ente pubblico necessiti di una rubrica contenente i dipendenti pubblici. Dall'applicazione desktop puo visualizzare i contatti fornire numeri aggiungerli o cancellarli.
Caso D'uso di esempio.
Si allaga la scuola e bisogna reperire il numero del dipendente di turno che possiede la reperibilità. Segnalata l'urgenza cerca il contatto telefonica e lo chiama, messaggia o invia una notifica.

## Compilazione e Esecuzione

### Prerequisiti


- Compilatore C (gcc)
- Librerie standard C

### Istruzioni per la compilazione

1. esegui il comando
    ```bash
    gcc -o main main.c gestione_file.c archivio_telefonico.c cifratura_decifratura.c gui.c levenshtein.c $(pkg-config --cflags --libs gtk+-3.0)
2. se ti trovi già su linux puoi anche direttamente lanciare l'eseguibile con il comando
    ```bash
    ./main



## Tecnologie Utilizzate
- C
- GTK per interfaccia

