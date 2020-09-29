#include <vector>
#include <iostream>
using namespace std;

class Graph {
public:
	Graph(int vertext_num) : edge_num(0) {
		vertex_head_edge.resize(vertext_num, -1);
	}

	struct Edge {
		int end;	//终点
		int weight;	//权值
		int no_next_edge;	//与这边起点相同的下条边编号
	};

	void add_edge(int begin, int end, int weight) {
		Edge edge;
		edge.end = end;
		edge.weight = weight;

		//下面几句是重点，后加入的边为遍历的第一条边
		edge.no_next_edge = vertex_head_edge[begin];
		edges.push_back(edge);
		vertex_head_edge[begin] = edge_num;
		++edge_num;
	}

	//根据顶点找边
	void edgesOfVertex(int vertex) {
		int index_edge = vertex_head_edge[vertex];
		while (index_edge != -1) {
			Edge edge = edges[index_edge];
			cout << vertex << "--->" << edge.end << "  权值为: " << edge.weight << endl;
			index_edge = edge.no_next_edge;
		}
	}

	void traverseAllEdges() {
		int vertex_num = vertex_head_edge.size();
		for (int i = 0; i < vertex_num; ++i) {
			edgesOfVertex(i);
		}
	}
private:
	int edge_num;	//边的条数
	vector<int> vertex_head_edge;	//存放下标i为起点的第一条边
	vector<Edge> edges;		//边的集合	
};

int main() {
	Graph graph(5);
	graph.add_edge(1, 2, 100);
	graph.add_edge(1, 3, 300);
	graph.edgesOfVertex(1);
	cout << endl;

	graph.add_edge(2, 0, 5);
	graph.add_edge(3, 1, 1000);
	graph.add_edge(2, 3, 888);
	graph.traverseAllEdges();

	return 0;
}