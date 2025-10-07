#include <iostream>
using namespace std;

void swap(int& a, int& b) {
	int t = a;
	a = b;
	b = t;
}

struct vec {
	int length = 0;
	int* data = nullptr;

	vec() = default;

	vec(int _length) : length(_length), data(new int[length] {}) {}

	~vec() {
		delete[] data;
	}

	/// <summary>
	/// Reallocates memory of vector, moving old values. If decreasing size, data might be lost.
	/// Do not modify length before reallocating. <b>It will break the function.</b>
	/// </summary>
	/// <param name="_length">New length</param>
	void realloc(int _length) {
		vec temp(_length);
		for (int i = 0; i < length && i < _length; i++)
			temp.data[i] = data[i];
		*this = std::move(temp);
	}

	/// <summary>
	/// Reads the length of the vector and then each element of the vector. Overrides all current information.
	/// </summary>
	void read() {
		int t;
		std::cin >> t;
		realloc(t);
		for (int i = 0; i < length; i++)
			std::cin >> data[i];
	}

	/// <summary>
	/// Prints all elements of the vector with a space.
	/// </summary>
	void print() {
		for (int i = 0; i < length; i++)
			std::cout << data[i] << ' ';
	}


	/// <summary>
	/// Returns the sorted state of the vector.
	/// </summary>
	/// <returns>
	/// 1 : ascending
	/// 0 : unsorted
	/// -1 : descending
	/// If all elements are equal, the vector is considered ascending.
	/// </returns>
	int sorted() {
		if (length < 2)
			return 0;
		int state = 0;
		for (int i = 0; i < length - 1; i++) {
			if (data[i] > data[i + 1]) {
				if (state == 1)
					return 0;
				else
					state = -1;
			}
			else if (data[i] < data[i + 1]) {
				if (state == -1)
					return 0;
				else
					state = 1;
			}
		}
		return (state == 0 ? 1 : state);
	}

	/// <summary>
	/// Sorts the vector using quick sort method. If "from" or "to" are set to an invalid value it will be corrected.
	/// </summary>
	/// <param name="ascending"> - whether the vector is ascending or descending. True for ascending, false for descending.</param>
	/// <param name="from"> - starting point of the search. Leave empty for default.</param>
	/// <param name="to"> - ending point of the search. Leave empty for default.</param>
	void sort(bool ascending, int from = -2, int to = -2) {
		if (from < 0 || to < 0) {//correcting values of from and to from public call or invalid input from user
			from = 0;
			to = length - 1;
		}

		if (to >= length)//asserting another invalid input problem
			to = length - 1;
		
		int index = from;

		for (int i = from; i < to; i++)
			if (
				(ascending) ?
				(data[i] < data[to]) :
				(data[i] > data[to])
				)
				swap(data[index++], data[i]);

		swap(data[index], data[to]);

		if (index > from) sort(ascending, from, index - 1);
		if (index < to) sort(ascending, index + 1, to);
	}

	/// <summary>
	/// Searches for an element using binary search method and custom function that checked the sorted status. If unsorted, it will sort automatically.
	/// </summary>
	/// <param name="element">- the element you want to search</param>
	/// <returns>Returns the position of the element without support for multiple elements search. In case no match was found it returns -1.</returns>
	int search(const int element) {
		int sorted_state = sorted();
		if (sorted_state == 0)
		{
			sort(true);
			sorted_state = 1;
		}

		for (int left = 0, right = length - 1, middle; left <= right; ) {
			middle = (left + right) / 2;

			if (data[middle] == element)
				return middle;
			
			if (data[middle] > element) {
				if (sorted_state == 1)
					right = middle - 1;
				else
					left = middle + 1;
			}
			else if (data[middle] < element) {
				if (sorted_state == 1)
					left = middle + 1;
				else
					right = middle - 1;
			}
		}
		return -1;
	}

	void push_back(int element) {
		realloc(length + 1);
		data[length - 1] = element;
	}

	void interclass(const vec& other, bool ascending = true) {
		if (!length || !other.length)
			return;
		
		vec first = *this, second = other, output;

		if (first.sorted() != ascending)
			first.sort(ascending);
		if (second.sorted() != ascending)
			second.sort(ascending);

		for (int first_counter = 0, second_counter = 0; true;)
			if (first_counter < first.length && second_counter < second.length)
				if (ascending ?
					(first.data[first_counter] < second.data[second_counter]) :
					(first.data[first_counter] > second.data[second_counter]))
					output.push_back(first.data[first_counter++]);
				else
					output.push_back(second.data[second_counter++]);
			else if (first_counter < first.length)
				output.push_back(first.data[first_counter++]);
			else if (second_counter < second.length)
				output.push_back(second.data[second_counter++]);
			else
				break;
		
		*this = std::move(output);
	}

	vec(const vec& other) {
		length = other.length;
		data = new int[length];
		for (int i = 0; i < length; i++)
			data[i] = other.data[i];
	}

	vec& operator=(const vec& other) {
		if (this == &other)
			return *this;

		length = other.length;

		delete[] data;
		data = new int[length];
		for (int i = 0; i < length; i++)
			data[i] = other.data[i];
		
		return *this;
	}

	vec(vec&& other) noexcept {
		length = other.length;
		data = new int[length];
		for (int i = 0; i < length; i++)
			data[i] = other.data[i];
		
		other.length = 0;
		other.data = 0;
	}

	vec& operator=(vec&& other) noexcept {
		if (this == &other)
			return *this;

		length = other.length;
		
		delete[] data;
		data = new int[length];
		for (int i = 0; i < length; i++)
			data[i] = other.data[i];

		other.length = 0;
		other.data = nullptr;

		return *this;
	}
};

int main() {
	vec a, b;
	a.read();
	b.read();
	a.interclass(b, true);
	a.print();
}