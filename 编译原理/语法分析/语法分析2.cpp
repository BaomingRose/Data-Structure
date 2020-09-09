#include <iostream>
using namespace std;

#if 0
E-- > E + T | T
T-- > T*F | F
F-- > (E) | i
改写：
E-- > TE'
E'-->+TE' | ε
T-- > FT'
T'-->*FT' | ε
F-- > (E) | i
#endif

class GrammarAnalyzer {
public:
	GrammarAnalyzer(char* p_str) : s(p_str), i(0), FLAG(true) { }

	bool judge() {
		E();
		if (s[i] == '#' && FLAG)
			return true;
		else
			return false;
	}
private:
	void E() {
		if (FLAG) {
			T();
			E1();
		}
	}
	void E1() {
		if (FLAG) {
			if (s[i] == '+') {
				++i;
				T();
				E1();
			} else if(s[i] != '#'&&s[i] != ')') {
				FLAG = false;
			}
		}
	}
	void T() {
		if (FLAG) {
			F();
			T1();
		}
	}
	void T1() {
		if (FLAG) {
			if (s[i] == '*') {
				++i;
				F();
				T1();
			} else if(s[i] != '#'&&s[i] != ')' && s[i] != '+') {
				FLAG = false;
			}
		}
	}

	void F() {
		if (FLAG) {
			if (s[i] == '(') {
				++i;
				E();
				if (s[i] == ')')
					++i;
				else if(s[i] == '#') {
					FLAG = false;
					++i;
				}
			} else if (s[i] == 'i') {
				++i;
			} else {
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
	char s[1024];

	while (1) {
		cout << "please input a sentence end with #" << endl;
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
	}

	return 1;
}

#if 0
//测试用例
i
a
B
i+i
i+
+++
i*i
i*i*i
i*
(i)
(i+i)*i
(i+i)*(i+i)
i+i*i
(*i+
#endif
