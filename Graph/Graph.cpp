#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
using namespace std;

//V表示顶点类型，W表示权值类型，D表示是否有向
template <class V, class W, bool D = false>
class Graph {
public:
	//数组和数组个数
	Graph(const V* a, int n) {
		//开空间
		_vertex.reserve(n);
		_edges.resize(n);
		for (int i = 0; i < n; ++i) {
			_edges[i].resize(n, W());
			_vertex.push_back(a[i]);

			_vertexIndexMap[a[i]] = i;
		}
	}

	void AddEdge(const V& src, const V& dst, const W& w) {
		//获取两个顶点的下标
		int src_index = get_vertex_index(src);
		int dst_index = get_vertex_index(dst);

		_edges[src_index][dst_index] = w;
		if (D == false) {
			_edges[dst_index][src_index] = w;
		}
	}


	//给定顶点去深搜
	void DFS(const V& vertex) {
		if (_vertexIndexMap.find(vertex) == _vertexIndexMap.end()) {
			return;
		}
		int srcIndex = _vertexIndexMap[vertex];
		vector<bool> visited;
		visited.resize(_vertexIndexMap.size(), false);
		_DFS(srcIndex, visited, srcIndex);
	}

	void BFS(const V& vertex) {
		if (_vertexIndexMap.find(vertex) == _vertexIndexMap.end()) {
			return;
		}
		int srcIndex = _vertexIndexMap[vertex];
		vector<bool> visited;
		visited.resize(_vertexIndexMap.size(), false);
		_BFS(srcIndex, visited);

	}

private:
	//深度优先搜索，后面的第三个参数只是为了打印格式而传入，判断是否是第一个顶点，如果是的话但因与后面有所不同
	void _DFS(int srcIndex, vector<bool>& visited, const int& first_vertex) {
		visited[srcIndex] = true;
		if (srcIndex == first_vertex) {
			cout << _vertex[srcIndex];
		} else {
			cout << "->" << _vertex[srcIndex];
		}
		for (int i = 0; i < _edges[srcIndex].size(); ++i) {
			if (_edges[srcIndex][i] != W() && visited[i] == false) {
				_DFS(i, visited, first_vertex);
			}
		}
	}

	void _BFS(int srcIndex, vector<bool>& visited) {
		visited[srcIndex] = true;
		cout << _vertex[srcIndex];
		queue<int> q;
		q.push(srcIndex);

		while (!q.empty()) {
			int index = q.front();
			for (int i = 0; i < _edges[index].size(); ++i) {
				if (_edges[index][i] != W() && visited[i] == false) {
					cout << "->" << _vertex[i];
					visited[i] = true;
					q.push(i);
				}
			}
			q.pop();
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
		//两种处理错误方式
		throw invalid_argument("非法顶点");

		//return -1;
#endif
		//使用map提高效率
		if (_vertexIndexMap.find(vertex) != _vertexIndexMap.end()) {
			return _vertexIndexMap[vertex];
		}

		throw invalid_argument("非法顶点");

		//return -1;
	}

private:
	//顶点集合,有了map，是否还要使用vector存储顶点信息？留着是有用的，深搜可以看到，如果变例输出顶点就要根据下标找顶点
	vector<V> _vertex;
	//邻接矩阵，边的集合
	vector<vector<W>> _edges;

	map<V, int> _vertexIndexMap;	//通过顶点找下标的映射关系
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

	g.DFS("curry");
	cout << endl;
	g.BFS("curry");
	cout << endl;
}

#if 0
int main() {
	testGraph();

	return 0;
}
#endif