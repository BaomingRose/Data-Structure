#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
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


	//��������ȥ����
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
	//�����������������ĵ���������ֻ��Ϊ�˴�ӡ��ʽ�����룬�ж��Ƿ��ǵ�һ�����㣬����ǵĻ����������������ͬ
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
	//���㼯��,����map���Ƿ�Ҫʹ��vector�洢������Ϣ�����������õģ����ѿ��Կ��������������������Ҫ�����±��Ҷ���
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