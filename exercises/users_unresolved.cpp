// C++ workshop

// Part I:
// For the "users_age" map:
// 1. Find the youngest user
// 2. Find one of the oldest users
// 3. Find all of the adults (age 18+)
// 4. Add your name and age to the "users_age" map
// *(your name and age doesn't need to be real:))

// Part II:
// 1. Create class "User" with "name" and "age" members
// 2. Create vector of users initialized with info from "users_age" map

// Part III:
// For the "users" vector:
// 1. Find the youngest user
// 2. Find one of the oldest person
// 3. Find all of the adults (age 18+)
// 4. Add name and age of your friend to the users
// 5. Sort the vector from the youngest to the oldest users
// 6. Extend User class with overloaded ostream operator to print the user
// object
//    *Refactor the code if some redundant print logic has been added,
//    "print_elements" function should be reusable

// Part IV:
// 1. Extend the User class with "followers_count" member.
//    Remember about updating constructor and ostream operator.
// 2. Modify the vector of users and update the "followers_count" of each user
//    based on the following formula followers_count = (100 + age) * 10
// 3. Find the most popular user (the highest number of followers)
// 4. Sort the vector by number of followers (descending and ascending)

// Part V (Extra):
// 1. Create custom container for users
// 2. Add iterator for the container, implement begin() and end()
// 3. Try to print elements from the container
// 4. Using iterators and algorithms repeat Part III for the custom container
//    (If Iterators are implemented correctly, solutions for std::vector should
//    be reusable)

#include <cstdint>
#include <iostream>
#include <map>

template <typename T>
void print_elements(const T& container) {
    std::cout << "\n{";
    for (const auto& element : container) {
        std::cout << element << ",";
    }
    std::cout << "}" << std::endl;
}

template <typename T_KEY, typename T_VALUE>
void print_elements(const std::map<T_KEY, T_VALUE>& container) {
    std::cout << "\n{";
    for (const auto& element : container) {
        std::cout << "{" << element.first << ", " << element.second << "},";
    }
    std::cout << "}" << std::endl;
}

int main() {
    std::map<std::string, uint32_t> users_age{{"BruNo", 24},
                                              {"Ann@", 15},
                                              {"dian_a", 17},
                                              {"1gor", 24},
                                              {"Cloe", 18}};
    std::cout << "Users age map: ";
    print_elements(users_age);
}
