#include "maybe_ptr.h"
#include <iostream>


class A
{
public:
  A(int x) : m_x(std::make_unique<int>(x)) {}

private:
  std::unique_ptr<int> m_x;

};

int main()
{
  A a(5);
  maybe_ptr<int> p;
  std::cout << (p == nullptr) << std::endl;
  maybe_ptr<int> q(std::make_unique<int>(42));
  std::cout << q.is_owning() << std::endl;
  p.reset(q.get());
  std::cout << q.is_owning() << std::endl;
  std::cout << not p.is_owning() << std::endl;
  return 0;
}
