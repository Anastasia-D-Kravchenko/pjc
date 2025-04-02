// // //
// // // Created by Anastasiia Kravchenko on 07.03.2025.
// // //
// //
// // #include <algorithm>
// // #include <iostream>
// // #include <vector>
// // #include <string>
// //
// // void printStringView(std::string_view sv) {
// //     std::cout << "String view: " << sv << std::endl;
// // }
// //
// // // void printSpan(std::span<int> sp) {
// // //     std::cout << "Span: ";
// // //     for (int value : sp) {
// // //         std::cout << value << " ";
// // //     }
// // //     std::cout << std::endl;
// // // }
// //
// //
// // int main() {
// //     std::cout << "hello world\n";
// //     /*
// //             int x;
// //             double y;
// //             std::string s;
// //             std::cin >> x;
// //             std::cin >> y;
// //             std::cin >> s;
// //         //    std::cout << "[" << x << "]";
// //
// //             std::cout << x << ' ' << y << ' ' << s;*/
// //
// //     //    int x = 0;
// //     //    auto x = int();
// //     //    auto x = 0;
// //     //    auto x = 17;
// //     //    for (int i = 0; i < 10; i++) { }
// //     //    std::cout << x;
// //     //    for (int i = 0; i < 10; i++) { }
// //
// //     //    auto a = 0;
// //     //    auto b = 0;
// //     //    std::cin >> a >> b;
// //
// //     //    auto text = std::string();
// //     auto text = std::string();
// //     std::cin >> text;
// //     std::cout << text << std::endl;
// //     //    auto numbers = std::vector<int>();
// //     //
// //     auto str = std::vector<std::string>();
// //     str.push_back("hello world");
// //     str.push_back("hello");
// //     str.push_back("world");
// //     for (auto i : str) std::cout << i << std::endl;
// //     str.pop_back();
// //     for (auto i : str) std::cout << i << std::endl;
// //     //    numbers.push_back(3);
// //     //    numbers.push_back(7);
// //     //    numbers.push_back(1);
// //     //
// //     //    for (auto element : numbers) {
// //     //        std::cout << element << ' ';
// //     //    }
// //     //
// //     //    numbers.pop_back();
// //     //
// //     //    std::cout << '\n';
// //     //    for (auto element : numbers) {
// //     //        std::cout << element << ' ';
// //     //    }
// //     auto hi = int(4);
// //     switch (hi) {
// //         case 4: std::cout << "hi\n"; break;
// //         default: std::cout << "hi"; return 0;
// //     }
// //
// //     /*auto nums = std::vector<int>{1, 2, 3, 5, 12, 54, 6, 2, 46, 3, 2, 6, 7, 7};
// //     std::ranges::sort(nums);
// //
// //     for (auto element : nums) {
// //         std::cout << element << ' ';
// //     }*/
// //     std::string text1 = "long sentance with some meaning";
// //     for (auto i = 0; i < text1.size(); i++) std::cout << text1[i];
// //     std::cout << std::endl;
// //     for (auto i : text1) std::cout << i;
// //     std::cout << std::endl;
// //     std::vector<char> rev;
// //     for (int i = text1.size() - 1; i >= 0; i--) rev.push_back(text1[i]);
// //     for (auto i : rev) std::cout << i;
// //     std::cout << std::endl;
// //
// //
// //     text = std::string();
// //     auto first  = std::string("Programming");
// //     auto second = std::string("in");
// //     auto third  = std::string("C++");
// //     auto fourth = std::string(", Python");
// //     for (auto chr : first) text += chr;
// //     text += ' ';
// //     for (auto chr : second) text += chr;
// //     text += ' ';
// //     for (auto chr : third) text += chr;
// //     text += fourth;
// //     std::cout << text;
// //
// //
// //     text = std::string("Programming");
// //     std::cout << "kg stands for kilo" << text.substr(3, 4) << std::endl;
// //     //    auto s1 = std::string("hello");
// //     //    std::ranges::reverse(s1);
// //     //    auto s2 = std::string();
// //     //
// //     //    std::cin >> s2;
// //     //
// //     //    if (s1 < s2) {
// //     //        std::cout << ":>";
// //     //    }
// //     //
// //     auto vec = std::vector<int>{3, 5, 1, 4, 2};
// //
// //     std::ranges::reverse(vec);
// //
// //     for (auto element : vec) {
// //         std::cout << element << ' ';
// //     }
// //     //    auto words = std::vector<std::string>{"hello", "everyone", "present"};
// //     //    std::ranges::sort(words);
// //     //
// //     //    for (auto word : words) std::cout << word << ' ';
// //
// //     //    std::cout << words;
// //
// //     //    auto const x = 0;
// //     //    x = 10;
// //
// //     std::string myString = "Hello, string view!";
// //     printStringView(myString); // No copy is made
// //     const char* cString = "C-style string";
// //     printStringView(cString); // Works with C-style strings too
// //
// //
// //     // auto myVector = std::vector<int>{1, 2, 3, 4, 5};
// //     // printSpan(myVector);
// //     // int myArray[] = {10, 20, 30};
// //     // printSpan(myArray);
// // }
//
// //
// // Created by Anastasiia Kravchenko on 14.03.2025.
// //
// #include <iostream>
// #include <vector>
// #include <string>
// #include <ranges>
//
// int main() {
//     auto const word = std::string("hello");
//     auto text = word.back() + word + word.front(); // ohelloh
//     std::ranges::sort(text); // abcdefghigknlmoprt => ehhlloo
//     std::cout << text << "\n";
//     std::cout << word.size() << "\n"; // 5
//
//     auto str = std::vector<std::string>(3);
//     for ( int i = 0; i < 3; i++) {
//         std::cin >> str[i];
//     }
//     auto sorted = std::ranges::sort(str);
//     auto bol =
//     for ( int i = 0; i < 3; i++) {
//         if ( sorted[i] != str[i] ) {
//             std::cout << "%";
//         }else std::cout << "#";
//     }
// }

