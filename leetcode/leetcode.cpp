// leetcode.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;


struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
		if(lists.size()==0)	return NULL;
		if(lists.size()==1)	return     lists[0];
		
		ListNode* demi = new ListNode(0);
		ListNode* p = demi;
		bool flag = false;
		while(!flag)
		{
			mergeKLists(p,lists,flag);
			p = p->next;
		}
		return demi->next;
    }

		void  mergeKLists(ListNode* p, vector<ListNode*>& list, bool& flag )
	{
		ListNode* q=NULL;
		int minval = INT_MAX;
		size_t cnt = 0;
		size_t ind = list.size();
		for(size_t i=0; i!= list.size(); i++)
		{
			if(list[i])
			{
				cnt++;
				if( list[i]->val <minval)
				{
					minval = list[i]->val;
					q = list[i];
					ind = i;
				}
			}
		}
		
		p->next = q;
		if(ind!=list.size())
		{
			list[ind] = list[ind]->next;
		}
		if(cnt<=1)	flag = true;
		else flag = false;
	}
	
	//找到vector容器中的最小值和次最小值
	void findMin(vector<ListNode*>& list, size_t& min0, size_t& min1)
	{
		int valmin0, valmin1;
		valmin0=valmin1=INT_MAX;
		for(size_t i=0; i!=list.size(); i++)
		{
			if(list[i] && list[i]->val < valmin1)
			{
				if(list[i]->val < valmin0)
				{
					valmin1 = valmin0;
					valmin0 = list[i]->val;
					min1 = min0;
					min0 = i;
				}
				else
				{
					valmin1 = list[i]->val;
					min1 = i;
				}
			}
		}
	}


	void mergeKLists(ListNode* p, vector<ListNode*>& list,size_t& min0, size_t& min1)
	{
		
	}

};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

