#include "graph.hpp"
#include "pritree.cpp"
#include <set>
#include <iostream>
#include <queue>
using namespace std;
Node::Node()
{
	this->vertex = NULL;
	this->nextNode = NULL;
  this->fromId = -1;
  this->toId = -1;
}

Node::Node(const Node& node)
{
  this->vertex = node.vertex;
	this->nextNode = node.nextNode;
  this->fromId = node.fromId;
  this->toId = node.toId;
  this->weight = node.weight;
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

void Node::setFromId(const int fromId_in)
{
  this->fromId = fromId_in;
}
int Node::getFromId()const
{
  return this->fromId;
}
void Node::setToId(const int toId_in)
{
  this->toId = toId_in;
}
int Node::getToId()const
{
  return this->toId;
}

void Node::setWeight(const float weight_in)
{
  this->weight = weight_in;
}
float Node::getWeight()const
{
  return this->weight;
}

bool Node::operator>(Node& node_in)
{
  if(this->weight > node_in.weight)
    return true;
  return false;
}

bool Node::operator<(Node& node_in)
{
  if(this->weight < node_in.weight)
    return true;
  return false;
}

bool Node::operator==(Node& node_in)
{
  if(this->weight == node_in.weight)
    return true;
  return false;
}

void Node::operator=(const Node& node_in)
{
  this->weight = node_in.weight;
  this->fromId = node_in.fromId;
  this->toId = node_in.toId;
  this->vertex = node_in.vertex;
  this->nextNode = node_in.nextNode;
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
	this->Gtrans = NULL;
  vertexNumber = 0;
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

bool Graph::addEdge(int fromId, int toId,float weight_in)
{
	if(fromId == toId)
		return false;
	if(!addAllVertex(fromId, toId))
		return false;
	if(!addOneEdge(fromId,toId,weight_in))
		return false;
	if(graphType == undirected)
	{
		if(!addOneEdge(toId,fromId,weight_in))
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
    vertexNumber = 2;
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
      vertexNumber += 2;
			return true;
		}
		else if(fromVertex == NULL)
		{
			Vertex *newVertex1 = new Vertex(fromVertexId_in);
			preVertex->setNextVertex(newVertex1);
      vertexNumber++;
			return true;
		}
		else if(toVertex == NULL)
		{
			Vertex *newVertex1 = new Vertex(toVertexId_in);
			preVertex->setNextVertex(newVertex1);
      vertexNumber++;
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
bool Graph::addOneEdge(int fromVertexId_in, int toVertexId_in, float weight_in)
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
    newNode1->setWeight(weight_in);
    newNode1->setFromId(fromVertexId_in);
    newNode1->setToId(toVertexId_in);
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
	//dfs(startVertex_in);
	exchangePointerForGtrans();
	Vertex* temp = Gtrans;
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
	exchangePointerForGtrans();
}


void Graph::kruskal()
{
  cout<<"from     "<<"to\n";
  Pritree<Node> pritree;
	initial(pritree);
	while(this->list_set[0][0] < this->vertexNumber+1)
	{
		Node newNode = pritree.popHead();
		//posf是下标靠前的某一行的下标，post是下标靠后的某一行的下标，pos1和pos2是找到的
		int posf = -1, post = -1;
		find(newNode,posf, post);
		if(posf != post)
		{//如果这两个元素不再同一个集合中，那么合并这两个集合
			cout<<newNode.getFromId()<<"        "<<newNode.getToId()<<"            "<<endl;
			merge(posf,post);//合并两个集合
		}
	}

}

void Graph::prim(int startId)
{
  set<int> setInt;//这个集合用来存放已经被加进来的顶点
  setInt.insert(startId);
  cout<<"from     "<<"to        "<<"weigh\n";
  while(setInt.size() < this->vertexNumber)//until all vertexes add to setInt
  {
    Pritree<Node> pritree;
    for(set<int>::iterator it = setInt.begin(); it != setInt.end(); it++)
    {//把这个集合所有的割边都加进来
      Vertex* vertexPtr = this->headVertex;
      while(vertexPtr != NULL)
      {//先在顶点链表中找到set中的某个顶点
        if(vertexPtr->getVertexId() == (*it))
        {
          Node *nodePtr = vertexPtr->getHeadNode();
          while(nodePtr != NULL)
          {//然后再去看，这条边是不是割边，也就是看它指向的顶点是狗已经在setInt中了
						//如果这个顶点不再集合中，那么他就是一个待选顶点
            if(setInt.find(nodePtr->getToId()) == setInt.end())
            {//add cut edge to priority queue
              pritree.insert(*nodePtr);
            }
            nodePtr = nodePtr->getNextNode();
          }
          break;
        }
        vertexPtr = vertexPtr->getNextVertex();
      }
    }
    Node newNode = pritree.popHead();//弹出权值最小的边
    setInt.insert(newNode.getToId());//把这个边指向的顶点加进集合中
    cout<<newNode.getFromId()<<"        "<<newNode.getToId()<<"           "<<newNode.getWeight()<<endl;
  }
}



void Graph::exchangePointerForGtrans()
{
	if(Gtrans == NULL)
	{
		Gtrans = headVertex;
		headVertex = NULL;
	}
	else
	{
		Vertex* temp = headVertex;
		headVertex = Gtrans;
		Gtrans = temp;
	}
}

void Graph::initial(Pritree<Node>& pritree)
{
	int counter = 0;//position 0 store the length of the array.
	list_set = new int*[this->vertexNumber];
	Vertex* vertexPtr = this->headVertex;
  while(vertexPtr != NULL)
  {//add all the edge into priority queue
    Node *nodePtr = vertexPtr->getHeadNode();
  	while(nodePtr != NULL)
  	{
      pritree.insert(*nodePtr);
  		nodePtr = nodePtr->getNextNode();
  	}
		list_set[counter] = new int[2];
		list_set[counter][0] = 2;
		list_set[counter][1] = vertexPtr->getVertexId();
		counter++;
    vertexPtr  = vertexPtr->getNextVertex();
  }
}

void 	Graph::find(Node& newNode, int& posf, int& post)
{
	for(int count1 = 0;count1 < this->vertexNumber;count1++ )
	{
		for(int count2 = 1; list_set[count1] != NULL && count2 < list_set[count1][0]; count2++)
		{
			if(newNode.getFromId() == list_set[count1][count2])
			{
				posf = count1;
			}
			if(newNode.getToId() == list_set[count1][count2])
			{
				post = count1;
			}
		}
		if(posf >= 0 && post >= 0)
			return;
	}
}

void Graph::merge(int& posf, int& post)
{
	if(posf > post)
	{
		int temp = posf;
		posf = post;
		post = temp;
	}
	int *temp =new int[list_set[posf][0]];
	for(int counter = 0; counter < list_set[posf][0];counter++)
	{
		temp[counter] = list_set[posf][counter];
	}
	delete []list_set[posf];
	list_set[posf] = new int[temp[0] + list_set[post][0] -1];
	list_set[posf][0] = temp[0] + list_set[post][0] -1;
	for(int counter = 1; counter < temp[0];counter++)
	{
		list_set[posf][counter] = temp[counter];
	}
	for(int counter = 1;counter < list_set[post][0];counter++)
	{
		list_set[posf][counter +temp[0]-1] = list_set[post][counter];
	}
	delete[]list_set[post];
	list_set[post] = NULL;
	delete []temp;
}
