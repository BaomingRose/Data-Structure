#include <iostream>
#include <vector>
using namespace std;

const int max_int = 0x7fffffff;	//表示两个顶点之间没有边，为无穷大

//时间复杂度为O(n^3)，可以求多源最短路径，下面为begin到end的最短路径
//动态规划，选取不同结点作为中转结点，比较较小值更新dp表
int Floyed(const vector<vector<int>>& graph, int begin, int end) {
	int vertex_num = graph.size();
	vector<vector<int>> dp(graph);

	//分别从0～k作为中间结点，更新i和j之间最短距离
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
	//标记结点是否入集合
	vector<bool> is_set(vertex_num, false);
	//记录每个结点到begin的最短路
	vector<int> shortest_path(vertex_num, max_int);

	//第一个结点入集合
	is_set[begin] = true;
	for (int i = 0; i < vertex_num; ++i) {
		shortest_path[i] = graph[begin][i];
	}

	for (int i = 0; i < vertex_num - 1; ++i) {	//这表示还有n-1个结点要入集合
		//每次选择离集合最近的结点
		int set_with_shortest = 0;
		int minx = max_int;
		for (int j = 0; j < vertex_num; ++j) {
			if (is_set[j] == false && shortest_path[j] < minx) {
				minx = shortest_path[j];
				set_with_shortest = j;
			}
		}
		//将选中结点入集合
		is_set[set_with_shortest] = true;

		//更新不在集合中的结点距离集合中的最短路数组，因为只加入一个新结点，所以只需要比较edge[刚加入结点][k]
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