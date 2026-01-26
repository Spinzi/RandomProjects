#include <iostream>
#include <fstream>

//
// inFile.in
// v1_len
// v1_1 v1_2 v1_3 ...
// v2_len
// v2_1 v2_2 v2_3 ...
//
// vn_1 < vn_2 < vn<3
// 
// outFile.out
// v1 + v2 (interclassed)
//
// seekg(streampos) - sets cursor to streampos
// streampos tellg - current pos
//

using namespace std;

const char IN_FILE_NAME[] = "inFile.in";

struct vec{
	int len;
	streampos pos;
	struct {
		int val, pos;
	}temp;

	void increment(ifstream& file) {
		file.clear();
		file.seekg(pos);
		file >> temp.val;
		pos = file.tellg();
		temp.pos++;
	}
};

int main() {
	
	ifstream file(IN_FILE_NAME);
	int temp;
	vec v1, v2;

	file >> v1.len;
	v1.pos = file.tellg();
	for (int i = 0; i < v1.len; i++)
		file >> temp;
	file >> v2.len;
	v2.pos = file.tellg();

	v1.increment(file);
	v2.increment(file);
	v1.temp.pos = v2.temp.pos = 0;
	
	while(v1.temp.pos < v1.len && v2.temp.pos < v2.len)
		if (v1.temp.val < v2.temp.val) {
			cout << v1.temp.val << ' ';
			v1.increment(file);//temp.pos is incremented here
		}
		else {
			cout << v2.temp.val << ' ';
			v2.increment(file);
		}

	while (v1.temp.pos < v1.len) {
		cout << v1.temp.val << ' ';
		v1.increment(file);
	}

	while (v2.temp.pos < v2.len) {
		cout << v2.temp.val << ' ';
		v2.increment(file);
	}
}