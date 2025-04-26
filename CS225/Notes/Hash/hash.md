## Key Concept
Hash:将键不可逆映射为值($O(1)$)  
HashTable:将值作为坐标，把键存储在array中
1. Hash Function
2. array
3. collision resolution strategy

### Hash Function
1. hash: key->(int)
2. compression: modulation 限制值范围
#### Perfect Hash Function
1. Computation Time 
2. Deterministic:对一个键进行hash,值应相同
3. Satisfy the SUHA

#### SUHA: 
1. 对任意键，被值会均匀随机分布到值空间
2. 不同键哈希值不同

### Hash Table 
Collision handling
#### Open Hasing (Separate Chaining)
Linked list of every node  
把所有对应此键的值存到链表中  
$n$ 键空间 $N$ 值空间
load factor: $\alpha=\frac{n}{N}$  
Worst Case:  
Insert: $O(1)$  
Remove/Find: $O(n)$  
SUHA:  
Insert: $O(1)$  
Remove/Find: $O(\frac{n}{N})$
#### Closed Hashing (Probe-based)
如果此值已经被占用，存到下一个值  
容易产生值聚集  
解决方法: Double Hashing  
如果$h_1(k) + i \times h_2(k) \bmod p$已被占用,测试$h_1(k) + (i + 1) \times h_2(k) \bmod p$


Rehashing: 
空间扩大一倍，所有值中心计算插入