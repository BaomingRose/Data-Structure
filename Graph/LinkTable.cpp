#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

//构造边，起点到终点，还有权值，起点有必要吗（还是有必要的），
template <class W>
struct Edge {
	int _src;
	int _des;
	W _weigth;

	struct Edge<W>* _next;

	Edge(int src, int des, const W& weight) : _src(src), _des(des), _weigth(weight), _next(nullptr) {}
};

//先实现无向图
template <class V, class W>
class GraphLinkTable {
public:
	GraphLinkTable(const V* data, int size) {
		_vertex.resize(size);
		_edge.resize(size, nullptr);
		for (int i = 0; i < size; ++i) {
			_vertex[i] = data[i];
			_vertexIndexMap.insert(make_pair(data[i], i));
		}
	}

	void addEdge(const V& src, const V& dst, const W& weight) {
		int src_index = getIndexOfVertex(src);
		int dst_index = getIndexOfVertex(dst);
		Edge<W>* edge_ptr = new Edge<W>(src_index, dst_index, weight);

		edge_ptr->_next = _edge[src_index];
		_edge[src_index] = edge_ptr;

		Edge<W>* edge_ptr2 = new Edge<W>(dst_index, src_index, weight);
		edge_ptr2->_next = _edge[dst_index];
		_edge[dst_index] = edge_ptr2;
	}

	void print_all_edges() {
		for (int i = 0; i < _edge.size(); ++i) {
			Edge<W>* cur = _edge[i];
			while (cur != nullptr) {
				cout << "src: " << cur->_src << "   dst: " << cur->_des << "    weight: " << cur->_weigth << endl;
				cur = cur->_next;
			}
		}
	}
private:
	int getIndexOfVertex(const V& vertex) {
		if (_vertexIndexMap.find(vertex) == _vertexIndexMap.end()) {
			return -1;
		}

		return _vertexIndexMap[vertex];
	}
private:
	vector<V> _vertex;
	vector<Edge<W>*> _edge;	//保存的是下标索引对应顶点为起点的边的集合
	map<V, int> _vertexIndexMap;
};

int main() {
	string a[] = { "curry", "tomthion", "james", "wade", "paul", "durant" };
	GraphLinkTable<string, int> g(a, 6);
	g.addEdge("curry", "tomthion", 99);
	g.addEdge("james", "wade", 100);
	g.addEdge("james", "paul", 98);
	g.addEdge("james", "curry", 80);
	g.addEdge("durant", "curry", 90);
	g.addEdge("durant", "tomthion", 90);

	g.print_all_edges();

	return 0;
}
