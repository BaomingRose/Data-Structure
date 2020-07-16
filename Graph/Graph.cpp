#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

//V��ʾ�������ͣ�W��ʾȨֵ���ͣ�D��ʾ�Ƿ�����
template <class V, class W, bool D = false>
class Graph {
public:
	//������������
	Graph(const V* a, int n) {
		//���ռ�
		_vertex.reserve(n);
		_edges.resize(n);
		for (int i = 0; i < n; ++i) {
			_edges[i].resize(n, W());
			_vertex.push_back(a[i]);

			_vertexIndexMap[a[i]] = i;
		}
	}

	void AddEdge(const V& src, const V& dst, const W& w) {
		//��ȡ����������±�
		int src_index = get_vertex_index(src);
		int dst_index = get_vertex_index(dst);

		_edges[src_index][dst_index] = w;
		if (D == false) {
			_edges[dst_index][src_index] = w;
		}

	}
private:
	int get_vertex_index(const V& vertex) {
#if 0
		for (int i = 0; i < _vertex.size(); ++i) {
			if (_vertex[i] == v) {
				return i;
			}
		}
		//���ִ������ʽ
		throw invalid_argument("�Ƿ�����");

		//return -1;
#endif
		//ʹ��map���Ч��
		if (_vertexIndexMap.find(vertex) != _vertexIndexMap.end()) {
			return _vertexIndexMap[vertex];
		}

		throw invalid_argument("�Ƿ�����");

		//return -1;
	}

private:
	//���㼯��
	vector<V> _vertex;
	//�ڽӾ��󣬱ߵļ���
	vector<vector<W>> _edges;

	map<V, int> _vertexIndexMap;	//ͨ���������±��ӳ���ϵ
};


void testGraph() {
	string a[] = { "curry", "tomthion", "james", "wade", "paul", "durant" };
	Graph<string, int> g(a, 6);
	g.AddEdge("curry", "tomthion", 99);
	g.AddEdge("james", "wade", 100);
	g.AddEdge("james", "paul", 98);
	g.AddEdge("james", "curry", 80);
	g.AddEdge("durant", "curry", 90);
	g.AddEdge("durant", "tomthion", 90);
}

int main() {
	testGraph();

	return 0;
}