#include <fmt/base.h>

auto print() -> void {
    fmt::println("Hello");
}

auto print(bool const b) -> void {
    fmt::println("Boolean: {}", b);
}

auto print(int const n) -> void {
    fmt::println("Int: {}", n);
}

auto print(double const d) -> void {
    fmt::println("Double: {}", d);
}