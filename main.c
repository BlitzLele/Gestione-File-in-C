//Classe 4INA
//Sorrentino Samuele

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void input(int cont);
void stampa(FILE *fp);
void ricerca(int codice, FILE *fp);
void ordinamento(FILE *fp);
void modifica(FILE *fp);
void cancellazione(FILE *fp);

typedef struct
{
    char nome[20];
    char cognome[20];
    int codice;
    float stipendio;
    int tmp;

} persona;

int main()
{
    FILE *fp;
    int i=0;
    int cont=0;
    int scelta;
    int codice=0;
    int fine;

    persona p;

    do
    {
        printf("\n");
        printf ("Scegli una tra queste operazioni:\n 1)Scrivere nel File\n 2)Stampare i dati nel File\n 3)Ricercare un dato nel File\n 4)Ordinare gli studenti\n 5)Modifica di uno studente\n 6)Cancellazione di uno studente\n 0)Fine\n");
        printf("\n");
        scanf ("%d",& scelta);
            switch (scelta)
            {
                default:
                printf("L'input non e' valido");

    case 1:;
                input(cont);
                break;

    case 2:;
                stampa(fp);
                break;

    case 3:;

                ricerca(codice,fp);
                break;

    case 4:;

                ordinamento(fp);
                break;

    case 5:;

                modifica(fp);
                break;

    case 6:;
                cancellazione(fp);
                break;

    case 0:
        fine = 1;
        break;
            }

    }
    while(scelta!=0);
    return 0;
}

void input(int cont)
{
    FILE *fp;
    int i;
    persona p;
    fp = fopen("archivio.dat", "ab");
    printf("\nScegli il numero di studenti da registrare: ");
    scanf("%d",& cont);
    for (i=0 ; i<cont ; i++)
    {
        printf("\nInserisci il Nome: ");
        scanf("%s",& p.nome);
        printf("\nInserisci il Cognome: ");
        scanf("%s",& p.cognome);
        printf("\nInserisci il Codice: ");
        scanf("%d",& p.codice);
        printf("\nInserisci lo Stipendio: ");
        scanf("%f",& p.stipendio);
        fwrite(&p,sizeof(persona),1,fp);
    }
    fclose(fp);
}

void stampa(FILE *fp)
{
    persona p;
    fp = fopen("archivio.dat", "rb");
    printf("|CODICE| \t\t |COGNOME| \t\t |NOME| \t\t |STIPENDIO|\n");
    while (fread(&p,sizeof(persona),1,fp)>0)
    {

        printf("\n|%03d| \t\t\t |%0s| \t\t |%0s| \t\t |%0.2f|\n",p.codice, p.cognome, p.nome, p.stipendio);
    }
    fclose(fp);
}

void ricerca(int codice,FILE *fp)
{
    persona p;
    printf("\n Inserire il codice da ricercare: ");
    scanf("%d",& codice);
    fp = fopen("archivio.dat", "rb");
    while (fread(&p,sizeof(persona),1,fp)>0)
    {
        if (codice==p.codice)
        {
            printf("\n %d %s %s %0.2f\n" ,p.codice, p.cognome, p.nome, p.stipendio);
        }
    }
    fclose(fp);
}

void ordinamento (FILE *fp)
{
    persona p;
    fp = fopen("archivio.dat", "rb");
    persona a[20], appoggio[20];
        int n1 = 0, i, j;
        while (fread(&p, sizeof(persona), 1, fp) > 0)
        {
            a[n1].codice = p.codice;
            a[n1].stipendio = p.stipendio;
            strcpy(a[n1].cognome, p.cognome);
            strcpy(a[n1].nome, p.nome);
            n1++;
        }
        for (i=0 ; i<n1-1 ; i++)
        {
            for (j=i+1 ; j<n1 ; j++)
            {
                if (strcmp(a[j].cognome, a[i].cognome) < 0)
                {
                    appoggio[0] = a[j];
                    a[j] = a[i];
                    a[i] = appoggio[0];
                }
            }
        }
        fclose(fp);
        fp = fopen("archivio.dat", "wb");
        for (i = 0; i < n1; i++)
        fclose(fp);
        fp = fopen("archivio.dat", "wb");

        for (i = 0; i < n1; i++)
        fwrite(&a[i], sizeof(persona), 1, fp);
        fclose(fp);
        printf("\n Ordinamento Eseguito[Premere 2 per Stampare]\n");
}

void modifica(FILE *fp)
{
    int i,cont,max;
    int flag;
    max=0;
    i=0;
    cont=0;
    char cognome[50];
    persona p;
    printf("Inserire il cognome da ricercare: \n");
    scanf("%s", &cognome);
    fp = fopen("archivio.dat", "rb");
    while (fread(&p, sizeof(persona), 1, fp) > 0)
    {
        max++;
        if (strcmp(p.cognome, cognome) == 0 && p.tmp==0)
        {
            flag = i;
            printf("%s\n", cognome);
        }
        i++;
    }
    if (flag != -1)
    {
        fseek(fp, flag * sizeof(persona), SEEK_SET);
        printf("nuovo nome da inserire: ");
        scanf("%s", p.nome);
        printf("nuovo cognome da inserire: ");
        scanf("%s", p.cognome);
        printf("nuovo codice da inserire: ");
        scanf("%d", &p.codice);
        printf("nuovo stipendio da inserire: ");
        scanf("%f", &p.stipendio);
        fwrite(&p, sizeof(persona), 1, fp);
        fclose(fp);
    }
    else
    {
        printf("Il cognome inserito non e' stato trovato\n");
        fclose(fp);
    }
}

void cancellazione(FILE *fp)
{
    int i,cont,max;
    int flag = -1;
    max = 0;
    i = 0;
    cont = 0;
    char cognome[50];
    persona p;
    printf("inserire il cognome della persona che si vuole cancellare: ");
    scanf("%s", &cognome);
    fp = fopen("archivio.dat", "r+b");
    while (fread(&p, sizeof(persona), 1, fp) > 0)
    {
        max++;
        if (strcmp(p.cognome, cognome) == 0)
        {
            flag = i;
            printf("%s\n", cognome);
        }
        i++;
    }
    if (flag != -1)
    {
        fseek(fp, flag * sizeof(persona), SEEK_SET);
        p.tmp=1;
        fwrite(&p, sizeof(persona), 1, fp);
        fclose(fp);
    }
    else
    {
        printf("non trovato\n");
        fclose(fp);
    }

}
