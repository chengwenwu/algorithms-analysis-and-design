[实验代码（github)](https://github.com/chengwenwu/algorithms-analysis-and-design/tree/master/BFS-DFS--TPST-SCC)
# 一、实验内容
- 实现广度优先搜索（BFS）和深度优先搜索（DFS)
- 用下面的图进行测试
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190102185204546.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0MyNjgxNTk1ODU4,size_16,color_FFFFFF,t_70)
- 预期结果：
从1号顶点开始
BFS:1->5->2->4->3
DFS:1->5->2->3->4
# 二、理论准备
 - 简单图：没有重复边和自环的图。
 - 顶点诱导子图：顶点子集中的任何两个顶点之间都存在边。

## 1、BFS
BFS核心思想：
- 伪码中V[G]表示图G中的所有顶点，s表示BFS开始的顶点。
- color[u]表示顶点u的颜色，其中white表示没有访问过这个顶点，gray表示访问过了，但是还没有访问完成，black表示已经访问结束了。
- d[u]表示这个顶点距离起始顶点s的距离。
- $\pi$[u]表示这个顶点的父节点。
- Q是一个先进先出队列。
- Adj[u]表示U的所有邻居节点。
  - 伪码表示：
![在这里插入图片描述](https://img-blog.csdnimg.cn/2019010211481371.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0MyNjgxNTk1ODU4,size_16,color_FFFFFF,t_70)
- 解读伪码：
    - 首先是初始化，把每个顶点的color都设置成white，与原点的距离d设置成无穷，父节点$\pi$设置为空。
    - 然后把原点s的color设为gray，距离d设为0，父节点$\pi$设为空，并加进队列Q中。
    - 然后进入循环。
    - 循环中队列Q的头部u出队，然后访问与它相邻的节点，并且如果这个节点没有被访问过（color为white)那么，把它的color标记为gray（表示已经访问过了），把它的父节点$\pi$设为u,距离d设为它父节点u的距离加一，并把它入队。
    - 最后在把已经弹出的队头的color设为black，说明已经处理结束。

## 2、DFS
- 伪码表示：
这里面的符号表示和BFS中是相同的，下面的算法用了递归的方法实现，当然也可以用栈来实现。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190102120316366.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0MyNjgxNTk1ODU4,size_16,color_FFFFFF,t_70)
- 解读伪码：
    - 这个伪码写的不是很规范，没有指明要从哪个节点开始，所以我们假设他就从节点链表的第一个节点开始。
    - 首先是初始化各个节点，颜色color设为白色white,父节点$\pi$设为空null，开始时间time设为0.
    - 然后进入循环开始DFS过程，首先查看这个节点是否被访问过（color是否是白色white，若是则没有访问过），如果没有访问过，那么就访问它，具体访问过程在DFS-VISIT()函数中。
    - 下面我们来看下DFS是如何访问一个节点的，首先把它的颜色color设置为灰色gray,然后设置它的发现时间d，设置为当前时间加一，同时当前时间time也加一。然后再看与它相邻的某一个节点，如果是白色的用相同地方式去访问它（开始递归）
    - 递归过程： 然后一直找该节点的下一个相邻节点，直到最后某个节点它的所有相邻节点都被访问过，就开始回退，回退时把该节点的完成使时间设置为time，同时time加一，颜色设置为黑色，表示处理已经结束。一直回退直到完成最先访问的那个节点。
# 三、实验环境
- windows10
- g++命令行编译器
- c++语言
# 四、实验过程
- 代码我已经发到[github](https://github.com/chengwenwu/algorithms-analysis-and-design/tree/master/bfsdfs)上了
- 文件依赖：
   - graph.h里面声明了各个类。
   - graph.cpp里面实现了各个类。
   - main.cpp中是构建了一个图，并调用了相关算法。 
## 1、代码架构：
  - Node类，这个类名起的有点尴尬，它表示的是边，本来给它起个Edge这样的名字可能会比较好，但是一开始他就是链表中的一个节点，所以直接就node了。它有两个私有变量Vertex和nextNode。vertex是它指向的那个顶点，nextNode是下一个Node。这样写的目的是，一个节点，从它出发可能会有不止一条边，所以我们把所有从它出发能够到达的节点就用一个链表保存下来。
   

```cpp
Vertex* vertex;
Node* nextNode;
```
   - Vertex类是表示节点，它的私有变量比较多,具体如下。
```cpp
int vertexId;//顶点的唯一标识符
	Vertex* nextVertex;//把所有顶点放在一个链表中，这个指针指向它的下一个顶点
	Node* headNode;//这里存放与它相邻的顶点
	Vertex* parent;//这里存放它的父节点
	Color color;//这是它的颜色
	int discovery;//这是它的发现时间（DFS中）
	int finish;//这是它的完成时间（BFS中）
```
- 然后就是最大的类Graph,

```cpp
Vertex* headVertex;//这里存放它的所有顶点
TypeOfGraph graphType;//这里存放这个图是有向图还是无向图
Vertex* topologicalSort;//这里存放的是拓扑排序的结果
Vertex* GT;//这里存放把所有边反向后的结果，主要用在求解强连通图的过程中。
```
- 好了代码架构就说到这里了。然后各个类里面的方法无非就是get和set来设置或者获取一些属性。
- Graph里面的`bool addEdge(int fromId, int toId);`方法是在途中加入一个边，fromId是起始顶点的Id，toId是到达顶点的Id，如果这是有向图就添加这一条边。如果是无向图，那么这一次操作会把它的toId到fromId的边也添加进去。
- `void reset();`这个函数负责把所有顶点的父节点，颜色，发现时间，结束时间等等进行初始化。
 - 然后还有两个函数,是私有的，功能在注释中也讲清楚了。
- 其他的函数都是相关算法函数，都是按照伪码来实现的。
```cpp
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
```

# 五、实验结果
- 由于这次关于图的前几个作业都是在同一个框架下完成的，所以忽略后面拓扑排序和强连通图的相关内容。
- 结果如图：
![在这里插入图片描述](https://img-blog.csdnimg.cn/2019010218545861.png)
# 六、实验总结
- 实验好久之前做完了，赶在期末考试补写实验报告，都不知道写啥了，感觉自己把这个弄得有点复杂，但是做出来结果了，只能说还可以吧，就这样了，后面几个实验还没做完，那几个实验边做边写实验报告，感想写完整一些吧。
