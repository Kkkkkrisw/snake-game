#include<stdio.h>
int main()
{
	printf("Snake v0.1\n");
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (i == 0||i==19)
			{
				printf("#");
			}
			else if (j == 0||j==19)
			{
				printf("#");
			}
			else
			{

				printf(" ");
			}
		}
		printf("\n");
	}
}