## Analysis
每个node有$[\lceil \frac{m}{2} \rceil,m]$个儿子，存贮$[\lceil \frac{m}{2} - 1 \rceil, m - 1]$个元素  
根节点子树数量 $[2, m]$  
树高$O(log_mn)$
### 根据给出的树判断m
通过树的子树和元素个数限制$m$上下界
### n 和 h 关系
$n$ 表示节点数 $h$ 表示树高 $cnt_k$ 表示元素数量, $t$ 表示下一层元素和上层子树数量的比值  
$$n = 1 + 2 \frac{t^h - 1}{t - 1}$$
$$cnt_k = n \times (t - 1) = 1 + 2 (t^h - 1) = 2t^h-1$$ 
$$cnt_k \geq 2 \lceil \frac{m}{2} \rceil ^ h - 1, \log_{\lceil \frac{m}{2} \rceil} \frac{n + 1}{2} \geq h$$ 