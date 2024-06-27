#include<iostream>
#include"inc/matrix.hpp"
#include <cassert>

using namespace mt;
using namespace std;

int main()
{

	cout << "===Test 0===" << endl;
	{
		Mat22d X({ {
			{0,1},
			{0,2}
			} });

		try
		{
			cout << X.reverse() << endl;
		}

		catch (const exception& e)
		{
			cerr << e.what() << endl;
		}
	}

	cout << "=== Test 1 ===" << endl;

	{
		Matrix <int , 3,2> A({ {
			{1,2},
			{3,4},
			{6,5}
			} });

		Matrix <int, 2, 3> X({ {
			{1,2,0},
			{3,4,1}
			} });

		auto B =  A*X;
		cout << B << endl;
	}

	cout << "Done!" << endl;

	cout << "=== Test 2 ===" << endl;
	{
		
		Mat22d A({ {
		{1,1},
		{1,1}
		} });

		Mat22d X({ {
			{1,2},
			{3,4}
			} });

		Mat22d B = A - X;

		assert(B.get(0, 0) == 0);
		assert(B.get(0, 1) == -1);
		assert(B.get(1, 0) == -2);
		assert(B.get(1, 1) == -3);
	}

	cout << "Done!!" << endl;

	cout << "=== Test 3 ===" << endl;
	{
		Mat22d A({ {
		{1,1},
		{1,1}
		} });

		Mat22d X({ {
		{1,2},
		{3,4}
		} });

		Mat22d B = A + X;

		assert(B.get(0, 0) == 2);
		assert(B.get(0, 1) == 3);
		assert(B.get(1, 0) == 4);
		assert(B.get(1, 1) == 5);
	}
	cout << "Done!" << endl;

	cout << "=== Test 4 ===" << endl;
	{
		Mat22d A({ {
		{1,2},
		{3,4}
		} });

		Mat33d X({ {
		{1,2,3},
		{4,5,6},
		{7,8,9}
		} });

		assert(A.D() == -2);
		assert(X.D() == 0);
	}
	cout << "Done!" << endl;

	cout << "=== Test 5  === " << endl;
	{
		Mat22d X({ {
		{1,2},
		{3,4}
		} });
		Mat33d A({ {
		{2,5,7},
		{6,3,4},
		{5,-2,-3},
		} });


		Mat22d B = X.reverse();
		Mat33d C = A.reverse();
		assert(B.get(0, 0) == -2);
		assert(B.get(0, 1) == 1);
		assert(B.get(1, 0) == 1.5);
		assert(B.get(1, 1) == -0.5);

		assert(C.get(0, 0) == 1);
		assert(C.get(0, 1) == -1);
		assert(C.get(0, 2) == 1);
		assert(C.get(1, 0) == -38);
		assert(C.get(1, 1) == 41);
		assert(C.get(1, 2) == -34);
		assert(C.get(2, 0) == 27);
		assert(C.get(2, 1) == -29);
		assert(C.get(2, 2) == 24);
	}
	cout << "Done!" << endl;

	cout << "=== Test 6  === " << endl;
	{
		Matrix<int, 2, 3> X({ {
		{1,2,3},
		{4,5,6}
		} });
		Matrix<int, 3, 2> B = X.transposition();
		assert(B.get(0, 0) == 1);
		assert(B.get(1, 0) == 2);
		assert(B.get(2, 0) == 3);
		assert(B.get(0, 1) == 4);
		assert(B.get(1, 1) == 5);
		assert(B.get(2, 1) == 6);
		cout << B << endl;
	}
	cout << "Done!" << endl;
	
	

	Matrix<double, 3, 4> A({ {
		{2,4,1,36},
		{5,2,1,47},
		{2,3,4,37}
		} });

	 A.Gauss_method();

	
	


	return 0;

}