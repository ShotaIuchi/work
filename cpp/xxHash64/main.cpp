#include <cstdint>
#include <iostream>

// xxHash64 の1ラウンドを実行
constexpr uint64_t xxhash64_round(uint64_t acc, uint64_t input)
{
    // アキュムレータに入力値と定数を加算・乗算
    return (acc + input * 0x9E3779B185EBCA87ULL) * 0x9E3779B185EBCA87ULL;
}

// xxHash64を計算
constexpr uint64_t xxhash64(const char *data, size_t len, uint64_t seed = 0)
{
    // アキュムレータを長さとシードで初期化
    uint64_t acc = len * 0x9E3779B185EBCA87ULL + seed;
    size_t index = 0;

    // 8バイトずつ処理
    while (index + 8 <= len)
    {
        uint64_t input = 0;
        // 次の8バイトを1つの64ビット値に組み合わせる
        for (size_t i = 0; i < 8; ++i)
        {
            input |= static_cast<uint64_t>(data[index + i]) << (i * 8);
        }
        // 入力値でxxHash64の1ラウンドを実行
        acc = xxhash64_round(acc, input);
        index += 8;
    }

    // 残りのバイトを処理
    uint64_t input = 0;
    for (size_t i = 0; i < len % 8; ++i)
    {
        input |= static_cast<uint64_t>(data[index + i]) << (i * 8);
    }

    // 残りの入力値でxxHash64の1ラウンドを実行
    acc = xxhash64_round(acc, input);

    // アキュムレータをXORおよびシフトしてハッシュを最終化
    return acc ^ (acc >> 33);
}

int main()
{
    // 文字列 "Hello, World!" のxxHash64 をコンパイル時に計算
    constexpr auto hash_value = xxhash64("Hello, World!", 13);
    std::cout << "Hash value: " << hash_value << std::endl;
    return 0;
}
