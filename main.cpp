#include <iostream>
#include "Shared_Ptr.h"
#include "Weak_Ptr.h"

class Test {
public:
      Test() { std::cout << "Test created!\n"; }
      ~Test() { std::cout << "Test destroyed!\n"; }
      void Print() { std::cout << "Printing from Test\n"; }
};

int main()
{
      std::cout << "\n\t\t\tShared Pointer Examples:\n\n";
      {
            SharedPtr<Test> sp1(new Test);
            sp1.operator->()->Print();     // == sp1->Print()
            std::cout << "sp1 count = " << sp1.UseCount() << '\n'; // = 1

            {
                  SharedPtr<Test> sp2 = sp1;
                  std::cout << "\nsp1 count = " << sp1.UseCount() << '\n'; // = 2
                  std::cout << "sp2 count = " << sp2.UseCount() << '\n'; // = 2

                  SharedPtr<Test> sp3;
                  sp3.operator=(sp2); // == (sp3 = sp2); Test obj. is now shared between sp1, sp2, sp3
                  std::cout << "sp3 count = " << sp3.UseCount() << '\n'; // = 3

                  SharedPtr<Test> sp4(sp3);
                  std::cout << "sp4 count = " << sp4.UseCount() << '\n'; // = 4

                  SharedPtr<Test> sp5;
                  sp5.Swap(sp4);
                  std::cout << "sp5 count = " << sp5.UseCount() << '\n'; // = 4 because  
                  std::cout << "sp4 count = " << sp4.UseCount() << '\n'; // sp4.res is for now nullptr; that is, sp4' use count = 0

            } // sp2, sp3 and sp5 are no longer sharing Test object, so it causes to decrement use' count

            std::cout << "\nsp1 count = " << sp1.UseCount() << '\n'; // = 1
            sp1.Reset(); // Test obj. should be destroyed 'cause no SharedPtr is pointing to it
            std::cout << "sp1 count = " << sp1.UseCount() << '\n'; // = 0
      }

      std::cout << "\n\n\t\t\tWeak Pointer Examples:\n\n";
      {
            SharedPtr<Test> sp6(new Test);
            WeakPtr<Test> wp1;
            wp1.operator=(sp6); // == (wp1 = sp6) 
            std::cout << "wp1 count = " << wp1.UseCount() << '\n'; // = 1
            std::cout << "wp1 expired = " << wp1.Expired() << '\n'; // = (0 <=> false)

            {
                  SharedPtr<Test> sp7 = wp1.Lock();
                  sp7->Print();

                  std::cout << "\nsp7 count = " << sp7.UseCount() << '\n';  // = 2
                  std::cout << "wp1 count = " << wp1.UseCount() << '\n';  // = 2
                  std::cout << "wp1 expired = " << wp1.Expired() << '\n'; // = (0 <=> false)

            } // sp7 is destroyed, but Test obj. still exists 'cause sp6 is still pointing to it

            std::cout << "\nwp1 count = " << wp1.UseCount() << '\n'; // =  1
            std::cout << "wp1 expired = " << wp1.Expired() << '\n'; // = (0 <=> false)
            sp6.Reset(); // Then the Test obj. should be destroyed here

            std::cout << "\nwp1 count = " << wp1.UseCount() << '\n'; // = 0
            std::cout << "wp1 expired = " << wp1.Expired() << '\n'; // (1 <=> true)
      }

      return 0;
}