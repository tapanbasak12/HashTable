#include<bits/stdc++.h>
#include<iostream>
#include<fstream>

using namespace std;

//Run Command:  g++ main.cpp -o main; ./main file.txt;

int* T;
char* A;
int N;
int n,  ind;

void create(int val, int executionNo)
{
	ind = 0;
	delete[] T;
    delete[] A;
    N= val;
    if(executionNo > 0)
    {
        N=N*2;
        n=N*15;
    }
    else
    {
        n=N*15;
    }

    T= new int[N];
    A= new char[n];

    for(int i=0; i<N; i++)
        T[i]=-1;
    for(int i=0; i<n; i++)
        A[i]=' ';

}


int calculate(string str)
{
    int t=0;
    for (int i=0; i<str.length(); i++)
    {
        t+=str[i];
    }
    t=(t-2)%N;

    return t;
}


void Searching_word(string str)
{
    int t=0;
    t = calculate(str);
    int h;
    for (int i=0; i<N; i++)
    {
        int f=1;
        h=((t+i*i)%N);
        int location=T[h];
        if(location==-1)
        {
            continue;
        }
        for(int j=0; j<=str.length(); j++)
        {
            if(A[location+j]!=str[j])
            {
                f=0;
                break;
            }
        }
        if(f==1)
        {
            cout << str << " found at slot " << h<< endl;
            return;
        }

    }
    cout << str << " not found" <<endl;

}


bool Insertion_word(string str)
{
    int t=0, f=0, h=0;
    t = calculate(str);

    for (int i=0; i<N; i++)
    {
        h=((t+i*i)%N);
        if(T[h]==-1)
        {
            f=1;
            t=h;
            break;
        }
    }

    if(f==0)
    {
        return true;
    }

    T[t]=ind;
    for(int i=0; i<str.length(); i++)
    {
        A[ind]=str[i];
        ind++;
    }
    A[ind]='\0';
    ind++;

    return false;
}

bool Empty_check(int i)
{
    if(i==-1)
        return 1;
    else
        return 0;
}

void Print()
{
    printf("T\n");
    for (int i=0; i< N; i++)
    {
        if(Empty_check(T[i]))
           cout<<i <<":" <<endl;
        else
            cout<<i<<": "<<T[i] <<endl;
    }

    printf("A: ");
    for (int i=0; i< ind; i++)
    {
        if(A[i]=='\0')
            printf("%c",'\\');
        else
            printf("%c", A[i]);
    }
    printf("\n");
}


void Delete_word(string str)
{
    int t=0;
    t = calculate(str);
    int h;
    for (int i=0; i<N; i++)
    {
        int f=1;
        h=((t+i*i)%N);
        int location=T[h];
        if(location==-1)
            continue;
        for(int j=0; j<=str.length(); j++)
        {
            if(A[location+j]!=str[j])
            {
                f=0;
                break;
            }
        }
        if(f==1)
        {
            for(int j=0; j<str.length(); j++)
            {
                A[location+j]='*';
            }
            T[h]=-1;
            cout << str << " deleted from slot " << h << endl;
            return;
        }
    }
}

void Batch(string fileName) {

	int executionNo = 0;
	bool isProgramCompleted = false;
	bool overflowOccured = false;

	while (isProgramCompleted == false)
	{

		fstream fl;
		int command;
		string line;
		fl.open(fileName);
		overflowOccured= false;

		while (getline(fl, line))
		{
			istringstream ss(line);
			int command;
			ss>>command;
			if(command==10)
			{
				string str;
				ss>>str;
				overflowOccured = Insertion_word(str);
				if(overflowOccured){
					cout << "Overflow Occurs!" <<endl;
					break;
				}
			}

			else if(command==11)
			{
				string str;
				ss>>str;
				Delete_word(str);
			}

			else if(command==12)
			{
				string str;
				ss>>str;
				Searching_word(str);
			}

			else if(command==13)
			{
				string str;
				Print();
				ss>>str;
			}
			else if(command==14)
			{
				int val_t;
				ss>>val_t;
				create(val_t, executionNo);
			}

			else if(command==15)
			{
				string str;
				ss>>str;
			}
		}

		if (!overflowOccured){
			isProgramCompleted = true;
		}
		executionNo++;

		fl.close();
	}
}


int main(int argc, char *argv[])
{
    string fileName;
    fileName=argv[1];
	Batch(fileName);
    return 0;
}