#include <iostream>
#include <vector>
#include <set>
#include <fmt/ranges.h>

// auto printhi() -> void {
//     fmt::print("Hello world!\n");
// }
// auto modify(int& x) -> void {
//     x += 3;
// }
//
// namespace std {
//     auto cou1(int x) -> void {
//         fmt::print("{}", x);
//     }
// }
// namespace pjc {
//     // auto sayHello() -> void {
//     //     fmt::print("Hello world!\n");
//     // }
//
//     auto sayHello() -> void {
//         fmt::println("Hello!");
//     }
// }
#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
// auto dotProduct(std::vector<double> const& v1, std::vector<double> const& v2) {
//     int count = 0;
//     for ( int i = 0; i < v1.size(); i++ ) {
//         count += v1[i] * v2[i];
//     }
//     return count;
// }

// bool suffix(const std::set<int>& s, const std::vector<int>& v) {
//     auto starts = --s.end();
//     auto startv = --v.end();
//     int count = 0;
//     for ( int i = 0; i < v.size(); i++ ) {
//         if ( *starts == *startv ) {
//             count++;
//         }
//         --starts;
//         --startv;
//     }
//     return count == v.size();
// }

// auto isPalindrome(std::string s) -> bool {
//     auto s1 = s;
//     std::ranges::reverse(s);
//     if (s1 == s) {
//         return true;
//     }
// }

// auto sortBiggerHalf(std::vector<int> & x, int y) {
//     if ( y == 0) {
//         std::ranges::sort(x.begin(), x.begin() + x.size()/2);
//     }else if (y == 1) {
//         std::ranges::sort(x.begin() + x.size()/2, x.end());
//     }else {
//         std::ranges::sort(x);
//     }
// }

// namespace v1 {
//     auto printLongestString(std::vector<std::string> a) {
//         std::cout << std::ranges::max(a, [](std::string x, std::string y){return x.size() < y.size();}) << std::endl;
//     }
// }
// namespace v2 {
//     auto printLongestString(std::vector<std::string> a) {
//         std::cout << *std::ranges::max_element(a,[](std::string x, std::string y){return x.size() < y.size();}) << std::endl;
//     }
// }
// namespace v3 {
//     auto printLongestString(std::vector<std::string> a) {
//         std::cout <<  std::ranges::min(a,[](std::string x, std::string y){return x.size() < y.size();}) << std::endl;
//     }
// }
// namespace v4 {
//     auto printLongestString(std::vector<std::string> a) {
//         std::cout << *std::ranges::min_element(a,[](std::string x, std::string y){return x.size() < y.size();}) << std::endl;
//     }
// }

// auto reduceAdjacentWhitespaces(std::string x) {
//     std::string modstr = "";
//     bool last_was_space = false;
//     for ( auto c : x) {
//         if (std::isspace(c)) {
//             if (!last_was_space) {
//                 modstr += ' ';
//             }
//             last_was_space = true;
//         }else {
//             modstr += c;
//             last_was_space = false;
//         }
//     }
//     return modstr;
// }

