#include <cctype>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <map>
#include <sstream>
using namespace std;


// 定义各种单词符号对应的种别表
// 0表示常数
// 1表示标识符
unordered_map<string, int> reserved_word = {
	{"int", 2 },
	{"if", 3 },
	{"else", 4 },
	{"while", 5 },
	{"for", 6 },
	{"bool", 7},
	{"break", 8},
	{"case", 9},
	{"char", 10},
	{"const", 11},
	{"continue", 12},
	{"default", 13},
	{"do", 14},
	{"double", 15},
	{"enum", 16},
	{"float", 17},
	{"goto", 18},
	{"long", 19},
	{"return", 20},
	{"short", 21},
	{"signed", 22},
	{"sizeof", 23},
	{"static", 24},
	{"struct", 25},
	{"switch", 26},
	{"typedef", 27},
	{"unsigned", 28},
	{"void", 29},
	{"include", 30},
	{"main", 31}
};

unordered_map<string, int> divided_char = {
	{"\"", 119},
	{"=", 120},
	{"(", 121},
	{")", 122},
	{",", 123},
	{";", 124},
	{"{", 125},
	{"}", 126},
	{"#", 127},
	{"+", 210},
	{"-", 211},
	{"*", 212},
	{"/", 213},
	{"<", 214},
	{"<=", 215},
	{">", 216},
	{">=", 217},
	{"!=", 218},
	{"==", 219},
	{"<<", 220},
	{">>", 221}
};

bool judge_digit(const string& str) {
	if (isdigit(str[0])) {
		for (const auto & ch : str)
			if (!isdigit(ch))
				return false;
		return true;
	}
	return false;
}

#if 0
//缺陷：无法识别<=连续
//新思路：将临时串设置几种状态：空串，数字，词语，运算符

bool exical_analysis(const string& context, vector<pair<int, string>>& result_id) {
	string tmp = "";
	for (const auto& ch : context) {
		stringstream ss;
		ss << ch;
		//如果当前字符是分割符
		if (isspace(ch) && tmp != "" || divided_char.find(ss.str()) != divided_char.end()) {
			//如果是保留字
			if (reserved_word.find(tmp) != reserved_word.end()) {
				result_id.push_back(make_pair(reserved_word[tmp], "-"));
			} else if (divided_char.find(tmp) != divided_char.end()) { //如果是分解符
				result_id.push_back(make_pair(divided_char[tmp], "-"));
			} else {
				if (judge_digit(tmp)) {
					result_id.push_back(make_pair(0, tmp));
				} else if (isalpha(tmp[0])) {
					result_id.push_back(make_pair(1, tmp));
				}
			}

			//如果当前符是分隔符
			if (divided_char.find(ss.str()) != divided_char.end()) {
				tmp.clear();
				tmp.push_back(ch);
			} else {
				tmp.clear();
			}
		} else if (isdigit(ch) || isalpha(ch))
			tmp.push_back(ch);
		else if (isprint(ch)) {
			tmp.push_back(ch);
			if (judge_digit(tmp)) {
				result_id.push_back(make_pair(0, tmp));
			} else if (isalpha(tmp[0])) {
				result_id.push_back(make_pair(1, tmp));
			}
		}
	}

	//最后一定遇到分隔符
	if (tmp != "") {
		if (divided_char.find(tmp) != divided_char.end())
			result_id.push_back(make_pair(divided_char[tmp], "-"));
	}
	return true;
}
#endif

#if 1
pair<int, string> search(const string& str) {
	if (divided_char.find(str) != divided_char.end())
		return make_pair(divided_char[str], "-");
	else if (reserved_word.find(str) != reserved_word.end())
		return make_pair(reserved_word[str], "-");
	else if (judge_digit(str))
		return make_pair(0, str);
	else
		return make_pair(1, str);
}
#endif

#if 1
//缺陷：没有逻辑关系的运算符连在一起会被当做标识符处理
bool exical_analysis(const string& context, vector<pair<int, string>>& result_id) {
	string tmp = "";
	//空串为0，常数为1，词语为2，间隔符为3
	int status = 0;
	for (const auto& ch : context) {
		if (isspace(ch)) {
			if (status != 0) {
				result_id.push_back(search(tmp));
				tmp.clear();
				status = 0;
			} else {
				continue;
			}
		}
		//是字母
		else if (isalpha(ch)) {
			if (status == 2) {
				tmp.push_back(ch);
			} else if (status == 0) {
				tmp.push_back(ch);
				status = 2;
			} else if (status > 0){
				result_id.push_back(search(tmp));
				status = 2;
				tmp.clear();
				tmp.push_back(ch);
			}
		}
		//是数字
		else if (isdigit(ch)){
			if (status == 1 || status == 2) {
				tmp.push_back(ch);
			} else if (status == 0) {
				tmp.push_back(ch);
				status = 1;
			} else if (status == 3) {
				result_id.push_back(search(tmp));
				status = 1;
				tmp.clear();
				tmp.push_back(ch);
			}
		}
		else if (isprint(ch)) {
			if (status == 0) {
				tmp.push_back(ch);
				status = 3;
			} else if (status == 3) {
				tmp.push_back(ch);
			} else {
				result_id.push_back(search(tmp));
				//忘记清空字符串
				tmp.clear();
				status = 3;
				tmp.push_back(ch);
			}
		}
	}
	return true;
}
#endif

int main() {
	//cout << isspace('\n') << endl;
	//cout << isprint('\t') << endl;
	cout << "请输入要词法分析的文件：" << endl;
	string fname;
	cin >> fname;
	ifstream ifs(fname, ios::in);
	if (!ifs) {
		cout << "文件打开失败!" << endl;
		return 1;
	}

	ostringstream tmp;
	tmp << ifs.rdbuf();
	string s = tmp.str();
	cout << s << endl;
	vector<pair<int, string>> result;
	if (!exical_analysis(s, result)) {
		cout << "语法错误！！" << endl;
		return 2;
	}

	for (const auto& e : result) {
		cout << "(" << e.first << ", " << e.second << ")\n";
	}

	ifs.close();
	return 0;
}