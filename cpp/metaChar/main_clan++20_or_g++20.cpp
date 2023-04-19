// clan++ -std=c++20 main_clan++20_or_g++20.cpp
// g++ -std=c++20 main_clan++20_or_g++20.cpp

#include <iostream>
#include <functional>

template<char... Chars>
struct String {
    static constexpr char value[] = {Chars..., '\0'};
};

template<typename T, T... Chars>
constexpr String<Chars...> operator""_s() {
    return {};
}

////////////////////////////////////////////////////////////////////////////////////////
/// sample /////////////////////////////////////////////////////////////////////////////
template <typename Str>
struct Sample
{
    void print() const
    {
        std::cout << Str::value << std::endl;
    }
};

int main()
{
    using MyStr = decltype("AAA"_s);
    const Sample<MyStr> sample{};
    sample.print();
    return 0;
}
