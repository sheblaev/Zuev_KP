#include"stdio.h"
#include"stdlib.h"
#include"def.h"
int posstr(char * t, char *w);
int dlina(char *t, int k);
int poisk(char * t, char * w, int n1);
int pospoisk(char * t, char * w, int n1);
char *poisku(char *s, char *w);
char* zamena(char * s, char * hello, char * privet, int n1, int n2);
void delete(int i, char **mas, int n);
int length(const char *s);
char *read_string(FILE *f);
char *strcpy(char *t, const char *s);
int strst(char *t, const char *w, int n);
char *pisk(char *t, char *w, int n, int p);
int dlina(char *t, int k);

void def(FILE *input1, FILE *output, const char *def, const char *und) 
{
	char *hello;
	char *privet;
	char *undef;
	char *s;
	char **mashello = NULL;
	char **masprivet = NULL;
	int n = 0, ind = 0, ind1 = 0, i, j, l1, l2;
	while((s = read_string(input1)) != NULL)
	{
		if(strst(s, def, length(def)) != 0)
		{
			l1 = dlina(s, 0);
			hello = (char*) malloc((l1)*sizeof(char));
			l2 = length(s)-length(def)-l1-3;
			privet = (char*) malloc((l2)*sizeof(char));
			hello = (char*) realloc(hello, l1+1);
			privet = (char*) realloc(privet, l2+1);
			pisk(s, hello, l1, 0);
			pisk(s, privet, l2, l1+length(def)-1);
			for(i = 0; i < n; i++)
			{
				if((poisk(mashello[i], hello, length(hello)) != 0) && (length(mashello[i]) == length(hello)))
				{
					free(masprivet[i]);
					masprivet[i] = malloc(length(privet) + 1);
					for(j = 0; j <= length(privet); j++)
					{
						masprivet[i][j] = privet[j];
					}
					ind = 1;
				}
			}
			if(ind == 0)
			{
				mashello = realloc(mashello, (n + 1)* sizeof(char *));
				masprivet = realloc(masprivet, (n + 1) * sizeof(char *));
				n = n+1;
				mashello[n - 1] = NULL;
				masprivet[n - 1] = NULL;
				mashello[n - 1] = realloc(mashello[n - 1], length(hello) + 1);
				masprivet[n - 1] = realloc(masprivet[n - 1], length(privet) + 1);
				for(i = 0; i <= length(hello); i++)
				{
					mashello[n - 1][i] = hello[i];
				}
				for(i = 0; i <= length(privet); i++)
				{
					masprivet[n - 1][i] = privet[i];
				}
			}
			free(hello);
			free(privet);
		}
		ind = 0;
		if(strst(s, und, length(und)) != 0)
		{
			undef = (char*) malloc((length(s)-length(und)-1)*sizeof(char));
			undef = poisku(s, undef);
			for(j = 0; j < n; j++)
			{
				if((poisk(mashello[j], undef, length(undef)) != 0) && (length(mashello[j]) == length(undef)))
				{
					delete(j, mashello, n); 
					delete(j, masprivet, n);
					n =n-1;
				}
			}
			free(undef);
		}
		if((strst(s, def, length(def)) == 0) && (strst(s, und, length(und)) == 0))
		{
			for(i = 0; i < n; i ++)
			{
				if(poisk(s, mashello[i], length(mashello[i])) != 0)
				{
					s = zamena(s, mashello[i], masprivet[i], length(mashello[i]), length(masprivet[i]));
					ind1 = 1;
				}
			}
			if(ind1 == 1)
			{
				fprintf(output, "%s\n", s);
			}            
			if(ind1 == 0)
			{
				fprintf(output, "%s\n", s);
			}
			ind1 = 0;
		}
		free(s);
	}						
	for(i = 0; i < n; i ++)
	{
		free(mashello[i]);
		free(masprivet[i]);
	}
	free(mashello);
	free(masprivet);
}

int dlina(char *t, int k) //ищет длину hello и privet
{
	int i = k, l = 0, n = 0;
	l = length(t);
	while((t[i] != ' ') && (i <= l))
	{
		i = i+1;
	}
	i = i+1;
	k = i;
	while((t[i] != ' ') && (i < l))
	{
		n = n+1;
		i = i+1;
	}
	return n;	
}

char *pisk(char *t, char *w, int n, int p) //ищет что заменять и на что заменять
{
	int i = p, k = 0, l = 0;
	l = length(t);
	while((t[i] != ' ') && (i <= l))
	{
		i = i+1;
	}
	i = i+1;
	k = i;	
	for(i = k; i < k+n; i++)
	{
		w[i-k] = t[i];
	}
	w[n] = '\0';
	return w;
}

