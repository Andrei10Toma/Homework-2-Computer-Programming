//311CB Toma Andrei
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define NR_MAX 100
#define CATREN 4
#include "util/task_helper.h"

void switch_word(char *sub, char x[], char *s, char *ultim_cuv, char *rez, char *sin)
{
	sub=strstr(s+strlen(x), ultim_cuv);
	strncpy(rez, s, strlen(s)-strlen(sub));
	rez[strlen(s)-strlen(sub)]='\0';
	strcpy(x,strcat(rez, sin));
	strcat(rez, s+strlen(s)-strlen(sub)+strlen(ultim_cuv));
	strcpy(s, rez);
}

void sort_alphabetically(char s[][NR_MAX], int n)
{
	int q, h;
	for (q=0;q<n;q++)
		for (h=0;h<n;h++)
		{
			if (strcmp(s[q],s[h])<0)
			{
				char aux[NR_MAX];aux[0]='\0';
				strcpy(aux, s[q]);
				strcpy(s[q], s[h]);
				strcpy(s[h], aux);
			}
		}
}

void delete_whitespace(char *s)
{
	/*functie pentru stergere a spatiilor in plus*/
	int i, j;
	for (i=0;s[i]!='\0';i++)
	{
		while (isblank(s[i])!=0 && isalpha(s[i+1])==0)
		{
			for (j=i;s[j]!='\0';j++)
			{
				s[j]=s[j+1];
			}
		}
	}
	return;
}

void uppercase(char *s)
{
	int i;
	/*prima litera este transformata in majuscula*/
	if (isupper(s[0])==0)
		s[0]=toupper(s[0]);
	for (i=1;s[i] != '\0';i++)
	{
		/*toate literele sunt transformate in litere mici pana la sfarsitul
		versului, iar dupa aceea se reia procesul la fiecare inceput de vers*/
		s[i]=tolower(s[i]);
		if (s[i]=='\n' && s[i+1]!='\n')
		{
			s[i+1]=toupper(s[i+1]);
			i+=1;
		}
	}
	return;
}

void trimming(char *s)
{
	int i, j;
	delete_whitespace(s);
	for (i=0;s[i]!='\0';i++)
	{
		/*conditie pentru a nu sterge spatiul dintre 2 catrene*/
		if (s[i]=='\n' && s[i-1]=='\n')
			continue;
		if (s[i]=='\n')
		{
			/*transforma toate caracterele nonalfabetice de la sfarsitul 
			versului in spatii*/
			j=i;
			while (!isalpha(s[j-1]))
			{
				s[j-1]=' ';
				j--;
			}
		}
		else
			if (isblank(s[i]))
			{
				/*se elimina spatiile in plus*/
				for (j=i-1;!isalpha(s[j]);j--)
					s[j]=s[i];
			}
	}
	delete_whitespace(s);
	if (!isalpha(s[strlen(s)-1]))
		s[strlen(s)-1]='\0';
}

void silly (char *s, char *prob)
{
	float sample;
	int i;
	for (i=0;s[i]!='\0';i++)
	{
		if (s[i]>=97 && s[i]<=122 || s[i]>=65 && s[i]<=90)/*verifica daca 
		este alfabetic*/
		{
			sample=rand()%100 / 99.0;
			if (sample<atof(prob))
			{
				/*am lucrat cu coduri ASCII ca am vazut dupa pe forum ca ar vrea
				sa vada si lucru cu coduri ASCII*/
				if (s[i]>=97 && s[i]<=122)/*verifica daca litera este mica*/
					s[i]=s[i]-32;/*transformare in majuscula*/
				else if (s[i]>=65 && s[i]<=90)/*verifica daca litera este mare*/
					s[i]=s[i]+32;/*transformare in litera mica*/
			}
		}
	}
	return;
}

