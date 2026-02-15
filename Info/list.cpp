#include <iostream>

struct list {

	struct list_element {
		int value;
		list_element* to;
		list_element() : value(0), to(nullptr) {}
		list_element(int value, list_element* to) : value(value), to(to) {}
		void print() { std::cout << value << '\n'; }
		void swap(list_element* other) { //realized it is not nececsary for reverse() but i will leave it here
			list_element* to_temp; int val_temp;

			to_temp = other->to;
			other->to = to;
			to = to_temp;

			val_temp = other->value;
			other->value = value;
			value = val_temp;
		}
		void value_swap(list_element* other) {
			if (other == nullptr)return;
			int t = other->value;
			other->value = value;
			value = t;
		}
	}*head, *tail;

	int size;

	list() :size(0), head(nullptr), tail(nullptr) {}

	list(const list&) = delete;
	list& operator=(const list&) = delete;


	~list() {
		list_element* pointer = head;
		while (pointer) {
			list_element* temp = pointer->to;
			delete pointer;
			pointer = temp;
		}
	}

	void add_front(int value) {
		list_element* el = new list_element(value, head);
		head = el;
		if (!tail)tail = head;
		size++;
	}

	void add_back(int value) {
		list_element* el = new list_element(value, nullptr);
		if (!head)head = el;
		if (!tail)tail = el;
		else {
			tail->to = el;
			tail = el;
		}
		size++;
	}

	void insert_at(int index,int value) {
		
		if (index >= size) {
			add_back(value);
			return;
		}
		else if (index <= 0) {
			add_front(value);
			return;
		}
		
		list_element* behind, *element;
		behind = get_at(index - 1);
		element = new list_element(value, behind->to);
		behind->to = element;
		size++;
	}

	void pop_front() {
		if (size <= 0) return;
		list_element *el = head;
		head = head->to;
		delete el;
		size--;
	}

	void pop_back() {
		if (size <= 0) return;
		if (size == 1) {
			delete head;
			head = tail = nullptr;
			size = 0;
			return;
		}
		list_element* el = tail;
		tail = get_at(size - 2);
		tail->to = nullptr;
		delete el;
		size--;
	}

	void pop_at(int index) {
		if (index < 0 || index >= size)
			return;
		
		if (index == 0) {
			pop_front();
			return;
		}
		else if (index == size - 1) {
			pop_back();
			return;
		}

		list_element* behind, * to_delete;
		behind = get_at(index - 1);
		to_delete = behind->to;
		behind->to = to_delete->to;
		delete to_delete;
		size--;
	}

	list_element* get_at(int index) {
		if (index >= size || index < 0) return nullptr;
		list_element* p = head;
		for (int i = 0; i < index; i++)
			p = p->to;
		return p;
	}

	void print_at(int index) {
		list_element* e = get_at(index);
		if (e) std::cout << e->value << '\n';
		else std::cout << "Error at getting element with index " << index << ".\n";
	}

	void print() {
		list_element* pointer = head; 
		std::cout << '\n';
		while (pointer) {
			std::cout << pointer->value << ' ';
			pointer = pointer->to;
		}
		std::cout << '\n';
	}

	void clear() {
		while (head) {
			list_element* e = head->to;
			delete head;
			head = e;
		}
		size = 0;
		head = tail = nullptr;
	}

	int get_size() {
		size = 0;
		list_element* e = head;
		while (e) {
			size++;
			e = e->to;
		}
		return size;
	}

	void reverse() {
		int s = get_size() / 2; // we do this to ensure size is correct and to not repeat size/2
		list_element* ptr = head, *second_ptr;
		for (int i = 0; i < s; i++) {
			second_ptr = get_at(size - i - 1);
			ptr->value_swap(second_ptr);
			ptr = ptr->to;
		}
	}

	list_element* find(int value) {
		list_element* ptr = head;
		while (ptr) {
			if (ptr->value == value) return ptr;
			ptr = ptr->to;
		}
		return nullptr;
	}
};

int main() {
	list l;
	for (int i = 0; i < 15; i++) l.add_back(i + 1);
	l.find(10)->print();
}