#include <iostream>
int main()
{
    int sum = 0, x;
    for (int i = 0; i < 5; ++i)
    {
        std::cin >> x;
        sum += x;
    }
    std::cout << (sum / 5.0) << std::endl;
}
