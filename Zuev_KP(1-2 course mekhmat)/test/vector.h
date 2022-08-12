#include <iostream>
#include <string>

class VectorError
{ 
	private: 
		int code_;
		std::string reason_;
	public:
		VectorError(int code, const std::string& reason)
		{
			code_ = code;
			reason_ = reason;
		}

		const std::string& get_reason() const 
		{ 
			return reason_; 
		}
};

class Vector 
{ 
	private: 
		int *elements_;
		int n_; 
		int k_;
	public: 
		Vector (int n, int k); 
		~Vector();
		void loc();
		void rec(const Vector& prav);
		friend bool operator<= (const Vector& lev, const Vector& prav);
		Vector & operator=(const Vector & right);
		friend std::ostream& operator<<(std::ostream &os, const Vector& q);
};
