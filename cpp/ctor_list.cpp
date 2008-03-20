#include <iostream>
#include <list>

class Drept
{
public:
  double stuff;
  double aria(){return 0.0;} //for testing purposes only
};

int main(void)
{
  std::cout << "here in main." << std::endl;

  std::list<Drept> elem;
  Drept d;

  elem.push_back(d);

  std::cout << "elem.size() == " << elem.size() << std::endl;

  return 0;
}
