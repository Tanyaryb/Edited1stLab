#include "CppUnitTest.h"
#include "Map.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
		
	public:
		
		TEST_METHOD(insert_test)
		{
			Map Tree;
			Tree.insert(1, 6);
			bool now = Tree.find(2);
			Tree.insert(2, 10);
			bool later = Tree.find(2);
			Assert::AreEqual(now, !later);



		}
		TEST_METHOD(remove_test)
		{
			Map Tree;
			Tree.insert(1, 6);
			bool prev = Tree.find(1);
			Tree.remove(1);
			bool after = Tree.find(1);
			Assert::AreEqual(prev, !after);
			
		}
		TEST_METHOD(clear_test)
		{
			Map Tree;
			Tree.insert(1, 9);
			Tree.insert(2, 11);
			Tree.clear();
			Assert::AreEqual(!Tree.find(1), !Tree.find(2));
		}
		TEST_METHOD(find_test)
		{
			Map Tree;
			bool now = Tree.find(1);
			Tree.insert(1, 20);
			bool after = Tree.find(1);
			Assert::AreEqual(!now, after);
		}
		TEST_METHOD(print_test)
		{
			Map Tree;
			bool now = Tree.print();
			Tree.insert(1, 15);
			Tree.insert(2, 3);
			bool after = Tree.print();
			Assert::AreEqual(!now, after);
		}
		TEST_METHOD(get_keys_test)
		{
			Map Tree;
			Tree.insert(1, 5);
			Tree.insert(2, 6);
			List list = Tree.get_keys();
			int sum = 0;
			while (!list.isEmpty())
			{
				sum += list.getData();
				list.Next();
			}
			Assert::IsTrue(sum == 3);
		}
		TEST_METHOD(get_value_test)
		{
			Map Tree;
			Tree.insert(1, 5);
			Tree.insert(2, 6);
			List list = Tree.get_values();
			int sum = 0;
			while (!list.isEmpty())
			{
				sum += list.getData();
				list.Next();
			}
			Assert::IsTrue(sum == 11);
		}
	};
}
