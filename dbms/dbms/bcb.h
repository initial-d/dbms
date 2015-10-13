#pragma once
#include "stdafx.h"
#define FRAMESIZE  4096
#define DEFBUFSIZE 1024
#define MAXPAGES 50001
#define COUNT 500000

struct bFrame
{
	char field[FRAMESIZE];
};

struct BCB
{
	BCB();
	int page_id;
	int frame_id;
	int latch;
	int count;
	int dirty;
	BCB * next;
};

struct LRU {
	LRU();
	int fid;
	LRU * less;
	LRU * more;
};
