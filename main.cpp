// // // //
// // // // Created by Anastasiia Kravchenko on 07.03.2025.
// // // //
// // //
// // // #include <algorithm>
// // // #include <iostream>
// // // #include <vector>
// // // #include <string>
// // //
// // // void printStringView(std::string_view sv) {
// // //     std::cout << "String view: " << sv << std::endl;
// // // }
// // //
// // // // void printSpan(std::span<int> sp) {
// // // //     std::cout << "Span: ";
// // // //     for (int value : sp) {
// // // //         std::cout << value << " ";
// // // //     }
// // // //     std::cout << std::endl;
// // // // }
// // //
// // //
// // // int main() {
// // //     std::cout << "hello world\n";
// // //     /*
// // //             int x;
// // //             double y;
// // //             std::string s;
// // //             std::cin >> x;
// // //             std::cin >> y;
// // //             std::cin >> s;
// // //         //    std::cout << "[" << x << "]";
// // //
// // //             std::cout << x << ' ' << y << ' ' << s;*/
// // //
// // //     //    int x = 0;
// // //     //    auto x = int();
// // //     //    auto x = 0;
// // //     //    auto x = 17;
// // //     //    for (int i = 0; i < 10; i++) { }
// // //     //    std::cout << x;
// // //     //    for (int i = 0; i < 10; i++) { }
// // //
// // //     //    auto a = 0;
// // //     //    auto b = 0;
// // //     //    std::cin >> a >> b;
// // //
// // //     //    auto text = std::string();
// // //     auto text = std::string();
// // //     std::cin >> text;
// // //     std::cout << text << std::endl;
// // //     //    auto numbers = std::vector<int>();
// // //     //
// // //     auto str = std::vector<std::string>();
// // //     str.push_back("hello world");
// // //     str.push_back("hello");
// // //     str.push_back("world");
// // //     for (auto i : str) std::cout << i << std::endl;
// // //     str.pop_back();
// // //     for (auto i : str) std::cout << i << std::endl;
// // //     //    numbers.push_back(3);
// // //     //    numbers.push_back(7);
// // //     //    numbers.push_back(1);
// // //     //
// // //     //    for (auto element : numbers) {
// // //     //        std::cout << element << ' ';
// // //     //    }
// // //     //
// // //     //    numbers.pop_back();
// // //     //
// // //     //    std::cout << '\n';
// // //     //    for (auto element : numbers) {
// // //     //        std::cout << element << ' ';
// // //     //    }
// // //     auto hi = int(4);
// // //     switch (hi) {
// // //         case 4: std::cout << "hi\n"; break;
// // //         default: std::cout << "hi"; return 0;
// // //     }
// // //
// // //     /*auto nums = std::vector<int>{1, 2, 3, 5, 12, 54, 6, 2, 46, 3, 2, 6, 7, 7};
// // //     std::ranges::sort(nums);
// // //
// // //     for (auto element : nums) {
// // //         std::cout << element << ' ';
// // //     }*/
// // //     std::string text1 = "long sentance with some meaning";
// // //     for (auto i = 0; i < text1.size(); i++) std::cout << text1[i];
// // //     std::cout << std::endl;
// // //     for (auto i : text1) std::cout << i;
// // //     std::cout << std::endl;
// // //     std::vector<char> rev;
// // //     for (int i = text1.size() - 1; i >= 0; i--) rev.push_back(text1[i]);
// // //     for (auto i : rev) std::cout << i;
// // //     std::cout << std::endl;
// // //
// // //
// // //     text = std::string();
// // //     auto first  = std::string("Programming");
// // //     auto second = std::string("in");
// // //     auto third  = std::string("C++");
// // //     auto fourth = std::string(", Python");
// // //     for (auto chr : first) text += chr;
// // //     text += ' ';
// // //     for (auto chr : second) text += chr;
// // //     text += ' ';
// // //     for (auto chr : third) text += chr;
// // //     text += fourth;
// // //     std::cout << text;
// // //
// // //
// // //     text = std::string("Programming");
// // //     std::cout << "kg stands for kilo" << text.substr(3, 4) << std::endl;
// // //     //    auto s1 = std::string("hello");
// // //     //    std::ranges::reverse(s1);
// // //     //    auto s2 = std::string();
// // //     //
// // //     //    std::cin >> s2;
// // //     //
// // //     //    if (s1 < s2) {
// // //     //        std::cout << ":>";
// // //     //    }
// // //     //
// // //     auto vec = std::vector<int>{3, 5, 1, 4, 2};
// // //
// // //     std::ranges::reverse(vec);
// // //
// // //     for (auto element : vec) {
// // //         std::cout << element << ' ';
// // //     }
// // //     //    auto words = std::vector<std::string>{"hello", "everyone", "present"};
// // //     //    std::ranges::sort(words);
// // //     //
// // //     //    for (auto word : words) std::cout << word << ' ';
// // //
// // //     //    std::cout << words;
// // //
// // //     //    auto const x = 0;
// // //     //    x = 10;
// // //
// // //     std::string myString = "Hello, string view!";
// // //     printStringView(myString); // No copy is made
// // //     const char* cString = "C-style string";
// // //     printStringView(cString); // Works with C-style strings too
// // //
// // //
// // //     // auto myVector = std::vector<int>{1, 2, 3, 4, 5};
// // //     // printSpan(myVector);
// // //     // int myArray[] = {10, 20, 30};
// // //     // printSpan(myArray);
// // // }
// //
// // //
// // // Created by Anastasiia Kravchenko on 14.03.2025.
// // //
// // #include <iostream>
// // #include <vector>
// // #include <string>
// // #include <ranges>
// //
// // int main() {
// //     auto const word = std::string("hello");
// //     auto text = word.back() + word + word.front(); // ohelloh
// //     std::ranges::sort(text); // abcdefghigknlmoprt => ehhlloo
// //     std::cout << text << "\n";
// //     std::cout << word.size() << "\n"; // 5
// //
// //     auto str = std::vector<std::string>(3);
// //     for ( int i = 0; i < 3; i++) {
// //         std::cin >> str[i];
// //     }
// //     auto sorted = std::ranges::sort(str);
// //     auto bol =
// //     for ( int i = 0; i < 3; i++) {
// //         if ( sorted[i] != str[i] ) {
// //             std::cout << "%";
// //         }else std::cout << "#";
// //     }
// // }
//
// // auto printhi() -> void {
// //     fmt::print("Hello world!\n");
// // }
// // auto modify(int& x) -> void {
// //     x += 3;
// // }
// //
// // namespace std {
// //     auto cou1(int x) -> void {
// //         fmt::print("{}", x);
// //     }
// // }
// // namespace pjc {
// //     // auto sayHello() -> void {
// //     //     fmt::print("Hello world!\n");
// //     // }
// //
// //     auto sayHello() -> void {
// //         fmt::println("Hello!");
// //     }
// // }
// #include <iostream>
// #include <vector>
// #include <ranges>
// #include <algorithm>
// #include <numeric>
// #include <fmt/ranges.h>
// #include <set>
// #include <string>
// // auto dotProduct(std::vector<double> const& v1, std::vector<double> const& v2) {
// //     int count = 0;
// //     for ( int i = 0; i < v1.size(); i++ ) {
// //         count += v1[i] * v2[i];
// //     }
// //     return count;
// // }
//
// // bool suffix(const std::set<int>& s, const std::vector<int>& v) {
// //     auto starts = --s.end();
// //     auto startv = --v.end();
// //     int count = 0;
// //     for ( int i = 0; i < v.size(); i++ ) {
// //         if ( *starts == *startv ) {
// //             count++;
// //         }
// //         --starts;
// //         --startv;
// //     }
// //     return count == v.size();
// // }
//
// // auto isPalindrome(std::string s) -> bool {
// //     auto s1 = s;
// //     std::ranges::reverse(s);
// //     if (s1 == s) {
// //         return true;
// //     }
// // }
//
// // auto sortBiggerHalf(std::vector<int> & x, int y) {
// //     if ( y == 0) {
// //         std::ranges::sort(x.begin(), x.begin() + x.size()/2);
// //     }else if (y == 1) {
// //         std::ranges::sort(x.begin() + x.size()/2, x.end());
// //     }else {
// //         std::ranges::sort(x);
// //     }
// // }
//
// // namespace v1 {
// //     auto printLongestString(std::vector<std::string> a) {
// //         std::cout << std::ranges::max(a, [](std::string x, std::string y){return x.size() < y.size();}) << std::endl;
// //     }
// // }
// // namespace v2 {
// //     auto printLongestString(std::vector<std::string> a) {
// //         std::cout << *std::ranges::max_element(a,[](std::string x, std::string y){return x.size() < y.size();}) << std::endl;
// //     }
// // }
// // namespace v3 {
// //     auto printLongestString(std::vector<std::string> a) {
// //         std::cout <<  std::ranges::min(a,[](std::string x, std::string y){return x.size() < y.size();}) << std::endl;
// //     }
// // }
// // namespace v4 {
// //     auto printLongestString(std::vector<std::string> a) {
// //         std::cout << *std::ranges::min_element(a,[](std::string x, std::string y){return x.size() < y.size();}) << std::endl;
// //     }
// // }
//
// // auto reduceAdjacentWhitespaces(std::string x) {
// //     std::string modstr = "";
// //     bool last_was_space = false;
// //     for ( auto c : x) {
// //         if (std::isspace(c)) {
// //             if (!last_was_space) {
// //                 modstr += ' ';
// //             }
// //             last_was_space = true;
// //         }else {
// //             modstr += c;
// //             last_was_space = false;
// //         }
// //     }
// //     return modstr;
// // }
//
// // bool bothHalvesContainGreatestNumber(const std::vector<int>& vec) {
// //     auto max_1 = std::ranges::max_element(vec.begin(),
// //         vec.begin() + vec.size()/2);
// //     auto max_2 = std::ranges::max_element(vec.begin() + vec.size()/2,
// //         vec.end());
// //     if ( *max_1 == *max_2 ) {
// //         return true;
// //     }
// //     return false;
// // }
// //
// // class Callable {
// // public:
// //     void replace( std::vector<int>& a,  std::vector<int>& b){
// //         auto max_1 = std::ranges::max_element(a);
// //         auto max_2 = std::ranges::max_element(b);
// //         std::ranges::swap(*max_1, *max_2);
// //     }
// // };
// // //
// // // bool fun(const std::vector<int>& v1) {
// // //
// // //     auto max1 = std::ranges::max(v1);
// // //     auto max2 = std::ranges::max(v1);
// // //     std::cout << *max1;
// // //     std::cout << *max2;
// // //     if (*max1 == *max2) {
// // //         return true;
// // //     }
// // //     return false;
// // // }
// // namespace name {
// //     int duplicatesCount( std::vector<int>& vec) {
// //         std::ranges::sort(vec);
// //         auto uniq = std::ranges::unique(vec);
// //         return vec.size() - uniq.size();
// //     }
// // }
// //
// // std::string getShortestAndLongest( std::vector<std::string>& vec) {
// //
// //     auto max_1 = std::ranges::max_element(vec.begin(), vec.end(), [](std::string s1, std::string s2){return s1.size()<s2.size();});
// //     auto min_1 = std::ranges::min_element(vec.begin(), vec.end(), [](std::string s1, std::string s2){return s1.size()<s2.size();});
// //     return *max_1 + *min_1;
// // }
//
// // template <std::ranges::range Container> // vec set
// // auto print(Container const& container) -> void {
// //     for (auto const& element : container) {
// //         std::cout << element << ' ';
// //     }
// //     std::cout << '\n';
// // }
// //
// // template <typename Object> // int, double
// // auto print(Object const& object) -> void {
// //     std::cout << object << '\n';
// // }
// // template< class T >
// // concept range = requires( T& t ) {
// //     std::ranges::begin(t);
// //     std::ranges::end  (t);
// // };
// // template <typename T>
// // concept HasSize = requires(T const& t){t.size();};
// // template <typename T>
// // concept HasSizeAndIsRange = HasSize<T> && std::ranges::range<T>;
// // auto greet(auto name) -> void {
// //     std::cout << "Hello, " << name << "!" << std::endl;
// // }
// //
// // auto multiply(auto a, auto b) {
// //     return a * b;
// // }
// //
// // template <typename F>
// // auto execute(F func) -> void {
// //     std::cout << "Executing: ";
// //     func();
// //     std::cout << "Done." << std::endl;
// // }
//
// #include <map>
// #include <utility>  // std::pair
// #include <fmt/ranges.h> // format for std::pair
// enum class Direction {
//     North, East, South, West
// };
//
// enum class Ordering {
//     Required, NotRequired
// };
//
// template <typename T>
// auto equalContents(
//         std::vector<T> const& left, std::vector<T> const& right,
//         Ordering const ordering
// ) -> bool {
//     if (ordering == Ordering::Required) return left == right;
//     else return std::ranges::is_permutation(left, right);
// }
//
// // namespace clazz {
//     // class Point {
//     //     public:
//     //         int x;
//     //         int y;
//     // };
// // }
//
// // namespace strukt {
//     struct Point {
//         // private:
//             int x;
//             int y;
//
//     auto distanceToOrigin() const -> double {
//         return std::hypot(x, y);
//     }
//     };
// // }
//
// auto format_as(Point const p1){return std::pair<int, int>{p1.x, p1.y};}
//
// auto toDist(Point const p1){ fmt::println("{}", std::hypot(p1.x, p1.y));return std::hypot(p1.x, p1.y);}