auto main() -> int {

//     auto iter = std::vector<std::string>{"hello", "world"};
//     // auto start = iter.begin();
//     auto end = iter.end();
//     end--;
//     std::cout << *end << std::endl;
//
//     auto vec = std::vector<int>{3, 5, 1, 4, 2, 0};
//
//     auto middle = vec.begin() + vec.size()/2;
//
//     std::ranges::reverse(++middle, vec.end());
//
//     for (auto n : vec) {
//         std::cout << n << ' ';
//     }
//     std::cout << std::endl;
//
//     std::cout << *vec.begin() << std::endl;
//     auto first = vec.begin() + 1;
//     std::cout << *vec.begin() << std::endl;
//     auto last = vec.begin() + 4;
//     std::cout << *first << ' ' << *last << '\n';
//
//     auto vec = std::vector<int>{11, 22, 33, 22, 33, 11};
//     auto middle = vec.begin() + vec.size()/2;
//     std::ranges::sort(middle, vec.end());
//
//     std::cout << std::ranges::equal(vec.begin(), middle, middle, vec.end());
//     std::cout << std::endl;
//
//     for ( auto i = vec.begin(); i != vec.end(); i++) {
//         std::cout << *i << " ";
//     }
//     std::cout << std::endl;
//
//     auto setik = std::set<int>();
//     for (auto i : {1,2,3,4,5,6,7,8,9,9,8,7,6,5,4,3,2,1,0}) {
//         setik.insert(i);
//     }
//     for (auto i : setik) {
//         std::cout << i << " ";
//     }
//     std::cout << std::endl;
//
//     auto Uniqeset = std::set<int>{1,2,3,4,5,6,7,8,9,9,8,7,6,5,4,3,2,1,0};
//     auto Uniqevec = std::vector<int>();
//     for (auto i : Uniqeset) {
//         std::cout << i << " ";
//         Uniqevec.emplace_back(i);
//     }
//     std::cout << std::endl;
//     for (auto i : Uniqevec) {
//         std::cout << i << " ";
//     }
//     std::cout << std::endl;
//
//     auto uniqevec = std::vector<int>(5,1);
//     auto dub = std::ranges::unique(uniqevec);
//     for (auto i : dub) {
//         std::cout << i << " ";
//     }
//     std::cout << std::endl;
//     uniqevec.erase(dub.begin(),dub.end());
//     // uniqevec.erase(uniqevec.begin(),uniqevec.end());
//     if (uniqevec.empty()) {
//         std::cout << "nothing" << std::endl;
//     }
//     for (auto i : uniqevec) {
//         std::cout << i << " ";
//     }
//
//     auto numbers = std::vector<int>{1, 2, 3, 1, 2, 3, 1, 2, 3};
//
//     std::ranges::sort(numbers);
//     auto duplicates = std::ranges::unique(numbers);
//
//     numbers.erase(duplicates.begin(), duplicates.end());
//
//     std::cout << std::endl;
//     for (auto element : numbers) {
//         std::cout << element << ' ';
//     }
//     std::cout << std::endl;
//
//     fmt::println("{}", numbers);
//
//     // numbers.erase(numbers.end()); // will work
//
//     fmt::print("{}", numbers);
//     fmt::print("{}", numbers);
//     std::cout << std::endl;
//
//     auto vector = std::vector<int>{1, 2, 3};
//     auto set    = std::set<int>{1, 2, 3};
//
//     fmt::println("{}", vector);
//     fmt::println("{}", set);
//     fmt::println("{}", vector);
//     fmt::println("[{}]", fmt::join(set, ", "));
//     fmt::println("The answer to ur question is {}", 3);
//
//     // fmt::format_string<> x = "5";
//     // fmt::println(x);
//
//     auto x = 5;
//     fmt::println("{}", x);
//
//     printhi();
//
//     modify(x);
//     fmt::println("{}", x);
//
//     auto vec = std::vector<int>{1, 1, 3};
//     fmt::println("{}", fmt::join(vec, " "));
//
//     std::cou1(5);
//     pjc::sayHello();
//
//     auto const find = std::ranges::find(vec, 1);
//     auto find2 = *find != 1;
//     fmt::println("{}", *find);
//
//     auto const numbers = std::vector<int>{3, 5, 1, 4, 2};
//
//     auto const iter = std::ranges::find(numbers, 9);
//
//     auto const present = iter != numbers.end();
//
//     if (present) {
//         fmt::println("{}", *iter);
//     } else {
//         fmt::println("No such element");
//     }
//
//     auto numbers = std::vector<int>(21);
//
//     for (auto i = 0; i < numbers.size(); i++) {
//         std::cin >> numbers[i];
//     }
//
//     auto zeroCounter = 0;
//
//     for (auto start = numbers.begin(); start != numbers.end(); start += 3) {
//         auto end = start + 3;
//
//         auto const iterToZero = std::ranges::find(start, end, 0);
//         auto range = std::ranges::subrange(start, end);
//         for ( auto i : range) {
//             std::cout << i << " ";
//         }
//         std::cout << std::endl;
//
//         if (iterToZero != end) {
//             zeroCounter += 1;
//         }
//     }
//
//     fmt::println("There were {} groups with zeros", zeroCounter);
//
//
//     auto numbers = std::vector<int>{11, 1, 1111, 111};
//
//     auto const maxNumber = std::ranges::max(numbers);
//     auto const maxIter   = std::ranges::max_element(numbers);
//
//     auto const minNumber = std::ranges::min(numbers);
//     auto const minIter   = std::ranges::min_element(numbers);
//
//     fmt::println(
//             "min: {}\nmax: {}\nminElement: {}\nmaxElement: {}",
//             minNumber, maxNumber,
//             *minIter, *maxIter
//     );
//
//     fmt::println("{}", numbers);
//     std::ranges::swap(*maxIter, *minIter);
//     // std::ranges::iter_swap(maxIter, minIter);
//     fmt::println("{}", numbers);
//
//     std::ranges::sort(numbers);
//     fmt::println("{}", numbers);
//
//
//     auto words = std::vector<std::string>{"w2", "w103", "w101", "w1020", "w105", "w7", "w303", "w4"};
//     std::ranges::sort(words, std::ranges::greater());
//     std::ranges::sort(words, std::ranges::greater(), std::ranges::size);
//     fmt::println("{}", words);
//
//
//     auto lamb = [](int x)->void{std::cout << x << '\n';};
//     lamb(3);
//
//     auto words = std::vector<std::string>{
//         "hello", "there", "and", "welcome"
// };
//
//     std::ranges::sort(words, std::ranges::less(), [](std::string const& s) {
//         return s.size();
//     });
//
//     fmt::println("{}", words);
//
//     std::ranges::sort(words, std::ranges::greater(), [](std::string const& s) {
//         return s.size();
//     });
//
//     fmt::println("{}", words);
//
//     auto words = std::vector<std::string>{
//         "hello", "there", "and", "welcome"
// };
//
//     auto const capitalize = [](std::string copy) {
//         auto const differenceBetweenLowerAndUpperCase = 'a' - 'A';
//         copy.front() -= differenceBetweenLowerAndUpperCase;
//         return copy;
//     };
//
//     fmt::println("{}", words);
//     std::ranges::transform(words, words.begin()+1, capitalize);
//     fmt::println("{}", words);
//
//     std::vector<int> data = {5, 2, 8, 1, 9, 3, 7, 4, 6};
//     auto min_it = std::ranges::min_element(data);
//     auto max_it = std::ranges::max_element(data);
//
//     if (min_it != data.end() && max_it != data.end()) {
//         std::ranges::iter_swap(min_it, max_it);
//     }
//
//     for (int val : data) {
//         std::cout << val << " ";
//     }
//     std::cout << std::endl;
//     return 0;
//
//
//     std::vector<int> numbers = {3, 1, 4, 1, 5, 9, 2, 6};
//     auto maxIter = std::ranges::max_element(numbers);
//     auto minIter = std::ranges::min_element(numbers);
//
//     std::cout << "Before swap: max = " << *maxIter << ", min = " << *minIter << std::endl;
//
//     std::ranges::iter_swap(maxIter, minIter);
//
//     std::cout << "After swap: max = " << *maxIter << ", min = " << *minIter << std::endl;
//     std::cout << "Vector after swap: ";
//     for (int num : numbers) {
//         std::cout << num << " ";
//     }
//     std::cout << std::endl;
//
//     std::vector<int> data = {5, 2, 8, 1, 9, 3, 7, 4, 6};
//     auto has = std::ranges::find_if(data, [](int x){return x > 10;});
//     std::cout << (has==data.end()?"hasn't":"has");
//
//
//     std::vector<int> data = {5, 2, 8, 1, 9, 3, 7, 4, 6};
//     auto has = std::ranges::find_if(data, [](int x) {
//         if (x > 10) {
//             return -1;
//         }
//         return 0;
//     });
//     std::cout << (has==data.end()?"hasn't":"has");
//
//     std::vector<std::string> words = {"apple", "banana", "kiwi", "orange", "grape"};
//     std::ranges::sort(words, std::ranges::greater(), [](const std::string& s) { return s.size(); });
//     for (const auto& word : words) {
//         std::cout << word << " ";
//     }
//     std::cout << std::endl;
//     std::vector<int> data = {5, 2, 8, 1, 9, 3, 7, 4, 6};
//     int mi = 0;
//     std::cin >> mi;
//     std::cout << ((std::ranges::find(data, mi) != data.end()) ? "all good" : "not good");
//
//     std::vector<int> data = {5, 2, 8, 1, 9, 3, 7, 4, 6};
//     auto max_value = std::ranges::max(data);
//     std::cout << max_value << std::endl;

    // auto all = std::vector<int>(7);
    // for ( int i = 0; i < 7; ++i ) {
    //     std::cin >> all[i];
    // }
    // // std::ranges::sort(all);
    // // auto start = all.begin();
    // // all.erase(start);
    // // auto end = all.end()-1;
    // // all.erase(end);
    // // fmt::print("{}", all);
    // all.erase(std::ranges::min_element(all));
    // all.erase(std::ranges::max_element(all));
    // fmt::print("{}\n", all);

    // std::vector<double> v1 = {1.0, 2.0, 3.0};
    // std::vector<double> v2 = {4.0, 5.0, 6.0};
    // std::cout << dotProduct(v1, v2) << std::endl;

    // auto mass = std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    // for ( int i = 0; i < mass.size(); i++ ) {
    //     if ( i % 2 == 0 ) {
    //         std::cout << mass[i] << std::endl;
    //     }
    // }

    // std::set<int> s1 = {1, 2, 3, 4, 5, 6, 7};
    // std::vector<int> v1 = {5, 6, 7};
    // std::cout << "v1 is a suffix of s1: " << (suffix(s1, v1) ? "true" : "false") << std::endl;

   //  fmt::println(
   //         "{}\n{}\n{}",
   //         isPalindrome("KajaK"),
   //         isPalindrome("ala"),
   //         isPalindrome("programowanie")
   // );

    // auto firstHalfBigger  = std::vector<int>{3, 2, 1, 0, 1, 0};
    // auto secondHalfBigger = std::vector<int>{3, 2, 1, 6, 5, 4};
    // auto bothHalvesSame   = std::vector<int>{5, 4, 5, 4};
    //
    // sortBiggerHalf(firstHalfBigger, 0);
    // sortBiggerHalf(secondHalfBigger, 1);
    // sortBiggerHalf(bothHalvesSame, 1);
    //
    // fmt::println(
    //         "{}\n{}\n{}",
    //         firstHalfBigger,
    //         secondHalfBigger,
    //         bothHalvesSame
    // );

    // std::vector<std::string> names = {"Adam", "Illia", "Ewa", "Anastasia", "Illia", "Ewa", "Illia", "Maciej", "Adam", "Natalia"};
    // std::set<std::string> unique_names;
    //
    // for (auto name : names) {
    //     unique_names.insert(name);
    // }
    //
    // fmt::println("{}", unique_names);

    // auto fileNames = std::vector<std::string>{
    //     "lecture 1", "lecture 2", "lecture 3",
    //     "lecture 10", "lecture 11", "lecture 12",
    //     "lecture 35", "lecture 39", "lecture 92",
    //     "lecture 101", "lecture 111", "lecture 133",
    //     "lecture 159", "lecture 212", "lecture 221",
    //     "file1.txt", "file10.txt", "file11.txt", "file2.txt", "file20.txt", "file3.txt",
    //     "file1_part3.txt", "file10_part10.txt", "file10_part2.txt", "file2_part1.txt", "file20_part21.txt", "file3_part1.txt"
    // };
    // std::ranges::sort(fileNames);
    // std::ranges::sort(fileNames, std::ranges::less{}, [](std::string const& a) {return a.size();});
    //
    // fmt::println("{}", fmt::join(fileNames, "\n"));

    // std::vector<std::string> strings = {"apple", "banana", "kiwi", "orange", "strawberry", "grapefruit"};
    //
    // v1::printLongestString(strings);
    // v2::printLongestString(strings);
    // v3::printLongestString(strings);
    // v4::printLongestString(strings);

    fmt::println(
            "[{}]\n[{}]\n[{}]\n[{}]",
            reduceAdjacentWhitespaces("Abc"),
            reduceAdjacentWhitespaces("A b c"),
            reduceAdjacentWhitespaces("   A\tb c      "),
            reduceAdjacentWhitespaces("A\t\tb\n \n  \t c")
    );

}
