//
// Created by Anastasiia Kravchenko on 06.05.2025.
//

auto isEven(int const n) -> bool {
    return n % 2 == 0;
}

auto isOdd(int const n) -> bool {
    return not isEven(n);
}

auto squared(int const n) -> int {
    return n * n;
}

auto squared(double const d) -> double {
    return d * d;
}