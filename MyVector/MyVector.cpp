#include <iostream>
#include <time.h>
using namespace std;

class MyVector
{
	int* arr;
	int size;

public:
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

	int operator[](int index)
	{
		if (index >= 0 && index < size)
		{
			return arr[index];
		}
		return -1;
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


	MyVector& operator = (MyVector& obj2)
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


		arr = new int[size + 1];
		for (int i = 0; i < size; i++)
		{
			arr[i] = obj2.arr[i];
		}
		size = obj2.size;


		return *this;
	}


};

int main()
{
	srand(unsigned(time(0)));

	MyVector vec1(5);
	vec1.Init();
	vec1.Print();

	/*for (size_t i = 0; i < vec1.GetSize(); i++)
	{
		cout << vec1[i] << "\t";
	}
	cout << endl;*/


	MyVector vec2 = vec1;
	vec2.Print();

	MyVector vec3(5);
	vec3 = vec1;
	vec3.Print();

	MyVector vec5 = vec1++;
	vec1.Print();


	MyVector vec6 = vec1--;
	vec1.Print();


	MyVector vec4 = move(vec1);

}