#include <iostream>
#include <utility>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <ranges>
#include <fmt/base.h>
#include <fmt/ranges.h>
#include <array>
#include <list>
#include <utility> // For std::pair
#include <string>

// namespace university {
//     enum class SortCriterion {
//         Name,
//         Surname,
//         Index,
//         Semester
//     };
//
//     struct Student {
//     private:
//         std::string firstName;
//         std::string lastName;
//         std::string studentID;
//         int semesterNumber;
//
//     public:
//         Student(std::string firstName, std::string lastName, std::string studentID, int semesterNumber)
//             : firstName(std::move(firstName)), lastName(std::move(lastName)), studentID(std::move(studentID)), semesterNumber(semesterNumber){}
//
//         std::string getFirstName() const { return firstName; }
//         std::string getLastName() const { return lastName; }
//         std::string getStudentID() const { return studentID; }
//         int getSemesterNumber() const { return semesterNumber; }
//
//         void setFirstName(const std::string& newFirstName) { firstName = newFirstName; }
//         void setLastName(const std::string& newLastName) { lastName = newLastName; }
//         void setStudentID(const std::string& newStudentID) { studentID = newStudentID; }
//         void setSemesterNumber(int newSemesterNumber) { semesterNumber = newSemesterNumber; }
//
//         auto print() const {
//             return getFirstName() + " " + getLastName() + " " + getStudentID() + " " + std::to_string(getSemesterNumber());
//         }
//     };
//     void sort(std::vector<Student>& group, SortCriterion criterion) {
//         switch (criterion) {
//             case SortCriterion::Name:
//                 std::ranges::sort(group, [](const Student& a, const Student& b) {
//                     return a.getFirstName() < b.getFirstName();
//                 });
//             break;
//             case SortCriterion::Surname:
//                 std::ranges::sort(group, [](const Student& a, const Student& b) {
//                     return a.getLastName() < b.getLastName();
//                 });
//             break;
//             case SortCriterion::Index:
//                 std::ranges::sort(group, [](const Student& a, const Student& b) {
//                     return a.getStudentID() < b.getStudentID();
//                 });
//             break;
//             case SortCriterion::Semester:
//                 std::ranges::sort(group, [](const Student& a, const Student& b) {
//                     return a.getSemesterNumber() < b.getSemesterNumber();
//                 });
//             break;
//         }
//     }
// }

// class Student {
// public:
//     std::string name;
//     std::string surname;
//     int age;
//
//     Student(std::string_view name, std::string_view surname, int age)
//         : name(name), surname(surname), age(age) {}
//
//     friend std::ostream& operator<<(std::ostream& os, const Student& student) {
//         os << "Name: " << student.name << " " << student.surname << ", Age: " << student.age;
//         return os;
//     }
// };

