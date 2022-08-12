void reduce_sum(int p, double *a, int n);
void reduce(int p, int *a, double *b);

class Status
{
        public:
        	int length=0;
                double second0=0;
                double first1=0;
                double element0=0;
                double element1=0;
};

class Args
{
        public:
                double *mas=nullptr;
                int m=0;
                int n=0;
                int p=0;
                int sm=0;
                int em=0;
                int res0=0;
                double res=0;
                Status *s=nullptr;
};
