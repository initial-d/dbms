#pragma once
#include<iostream>
#include<stdio.h>
#include "stdafx.h"
#include<fstream>
using namespace std;

DSMgr::DSMgr()
{
    currFile = NULL;
    for(int i = 0; i < MAXPAGES ;i++)
        pages[i] = -1;
}
int DSMgr::OpenFile(string filename)
{
    currFile=fopen(filename.c_str(),"r+");
    if(currFile == NULL)
        return 1;
    else
        return 0;
}
bFrame DSMgr::ReadPage(int page_id)
{
    int read = 0;
    bFrame bf_ds;
    fseek(currFile,page_id * FRAMESIZE,SEEK_SET);
    read = (int)fread(&bf_ds,sizeof(bf_ds),1,currFile);
    return bf_ds;
}
int DSMgr::WritePage(int frame_id, bFrame frm)
{
    int numbyte = 0;
    fseek(currFile,frame_id * FRAMESIZE,SEEK_SET);
    numbyte = (int)fwrite(&frm,sizeof(frm),1,currFile);
    return numbyte;
}



