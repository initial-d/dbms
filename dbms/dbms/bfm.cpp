#pragma once
#include "stdafx.h"
#include<iostream>
#include<stdio.h>
#include <ctime>
#include <iomanip>
using namespace std;

DSMgr d;
BMgr b;
LRU * tail , *head;
BMgr::BMgr()
{
    for(int i = 0; i < DEFBUFSIZE ;i++)
    {
        ptof[i] = 0;
        ftop[i] = -1;
    }
    d.OpenFile("data.dbf");
}
int BMgr::FixPage(int page_id , int prot)
{
    int fid = -1;
    int frame_id=Hash(page_id);
	BCB * bcb =ptof[frame_id];

    while(bcb != NULL)
    {
		if (bcb->page_id == page_id)
			break;
        bcb = bcb->next;
    }
	
    if(bcb != NULL)
	{
		calcLRUList(bcb, bcb->frame_id , 2);
		return bcb->frame_id;
	}
	else
	{
		BCB * bcb1 = ptof[frame_id];
		fid = SelectVictim(); 
		//cout << fid << ",";
		buf[fid] = d.ReadPage(page_id);
		ftop[fid] = page_id;
		if(bcb1 != NULL)
		{
			bcb = new BCB();
			bcb->next = NULL;
			bcb->page_id = page_id;
			bcb->frame_id = fid;
			bcb->latch = 0;
			bcb->count = 0;
			calcLRUList(bcb, fid , 1);
		}
		else
		{
			bcb1 = new BCB();
			ptof[frame_id] = bcb1;
			bcb1->next = NULL;
			bcb1->page_id = page_id;
			bcb1->frame_id = fid;
			bcb1->latch = 0;
			bcb1->count = 0;
			calcLRUList(bcb1, fid , 1);
		}
	}
	return fid;
}


int BMgr::SelectVictim()
{
	int vFrame = 0,pid = 0,fid=0;
	BCB * bcb = NULL;
	bool found = false;
	LRU * temp = head;
	if(temp == NULL)
		return 0;
	for(int i = 0; i < DEFBUFSIZE; i++)
		if(ftop[i] == -1)
			return i;
	vFrame = temp->fid;
	pid = ftop[vFrame];
	fid = Hash(pid);
	bcb = ptof[fid];
	while(bcb != NULL && bcb->page_id != pid)
		bcb = bcb->next;
	if (bcb != NULL && bcb->dirty == 1)
	{
		d.WritePage(pid, buf[vFrame]);
	}
	if(bcb != NULL)
	{
		RemoveLRUEle(vFrame);
		RemoveBCB(bcb,bcb->page_id);
	}
	return head->fid;
}
bool BMgr::FindFrame(int page_id)
{
	int frame_id = Hash(page_id);
	BCB * hi = ptof[frame_id];
	if (hi != NULL)
	{ 
		while (hi->page_id != page_id && hi->next != NULL)
		{
			hi = hi->next;
		}
		if (hi->page_id == page_id)
			return true;
	}
	return false;
}

int BMgr::Hash(int page_id)
{
	return  page_id % DEFBUFSIZE;
}

void BMgr::RemoveBCB(BCB *ptr, int page_id)
{
	BCB * bcb = ptof[Hash(page_id)];
	if(bcb == ptr)
	{
		if(bcb->next != NULL)
		{
			bcb = bcb->next;
			delete ptr;
			ptof[Hash(page_id)] = bcb;
			ptr = bcb = NULL;
		}
		else
		{
			delete ptr;
			ptof[Hash(page_id)] = NULL;
			ptr = bcb = NULL;
		}
	}
	else
	{
		while(bcb->next != ptr)
			bcb = bcb->next;
		bcb->next = ptr->next;
		delete ptr;
		ptr = NULL;
	}
}
void BMgr::RemoveLRUEle(int frid)
{
	LRU * ptr = head;
	if(ptr == NULL)
		return;
	head = head->less;
	head->more = NULL;
	tail->less =  ptr;
	ptr->more = tail;
	tail = tail->less;
	tail->less = NULL;
	//delete ptr;
}

void BMgr::calcLRUList(BCB * ptr, int frid  , int flag)
{
	if (flag == 1)
	{
		if (head == NULL)
		{
			head = new LRU();
			head->fid = frid;
			head->less = NULL;
			head->more = NULL;
			tail = head;
		}
		else
		{
			LRU * it = head;
			bool flag = false;
			while (it != NULL)
			{
				if (it->fid == frid)
				{
					flag = true;
					if (it == tail)
						break;
					if (it->more == NULL)
					{
						head = it->less;
						head->more = NULL;
						tail->less = it;
						it->more = tail;
						tail = tail->less;
						tail->less = NULL;
						//delete it;
						break;
					}
					else{
						it->more->less = it->less;
						it->less->more = it->more;
						tail->less = it;
						it->more = tail;
						tail = tail->less;
						tail->less = NULL;
						//delete it;
					}
					break;
				}
				it = it->less;
			}
			if (!flag)
			{
				tail->less = new LRU();
				tail->less->more = tail;
				tail = tail->less;
				tail->fid = frid;
				tail->less = NULL;
			}
		}
	}
	else if (flag == 2)
	{
		LRU * it = head;
		while (it != NULL)
		{
			if (it->fid == frid)
			{
				if (it == tail)
					break;
				if (it->more == NULL)
				{
					head = it->less;
					head->more = NULL;
					tail->less = it;
					it->more = tail;
					tail = tail->less;
					tail->less = NULL;
					//delete it;
					break;
				}
				else{
					it->more->less = it->less;
					it->less->more = it->more;
					tail->less = it;
					it->more = tail;
					tail = tail->less;
					tail->less = NULL;
					//delete it;
				}
				break;
			}
			it = it->less;
		}
	}
}


