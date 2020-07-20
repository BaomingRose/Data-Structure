#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

struct TrieNode {
	char charactor;
	int child_num;
	unordered_map<char, struct TrieNode*> childs;

	TrieNode(char ch = 0) {
		charactor = ch;
		child_num = 0;
	}
};

class TrieTree {
public:
	TrieTree() {
		_head = new TrieNode();
	}

	~TrieTree() {
		del(_head);
	}


	void insert(const string& str) {
		TrieNode* cur = _head;
		for (const auto& ch : str) {
			auto it = cur->childs.find(ch);
			if (it == cur->childs.end()) {
				TrieNode* pNode = new TrieNode(ch);
				//奇怪的东西，不强转为什么编译不过啊？
				//cur->childs.insert(make_pair(ch, (TrieNode*)pNode));
				cur->childs.insert(make_pair(ch, pNode));
				++cur->child_num;
			}
			//不能将TrieNode*类型的值分配到TrieNode*类型的实体
			cur = cur->childs[ch];
		}
	}

	bool find(const string& str) {
		TrieNode* cur = _head;
		for (const auto& ch : str) {
			auto it = cur->childs.find(ch);
			if (it == cur->childs.end()) {
				return false;
			}
			cur = cur->childs[ch];
		}
		return true;
	}

private:
	void del(TrieNode*& root) {
		if (root->child_num > 0) {
			for (auto& e : root->childs) {
				del(e.second);
				e.second = nullptr;
			}
			root->child_num = 0;
			root->childs.clear();
		}
		delete root;
		root = nullptr;
	}
private:
	TrieNode* _head;
};



int main() {
	TrieTree tt;
	tt.insert("map");
	tt.insert("maq");

	cout << tt.find("map") << endl;
	cout << tt.find("map") << endl;
	tt.insert("set");
	cout << tt.find("set") << endl;
	cout << tt.find("maqq") << endl;
	cout << tt.find("set") << endl;
	cout << tt.find("maq") << endl;

	return 0;
}
