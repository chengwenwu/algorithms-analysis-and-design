#include "bfs.hpp"
#include <iostream>
#include <queue>
using namespace std;
Node::Node()
{
	this->vertex = NULL;
	this->nextNode = NULL;
}
void Node::setVertex(Vertex * vertex_in)
{
	this->vertex = vertex_in;
}
Vertex* Node::getVertex()const
{
	return this->vertex;
}
void Node::setNextNode(Node* nextNode_in)
{
	this->nextNode = nextNode_in;
}
Node* Node::getNextNode()const
{
	return this->nextNode;
}

Vertex::Vertex()
{
	this->vertexId = -1;
	this->nextVertex = NULL;
	this->headNode = NULL;
	this->parent = NULL;
	this->color = white;
	this->discovery = -1;
	this->finish = -1;
}

Vertex::Vertex(int vertexId_in)
{
	this->vertexId = vertexId_in;
	this->nextVertex = NULL;
	this->headNode = NULL;
	this->parent = NULL;
	this->color = white;
	this->discovery = -1;
	this->finish = -1;
}


void Vertex::setVertexId(int vertexId_in)
{
	this->vertexId = vertexId_in;
}
int Vertex::getVertexId()const
{
	return this->vertexId;
}
void Vertex::setNextVertex(Vertex * nextVertex_in)
{
	this->nextVertex = nextVertex_in;
}
Vertex* Vertex::getNextVertex()const
{
	return nextVertex;
}
void Vertex::setHeadNode(Node* headNode_in)
{
	this->headNode = headNode_in;
}
Node* Vertex::getHeadNode()const
{
	return this->headNode;
}
void Vertex::setParent(Vertex* parent_in)
{
	this->parent = parent_in;
}
Vertex* Vertex::getParent()const
{
	return this->parent;
}
void Vertex::setColor(Color color_in)
{
	this->color = color_in;
}
Color Vertex::getColor()const
{
	return this->color;
}
void Vertex::setDiscovery(int discovery_in)
{
	this->discovery = discovery_in;
}
int Vertex::getDiscovery()const
{
	return this->discovery;
}
void Vertex::setFinish(int finish_in)
{
	this->finish = finish_in;
}
int Vertex::getFinish()
{
	return this->finish;
}
Graph::Graph()
{
	this->headVertex = NULL;
	this->graphType = directed;
	this->topologicalSort = NULL;
	this->GT = NULL;
}
void Graph::setHeadVertex(Vertex* headVertex_in)
{
	this->headVertex = headVertex_in;
}
Vertex* Graph::getHeadVertex()const
{
	return this->headVertex;
}

void Graph::setGraphType(TypeOfGraph graphType_in)
{
	this->graphType = graphType_in;
}

bool Graph::addEdge(int fromId, int toId)
{
	if(fromId == toId)
		return false;
	if(!addAllVertex(fromId, toId))
		return false;
	if(!addOneEdge(fromId,toId))
		return false;
	if(graphType == undirected)
	{
		if(!addOneEdge(toId,fromId))
			return false;
	}
	return true;
}
/*
*check if the fromVertex and toVertex exist
*if not add them to Vertex list
*/
bool Graph::addAllVertex(int fromVertexId_in, int toVertexId_in)
{
	if(headVertex == NULL)
	{
		Vertex *newVertex1 = new Vertex(fromVertexId_in);
		Vertex *newVertex2 = new Vertex(toVertexId_in);

		newVertex1->setNextVertex(newVertex2);
		headVertex = newVertex1;
		return true;
	}
	else
	{
		Vertex *fromVertex = NULL, *toVertex = NULL,
				*vertexptr = headVertex, *preVertex = NULL;
		while(vertexptr != NULL)
		{
			if(vertexptr->getVertexId() == fromVertexId_in)
				fromVertex = vertexptr;
			if(vertexptr->getVertexId() == toVertexId_in)
				toVertex = vertexptr;
			preVertex = vertexptr;
			vertexptr = vertexptr->getNextVertex();
		}

		if(fromVertex != NULL && toVertex != NULL)//if alread have fromid
		{
			return true;
		}
		else if(fromVertex == NULL && toVertex == NULL)//if don't have fromid
		{
			Vertex *newVertex1 = new Vertex(fromVertexId_in);
			Vertex *newVertex2 = new Vertex(toVertexId_in);

			newVertex1->setNextVertex(newVertex2);
			preVertex->setNextVertex(newVertex1);
			return true;
		}
		else if(fromVertex == NULL)
		{
			Vertex *newVertex1 = new Vertex(fromVertexId_in);
			preVertex->setNextVertex(newVertex1);
			return true;
		}
		else if(toVertex == NULL)
		{
			Vertex *newVertex1 = new Vertex(toVertexId_in);
			preVertex->setNextVertex(newVertex1);
			return true;
		}
		else
			return false;

	}
}

