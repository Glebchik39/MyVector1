#include <iostream>
#include <time.h>
using namespace std;

class MyVector
{
	int* arr;
	int size;
	friend ostream& operator << (ostream& os, MyVector& obj);
	friend istream& operator>>(istream& os, MyVector& obj);

public:

	/*friend void Test(MyVector& obj);*/

	MyVector() :arr(nullptr), size(0) {}
	MyVector(int s) :size(s) {
		arr = new int[size];
	}


	void Init()
	{
		for (int i = 0; i < size; i++)
		{
			arr[i] = rand() % 50;
		}
	}

	void Print()
	{
		for (size_t i = 0; i < size; i++)
		{
			cout << arr[i] << "\t";
		}
		cout << endl;
	}

	~MyVector()
	{
		delete[]arr;
		size = 0;
	}

	int GetSize()const
	{
		return size;
	}

	void SetSize(int s)
	{
		size = s;
	}

	int operator[](int index)
	{
		if (index >= 0 && index < size)
		{
			return arr[index];
		}
		return -1;
	}

	void SetArr(int e) {
		*arr = e;
	}

	int GetArr()
	{
		return *arr;
	}


	MyVector operator++(int) // obj++
	{
		cout << "obj++\n";
		MyVector temp = *this;
		int* Newarr = new int[size + 1];
		for (size_t i = 0; i < size; i++) {
			Newarr[i] = arr[i];
		}
		Newarr[size] = 0;
		delete[] arr;
		arr = Newarr;
		size++;
		return temp;
	}


	MyVector operator--(int) { // obj--
		cout << "obj--\n";
		MyVector temp = *this;
		int* Newarr = new int[size - 1];
		for (size_t i = 0; i < size - 1; i++) {
			Newarr[i] = arr[i];
		}
		delete[] arr;
		arr = Newarr;
		size--;
		return temp;
	}





	// копирование конструктор, перенос, = с копированием, obj++(добавляет 1 элемент в конец , значение = 0), -- удаляет последний элемент массива

	MyVector(const MyVector& obj2) // конструктор копирования
	{
		size = obj2.size;
		arr = new int[size];
		for (int i = 0; i < size; i++)
		{
			arr[i] = obj2.arr[i];
		}
		cout << "Copy constructor\n";
	}

	MyVector(MyVector&& obj) // конструктор переноса;
	{
		arr = obj.arr;
		obj.arr = nullptr;
		obj.size = 0;
		cout << "Move Constructor\n";
	}

	void operator()() // operator()
	{
		for (size_t i = 0; i < size; i++)
		{
			cout << arr[i] << " ";
		}
		cout << "Operator() " << endl;
	}

	MyVector& operator+=(int number) // operator +=
	{
		cout << "operator+=\n";
		int* newArr = new int[size + number];
		for (size_t i = 0; i < size; i++) {
			newArr[i] = arr[i];
		}
		for (size_t i = 0; i < number; i++)
		{
			newArr[size + i] = rand() % 50;
		}
		delete[] arr;
		arr = newArr;
		size += number;
		return *this;
	}

	MyVector& operator-=(int number) // operator -=
	{

		cout << "operator-=\n";
		int* newArr = new int[size - number];
		for (size_t i = 0; i < size - number; i++) {
			newArr[i] = arr[i];
			cout << arr[i] << " ";
		}
		delete[] arr;
		arr = newArr;
		size -= number;
		return *this;

	}



	MyVector& operator*=(int number) { // operator *=
		cout << "operator*=\n";
		for (size_t i = 0; i < size; i++)
		{
			arr[i] *= number;
			cout << arr[i] << " ";
		}
		return *this;
	}

	operator int() { // перегрузка типов
		return size;
	}

	MyVector& operator= (MyVector& obj2)
	{
		cout << "operator = \n";
		if (this == &obj2)
		{
			return *this;
		}

		if (arr != nullptr)
		{
			delete[]arr;
		}

		size = obj2.size;

		arr = new int[size + 1];
		for (int i = 0; i < size; i++)
		{
			arr[i] = obj2.arr[i];
		}


		return *this;
	}




};

//void Test(MyVector& obj)
//{
//	for (size_t i = 0; i < obj.size; i++)
//	{
//
//	}
//}


 ostream& operator<<(ostream& os, MyVector& obj) //operator << 
 {
	 os << "Peregruzka <<\n";
	 for (size_t i = 0; i < obj.size; i++)
	 {
		 os << obj.arr[i] << " ";
	 }
	 return os;
 }


 istream& operator>>(istream& is, MyVector& obj) // operator >>
 {
	 int a;
	 for (size_t i = 0; i < obj.size; i++)
	 {
		 is >> a;
		 obj.arr[i] = a;
	 }
	 return is;
 }




MyVector operator+(int c, MyVector& b) // + 5 function
{
	int result;
	for (size_t i = 0; i < b.GetSize(); i++)
	{
		result = b[i] + c;
		cout << result << " ";
	}
	cout << "+ 5 k znaheniu" << endl;
	return result;
}


MyVector operator--(MyVector& obj)
{
	cout << "peregruzka -- cherez function" << endl;
	MyVector result(obj.GetSize() - 1);
	for (size_t i = 0; i < obj.GetSize() - 1; i++)
	{
		cout << obj[i] << "\t";
	}
	return result;
}

int main()
{
	srand(unsigned(time(0)));

	MyVector vec1(5);
	vec1.Init();
	vec1.Print();

	//for (size_t i = 0; i < vec1.GetSize(); i++)
	//{
	//	cout << vec1[i] << "\t";
	//}
	//cout << endl;



	int size = vec1; // 1.+
	cout << "Size = " << size << endl;

	vec1();//2.+

	MyVector vec10(10);
	vec10.Init();
	vec10+=5; // operatro +=
	vec10.Print();

	cout << "\n";

	cout << vec10;// peregruzka <<
	
	cout << "\n\n";

	cin >> vec10; // operator >>

	cout << "\n\n";

	MyVector vec15 = 5 + vec10;
	cout << "\n";// + 5 

	MyVector vec21 = --vec10; // function operator --obj

	cout << "\n";

	 vec10 -= 2;// operator -=

	cout << "\n";

	vec10 *= 5; // operator *=
	
	cout << "\n";

	MyVector vec2 = vec1;
	vec2.Print();

	MyVector vec3(3);
	vec3 = vec1;
	vec3.Print();

	MyVector vec5 = vec1++;
	vec1.Print();


	MyVector vec6 = vec1--;
	vec1.Print();


	MyVector vec4 = move(vec1);



}


