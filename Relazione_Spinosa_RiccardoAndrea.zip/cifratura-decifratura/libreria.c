#include "libreria.h"

/* la function codifica il messaggio contenuto nel primo parametro, testo, in base alla chiave, contenuta nel secondo parametro e utilizzando il codice
asci per la codifica. Il testo criptato risultatante è restituito in output nel primo parametro*/
void crittografare(char testo[], char chiave[])
{
    int n,i;// dichiarazione variabili

    n=strlen(testo);// dimensione testo
    for(i=0; i<n; i++)// ciclo ripetitivo
    {
        if(chiave[i]!='A')
        {
            testo[i]+= chiave[i]-'A';/*codifica se la lettera della chiave e' diversa da a grazie al codice asci aggiungendo
            partendo dal testo il numero appertenente a chiave e sottraendo A che e il numero iniziale dell'alfabeto  per dare la lettera
            successiva alla chiave*/
            if(testo[i]>'Z')
                testo[i]=testo[i]-26;// codifica in senso circolare ripartendo da nel caso in cui il testo superi z
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
        if(chiave[i]!='A')
        {
            testo[i] = testo[i]-chiave[i]+'A';
            if(testo[i]<'A')
                testo[i]=testo[i]+26;
        }
    }
}
