#include <stdio.h>

class A
{
public:
    A(int value) : dunoVal(value) {}
    void Say()
    {
        printf("Class A %i\n",dunoVal);
    }
    int dunoVal;
};

class B
{
public:
    A& m_aRef;
    B(A& aRef) : m_aRef(aRef)
    {
        // m_aRef = NULL;
    }
    void Say()
    {
        // printf("Class B\n");
        m_aRef.Say();
    }
};
void swap(A& first, A& second)
{
    A temp = first;
    first = second;
    second = temp;
}
int main()
{

    A a1 = A(10);
    A a2 = A(20);

    A& a1Ref = a1;
    A& a2Ref = a2;

    a1.Say();
    a2.Say();


    a1.Say();
    a2.Say();




    // B b(*a);

    // b.Say();

    // delete a;

    // b.Say();

    //A a;
    //b.aRef = &A;

    //b.Say();

    return 0;
}