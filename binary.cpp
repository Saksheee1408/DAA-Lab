#include<iostream>
using namespace std;
class binary{
    public:
    int arr[10];
    int size;
    int element;
    void input()
    {
        cout<<"Enter the size of array:"<<endl;
        cin>>size;
        cout<<"Enter elements:"<<endl;
        for(int i=0;i<size;i++)
        {
            cin>>arr[i];
        }
        cout<<"Enter element to be found:"<<endl;
        cin>>element;
    }
    void sort()
    {
        for(int i=0;i<size-1;i++)
        {
            for(int j=i+1;j<size;j++)
            {
                if(arr[i]>arr[j])
                {
                    int temp=arr[i];
                    arr[i]=arr[j];
                    arr[j]=temp;
                }
            }
            
        }
    }
   int binary_search()
    {
        int start=0;
        int end=size-1;
        while(start<end)
        {
            int mid=(start+end)/2;
            if(arr[mid]==element)
            {
                return mid;
            }
            else if(element>arr[mid])
            {
                start=mid+1;
            }
            else
            {
                end=mid-1;
            }
        }
        return -1;
 
    }
};
int main()
{
    binary obj;
    obj.input();
    obj.sort();
    int result=obj.binary_search();
    if (result != -1) {
        cout << "Element found at index: " << result << endl;
    } else {
        cout << "Element not found." << endl;
    }
    return 0;
}
/*Time Complexity:O(log2n)
Space Complexity:O(logn)*/
