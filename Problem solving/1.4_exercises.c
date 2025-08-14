#include <stdio.h>

int exercise_1(int x, int y, int z)
{
    int maxi,mini,l[3]={x,y,z};
    maxi = max(l);
    mini = min(l);
    int i, other;
    for (i=0; (l[i]!= maxi) || (l[i]!= mini); i++ )
    {
        other = l[i];
    }
    return (maxi,other,mini);

}

void main()
{
    int exercise1,x,y,z;
    prinf("Type 3 numbers: ");
    scanf("%d %d %d",x,y,z);
    exercise_1(x,y,z);
}