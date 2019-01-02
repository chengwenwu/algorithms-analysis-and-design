enum Color{white, gray, black};
enum TypeOfGraph{directed, undirected};
class Vertex;
class Node{
public:
	Node();
	void setVertex(Vertex * vertex_in);
	Vertex* getVertex()const;
	void setNextNode(Node* nextNode_in);
	Node* getNextNode()const;
private:
	Vertex* vertex;
	Node* nextNode;
};

class Vertex{
public:
	Vertex();
	Vertex(int vertexId_in);
	void setVertexId(int vertexId_in);
	int getVertexId()const;
	void setNextVertex(Vertex * nextVertex_in);
	Vertex* getNextVertex()const;
	void setHeadNode(Node* headNode_in);
	Node* getHeadNode()const;
	void setParent(Vertex* parent_in);
	Vertex* getParent()const;
	void setColor(Color color_in);
	Color getColor()const;
	void setDiscovery(int discovery_in);
	int getDiscovery()const;
	void setFinish(int finish_in);
	int getFinish();
private:
	int vertexId;//顶点的唯一标识符
	Vertex* nextVertex;//把所有顶点放在一个链表中，这个指针指向它的下一个顶点
	Node* headNode;//这里存放与它相邻的顶点
	Vertex* parent;//这里存放它的父节点
	Color color;//这是它的颜色
	int discovery;//这是它的发现时间（DFS中）
	int finish;//这是它的完成时间（BFS中）
};

class Graph{
public:
	Graph();
	void setHeadVertex(Vertex* headVertex_in);
	Vertex* getHeadVertex()const;
	/*
	@fromid是起始顶点的Id
	@toId是到达顶点的Id
	*/
	bool addEdge(int fromId, int toId);

	void setGraphType(TypeOfGraph graphType_in);
	bool bfs(int startVertex_in);
	bool dfs(int startVertex_in);
	/*这个函数负责把所有顶点的父节点，颜色，发现时间，结束时间等等进行初始化。
 */
	void reset();
	void TopologicalSort();
	void stronglyConnectCompents(int startVertex_in);
private:
	Vertex* headVertex;//这里存放它的所有顶点
	TypeOfGraph graphType;//这里存放这个图是有向图还是无向图
	Vertex* topologicalSort;//这里存放的是拓扑排序的结果
	Vertex* GT;//这里存放把所有边反向后的结果，主要用在求解强连通图的过程中
	/*
	*检查 fromVertex 和 toVertex 是否存在
	*如果没有则把他们添加到顶点列表
	*/
	bool addAllVertex(int fromVertexId_in, int toVertexId_in);

	/*
	*添加一条从fromVertexId_in到toVertexId_in的边
	*这两个顶点必须都已经在顶点列表中才能调用这个函数
	*/
	bool addOneEdge(int fromVertexId_in, int toVertexId_in);
	bool bfsSub(int startVertex_in);
	void dfsSub(Vertex* vertexPtr, int &time);
	void exchangePointerForGT();
};
