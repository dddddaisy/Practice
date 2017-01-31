#include <iostream>
#include <stack>
using namespace std;

int main(void)
{
    stack<int> a;
    int oper,data;
    cout<<"------------STACK TRY------------"<<endl;
    cout<<"1-push 2-pop 3-size 4-clean 0-end"<<endl;
    cout<<"I want to : ";
    while(cin>>oper)
    {
        switch(oper)
        {
        case 1:
            cout<<"number pop to stack: ";
            cin>>data;
            a.push(data);
            break;
        case 2:
            a.pop();
            cout<<"pop top element successful"<<endl;
            break;
        case 3:
            cout<<"now stack size is "<<a.size()<<endl;
            break;
        case 4:
            while(!a.empty())
            {
                a.pop();
            }
            cout<<"stack.empty() = "<<a.empty()<<endl;
            break;
        default:
            cout<<"Wrong input!!"<<endl;
            break;
        }

        cout<<endl;
        cout<<"------------STACK TRY------------"<<endl;
        cout<<"1-push 2-pop 3-size 4-clean 0-end"<<endl;
        cout<<"I want to : ";
    }
    return 0;
}
