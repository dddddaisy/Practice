#include <iostream>
#include <stack>
#include <string>
using namespace std;

int priority(char c);
void prefix();
void postfix();

int main(void)
{
    int fix;
    cout<<"1-prefix 2-postfix 0-exit"<<endl;
    cout<<"I want to do : ";
    while(cin>>fix)
    {
        switch(fix)
        {
        case 1:
            prefix();
            break;
        case 2:
            postfix();
            break;
        case 0:
            return 0;
        default:
            cout<<"Wrong input!"<<endl;
        }

        cout<<endl;
        cout<<"-----------------------"<<endl;
        cout<<"1-prefix 2-postfix"<<endl;
        cout<<"I want to do : ";
    }

    return 0;
}

int priority(char c)
{
    switch(c)
    {
        case '+': return 1;
        case '-': return 1;
        case '*': return 2;
        case '/': return 2;
        default: return 0;
    }
}

void prefix()
{
    int i;
    string expr;
    cout<<"expression: ";
    cin>>expr;

    for(i=0;i<expr.length();i++)
    {

    }
}

void postfix()
{
    int i,num;
    stack<char> store,ans,output;
    string question;

    cout<<"START > ";
    cin>>question;
    for(i=0;i<question.size();i++)
    {
        if(question[i]>='0'&&question[i]<='9')
            ans.push(question[i]);
        else
        {
            if(store.empty()||question[i]=='(')
                store.push(question[i]);
            else if(question[i]==')')
            {
                while(store.top()!='(')
                {
                    ans.push(store.top());
                    store.pop();
                }
                store.pop();
            }
            else
            {
                while(!store.empty())
                {
                    if(priority(store.top()) >= priority(question[i]))
                    {
                        ans.push(store.top());
                        store.pop();
                    }
                    else break;
                }
                store.push(question[i]);
            }
        }
    }
    while(!store.empty())
    {
        ans.push(store.top());
        store.pop();
    }

    cout<<"ANS > ";
    /*inverse*/
    while(!ans.empty())
    {
        output.push(ans.top());
        ans.pop();
    }
    /*output*/
    num = 0;
    while(!output.empty())
    {
        cout<<output.top();
        output.pop();
    }

}