void rhimy(char *s, char *rima)
{
	int k=0, n=0, m=0, i, j, q, h;
	char copie_poem[NR_MAX*NR_MAX], cuv[NR_MAX*NR_MAX][NR_MAX];
	char ultim_cuv[NR_MAX][NR_MAX], **sinonim[NR_MAX], v1, v2, v3, v4;
	char *sub, vers[NR_MAX*NR_MAX][NR_MAX], sin[NR_MAX][NR_MAX];
	copie_poem[0]='\0';
	strcpy(copie_poem, s);
	char *p_vers=strtok(copie_poem,"\n"), *delim=" .,\n?!", x[NR_MAX], rez[NR_MAX*NR_MAX];
	x[0]='\0';
	/*creare matrice de versuri*/
	while (p_vers!=NULL)
	{
		strcpy(vers[k], p_vers);
		k++;
		p_vers=strtok(NULL, "\n");
	}
	copie_poem[0]='\0';
	strcpy(copie_poem,s);
	char *p=strtok(copie_poem, delim);
	/*creare matrice de cuvinte*/
	while (p!=NULL)
	{
		strcpy(cuv[m], p);
		m++;
		p=strtok(NULL, delim);
	}
	for (i=0;i<k;i++)	
	{
		/*extragerea ultimului cuvant din fiecare vers*/
		char *ulti=strrchr(vers[i],' ');
		strcpy(ultim_cuv[i], ulti+1);
		int contor=0;
		while (!isalpha(ultim_cuv[i][strlen(ultim_cuv[i])-contor]))
			contor++;
		ultim_cuv[i][strlen(ultim_cuv[i])-contor+1]='\0';
	}
	for (i=0;i<k;i+=CATREN)
	{
		/*extragerea ultimei litere din fiecare vers din catren*/
		v1=ultim_cuv[i][strlen(ultim_cuv[i])-1];
		v2=ultim_cuv[i+1][strlen(ultim_cuv[i+1])-1];
		v3=ultim_cuv[i+2][strlen(ultim_cuv[i+2])-1];
		v4=ultim_cuv[i+3][strlen(ultim_cuv[i+3])-1];
		/*dupa aceea se verifica fiecare tip de rima si se inlocuieste cu 
		sinonimul care rimeaza, in cazul in care nu rimeaza*/
	if (strncmp(rima, "imperecheata", strlen("imperecheata"))==0)
	{	
		if (tolower(v1) != tolower(v2))
		{

			get_synonym(ultim_cuv[i], &n, sinonim);
			if (*sinonim!=NULL)
			{
				for (q=0;q<n;q++)
					strcpy(sin[q], *(*sinonim+q));
				sort_alphabetically(sin, n);
				for (q=0;q<n;q++)
					if (tolower(sin[q][strlen(sin[q])-1])==tolower(v2))
					{
						switch_word(sub, x, s, ultim_cuv[i], rez, sin[q]);
						break;
					}
			}
			else
			{
				x[0]='\0';
				get_synonym(ultim_cuv[i+1], &n, sinonim);
				if (*sinonim!=NULL)
				{
				for (q=0;q<n;q++)
					strcpy(sin[q], *(*sinonim+q));
				sort_alphabetically(sin, n);
				for (q=0;q<n;q++)
					if (tolower(sin[q][strlen(sin[q])-1])==tolower(v1))
					{
						switch_word(sub, x, s, ultim_cuv[i+1], rez, sin[q]);
						break;
					}
				}
			}
		}
		if (tolower(v3)!=tolower(v4))
		{	
			x[0]='\0';
			get_synonym(ultim_cuv[i+2], &n, sinonim);
			if (*sinonim!=NULL)
			{
				for (q=0;q<n;q++)
					strcpy(sin[q], *(*sinonim+q));
				sort_alphabetically(sin, n);
				for (q=0;q<n;q++)
					if (tolower(sin[q][strlen(sin[q])-1])==tolower(v4))
					{
						switch_word(sub, x, s, ultim_cuv[i+2], rez, sin[q]);
						break;
					}
			}
			else
			{
				x[0]='\0';
				get_synonym(ultim_cuv[i+3], &n, sinonim);
				if (*sinonim!=NULL)
				{
				for (q=0;q<n;q++)
					strcpy(sin[q], *(*sinonim+q));
				sort_alphabetically(sin, n);
				for (q=0;q<n;q++)
					if (tolower(sin[q][strlen(sin[q])-1])==tolower(v3))
					{
						switch_word(sub, x, s, ultim_cuv[i+3], rez, sin[q]);
						break;
					}
				}
			}
		}
	}
	if (strncmp(rima, "incrucisata", strlen("incrucisata"))==0)
	{	
		if (tolower(v1) != tolower(v3))
		{	
			get_synonym(ultim_cuv[i], &n, sinonim);
			if (*sinonim!=NULL)
			{
				for (q=0;q<n;q++)
					strcpy(sin[q], *(*sinonim+q));
				sort_alphabetically(sin, n);
				for (q=0;q<n;q++)
					if (tolower(sin[q][strlen(sin[q])-1])==tolower(v3))
					{
						switch_word(sub, x, s, ultim_cuv[i], rez, sin[q]);
						break;
					}
			}
			else
			{
				x[0]='\0';
				get_synonym(ultim_cuv[i+2], &n, sinonim);
				if (*sinonim!=NULL)
				{
				for (q=0;q<n;q++)
					strcpy(sin[q], *(*sinonim+q));
				sort_alphabetically(sin, n);
				for (q=0;q<n;q++)
					if (tolower(sin[q][strlen(sin[q])-1])==tolower(v1))
					{
						switch_word(sub, x, s, ultim_cuv[i+2], rez, sin[q]);
						break;
					}
				}
			}
		}
		if (tolower(v2)!=tolower(v4))
		{	
			x[0]='\0';
			get_synonym(ultim_cuv[i+1], &n, sinonim);
			if (*sinonim!=NULL)
			{
				for (q=0;q<n;q++)
					strcpy(sin[q], *(*sinonim+q));
				sort_alphabetically(sin, n);
				for (q=0;q<n;q++)
					if (tolower(sin[q][strlen(sin[q])-1])==tolower(v4))
					{
						switch_word(sub, x, s, ultim_cuv[i+1], rez, sin[q]);
						break;
					}
			}
			else
			{
				x[0]='\0';
				get_synonym(ultim_cuv[i+3], &n, sinonim);
				if (*sinonim!=NULL)
				{
				for (q=0;q<n;q++)
					strcpy(sin[q], *(*sinonim+q));
				sort_alphabetically(sin, n);
				for (q=0;q<n;q++)
					if (tolower(sin[q][strlen(sin[q])-1])==tolower(v2))
					{
						switch_word(sub, x, s, ultim_cuv[i+3], rez, sin[q]);
						break;
					}
				}
			}
		}
	}
	if (strncmp(rima, "imbratisata", strlen("imbratisata"))==0)
	{	
		if (tolower(v1) != tolower(v4))
		{	
			get_synonym(ultim_cuv[i], &n, sinonim);
			if (*sinonim!=NULL)
			{
				for (q=0;q<n;q++)
					strcpy(sin[q], *(*sinonim+q));
				sort_alphabetically(sin, n);
				for (q=0;q<n;q++)
					if (tolower(sin[q][strlen(sin[q])-1])==tolower(v4))
					{
						switch_word(sub, x, s, ultim_cuv[i], rez, sin[q]);
						break;
					}
			}
			else
			{
				x[0]='\0';
				get_synonym(ultim_cuv[i+3], &n, sinonim);
				if (*sinonim!=NULL)
				{
				for (q=0;q<n;q++)
					strcpy(sin[q], *(*sinonim+q));
				sort_alphabetically(sin, n);
				for (q=0;q<n;q++)
					if (tolower(sin[q][strlen(sin[q])-1])==tolower(v1))
					{
						switch_word(sub, x, s, ultim_cuv[i+3], rez, sin[q]);
						break;
					}
				}
			}
		}
		if (tolower(v2)!=tolower(v3))
		{	
			x[0]='\0';
			get_synonym(ultim_cuv[i+1], &n, sinonim);
			if (*sinonim!=NULL)
			{
				for (q=0;q<n;q++)
					strcpy(sin[q], *(*sinonim+q));
				sort_alphabetically(sin, n);
				for (q=0;q<n;q++)
					if (tolower(sin[q][strlen(sin[q])-1])==tolower(v3))
					{
						switch_word(sub, x, s, ultim_cuv[i+1], rez, sin[q]);
						break;
					}
			}
			else
			{
				x[0]='\0';
				get_synonym(ultim_cuv[i+2], &n, sinonim);
				if (*sinonim!=NULL)
				{
					for (q=0;q<n;q++)
						strcpy(sin[q], *(*sinonim+q));
					sort_alphabetically(sin, n);
					for (q=0;q<n;q++)
						if (tolower(sin[q][strlen(sin[q])-1])==tolower(v2))
						{
							switch_word(sub, x, s, ultim_cuv[i+2], rez, sin[q]);
							break;
						}
				}
			}
		}
	}
	}
	return;
}


