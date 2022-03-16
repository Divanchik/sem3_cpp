/**
 * \file
 * Body of the program
 */
#include <iostream>
#include <vector>
#include <list>
#include "my_vector.h"
#include "my_list.h"

template <typename T>
using CollectionType = Vector<T>;
using collection = CollectionType<int>;

void print_container(collection& a, const char* name)
{
    std::cout << name << " == [ ";
    auto tmp = a.begin();
    for (size_t i = 0; i < a.size()-1; i++, tmp++)
    {
        std::cout << *tmp << ", ";
    }
    std::cout << *tmp << " ]" << std::endl;
}
void flag(const char *message) { std::cout << message << std::endl; }

/// 'main' function \return Exit code('0' if program ended successfully)
int main()
{
    try
    {
        // collection a;
        // collection b(10);
        // auto tmp = b.begin();
        // for (int i = 0; i < 10; i++, tmp++)
        // {
        //     *tmp = i * i;
        //     std::cout << "b[" << i << "] = " << *tmp << std::endl;
        // }
        // a = b;
        // collection c(a);
        // collection d = std::move(a);
        // // print_container(a);
        // // b.erase(b.begin());
        // print_container(b, "b");
        // c.erase(c.begin());
        // c.erase(c.begin());
        // print_container(c, "c");
        // print_container(d, "d");
        // return 0;
        collection v1;
        v1.insert(v1.end(), 1);
        v1.insert(v1.end(), 67);
        print_container(v1, "v1");

        collection v2(10);
        auto tmp = v2.begin();
        for (size_t i = 1; i <= v2.size(); ++i)
        {
            *tmp = (int)(i * i);
            ++tmp;
        }
        print_container(v2, "v2");

        collection v3(v2);
        v3.erase(v3.begin());
        print_container(v3, "v3");

        collection v4 = std::move(v3);
        //v4.erase(v4.end());
        v4.erase(v4.begin());
        print_container(v4, "v4");

        auto tmp1 = v4.begin();
        tmp1++;
        v4.insert(tmp1, 228);
        print_container(v4, "v4");
        v4.erase(tmp1);
        print_container(v4, "v4");
    }
    catch (const char *message)
    {
        std::cout << "Program throwed an exception: " << message << std::endl;
    }
}