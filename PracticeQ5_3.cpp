#include <iostream>
using namespace std;
#include <algorithm>   //to use copy, must include this
#include <vector>     
#include <iterator>
#include <list>// to use ostream_iterator
#include <numeric>
int main()
{
	vector <int> vectnum;
	vector <int>::iterator it=vectnum.begin();

	int x,max,min,avg; 
	cout << "Enter a real number or 0 to stop" << endl;
	cin >> x;
	

	while (x != 0)
	{
		vectnum.push_back(x);
		cout << "Enter a real number or 0 to stop" << endl;
		cin >> x;
		
	}

	min = *min_element(vectnum.begin(), vectnum.end());
	max = *max_element(vectnum.begin(), vectnum.end());
	avg = accumulate(vectnum.begin(), vectnum.end(), 0);

	cout << "MIN NUM: " << min << endl;
	cout << "MAX NUM: " << max << endl;
	cout << "AVG NUM: " << avg << endl;

	return 0;


}