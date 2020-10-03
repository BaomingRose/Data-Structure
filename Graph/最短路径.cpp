#include <iostream>
#include <vector>
using namespace std;

const int max_int = 0x7fffffff;	//��ʾ��������֮��û�бߣ�Ϊ�����

//ʱ�临�Ӷ�ΪO(n^3)���������Դ���·��������Ϊbegin��end�����·��
//��̬�滮��ѡȡ��ͬ�����Ϊ��ת��㣬�ȽϽ�Сֵ����dp��
int Floyed(const vector<vector<int>>& graph, int begin, int end) {
	int vertex_num = graph.size();
	vector<vector<int>> dp(graph);

	//�ֱ��0��k��Ϊ�м��㣬����i��j֮����̾���
	for (int k = 0; k < vertex_num; ++k) {
		for (int i = 0; i < vertex_num; ++i) {
			for (int j = 0; j < vertex_num; ++j) {
				if (dp[k][j] < max_int && dp[i][k] < max_int && dp[i][k] + dp[k][j] < dp[i][j])
					dp[i][j] = dp[i][k] + dp[k][j];
			}
		}
	}

	return dp[begin][end];
}

int Dijkstra(const vector<vector<int>>& graph, int begin, int end) {
	int vertex_num = graph.size();
	//��ǽ���Ƿ��뼯��
	vector<bool> is_set(vertex_num, false);
	//��¼ÿ����㵽begin�����·
	vector<int> shortest_path(vertex_num, max_int);

	//��һ������뼯��
	is_set[begin] = true;
	for (int i = 0; i < vertex_num; ++i) {
		shortest_path[i] = graph[begin][i];
	}

	for (int i = 0; i < vertex_num - 1; ++i) {	//���ʾ����n-1�����Ҫ�뼯��
		//ÿ��ѡ���뼯������Ľ��
		int set_with_shortest = 0;
		int minx = max_int;
		for (int j = 0; j < vertex_num; ++j) {
			if (is_set[j] == false && shortest_path[j] < minx) {
				minx = shortest_path[j];
				set_with_shortest = j;
			}
		}
		//��ѡ�н���뼯��
		is_set[set_with_shortest] = true;

		//���²��ڼ����еĽ����뼯���е����·���飬��Ϊֻ����һ���½�㣬����ֻ��Ҫ�Ƚ�edge[�ռ�����][k]
		for (int k = 0; k < vertex_num; ++k) {
			if (is_set[k] == false 
				&& shortest_path[set_with_shortest] + graph[set_with_shortest][k] < shortest_path[k] 
				&& graph[set_with_shortest][k] < max_int) {
				shortest_path[k] = shortest_path[set_with_shortest] + graph[set_with_shortest][k];
			}
		}
	}
	return shortest_path[end];
}


int main() {


	return 0;
}