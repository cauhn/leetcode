// leetcode.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <map>
#include <math.h>
#include <string>
#include <set>
#include <bitset>

using namespace std;


struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
	//�����Ƿ���Ч
	//��λΪ��.��
	bool isValidSudoku(vector<vector<char> > &board) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
		const int n = 9;
        //row identify
		for(size_t i=0; i!= board.size(); i++)
		{
			vector<char>	str = board[i];
			bitset<n>	bflag(0);
			for(size_t j=0; j!= str.size(); j++)
			{
				if(str[j]=='.')	continue;
				size_t ind = str[j]-'0';
				if(bflag.test(ind))	return false;
				else bflag.set(ind);
			}

		}
    }

	//����target���Բ����λ��
	int searchInsert(int A[], int n, int target) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if(target < A[0])	return 0;
		if(target > A[n-1])	return n;
		return searchInsert(A,0,n-1,target);
    }

	int searchInsert(int a[], int l, int r, int target)
	{
		if(l>r)
		{
			return l;
		}

		int m = (l+r)/2;
		if(target == a[m])		return m;
		else if(target < a[m])	return searchInsert(a,l,m-1,target);
		else return searchInsert(a,m+1,r,target);
	}


	//�������������ҵ���targetһ����ֵ��λ��
	vector<int> searchRange(int A[], int n, int target) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<int>	res;
		searchRange(A,0,n-1,target,res);
		if(res.empty())	
		{
			res.push_back(-1);
			res.push_back(-1);
			return res;
		}
		else
		{
			int lloc,rloc;
			lloc = n-1, rloc=0;
			for(size_t i=0; i!=res.size(); i++)
			{
				if(res[i]<lloc)
				{
					lloc = res[i];
				}
				if(res[i]>rloc)
					rloc = res[i];
			}
			vector<int> result;
			result.push_back(lloc);
			result.push_back(rloc);
			return result;
		}
    }

	void searchRange(int a[], int l, int r, int target, vector<int>& res)
	{
		if(l>r)	return ;
		int m = (l+r)/2;
		
		if(a[m]>target)
			 searchRange(a,l,m-1,target,res);
		else if(a[m]<target)
			 searchRange(a,m+1,r,target,res);
		else	//target �ҵ�
		{
			res.push_back(m);
			searchRange(a,l,m-1,target,res);
			searchRange(a,m+1,r,target,res);
		}

	
	}
	//������һ���������飬���������˼�λ��������target��λ��
	int search(int A[], int n, int target) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        search(A,0,n-1,target);
    }

	int search(int A[], int l, int r, int target)
	{
		if(l>r)
			return -1;
		int m = (l+r)/2;
		if(A[m]==target)
			return m;
		
		if(A[l]<A[m])
		{
			if(A[l]<=target && target < A[m])
				return search(A,l,m-1,target);
			else
				return search(A,m+1,r,target);
		}
		else if(A[l]==A[m])
		{
			int res = search(A,l+1,m-1,target);
			if(res!=-1)	return res;
			else return search(A,m+1,r,target);
		}
		else if(A[l]>A[m])
		{
			if(target >A[m] && target<= A[r])
				return search(A,m+1,r,target);
			else
				return search(A,l,m-1,target);
		}

		return -1;
	
	}

	//���ֵ��е���һ���� 
	void nextPermutation(vector<int> &num) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        //��ĩβ��ʼ�ҵ���һ�� ǰһ��ֵ< ��һ��ֵ
		size_t sz = num.size();
		size_t px=0;
		for(size_t i = sz-1; i>0; i--)
		{
			if( num[i]<= num[i-1])
				continue;
			else
			{
				px = i-1;
				break;
			}
		}
		//���ǵݼ����У�����һ��Ϊ��С����
		if(px==0)
		{
			int j=0;
			int k = sz-1;
			while(j<k)
			{
				num[j] ^=num[k];
				num[k]	^=num[j];
				num[j]	^=num[k];
				j++;
				k--;
			}
			return;
		}
		size_t ch=0;
		for(size_t i= sz-1; i>px; i--)
		{
			if(num[i]>num[px])
			{
				ch = i;
				break;
			}		
		}

		int tmp = num[ch];
		num[ch] = num[px];
		num[px] = tmp;

		int j = px+1;
		int k = sz-1;
		while(j<k)
		{
			int temp = num[j];
			num[j] = num[k];
			num[k] = temp;
			j++;
			k--;
		}


    }


	//���Ҽ��������е��ַ�����S�е�λ��
	vector<int> findSubstring(string S, vector<string> &L) {
     // Start typing your C/C++ solution below
        // DO NOT write int main() function
		vector<int>	res;
		if(L.empty())	return res;
		size_t sz = L.begin()->size();
		multiset<string>	strset(L.begin(),L.end()),tmp(strset);
		int sumsz = sz*L.size();


	for(int i=0; i<sz; i++)
		{
			int ind = i;
			vector<string>		subvec;
			multiset<string>	tmpset(strset);
			//���ַ����ִ�
			while(ind<S.size())
			{
				string str = S.substr(ind,sz);
				subvec.push_back(str);
				ind = ind+sz;
			}

			while(!tmpset.empty())
			{
				
			
			}
		
		}
		return res;

		//for(int i=0; i<S.size();i++ )
		//{
		//	tmp = strset;
		//	if(i+sumsz>S.size())
		//		break;
		//	int ind =i;
		//	while(!tmp.empty())
		//	{
		//		string sub = S.substr(ind,sz);
		//		multiset<string>::iterator iter = tmp.find(sub);
		//		if(iter==tmp.end())
		//			break;
		//		else
		//		{
		//			ind = ind+sz;
		//			tmp.erase(iter);
		//		}
		//	}
		//	//�ж��Ƿ�ȫ���ҵ�
		//	if(tmp.empty())
		//	{
		//		int index = ind-sumsz;
		//		res.push_back(index);
		//	}
		//}
		//return res;
		
    }
	//���� 
	int divide(int dividend, int divisor) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        bool flag = true;
		if(divisor==1 )	return dividend;
		if(divisor==0)	return 0;
		if((divisor>0 && dividend<0 ) || (divisor<0 && dividend>0))
			flag = false;

		long long u_divisor, u_dividend, big ,small, result, sum=0;
		
		u_divisor = abs((long double)divisor);
		u_dividend = abs((long double)dividend);


		while(u_dividend>u_divisor)
		{
			big = u_dividend;
			small = u_divisor;
			result = 1;

			while(small<big)
			{
				small = small<<1;
				result = result<<1;
			}
			if(small > big)
			{
				small = small>>1;
				result = result >>1;
			}
			u_dividend = u_dividend - small;
			sum = sum+result;
		}
		
		if(u_dividend == u_divisor)
			sum = sum+1;
		

		if(!flag)	return -sum;
		else return sum;

    }
	//KMP�㷨
	char *strStr(char *haystack, char *needle) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        
        int m = strlen(needle);
    	int* move = new int[m];
		compute_prefixfun(needle,move);
		int q=-1;
		int n = strlen(haystack);
		if(m==0)    return haystack;
        
        for(int i=0; i<n;i++)
		{
			while(q>-1 && haystack[i]!=needle[q+1])
				q = move[q];
			if(haystack[i]==needle[q+1])
				q = q+1;
			if(q==m-1)
				return haystack+i-m+1;
		}
		return NULL;
    }
	
	void compute_prefixfun(char* needle, int* move)
	{
		int m = strlen(needle);
		move[0]= -1;
		int k=-1;
		for(int i=1; i<m-1; i++)
		{
			while(k>-1 && needle[k+1] !=needle[i])
				k = move[k];
			if(needle[k+1]==needle[i])
				k++;
			move[i] = k;
		}
	}


	//ɾ����������elemֵ��ͬ��ֵ��ͬʱ������󳤶�
	int removeElement(int A[], int n, int elem) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int ind,cnt;
		for(ind=0,cnt=0; cnt!=n; cnt++)
		{
			if(A[cnt]==elem)
			{
				continue;
			}
			else
			{
				A[ind++] = A[cnt];
			}
		}

		return ind;
    }

	//ԭ��ɾ���ظ�����  ����������
    int removeDuplicates(int A[], int n) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
		int ind =1;
		int ptr = 1;
		if(n<2)	return n;
		for(; ptr!=n; ptr++)
		{
			if(A[ptr]==A[ptr-1])
			{
				continue;
			}
			else
			{
				A[ind] = A[ptr];
				ind++;
			}
		}
		return ind;
	}
	//��������ָ�룬���ܸı�����
    ListNode *swapPairs(ListNode *head) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        ListNode* first = new ListNode(0);
		first->next = head;
		
		ListNode *pre, *cur, *nex;
		pre = first;
		cur = head;
		while(cur && cur->next)
		{
			nex = cur->next;

			pre->next = nex;
			cur->next = nex->next;
			nex->next = cur;
			
			pre = cur;
			cur = cur->next;
		}
		return first->next;

    }
	
	//ÿK���ڵ㷴ת�������K�ڵ�Ĳ�����ת
	ListNode *reverseKGroup(ListNode *head, int k) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        ListNode* first = new ListNode(0);
		first->next = head;

		ListNode* pre = first;
		ListNode *p, *q,*r,*tail;
		while(pre->next)
		{
			tail = pre->next;
			p = pre->next;
			q = p->next;
			int cnt ;
			for(cnt=1; cnt<k && q ;cnt++)
			{
				r = q->next;
				q->next = p;
				p = q;
				q = r;
			}
			//ǰ��N��
			if(cnt==k)
			{
				pre->next = p;
				pre = tail;
				pre->next = q;
			}
			//���һ��
			else
			{
				while(cnt!=1)
				{
					r = p->next;
					p->next = q;
					q = p;
					p = r;
					cnt--;
				}
				break;
			}
		}
		return first->next;
    }
	



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
	
	//�ҵ�vector�����е���Сֵ�ʹ���Сֵ
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

	Solution s;
	int i = (int)2147483648*-1;
	int c;
	if(i>=0L)
	{
		printf("hello\n");
	}
	else
		 c = -i;
	int d = i>=0L ? i : -i;
	//int d = abs(i);
	s.divide(i,2);
	return 0;
}

