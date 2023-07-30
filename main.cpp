#include <array>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <optional>
#include <string>
#include <thread>
#include <utility>
#include <vector>
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

[[maybe_unused]] void people_test()
{
    std::string name{"elliot"};
    People w{name};
    w.set_name("fish");
    add_people(w);
    w.say_name();
}

[[maybe_unused]] void direct_init_list()
{
    std::initializer_list<int> list_cpp17{1, 12};
    for (const int &i : list_cpp17)
    {
        std::cout << i << std::endl;
    }
}

void array_cout(int *p, size_t size)
{
    for (std::size_t i = 0; i < size; i += 1)
    {
        std::cout << "array_cout:" << p[i] << std::endl;
    }
}

[[maybe_unused]] void about_array_uniform_initialization()
{
    std::array<int, 5> automatic_store{4, 5, 6, 7};
    std::array<int, 5> *free_store{new std::array<int, 5>{1, 2, 3, 4, 5}};
    std::cout << automatic_store[0] << std::endl;
    std::cout << (*free_store)[0] << std::endl;
    std::cout << "---- stack ----" << std::endl;
    array_cout(automatic_store.data(), 5);
    std::cout << "---- free store ----" << std::endl;

    int *free_store_ptr{free_store->data()};
    array_cout(free_store_ptr, 5);

    delete free_store;
    free_store = nullptr; // 你会发现编译器会发出 The value is never used
                          // 的合理警告，请使用智能指针，这样可以避免争论是否应该在回收资源后设置指针为null

    int *raw_heap = new int[5];
    delete[] raw_heap;
    raw_heap = nullptr;
}

// if students use type std::vector<std::string>, 拷贝的会是std::vector本身，而不是传递像C风格数组那样复制指向首位的指针
void add_students(std::vector<std::string> &students)
{
    students.push_back("王瑞轩"); // https://stackoverflow.com/questions/4303513/push-back-vs-emplace-back 为了兼容性
                                  // 不要使用 emplace_back
    std::cout << students.at(0) << std::endl;
}

void students_read_vec()
{
    std::vector<std::string> students{};
    add_students(students);
    std::cout << students.at(0) << std::endl;
}

void add_students(std::array<std::string, 1> &students)
{
    students.at(0) = "王瑞轩";
    std::cout << students.at(0) << std::endl;
}

// 与 vec 同理
void students_read_array()
{
    std::array<std::string, 1> students{};
    add_students(students);
    std::cout << students.at(0) << std::endl;
}

// 注意此处拷贝的是数组中首个元素的指针
void add_students(std::string students[], int size)
{
    if (size > 0)
    {
        students[0] = "王瑞轩";
        std::cout << students[0] << std::endl;
    }
}
// CPP 加强版本写法 见Professional C++ P226
void add_students(std::string (&students)[1])
{
    students[0] = "王瑞轩";
    std::cout << students[0] << std::endl;
}

void students_read_array_c()
{
    std::string students[1]{};
    std::string students_2[2]{};
    add_students(students, 1);
    std::cout << students[0] << std::endl;

    // add_students(students_2)
}

class Hello
{
  public:
    std::string name{};
    Hello();
    ~Hello();
};
Hello::Hello()
{
    std::cout << "构造" << std::endl;
}
Hello::~Hello()
{
    std::cout << "析构" << std::endl;
}
void copy_hello(Hello hello)
{
    hello.name = "李柯";
    std::cout << hello.name << std::endl;
};
void ref_hell(Hello &hello){};
Hello copy_hello_return_copy(Hello hello)
{
    Hello h{};
    return h;
};

void test_copy_ref()
{
    Hello hello{};
    hello.name = "王瑞轩";
    copy_hello(hello);
    std::cout << hello.name << std::endl;
}

void test_ref()
{
    Hello a{};
    auto b = a;
    auto d = &b;
    auto c = &a;
}

struct Pet
{
    int age;
};

void pet_c_style_func(Pet** out)
{
//    Pet b {.age = 7};
//    *out = (Pet *)malloc(sizeof (struct Pet));
    (*out)->age = 5;
}
int test()
{
    Pet* out {nullptr};
    {
        Pet c {.age = 4};
        Pet* a = &c;
        pet_c_style_func(&a);
        out = a;
    }
    std::cout << out->age << std::endl;
}
void hello(int* p) {
    std::cout << "HELLO" << std::endl;
}
struct PeopleInfo {
    std::string name;
    int age;
};
int main() {
//    auto a = new int {1};
//    std::unique_ptr<int, decltype(&hello)> h {a, hello};
//    std::optional<std::unique_ptr<int, decltype(&hello)>> b {std::move(h)};
//    std::cout << *b.value() << std::endl;
    std::array<PeopleInfo, 2> l {PeopleInfo{.name = "123", .age = 2}};
    std::cout << l.at(l.size() - 2).name << std::endl;
}