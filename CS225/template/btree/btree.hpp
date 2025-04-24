#include <algorithm>
#include <vector>
template<typename T>
class btree
{
public:
  class bNode
  {
  public:
    bNode(int m, bNode* fa)
    {
      dataBlock.resize(m - 1);
      children.resize(m);
      _fa = fa;
      bool leaf = true;
      _siz = 0;
    }
    std::vector<T> dataBlock;
    std::vector<bNode*> children;
    bNode* _fa;
    int _siz;
    bool leaf;
  };
  btree(int m);
  void insert(T key, bNode* cur);
  bNode find();
private:
  void split(bNode* cur);
  void insertVal(bNode* cur, T key, bNode* newNode);
  bNode* root;
  int m;
};

template<typename T>
void btree<T>::insert(T key, bNode* cur)
{
  int idx = std::upper_bound(cur->dataBlock.begin(), cur->dataBlock.end(), key) - cur->dataBlock.begin();
  if (cur->leaf)
  {
    split(cur);
    cur->dataBlock.insert(idx, key);
    cur->children.insert(idx + 1, nullptr);
    cur->_siz += 1;
  }
  insert(key, cur->children[idx]);
  split(cur);
}
template<typename T>
void btree<T>::split(bNode* cur)
{
  if (cur->_siz < m - 1)
    return;
  int mid = (m - 1) / 2; 
  bNode* leftNode = new bNode(m), rightNode = new bNode(m);
  for (int i = mid; i < m - 1; ++i)
    rightNode.dataBlock.push_back(cur->dataBlock[i]);
  for (int i = mid; i < m; ++i)
    cur->dataBlock.pop_back();
  for (int i = mid; i < m; ++i)
    rightNode.children.push_back(cur->children[i]);
  for (int i = mid; i < m; ++i)
    cur->children.pop_back();
}