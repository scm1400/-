#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include<string.h>
#include <stdint.h> 


int main()
{
	int iter;
	int table;
	int start;
	//char epf[20];
	//char epf2[300];
	printf("\n [ Position Offest ]\n");
	printf("\n 2019.07.06 \n");
	printf("\n  �ٵ� tbl������ \n");
	printf("\n ������ ������ ���̽� ����. \n");
	printf("\n � �ε��� ?");
	scanf("%d", &iter);
	printf("\n");
	printf("\n ���̺� ���۹�ȣ ?");
	scanf("%d", &table);
	printf("\n");
	printf("\n y �̹��� ���۳ѹ� ");
	scanf("%d", &start);
	printf("\n");

	//printf(" ���� epf���� �̸��� �����ּ���. xxxxx.epf ( �������� �ȼ� �� + ���ٽ� ���� ��� )\n\n ");
	//scanf("%s", &epf);
	//sprintf(epf2, "%s.epf", epf);

	printf("\n ó����.. ���α׷��� ���� �� ���� ��ٷ��ּ���. \n ");

	for (int i = 0; i < iter; i++)
	{

		FILE *fpTxt;
		unsigned char *data;
		int f = 0;

		int number = start + 104 * i;

		fpTxt = fopen("tbl.txt", "at+");

		data = malloc(4);

		fprintf(fpTxt, "%02x 00 00 00 ", table+i);
		fprintf(fpTxt, "00 00 00 00 ");

		

		memcpy(data, &number, 4);
		for (f = 0; f < 4; f++)
		{
			fprintf(fpTxt, "%02x", data[f]);
		}
		for (f = 0; f < 4; f++)
		{
			data[f] = 0;
		}
		fprintf(fpTxt, "\n");
		fclose(fpTxt);

	}
}