int posstr(char * t, char *w) //ищет позицию слова(любого)
{
	int i, j = 0;
	int p = 0;
	int n1 = 0;
	int l = length(t);
	n1 = length(w);
	for(i = 0; i < l - n1; i++)
	{
		p = 0;
		j = 0;
		while((t[i + j] == w[j]) && (j < n1))
		{
			j = j+1;
			p = p+1;
		}
		if(p == n1)
		{
			return i;
		}
	}
}

char* zamena(char * s, char * hello, char * privet, int n1, int n2) //заменяет
{
	char * news;
	int pos, i, l = 0;
	while(poisk(s, hello, n1) != 0)
	{
		pos = pospoisk(s, hello, n1);
		news = (char*) malloc((pos+n2+1+length(s))*sizeof(char));
		for(i = 0; i < pos; i++)
		{
			news[i] = s[i];
		}
		for(i = 0; i < n2; i ++)
		{
			news[pos + i] = privet[i];
		}
		for(i = pos + n1; i <= length(s); i ++)
		{
			news[n2 - n1 + i] = s[i];
		}
		news[length(news)] = '\0';
		s = realloc(s, length(news) + 1);
		strcpy(s, news);
		free(news);	
	}
	return(s);
}

int poisk(char * t, char * w, int n1) //ищет слово между пробелами
{
	if(length(t) < n1)
		return 0;
	int i, j = 0;
	int p = 0, l = 0;
	l = length(t);
	for(i = 0; i <= l - n1; i++)
	{
		p = 0;
		j = 0;
		while((t[i + j] == w[j]) && (j < n1-1))
		{
			j++;
			p = p + 1;
		}
		if(p == n1-1)
		{
			if(i == 0)
			{
				if(((i + n1) == length(t)))
				{
					return 1;
				}
				if((t[i + n1] == ' '))
				{
					return 1;
				}
				if((t[i + n1 + 1] == '\0'))
				{
					return 1;
				}

			}
			else
			{
				if((t[i - 1] == ' '))
				{
					if(((i + n1) == length(t)))
					{
						return 1;
					}
					if((t[i + n1] == ' '))
					{
						return 1;
					}
					if((t[i + n1 + 1] == '\0'))
					{
						return 1;
					}

				}
			}
		}

	}
	return 0;
}

char *poisku(char *s, char *w) //#undef
{
	int j = 0, i;
	for(i = 7; i < (length(s)-1); i++)
	{
		w[i - 7] = s[i];
		j = j+1;
	}
	w[j] = '\0';
	return w;
}

int pospoisk(char * t, char * w, int n1) //ищет позицию слова между пробелами
{
	int i, j = 0;
	int p = 0, l = 0;
	l = length(t);
	for(i = 0; i <= l - n1; i++)
	{
		p = 0;
		j = 0;
		while((t[i + j] == w[j]) && (j < n1-1))
		{
			j = j+1;
			p = p+1;
		}
		if(p == n1-1)
		{
			if((i == 0) || (t[i - 1] == ' '))
			{
				if((t[i + n1] == ' ') || (t[i + n1 + 1] == '\0'))
				{
					return i;
				}                          
			}
		}

	}
	return 0;


}

void delete(int i, char **mas, int n) //удаляет
{
	int j, k;
	for(j = i; j < n - 1; j++)
	{
		free(mas[j]);
		mas[j] = malloc(length(mas[j+1])+1);
		for(k = 0; k <= length(mas[j+1]); k++)
		{
			mas[j][k] = mas[j + 1][k];
		}
	}
	free(mas[n - 1]);
}

int length(const char *s) 
{
	int n = 0;
	while (s[n] != '\0') 
	{
		n = n+1;
	}	
	return n;
}

char *strcpy(char *t, const char *s) 
{
	int n, i; 
	n = length(s);
	for (i = 0; i < n+1; i++) 
	{
		t[i] = s[i];
	}
	return t;
}

char *read_string(FILE *f) 
{
	int l = 0, l1 = 0;	
	char *result;
	char buf[1024];	
	char *s = fgets(buf, 1024, f);
	if(!s) 
		return NULL;
	else
	{
		l = length(s);
		l1 = 0;
		result = (char*) malloc((l + 1)*sizeof(char));
		while(s)
		{
			strcpy(result+l1, s);
			if(s[length(s)-1] == '\n') 
				break;
			s = fgets(buf, 1024, f);
			if (s) 
			{
				l1 = length(s);
				l = l+l1;
				result = (char*) realloc(result, l+1);
			}
		} 
		return result;
	} 
}

int strst(char * t, const char *w, int n) //ищет подстроку в строке
{
	if(n > length(t))
		return 0;
	int i, j = 0;
	int p = 0, l = 0;
	l = length(t);
	for(i = 0; i < l - n; i++) 
	{
		p = 0;
		j = 0;
		while((t[i + j] == w[j]) && (j < n-1))
		{
			j = j+1;	
			p = p+1;
		}
		if(p+1 == n)
		{
			return 1;
		}
	}
	return 0;	
}

