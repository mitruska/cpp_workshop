// C++ workshop
// Try: https://godbolt.org/z/1f44e3M87

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

#include <algorithm>
#include <cstdint>
#include <functional>
#include <iostream>
#include <map>
#include <vector>

//// II.1 Create class "User"
class User {
   public:
    User(const std::string& name, uint32_t age, uint32_t followers_count = 0)
        : name_(name), age_(age), followers_count_(followers_count) {}

    User(const std::pair<const std::string, uint32_t>& name_age)
        : name_(name_age.first), age_(name_age.second), followers_count_(0) {}

    std::string get_name() const { return name_; }
    uint32_t get_age() const { return age_; }
    uint32_t get_followers_count() const { return followers_count_; }

    void set_followers_count(uint32_t followers_count) {
        followers_count_ = followers_count;
    }

    // Overloaded operators useful for sort or looking for min/max
    bool operator<(const User& usr) const {
        return followers_count_ < usr.get_followers_count();
    }
    bool operator>(const User& usr) const {
        return followers_count_ > usr.get_followers_count();
    }

    //// III.6 Overloaded ostream operator to print the object
    friend std::ostream& operator<<(std::ostream& out, const User& usr) {
        out << "{Name: " << usr.name_ << ", ";
        out << "Age: " << usr.age_ << ", ";
        out << "Followers: " << usr.followers_count_ << "}";
        return out;
    }

   private:
    std::string name_ = "";
    uint32_t age_ = 0;
    uint32_t followers_count_ = 0;
};

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

    //// I.1 Find the youngest user
    const auto min_elem_it =
        std::min_element(users_age.cbegin(), users_age.cend(),
                         [](const auto& user_a, const auto& user_b) {
                             return user_a.second < user_b.second;
                         });

    // [Warining] std::max_element compares the keys by default
    // The following will point to the first element in the map
    // std::min_element(users_age.cbegin(), users_age.cend());

    std::cout << "\nI.1 The youngest user is " << (*min_elem_it).first
              << " with age " << (*min_elem_it).second << std::endl;

    //// I.2 Find one of the oldest users
    const auto max_elem_it =
        std::max_element(users_age.cbegin(), users_age.cend(),
                         [](const auto& user_a, const auto& user_b) {
                             return user_a.second < user_b.second;
                         });
    std::cout << "\nI.2 One of the oldest user is " << (*max_elem_it).first
              << " with age " << (*max_elem_it).second << std::endl;

    //// I.3 Find all of the adult users (just printing)
    std::cout << "\nI.3 Adult users only: \n";
    //// In a for loop
    for (const auto& usr : users_age) {
        std::cout << usr.first << ":" << usr.second << ",";
    }
    //// Or with std::for_each
    std::for_each(users_age.begin(), users_age.end(), [](const auto& usr) {
        if (usr.second >= 18)
            std::cout << usr.first << ":" << usr.second << ",";
    });

    //// I.3 Find all of the adult users (by copy)
    std::map<std::string, uint32_t> adult_users;
    std::copy_if(users_age.begin(), users_age.end(),
                 std::inserter(adult_users, adult_users.end()),
                 [](const auto& usr) { return usr.second >= 18; });

    std::cout << "\nI.3 Adult users only: ";
    print_elements(adult_users);

    // [Warining] Without std::inserter, error: use of deleted function pair&
    // operator=(const pair&) = delete std::copy_if(users_age.begin(),
    // users_age.end(), adult_users.begin(), [](const auto& usr){return
    // usr.second >= 18;});

    //// I.4 Add new user to the map
    users_age.emplace("Kate", 27);
    std::cout << "\nI.4 Users map with new user:";
    print_elements(users_age);

    //// II.2 Create vector of users initialized with info from "users_age" map
    std::vector<User> users;

    // [Warning] std::copy works with additional constructor User(const
    // std::pair<const std::string, uint32_t>& name_age)
    // std::copy(users_age.begin(), users_age.end(), std::back_inserter(users));
    // print_elements(users);

    // std::transform can use copy logic from lambda
    std::transform(users_age.cbegin(), users_age.cend(),
                   std::back_inserter(users), [](const auto& usr) {
                       return User{usr.first, usr.second};
                   });
    print_elements(users);

    std::cout << "\nII.2 Users map:";
    print_elements(users_age);
    std::cout << "\nII.2 Users copied to vector:";
    print_elements(users);

    //// III.4 Add name and age of your friend to the users
    users.emplace_back("Tom", 30);
    std::cout << "\nIII.4 Users vector with new user:";
    print_elements(users);

    //// IV.2 Modify the vector of users and update the "followers_count" of
    /// each user
    std::for_each(users.begin(), users.end(), [](auto& usr) {
        usr.set_followers_count((100 + usr.get_age()) * 10);
    });

    std::cout << "\nIV.2 Users after followers init:";
    print_elements(users);

    //// IV.3. Find the most popular user (the highest number of followers)
    auto most_pupular_it = std::max_element(
        users.cbegin(), users.cend(),
        [](const auto& user_a, const auto& user_b) {
            return user_a.get_followers_count() < user_b.get_followers_count();
        });
    std::cout << "\nIV.3 The most popular user is " << (*most_pupular_it);

    //// IV.3. Find the most popular user (the highest number of followers)
    //// By overloaded operator< in the User class
    most_pupular_it = std::max_element(users.cbegin(), users.cend());
    std::cout << "\nIV.3 The most popular user is " << (*most_pupular_it);

    //// IV.4 Sort the vector of by number of followers (descending)
    std::sort(
        users.begin(), users.end(), [](const auto& usr_a, const auto& usr_b) {
            return usr_a.get_followers_count() > usr_b.get_followers_count();
        });
    std::cout << "\n\nIV.4 Users sorted by number of followers (descending): ";
    print_elements(users);

    //// IV.4 Sort the vector of by number of followers (ascending)
    //// By overloaded operator< in the User class
    std::sort(users.begin(), users.end());
    std::cout << "\nIV.4 Users sorted by number of followers (ascending): ";
    print_elements(users);

    //// IV.4 Sort the vector of by number of followers (descending)
    //// By overloaded operator> in the User class
    //// and function object greater (C++14)
    std::sort(users.begin(), users.end(), std::greater<>());

    std::cout << "\nIV.4 Users sorted by number of followers (descending) ";
    print_elements(users);
}
