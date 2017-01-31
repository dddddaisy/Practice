#include <iostream>
#include <vector>
using namespace std;

int main(void)
{
    vector<int> integral_vec(5);
    vector<int> ::iterator ptr;

    for(ptr=integral_vec.begin();ptr!=integral_vec.end();ptr++)
        cout<<*ptr<<" ";
    cout<<endl<<integral_vec.size()<<endl;

    return 0;
}
