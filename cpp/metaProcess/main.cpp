#include <concepts>
#include <iostream>
#include <tuple>
#include <type_traits>

// テンプレート関数を反復処理する
// Ts       : 型リスト   (int, double, float, ...)
// Is       : 型IDリスト（0, 1, 2, ...)
// Func     : 反復処理する関数型
// 1st      : 型リスト   (std::tuple<int, double, float, ...>）
// 2nd      : 型IDリスト（std::index_sequence<0, 1, 2, ...>）
// func     : 反復処理する関数
template <typename... Ts, std::size_t... Is, typename Func>
void processTypeList(const std::tuple<Ts...>, std::index_sequence<Is...>, const Func &func)
{
    (..., func(std::tuple_element_t<Is, std::tuple<Ts...>>{}));
}

// テンプレート関数を反復処理する
// Ts       : 型リスト (int, double, float, ...)
// Func     : 反復処理する関数型
// typeList : 型リスト (std::tuple<int, double, float, ...>)
// func     : 反復処理する関数
template <typename... Ts, typename Func>
void processTypeList(const std::tuple<Ts...> typeList, const Func &func)
{
    processTypeList(typeList, std::index_sequence_for<Ts...>{}, func);
}

// テンプレート関数を反復処理する
// Ts       : 型リスト (int, double, float, ...)
// Func     : 反復処理する関数型
// func     : 反復処理する関数
template <typename... Ts, typename Func>
void processTypeList(const Func &func)
{
    processTypeList(std::tuple<Ts...>{}, std::index_sequence_for<Ts...>{}, func);
}

////////////////////////////////////////////////////////////////////////////////////////
/// sample /////////////////////////////////////////////////////////////////////////////
template <class T>
void hoge()
{
    std::cout << typeid(T).name() << std::endl;
}

int main()
{
    processTypeList<int, double, short, int>([](const auto type)
                                             { hoge<decltype(type)>(); });

    std::cout << "--------------------" << std::endl;
    const std::tuple<int, double, short, int> typeList{};
    processTypeList(typeList, [](const auto type)
                    { hoge<decltype(type)>(); });
}