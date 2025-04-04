#include "libreria.h"

int inserisci_elemento(archivio_telefonico* a, char *nome_ins, char *cognome_ins, int num)
{
    if(a->n==30)
        return -1;

    int i=a->n;
    a->n++;

    /* Si scorrono gli array di nome e cognome. Tutti i contatti che, nell'ordine alfabetico,
       seguono il contatto che si sta inserendo vengono spostati nella posizione successiva.
       Un contatto viene prima di un altro in ordine alfabetico se il suo nome viene prima
       oppure se il nome � lo stesso e il cognome viene prima*/
    while((strcmp(nome_ins, a->nome[i-1])<0 || strcmp(nome_ins,a->nome[i-1])==0 && strcmp(cognome_ins,a->cognome[i-1])<0)&& i>0){
        strcpy(a->nome[i],a->nome[i-1]);
        strcpy( a->cognome[i], a->cognome[i-1]);
        a->Numero_telefonico[i]=a->Numero_telefonico[i-1];
        a->numero_chiamate[i]=a->numero_chiamate[i-1];
        i--;
    }
    /* Il posto che si libera dallo spostamento viene occupato dal nuovo contatto */
    strcpy(a->nome[i], nome_ins);
    strcpy(a->cognome[i], cognome_ins);
    a->Numero_telefonico[i]=num;
    a->numero_chiamate[i]=0;

    return 1;
}
int ric_bin_ric(archivio_telefonico* a , stringa nominativo, stringa cogn, int primo, int ultimo) {
    int mediano;
    /* Quando l'indice del primo elemento supera quello dell'ultimo, il contatto non � nell'archivio*/
    if (primo > ultimo)
        return -1;

    /* Ogni ricorsione calcola la posizione centrale dell'array. Se il contatto che si sta cercando
       corrisponde a quello nella posizione calcolata, tale posizione viene restituita dalla funzione.
       Quando l'elemento centrale non corrisponde, se l'elemento ricercato viene prima in ordine alfabetico,
       viene chiamata ricorsivamente la funzione sulla met� destra dell'array (passando la posizione
       centrale al posto dell'ultima), se l'elemento da inserire viene dopo la funzione viene chiamata sulla
       met� sinistra (passando la posizione centrale al posto della prima) */
    else
        mediano = (primo+ultimo)/2 ;
    if (strcmp(nominativo,a->nome[mediano])==0 && strcmp(cogn,a->cognome[mediano])==0)
        return mediano;

    else if (strcmp(nominativo,a->nome[mediano])<0 || strcmp(nominativo,a->nome[mediano])==0 && strcmp(cogn,a->cognome[mediano])<0)
        return ric_bin_ric(a,nominativo,cogn,primo,mediano-1) ;
    else
        return ric_bin_ric(a,nominativo,cogn,mediano+1,ultimo) ;
}
// trova il numero ricercato tramite nome e cognome
int trova_numero(archivio_telefonico * a, stringa nome,stringa cognome)
{
   int i;
   i= ric_bin_ric(a, nome, cognome,  0,  a->n-1);
   if(i<0)
    return -1;
   return a->Numero_telefonico[i];

}
// visualizza il numero di chiamate effettuate da o verso un numero
long int trova_chiamate(archivio_telefonico *a, long int numero_inserito)
{
    int i;
    for(i=0; i<a->n; i++)
        if(numero_inserito==a->Numero_telefonico[i])
            return a->numero_chiamate[i];
    return -1;
}
// effettua una chiamata aggiungendo una chiamata al numero chiamate
int chiamata(archivio_telefonico *a ,stringa nome,stringa cognome)
{
    int i;
    i=ric_bin_ric( a,nome,  cognome, 0, a->n-1);
    if(i<0)
        return -1;
    a->numero_chiamate[i]++;
    return 1;
}
//permette la cancellazione di un numero dall'archivio telefonico
int cancella_numero( archivio_telefonico * a, stringa nome, stringa cognome)
{

    int i=ric_bin_ric( a,nome,  cognome, 0, a->n-1);
    if(i<0)
        return -1;
    while(i<a->n){
        strcpy(a->nome[i],a->nome[i+1]);
        strcpy( a->cognome[i], a->nome[i+1]);
        a->Numero_telefonico[i]=a->Numero_telefonico[i+1];
        a->numero_chiamate[i]=a->numero_chiamate[i+1];
        i++;
    }
    a->n--;

    return 1;

}
