#include <stdio.h>

int main()
{
	// Calculate the average score of all students in a class.

	int num;
	int sum;

	printf("How many students are there?\n");
	scanf("%d", &num);
	printf("What are their scores?\n");

	// We programmers count from zero!
	int score;
	sum = 0;
	for (int i = 0; i < num; i++)
	{
		
		scanf("%d", &score);
		sum += score;
	}

	double average = 1.0 * sum / num;
	if (average == 60)
		printf("Good!\n");
	else if (average > 60)
		printf("Excellent!\n");
	else
		printf("Bad!\n");

	printf("Average score is %.2f.\n", average);

	return 0;
}
