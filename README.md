## MIT 6.006

---

### LECTURE 1: ALGORITHM AND COMPUTATION
In this lecture, i revised the **big O notation**, where i know how to represent a algorithm by $\Theta$ or 
$O$ or $\Omega$.

*2023.09.11*

### ASSIGNMENT 0
I installed Latex and equipeed Vscode with it. I learned the grammar of Latex, which is a bit complex.

*2023.09.11*

### LECTURE 2: DATA STRUCTURE AND DYNAMIC ARRAYS
This lecture, i learned something new: 
- **Sequence Interface and Set Interface**: Interface ddefines a collection of operations (API or ADT), which gives me a new point of view.
- Amortized time, which is used by the `resize()` of dynamic-array.
I also revised three data structures: static-array, linked-list and dynamic-array.

*2023.09.11*

### LECTURE 3: SETS AND SORTING
I revised three sorts: selection sort, insertion sort and merge sort. I have a great impression on selection
sort and insertion sort now. Selection sort is implemented in *exercices/sorts.py*, which performs fewer swaps.
Insertion sort performs better when the data is basiclly sorted. There is a case related in Problem 2-2.

*2023.09.12*

### ASSIGNMENT 1
Calculate a bunch of time complexity and write a double-linked list, which is easy.

*2023.09.12*

### LECTURE 4:  HASHING
I learned how to prove the lower bound of a find operation based on **a comparative model** is $\Omega(log_2n)$.
I also touch a new way of choosing hash function: **Universal Hash**. The probability of collision can be 
controlled tight: $\mathop{Pr}_{h\in \mathbb{H}}\{h(k_i)=h(k_j)\}\le 1/m\quad \forall k_i\ne k_j\in \{0,...,u-1\}$

*2023.09.13*

### ASSIGNMENT 2
I learned how to draw a tree in Latex, which is hard though.

*2023.09.13*

### LECTURE 5: LINEAR SORTING
I learned bucket sort, count sort(which is a kind of bucket sort, but enable us to store replicated items) and
radix sort. This is fantastic. In a comparative model, the lower bound of sort is definitely $\Omega(nlogn)$.
But use these three sorts, time complexity reaches $O(n)$.

*2023.09.13*

---
#### Thinking
[为什么时效上具有明显优势的基数排序（radix sort）没有快速排序流行？--知乎](https://www.zhihu.com/question/27064078)
总的来说，基数排序对特定数据排序都是有优势的，如整数、字符串都可以基数排序，缺点就是**占用空间**（不稳定版本似乎不占额外空间）并且不好抽象，无法作为泛型算法。反观标准库算法：`std::sort()`就足够 General。

---
*2023.09.14*

### ASSIGNMEN 3
I learned how to draw a hash table in Latex. Be more familiar with Linear sorts.

*2023.09.14*

### LECTURE 6, 7: BINARY TREES, PART 1, PART 2: AVL
I have already learned. As consequence, nothing new here.

---

#### Thinking
[为什么STL和linux都使用红黑树作为平衡树的实现？ - 知乎](https://www.zhihu.com/question/20545708)

下面这段话是 Linux 内核为什么使用红黑树的原因：
> Red-black trees are similar to AVL trees, but provide faster real-time boundedworst case performance for insertion and deletion (at most two rotations andthree rotations, respectively, to balance the tree), with slightly slower(but still O(log n)) lookup time.

对于 Rust，它的 Set 是用 B树 维护的，这是很新颖的地方：
[为什么Rust 标准库的 TreeMap 采用 B 树实现，而不是常用的红黑树？ - 知乎](https://www.zhihu.com/question/516912481)

总的来说是因为 CPU 越来越快，而内存速度停滞不前。选取例如八叉树，能使一次装入更多东西到 Cache.
这里我的理解是原先比如数据库使用 B+树 作索引，是把 Memory 当 Destination，Disk 当 Source. 现在 Source 变成 Memory，而 Destination 变成 CPU Cache 

*2023.09.14*

---
### ASSIGNMENT 4
Sequence interface doesn't need to implement the sort semantic. So build a sequence AVL Tree is $O(n)$. Start to write a AVL Tree in C++. Introduce CMake and GTest in Windows10.

#### TODO:
1. ~~write an AVL Tree, which stores the int.~~ (*Done at 2023.09.15*)
2. ~~change it to be general~~ (*Done at 2023.09.16*)

[Why can templates only be implemented in the header file?](https://stackoverflow.com/a/16493574)
[模板类在.h中定义，在.cpp中实现 - 知乎](https://zhuanlan.zhihu.com/p/147623943)

*2023.09.15*

### LECTURE 8 BINARY HEAP
Nothing new.
*2023.09.15*

### LECTURE 9, 10, 11 BFS, DFS, WEIGHTED SHORTEST PATH
Pass, read the Note directly because i have already learned this part.
*2023.09.16*

---
#### Thinking
与写 C++ 不同，Python 的函数传参到底是如何进行的？这事关**正确性**以及**效率**，Python 的相关机制非常独特。

[Python: 函数参数是值传递还是引用传递? - 知乎](https://zhuanlan.zhihu.com/p/69746955)

---

### ASSIGNMENT 5
There are too much English, which is useless. So pass them directly.
*2023.09.17*

### LECTURE 12, 13 BELLMAN-FORD, DIJKSTRA
I have learned before. But there is something new.
1. The proof of all algorithms, which is hard to understand.
The proof of DIJKSTRA is strange, so i made **a little change**:

- $Q$ is the priority queue
- Want to prove: $d(s, v)=\delta(s, v)$ when vertex $v$ is removed from $Q$
- Base Case($k=1$): $s$ is the first vertex, $d(s, s) = 0$
- Inductive step: Assume true for $k<k'$, consider $k'$th vertex $v'$ removed from $Q$
- Consider the shortest path $\pi$ from $s$ to $v'$.
- Let$(x, v')$ be the last edge in $\pi$.
$$
d(s, v')\le d(s,x)+w(x, v')\quad (1)\\
=\delta(s,x')+w(x,v')\quad (2) \\
=\delta(s,v')\le d(s,v')\quad (3)
$$
(1): $x$ must be removed from $Q$. Ifnot, we can't use the edge$(x,v')$. When x was removed from $Q$, $d(s,x)=\delta(s,x)$ 
(2): subpath of shortest path is shortest path.

2. There are two versions of Bellman-Ford

*2023.09.17*

ASSIGNMENT 6, 7
pass, **do some leecode instead**.

### LECTURE 14-19
pass, which is DP. Do leetcode instead. 

---
END