void friendly(char *s)
{
	int i, n=0, contor=0, m=0, 	j;
	char aux[NR_MAX*NR_MAX], vers[NR_MAX][NR_MAX], x[NR_MAX];aux[0]='\0';
	char copie_poem[NR_MAX*NR_MAX], cuv[NR_MAX*NR_MAX][NR_MAX], copie[NR_MAX*NR_MAX];
	copie_poem[0]='\0';
	strcpy(copie_poem, s);
	char *delim=".,!?- \n", *friendly[NR_MAX];
	char *p_vers=strtok(copie_poem, "\n");
	/*creare matrice de versuri*/
	while(p_vers!=NULL)
	{
		strcpy(vers[m], p_vers);
		m++;
		p_vers=strtok(NULL, "\n");
	}
	copie_poem[0]='\0';
	strcpy(copie_poem, s);
	char *p=strtok(copie_poem, delim);
	/*creare matrice de cuvinte*/
	while (p!=NULL)
	{
		strcpy(cuv[n], p);
		n++;
		p=strtok(NULL, delim);
	}
	for (i=0;i<n;i++)
	{
		/*obtinerea diminutivelor*/
		get_friendly_word(cuv[i], friendly);
		if (*friendly!=NULL)
		{
			for (j=0;j<m;j++)
			{
				char *sub=NULL;
				char copie_vers[NR_MAX];
				copie_vers[0]='\0';
				sub=strstr(vers[j], cuv[i]);
				if (sub!=NULL)
				{
					/*se modifica matricea de versuri inlocuindu-se fiecare
					cuvant care are diminutiv cu diminutivul sau*/
					if (!isalpha(vers[j][strlen(vers[j])-strlen(sub)
						+strlen(cuv[i])]))
					{
						strncpy(copie_vers, vers[j], strlen(vers[j])-strlen(sub));
						copie_vers[strlen(vers[j])-strlen(sub)]='\0';
						strcat(copie_vers, *friendly);
						strcat(copie_vers, vers[j]+strlen(vers[j])-strlen(sub)+
							strlen(cuv[i]));
						strcpy(vers[j], copie_vers);	
					}
				}
			}
		}
	}
	/*crearea unei variabile auxiliare in care este retinut poemul modificat*/
	for (j=0;j<CATREN;j++)
	{
		strcat(aux, vers[j]);
		strcat(aux, "\n");
	}
	for (j=CATREN;j<m;j++)
	{
		if (j%4!=0)
		{
			strcat(aux, vers[j]);
			strcat(aux, "\n");
		}
		else
		{
			strcat(aux,"\n");
			strcat(aux, vers[j]);
			strcat(aux, "\n");
		}
	}
	aux[strlen(aux)-1]='\0';
	strcpy(s, aux);
	return;
}

