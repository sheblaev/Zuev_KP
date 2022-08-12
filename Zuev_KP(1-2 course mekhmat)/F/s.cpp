#include <iostream>
#include <string>

using namespace std;

template <typename T>
struct Stackitem
{
	T item;
	Stackitem* next;
};

class StackLError
{ 
	private: 
		int code_;
		std::string reason_;
	public:
		StackLError(int code, const std::string& reason)
		{
			code_ = code;
			reason_ = reason;
		}

		const std::string& get_reason() const 
		{ 
			return reason_; 
		}
};

template <typename T>
class StackL
{
	private:
		Stackitem<T>* vershina;
	public:
		class Iterator
		{
			private:
				friend class StackL<T>;
				Stackitem<T>* current_;
			public:
				Iterator()
				{
					current_ = nullptr;
				}

				Iterator& operator=(const Iterator & right)
				{
					current_ = right.current_;
					return *this;
				}

				friend bool operator!=(const Iterator & lev, const Iterator& prav)
				{
					if(lev.current_ != prav.current_)
						return true;
					else
						return false;
				}

				void next1()
				{
					current_ = current_->next;
				}

				friend T & operator*(const Iterator & i)
				{
					return i.current_->item;
				}
		};

		Iterator begin()
		{
			Iterator i;
			i.current_ = vershina;
			return i;
		}

		Iterator end()
		{
			Iterator i;
			i.current_ = nullptr;
			return i;
		}

		StackL() 
		{ 
			vershina = nullptr; 
		}

		StackL(const StackL& S)
		{
			Stackitem<T>* p;
			Stackitem<T>* p1;
			Stackitem<T>* t;
			vershina = nullptr;
			t = nullptr;
			p = S.vershina;
			while (p != nullptr)
			{
				p1 = new Stackitem<T>;
				p1->item = p->item;
				p1->next = nullptr;
				if (vershina == nullptr)
				{
					vershina = p1;
					t = p1;
				}
				else
				{
					t->next = p1;
					t = t->next;
				}
				p = p->next;
			}
		}

		~StackL()
		{
			Empty();
		}

		void Put(T i)// добавить
		{
			Stackitem<T>* p;
			p = new Stackitem<T>;
			p->item = i;
			p->next = vershina;
			vershina = p;
		}

		void Empty()
		{
			Stackitem<T>* p;
			Stackitem<T>* p1;

			p = vershina;

			while (p != nullptr)
			{
				p1 = p;
				p = p->next;
				delete p1;
			}
			vershina = nullptr;
		}

		void Print()// вывод
		{
			if (vershina == nullptr)
			{
				throw StackLError(-1, std::string("empty"));
			}
			else
			{
				Stackitem<T>* p;
				p = vershina;
				while (p != nullptr)
				{
					cout << p->item << "\t";
					p = p->next;
				}
				cout << endl;
			}
		}

		void Del()// вынуть вершину стека
		{
			if (vershina == nullptr)
			{
				throw StackLError(-5, std::string("empty"));
			}
			Stackitem<T>* p;
			T item;
			item = vershina->item;
			p = vershina;
			vershina = vershina->next;
			delete p;
		}

		StackL<T>& operator=(const StackL<T>& right)// копирование
		{
			Stackitem<T>* p;
			Stackitem<T>* p1;
			Stackitem<T>* t;
			Empty();
			vershina = nullptr;
			t = nullptr;
			p = right.vershina;
			while (p != nullptr)
			{
				p1 = new Stackitem<T>;
				p1->item = p->item;
				p1->next = nullptr;
				if (vershina == nullptr)
				{
					vershina = p1;
					t = p1;
				}
				else
				{
					t->next = p1;
					t = t->next;
				}
				p = p->next;
			}
			return *this;
		}

		int dlina(StackL<T>& S)
		{
			StackL<T>::Iterator i;
			StackL<T>::Iterator r;
			int l = 0;
			r = S.end();
			for(i = S.begin(); i != r; i.next1())
			{
				l = l+1;
			}
			return l;
		}

		friend std::ostream& operator<< (std::ostream &out, const StackL<T>& S)
		{	
			if (S.vershina == nullptr)
			{
				throw StackLError(-6, std::string("empty"));
			}
			Stackitem<T>* p;
			p = S.vershina;
			while (p != nullptr)
			{
				cout << p->item << "\t";
				p = p->next;
			}
			cout << endl;
			return out;
		}
};