// template <typename T>
// auto call(int n, T t, int& x) -> void {
//     for (auto i = 0; i < n; i++) {
//         t(x);
//         t(x);
//         fmt::println("{}", i);
//     }
// }
//
// class Student {
// public:
//     std::string name;
//     std::string surname;
//     Student(std::string_view name, std::string_view surname) : name(name), surname(surname) {}
// };
//
// auto format_as(Student const& stud){return stud.name + " " + stud.surname;}

// template <typename I, typename S>
// std::vector<S> values(const std::map<I,S>& vec) {
//     auto vecN = std::vector<S>();
//     for ( auto i : vec) {
//         vecN.push_back(i.second);
//     }
//     return vecN;
// }
//
// class Stats {
// public:
//     double max;
//     double min;
//     double average;
// };
//
// template<typename C>
// Stats getStats(const C& vec) {
//     Stats result{};
//     result.max = *std::ranges::max_element(vec);
//     result.min = *std::ranges::min_element(vec);
//     auto average = 0.0;
//     for (auto i : vec) {
//         average += i;
//     }
//     result.average = average/vec.size();
//     return result;
// }


template<typename F>
auto fun(const F& funy) {
    funy();
    funy();
}

// Function template to print a container.
template <typename Container> // vec set
auto print(const std::vector<Container>& container) -> void {
    fmt::println("Container: {}", container);
}

// Function template to print an object.
template <typename Object> // int, double
auto print(const Object& object) -> void {
    if constexpr (std::ranges::range<Object>) {
        std::vector<int> vec1 = {1, 2, 3};
        std::vector<int> vec2 = {3, 2, 1};
        bool isPermutation = std::ranges::is_permutation(vec1, vec2);
        fmt::println("{}", isPermutation);
    }
    fmt::println("Object: {}", object);
}

template <typename T>
concept hasSize = requires(const std::vector<T>& t){t.size();};

namespace clazz {
    class Point { // class: members are private by default
    public:
        int x;
        int y;
    };
}
namespace strukt {
    struct Point { // struct: members are public by default
        int x;
        int y;
    };
}

// Chapter 5.4:
// auto format_as(Point const p) { return std::pair<int, int>(p.x, p.y); }
// return std::hypot(x, y); // ~ | |
// auto fibonacci = [n = 0, m = 1]() mutable {
struct Point2D {
    double x;
    double y;
};

auto format_as = [](Point2D const& p) { // Lambda function
    return std::make_pair(p.x, p.y);
};

