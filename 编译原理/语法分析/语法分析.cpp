#include <cstdio>
#include <iostream>
using namespace std;

#if 0
已知文法G[S]:
S → aB | bD
B → bC
C → aS | bD | ε
D → aB | bD | ε
#endif

class GrammarAnalyzer {
public:
	GrammarAnalyzer(char* p_str) : s(p_str), i(0), FLAG(true) { }

	bool judge() {
		S();
		if (s[i] == '#' && FLAG)
			return true;
		else
			return false;
	}
private:
	void S() {
		if (FLAG) {
			// 当输入的字符串中首字母为a时
			if (s[i] == 'a') {
				++i;    // 自增操作
				B();
			} else if (s[i] == 'b') {
				++i;
				D();
			} else {
				FLAG = false;
			}
		}
	}

	void B() {
		if (FLAG) {
			if (s[i] == 'b') {
				++i;
				C();
			} else if (s[i] == '#') {
				FLAG = false;
			}
		}
	}

	void C() {
		if (FLAG) {
			if (s[i] == 'a') {
				++i;
				S();
			} else if (s[i] == 'b') {
				++i;
				D();
			} else if (s[i] != '#') {
				FLAG = false;
			}
		}
	}

	void D() {
		if (FLAG) {
			if (s[i] == 'a') {
				++i;
				B();
			} else if (s[i] == 'b') {
				++i;
				D();
			} else if (s[i] != '#') {
				FLAG = false;
			}
		}
	}

private:
	// 定义一个长度为100的字符数组
	char* s;
	// 用来作数组索引,当每次匹配成功存入数据时index自增1
	int i;
	//  用来标记语句是否正确
	bool FLAG;
};


int main() {
	cout << "please input a sentence ends with #:" << endl;
	char s[1024];

	while (1) {
		cin >> s;

		// 当输入的第一个字符为#时,程序直接结束
		if (s[0] == '#')
			return 0;

		GrammarAnalyzer grammar_analyzer(s);

		bool res = grammar_analyzer.judge();
		if (res)
			cout << "This is a right sentence!" << endl;
		else
			cout << "This a wrong sentence!" << endl;

		cout << "please input a sentence end with #" << endl;
	}

	return 1;
}

#if 0
//测试用例
ab
abb
abaab
ababbbbbbbbb
bbbbbbbbbbbbbbbbbbbbbbbbbbb
baaaaabbbb(错误用例）
a##b#(错误用例）
abcdefg(错误用例）
ABCDEFG(错误用例）
#endif
