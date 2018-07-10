#include <iostream>
#include <unordered_map>
#include <maybe_ptr.h>

class Node
{
public:
  using dictionary_type = std::unordered_map<std::string, int>;
  // root node
  Node() :
    m_parent(nullptr),
    m_dict(make_owner<dictionary_type>())
  {}

  // node with parent
  Node(Node* parent) :
    m_parent(parent),
    m_dict(make_observer(parent->m_dict))
  {}

  bool has_parent() const
  {
    return m_parent != nullptr;
  }

  bool has_owning_dictionary() const
  {
    return m_dict.is_owning();
  }

private:
  Node* m_parent;
  maybe_ptr<dictionary_type> m_dict;
};

int main()
{
  Node root;
  Node child(&root);
  std::cout << not root.has_parent() << std::endl;
  std::cout << root.has_owning_dictionary() << std::endl;
  std::cout << child.has_parent() << std::endl;
  std::cout << not child.has_owning_dictionary() << std::endl;
  return 0;
}
