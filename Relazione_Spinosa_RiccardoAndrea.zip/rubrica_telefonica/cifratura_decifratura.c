#include "header.h"

/* la function codifica il messaggio contenuto nel primo parametro, testo, in base alla chiave, contenuta nel secondo parametro e utilizzando il codice
asci per la codifica. Il testo criptato risultatante è restituito in output nel primo parametro*/
void crittografare(char testo[], char chiave[])
{
    int n,i;// dichiarazione variabili

    n=strlen(testo);// dimensione testo
    for(i=0; i<n; i++)// ciclo ripetitivo
    {
        if(chiave[i]!='!')
        {
            testo[i]+= chiave[i]-'!';/*codifica se la lettera della chiave e' diversa da ! grazie al codice asci aggiungendo
            partendo dal testo il numero appertenente a chiave e sottraendo ! che e il numero iniziale dell'alfabeto  per dare la lettera
            successiva alla chiave*/
            if(testo[i]>255)
                testo[i]=testo[i]-94;// codifica in senso circolare ripartendo da nel caso in cui il testo superi il carattere
        }
    }

}


/* la function decodifica il messaggio contenuto nel primo parametro, testo, in base alla chiave, contenuta nel secondo parametro e utilizzando il codice
asci per la decodifica. Il testo decriptato risultatante è restituito in output nel primo parametro*/
void decrittografare(char testo[], char chiave[])
{
   int n,i;
    n=strlen(testo);// dimensione testo
    /*Il seguente ciclo for scorre la stringa testo per tutta la sua lunghezza (calcolata con la funzione strlen) e decrementa ciascun carattere di un
      valore pari alla posizione nell'alfabeto del corrispondente carattere della chiave (chiave[i]-'A'). Se il valore risulatnte in codice ASCII scende al
      di sotto di quello del carattere 'A', questo è incementato di 26, in modo che le lettere siano gestite in maniera circolare rispetto all'alfabeto*/
    for(i=0; i<n; i++)// ciclo iterativo
    {
        if(chiave[i]!='!')
        {
            testo[i] = testo[i]-chiave[i]+'!';
            if(testo[i]<'!')
                testo[i]=testo[i]+94;
        }
    }
}


char * genera_chiave(char * testo)
{
    int n = strlen(testo);
    char * password = (char *)malloc(sizeof(char) * (n+1) );
    for (int i = 0; i < n; i++) {
        unsigned char carattere_testo = testo[i];
        unsigned char salt = rand() % 256;
        unsigned char carattere_password = rand() % (carattere_testo + salt);
        
        if(carattere_password < 33)
            carattere_password = carattere_password + 33;
        else if (carattere_password > 126)
            carattere_password = rand() % 94 + 33;
        password[i] = carattere_password;
    }
    password[n] = '\0'; // Terminatore di stringa
    return password;
}


