void reduce_sum(int p);
void reduce(int p, double *a);

class Status
{
        public:
                double *second0=nullptr;
                double *first1=nullptr;
                double *element0=nullptr;
                double *element1=nullptr;
};

class Args
{
        public:
                double *mas=nullptr;
                int m=0;
                int n1=0;
                int n2=0;
                int p=0;
                int sm=0;
                int em=0;
                double res=0;
                Status *s=nullptr;
};