// using namespace university;
auto main() -> int {
// //
// //     auto iter = std::vector<std::string>{"hello", "world"};
// //     // auto start = iter.begin();
// //     auto end = iter.end();
// //     end--;
// //     std::cout << *end << std::endl;
// //
// //     auto vec = std::vector<int>{3, 5, 1, 4, 2, 0};
// //
// //     auto middle = vec.begin() + vec.size()/2;
// //
// //     std::ranges::reverse(++middle, vec.end());
// //
// //     for (auto n : vec) {
// //         std::cout << n << ' ';
// //     }
// //     std::cout << std::endl;
// //
// //     std::cout << *vec.begin() << std::endl;
// //     auto first = vec.begin() + 1;
// //     std::cout << *vec.begin() << std::endl;
// //     auto last = vec.begin() + 4;
// //     std::cout << *first << ' ' << *last << '\n';
// //
// //     auto vec = std::vector<int>{11, 22, 33, 22, 33, 11};
// //     auto middle = vec.begin() + vec.size()/2;
// //     std::ranges::sort(middle, vec.end());
// //
// //     std::cout << std::ranges::equal(vec.begin(), middle, middle, vec.end());
// //     std::cout << std::endl;
// //
// //     for ( auto i = vec.begin(); i != vec.end(); i++) {
// //         std::cout << *i << " ";
// //     }
// //     std::cout << std::endl;
// //
// //     auto setik = std::set<int>();
// //     for (auto i : {1,2,3,4,5,6,7,8,9,9,8,7,6,5,4,3,2,1,0}) {
// //         setik.insert(i);
// //     }
// //     for (auto i : setik) {
// //         std::cout << i << " ";
// //     }
// //     std::cout << std::endl;
// //
// //     auto Uniqeset = std::set<int>{1,2,3,4,5,6,7,8,9,9,8,7,6,5,4,3,2,1,0};
// //     auto Uniqevec = std::vector<int>();
// //     for (auto i : Uniqeset) {
// //         std::cout << i << " ";
// //         Uniqevec.emplace_back(i);
// //     }
// //     std::cout << std::endl;
// //     for (auto i : Uniqevec) {
// //         std::cout << i << " ";
// //     }
// //     std::cout << std::endl;
// //
// //     auto uniqevec = std::vector<int>(5,1);
// //     auto dub = std::ranges::unique(uniqevec);
// //     for (auto i : dub) {
// //         std::cout << i << " ";
// //     }
// //     std::cout << std::endl;
// //     uniqevec.erase(dub.begin(),dub.end());
// //     // uniqevec.erase(uniqevec.begin(),uniqevec.end());
// //     if (uniqevec.empty()) {
// //         std::cout << "nothing" << std::endl;
// //     }
// //     for (auto i : uniqevec) {
// //         std::cout << i << " ";
// //     }
// //
// //     auto numbers = std::vector<int>{1, 2, 3, 1, 2, 3, 1, 2, 3};
// //
// //     std::ranges::sort(numbers);
// //     auto duplicates = std::ranges::unique(numbers);
// //
// //     numbers.erase(duplicates.begin(), duplicates.end());
// //
// //     std::cout << std::endl;
// //     for (auto element : numbers) {
// //         std::cout << element << ' ';
// //     }
// //     std::cout << std::endl;
// //
// //     fmt::println("{}", numbers);
// //
// //     // numbers.erase(numbers.end()); // will work
// //
// //     fmt::print("{}", numbers);
// //     fmt::print("{}", numbers);
// //     std::cout << std::endl;
// //
// //     auto vector = std::vector<int>{1, 2, 3};
// //     auto set    = std::set<int>{1, 2, 3};
// //
// //     fmt::println("{}", vector);
// //     fmt::println("{}", set);
// //     fmt::println("{}", vector);
// //     fmt::println("[{}]", fmt::join(set, ", "));
// //     fmt::println("The answer to ur question is {}", 3);
// //
// //     // fmt::format_string<> x = "5";
// //     // fmt::println(x);
// //
// //     auto x = 5;
// //     fmt::println("{}", x);
// //
// //     printhi();
// //
// //     modify(x);
// //     fmt::println("{}", x);
// //
// //     auto vec = std::vector<int>{1, 1, 3};
// //     fmt::println("{}", fmt::join(vec, " "));
// //
// //     std::cou1(5);
// //     pjc::sayHello();
// //
// //     auto const find = std::ranges::find(vec, 1);
// //     auto find2 = *find != 1;
// //     fmt::println("{}", *find);
// //
// //     auto const numbers = std::vector<int>{3, 5, 1, 4, 2};
// //
// //     auto const iter = std::ranges::find(numbers, 9);
// //
// //     auto const present = iter != numbers.end();
// //
// //     if (present) {
// //         fmt::println("{}", *iter);
// //     } else {
// //         fmt::println("No such element");
// //     }
// //
// //     auto numbers = std::vector<int>(21);
// //
// //     for (auto i = 0; i < numbers.size(); i++) {
// //         std::cin >> numbers[i];
// //     }
// //
// //     auto zeroCounter = 0;
// //
// //     for (auto start = numbers.begin(); start != numbers.end(); start += 3) {
// //         auto end = start + 3;
// //
// //         auto const iterToZero = std::ranges::find(start, end, 0);
// //         auto range = std::ranges::subrange(start, end);
// //         for ( auto i : range) {
// //             std::cout << i << " ";
// //         }
// //         std::cout << std::endl;
// //
// //         if (iterToZero != end) {
// //             zeroCounter += 1;
// //         }
// //     }
// //
// //     fmt::println("There were {} groups with zeros", zeroCounter);
// //
// //
// //     auto numbers = std::vector<int>{11, 1, 1111, 111};
// //
// //     auto const maxNumber = std::ranges::max(numbers);
// //     auto const maxIter   = std::ranges::max_element(numbers);
// //
// //     auto const minNumber = std::ranges::min(numbers);
// //     auto const minIter   = std::ranges::min_element(numbers);
// //
// //     fmt::println(
// //             "min: {}\nmax: {}\nminElement: {}\nmaxElement: {}",
// //             minNumber, maxNumber,
// //             *minIter, *maxIter
// //     );
// //
// //     fmt::println("{}", numbers);
// //     std::ranges::swap(*maxIter, *minIter);
// //     // std::ranges::iter_swap(maxIter, minIter);
// //     fmt::println("{}", numbers);
// //
// //     std::ranges::sort(numbers);
// //     fmt::println("{}", numbers);
// //
// //
// //     auto words = std::vector<std::string>{"w2", "w103", "w101", "w1020", "w105", "w7", "w303", "w4"};
// //     std::ranges::sort(words, std::ranges::greater());
// //     std::ranges::sort(words, std::ranges::greater(), std::ranges::size);
// //     fmt::println("{}", words);
// //
// //
// //     auto lamb = [](int x)->void{std::cout << x << '\n';};
// //     lamb(3);
// //
// //     auto words = std::vector<std::string>{
// //         "hello", "there", "and", "welcome"
// // };
// //
// //     std::ranges::sort(words, std::ranges::less(), [](std::string const& s) {
// //         return s.size();
// //     });
// //
// //     fmt::println("{}", words);
// //
// //     std::ranges::sort(words, std::ranges::greater(), [](std::string const& s) {
// //         return s.size();
// //     });
// //
// //     fmt::println("{}", words);
// //
// //     auto words = std::vector<std::string>{
// //         "hello", "there", "and", "welcome"
// // };
// //
// //     auto const capitalize = [](std::string copy) {
// //         auto const differenceBetweenLowerAndUpperCase = 'a' - 'A';
// //         copy.front() -= differenceBetweenLowerAndUpperCase;
// //         return copy;
// //     };
// //
// //     fmt::println("{}", words);
// //     std::ranges::transform(words, words.begin()+1, capitalize);
// //     fmt::println("{}", words);
// //
// //     std::vector<int> data = {5, 2, 8, 1, 9, 3, 7, 4, 6};
// //     auto min_it = std::ranges::min_element(data);
// //     auto max_it = std::ranges::max_element(data);
// //
// //     if (min_it != data.end() && max_it != data.end()) {
// //         std::ranges::iter_swap(min_it, max_it);
// //     }
// //
// //     for (int val : data) {
// //         std::cout << val << " ";
// //     }
// //     std::cout << std::endl;
// //     return 0;
// //
// //
// //     std::vector<int> numbers = {3, 1, 4, 1, 5, 9, 2, 6};
// //     auto maxIter = std::ranges::max_element(numbers);
// //     auto minIter = std::ranges::min_element(numbers);
// //
// //     std::cout << "Before swap: max = " << *maxIter << ", min = " << *minIter << std::endl;
// //
// //     std::ranges::iter_swap(maxIter, minIter);
// //
// //     std::cout << "After swap: max = " << *maxIter << ", min = " << *minIter << std::endl;
// //     std::cout << "Vector after swap: ";
// //     for (int num : numbers) {
// //         std::cout << num << " ";
// //     }
// //     std::cout << std::endl;
// //
// //     std::vector<int> data = {5, 2, 8, 1, 9, 3, 7, 4, 6};
// //     auto has = std::ranges::find_if(data, [](int x){return x > 10;});
// //     std::cout << (has==data.end()?"hasn't":"has");
// //
// //
// //     std::vector<int> data = {5, 2, 8, 1, 9, 3, 7, 4, 6};
// //     auto has = std::ranges::find_if(data, [](int x) {
// //         if (x > 10) {
// //             return -1;
// //         }
// //         return 0;
// //     });
// //     std::cout << (has==data.end()?"hasn't":"has");
// //
// //     std::vector<std::string> words = {"apple", "banana", "kiwi", "orange", "grape"};
// //     std::ranges::sort(words, std::ranges::greater(), [](const std::string& s) { return s.size(); });
// //     for (const auto& word : words) {
// //         std::cout << word << " ";
// //     }
// //     std::cout << std::endl;
// //     std::vector<int> data = {5, 2, 8, 1, 9, 3, 7, 4, 6};
// //     int mi = 0;
// //     std::cin >> mi;
// //     std::cout << ((std::ranges::find(data, mi) != data.end()) ? "all good" : "not good");
// //
// //     std::vector<int> data = {5, 2, 8, 1, 9, 3, 7, 4, 6};
// //     auto max_value = std::ranges::max(data);
// //     std::cout << max_value << std::endl;
// //
// //     auto all = std::vector<int>(7);
// //     for ( int i = 0; i < 7; ++i ) {
// //         std::cin >> all[i];
// //     }
// //     // std::ranges::sort(all);
// //     // auto start = all.begin();
// //     // all.erase(start);
// //     // auto end = all.end()-1;
// //     // all.erase(end);
// //     // fmt::print("{}", all);
// //     all.erase(std::ranges::min_element(all));
// //     all.erase(std::ranges::max_element(all));
// //     fmt::print("{}\n", all);
// //
// //     std::vector<double> v1 = {1.0, 2.0, 3.0};
// //     std::vector<double> v2 = {4.0, 5.0, 6.0};
// //     std::cout << dotProduct(v1, v2) << std::endl;
// //
// //     auto mass = std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
// //     for ( int i = 0; i < mass.size(); i++ ) {
// //         if ( i % 2 == 0 ) {
// //             std::cout << mass[i] << std::endl;
// //         }
// //     }
// //
// //     std::set<int> s1 = {1, 2, 3, 4, 5, 6, 7};
// //     std::vector<int> v1 = {5, 6, 7};
// //     std::cout << "v1 is a suffix of s1: " << (suffix(s1, v1) ? "true" : "false") << std::endl;
// //
// //     fmt::println(
// //            "{}\n{}\n{}",
// //            isPalindrome("KajaK"),
// //            isPalindrome("ala"),
// //            isPalindrome("programowanie")
// //    );
// //
// //     auto firstHalfBigger  = std::vector<int>{3, 2, 1, 0, 1, 0};
// //     auto secondHalfBigger = std::vector<int>{3, 2, 1, 6, 5, 4};
// //     auto bothHalvesSame   = std::vector<int>{5, 4, 5, 4};
// //
// //     sortBiggerHalf(firstHalfBigger, 0);
// //     sortBiggerHalf(secondHalfBigger, 1);
// //     sortBiggerHalf(bothHalvesSame, 1);
// //
// //     fmt::println(
// //             "{}\n{}\n{}",
// //             firstHalfBigger,
// //             secondHalfBigger,
// //             bothHalvesSame
// //     );
// //
// //     std::vector<std::string> names = {"Adam", "Illia", "Ewa", "Anastasia", "Illia", "Ewa", "Illia", "Maciej", "Adam", "Natalia"};
// //     std::set<std::string> unique_names;
// //
// //     for (auto name : names) {
// //         unique_names.insert(name);
// //     }
// //
// //     fmt::println("{}", unique_names);
// //
// //     auto fileNames = std::vector<std::string>{
// //         "lecture 1", "lecture 2", "lecture 3",
// //         "lecture 10", "lecture 11", "lecture 12",
// //         "lecture 35", "lecture 39", "lecture 92",
// //         "lecture 101", "lecture 111", "lecture 133",
// //         "lecture 159", "lecture 212", "lecture 221",
// //         "file1.txt", "file10.txt", "file11.txt", "file2.txt", "file20.txt", "file3.txt",
// //         "file1_part3.txt", "file10_part10.txt", "file10_part2.txt", "file2_part1.txt", "file20_part21.txt", "file3_part1.txt"
// //     };
// //     std::ranges::sort(fileNames);
// //     std::ranges::sort(fileNames, std::ranges::less{}, [](std::string const& a) {return a.size();});
// //
// //     fmt::println("{}", fmt::join(fileNames, "\n"));
// //
// //     std::vector<std::string> strings = {"apple", "banana", "kiwi", "orange", "strawberry", "grapefruit"};
// //
// //     v1::printLongestString(strings);
// //     v2::printLongestString(strings);
// //     v3::printLongestString(strings);
// //     v4::printLongestString(strings);
// //
// //     // fmt::println(
// //     //         "[{}]\n[{}]\n[{}]\n[{}]",
// //     //         reduceAdjacentWhitespaces("Abc"),
// //     //         reduceAdjacentWhitespaces("A b c"),
// //     //         reduceAdjacentWhitespaces("   A\tb c      "),
// //     //         reduceAdjacentWhitespaces("A\t\tb\n \n  \t c")
// //     // );
// //
// //     std::vector<int> v1 = {1, 2, 3, 4};
// //     std::cout << "v1: " << bothHalvesContainGreatestNumber(v1) << std::endl; // Output: 0
// //
// //     std::vector<int> v2 = {1, 4, 3, 4};
// //     std::cout << "v2: " << bothHalvesContainGreatestNumber(v2) << std::endl; // Output: 1
// //
// //     std::vector<int> v3 = {5, 2, 5, 1};
// //     std::cout << "v3: " << bothHalvesContainGreatestNumber(v3) << std::endl; // Output: 1
// //
// //     std::vector<int> v4 = {10, 2, 3, 4, 10, 1};
// //     std::cout << "v4: " << bothHalvesContainGreatestNumber(v4) << std::endl; // Output: 1
// //
// //     std::vector<int> v5 = {1, 2, 3, 10, 5, 6};
// //     std::cout << "v5: " << bothHalvesContainGreatestNumber(v5) << std::endl; // Output: 0
// //
// //     auto words = std::set<std::string>{
// //         "this", "is", "the", "second" // is second the this
// //     };
// //     // for (const auto& word : words) {
// //     //     std::cout << word << std::endl;
// //     // }
// //     auto iter = words.begin(); // std::cout << *iter << std::endl; // is
// //     for (auto i = 0; i < 3; ++i) /*std::cout << *iter;*/ ++iter; // the
// //     fmt::println("({})", *words.begin(), *iter); // {} -> *words.begin() -> (is)
// //     // fmt::println("({})", *iter);
// //     auto count = std::ranges::count_if(
// //         words.begin(), iter,
// //         [](std::string const& s) {
// //           return s.front() == 't';
// //         });
// //     fmt::println("({})", count); // 1
// //     fmt::println("({})", std::vector<std::string>(iter, words.end())); // ([this])
// //
// //
// //     Callable callable_obj;
// //
// //     std::vector<int> vec_a = {1, 5, 2, 8, 3};
// //     std::vector<int> vec_b = {9, 4, 7, 6, 10};
// //
// //     std::cout << "Before calling replace:" << std::endl;
// //     std::cout << "vec_a: ";
// //     for (int val : vec_a) {
// //         std::cout << val << " ";
// //     }
// //     std::cout << std::endl;
// //     std::cout << "vec_b: ";
// //     for (int val : vec_b) {
// //         std::cout << val << " ";
// //     }
// //     std::cout << std::endl;
// //
// //     callable_obj.replace(vec_a, vec_b);
// //
// //     std::cout << "After calling replace:" << std::endl;
// //     std::cout << "vec_a: ";
// //     for (int val : vec_a) {
// //         std::cout << val << " ";
// //     }
// //     std::cout << std::endl;
// //     std::cout << "vec_b: ";
// //     for (int val : vec_b) {
// //         std::cout << val << " ";
// //     }
// //     std::cout << std::endl;
// //
// //
// //
// //     std::vector<std::string> vec = {"hello", "i am", "david", "a", "short"};
// //     std::ranges::sort(vec, [](std::string const& s1, std::string const& s2) {
// //         if (s1.size() != s2.size()) {
// //             return s1.size() < s2.size();
// //         } return s1 < s2;
// //     });
// //     fmt::println("({})", vec);
// //
// //     // std::vector<int> v6 = {1, 2, 3, 2, 1, 3};
// //     // std::cout<< fun(v6);
// //
// //     auto word = std::string{"programming"};
// //
// //     for (auto const& c : word) {
// //         std::cout << c;
// //     }
// //     std::cout << std::endl;
// //
// //     auto changer = [](char c) {
// //         if (c == 'r') {
// //             return 'R';
// //         }
// //         return c;
// //     };
// //
// //     std::ranges::transform(word, word.begin(), changer);
// //
// //     std::cout << word << std::endl;
// //
// //
// //     auto nums = std::vector<int>{237, 154, 33, 81, 900, 525};
// //     std::ranges::sort(nums, {}, [](int const n) { return n % 10; });
// //     fmt::println("({})", nums);
// //     std::ranges::reverse(nums.begin() + 3, nums.end());
// //     fmt::println("({})", nums);
// //     fmt::println("({})", std::set<int>(nums.begin(), nums.end()));
// //
// //
// //     std::vector<int> v7 = {3, 1, 2, 1, 2, 3, 2};
// //     std::cout << "Duplicates in v1: " << name::duplicatesCount(v7) << std::endl; // Output: 4
// //
// //     std::vector<int> v8 = {1, 2, 3, 4, 5};
// //     std::cout << "Duplicates in v2: " << name::duplicatesCount(v8) << std::endl; // Output: 0
// //
// //     std::vector<int> v9 = {1, 1, 1, 1, 1};
// //     std::cout << "Duplicates in v3: " << name::duplicatesCount(v9) << std::endl; // Output: 4
// //
// //     std::vector<int> v10 = {};
// //     std::cout << "Duplicates in v4: " << name::duplicatesCount(v10) << std::endl; // Output: 0
// //
// //     std::vector<int> v11 = {1, 2, 2, 3, 3, 3};
// //     std::cout << "Duplicates in v5: " << name::duplicatesCount(v11) << std::endl; // Output: 3
// //
// //
// //     auto producer = [](int n) { return std::vector<int>(n, 1); };
// //     auto a1 = producer(3); // 0 0 0
// //     auto a2 = producer(5); // 0 0 0 0 0
// //     auto x = 0;
// //     for (auto& e : a1) e *= x;
// //     for (auto& e : a2) e *= x;
// //     fmt::println("START {} END", a1); // START [0, 0, 0] END
// //     fmt::println("START {} END", a2); // START [0, 0, 0, 0, 0] END
// //     fmt::println("START {} END", std::set<int>(a2.begin(), a2.end())); // START {0} END
// //
// //
// //     std::vector<std::string> b1 = {"hello", "i am", "david", "a", "short"};
// //     std::cout << getShortestAndLongest(b1) << std::endl;
// //
// //     std::vector<std::string> b2 = {"one", "two", "three"};
// //     std::cout << getShortestAndLongest(b2) << std::endl;
// //
// //     std::vector<std::string> b3 = {"same", "same"};
// //     std::cout << getShortestAndLongest(b3) << std::endl;
// //
// //     std::vector<std::string> b4 = {"longest", "shrt"};
// //     std::cout << getShortestAndLongest(b4) << std::endl;
// //
// //     std::vector<std::string> b5 = {};
// //     std::cout << getShortestAndLongest(b5) << std::endl;
// //
// //     std::vector<int> numbers_vec = {1, 2, 3};
// //     std::set<int> numbers_set = {1, 2, 3};
// //
// //     // fmt::print("{}", numbers); // Assuming you want to print the vector/set
// //     fmt::println("Vector: {}", numbers_vec);
// //     fmt::println("Set: {}", numbers_set);
// //
// //     // fmt::join(set, ", ")
// //     fmt::println("Set joined with comma: {}", fmt::join(numbers_set, ", "));
// //
// //     // fmt::println("The answer is {}", 42);
// //     fmt::println("The answer is {}", 42);
// //
// //     // fmt::println("{}", fmt::join(vec, " "));
// //     std::vector<std::string> words1 = {"hello", "world", "cpp"};
// //     fmt::println("Words joined with space: {}", fmt::join(words1, " "));
// //
// //     std::vector<int> numbers = {5, 2, 8, 1, 9, 4};
// //
// //     // std::ranges::find(): Find the first occurrence of a value
// //     auto find_result = std::ranges::find(numbers, 8);
// //     if (find_result != numbers.end()) {
// //         fmt::println("Found 8 at index: {}", std::ranges::distance(numbers.begin(), find_result));
// //     } else {
// //         fmt::println("8 not found.");
// //     }
// //
// //     // std::ranges::max(): Find the maximum value in the range
// //     auto max_val = std::ranges::max(numbers);
// //     fmt::println("Maximum value: {}", max_val);
// //
// //     // std::ranges::max_element(): Find an iterator to the maximum element
// //     auto max_iter = std::ranges::max_element(numbers);
// //     if (max_iter != numbers.end()) {
// //         fmt::println("Maximum element is: {}", *max_iter);
// //     }
// //
// //     // std::ranges::min(): Find the minimum value in the range
// //     auto min_val = std::ranges::min(numbers);
// //     fmt::println("Minimum value: {}", min_val);
// //
// //     // std::ranges::min_element(): Find an iterator to the minimum element
// //     auto min_iter = std::ranges::min_element(numbers);
// //     if (min_iter != numbers.end()) {
// //         fmt::println("Minimum element is: {}", *min_iter);
// //     }
// //
// //     // std::ranges::iter_swap(maxIter, minIter): Swap elements pointed to by iterators
// //     if (max_iter != numbers.end() && min_iter != numbers.end()) {
// //         std::ranges::iter_swap(max_iter, min_iter);
// //         fmt::println("Vector after iter_swap: {}", numbers);
// //     }
// //
// //     // std::ranges::swap(*maxIter, *minIter): Swap elements directly
// //     // (Assuming max_iter and min_iter are still valid)
// //     if (max_iter != numbers.end() && min_iter != numbers.end()) {
// //         std::ranges::swap(*max_iter, *min_iter);
// //         fmt::println("Vector after swap: {}", numbers);
// //     }
//
//     // auto set = std::set<int>{5, 5, 5, 4, 3, 1, 2};
//     // for ( auto set1 : set) {
//     //     std::cout << set1 << std::endl;
//     // }
//     // auto iter = set.begin();
//     // for ( int i=0; i<3; i++) ++iter;
//     // fmt::print( "{:d}\n", std::ranges::count(set.begin(), iter, 5));
//     // auto count = std::ranges::count_if(set, [](int i){return i>=2;});
//     // fmt::println("{}", count);
//
//     // // auto const vec = std::vector<int>{1, 2, 3};
//     // // auto const set = std::set<int>{1, 2, 3};
//     //
//     // auto const set = "HI";
//     // print(set);
//     // // print(vec);
//     // // print(set);
//     //
//     // fmt::println("vector is a range? {}", std::ranges::range<std::vector<int>>);
//     // fmt::println("set is a range?    {}", std::ranges::range<std::set<int>>);
//     // fmt::println("string is a range? {}", std::ranges::range<std::string>);
//     // fmt::println("int is a range?    {}", std::ranges::range<int>);
//     // fmt::println("double is a range? {}", std::ranges::range<double>);
//     //
//     // fmt::println("int has size?    {}", HasSize<int>);
//     // fmt::println("string has size? {}", HasSize<std::string>);
//     // fmt::println("vector has size? {}", HasSize<std::vector<int>>);
//     //
//     // fmt::println("{}", HasSizeAndIsRange<int>);
//     // fmt::println("{}", HasSizeAndIsRange<std::string>);
//     // fmt::println("{}", HasSizeAndIsRange<std::vector<int>>);
//     //
//     // greet("Alice");
//     // std::cout << multiply(3, 4) << std::endl;
//     // std::cout << multiply(1.5, 2.0) << std::endl;
//     //
//     // auto myLambda = []() { std::cout << "Lambda called!" << std::endl; };
//     // execute(myLambda);
//
//     // // Using std::function (as mentioned, it's a template itself)
//     // std::function<void()> anotherLambda = []() { std::cout << "Another lambda!" << std::endl; };
//     // execute(anotherLambda);
//
//     // auto const fileContent = std::string("some random text appears here");
//     //
//     // auto const totalNumberOfASCIICharacters = 128;
//     // auto occurrences = std::vector<int>(totalNumberOfASCIICharacters);
//     // fmt::println("{}", occurrences);
//     //
//     // for (auto const c : fileContent) {
//     //     occurrences[c] += 1; // c will give ascci value
//     // }
//     //
//     // for (auto i = 0; i < occurrences.size(); i++) {
//     //     if (occurrences[i] > 0) {
//     //         fmt::println(
//     //                 "'{}' occurred {} times",
//     //                 static_cast<char>(i), //(char)i,
//     //                 occurrences[i]
//     //         );
//     //     }
//     // }
//
//     // auto const fileContent = std::string("some random text appears here");
//     //
//     // auto occurrences = std::map<char, int>();
//     //
//     // for (auto const c : fileContent) {
//     //     occurrences[c] += 1;
//     // }
//     //
//     // for (auto const& charAndCount : occurrences) {
//     //     fmt::println(
//     //             "'{}' occurred {} times",
//     //             charAndCount.first,
//     //             charAndCount.second
//     //     );
//     // }
//     // for (auto const& [c, count] : occurrences) {
//     //     fmt::println("'{}' occurred {} times", c, count);
//     // }
//     //
//     // auto const pair = std::pair<char, int>('a', 5);
//     //
//     // auto const [c, i] = pair;
//     //
//     // fmt::println("{} {}", c, i);
//     //
//     // // auto uniqueCharacters = fileContent;
//     // // std::ranges::sort(uniqueCharacters);
//     // // auto [from, to] = std::ranges::unique(uniqueCharacters);
//     // // // auto newy = std::ranges::unique(uniqueCharacters);
//     // // // fmt::println("{}", newy);
//     // // // uniqueCharacters.erase(newy.begin(), newy.end());
//     // // // fmt::println("{}", uniqueCharacters);
//     // // fmt::println("{} {}", *from, *to);
//     // // fmt::println("{}", uniqueCharacters);
//     // // uniqueCharacters.erase(from, to);
//     // // fmt::println("{}", uniqueCharacters);
//     //
//     // auto uniqueCharacters = fileContent;
//     // std::ranges::sort(uniqueCharacters);
//     // auto const [from, to] = std::ranges::unique(uniqueCharacters);
//     // uniqueCharacters.erase(from, to);
//     //
//     // auto array = std::array<int, 5>{1, 2, 3, 4, 5};
//     // std::ranges::reverse(array);
//     // fmt::println("{}", array);
//
//     // auto currentDirection = Direction();
//     //
//     // currentDirection = Direction::South;
//     // currentDirection = Direction::West;
//     //
//     // auto v1 = std::vector<int>{1, 2, 3};
//     // auto v2 = std::vector<int>{3, 2, 1};
//     //
//     // fmt::println(
//     //         "{} {}",
//     //         equalContents(v1, v2, Ordering::Required),
//     //         equalContents(v1, v2, Ordering::NotRequired)
//     // );
//     //
//     // // auto p1 = Point();p1.x = 1;p1.y = 2;
//     // auto p2 = Point();p2.x = 1;p2.y = 2;
//     // auto sorting = std::vector<Point>{{1,0}, {2,3}, {0,0}};
//     //
//     // // fmt::println("{} {}", p1.x, p1.y);
//     // fmt::println("{} {}", p2.x, p2.y);
//     // std::ranges::sort(sorting, [](Point left, Point right) { return toDist(left) < toDist(right); });
//     // fmt::println("{}", p2);
//     // fmt::println("{}", sorting);
//     //
//     // auto points = std::vector<Point>{ {1, 2}, {0, 0}, {2, 0} };
//     // std::ranges::sort(points, [](Point const left, Point const  right) {
//     //     return left.distanceToOrigin() < right.distanceToOrigin();
//     // });
//     // fmt::println("{}", points);
//     //
//     // auto fibonacci = [n = 0, m = 1]() mutable {
//     //     fmt::print("{} ", m);
//     //     auto prevM = m;
//     //     m += n;
//     //     n = prevM;
//     // };
//     //
//     // for (auto i = 0; i < 10; i++) {
//     //     fibonacci();
//     // }
//
//     // auto graph = std::map<std::string, std::set<std::string>>();
//     // graph["A"] = {"B", "C"};
//     // graph["B"] = {"E"};
//     // graph["C"] = {"D"};
//     // graph["D"] = {"B"};
//     // graph["E"] = {"C"};
//     //
//     // auto route = [graph, letter = std::string("A")]() mutable {
//     //     for ( auto ent : graph[letter] ) {
//     //         fmt::print("{} -> ", ent);
//     //     }
//     //     letter = *graph[letter].begin();
//     // };
//     //
//     // for ( int i = 0; i < graph.size() * 2; ++i ) {
//     //     route();
//     // }
//     // std::cout << "..." << std::endl;
//     // std::cout << "Enter words (type 'stop' to finish):\n";
//     //
//     // std::map<int, std::set<std::string>> words;
//     // std::string word;
//     //
//     // while (std::cin >> word && word != "stop") {
//     //     words[word.length()].insert(word);
//     // }
//     // for (const auto& word : words) {
//     //     fmt::print("{}\n", fmt::join(word.second, " "));
//     // }
//
//     // std::vector<Student> studentGroup = {
//     //     {"Alice", "Smith", "S1001", 3},
//     //     {"Bob", "Johnson", "S1002", 3},
//     //     {"Charlie", "Brown", "S1003", 4},
//     //     {"David", "Lee", "S1004", 3}
//     // };
//     //
//     // fmt::println("Student Group:");
//     // for (const auto& student : studentGroup) {
//     //     fmt::println("{}", student.print());
//     // }
//     // fmt::println("");
//     //
//     // fmt::println("Sorting by Name:");
//     // sort(studentGroup, SortCriterion::Name);
//     // for (const auto& student : studentGroup) {
//     //     fmt::println("{}", student.print());
//     // }
//     // fmt::println("");
//     //
//     // fmt::println("Sorting by Surname:");
//     // sort(studentGroup, SortCriterion::Surname);
//     // for (const auto& student : studentGroup) {
//     //     fmt::println("{}", student.print());
//     // }
//     // fmt::println("");
//     //
//     // fmt::println("Sorting by Index:");
//     // sort(studentGroup, SortCriterion::Index);
//     // for (const auto& student : studentGroup) {
//     //     fmt::println("{}", student.print());
//     // }
//     // fmt::println("");
//     //
//     // fmt::println("Sorting by Semester:");
//     // sort(studentGroup, SortCriterion::Semester);
//     // for (const auto& student : studentGroup) {
//     //     fmt::println("{}", student.print());
//     // }
//     // fmt::println("");
//     //
//     // auto text = std::string("helloworld");
//     //
//     // auto map  = std::map<char, int>();
//     // for (auto c : text) map[c] += 1;
//     //
//     // // for (auto all : map) {
//     // //     fmt::println("{} {}", all.first, all.second);
//     // // }
//     // for (auto [k, v] : map) {
//     //     fmt::println("{} {}", k, v);
//     // }
//
//     // std::array<int, 9> arr1 = {1, 2, 3, 2, 3, 1, 3, 2, 1};
//     // std::array<int, 3> triplet1 = {arr1[0], arr1[1], arr1[2]};
//     // std::array<int, 3> triplet2 = {arr1[0], arr1[1], arr1[2]};
//     // std::array<int, 3> triplet3 = {arr1[0], arr1[1], arr1[2]};
//     // if (std::ranges::is_permutation(triplet1, triplet2) and std::ranges::is_permutation(triplet1, triplet3) and std::ranges::is_permutation(triplet2, triplet3)) {
//     //     std::cout << "yes" << std::endl;
//     // }else {
//     //     std::cout << "no" << std::endl;
//     // }
//
//     // std::vector<Student> vec = {
//     //     {"Alice", "Smith", 20},
//     //     {"Bob", "Johnson", 22},
//     //     {"Charlie", "Williams", 21},
//     //     {"David", "Brown", 20},
//     //     {"Eve", "Davis", 22},
//     //     {"Frank", "Miller", 21},
//     //     {"Grace", "Smith", 19}
//     // };
//     //
//     // std::cout << "Original Vector:\n";
//     // std::ranges::for_each(vec, [](const Student& student) {
//     //     std::cout << student << "\n";
//     // });
//     // std::cout << "\n";
//     //
//     // std::ranges::sort(vec, [](const Student& a, const Student& b) {
//     //     if (a.age != b.age) {
//     //         return a.age < b.age;
//     //     }
//     //     return a.surname < b.surname;
//     // });
//     //
//     // // Print the sorted vector.  Again using std::ranges::for_each
//     // std::cout << "Sorted Vector (Youngest to Oldest, then Last Name):\n";
//     // std::ranges::for_each(vec, [](const Student& student) {
//     //     std::cout << student << "\n";
//     // });
//     // std::cout << "\n";
//
//     // auto modifier = [](int& x) {
//     //     x += 10;
//     // };
//     // auto num = 0;
//     // call(3, modifier, num);
//     // fmt::println("{}", num);
//     //
//     // auto first = Student("Giorno", "Giovanna");
//     // auto second = Student("Bruno", "Bucciarati");
//     // fmt::println("[{}] [{}] {}", first.name, second.surname, second);
//     //
//     // auto ints = std::vector<int>{3, 4, 5, 6, 7, 8, 9, 10};
//     // auto map = std::map<int, std::set<int>>{};
//     //
//     // for (auto e : ints) {
//     //     map[e % 3].insert(e);
//     // }
//     //
//     // for (auto pair : map) {
//     //     fmt::println("{} {}", pair.first, pair.second);
//     // }
//
//     std::map<int, std::string> my_map = {
//         {1, "apple"},
//         {2, "banana"},
//         {3, "cherry"}
//     };
//
//     std::vector<std::string> val_vec = values(my_map);
//     fmt::println("{}", val_vec);
//
//
//     auto words = std::vector<std::string>{
//         "the", "dog", "and", "frog",
//         "leaped", "barked", "and", "croaked"
//     };
//
//     auto map = std::map<int, std::string>{};
//
//     for (auto word : words) {
//         map[word.size()] += word.front();
//     }
//
//     for (auto pair : map) {
//         fmt::println("{} - {}", pair.first, pair.second);
//     }
//
//     //  Using double for map values.
//     auto my_map1 = std::map<int, double>{};
//
//     // Inserts elements into the map.
//     for (auto i = 0; i < 5; ++i) {
//         my_map1[i] = i * 1.5;
//     }
//     fmt::println("Map after insertions: {}", my_map1); // Print the map
//
//     fmt::println("my_map.size(): {}", my_map1.size()); // Print the size of the map.
//
//     auto start = 2;
//     for (auto i = start; i < 5; ++i) {
//         my_map1[i] = 10.0 / i;
//     }
//     fmt::println("Map after update: {}", my_map1);
//
//     // Iterate and print map.
//     for (const auto& pair : my_map1) {
//         fmt::println("({}, {})", pair.first, pair.second);
//     }
//
//     // Example usage with a vector of doubles.
//     std::vector<double> numbers = {1.0, 2.0, 3.0, 4.0, 5.0};
//     Stats stats = getStats(numbers);
//
//     std::cout << "Max: " << stats.max << std::endl;
//     std::cout << "Min: " << stats.min << std::endl;
//     std::cout << "Average: " << stats.average << std::endl;
//
//     // Example with another container (e.g., a list).  Requires #include <list>
//     std::list<double> values = {2.5, 1.0, 5.5, 3.0, 4.0};
//     Stats listStats = getStats(values);
//
//     std::cout << "List Max: " << listStats.max << std::endl;
//     std::cout << "List Min: " << listStats.min << std::endl;
//     std::cout << "List Average: " << listStats.average << std::endl;
    auto x = 5;
    auto fu = [x]{std::cout << x << " hi\n";return 0;};
    fun(fu);

    // Example with a vector (a range).
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    print(numbers); // Calls the container version of print

    // Example with a set (another range).
    std::set<std::string> fruits = {"apple", "banana", "cherry"};
    print(fruits); // Calls the container version of print

    // Example with an int (a single object).
    int count = 10;
    print(count); // Calls the object version of print

    // Example with a double (another single object).
    double pi = 3.14159;
    print(pi); // Calls the object version of print



    std::cout << hasSize<decltype(fruits)>;

    clazz::Point p1; // No () for default constructor in C++
    p1.x = 1;
    p1.y = 2;
    strukt::Point p2;
    p2.x = 1;
    p2.y = 2;
    fmt::println("p1: x = {}, y = {}", p1.x, p1.y);
    fmt::println("p2: x = {}, y = {}", p2.x, p2.y);
    fmt::println("\n");

    // occurrences[c] += 1; // c will give ASCII value
    std::string text = "hello";
    std::map<char, int> occurrences;
    for (char c : text) {
        occurrences[c]++; // c is implicitly converted to its ASCII value for map access
    }
    fmt::println("Character occurrences: ");
    for (const auto& pair : occurrences) {
        fmt::println("  '{}': {}", pair.first, pair.second);
    }
    fmt::println("\n");

    // static_cast<char>(i), //(char)i,
    int intValue = 65; // ASCII value for 'A'
    char charValue1 = static_cast<char>(intValue); // Preferred C++ style
    char charValue2 = (char)intValue;             // C-style cast (less safe)
    fmt::println("Casting int to char: {} {}", charValue1, charValue2); // Both print 'A'
    fmt::println("\n");

    // std::map<char, int>(); // alike set
    std::map<char, int> charToIntMap; // Stores key-value pairs, keys are unique
    charToIntMap['a'] = 1;
    charToIntMap['b'] = 2;
    charToIntMap['c'] = 3;
    fmt::println("charToIntMap: ");
    for (const auto& pair : charToIntMap) {
        fmt::println("  {} : {}", pair.first, pair.second);
    }
     fmt::println("\n");

    // auto const pair = std::pair<char, int>('a', 5);
    // auto const [c, i] = pair;
    std::pair<char, int> const myPair('a', 5); // Creating a pair
    auto const [c, i] = myPair;             // Structured binding (C++17)
    fmt::println("Pair values: c = {}, i = {}", c, i); // Prints 'a' 5
    fmt::println("\n");

    // auto [from, to] =
    // auto new = ===> new.begin(), new.end()
    std::string myString = "hello world";
    auto [from, to] = std::make_pair(myString.front(), myString.back()); //using make_pair
    fmt::println("First char: {}, Last char: {}", from, to);

    // auto new = myString.begin(); // Example of getting iterator.
    // auto newEnd = myString.end();
     fmt::println("\n");

    // auto array = std::array<int, 5>{1, 2, 3, 4, 5};
    std::array<int, 5> myArray = {1, 2, 3, 4, 5}; // Fixed-size array
    fmt::println("Array elements: {}", myArray);
    fmt::println("Array size: {}", myArray.size());
     fmt::println("\n");

    // Chapter 5.2:
    // enum class Direction {North, East, South, West};
    // auto currentDirection = Direction();
    // currentDirection = Direction::West;
    enum class Direction { North, East, South, West }; // Scoped enum
    Direction currentDirection = Direction::West;      // Initialization
    fmt::println("Current direction: {}", static_cast<int>(currentDirection)); // Cast to int for output
     fmt::println("\n");

    // Chapter 5.3:
    // namespace clazz {class Point {public:int x;int y;};}
    // namespace strukt {struct Point {// private:int x;int y;};}
    // auto p1 = clazz::Point();p1.x = 1;p1.y = 2;
    // auto p2 = strukt::Point();p2.x = 1;p2.y = 2;

    Point2D myPoint{ 3.0, 4.0 };
    auto pointPair = format_as(myPoint);
    fmt::println("Point as pair: ({}, {})", pointPair.first, pointPair.second);

    double distance = std::hypot(myPoint.x, myPoint.y);
    fmt::println("Distance from origin: {}", distance);

    auto fibonacci = [n = 0, m = 1]() mutable {
        auto result = n;
        auto temp = n + m;
        n = m;
        m = temp;
        return result;
    };

    fmt::println("Fibonacci sequence:");
    for (int i = 0; i < 10; ++i) {
        fmt::println("{}", fibonacci());
    }

    return 0;

}


