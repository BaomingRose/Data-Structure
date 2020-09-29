#include <vector>
#include <iostream>
using namespace std;

class Graph {
public:
	Graph(int vertext_num) : edge_num(0) {
		vertex_head_edge.resize(vertext_num, -1);
	}

	struct Edge {
		int end;	//�յ�
		int weight;	//Ȩֵ
		int no_next_edge;	//����������ͬ�������߱��
	};

	void add_edge(int begin, int end, int weight) {
		Edge edge;
		edge.end = end;
		edge.weight = weight;

		//���漸�����ص㣬�����ı�Ϊ�����ĵ�һ����
		edge.no_next_edge = vertex_head_edge[begin];
		edges.push_back(edge);
		vertex_head_edge[begin] = edge_num;
		++edge_num;
	}

	//���ݶ����ұ�
	void edgesOfVertex(int vertex) {
		int index_edge = vertex_head_edge[vertex];
		while (index_edge != -1) {
			Edge edge = edges[index_edge];
			cout << vertex << "--->" << edge.end << "  ȨֵΪ: " << edge.weight << endl;
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
	int edge_num;	//�ߵ�����
	vector<int> vertex_head_edge;	//����±�iΪ���ĵ�һ����
	vector<Edge> edges;		//�ߵļ���	
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