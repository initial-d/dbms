#pragma once
#include<iostream>
#include<string>
#include "stdafx.h"
using namespace std;
class DSMgr
{
public:
    DSMgr();
    int OpenFile(string filename);
    int CloseFile();
    bFrame ReadPage(int page_id);
    int WritePage(int frame_id, bFrame frm);
    int Seek(int offset, int pos);
    FILE * GetFile();
    void IncNumPages();
    int GetNumPages();
    void SetUse(int index, int use_bit);
    int GetUse(int index);
    FILE *currFile;
    int numPages;
	int pages[MAXPAGES];
};