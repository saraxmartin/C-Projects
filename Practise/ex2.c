#include <stdio.h>

struct Student
{
   int id;
   float average_grade;
   int credits;
};

void Init (struct Student st[], int numStudents)
{
    st[0].id = 1111;
    st[0].average_grade = 6.5;
    st[0].credits = 60;
    st[1].id = 1112;
    st[1].average_grade = 7.5;
    st[1].credits = 30;
    st[2].id = 1113;
    st[2].average_grade = 9.0;
    st[2].credits = 90;
    st[3].id = 1114;
    st[3].average_grade = 9.1;
    st[3].credits = 30;
}

float Average (struct Student st[], int numStudents)
{
    float sum = 0;
    int i;
    for (i=0; i<numStudents; i++)
    {
        sum += st[i].average_grade;
    }
    return sum / numStudents;
}


int main()
{
    float average;
    struct Student array[4];
    Init(array,4);
    average = Average(array, 4);
    printf("%f", average);

    return 0; 
}