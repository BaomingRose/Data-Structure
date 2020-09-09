#include <iostream>
using namespace std;

#if 0
E-- > E + T | T
T-- > T*F | F
F-- > (E) | i
��д��
E-- > TE'
E'-->+TE' | ��
T-- > FT'
T'-->*FT' | ��
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
	// ����һ������Ϊ100���ַ�����
	char* s;
	// ��������������,��ÿ��ƥ��ɹ���������ʱindex����1
	int i;
	//  �����������Ƿ���ȷ
	bool FLAG;
};


int main() {
	char s[1024];

	while (1) {
		cout << "please input a sentence end with #" << endl;
		cin >> s;

		// ������ĵ�һ���ַ�Ϊ#ʱ,����ֱ�ӽ���
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
//��������
ab
abb
abaab
ababbbbbbbbb
bbbbbbbbbbbbbbbbbbbbbbbbbbb
baaaaabbbb(����������
a##b#(����������
abcdefg(����������
ABCDEFG(����������
#endif
