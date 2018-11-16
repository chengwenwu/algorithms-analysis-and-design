#include <iostream>
using namespace std;
void merge(int array[], int aarray[], int alength, int barray[], int blength)
{
	int acounter = 0, bcounter = 0; 
	for(int counter = 0; counter < alength + blength; counter++)
	{
		if(acounter < alength && bcounter < blength)
		{
			if(aarray[acounter] < barray[bcounter])
			{
				array[counter] = aarray[acounter];
				acounter++;
			}
			else
			{
				array[counter] = barray[bcounter];
				bcounter++;
			}

		}
		else
		{
			if( acounter == alength)
			{
				for(int counter3 = counter; counter3 < blength+alength; counter3++)
				{
					array[counter3] = barray[bcounter];
					bcounter++;
				}
				break;
			}
			else
			{
				for(int counter3 = counter; counter3 < alength+blength; counter3++)
				{
					array[counter3] = aarray[acounter];
					acounter++;
				}
				break;
			}
		}
	}
	delete []aarray;
	delete []barray;
}
void mergeSort(int array[], int length)
{
	if(length == 1)
		return ;
	int alength = 0, blength = 0;
	if(length % 2 == 0)
	{
		alength = blength = length/2;
	}
	else
	{
		alength = length/2 +1;
		blength = length/2;
	}
	int *aarray = new int[alength],
		*barray = new int[blength];


	for(int counter1 = 0; counter1 < alength; counter1++)
	{
		aarray[counter1] = array[counter1];
	}
	for(int counter2 = 0; counter2 < blength; counter2++)
	{
		barray[counter2] = array[counter2 + alength];
	}
	mergeSort(aarray, alength);
	mergeSort(barray, blength);
	merge(array, aarray, alength, barray, blength);
	return ;
}
int main()
{
	int array[] = {8,5,6,1,4,2,3,9,8,7,5,2,1,5,10,12,555,999,55};
	mergeSort(array,19);
	for(int counter = 0; counter < 19; counter++)
	{
		cout<<array[counter]<<' ';
	}
	cout<<endl;
	return 0;
}