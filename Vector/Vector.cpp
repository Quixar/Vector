#include <iostream>
#include <ctime>
using namespace std;

class ArrayList // Vector
{
	unsigned int size = 0; // количество действительно присутствующих элементов в контейнере
	unsigned int capacity = 10; // ёмкость (вместительность, запас памяти)
	int* data = nullptr; // указатель на динамический массив целых чисел

public:
	ArrayList() : ArrayList(10)
	{
		// cout << "C-TOR WITHOUT PARAMS!\n";
	}

	ArrayList(unsigned int capacity)
	{
		if (capacity < 10)
		{
			capacity = 10;
		}
		this->capacity = capacity;
		data = new int[capacity];
		// cout << "C-TOR WITH PARAMS!\n";
	}

	ArrayList(const ArrayList& original)
	{
		//cout << "COPY C-TOR!\n";
		this->size = original.size;
		this->capacity = original.capacity;
		this->data = new int[original.capacity];

		for (int i = 0; i < original.size; i++)
		{
			this->data[i] = original.data[i];
		}
	}

	~ArrayList()
	{
		// cout << "DESTRUCTOR!\n";
		if (data != nullptr)
		{
			delete[] data;
			data = nullptr;
		}
	}

	void SetCapacity(unsigned int capacity)
	{
		this->capacity = capacity;
	}

	unsigned int GetCapacity() const
	{
		return capacity;
	}

	unsigned int GetSize() const
	{
		return size;
	}

	void EnsureCapacity()
	{
		if (size < capacity) return;

		int* temp = new int[size * 2];
		for (int i = 0; i < size; i++)
		{
			temp[i] = data[i];
		}

		delete[] data;
		data = temp;

		capacity *= 2;
	}

	void PushBack(int value)
	{
		EnsureCapacity(); // проверка, хватит ли места для нового элемента
		data[size] = value;
		size++;
	}

	void Insert(int index, int value)
	{
		if (index < 0 || index > size)
		{
			throw("Out of range");

		}

		EnsureCapacity();
		for (int i = size - 1; i >= index; i--)
		{
			data[i + 1] = data[i];
		}
		data[index] = value;
		size++;
	}


	void PushFront(int value)
	{
		EnsureCapacity();
		for (int i = size; i > 0; i--) // i = 1
		{
			data[i] = data[i - 1]; // data[1] = data[0]
		}
		data[0] = value;
		size++;
	}

	void RemoveAt(int index)
	{
		if (index < 0 || index > size)
		{
			throw("Out of range");

		}

		EnsureCapacity();
		for (int i = index; i < size; i++)
		{
			data[i] = data[i + 1];
		}
		size--;
	}

	void PopFront()
	{
		EnsureCapacity();
		for (int i = 0; i < size; i++)
		{
			data[i] = data[i + 1];
		}
		size--;
	}

	int IndexOf(int value)
	{
		for (int i = 0; i < size; i++)
		{
			if (data[i] == value)
			{
				cout << "Index of value = " << i << "\n";
				return i;
			}
		}
		cout << "Value not found\n";
		return -1;
	}

	int LastIndexOf(int value)
	{
		for (int i = size; i > 0; i--)
		{
			if (data[i] == value)
			{
				cout << "Index of value = " << i << "\n";
				return i;
			}
		}
		cout << "Value not found\n";
		return -1;
	}

	void Reverse()
	{
		for (int i = 0, j = size -1; i < j; i++, j--)
		{
			swap(data[i], data[j]);
		}
	}

	void PopBack()
	{
		size--;
	}

	int Partition(int start, int end)
	{

		int pivot = data[start];

		int count = 0;
		for (int i = start + 1; i <= end; i++) {
			if (data[i] <= pivot)
				count++;
		}

		int pivotIndex = start + count;
		swap(data[pivotIndex], data[start]);

		int i = start, j = end;

		while (i < pivotIndex && j > pivotIndex) {

			while (data[i] <= pivot) {
				i++;
			}

			while (data[j] > pivot) {
				j--;
			}

			if (i < pivotIndex && j > pivotIndex) {
				swap(data[i++], data[j--]);
			}
		}

		return pivotIndex;
	}

