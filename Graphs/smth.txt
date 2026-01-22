#include <iostream>

const int MAX_SIZE = 100;

struct path {
	int vertices[MAX_SIZE], size;
	path() : size(0) {}
	void push_back(int value) {
		vertices[size++] = value;
	}
	int pop_back() {
		return vertices[--size];
	}
	int get_last() {
		return vertices[size - 1];
	}
	operator bool() const {
		return size > 0;
	}
	path& operator=(const path& other) {
		for (int i = 0; i < other.size; i++)
			vertices[i] = other.vertices[i];
		size = other.size;
		return *this;
	}
	bool find(int value) {
		for (int i = 0; i < size; i++)
			if (vertices[i] == value)
				return true;
		return false;
	}
	void print() const {
		std::cout << "Path: ";
		for (int i = 0; i < size; i++) {
			std::cout << vertices[i];
			if (i < size - 1) std::cout << " -> ";
		}
		std::cout << "\n";
	}
};

struct path_stack {
	path array[MAX_SIZE];
	int size;
	path_stack() : size(0) {}
	void push_back(path value) {
		array[size++] = value;
	}
	path pop_back(int value) {
		size--;
		return array[size];
	}
	path get_last() {
		return array[size - 1];

	}
	path_stack& operator=(const path_stack& other) {
		for (int i = 0; i < other.size; i++)
			array[i] = other.array[i];
		size = other.size;
		return *this;
	}
	
	operator bool() const {
		return size > 0;
	}

	void reset() {
		size = 0;
	}
};

struct edge {
	int to, weight;
	edge() : to(0), weight(0) {}
	edge(int to, int weight) : to(to), weight(weight) {}
};

struct vertice {
	int value = 0, edges_size = 0;
	edge edges[MAX_SIZE];
	void add_edge(int to, int weight = 0) {
		edges[edges_size].to = to;
		edges[edges_size++].weight = weight;
	}
};

struct Graph {
	int vertices_size = 0;
	vertice vertices[MAX_SIZE];

	void read() {
		std::cout << "Size of vertices: ";
		std::cin >> vertices_size;
		for (int i = 0; i < vertices_size; i++) {
			std::cout << "Vertice " << i << " \nEnter value and number of adjacents separated by space:\n";
			int t;
			std::cin >> vertices[i].value >> t;
			for (int j = 0; j < t; j++) {
				std::cout << "Reading adjacent " << j << " of vertice " << i << ", enter the other element and its weight:\n";
				int to, weight;
				std::cin >> to >> weight;
				vertices[i].add_edge(to, weight);
			}
		}
	}

	void print() {
		std::cout << "\nListing graph\n";
		std::cout << "G = ( {";
		for (int i = 0; i < vertices_size; i++)
			std::cout << i << ", ";
		std::cout << "}, {";
		for (int i = 0; i < vertices_size; i++)
			for (int j = 0; j < vertices[i].edges_size; j++)
				std::cout << '[' << i << ',' << vertices[i].edges[j].to << ']';
		std::cout << "}]\n\n";

		for (int i = 0; i < vertices_size; i++) {
			std::cout << "Vertice " << i << '\n';
			std::cout << "Value: " << vertices[i].value << '\n';
			std::cout << "Adjacents:\n";
			for (int j = 0; j < vertices[i].edges_size; j++) {
				std::cout << " " << j << ". To: " << vertices[i].edges[j].to << " Weight: " << vertices[i].edges[j].weight << "\n";
			}
			std::cout << '\n';
		}
		std::cout << "\n Matrix of graph:\n\n";

		for (int i = 0; i < vertices_size; i++) {
			for (int j = 0; j < vertices_size; j++) {
				bool value = false;
				for (int a = 0; a < vertices[i].edges_size; a++) {
					if (j == vertices[i].edges[a].to)
						value = true;
				}
				std::cout << value;
			}
			std::cout << '\n';
		}

		std::cout << "\n";
	}

	path find(const int starting_point, const int target) {

		path_stack queue_current, queue_next;

		path start;
		bool visited[MAX_SIZE]{};

		start.push_back(starting_point);
		
		queue_current.push_back(start);

		while (queue_current) {

			for (int path_index = 0; path_index < queue_current.size; path_index++) {

				const int vertice_to_check_index = queue_current.array[path_index].get_last();
				for (int edge_index = 0; edge_index < vertices[vertice_to_check_index].edges_size; edge_index++) {
					
					int adjacents_index = vertices[vertice_to_check_index].edges[edge_index].to;

					if (adjacents_index >= vertices_size || visited[adjacents_index]) continue;

					visited[adjacents_index] = true;

					if (adjacents_index == target) {
						queue_current.array[path_index].push_back(adjacents_index);
						return queue_current.array[path_index];
					}
					
					if (vertices[adjacents_index].edges_size > 0) {
						path next_path = queue_current.array[path_index];
						next_path.push_back(adjacents_index);
						queue_next.push_back(next_path);
					}

				}

			}

			queue_current = queue_next;
			queue_next.reset();
		}

		path null;
		return null;
	}

};


int main() {

	Graph G;

	G.read();
	G.print();

	// Ask for start and target
	int start, target;
	std::cout << "Enter starting vertex: ";
	std::cin >> start;
	std::cout << "Enter target vertex: ";
	std::cin >> target;

	// Find path
	path result = G.find(start, target);

	// Print result
	if (result) { // operator bool() returns true if path has elements
		std::cout << "Path found: ";
		result.print();
	}
	else {
		std::cout << "Path not found.\n";
	}

	return 0;
}