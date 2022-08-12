#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int n;
static int *a;	
static char **b;

int filesize(const char* file_name);
void sort(int *a, char **b, int n);
char *strcpy(char *t, const char *s);
int length(const char *s);

	/*
	Параметры:
	int argc: количество аргументов командной строки.
	char *argv[]: массив аргументов командной строки.
	  
	argc = 2:
	имя исполяемого файла.
	имя директории, в которой будет происходить поиск.

	Если количество аргументов командной строки не равно 2, то программа не заработает.

	В результате работы программы будет напечатан упорядоченный по размеру список всех файлов(путь до этого файла) и их размер.
	Если в результате работы программы ничего не будет напечатано, то это означает, что файлов в указанном каталоге нет.

	Метод:
	для обхода дерева файлов, используется функция ftw из библиотеки <ftw.h>.
	*/

	/*
	callback function: poisk - функция, вызымаемая для каждого элемента дерева файлов.

	Параметры:
	const char *file: полное имя элемента.
	const struct stat *sb:  указатель на структуру элемента stat(2).
	int flag: целое число, которое показывает тип file. 

	Метод:
	Сначала функция poisk считает размер файла и записывает его в массив A, потом она пишет в массив B название этого файла. 		Потом функция sort сортирует массивы A и B по размеру файла.
	*/

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

void sort(int *a, char **b, int n)
{
	int i, k, s;
	for(i = 1; i < n; i ++)
	{
		for(k = 1; k < n; k ++)
		{
			if(a[k] < a[k-1])
			{
				char *str = NULL;
				s = a[k];
				a[k] = a[k-1];
				a[k-1] = s;
				str = realloc(str, length(b[k]) + 1);
				str = strcpy(str, b[k]);
				b[k] = realloc(b[k], length(b[k-1]) + 1);
				b[k] = strcpy(b[k], b[k-1]);
				b[k-1] = realloc(b[k-1], length(str) + 1);
				b[k-1] = strcpy(b[k-1], str);
				free(str);
			}
		}
	}
}

int filesize(const char* file_name)
{
	int size = 0;
	FILE* f = fopen(file_name, "rb"); //"rb" открывает двоичный файл для чтения
	if(f == NULL)
	{
		size = -1;
	}
	else
{
		while(getc(f) != EOF)
			size++;
		fclose(f);
	}
	return size;
}

static int poisk(const char *file, const struct stat *sb, int flag) 
{
	int i;
	int size;
	if (flag == FTW_F) 
	{
			size = filesize(file);
			n = n+1;
			a = realloc(a, (n)* sizeof(int *));
			b = realloc(b, (n)* sizeof(char *));
			b[n - 1] = NULL;
			b[n - 1] = realloc(b[n - 1], length(file) + 1);
			strcpy(b[n-1], file); 
			a[n-1] = size;
	}
	return 0;         
}

int main(int argc, char *argv[]) 
{
	int i;
	n = 0;
	a = (int*) malloc(0 * sizeof(int));
	b = malloc(0* sizeof(char));
	if (argc == 1 || argc >= 3) 
	{
        return 0;
    	}
	if (argc == 2) 
	{
		ftw(argv[1], poisk, 50);
	} 
	sort(a, b, n);
	for (i = 0; i<n; i++)
	{
		printf("%d\n", a[i]);
		printf("%s\n", b[i]);
	}
	for (i = 0; i<n; i++)
	{
		free(b[i]);
	}
	free(a);
	free(b);
	return 0;
}

