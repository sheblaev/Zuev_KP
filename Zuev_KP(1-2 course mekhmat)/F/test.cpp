#include <iostream>
#include "s.cpp"

using namespace std;

int main()
{
        try
        {
                StackL<int> S;
                S.Put(8);
                S.Put(5);
                S.Put(10);
                S.Put(7);
                cout << "S"<< endl;
                S.Print();

                StackL<int> S1;
                S1.Put(1);
                S1.Put(2);
                S1.Put(3);
                cout << "S1"<< endl;
                S1.Print();

                StackL<int> S5;
                S5 = S;
                cout << "S5"<< endl;
                S5.Print();

                S.Del();
                cout << "S"<< endl;
                S.Print();

                S.Put(1);
                S.Put(4);
                S.Put(6);
                S.Put(9);
                S.Put(15);
                S.Put(19);
                cout << "S"<< endl;
                S.Print();

                StackL<int>::Iterator i;
                StackL<int>::Iterator i1;
                StackL<int>::Iterator i5;
                StackL<int>::Iterator r;
                int l;
                int k;
                int p;
                int t;
                int m;
		l = S.dlina(S);
                m = l;
                r = S.end();
                for(i = S.begin(); i != r; i.next1())
                {
                        if ((l == m/2) || (l == (m+1)/2))
                                break;
                        p = 0;
                        i1 = S.begin();
                        for(k = 1; k != l; ++k)
                        {
                                i1.next1();
                        }
                        p = *i;
                        *i = *i1;
                        i5 = i;
                        i = S.begin();
                        for(t = 1; t != l; ++t)
                        {
                                i.next1();
                        }
                        *i = p;
                        i = i5;
                        l = l-1;
                }
                cout << "S"<< endl;

                S.Print();

                StackL<StackL<int>> E;
                E.Put(S);
                E.Put(S1);
                E.Put(S5);
                cout << "E"<< endl;
                std::cout << "\t" << E << endl;

                StackL<int> L;
                cout << "L"<< endl;
                L.Print();
        }
        catch(StackLError &err)
        {
                std::cout << err.get_reason() << std::endl;
        }
        return 0;
}

