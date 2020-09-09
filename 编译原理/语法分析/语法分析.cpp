#include <cstdio>
#include <iostream>
using namespace std;

#if 0
��֪�ķ�G[S]:
S �� aB | bD
B �� bC
C �� aS | bD | ��
D �� aB | bD | ��
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
			// ��������ַ���������ĸΪaʱ
			if (s[i] == 'a') {
				++i;    // ��������
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
	// ����һ������Ϊ100���ַ�����
	char* s;
	// ��������������,��ÿ��ƥ��ɹ���������ʱindex����1
	int i;
	//  �����������Ƿ���ȷ
	bool FLAG;
};


int main() {
	cout << "please input a sentence ends with #:" << endl;
	char s[1024];

	while (1) {
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

		cout << "please input a sentence end with #" << endl;
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
