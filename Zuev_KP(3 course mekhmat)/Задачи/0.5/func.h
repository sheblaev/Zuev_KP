void reduce_sum(int p, int *a, double *b);

class Status
{
        public:
        	int length=0;
                double first0=0;
                double second0=0;
                double first1=0;
                double second1=0;
};

class Args
{
        public:
                char *f=nullptr;
                int c=0;
                int m=0;
                int p=0;
                int res0=0;
                double res=0;
                int res1=0;
                Status *s=nullptr;
};
