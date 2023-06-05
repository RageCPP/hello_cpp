#include <iostream>
#include <string>
#include <utility>
#include <array>

class People
{
    std::string name;

  public:
    explicit People(std::string name) : name{std::move(name)}
    {
    }
    void set_name(std::string s)
    {
        name = std::move(s);
    }
    void say_name()
    {
        std::cout << name << std::endl;
    }
};

void add_people(People &p)
{
    p.say_name();
    p.set_name("tom");
}

void people_test()
{
    std::string name{"elliot"};
    People w{name};
    w.set_name("fish");
    add_people(w);
    w.say_name();
}

void direct_init_list() {
    std::initializer_list<int> list_cpp17 { 1, 12 };
}

void array_cout(int *p, size_t size) {
    for(std::size_t i = 0; i < size; i+=1) {
        std::cout << "array_cout:" << p[i] << std::endl;
    }
}

void about_array_uniform_initialization() {
    std::array<int, 5> automatic_store { 4, 5, 6, 7};
    std::array<int, 5>* free_store { new std::array<int, 5> {1,2,3,4,5} };
    std::cout << automatic_store[0] << std::endl;
    std::cout << (*free_store)[0] << std::endl;
    std::cout << "---- stack ----" << std::endl;
    array_cout(automatic_store.data(), 5);
    std::cout << "---- free store ----" << std::endl;

    int* free_store_ptr { free_store->data() };
    array_cout(free_store_ptr, 5);

    delete free_store;
    free_store = nullptr;
}

int main()
{
    return 0;
}