// #include <iostream>
// #include <cmath>
// #include <vector>
// #include <random>
// #include <algorithm>
// #include <limits>
//
// struct Point {
//     double x;
//     double y;
//
//     void display() const {
//         std::cout << "[ " << x << ", " << y << " ]";
//     }
//
//     double distanceTo(const Point& other) const {
//         double dx = x - other.x;
//         double dy = y - other.y;
//         return std::sqrt(dx * dx + dy * dy);
//     }
//
//     void changeCoordinates(double newX, double newY) {
//         x = newX;
//         y = newY;
//     }
// };
//
// struct Rectangle {
//     Point bottomLeft;
//     Point topRight;
//
//     Rectangle(const Point& bl, const Point& tr) : bottomLeft(bl), topRight(tr) {}
//
//     Rectangle() : bottomLeft({std::numeric_limits<double>::max(), std::numeric_limits<double>::max()}),
//                   topRight({std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest()}) {}
//
//     void display() const {
//         std::cout << "Bottom-Left: ";
//         bottomLeft.display();
//         std::cout << ", Top-Right: ";
//         topRight.display();
//         std::cout << std::endl;
//     }
//
//     bool contains(const Point& p) const {
//         return p.x >= bottomLeft.x && p.x <= topRight.x &&
//                p.y >= bottomLeft.y && p.y <= topRight.y;
//     }
//
//     void expandToContain(const Point& p) {
//         if (p.x < bottomLeft.x) {
//             bottomLeft.x = p.x;
//         }
//         if (p.y < bottomLeft.y) {
//             bottomLeft.y = p.y;
//         }
//         if (p.x > topRight.x) {
//             topRight.x = p.x;
//         }
//         if (p.y > topRight.y) {
//             topRight.y = p.y;
//         }
//     }
// };
//
// // int main() {
// //     Point p1{2.5, 3.0};
// //     Point p2{-1.0, 5.0};
// //
// //     std::cout << "Point 1 coordinates: ";
// //     p1.display();
// //     std::cout << std::endl;
// //
// //     std::cout << "Point 2 coordinates: ";
// //     p2.display();
// //     std::cout << std::endl;
// //
// //     double distance = p1.distanceTo(p2);
// //     std::cout << "Distance between Point 1 and Point 2: " << distance << std::endl;
// //
// //     p1.changeCoordinates(0.0, 0.0);
// //     std::cout << "Point 1 coordinates after change: ";
// //     p1.display();
// //     std::cout << std::endl;
// //
// //     Point bl{1.0, 1.0};
// //     Point tr{5.0, 4.0};
// //     Rectangle rect1(bl, tr);
// //     std::cout << "Rectangle 1: ";
// //     rect1.display();
// //
// //     Point p3{3.0, 2.0};
// //     Point p4{6.0, 3.0};
// //     std::cout << "Does Rectangle 1 contain Point 3? " << (rect1.contains(p3) ? "Yes" : "No") << std::endl;
// //     std::cout << "Does Rectangle 1 contain Point 4? " << (rect1.contains(p4) ? "Yes" : "No") << std::endl;
// //
// //     std::vector<Point> randomPoints(20);
// //     std::random_device rd;
// //     std::mt19937 gen(rd());
// //     std::uniform_real_distribution<> distrib(-10.0, 10.0);
// //
// //     std::cout << "\nRandomly generated points:\n";
// //     for (auto& p : randomPoints) {
// //         p.x = distrib(gen);
// //         p.y = distrib(gen);
// //         p.display();
// //         std::cout << std::endl;
// //     }
// //     Rectangle smallestRect;
// //     for (const auto& p : randomPoints) {
// //         smallestRect.expandToContain(p);
// //     }
// //
// //     std::cout << "\nSmallest rectangle containing all points:\n";
// //     smallestRect.display();
// //
// //     return 0;
// // }