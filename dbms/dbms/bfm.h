#pragma once
#include<iostream>
#include "stdafx.h"
#include <ctime>
#include <iomanip>
using namespace std;
class BMgr
{
public:
    BMgr();
    // Interface functions
    int FixPage(int page_id, int prot);
    int UnfixPage(int page_id);
    int NumFreeFrames();
    bool FindFrame(int page_id);
    // Internal Functions
    int SelectVictim();
    int Hash(int page_id);
    void RemoveBCB(BCB * ptr, int page_id);
    void RemoveLRUEle(int frid);
    void SetDirty(int frame_id);
    void UnsetDirty(int frame_id);
    void WriteDirtys();
    void PrintFrame(int frame_id);
    void calcLRUList(BCB * ptr, int frid , int flag);
    // Hash Table

	int ftop[DEFBUFSIZE];
    BCB* ptof[DEFBUFSIZE];
    bFrame buf[DEFBUFSIZE];
};