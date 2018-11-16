#include <iostream>
using namespace std;
void insertSort(int array[], int length)
{
	for(int counter1 = 1; counter1 < length; counter1++)
	{
		int temp = array[counter1];
		int counter2 = counter1 - 1;
		for(counter2 = counter1 - 1; counter2 >= 0; counter2--)
		{
			if(array[counter2] > temp)
			{
				array[counter2 + 1] = array[counter2];
			}
			else 
				break;
		}
		array[counter2 + 1] = temp;
	}
}
int main()
{
	int array[] = {8,5,6,1,4,2,3,9,8,7,5,2,1,5,10,12,555,999,55};
	insertSort(array,19);
	for(int counter = 0; counter < 19; counter++)
	{
		cout<<array[counter]<<' ';
	}
	cout<<endl;
	return 0;
}