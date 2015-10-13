// dbms.cpp 
#pragma once
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <ctime>
using namespace std;
LRU::LRU()
{
	fid = -1;
	less = NULL;
	more = NULL;
}
BCB::BCB()
{
	next = NULL;
	latch = -1;
	count = -1;
	page_id = -1;
	frame_id = -1;
	dirty = -1;
}
int main()
{
	/*FILE *fp = fopen("data.dbf", "w+");
	char str[100000];
	memset(str, 0, sizeof(bu));//清0//
	for (int i = 0; i<4096; i++)
	{
		fwrite(str, sizeof(char), sizeof(str), fp);
	}
	fclose(fp);*/
	ifstream infile("data-5w-50w-zipf.txt");
	if (!infile)
	{
		cerr << "error" << endl;
		exit(1);
	}
	int val1, val2;
	int number = 0;
	int IOCount = 0;
	char c1;
	BMgr *bm = new BMgr();
	DSMgr *ds = new DSMgr();
	bFrame *bf_init = new bFrame[DEFBUFSIZE];
	ds->OpenFile("data.dbf");
	/*for (int i2 = 0; i2<DEFBUFSIZE; i2++)
	{
		bf_init[i2] = ds->ReadPage(i2);
	}
	for (int i3 = 0; i3 < DEFBUFSIZE; i3++)
	{
		bm->FixPage(i3,0);
	}*/
	double begin = (double)clock() / CLK_TCK;

	while (!infile.eof())
	{
		infile >> val1;
		infile >> c1;
		infile >> val2;
		number++;
		if (val1 == 0)
		{
			bm->FixPage(val2, 0);
			if (bm->FindFrame(val2));
			else
				IOCount++;
		}
		else
		{
			bm->FixPage(val2, 0);
			if (bm->FindFrame(val2));
			else
				IOCount++;
		}
	}
	double finish = (double)clock() / CLK_TCK;
	double run = finish - begin;
	double tti = (double(number - IOCount) / (number)) * 100;
	cout << "***************************************运行结果****************************"<<endl;
	cout << "I/O操作的执行次数：" << number << endl;
	cout << "统计程序的I/O次数：" << IOCount << endl;
	cout << "缓冲区块的命中率   " << tti << "%" << endl;
	cout << "程序的运行时间为： " << run <<"s"<< endl;
	exit(0);
	/*for (int i = 0; i < DEFBUFSIZE; i++)
	{
		if(bm->ptof[i] == NULL)
			continue;
		if((bm->ptof[i]->dirty) == 1)
		{
			bFrame bf = bm->buf[bm->ptof[i]->page_id];
			ds->WritePage(bm->ptof[i]->page_id, bf);
		}
	}*/
	infile.close();
	return 0;
}
