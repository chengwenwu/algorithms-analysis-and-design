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
	int vertexId;
	Vertex* nextVertex;
	Node* headNode;
	Vertex* parent;
	Color color;
	int discovery;
	int finish;
};

class Graph{
public:
	Graph();
	void setHeadVertex(Vertex* headVertex_in);
	Vertex* getHeadVertex()const;
	bool addEdge(int fromId, int toId);

	void setGraphType(TypeOfGraph graphType_in);
	bool bfs(int startVertex_in);
	bool dfs(int startVertex_in);
	void reset();
	void TopologicalSort();
	void stronglyConnectCompents(int startVertex_in);
private:
	Vertex* headVertex;
	TypeOfGraph graphType;
	Vertex* topologicalSort;
	Vertex* GT;
	/*
	*check if the fromVertex and toVertex exist
	*if not add them to Vertex list
	*/
	bool addAllVertex(int fromVertexId_in, int toVertexId_in);

	/*
	*according to the graph type add edge
	*before this step all vertexes have added to the vertexlist
	*/
	bool addOneEdge(int fromVertexId_in, int toVertexId_in);
	bool bfsSub(int startVertex_in);
	void dfsSub(Vertex* vertexPtr, int &time);
	void exchangePointerForGT();
};