	void QuickSort(int start, int end)
	{
		if (start >= end)
			return;

		int p = Partition(start, end);

		QuickSort(start, p - 1);

		QuickSort( p + 1, end);
	}

	void SortAsc()
	{
		QuickSort(0, size - 1);
	}

	int ReversePartition(int start, int end)
	{
		int pivot = data[end];
		int i = start - 1;

		for (int j = start; j <= end - 1; j++) 
		{
			if (data[j] >= pivot)
			{
				i++;
				swap(data[i], data[j]);
			}
		}
		swap(data[i + 1], data[end]);
		return i + 1;
	}

	void ReverseQuickSort(int start, int end)
	{
		if (start < end) {
			int p = ReversePartition(start, end);
			ReverseQuickSort(start, p - 1);
			ReverseQuickSort(p + 1, end);
		}
	}

	void SortDesc()
	{
		ReverseQuickSort(0, size - 1);
	}

	void Shuffle()
	{
		for (int i = 0; i < size; i++)
		{
			int x = rand() % size;
			int y = rand() % size;
			int temp = data[x];
			data[x] = data[y];
			data[y] = temp;
		}
	}

	void RandomFill()
	{
		for (int i = 0; i < size; i++)
		{
			data[i] = rand();
		}
	}

	void Clear()
	{
		size = 0;
	}

	bool IsEmpty() const
	{
		return size == 0;
	}

	void Print() const
	{
		if (IsEmpty())
		{
			cout << "Vector is empty.\n";
			return;
		}

		for (int i = 0; i < size; i++)
		{
			cout << data[i] << " ";
		}
		cout << "\n";
	}

	bool operator == (ArrayList& ar2)
	{
		if (this->size != ar2.size)
		{
			cout << "Array lists aren't equal\n";
			return false;
		}

		for (int i = 0; i < size; i++)
		{
			if (this->data[i] != ar2.data[i])
			{
				cout << "Array lists aren't equal\n";
				return false;
			}
		}
		cout << "Array lists are equal\n";
		return true;
	}

	int& operator [] (unsigned int index)
	{
		if (index < 0 || index > size)
		{
			throw("Index out of range!");
		}
		return data[index];
	}

	ArrayList& operator=(const ArrayList& original)
	{
		if (data != nullptr) {
			delete[] data;
		}

		size = original.size;
		capacity = original.capacity;
		data = new int[capacity];

		for (int i = 0; i < size; i++) {
			data[i] = original.data[i];
		}

		return *this;
	}
};

istream& operator >> (istream& i, ArrayList& ar)
{
	cout << "Enter capacity: ";
	unsigned int capacity;
	cin >> capacity;
	ar.SetCapacity(capacity);
	return cin;
}

ostream& operator << (ostream& o, ArrayList ar)
{
	ar.Print();
	return cout;
}

int main()
{
	srand(time(NULL));

	ArrayList ar;
	ArrayList ar2;

	//cin >> ar;
	//cout << ar[7];
	//ar.SetCapacity(10);
	//ar.SetCapacity(10);
	//ar.GetCapacity();
	//ar.GetSize();
	//ar.PushBack(1);
	//ar.PushBack(2);
	//ar.PushBack(3);
	//ar.PushBack(4);
	//ar.PushBack(5);
	//ar2 = ar;
	//ar.Print();
	//ar2.Print();
	//cout << ar << "\n";
	//ar2.PushBack(1);
	//ar2.PushBack(2);
	//ar2.PushBack(3);
	//ar2.PushBack(4);
	//ar2.PushBack(5);
	//ar == ar2;
	//ar.Insert(5, 6);
	//ar.RemoveAt(2);
	//ar.PopFront();
	//ar.PopBack();
	//ar.IndexOf(1);
	//ar.LastIndexOf(1);
	//ar.Reverse();
	//ar.SortAsc();
	//ar.SortDesc();
	//ar.Shuffle();
	//ar.RandomFill();
	//ar.Print();
}