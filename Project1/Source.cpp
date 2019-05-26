#include<iostream>
#include<string>
using namespace std;


enum erors {
	the_same_key, incorrect_key, remotely, not_faunt, not_erors, list_is_full
};
enum  Status { free1, busy};
struct Record {
	int Personal_Account;
	string name;
	Status status;
};

class Hash
{
private:
	unsigned int count;
	unsigned int max_size;
	unsigned int min_key;
	Record *table;
	unsigned int search_key(Record);
public:
	Hash(unsigned int max_size) {
		if (max_size < 5) max_size = 10;
		this->max_size = max_size; 
		count = 0;
		table = new Record[max_size];
		for (int i = 0; i < max_size; i++) {
			table[i].Personal_Account = 0;
			table[i].name = "-";
			table[i].status = free1;
		}
	}
	~Hash() {
		delete[] table;
	}
	int hash_func_one(string key) {//складывает все числовые значения строки
		int sum=0;
		for (int i = 0; i < key.length(); i++) {
			sum = sum + int(key[i]);
		}
		return (sum % max_size); 
	}

	int hash_func_two(unsigned int hash) {//+k
		int k = 2;
		for (int i = 0; i < max_size; i++) {
			if ((max_size) % k != 0) break;
			k++;
		}
		return (hash + k) % (max_size);
	}

	erors add(string name, int personal_account) {
		if (personal_account < 1 || personal_account > 9999999) return incorrect_key;
		if (count == max_size) return list_is_full;
		int N = hash_func_one(name);
		if ((table[N].status == free1)) {
		/*	if (table[N].Personal_Account == personal_account)
			{
				return the_same_key;
			}*/
			table[N].Personal_Account = personal_account;
			table[N].name = name;
			table[N].status = busy;
			count++;
			return not_erors;
		}
		else if ((table[N].status == busy)) {
		    for (int i = 0; i < max_size; i++) {
				if (table[i].Personal_Account == personal_account) return the_same_key;
			}
			int N2 = hash_func_two(N);
			while (count < max_size) {
				if (table[N2].Personal_Account == personal_account)
				{
					return the_same_key;
				}
				if ((table[N2].status == free1) ) {
					table[N2].Personal_Account = personal_account;
					table[N2].name = name;
					table[N2].status = busy;
					count++;
					return not_erors;
				}
				N2 = hash_func_two(N2);
			}
		}
		return list_is_full;
	}
	void Print() {
		cout << "           HashTable" << endl;
		for (int i = 0; i < max_size; i++) {
			cout << "-----------------------------------" << endl;
			if (table[i].status == busy) {
				cout << i << ") " << table[i].Personal_Account << " " << table[i].name << endl;
			}
			else if (table[i].status == free1) {
				cout << i << ") " << "Free" << endl;
			}
		}
		cout << "-----------------------------------" << "\n\n\n";
	}

	int search(string name, int personal_account) {
		int N = hash_func_one(name);
		if ((name == table[N].name) && (personal_account == table[N].Personal_Account)) {
				return N;
		}
		else {
			int count1 = 0;
			while (true) {
				N = hash_func_two(N);
				if ((table[N].Personal_Account == personal_account) && (name == table[N].name)){
						return N;
				}
				count1++;
				if (count1 >= max_size)return -2;
			}
		}
	}
	erors remove(string name, int personal_account) {
		if (personal_account < 1) return incorrect_key;
		int N = search(name, personal_account);
		if (N == -2)return not_faunt;
		if (N == -1)return remotely;
		table[N].status = free1;
		table[N].Personal_Account = 0;
		table[N].name = "-";
		count--;
		return not_erors;
	}
};

int main() {
	setlocale(LC_ALL, "rus");
	Hash table(10);
	string name = "AAAA";
	int Personal_Account1 = 85463;
	int Personal_Account = 765536;
	table.add(name, Personal_Account);
	table.add(name, Personal_Account1);
	table.Print();
	system("pause");
	return 0;
}