/*
*according to the graph type add edge
*before this step all vertexes have added to the vertexlist
*/
bool Graph::addOneEdge(int fromVertexId_in, int toVertexId_in)
{
	Vertex *fromVertex = NULL, *toVertex = NULL,
				*vertexptr = headVertex;
	while(vertexptr != NULL)
	{

		if(vertexptr->getVertexId() == fromVertexId_in)
			fromVertex = vertexptr;
		if(vertexptr->getVertexId() == toVertexId_in)
			toVertex = vertexptr;
		if(fromVertex != NULL && toVertex != NULL)
		 	break;
		vertexptr = vertexptr->getNextVertex();
	}

	if(fromVertex == NULL || toVertex == NULL)
	{
		return false;
	}
	else
	{
		Node *newNode1 = new Node();
		newNode1->setVertex(toVertex);
		Node* nodeptr = fromVertex->getHeadNode(), *preNode = NULL;
		if(nodeptr == NULL)
		{
			fromVertex->setHeadNode(newNode1);
		}
		else
		{
			while(nodeptr != NULL)
			{
				preNode = nodeptr;
				nodeptr = nodeptr->getNextNode();
			}
			preNode->setNextNode(newNode1);
		}
		return true;
	}
}

bool Graph::bfs(int startVertex_in)
{
	reset();
	cout<<"BFS results: ";
	bfsSub(startVertex_in);
	Vertex *vertexPtr = headVertex;
	while(vertexPtr != NULL)
	{
		if(vertexPtr->getColor() == white)
		{
			if(!bfsSub(vertexPtr->getVertexId()))
				return false;
		}
		vertexPtr = vertexPtr->getNextVertex();
	}
	cout<<endl;
	return true;
}
bool Graph::bfsSub(int startVertex_in)
{
	Vertex* startVertex = NULL, *vertexPtr = headVertex;
	while(vertexPtr != NULL)
	{
		if(vertexPtr->getVertexId() == startVertex_in)
		{
			startVertex = vertexPtr;
			break;
		}
		vertexPtr = vertexPtr->getNextVertex();
	}
	if(startVertex == NULL)
		return false;

	queue<Vertex*> que;

	startVertex->setColor(gray);
	startVertex->setDiscovery(0);
	startVertex->setParent(NULL);
	que.push(startVertex);
	while(que.size() != 0)
	{
		vertexPtr = que.front();
		que.pop();
		cout<<vertexPtr->getVertexId()<<" -> ";
		vertexPtr->setColor(black);
		Node* nodePtr = vertexPtr->getHeadNode();
		while(nodePtr != NULL)
		{
			Vertex* vertexNext = nodePtr->getVertex();
			if(vertexNext->getColor() == white)
			{
				vertexNext->setColor(gray);
				vertexNext->setDiscovery(vertexPtr->getDiscovery() + 1);
				vertexNext->setParent(vertexPtr);
				que.push(vertexNext);
			}
			nodePtr = nodePtr->getNextNode();
		}
	}
	return true;
}
bool Graph::dfs(int startVertex_in)
{
	reset();
	Vertex *vertexPtr = headVertex;
	int time = 0;

	cout<<"DFS results: ";

	while(vertexPtr != NULL)
	{
		if(vertexPtr->getVertexId() == startVertex_in)
		{
			dfsSub(vertexPtr, time);
			break;
		}
		vertexPtr = vertexPtr->getNextVertex();
	}
	if(vertexPtr == NULL)
		return false;
	//if the graph is a disconnected graph
	vertexPtr = headVertex;
	while(vertexPtr != NULL)
	{
		if(vertexPtr->getColor() == white)
		{
			dfsSub(vertexPtr, time);
		}
		vertexPtr = vertexPtr->getNextVertex();
	}
	cout<<endl;
	return true;
}

