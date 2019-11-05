#include <iostream>
#include <deque>
#include <vector>

template<typename T, std::size_t N>
constexpr std::size_t f(T(&)[N]) noexcept {
    return N;
};

template<typename Container, typename Index>
decltype(auto) authAndAccess(Container &&c, Index i) {
    return std::forward<Container>(c)[i];
}
template<typename T>	//只对TD进行声明
class TD;
int main() {
    std::cout << "Hello, World!" << std::endl;
    int a[] = {1, 3, 5, 7, 8, 9};
    std::cout << f(a);
    std::deque<int> d;
    authAndAccess(std::move(d), 5) = 10;
    const int theAnswer = 42;
    std::vector b{1,2,3,4};
    auto y = &theAnswer;

    std::vector<std::string> createVec();

    const auto vw = createVec();


    TD<decltype(vw)> xTy pe;	//引出错误消息
    TD<decltype(y)> yType;	//x和y的类型
    return 0;
}
decltype(auto) f1()
{
    int x = 0;
    return x;           //decltype(x）是int，所以f1返回int
}

decltype(auto) f2()
{
    int x =0l;
    return (x);         //decltype((x))是int&，所以f2返回int&
}