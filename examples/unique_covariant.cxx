#include <memory>
#include "maybe_ptr.h"

struct A
{
  explicit A(int x) : m_x(x) {}
  int m_x;
};

struct B : public A
{
  B(int x, int y) : A(x), m_y(y) {}
  int m_y;
};

int main()
{
  std::unique_ptr<B> b = std::make_unique<B>(1, 2);
  auto b_observer = make_observer<A>(b.get());
  auto b_owner = maybe_ptr<B>(std::move(b));
  maybe_ptr<A> a_owner = std::move(b_owner);
  return 0;
}
