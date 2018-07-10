#include <iostream>
#include <maybe_ptr.h>

int main()
{
  auto owner = make_owner<int>(42);
  auto observer = make_observer(owner);
  std::cout << "initial " << *owner << " " << *observer << std::endl;
  *owner = 12;
  std::cout << "affected owner " << *owner << " " << *observer << std::endl;
  *observer = 6;
  std::cout << "affected observer " << *owner << " " << *observer << std::endl;
  auto copied_owner = to_owner(observer);
  std::cout << "added copied_owner " << *owner << " " << *observer << " " << *copied_owner << std::endl;
  *owner = 42;
  std::cout << "affected owner " << *owner << " " << *observer << " " << *copied_owner << std::endl;
  *copied_owner = 0;
  std::cout << "affected copied_owner " << *owner << " " << *observer << " " << *copied_owner << std::endl;
  into_owner(observer);
  std::cout << "changed observer into owner " << *owner << " " << *observer << " " << *copied_owner << std::endl;
  *owner = 12;
  std::cout << "affected owner " << *owner << " " << *observer << " " << *copied_owner << std::endl;
  *observer = 6;
  std::cout << "affected observer " << *owner << " " << *observer << " " << *copied_owner << std::endl;

  return 0;
}