void print(char *s)
{
	printf("%s\n", s);
	printf("\n");
	return;
}

int main(void)
{
	srand(42);
	char req[NR_MAX], poem[NR_MAX*NR_MAX];
	int i;
	/*crearea consolei virtuale*/
	while (strncmp(req, "quit", strlen("quit"))!=0)
	{
		fgets (req, NR_MAX, stdin);
		if (strncmp(req, "load", strlen("load"))==0)
		{
			/*retinerea caii in care se afla poemul*/
			char *path=strchr(req,' ');
			for (i=0;i<strlen(path);i++)
				*(path+i)=*(path+i+1);
			path[strlen(path)-1]='\0';
			load_file(path, poem);
		}
		if (strncmp(req, "print", strlen("print"))==0)
		{
			print(poem); 
		}
		if (strncmp(req, "uppercase", strlen("uppercase"))==0)
		{
			uppercase(poem);
		}
		if (strncmp(req, "trimming", strlen("trimming"))==0)
		{ 
			trimming(poem);
		}
		if (strncmp(req, "make_it_silly", strlen("make_it_silly"))==0)
		{
			/*retinerea probabilitatii*/
			char *prob=strchr(req,' ');
			for (i=0;i<strlen(prob);i++)
				*(prob+i)=*(prob+i+1);
			prob[strlen(prob)-1]='\0';
			silly(poem,prob);
		}
		if (strncmp(req, "make_it_friendlier", strlen("make_it_friendlier"))==0)
		{
			friendly(poem);
		}
		if (strncmp(req, "make_it_rhyme", strlen("make_it_rhyme"))==0)
		{
			/*retinerea rimei*/
			char *rima=strchr(req,' ');
			for (i=0;i<strlen(rima);i++)
				*(rima+i)=*(rima+i+1);
			rima[strlen(rima)-1]='\0';
			rhimy(poem, rima);	
		}

	}
	return 0;
}