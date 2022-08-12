double func(int s, int n, int i, int j);
double modul(double x);
void vvod(double *mas, int s, int n, char *a);
double *gauss(int n, int m, int s1, int p, double *mas, double *b, double *x, char *filename, int r, double *mas5, double *b5);

class Args
{
        public:
                double *mas=nullptr;
                double *stroka=nullptr;
                int *nomer=nullptr;
                double *b=nullptr;
                double *x=nullptr;
                int n=0;
                int m=0;
                int k=0;
                int p=0;
                int q=0;
                double min = 0;
                int otvet=0;
                int s1 = 0;
                char *filename = 0;
                int r = 0;
                double *mas5=nullptr;
                double *b5=nullptr;
                int error = 0;
};
