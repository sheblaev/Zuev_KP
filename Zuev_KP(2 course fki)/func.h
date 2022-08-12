using namespace std;

void reduce_sum(int p);

class Status
{
        public:
                vector<int> v0;
                vector<int> i;
};

class Args
{
        public:
                vector<int> v;
                int m=0;
                int n=0;
                int p=0;
                int k=0;
                Status *s=nullptr;
};