void Graph::dfsSub(Vertex* vertexPtr, int &time)
{
	if(vertexPtr->getColor() != white)
		return;
	vertexPtr->setColor(gray);
	time++;
	vertexPtr->setDiscovery(time);
	cout<<vertexPtr->getVertexId()<<" -> ";
	Node *nodePtr = vertexPtr->getHeadNode();
	while(nodePtr != NULL)
	{
		if((nodePtr->getVertex())->getColor() == white)
		{
			(nodePtr->getVertex())->setParent(vertexPtr);
			dfsSub(nodePtr->getVertex(), time);
		}
		nodePtr = nodePtr->getNextNode();
	}
	vertexPtr->setColor(black);
	time++;
	vertexPtr->setFinish(time);
	//toplolgical sort
	Vertex* vertexp = new Vertex(vertexPtr->getVertexId());
	if(topologicalSort == NULL)
	{
		this->topologicalSort = vertexp;
	}
	else
	{
		vertexp->setNextVertex(topologicalSort);
		this->topologicalSort = vertexp;
	}
	return;
}


void Graph::reset()
{
	Vertex* vertexPtr = headVertex;
	while(vertexPtr != NULL)
	{
		vertexPtr->setParent(NULL);
		vertexPtr->setColor(white);
		vertexPtr->setDiscovery(-1);
		vertexPtr->setFinish(-1);
		vertexPtr = vertexPtr->getNextVertex();
	}
}
void Graph::TopologicalSort()
{
	Vertex* vertexPtr = topologicalSort;
	cout<<"Toplolgical Sort:  ";
	while(vertexPtr != NULL)
	{
		cout<<vertexPtr->getVertexId()<<" -> ";
		vertexPtr = vertexPtr->getNextVertex();
	}
	cout<<endl;
}

void Graph::stronglyConnectCompents(int startVertex_in )
{
	cout<<"SCC results: \n";
	dfs(startVertex_in);
	exchangePointerForGT();
	Vertex* temp = GT;
	while(temp != NULL)
	{
		Node *nodePtr = temp->getHeadNode();
		while(nodePtr != NULL)
		{
			addEdge(nodePtr->getVertex()->getVertexId(),temp->getVertexId());
			nodePtr = nodePtr->getNextNode();
		}
		temp = temp->getNextVertex();
	}

	temp = topologicalSort;
	int time = 0;
	while(temp != NULL)
	{
		Vertex* vertexPtr = this->headVertex;
		while(vertexPtr != NULL)
		{
			if(vertexPtr->getVertexId() == temp->getVertexId()  && vertexPtr->getColor() == white)
			{
				dfsSub(vertexPtr, time);
				cout<<endl;
				break;
			}
			vertexPtr = vertexPtr->getNextVertex();
		}
		temp = temp->getNextVertex();
	}
	exchangePointerForGT();
}

void Graph::exchangePointerForGT()
{
	if(GT == NULL)
	{
		GT = headVertex;
		headVertex = NULL;
	}
	else
	{
		Vertex* temp = headVertex;
		headVertex = GT;
		GT = temp;
	}
}
