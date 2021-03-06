// leetcode.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <map>
#include <math.h>
#include <string>
#include <set>
#include <bitset>
#include <deque>
#include <queue>
#include <list>
#include <algorithm>
#include <numeric>
#include <stack>

using namespace std;


struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

bool operator<(ListNode& a, ListNode& b)
{
	return a.val<b.val;
}


 struct Interval {
	     int start;
	    int end;
		Interval() : start(0), end(0) {}
	    Interval(int s, int e) : start(s), end(e) {}
 };

 struct TreeLinkNode {
	   int val;
	   TreeLinkNode *left, *right, *next;
	   TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 };

 struct TreeNode {
	      int val;
	      TreeNode *left;
	      TreeNode *right;
	      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	 };
 template<typename T> struct unordered_set:set<T>
 {
		
 };
 template<typename t, class s> struct unordered_map:map<t,s>
 {

 };

class Solution {
public:

	TreeNode *sortedListToBST(ListNode *head) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		return sortedListToBSTHelper(head);
	}
	TreeNode* sortedListToBSTHelper(ListNode* head)
	{
		if (!head)
		{
			return NULL;
		}
		ListNode *p,*q,*pre,*phead;
		phead = new ListNode(0);
		phead->next = head;
		p=q =  phead;
		pre = phead;
		while (p && p->next )
		{
			pre = q;
			p = p->next->next;
			q = q->next;
		}
		pre->next = NULL;
		TreeNode* root = new TreeNode(q->val);
		TreeNode *left,*right;
		left = sortedListToBSTHelper(phead->next);
		right = sortedListToBSTHelper(q->next);
		root->left = left;
		root->right = right;
		delete phead;
		return root;		
		
	}
	//对排序好的数组生成平衡树
	TreeNode *sortedArrayToBST(vector<int> &num) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		//可以将mid作为根节点，左半边作为左子树，右半边作为右子树
		return sortedArrayToBSTHelper(num,0,num.size()-1);
	}
	TreeNode* sortedArrayToBSTHelper(vector<int> & num, int beg, int end)
	{
		if (beg>end)
		{
			return NULL;
		}
		if (beg<=end)
		{
			int mid = (beg+end)/2;
			TreeNode* root = new TreeNode(num[mid]);
			TreeNode *left, *right;
			left = sortedArrayToBSTHelper(num,beg,mid-1);
			right = sortedArrayToBSTHelper(num,mid+1,end);
			root->left = left;
			root->right = right;
			return root;
		}
	}
	int minCut(string s) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		int len = s.size();
		vector<int> dp(len+1);
		vector<vector<bool> >isPa(len,vector<bool>(len,false));
		
		for (int i=len; i>=0; i--)
		{
			dp[i]=len-i;
		}
		for (int i=len-1;i>=0; i--)
		{
			for (int j=i; j<len; j++)
			{
				if (s[i]==s[j]&&(j-i<2 || isPa[i+1][j-1]))
				{
					isPa[i][j]=true;
					dp[i] = min(dp[i],1+dp[j+1]);
				}
			}
		}
		return dp[0]-1;


		////time limit
		//int len =s.size();
		//if (len<=1)
		//{
		//	return 0;
		//}
		//vector<vector<bool> > isPa(len,vector<bool>(len,false));
		//for (int i=0; i<len; i++)
		//{
		//	isPa[i][i]=true;
		//	if (i<len-1)
		//	{
		//		isPa[i][i+1] = s[i]==s[i+1];
		//	}
		//}
		//for (int i=2; i<len; i++)
		//{
		//	for (int j=0; i+j<len; j++)
		//	{
		//		if (s[j]==s[i+j] && isPa[j+1][i+j-1])
		//		{
		//			isPa[j][j+i]=true;
		//		}
		//	}
		//}
		//vector<vector<int> > cutnum(len,vector<int>(len));
		//for (int i=len-2; i>=0; i--)
		//{
		//	for (int j=1; i+j<len; j++)
		//	{
		//		int ind = j;
		//		while (ind>=1 && !isPa[i][i+ind])
		//		{
		//			ind--;
		//		}
		//		if (ind!=j)
		//			cutnum[i][i+j]=1+cutnum[i+ind+1][i+j];
		//	
		//	}
		//}
		//int minval = len-1;
		//for (int i=0; i<len-1; i++)
		//{
		//	minval = min(minval,cutnum[0][i]+cutnum[i+1][len-1]+1);
		//}
		//minval = min(minval,cutnum[0][len-1]);
		//return minval;
	}
	vector<vector<string>> partition(string s) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		int len = s.size();
		vector<vector<string> >result;
		vector<string> input;
		if (len==0)
		{
			return result;
		}
		vector<vector<bool> > isPa(len,vector<bool>(len,false));
		for (int i=0; i<len; i++)
		{
			isPa[i][i]=true;
			if (i<len-1)
			{
				isPa[i][i+1] = s[i]==s[i+1];
			}
		}
		for (int i=2; i<len; i++)
		{
			for (int j=0; i+j<len; j++)
			{
				if (s[j]==s[i+j] && isPa[j+1][i+j-1])
				{
					isPa[j][j+i]=true;
				}
			}
		}
		partitionhelper(s,0,isPa,input,result);
		return result;
	}
	void partitionhelper(string str, int start,const vector<vector<bool>>&isPa, vector<string>& input, vector<vector<string> >& result)
	{
		if (start>=str.size())
		{
			result.push_back(input);
			return ;
		}
		for (int i=0; start+i<str.size(); i++)
		{
			if (isPa[start][start+i])
			{
				string substr = str.substr(start,i+1);
				input.push_back(substr);
				partitionhelper(str,start+i+1,isPa,input,result);
				input.pop_back();
			}
		}
	}
	//将所有被包围的'O'，用‘X’表示
	void solve(vector<vector<char>> &board) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		int row = board.size();
		if (row<=2)
		{
			return;
		}
		if (board[0].size()<=2)
		{
			return;
		}
		int col = board[0].size();
		vector<vector<bool> > visit(row,vector<bool>(col,false));
		vector<pair<int, int> >deq;
		bool flag = true;
		for (int i=0; i<row; i++)
		{
			for (int j=0; j<col; j++)
			{
				if (!visit[i][j] && board[i][j]=='O' )
				{
					visit[i][j]=true;
					deq.clear();
					deq.push_back(make_pair(i,j));
					int beg, end;
					beg = 0; end=1;
					flag = true;
					while (beg<end)
					{
						for (int m=beg; m<end; m++)
						{
							int r,c;
							r = (deq[m]).first;
							c = (deq[m]).second;
							if (flag && (r==0 || r==row-1 || c==0 || c==col-1))
							{
								flag =false;
							}
							if (r!=0 && !visit[r-1][c] && board[r-1][c]=='O')
							{
								deq.push_back(make_pair(r-1,c));
								visit[r-1][c]=true;
							}
							if (r!=row-1 && !visit[r+1][c]&&board[r+1][c]=='O')
							{
								deq.push_back(make_pair(r+1,c));
								visit[r+1][c]=true;
							}
							if (c!=0 && !visit[r][c-1] && board[r][c-1]=='O')
							{
								deq.push_back(make_pair(r,c-1));
								visit[r][c-1]=true;
							}
							if (c!=col-1 && !visit[r][c+1] && board[r][c+1]=='O')
							{
								deq.push_back(make_pair(r,c+1));
								visit[r][c+1]=true;
							}
						}
						beg = end;
						end = deq.size();
					}// end while
					if (flag)
					{
						for (int m=0; m<deq.size();m++)
						{
							int r,c;
							r = deq[m].first;
							c=deq[m].second;
							board[r][c]='X';
						}
						deq.clear();
					}
				}// end if 
				else
					visit[i][j]=true;
			}
		}
	}
	int sumNumbers(TreeNode *root) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		int sum=0;
		vector<int> input;
		sumNumbers(root,input,sum);
		return sum;
	}
	void sumNumbers(TreeNode *root,vector<int>& input, int& sum)
	{
		if (!root)
		{
			return ;
		}
		input.push_back(root->val);
		if (!root->left && !root->right)
		{
			int num=0;
			for (int i=0; i<input.size();i++)
			{
				num = 10*num+input[i];
			}
			sum +=num;
			input.pop_back();
			return;
		}
		sumNumbers(root->left,input,sum);
		sumNumbers(root->right,input,sum);
		input.pop_back();
		return;
	}
	//最长的连续
	int longestConsecutive(vector<int> &num) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		if (num.empty())
		{
			return 0;
		}
		unordered_map<int,int> nummap;
		int maxval = 0;
		for (int i=0; i<num.size();i++)
		{
			nummap[num[i]]=0;
		}
		for (int i=0; i<num.size(); i++)
		{
			int ind = num[i];
			if (nummap[ind]==0)
			{
				int c = 1, val = ind+1;
				while(nummap.find(val)!=nummap.end() && nummap[val]==0)
				{
					c++;
					nummap[val]=-1;
					val++;
				}
				nummap[ind] = nummap.find(val)==nummap.end() ? c : c+nummap[val];
				maxval = max(maxval,nummap[ind]);
			}
		}//end for i
		return maxval;
	}
	vector<vector<string>> findLadders(string start, string end, unordered_set<string> &dict) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		dict.insert(end);
		dict.insert(start);
		
		vector<string>	 wordvec;
	
		vector<vector<int> >adjacent;
		vector<int> last;
		int indlast;
		adjacent.resize(dict.size());

		deque<string> deq;
		deq.push_back(start);
		dict.erase(start);
		bool flag = false;
		int low,high;
		low = 0; high=1;
		int level = 0;
		unordered_set<string> cpset;
		unordered_map<string,int> wordmap;
		while (low<high)
		{
			level++;
			for (int i=low; i<high; i++)
			{
				string s = deq[i];
				if (flag)
				{
					if (ladderLengthHelper(s,end))
					{
						adjacent[wordmap[end]].push_back(i);
					}
					continue;
				}
				for (int j=0; j<s.size(); j++)
				{
					string t = s;
					for (int k=0; k<26; k++)
					{
						t[j]='a'+k;
						if (t==end)
						{
							if (flag)
							{
								adjacent[wordmap[end]].push_back(i);
							}
							else
							{
								deq.push_back(t);
								flag = true;
								wordmap[end]=deq.size()-1;
								adjacent[deq.size()-1].push_back(i);
							}
							break;
						}
						if (dict.find(t)!=dict.end())
						{
							if (wordmap.find(t)==wordmap.end())
							{
								deq.push_back(t);
								wordmap[t]=deq.size()-1;
							}
							adjacent[wordmap[t]].push_back(i);
						}
					}//end for k
					if (flag)
					{
						break;
					}
				}// end for j
			}//end for i
			for(int i=high; i<deq.size(); i++)
				dict.erase(deq[i]);
			low = high;
			high = deq.size();
			if (flag)
			{
				break;
			}
		}
		
		vector<string> input;
		vector<vector<string> >res;
		if (!flag)
		{
			return res;
		}
		input.push_back(end);
		ladder(wordmap[end],deq,adjacent,input,res);
		return res;
		
	}
	void ladder(int ind, deque<string>& deq, vector<vector<int> >& adjacent, vector<string>& input, vector<vector<string> >&res)
	{
		if (ind==0)
		{
			vector<string>	reverse(input.rbegin(),input.rend());
			res.push_back(reverse);
			return;
		}
		for (int i=0; i<adjacent[ind].size(); i++)
		{
			int num = adjacent[ind][i];
			input.push_back(deq[num]);
			ladder(num,deq,adjacent,input,res);
			input.pop_back();
		}
	}
	bool ladderLengthHelper(const string& start,const string& end)
	{
		int diff=0,ind;
		for (int i=0; i<start.size();i++)
		{
			if (start[i]!=end[i])
			{
				diff++;
				if (diff>1)
				{
					return false;
				}
			}
		}
		return true;
	}
	//从一个字符串到另外一个字符串需要几次变换，每次只能变换一个字符，且变换后的字符需要在字典中
	int ladderLength(string start, string end, unordered_set<string> &dict) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		dict.insert(end);
		dict.insert(start);
		vector<vector<int> >adjacent;
		vector<string>	 wordvec;

		
		adjacent.resize(dict.size());

		deque<string> deq;
		deq.push_back(start);
		dict.erase(start);
		bool flag = false;
		int low,high;
		low = 0; high=1;
		unordered_set<string> cpdict(dict);
		int level = 0;
		while (low<high)
		{
			level++;
			for (int i=low; i<high; i++)
			{
				string s = deq[i];
				
				for (int j=0; j<s.size();j++)
				{
					string t = s;
					for (int k=0;k<26; k++)
					{
						t[j]=k+'a';
						if (dict.find(t)!=dict.end())
						{
							deq.push_back(t);
							dict.erase(t);
							adjacent[j].push_back(i);
							if (t==end)
							{
								flag=true;
								break;
							}
						}
					}//end for k
					if (flag)
					{
						break;
					}
				}// end for j
			}// end for i
			
			low = high;
			high = deq.size();
			if (flag)
			{
				break;
			}
		}// end while
		
		if (flag)
		{
			return level+1;
		}
		return 0;
	}
	
	
	//判断是否为回文字符串，只考虑字母
	bool isPalindrome(string s) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		int len = s.size();
		if (len==0)
		{
			return true;
		}
		int beg,end;
		beg =0; 
		end = len-1;
		bool flag1,flag2;
		while (beg<=end)
		{
			flag1=isalpha(s[beg]);
			flag2 = isalpha(s[end]);
			if (!flag1 && !flag2)
			{
				beg++;
				end--;
				continue;
			}
			if (!flag1)
			{
				beg++;
				continue;
			}
			if (!flag2)
			{
				end--;
				continue;
			}
			if(tolower(s[beg])==tolower(s[end]))
			{
				beg++;
				end--;
				continue;
			}
			else
				return false;

		}
		return true;
	}
	//从某个节点到另外一个节点的最大值
	int maxPathSum(TreeNode *root) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function

		int maxsum = INT_MIN;
		int csum = 0;
		maxPathSum(root,csum,maxsum);
		return maxsum;
	}
	void maxPathSum(TreeNode *root, int& csum, int& maxsum)
	{
		if (!root)
		{
			csum=0;
			return ;
		}
		int left,right;
		maxPathSum(root->left,left,maxsum);
		maxPathSum(root->right,right,maxsum);
		csum = max(root->val,max(left+root->val, right+root->val));
		maxsum = max(maxsum,max(csum,root->val+left+right));
		return;
	}
	//最多购买两次
	int maxProfit3(vector<int> &prices) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		int len = prices.size();
		if (len==0)
		{
			return 0;
		}

		vector<int> history(len,0);
		vector<int> future(len,0);
		int vally = prices[0];
		int maxval = 0;
		int high = prices[len-1];
		//forward, find the best profit until now
		for (int i=0; i<len; i++)
		{
			vally = min(prices[i],vally);
			if (i>0)
			{
				history[i] = max(history[i-1],prices[i]-vally);
			}
		}
		//backward, find the best profit from now
		for (int i=len-1; i>=0; i--)
		{
			high = max(prices[i],high);
			if (i<len-1)
			{
				future[i] = max(future[i+1],high-prices[i]);
			}
			maxval = max(maxval,history[i]+future[i]);
		}
		return maxval;
	}
	//可以多次购买，但是每次重新购买前都必须卖掉前一个已有的股票，求最大收益
	int maxProfit2(vector<int> &prices) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		int sz = prices.size();
		if (sz==0)
		{
			return 0;
		}
		//找到第一个前一天比今天大的值
		int sum=0;
		int beg, end;
		beg=end = sz-1;
		while (beg>=0)
		{
			while (beg>=1)
			{
				if(prices[beg]>=prices[beg-1])
					beg--;
				else
					break;
			}
			sum += prices[end]-prices[beg];
			beg = beg-1;
			end = beg;
		}
		return sum;
	}
	//购买一次后再卖掉，求最大收益值
	int maxProfit(vector<int> &prices) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		int sz = prices.size();
		if (sz==0)
		{
			return 0;
		}
		int maxval = 0;
		vector<int> maxprice(sz,0);
		maxprice[sz-1] = prices[sz-1];
		int num,dif;
		for (int i=sz-2; i>=0; i--)
		{
			num = prices[i];
			dif = maxprice[i+1]-num;
			if (dif>maxval)
			{
				maxval=dif;
			}
			if (num>maxprice[i+1])
			{
				maxprice[i] = num;		
			}
			else
				maxprice[i] = maxprice[i+1];
		}// end for
		return maxval;

	}
	//返回从顶到底部的累加和最小值
	int minimumTotal(vector<vector<int> > &triangle) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		//利用动态规划的思想，从底部开始往上走
		int sz = triangle.size();
		if (sz==0)
		{
			return 0;
		}
		int minval = INT_MAX;
		vector<int> sum(triangle[sz-1].begin(),triangle[sz-1].end()),sum2(sum.size());
		int left,mid,right;
		for (int i=sz-2; i>=0; i--)
		{
			for (int j=0; j<triangle[i].size();j++)
			{
				int num = triangle[i][j];
				if (j==0)
				{
					left = INT_MAX;
				}
				else
					left = num+sum[j-1];
				mid = num+sum[j];
				right = num+sum[j+1];
				sum2[j] = min(left,min(mid,right));
				/*sum[j] = min(left,min(mid,right));*/
			}
			sum = sum2;
		}
		return sum[0];
	}
	//速度太慢，大数据肯定过不了
	void minimumTotal(vector<vector<int> > &triangle, int k, int ind, int sum, int&minval, int len)
	{
		int num = triangle[k][ind];
		sum = sum+num;
		if (sum>minval)
		{
			return;
		}
		if (k+1==len)
		{
			if (sum<minval)
			{
				minval = sum;
			}
			return;
		}
		if (ind!=0)
		{
			minimumTotal(triangle,k+1,ind-1,sum,minval,len);
		}
		minimumTotal(triangle,k+1,ind,sum,minval,len);
		minimumTotal(triangle,k+1,ind+1,sum,minval,len);
		
	}
	//返回巴斯特三角的第几行
	vector<int> getRow(int rowIndex) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		vector<int> res;
		if (rowIndex<0)
		{
			return res;
		}
		res.push_back(1);
		if (rowIndex==0)
		{
			return res;
		}
		vector<int> levelup,leveldown;
		levelup.reserve(rowIndex+1);
		leveldown.reserve(rowIndex+1);
		int ind=0;
		levelup.push_back(1);
		while (ind!=rowIndex)
		{
			ind++;
			leveldown.push_back(1);
			for (int i=0; i<levelup.size()-1;i++)
			{
				int num = levelup[i]+levelup[i+1];
				leveldown.push_back(num);
			}
			leveldown.push_back(1);
			levelup = leveldown;
			leveldown.clear();
		}
		return levelup;

	}
	//巴斯特三角
	vector<vector<int> > generate(int numRows) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		vector<vector<int> >res;
		vector<int> level;
		if (numRows<=0)
		{
			return res;
		}
		if (numRows==1)
		{
			level.push_back(1);
			res.push_back(level);
			return res;
		}
		res = generate(numRows-1);
		vector<int> bottom = res[res.size()-1];
		level.push_back(1);
		for (int i=0; i<bottom.size()-1; i++)
		{
			int num = bottom[i]+bottom[i+1];
			level.push_back(num);
		}
		level.push_back(1);
		res.push_back(level);
		return res;
	}
	//将右边的结点，变成左边结点的next结点
	void connect(TreeLinkNode *root) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		if (!root)
		{
			return ;
		}
		TreeLinkNode *beg,*p;
		TreeLinkNode* phead = new TreeLinkNode(0);
		root->next = NULL;
		beg = phead;
		p = phead;
		beg->next = root;
		while (beg->next)
		{		
			while (beg)
			{
				if (beg->left)
				{
					p->next = beg->left;
					p = beg->left;
				}
				if (beg->right)
				{
					p->next = beg->right;
					p = beg->right;
				}
				beg = beg->next;
			}// end while
			p->next = NULL;
			beg = phead;
			p = phead;
		}
	}
	//从母串里找出有多少个子串为给出的字串
	int numDistinct(string S, string T) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		if (T.empty())
		{
			return 1;
		}
		
		int sz1,sz2;
		sz1 = S.size();
		sz2 = T.size();
		if (sz1<sz2)
		{
			return 0;
		}
		vector< vector<int> > mt(sz1,vector<int>(sz2,0));
		for (int i=0; i<sz1; i++)
		{
			for (int j=0; j<sz2;j++)
			{
				if (i==0)
				{
					if (j==0)
					{
						mt[i][j] = S[i]==T[j]?1:0;
					}
					continue;
				}
				if (j==0)
				{
					mt[i][j] = mt[i-1][j];
					mt[i][j] +=   S[i]==T[j]?1:0;
				}
				else
				{
					mt[i][j] = mt[i-1][j];
					mt[i][j] += S[i]==T[j]?mt[i-1][j-1]:0;
				}
			}
		}//end for
		return mt[sz1-1][sz2-1];

	}
	//将二叉树表示成先序形式的链表
	void flatten(TreeNode *root) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		
		TreeNode* beg,*end;
		beg=end=NULL;
		flatten(root,beg,end);
	}
	void flatten(TreeNode *root,TreeNode*& beg, TreeNode*& end)
	{
		if (!root)
		{
			beg=end=NULL;
			return;
		}
		if (!root->left && !root->right)
		{
			beg=end = root;
			return;
		}
		TreeNode *leftbeg,*leftend,*rightbeg,*rightend;
		leftbeg=leftend=rightbeg=rightend=NULL;
		flatten(root->left,leftbeg,leftend);
		flatten(root->right,rightbeg,rightend);
		beg = root;
		end = root;
		if (leftend)
		{
			leftend->right = rightbeg;
			root->right = leftbeg;
			root->left = NULL;
			end = leftend;
		}
		if (rightend)
		{
			end = rightend;
		}
		
	}
	//保存路径上的值
	vector<vector<int> > pathSum(TreeNode *root, int sum) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		vector<int> input;
		vector<vector<int> >res;
		pathSum(root,sum,input,res);
		return res;
	}
	void pathSum(TreeNode *root, int sum, vector<int>& input, vector<vector<int> >&res)
	{
		if (!root)
		{
			return;
		}
		int num = root->val;
		input.push_back(num);
		if (!root->left && !root->right)
		{
			if (sum-num==0)
			{
				res.push_back(input);
				input.pop_back();
				return;
			}
			else
			{
				input.pop_back();
				return;
			}
		}
		pathSum(root->left,sum-num,input,res);
		pathSum(root->right,sum-num,input,res);
		input.pop_back();
	}
	//求是否有一条 根-叶子 路径的和为某值
	bool hasPathSum(TreeNode *root, int sum) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		if (!root)
		{
			return false;
		}
		int num = root->val;
		if (!root->left && !root->right)
		{
			return sum-num==0;
		}
		if (hasPathSum(root->left,sum-num))
		{
			return true;
		}
		return hasPathSum(root->right,sum-num);

	}
	
	//求根节点到叶子节点的最短距离
	int minDepth(TreeNode *root) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		int depth=0;
		deque<TreeNode*>	deq;
		int beg,end;
		beg=0;
		end=1;
		if (!root)
		{
			return 0;
		}
		deq.push_back(root);
		TreeNode* node;
		bool flag = false;
		while (beg<end)
		{
			depth++;
			for (int i=beg; i<end; i++)
			{
				node = deq[i];
				if (node->left)
				{
					deq.push_back(node->left);
				}
				
				if (node->right)
				{
					deq.push_back(node->right);
				}
				if (!node->left && !node->right)
				{
					flag = true;
					break;
				}
				
			}// end for
			beg = end;
			end = deq.size();
			if (flag)
			{
				break;
			}
		}//end while
		return depth;
	}
	//判断树是否为平衡树，平衡树的定义为左右子树的高度相差不超过1
	bool isBalanced(TreeNode *root) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		if (root)
		{
			return true;
		}
		if (!isBalanced(root->left))
		{
			return false;
		}
		if (!isBalanced(root->right))
		{
			return false;
		}
		int left = treeHeight(root->left);
		int right = treeHeight(root->right);
		if (abs(left-right)<=1)
		{
			return true;
		}
		else
			return false;
	}
	int treeHeight(TreeNode* root)
	{
		if (!root)
		{
			return 0;
		}
		int left = treeHeight(root->left);
		int right = treeHeight(root->right);
		return max(left,right)+1;
	}
	//从底层往上开始访问
	vector<vector<int> > levelOrderBottom(TreeNode *root) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		vector<vector<int> > result;
		deque<TreeNode*> deq;
		if (!root)
		{
			return result;
		}
		deq.push_back(root);
		levelOrderBottom(deq,result);
		return result;
	}
	void levelOrderBottom(deque<TreeNode*>& deq,vector<vector<int> >&res)
	{
		deque<TreeNode*> tmdeq;
		TreeNode* node;
		if (deq.empty())
		{
			return ;
		}
		for (int i=0; i<deq.size();i++)
		{
			node = deq[i];
			if (node->left)
			{
				tmdeq.push_back(node->left);
			}
			if (node->right)
			{
				tmdeq.push_back(node->right);
			}
		}
		levelOrderBottom(tmdeq,res);
		vector<int>	level;
		while(!deq.empty())
		{
			node = deq.front();
			level.push_back(node->val);
			deq.pop_front();
		}
		res.push_back(level);
	}
	TreeNode *buildTree2(vector<int> &inorder, vector<int> &postorder) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		int sz = postorder.size();
		return buildTree2(inorder,postorder,0,0,sz);
	}
	TreeNode* buildTree2(vector<int> &inorder, vector<int> &postorder,int in_beg, int post_beg, int len)
	{
		if (len==0)
		{
			return NULL;
		}
		TreeNode* node = new TreeNode(postorder[post_beg+len-1]);
		if (len==1)
		{
			return node;
		}
		int num = postorder[post_beg+len-1];
		int ind=0;
		while (inorder[in_beg+ind]!=num)
		{
			ind++;
		}
		int in_beg1,post_beg1,in_beg2,post_beg2,len1,len2;
		in_beg1 = in_beg;
		post_beg1 = post_beg;
		len1 = ind;
		node->left = buildTree2(inorder,postorder,in_beg1,post_beg1,len1);
		in_beg2 = in_beg+ind+1;
		post_beg2 = post_beg+ind;
		len2 = len-len1-1;
		node->right = buildTree2(inorder,postorder,in_beg2,post_beg2,len2);
		return node;
	}
	//给出先序和中序
	TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		
		if (preorder.size()==0)
		{
			return NULL;
		}
		int sz = preorder.size();
		return buildTree(preorder,inorder,0,sz-1,0);

		//消耗太多内存
		/*int sz = preorder.size();
		if (sz==0)
		{
			return NULL;
		}
		TreeNode* p=new TreeNode(preorder[0]);
		if (sz==1)
		{
			return p;
		}
		int num = preorder[0];
		int ind = 0;
		while (inorder[ind]!=num)
		{
			ind++;
		}
		vector<int> pre1,ino1,pre2,ino2;
		pre1.assign(preorder.begin()+1,preorder.begin()+ind+1);
		ino1.assign(inorder.begin(),inorder.begin()+ind);
		TreeNode* left = buildTree(pre1,ino1);
		p->left = left;
		if (ind==inorder.size()-1)
		{
			return p;
		}
		pre2.assign(preorder.begin()+ind+1,preorder.end());
		ino2.assign(inorder.begin()+ind+1,preorder.end());
		TreeNode* right = buildTree(pre2,ino2);
		p->right = right;*/
		//return p;


	}
	TreeNode* buildTree(vector<int> &preorder, vector<int> &inorder, int pre, int end, int ino)
	{
		int sz = preorder.size();
		
		if (pre>end)
		{
			return NULL;
		}
		TreeNode* p = new TreeNode(preorder[pre]);
		if (pre == end)
		{
			return p;
		}
		int ind = ino;
		int num = preorder[pre];
		while (inorder[ind]!=num)
		{
			ind++;
		}
		int len = ind-ino;
		int pre1,pre2,ino1,ino2,end1,end2;
		pre1 = pre+1;
		end1 = pre+len;
		ino1 = ino;
		p->left = buildTree(preorder,inorder,pre1,end1,ino1);
		pre2 = pre+len+1;
		ino2 = ino+len+1;
		end2 = end;
		p->right = buildTree(preorder,inorder,pre2,end2,ino2);
		return p;
	}

	int maxDepth(TreeNode *root) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		deque<TreeNode*> deq;
		if (!root)
		{
			return 0;
		}
		deq.push_back(root);
		int beg,end;
		beg=0;
		end =1;
		int level=0;
		TreeNode* node;
		while (beg<end)
		{
			level++;
			for (int i=beg; i<end; i++)
			{
				node = deq[i];
				if (node->left)
				{
					deq.push_back(node->left);
				}
				if (node->right)
				{
					deq.push_back(node->right);
				}
				
			}
			beg = end;
			end = deq.size();
		}
		return level;
	}
	//蛇形广度优先探索
	vector<vector<int> > zigzagLevelOrder(TreeNode *root) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		vector<vector<int> >	res;
		if (!root)
		{
			return res;
		}
		deque<TreeNode*>	deq;
		deq.push_back(root);
		bool flag = true;
		int beg,end;
		beg = 0;
		end =1;
		TreeNode* node;
		while (beg<end)
		{
			vector<int>	level;	
			for (int i= beg; i<end; i++)
			{
				
				node = deq[i];
				if (flag)
				{
					level.push_back(node->val);
				}
				if (node->left)
				{
					deq.push_back(node->left);
				}
				if (node->right)
				{
					deq.push_back(node->right);
				}
			}
			if (!flag)
			{
				for (int i=end-1; i>=beg; i--)
				{
					level.push_back(deq[i]->val);
				}
			}
			res.push_back(level);
			flag = !flag;
			beg = end;
			end =deq.size();
		}
		return res;
	}
	//广度优先探索
	vector<vector<int> > levelOrder(TreeNode *root) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		vector<vector<int> >res;
		deque<TreeNode*> deq;
		if (!root)
		{
			return res;
		}
		deq.push_back(root);
		int beg,end;
		beg=0;
		end =1;
		TreeNode* node;
		while (beg<end)
		{
			vector<int>	level;
			for (int i=beg; i<end; i++)
			{
				node = deq[i];
				level.push_back(node->val);
				if (node->left)
				{
					deq.push_back(node->left);
				}
				if (node->right)
				{
					deq.push_back(node->right);
				}
			}
			beg = end;
			end = deq.size();
			res.push_back(level);
		}
		return res;
	}
	bool isSymmetric(TreeNode *root) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		if (!root)
		{
			return true;
		}
		//迭代方法
		deque<TreeNode*>	left,right;
		left.push_back(root->left);
		right.push_back(root->right);
		TreeNode *p,*q;
		while (!left.empty() && !right.empty())
		{
			p = left.front();
			q = right.front();
			left.pop_front();
			right.pop_front();
			if (!p && !q)
			{
				continue;
			}
			if (!p || !q)
			{
				return false;
			}
			if (p->val!=q->val)
			{
				return false;
			}
			left.push_back(p->left);
			left.push_back(p->right);
			right.push_back(q->right);
			right.push_back(q->left);
		}
		if (left.empty()&&right.empty())
		{
			return true;
		}
		return false;
		//递归方法
		//return isSymmetric(root->left,root->right);
	}
	bool isSymmetric(TreeNode* left, TreeNode* right)
	{
		if (!left && !right)
		{
			return true;
		}
		if (!left || !right)
		{
			return false;
		}

		if (left->val==right->val)
		{
			if(isSymmetric(left->left,right->right))
			{
				return isSymmetric(left->right,right->left);
			}
			else
				return false;
		}
		return false;

	}
	bool isSameTree(TreeNode *p, TreeNode *q) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		if (!p || !q)
		{
			if (!p && !q)
			{
				return true;
			}
			else 
				return false;
		}
		if (p->val==q->val)
		{
			if (isSameTree(p->left,q->left))
			{
				return isSameTree(p->right,q->right);
			}
			else
				return false;
		}
		else
			return false;
	}
	//有两个节点调换位置，发生错误
	void recoverTree(TreeNode *root) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		vector<TreeNode*>	list;
		inorder(root,list);
		if (list.size()<=1)
		{
			return;
		}
		TreeNode *first=NULL, *second=NULL;
		int i;
		for (i=0; i<list.size()-1; i++)
		{
			if (list[i]->val>list[i+1]->val)
			{
				first = list[i];
				break;
			}
		}
		for (int j=i+1; j<list.size()-1; j++)
		{
			if (list[j]->val > list[j+1]->val)
			{
				second = list[j+1];
				break;
			}
		}
		if (!second)
		{
			second = list[i+1];
		}
		int tmp = first->val;
		first->val = second->val;
		second->val = tmp;
		return;
	}
	void inorder(TreeNode* root, vector<TreeNode*>& list)
	{
		if (!root)
		{
			return;
		}
		inorder(root->left,list);
		list.push_back(root);
		inorder(root->right,list);
	}
	//判断是否为二叉查找树  左子树比本身小，右子树比本身大
	bool isValidBST(TreeNode *root) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		
		return isValidBST(root,INT_MIN,INT_MAX);
		
	}
	
	bool isValidBST(TreeNode* root, int minval, int maxval)
	{
		if (!root)
		{
			return true;
		}
		if (!(root->val>minval && root->val<maxval))
			return false;
		if (!isValidBST(root->left,minval,root->val))
		{
			return false;
		}
		if (!isValidBST(root->right,root->val,maxval))
		{
			return false;
		}
		return true;
		
	}

	//判断字符串s3是不是由s1和s2交错形成的
	bool isInterleave(string s1, string s2, string s3)
	{
		bool flag =isInterleave(s1,s2,s3,true) || isInterleave(s2,s1,s3,true);
		return flag;
	}

	bool isInterleave(string s1, string s2, string s3,bool flag) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function    
		
		int sz1 = s1.size();
		int sz2 = s2.size();
		int sz3 = s3.size();
		if (sz1+sz2!=sz3)
		{
			return false;
		}
		if (sz1==0 || sz2==0)
		{
			return s1==s3 || s2==s3;
		}
		vector<vector<bool> >mt(sz1+1, vector<bool>(sz2+1,false));
		mt[0][0]=true;
		for (int i=0; i<sz1;i++)
		{
			if (s1[i]==s3[i])
			{
				mt[i+1][0]=true;
			}
			else
				break;
		}

		for (int i=0; i<sz2; i++)
		{
			if (s2[i]==s3[i])
			{
				mt[0][i+1]=true;
			}
			else
				break;
		}
		
		for (int i=1; i<=sz1; i++)
		{
			for (int j=1; j<=sz2; j++)
			{
				mt[i][j] = (mt[i][j-1]&&s3[i+j-1]==s2[j-1])||(mt[i-1][j] && s1[i-1]==s3[i+j-1]);
			}
		}
		return mt[sz1][sz2];



		//时间复杂度太高
		/*int sz1 = s1.size();
		int sz2 = s2.size();
		int sz3 = s3.size();
		if (sz3!=sz1+sz2)
		{
			return false;
		}
		if (sz1==0 && sz2!=0)
		{
			return false;
		}
		if (sz2 ==0)
		{
			return s1==s3;
		}
		string begstr1,endstr1,begstr3,endstr3;
		for (int i=1; i<=sz1; i++)
		{
			begstr1 = s1.substr(0,i);
			endstr1 = s1.substr(i);
			begstr3 = s3.substr(0,i);
			endstr3 = s3.substr(i);
			if (begstr1==begstr3)
			{
				if (isInterleave(s2,endstr1,endstr3))
				{
					return true;
				}
				else 
					continue;
			}
			else 
				return false;
		}
		return false;*/
	}
	vector<TreeNode *> generateTrees(int n) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		
		return generateTrees(1,n);
	}

	vector<TreeNode*> generateTrees(int beg, int end)
	{
		if (beg>end)
		{
			vector<TreeNode*> res;
			res.push_back(NULL);
			return res;
		}
		vector<TreeNode*> result;
		for (int i=beg; i<=end; i++)
		{
			vector<TreeNode*>	left = generateTrees(beg,i-1);
			vector<TreeNode*>	right = generateTrees(i+1,end);

			for (int j=0; j<left.size();j++)
			{
				for (int k=0;k<right.size();k++)
				{
					TreeNode* root = new TreeNode(i);
					root->left = left[j];
					root->right = right[k];
					result.push_back(root);
				}
			}
		}
		return result;
	}


	

	//中序排列 刚好为1...n	求有多少种树的排列方法
	//   要排列成 1...n
	//   则必须是这样的机构 
	//    A
	//		 \
	//		 N
	//		/
	//	   B
	int numTrees(int n) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		vector<int> num(n+1,1);
		for (int i=2; i<=n; i++)
		{
			num[i]=0;
			for (int j=0; j<i; j++)
			{
				num[i] += num[j]*num[i-j-1];
			}
		}
		return num[n];
	}
	//中序排列
	vector<int> inorderTraversal(TreeNode *root) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		//利用迭代的方法
		vector<int> res;
		if (!root)
		{
			return res;
		}
		stack<TreeNode*>	stk;
		TreeNode* p = root;
		TreeNode* top;
		while (!stk.empty() || p)
		{
			if (p)
			{
				stk.push(p);
				p = p->left;
			}
			else
			{
				p = stk.top();
				res.push_back(p->val);
				stk.pop();
				p = p->right;
			}
		}
		return res;



		/*vector<int> left,right;
		vector<int> res;
		if (root==NULL)
		{
			return res;
		}
		if (root->left)
		{
			left = inorderTraversal(root->left);
			res = left;
		}
		res.push_back(root->val);
		if (root->right)
		{
			right = inorderTraversal(root->right);
			copy(right.begin(),right.end(),back_inserter(res));
		}
		return res;*/
	}

	//对ip字符串分析
	vector<string> restoreIpAddresses(string s) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		vector<string>	result;
		string str = "";
		restoreIpAddresses(0,s,str,result);
		return result;
	}
	void restoreIpAddresses(int ind, string s, string str,vector<string>& result)
	{
		if (s.empty())
		{
			return ;
		}
		int num;
		if (ind==3)
		{
			if (s.size()>3 || s.size()==0)
			{
				return ;
			}
			if (s[0]=='0'&& s.size()>1)
			{
				return;
			}
			num = atoi(s.c_str());
			if (num>=0 && num<=255)
			{
				str += s;
				result.push_back(str);
				return ;
			}
		}

		string begstr,endstr;
		int ipnum;
		for (int k=1; k<=3; k++)
		{
			if (s.size()<k)
			{
				return ;
			}
			begstr = s.substr(0,k);
			ipnum = atoi(begstr.c_str());
			if (begstr[0]=='0' && k>1)
			{
				return;
			}
			if (ipnum>=0 && ipnum<=255)
			{
				begstr = str+begstr+".";
				endstr = s.substr(k);
				restoreIpAddresses(ind+1,endstr,begstr,result);
			}
		}
	}
	//对链表中第m个节点到第n个节点反向
	ListNode *reverseBetween(ListNode *head, int m, int n) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		ListNode *ptrm,*ptrn, *p,*pnext, *ptrmpre, *ptrnnext,*ptmp;
		ListNode* phead = new ListNode(0);
		phead->next = head;
		if (m==n)
		{
			return head;
		}
		p = phead;
		pnext = head;
		int ind=-1;
		while (p)
		{
			ind++;
			if (ind<m-1)
			{
				p = pnext;
				pnext = pnext->next;
			}
			else if (ind==m-1)
			{
				ptrmpre = p;
				ptrm = pnext;
				p =pnext;
				pnext = pnext->next;
			}
			else if (ind<n)
			{
				ptmp = pnext->next;
				pnext->next = p;
				p = pnext;
				pnext = ptmp;
			}
			else if (ind==n)
			{
				ptrn = p;
				ptrnnext = pnext;
				ptrmpre->next = ptrn;
				ptrm->next = ptrnnext;
				break;
			}
		}
		return phead->next;
	}

	//对数组中的数组排列组合，数组中有重复数字，结果中不能包含相同数组
	vector<vector<int> > subsetsWithDup(vector<int> &S) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		multiset<int> numset(S.begin(),S.end());
		vector<int> input;
		vector<vector<int> >result;
		result.push_back(input);

		for (int ind=1; ind<=S.size(); ind++)
		{

			subsetsWithDup(0,ind,numset,input,result);
		}
		return result;
	}

	void subsetsWithDup(int k, int ind,multiset<int>& numset, vector<int>& input, vector<vector<int> >&result)
	{
		multiset<int>::iterator iter, iter1,iter2;
		multiset<int> cpset(numset);
		int num;
		for (iter = numset.begin(); iter!=numset.end(); iter++)
		{
			num = *iter;
			iter2 = iter;
			iter2--;
			if (iter!=numset.begin())
			{
				if (*iter==*iter2)
				{
					continue;
				}
			}

			input.push_back(num);
			iter1 = cpset.find(num);
			cpset.erase(iter1);
			if (k+1==ind)
			{
				result.push_back(input);
			}
			else
			{
				subsetsWithDup(k+1,ind,cpset,input,result);
			}
			input.pop_back();
			cpset.erase(num);
		}
	}
	// 可以将A-B编码成1-26，然后给出一个序列，给出有多少种解码方法
	int numDecodings(string s) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		
		//利用动态规划
		int len = s.size();
		if (len==0)
		{
			return 0;
		}
		vector<int> num(len,0);
		for (int i=len-1; i>=0; i--)
		{
			if (i==len-1 )
			{	
				if(s[i]>'0'&& s[i]<='9')
				{
					num[i]=1;
				}
				else 
					num[i]=0;
			}
			else if (i==len-2)
			{
				if ((s[i]=='1' && (s[i+1]>='0'&&s[i+1]<='9'))||(s[i]=='2' && (s[i+1]>='0'&&s[i+1]<='6')))
				{
					num[i] += 1;
				}

				if (s[i]>'0'&& s[i]<='9')
				{
					num[i] +=num[i+1];
				}

			}
			else
			{
				if (s[i]>'0' && s[i]<='9')
				{
					num[i] += num[i+1];
				}
				if ((s[i]=='1' && (s[i+1]>='0'&&s[i+1]<='9'))||(s[i]=='2' && (s[i+1]>='0'&&s[i+1]<='6')))
					num[i] += num[i+2];
			}

			if (i<len-1&&(num[i]==0 && num[i+1]==0))
			{
				break;
			}

		}
		return num[0];


		//复杂度太高	time limit
		/*int len = s.size();
		if (len==0)
		{
			return 0;
		}
		if (len==1)
		{
			if (s[0]>'0'&& s[0]<='9')
			{
				return 1;
			}
			else 
				return 0;
		}
		int sum=0;
		if (len>=2)
		{
			if (s[0]>'0' && s[0]<='9')
			{
				string str = s.substr(1);
				int num = numDecodings(str);
				sum +=num;
			}

			if ((s[0]=='1' && (s[1]>='0'&&s[1]<='9'))||(s[0]=='2' && (s[1]>='0'&&s[1]<='6')))
			{
				string str = s.substr(2);
				int num;
				if (str.empty())
				{
					num=1;
				}
				else
					num = numDecodings(str);
				sum +=num;
			}
		}
		return sum;*/
	}
	//将n位二进制数从0开始变化，后一个与前一个只有一位的变化
	vector<int> grayCode(int n) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		vector<int> res,tmp;
		if(n==0)
		{
			res.push_back(0);
			return res;
		}
		if (n==1)
		{
			res.push_back(0);
			res.push_back(1);
			return res;
		}
		tmp = grayCode(n-1);
		res = tmp;
		int add = 1<<(n-1);
		for (int i=tmp.size()-1; i>=0; i--)
		{
			res.push_back(add+tmp[i]);
		}
		return res;
	}
	//将两个排序的数组合并
	void merge(int A[], int m, int B[], int n) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		int num,ind;	//ind表示在a数组中插入的位置
		int low,high;
		if (m==0 )
		{
			for (int i=0; i<n; i++)
			{
				A[i]=B[i];
			}
			return;
		}
		low = 0, high = m-1;
		for (int i=0; i<n; i++)
		{
			num = B[i];
			ind = merge(A,low,high,num);
			low = ind;
			high = high+1;
		}
		return;
	}
	int merge(int a[], int low, int high, int num)
	{
		if (low==high)
		{
			if (num<a[low])
			{
				a[high+1]=a[low];
				a[high] = num;
				return low;
			}
			else
			{
				a[high+1]=num;
				return high+1;
			}		
		}
		int mid,_high = high;
		bool flag = false;
		while (low<=high)
		{
			mid = (low+high)/2;
			if (a[mid]==num)
			{
				flag = true;
				break;
			}
			else if (a[mid]<num)
			{
				low = mid+1;
			}
			else
			{
				high = mid-1;
			}
		}
		int ind=0;
		if (flag)
		{
			ind = mid+1;
		}
		else
			ind = low;
		for (int i=_high+1; i>ind; i--)
		{
			a[i] = a[i-1];
		}
		a[ind] = num;
		return ind;
	}
	//判断s2是否可以由s1拼凑出来，
	bool isScramble(string s1, string s2) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		int sz1,sz2;
		sz1 = s1.size();
		sz2 = s2.size();
		if (sz1!=sz2)
		{
			return false;
		}
		if (sz1==1)
		{
			return s1==s2;
		}
		multiset<char> set1(s1.begin(),s1.end()),set2(s2.begin(),s2.end());
		if (set1!=set2)
		{
			return false;
		}


		bool result = false;
		for (int i=1; i<sz1 && !result ; i++)
		{
			string left1,right1,left2,right2;
			left1 = s1.substr(0,i);
			right1 = s1.substr(i);
			left2 = s2.substr(0,i);
			right2 = s2.substr(i);
			result = isScramble(left1,left2) && isScramble(right1,right2);
			if (!result)
			{
				left2 = s2.substr(sz1-i);
				right2 = s2.substr(0,sz1-i);
				result = isScramble(left1,left2) && isScramble(right1,right2);
			}
		}
		return result;

	}
	//将链表中所有小于x的结点，放在 大于或等于x的结点之前
	ListNode *partition(ListNode *head, int x) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		ListNode *phead, *big, *p,*pre,*mid;
		phead = new ListNode(0);
		phead->next = head;
		p = head;
		pre = phead;
		bool flag = false;
		while (p)
		{
			if (!flag)
			{
				if (p->val<x)
				{
					pre->next = p;
					pre = p;
					p = p->next;
				}
				else
				{
					flag = true;
					mid = p;
					big = p;
					p = p->next;
				}
			}
			else
			{
				if (p->val<x)
				{
					pre->next = p;
					pre = p;
					p = p->next;
				}
				else
				{
					big->next = p;
					big = p;
					p = p->next;
				}
			}
		}// end while
		if (!flag)
		{
			return head;
		}
		else
		{
			pre->next = mid;
			big->next = NULL;
			return phead->next;
		}
	}
	//求矩阵中都为1的最大矩阵的面积
	int maximalRectangle(vector<vector<char> > &matrix) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		return 1;
	}
	//查找直方图中最大的包含面积
	int largestRectangleArea(vector<int> &height) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		int length = height.size();
		vector<int> left(length),right(length);
		for (int i=0; i<length; i++)
		{
			getleftside(height,i,i-1,left);
			
		}
		for (int i=0; i<length; i++)
		{
			getrightside(height,length-i-1, length-i, right);
		}

		int maxarea = 0;
		for (int i=0; i<length; i++)
		{
			int area = (right[i]-left[i]-1)*height[i];
			if (area>maxarea)
			{
				maxarea = area;
			}
		}
		return maxarea;
		

	}
	void getleftside(vector<int>& height, int i, int j, vector<int>& left)
	{
		if (i==0 || j==-1)
		{
			left[i]=-1;
			return;
		}

		if (height[j]==height[i])
		{
			left[i] = left[j];
		}
		else if (height[i]<height[j])
		{
			getleftside(height,i,left[j],left);
		}
		else
			left[i] = j;

	}

	void getrightside(vector<int>&height, int i, int j, vector<int>& right)
	{
		int length = height.size();
		if (i==length-1 || j == length)
		{
			right[i] = length;
			return;
		}
		if (height[i]==height[j])
		{
			right[i] = right[j];
		}
		else if (height[i]>height[j])
		{
			right[i] = j;
		}
		else
			getrightside(height,i,right[j],right);
	}
		/*int n = height.size();
		if (n==0)
		{
			return 0;
		}
		if (n==1)
		{
			return height[0];
		}

		vector<int> defarea(n+1,-1);
		vector<vector<int> > area(n+1,defarea);
		int maxarea = 0;
		for (int i=0; i<n; i++)
		{
			area[i][i] = height[i];
		}
		largestRectangleArea(height,area,0,n,maxarea);
		return maxarea;*/
	//}

	int largestRectangleArea(vector<int> &height, vector<vector<int> >&area, int low, int high,int& maxarea)
	{
		if (low>=high)
		{
			return -1;
		}
		vector<int>::iterator iter = min_element(height.begin()+low, height.begin()+high);
		int minheight = *iter;
		int minind = iter-height.begin();
		area[low][high-1] = minheight*(high-low);
		if (minind>low && area[low][minind-1]==-1)
		{
			largestRectangleArea(height,area,low,minind,maxarea);
		}
		if (minind+1<high && area[minind+1][high-1]==-1)
		{
			largestRectangleArea(height,area,minind+1,high,maxarea);
		}
		if (area[low][high-1]>maxarea)
		{
			maxarea = area[low][high-1];
		}
		if (minind+1<high && area[minind+1][high-1]>maxarea)
		{
			maxarea = area[minind+1][high-1];
		}
		if (minind>low && area[low][minind-1]>maxarea)
		{
			maxarea = area[low][minind-1];
		}
	}

	//删除重复的值,完全不保留
	ListNode *deleteDuplicates2(ListNode *head) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		ListNode* phead = new ListNode(INT_MAX), *pre = new ListNode(INT_MIN);
		ListNode *ppre, *p;
		phead->next = pre;
		ppre = phead;
		p = head;
		bool flag = false;
		while (p!=NULL)
		{
			if (p->val==pre->val)
			{
				flag = true;
				p = p->next;
			}
			else 
			{
				if (flag==true)
				{
					ppre->next = p;
					pre = p;
					p = p->next;
				}
				else
				{
					ppre->next = pre;
					ppre = pre;
					pre->next = p;
					pre = p;
					p = p->next;
				}
				flag = false;
			}
		}	// end while
		if (flag==true)
		{
			ppre->next = NULL;
		}
		else
			pre->next =NULL;
		return phead->next->next;
	}
	//删除重复的已排序链表中重复的值，保留一个
	ListNode *deleteDuplicates(ListNode *head) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		ListNode* phead = new ListNode(INT_MAX);
		ListNode *pre = phead, *p = head;
		while (p!=NULL)
		{
			if (p->val!=pre->val)
			{
				pre->next = p;
				pre = p;
				p = p->next;
			}
			else
			{
				p = p->next;
			}
		}
		pre->next = NULL;
		return phead->next;
	}
	bool search2(int A[], int n, int target) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		return search2(A,0,n-1,target);
	}
	bool search2(int a[],int low, int high, int target)
	{
		if (low>high)
		{
			return false;
		}
		int mid = (low+high)/2;
		if (a[mid]==target)
		{
			return true;
		}

		if (a[low]<a[mid])
		{
			if (target>=a[low] && target<a[mid])
			{
				return search2(a,low,mid-1,target);
			}
			else 
				return search2(a,mid+1,high,target);
		}
		else if (a[low]==a[mid])
		{
			//由于有重复数
			if (search2(a,low,mid-1,target))
			{
				return true;
			}
			else
				return search2(a,mid+1,high,target);
		}
		else
		{
			if (target>a[mid] && target<= a[high])
			{
				return search2(a,mid+1,high,target);
			}
			else
				return search2(a,low,mid-1,target);
		}
	
	}
	//在排序好的数组中保留1~2个相同的数字
	int removeDuplicates2(int A[], int n) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		if (n==0 || n==1)
		{
			return n;
		}
		int count = 1;
		int duplicate=0;
		for (int i=1; i<n; i++)
		{
			if (A[i]==A[i-1])
			{
				duplicate++;
				if (duplicate>=2)
				{
					continue;
				}
				else
				{
					A[count]=A[i];
					count++;
				}
			}
			else
			{
				A[count]=A[i];
				duplicate = 0;
				count++;
			}
		}
		return count;
	}
	//可以走上下左右四个方向，但是不能重复走
	bool exist(vector<vector<char> > &board, string word) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		int m,n;
		m = board.size();
		if (m==0)
		{
			return word=="";
		}
		if (word.empty())
		{
			return true;
		}
		n = board[0].size();
		vector<bool>	defflag(n,false);
		vector<vector<bool> >flag(m,defflag);
		
		for (int i=0; i<m; i++)
		{
			for (int j=0; j<n; j++)
			{
				char ch = board[i][j];
				if (ch!=word[0])
				{
					continue;
				}
				flag[i][j] = true;
				if (exist(board,word,1,flag,i,j))
				{
					return true;
				}
				else
					flag[i][j] = false;
			}
		}

		return false;
		
	}
	bool exist(vector<vector<char> > &board, string word, int ind, vector<vector<bool> >& flag, int r, int c)
	{
		int sz;
		sz = word.size();
		int m = board.size(), n=board[0].size();
		int location;
		if (ind==sz)
		{
			return true;
		}
		//左
		if (c!=0 && !flag[r][c-1] && board[r][c-1]==word[ind])
		{
			
			if (ind+1==sz)
			{
				return true;
			}
			flag[r][c-1]=true;
			if (exist(board,word,ind+1,flag,r,c-1))
				return true;
			else
			{
				flag[r][c-1]=false;
			}
		}
		//上
		if (r!=0 && !flag[r-1][c] && board[r-1][c]==word[ind])
		{
			if (ind+1==sz)
			{
				return true;
			}
			flag[r-1][c]=true;
			if (exist(board,word,ind+1,flag,r-1,c))
				return true;
			else
			{
				flag[r-1][c]=false;
			}
		}
		//右 
		if (c!=n-1 && !flag[r][c+1] && board[r][c+1]==word[ind])
		{
			if (ind+1==sz)
			{
				return true;
			}
			flag[r][c+1]=true;
			if (exist(board,word,ind+1,flag,r,c+1))
				return true;
			else
			{
				flag[r][c+1]=false;
			}
		}

		if (r!=m-1 && !flag[r+1][c] && word[ind]==board[r+1][c])
		{
			if (ind+1==sz)
			{
				return true;
			}
			flag[r+1][c]=true;
			if (exist(board,word,ind+1,flag,r+1,c))
				return true;
			else
			{
				flag[r+1][c]=false;
			}
		}
		return false;

	}

	//所有排列组合，无序法
	vector<vector<int> > subsets(vector<int> &S) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		set<int>	 numset;
		for (int i=0; i<S.size();i++)
		{
			numset.insert(S[i]);
		}
		vector<vector<int>	>res;
		vector<int>	result;
		res.push_back(result);
		for (int i=1; i<=numset.size(); i++)
		{
			set<int>	cpset(numset);
			result.clear();
			combine(0,i,cpset,result,res);
		}
		return res;
	}
	// 从1...n中选取K个数的组合
	vector<vector<int> > combine(int n, int k) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		vector<vector<int> >res;
		vector<int>	input;
		if (k<=0 || k>n)
		{
			return res;
		}
		set<int>	numset;
		for (int i=1; i<=n; i++)
		{
			numset.insert(i);
		}
		combine(0,k,numset,input,res);
		return res;
	}

	void combine(int ind, int k, set<int>& numset, vector<int>& input, vector<vector<int> >&res)
	{
		set<int>::iterator iter1,iter2;
		set<int> cpset(numset);
		for (iter1 = numset.begin(); iter1!=numset.end(); iter1++)
		{
			
			int num = *iter1;
			input.push_back(num);
			cpset.erase(num);
			if (ind+1==k)
			{
				res.push_back(input);
				input.pop_back();
			}
			else
			{
				combine(ind+1,k,cpset,input,res);
				input.pop_back();
			}
		}
	}

	//利用递归方法，实现功能
	string minWindow(string S, string T) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		
		map<char,int> hasfind,needfind;
		for (int i=0; i<T.size(); i++)
		{
			needfind[T[i]]++;
		}
		int count=0;
		int minSz = INT_MAX;
		string res;
		for (int beg=0, end=0; end<S.size();end++)
		{
			char ch = S[end];
			if (needfind.find(ch)==needfind.end())
			{
				continue;
			}
			hasfind[ch]++;
			if (hasfind[ch]<=needfind[ch])
			{
				count++;
			}
			if (count==T.size())
			{
				while (needfind.find(S[beg])==needfind.end() || hasfind[S[beg]]>needfind[S[beg]] )
				{
					if (needfind.find(S[beg])!=needfind.end() &&  hasfind[S[beg]]>needfind[S[beg]] )
					{
						hasfind[S[beg]]--;
					}
					beg++;
				}
				int length = end-beg+1;
				if (length<minSz)
				{
					minSz = length;
					res = S.substr(beg,length);
				}
			}

		}
		return count==T.size() ? res : "";

		//以下为o（nlgm）算法
	/*	multiset<char> strset,defset;
		deque<pair<char,int> > strdeq;
		deque<char> deqturn;
		for (int i=0; i<T.size(); i++)
		{
			strset.insert(T[i]);
		}
		defset = strset;
		bool flag = false;
		int minsz = -1;
		string result,res;
		multiset<char>::iterator iter,iter2;
		for (int i=0; i<S.size(); i++)
		{
			char c=  S[i];
			if (defset.find(c)==defset.end())
			{
				continue;
			}
			else
				strdeq.push_back(make_pair(c,i));
		}
		int beg=0,end=S.size();
		for (int i=strdeq.size()-1; i>=0;i--)
		{
			char c= strdeq[i].first;
			strset = defset;
			iter = strset.find(c);
			strset.erase(iter);
			end = i;
			beg = end-1;
			int length=0;
			while (beg>=0)
			{
				char ch = strdeq[beg].first;
				length = strdeq[end].second-strdeq[beg].second;
				if (minsz!=-1 && length+1>minsz)
				{
					break;
				}
				iter2 = strset.find(ch);
				if (iter2==strset.end())
				{
					beg--;
					continue;
				}
				strset.erase(iter2);
				if (strset.empty())
				{
					result = S.substr(strdeq[beg].second,strdeq[end].second-strdeq[beg].second+1);
					if (minsz==-1 || result.size()<minsz)
					{
						minsz = result.size();
						res = result;
					}
					break;
				}
				beg--;
			}
		}
		
		return res;*/
	}
	//对颜色进行排序， 0-red 1-white 2-bule
	void sortColors(int A[], int n) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		const int color = 3;
		//one-pass sort
		bool flag[color];
		memset(flag,false,color*sizeof(bool));
		int ind[color];
		memset(ind, -1,color*sizeof(int));
		for (int i=0; i<n; i++)
		{
			int num = A[i];
			//the first time of the color appear
			if (!flag[num])
			{
				flag[num]=true;
				ind[num] = i;
			}

				int j = color-1;
				int index = i;
				while (j>num)
				{
					if (flag[j])
					{
						A[index] = j;
						index = ind[j];
						ind[j]++;
					}
					j--;
				}
				if (index!=i)
				{
					A[index] = num;
					if (ind[num]==i)
					{
						ind[num] = index;
					}
				}

			
			
		}


		//计数排序
		/*int rednum,whitenum,bluenum;
		rednum = whitenum = bluenum = 0;
		for (int i=0; i<n; i++)
		{
			if (A[i]==0)
			{
				rednum++;
			}
			else if (A[i]==1)
			{
				whitenum++;
			}
			else 
				bluenum++;
		}
		for (int i=0; i<n; i++)
		{
			if (i<rednum)
			{
				A[i]=0;
			}
			else if (i<rednum+whitenum)
			{
				A[i]=1;
			}
			else 
				A[i]=2;
		}*/
	}
	// every array is sorted, ande the first value of an array is greater than the previous.
	bool searchMatrix(vector<vector<int> > &matrix, int target) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		// First, use the first integer find the index array
		int m,n;
		m = matrix.size();
		if (m==0)
		{
			return false;
		}
		n = matrix[0].size();

		int low,high,mid, ind;
		low = 0; 
		high = m-1;
		while (low<=high)
		{
			mid = (low+high)/2;
			if (matrix[mid][0]>target)
			{
				high = mid-1;
			}
			else if (matrix[mid][0]<target)
			{
				low = mid+1;
			}
			else
				return true;
		}
		ind = high;
		if (ind < 0)
		{
			return false;
		}

		low = 0;
		high = n-1;
		while (low<=high)
		{
			mid = (low+high)/2;
			if (matrix[ind][mid]>target)
			{
				high = mid-1;
			}
			else if (matrix[ind][mid]<target)
			{
				low = mid+1;
			}
			else
				return true;
		}
		return false;
	}
	//Given a m x n matrix, if an element is 0, set its entire row and column to 0. Do it in place.
	void setZeroes(vector<vector<int> > &matrix) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		int m,n;
		m = matrix.size();
		if (m==0)
		{
			return;
		}
		n = matrix[0].size();
		
		//o(1) space
		bool firstRowHas0, firstColHas0;
		firstColHas0 = false;
		firstRowHas0 = false;

		//Does the first row has a Zero
		for (int i=0; i<n; i++)
		{
			if (matrix[0][i]==0)
			{
				firstRowHas0 = true;
				break;
			}
		}
		
		//Does the first col has a zero
		for (int i=0; i<m; i++ )
		{
			if (matrix[i][0]==0)
			{
				firstColHas0 = true;
				break;
			}
		}

		// find zeros and store infos in first row and column
		for (int i=1; i<m; i++)
		{
			for (int j=1; j<n; j++)
			{
				if (matrix[i][j]==0)
				{
					matrix[i][0]=0;
					matrix[0][j] = 0;
				}
			}
		}

		//set zeros except first row and column
		for (int i=1; i<m; i++)
		{
			if (matrix[i][0]==0)
			{
				for (int j=1; j<n; j++)
				{
					matrix[i][j]=0;
				}
			}
		}

		for (int j=1; j<n; j++)
		{
			if (matrix[0][j]==0)
			{
				for (int i=1; i<m; i++)
				{
					matrix[i][j]=0;
				}
			}
		}

		if (firstColHas0)
		{
			for (int i=0; i<m; i++)
			{
				matrix[i][0]=0;
			}
		}
		if (firstRowHas0)
		{
			for (int j=0; j<n; j++)
			{
				matrix[0][j]=0;
			}
		}


		// o(m+n) space
		//bool *rowflag,*colflag;
		//rowflag = new bool[m];
		//colflag = new bool[n];
		//memset(rowflag,false,m*sizeof(bool));
		//memset(colflag,false,n*sizeof(bool));

		//for (int i=0; i<m; i++)
		//{
		//	bool flag = false;	//找没找到0
		//	for (int j=0; j<n; j++)
		//	{
		//		if (!flag && matrix[i][j]==0)
		//		{
		//			flag = true;
		//			rowflag[i]=true;
		//			colflag[j]=true;
		//		}
		//		else if (flag && !colflag[j] && matrix[i][j]==0)
		//		{
		//			colflag[j] = true;
		//		}
		//	}
		//}

		//对行列进行置零操作
	/*	for (int i=0; i<m; i++)
		{
			if (rowflag[i])
			{
				for (int j=0; j<n; j++)
				{
					matrix[i][j] = 0;
				}
			}
		}

		for (int i=0; i<n; i++)
		{
			if (colflag[i])
			{
				for (int j=0; j<m; j++)
				{
					matrix[j][i]=0;
				}
			}
		}*/
	}
	


	//求两个字符串中最少转换次数
	//只能 原地替代，插入，删除
	int minDistance(string word1, string word2) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		int m = word1.length();
		int n = word2.length();
		if (m==0 || n==0)
		{
			return max(m,n);
		}
		vector< vector<int> > table(m+1, vector<int>(n+1));
		for (int i=0; i<=m; i++)
		{
			table[i][0] = i;
		}
		for (int i=0; i<=n; i++)
		{
			table[0][i ]=i;
		}
		for (int i=1; i<=m; i++)
		{
			for (int j=1; j<=n; j++)
			{
				table[i][j] = word1[i-1]==word2[j-1] ? table[i-1][j-1] : table[i-1][j-1]+1;
				int del = table[i-1][j]+1;
				int insert = table[i][j-1]+1;
				table[i][j] = min(table[i][j],min(del,insert));
			}
		}
		return table[m][n];
	}

	void minDistance(int ind, int& minval,  list<char>& chvec,  const string& word )
	{
		if (ind>minval)
		{
			return;
		}
		list<char> clonelist;
		while (ind<=minval)
		{
			//插入操作
			ind++;
			if (ind>minval)
			{
				return;
			}
			list<char>::iterator iter = chvec.begin(),iter1, iter2;
			for (iter = chvec.begin(); iter!=chvec.end(); iter++)
			{
				iter2 = chvec.insert(iter,' ');
				for (int i=0; i<word.size(); i++)
				{
					*iter2 = word[i];
					string str(chvec.begin(),chvec.end());
					if (str == word && ind<minval)
					{
						minval = ind;
						return;
					}
					minDistance(ind,minval,chvec,word);
				}
				iter1 = chvec.erase(iter2);
				if (iter!=iter1)
				{
					cout<<"insert error"<<endl;
				}
			}
			ind--;
			//删除操作
			ind++;		
			if (ind>minval)
			{
				return;
			}
			for (iter = chvec.begin(); iter!=chvec.end(); iter++)
			{
				char ch = *iter;

				iter2 = chvec.erase(iter);
				string str(chvec.begin(),chvec.end());
				if (str == word && ind<minval)
				{
					minval = ind;
					return;
				}
				minDistance(ind,minval,chvec,word);
				iter = chvec.insert(iter2,ch);
			}
			ind--;
			//替代操作
			ind++;
			if (ind>minval)
			{
				return;
			}
			for (iter = chvec.begin(); iter!=chvec.end(); iter++)
			{
				char ch =*iter;
				for(int i=0; i<word.size(); i++)
				{
					*iter = word[i];
					string str(chvec.begin(),chvec.end());
					if (str == word && ind<minval)
					{
						minval = ind;
						return;
					}
					minDistance(ind,minval,chvec,word);
				}
				*iter = ch;
			}
			ind--;
		}
	}
	//求unix路径的简化模式
	string simplifyPath(string path) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		int ind = 0;
		vector<char> res;
		while(ind<path.size())
		{
				if (path[ind]=='.')
				{
					//如果是"../"
					if (ind<path.size()-2 && path[ind+1]=='.' && path[ind+2]=='/')
					{
						int num=0;
						for (int i=res.size()-1; i>=0; i--)
						{
							if (res[i]=='/')
							{
								num++;
								if (num==2)
								{
									break;
								}
							}
							res.pop_back();
						}
						if (res.empty())
						{
							res.push_back('/');
						}
						ind = ind+3;
					}
					else if (ind < path.size()-1 && path[ind+1]=='/')
					{
						ind = ind+2;
					}
					else
					{
						res.push_back(path[ind]);
						ind++;
					}
				}
				else if (ind>0 && path[ind]=='/' && path[ind-1]=='/')
				{
					ind = ind+1;
				}
				else
				{
					res.push_back(path[ind]);
					ind++;
				}				
		}
		if (res.size()>1 && res[res.size()-1]=='/')
		{
			res.pop_back();
		}
		string str(res.begin(),res.end());
		return str;
		
	}
	//每次只能爬 1步 或者两步
	int climbStairs(int n) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		if (n==1 || n==0)
		{
			return 1;
		}
		vector<int> step(n+1,1);
		for (int i=2; i<=n; i++)
		{
			step[i] = step[i-1]+step[i-2];
		}
		return step[n];
	}
	//计算平均根
	int sqrt(int x) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		if (x<0)
		{
			return -1;
		}

		long long x2 = x;
		long long low = 0;
		long long high = x;
		long long mid;
		while (low <= high)
		{
			mid = (low+high)/2;
			if (mid*mid==x2 ||(mid*mid<x2 && (mid+1)*(mid+1)>x2))
			{
				return mid;
			}
			else if (mid*mid < x2)
			{
				low = mid+1;
			}
			else 
			{
				high = mid-1;
			}
		}



	}
	//将单词左右对齐显示，每行最多只能有L个字符
	vector<string> fullJustify(vector<string> &words, int L) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		vector<string> result;
		string line;
		vector<string> line_word;
		int sz=0, wordsz=0;
		int ind=0;
		while (ind<words.size())
		{
			//如果此时在原有基础上可以继续增加，则把字符串插入
			if (sz+words[ind].size()<=L)
			{
				line_word.push_back(words[ind]);
				sz = sz+words[ind].size()+1;
				wordsz += words[ind].size();
			}
			else	//表示无法继续增加了
			{
				
				int num = line_word.size();
				if (num==1)
				{
					line = line_word[0] + string(L-line_word[0].size(),' ');
					result.push_back(line);
				}
				else
				{
					int ressz = L-wordsz;
					//如果刚好可以把所有空格完全分配
					if (ressz%(num-1)==0)
					{
						string space(ressz/(num-1),' ');
						line = "";
						for (int i=0; i<line_word.size()-1; i++)
						{
							line += line_word[i]+space;
						}
						line += line_word[line_word.size()-1];
						result.push_back(line);
					}
					//不能完全分配，则把多余的放到第一个单词后面
					else
					{
						int reservenum = ressz%(num-1);
						line = "";
						for (int i=0; i<reservenum; i++)
						{
							string space(ressz/(num-1)+1,' ');
							line = line + line_word[i]+space;
						}
						for (int i=reservenum; i<num-1; i++)
						{
							string space(ressz/(num-1),' ');
							line = line+line_word[i]+space;
						}
						line = line+line_word[num-1];
						result.push_back(line);
					}
				}
				line_word.clear();
				sz = 0;
				wordsz=0;
				sz = words[ind].size()+1;
				wordsz = words[ind].size();
				line_word.push_back(words[ind]);
			}
			ind++;
		}
		if (!line_word.empty())
		{
			string space(L-sz+1,' ');
			line = "";
			for (int i=0; i<line_word.size()-1; i++)
			{
				line = line+ line_word[i] + " ";
			}
			line = line + line_word[line_word.size()-1] + space;
			result.push_back(line);
		}

		return result;
	}
	//一个数用数组表示
	vector<int> plusOne(vector<int> &digits) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		int add=1;
		int dig, sum;
		for (int ind = digits.size()-1; ind>=0; ind--)
		{
			dig = digits[ind];
			sum = dig+ add;
			digits[ind] = sum%10;
			add = sum/10;
			if (add==0)
			{
				break;
			}
		}
		if (add==0)
		{
			return digits;
		}
		else 
		{
			vector<int>	tmp(digits.size()+1);
			tmp[0] = add;
			for (int i=0; i<digits.size(); i++)
			{
				tmp[i+1] = digits[i];
			}
			return tmp;
		}
	}
	//判断字符串是否可以表示为 数
	//浮点数 [whitespace] [sign] [digits] [.digits] [ {d | D | e | E }[sign]digits]
	//整数 [whitespace] [sign] [digits]]
	//貌似这里没有判断十六进制和8进制数
	bool isNumber(const char *s) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		//利用有限状态机来实现该功能
		int sz = strlen(s);
		if (sz==0)
		{
			return false;
		}
		bool flag = true;
		int state=0;
		int ind = 0;
		bool decimal = false;
		bool brkflag = false;
		while (ind<=sz)
		{
			char c = s[ind];
			switch(state)
			{
			case 0:
				if (c==' ')
				{
					state = 0;
				}
				else if (c=='+' || c=='-')
				{
					state = 1;
				}
				else if (c>='0' && c<='9')
				{
					state = 2;
				}
				else if (c=='.')
				{
					state = 3;
					decimal =true;
				}
				else
					return false;
				break;
			case 1:
				if (c>='0' && c<='9')
				{
					state = 2;
				}
				else if (c=='.')
				{
					decimal = true;
					state = 3;
				}
				else
					return false;
				break;
			case 2:
				if (c>='0' && c<='9')
				{
					state =2;
				}
				else if (c=='.')
				{
					state = 3;
					decimal = false;
				}
				else if (c==' ')
				{
					state = 9;
				}
				else if (c=='e' || c=='E' || c=='d' || c=='D')
				{
					state = 4;
				}
				else if (c=='\0')
				{
					return true;
				}
				else
					return false;
				break;
			case 3:
				if (!flag && (c=='e' || c=='E' || c=='d' || c=='D'))
				{
					state = 4;
				}
				else if (c>='0' && c<='9')
				{
					state =5;
				}
				else if (c==' ' && !decimal)
				{
					state = 9;
				}
				else if (c=='\0' && !decimal)
				{
					return true;
				}
				else 
					return false;
				break;
			case 4:
				if (c=='+' || c=='-')
				{
					state = 7;
				}
				else if (c>='0' && c<='9')
				{
					state = 6;
				}
				else
					return false;
				break;
			case 5:
				if (c>='0' && c<='9')
				{
					state = 5;
				}
				else if (c=='e' || c=='E' || c=='d' || c=='D')
				{
					state = 4;
				}
				else if (c==' ')
				{
					state = 9;
				}
				else if (c=='\0')
				{
					return true;
				}
				else 
					return false;
				break;
			case 6:
				if (c>='0' && c<='9')
				{
					state = 6;
				}
				else if (c==' ')
				{
					state = 9;
				}
				else if (c=='\0')
				{
					return true;
				}
				else
					return false;
				break;
			case 7:
				if (c>='0' && c<='9')
				{
					state = 6;
				}
				else 
					return false;
				break;
			case 9:
				if (c==' ')
				{
					state = 9;
				}
				else if (c=='\0')
				{
					return true;
				}
				else 
					return false;
				break;
			default:
				return false;
				break;
			}
			
			ind++;
		}
		return false;
	}
	//对两个二进制字符串进行加法运算
	string addBinary(string a, string b) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		int m = a.size();
		int n = b.size();
		int sz = max(m,n);
		string sum(max(m,n),'0');
		
		int flag = 0;
		int numa,numb,numc;
		int i=m-1,j=n-1,ind = sz-1;
		while (i>=0 && j>=0)
		{
			numa = a[i]-'0';
			numb = b[j]-'0';
			numc = numa+numb+flag;
			sum[ind] = numc%2 + '0';
			flag = numc/2;
			i--;
			j--;
			ind--;
		}
		if (flag==0)
		{
			while(i>=0)
			{
				sum[ind--] = a[i--];
			}
			while (j>=0)
			{
				sum[ind--] = b[j--];
			}
			return sum;
		}
		else
		{
			while (i>=0)
			{
				numa = a[i--]-'0';
				numc = numa+flag;
				sum[ind--] = numc%2+'0';
				flag = numc/2;
			}
			while (j>=0)
			{
				numb = b[j--]-'0';
				numc = numb+flag;
				sum[ind--]=numc%2+'0';
				flag = numc/2;
			}

			if (flag !=0)
			{
				string add(1,'1');
				return add+sum;
			}
			else
				return sum;
		}

	}
	//合并两个已排序的链表
	ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		ListNode *head, *p,*tmp, *p1,*p2;
		head = NULL;
		p1 = l1;
		p2 = l2;
		if (p1==NULL)
		{
			return p2;
		}
		if (p2==NULL)
		{
			return p1;
		}
		//对两个链表进行排序
		while (p1 && p2)
		{
			if (p1->val < p2->val)
			{
				tmp = p1;
				p1 = p1->next;
			}
			else
			{
				tmp = p2;
				p2 = p2->next;
			}
			if (head==NULL)
			{
				head = tmp;
				p = tmp;
			}
			else
			{
				p->next = tmp;
				p = tmp;
			}
		}
		if (p1)
		{
			p->next = p1;
		}
		else
			p->next = p2;
		return head;
	}
	//从左上到右下的路径上的累加和最小
	// 每个数为非负数
	int minPathSum(vector<vector<int> > &grid) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		int m= grid.size();
		if (m==0)
		{
			return 0;
		}
		int n = grid[0].size();
		if (n==0)
		{
			return 0;
		}

		for (int i = m-1; i>=0; i--)
		{
			for (int j = n-1; j>=0; j--)
			{
				if (i==m-1 && j==n-1)
				{
					continue;
				}
				if (i==m-1)
				{
					grid[i][j] = grid[i][j+1] + grid[i][j];
					
				}
				else if (j==n-1)
				{
					grid[i][j] +=grid[i+1][j];
				}
				else
				{
					grid[i][j] += min(grid[i+1][j], grid[i][j+1]) ;
				}

			}
		}
		return grid[0][0];
	}
	//路径上不能有障碍物
	int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		int m,n;
		m = obstacleGrid.size();
		n = obstacleGrid[0].size();
		if (obstacleGrid[0][0]==1)
		{
			return 0;
		}
		if (obstacleGrid[m-1][n-1]==1)
		{
			return 0;
		}
		vector<int> defvec(n,1);
		vector<vector<int> > path(m,defvec);
		
		for (int i=m-1; i>=0; i--)
		{
			for (int j=n-1;j>=0; j--)
			{
				int num = 0;
				if (i!=m-1 && obstacleGrid[i+1][j]==0)
				{
					num = num+ path[i+1][j];
				}
				
				if (j!=n-1 && obstacleGrid[i][j+1]==0)
				{
					num = num+path[i][j+1];
				}

				if (i==m-1 && j==n-1)
				{
					num = 1;
				}
				path[i][j] = num;
			}
		}
		return path[0][0];
	}
	//A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

	//The robot can only move either down or right at any point in time.
	//The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).
	//	How many possible unique paths are there?
	//由于机器人只能向右和向下
	//
	int uniquePaths(int m, int n) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		vector<int> defvec(n,1);
		vector<vector<int> > path(m,defvec);
		for (int ind=m-2; ind>=0; ind--)
		{
			for (int i = n-2; i>=0; i--)
			{
				path[ind][i] = path[ind+1][i] + path[ind][i+1];
			}
		}
		return path[0][0];
	}
	int uniquePaths(int w, int c, int m, int n)
	{
		
	}

	//将节点循环右移
	ListNode *rotateRight(ListNode *head, int k) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		ListNode* p = head, *end;
		int n = 0;
		//求链表长度
		while (p)
		{
			n++;
			end = p;
			p = p->next;
		}

		k = k%n;
		if (k==0)
		{
			return head;
		}

		int c=0;
		p = head;
		ListNode *pre;
		while (c!=k+1)
		{
			p = p->next;
			c++;
		}
		pre = p;
		p = head;
		while (pre)
		{
			p = p->next;
			pre = pre->next;
		}
		
		end->next = head;
		pre = p->next;
		p->next = NULL;
		return pre;




	}
	string getPermutation(int n, int k) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function

		//记录n!的个数
		vector<int> numbers(n+1,1);
		set<int> numset;
		for (int i=1; i<numbers.size(); i++)
		{
			numbers[i] = i*numbers[i-1];
			numset.insert(i);
		}
		if (k<1 && k>numbers[n])
		{
			return "";
		}

		vector<int> strnum(n+1);
		set<int>::iterator iter;
		int ind = 1;
		k = k-1;
		while (!numset.empty())
		{
			int c = (k)/numbers[n-ind];
			iter = numset.begin();
			while (c)
			{
				c--;
				iter++;
			}
			c = *iter;
			numset.erase(iter);
			strnum[ind] = c;
			k = (k)%numbers[n-ind];
			ind++;
			if (k==0)
			{
				break;
			}
		}
		iter = numset.begin();
		while (iter!=numset.end())
		{
			strnum[ind] = *iter;
			iter++;
			ind++;
		}
		string str(n,'0');
		for (int i=1; i<n+1; i++)
		{
			str[i-1] = strnum[i]+str[i-1];
		}
		return str;
	}

	


	//用螺旋状的方式生成一个矩阵，从1~N^2
	vector<vector<int> > generateMatrix(int n) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function

		vector<int> num(n,0);
		vector<vector<int> >result(n,num);
		if (n==0)
		{
			return result;
		}
		int digit = 1;
		for (int i=0; i<n/2; i++)
		{
			int r,c;
			r = i;
			c = i;
			for (int j = c; j< n-1-c; j++)
			{
				result[r][j] = digit;
				digit++;
			}
			for (int j=r; j<n-1-r; j++)
			{
				result[j][n-1-c] = digit;
				digit++;
			}
			for (int j = n-1-c; j>c; j--)
			{
				result[n-1-r][j] = digit;
				digit++;
			}
			for (int j = n-1-r; j>r; j--)
			{
				result[j][c] = digit;
				digit++;
			}
		}
		if(n%2!=0)  result[n/2][n/2] = digit;
		return result;
	}
	//求最后一个单词的长度，用' '分割两个单词
	int lengthOfLastWord(const char *s) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		int num = 0;
		int cnt=0;
		bool flag = true;
		while (s[num]!='\0')
		{
			char ch = s[num];
			if (!flag && ch!=' ')
			{
				flag = true;
				cnt=1;
			}
			else if (flag)
			{
				if (ch!=' ')
				{
					cnt++;
				}
				else
				{
					flag = false;
					
				}
			}
			num++;
			
		}
		return cnt;

	}
	//插入新的间隔
	vector<Interval> insert(vector<Interval> &intervals, Interval newInterval) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		vector<Interval> result;
		if (intervals.size() == 0)
		{
			result.push_back(newInterval);
			return result;
		}
		int ind=0;
		map<int,int>	maptm;
		for (ind = 0; ind<intervals.size(); ind++)
		{
			maptm.insert(make_pair(intervals[ind].start,intervals[ind].end));
		}
		map<int,int>::iterator iter2, iter = maptm.find(newInterval.start);
		//如果没有找到
		if (iter==maptm.end())
		{
			maptm.insert(make_pair(newInterval.start,newInterval.end));
			iter = maptm.find(newInterval.start);		
		}
		else
		{
			iter->second = max(iter->second,newInterval.end);
		}
		if (iter!=maptm.begin())
		{
			iter--;
		}
		
		Interval cmpInt(iter->first,iter->second);
		iter2 = maptm.begin();
		while (iter2!=iter)
		{
			result.push_back(Interval(iter2->first,iter2->second));
			iter2++;
		}
		iter2++;
		while(iter2!=maptm.end())
		{
			if (cmpInt.end<iter2->first)
			{
				result.push_back(cmpInt);
				cmpInt.start = iter2->first;
				cmpInt.end = iter2->second;
			}
			else
			{
				cmpInt.end = max(iter2->second,cmpInt.end);
			}
			iter2++;
		}
		result.push_back(cmpInt);
		return result;
		
		




	}

	//合并重叠的时间间隔
	//For example,
	//	Given [1,3],[2,6],[8,10],[15,18],
	//	return [1,6],[8,10],[15,18].
	vector<Interval> merge(vector<Interval> &intervals) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		if (intervals.size()<=1)
		{
			return intervals;
		}
		vector<Interval>	result; 
		map<int,int> timemap;
		for (int i=0; i<intervals.size(); i++)
		{
			int beg = intervals[i].start;
			int end = intervals[i].end;
			if (timemap.find(beg)==timemap.end())
			{
				timemap.insert(make_pair(beg,end));
			}
			else
			{
				timemap[beg] = max(end,timemap[beg]);
			}
		}

		map<int,int>::iterator iter1, iter2;
		iter1 = timemap.begin();
		iter2 = ++timemap.begin();
		Interval cmpInt(iter1->first,iter1->second);
		while (iter2!=timemap.end())
		{
			if ( iter2->first > cmpInt.end)
			{
				result.push_back(cmpInt);
				cmpInt.start = iter2->first;
				cmpInt.end = iter2->second;
			}
			else
			{
				cmpInt.end =max(iter2->second,cmpInt.end);
			}
			iter2++;
		}
		result.push_back(cmpInt);

		return result;

	}
	
	

	//判断是否可以跳到终点
	bool canJump(int A[], int n) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		if (n<=1 )
		{
			return true;
		}

		int curmax, nextmax, begid, id;
		curmax = A[0];
		begid = 0;
		while (curmax<n-1)
		{
			nextmax = curmax;
			for (id = begid; id<=curmax; id++)
			{
				if (id+A[id]>nextmax)
				{
					nextmax = id+A[id];
				}
			}
			begid = curmax;
			curmax = nextmax!=curmax ? nextmax : A[curmax]+curmax;
			if (curmax == begid)
			{
				return false;
			}
		}
		return true;

	}


	//螺旋状遍历
	vector<int> spiralOrder(vector<vector<int> > &matrix) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		vector<int> result;
		int sz = matrix.size();
		if(sz==0)   return result;
		spiralOrder(matrix,0,0,result);
		return result;
	}

	void spiralOrder(const vector<vector<int> > &matrix, int r, int c,vector<int>& res)
	{
		int m = matrix.size();
		int n = matrix[0].size();

		if (r>=(m+1)/2 || c>= (n+1)/2)
		{
			return;
		}
		//行

		if (c==n-1-c)
		{
				for (int i=r; i<=m-1-r; i++)
				{
					res.push_back(matrix[i][c]);
				}		
		}
		else
		{
			for (int i=c; i<=n-1-c; i++)
			{
				res.push_back(matrix[r][i]);
			}
			if (r==m-1-r)
			{
				;
			}
			else
			{
				for(int i=r+1; i<m-1-r;i++)
					res.push_back(matrix[i][n-1-c]);
				for (int i=n-1-c; i>=c; i--)
				{
					res.push_back(matrix[m-1-r][i]);
				}
				for (int i=m-1-r-1; i>r; i--)
				{
					res.push_back(matrix[i][c]);
				}
			}
		}
		spiralOrder(matrix,r+1,c+1,res);
	}


	//找到子串和最长的和
	int maxSubArray(int A[], int n) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		
		int curleft,curright, left,right,curmax, maxval;
		if (n==1)
		{
			return A[0];
		}
		maxval = A[0];
		curleft = curright = left = right =  curmax=0;
		for (int i=0; i<n; i++)
		{
			curmax = curmax+A[i];
			if (curmax>0)
			{
				curright = i;
				if (curmax > maxval)
				{
					maxval = curmax;
					left = curleft;
					right = curright;
				}
			}
			else
			{
				if (curmax > maxval)
				{
					maxval = curmax;
					left = i;
					right = i;
				}
				curmax = 0;
				curleft = i+1;
				curright = i+1;
				
			}
		}
		return maxval;

		
	}



	int totalNQueens(int n) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		int* a = new int[n];
		bool* canuse = new bool[n];
		memset(canuse,true,sizeof(bool)*n);
		int cnt = 0;
		totalNQueens(0,n,a,canuse,cnt);
		return cnt;
	}
	void totalNQueens(int dep, int n,  int*a, bool* canuse, int& cnt)
	{
		if (dep == n)
		{
			cnt++;
			return ;
		}
		for (int i=0; i<n; i++)
		{
			if (canuse[i] && checkQueens(i,dep,a))
			{
				canuse[i] = false;
				a[dep] = i;
				totalNQueens(dep+1,n,a,canuse,cnt);
				canuse[i]=true;
			}
		}
	}
	bool checkQueens(int x, int depth, int* a)
	{
		for (int i=0; i<depth; i++)
		{
			if (abs(i-depth) == abs(a[i]-x))
			{
				return false;
			}
		}
		return true;
	}
	//N皇后问题
	vector<vector<string> > solveNQueens(int n) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		vector<int> defvec(n,0);
		vector<vector<int> >input(n,defvec);
		vector<vector<string> >result;
		
		solveNQueens(0,n,input,result);
		return result;
	}
	
	
	void solveNQueens(int ind, int n, vector<vector<int> >&input, vector<vector<string> >& res)
	{
		if (ind==n)
		{
			vector<string> tmp;
			for (int i=0; i<n; i++)
			{
				string str;
				for (int j=0; j<n; j++)
				{
					if (input[i][j])
					{
						str.push_back('Q');
					}
					else
						str.push_back('.');
				}
				tmp.push_back(str);
			}
			res.push_back(tmp);
			return;
		}
		for (int i=0; i <n; i++)
		{
			input[ind][i] = 1;
			if (!solveNQueens(input,n))
			{
				input[ind][i]=0;
				continue;
			}
			solveNQueens(ind+1,n,input,res);
			input[ind][i]=0;
		}
			
	}
	bool solveNQueens(const vector<vector<int> >&input, int n)
	{
		for (int i= 0 ; i<n; i++ )
		{
			for (int j=0; j<n; j++)
			{
				if (input[i][j]==0)
				{
					continue;
				}
				else
				{
					//判断 上下、前后
					for (int k=0; k<n; k++)
					{
						if (input[i][k] && k!=j)
						{
							return false;
						}

						if (input[k][j] && k!=i)
						{
							return false;
						}

						if (i-k >=0 && k!=0)
						{
							if (j-k>=0  && input[i-k][j-k])
							{
								return false;
							}
							if (j+k<=n-1  && input[i-k][j+k])
							{
								return false;
							}
						}

						if (i+k <=n-1 && k!=0)
						{
							if (j-k>=0 && input[i+k][j-k])
							{
								return false;
							}
							if (j+k<=n-1 && input[i+k][j+k])
							{
								return false;
							}
						}
					}
				}
			}
		}
		return true;
	}
	
	//求 x^n
	double pow(double x, int n) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		int abn = abs(n);
		bool positive = true;
		if (n<0)
		{
			positive = false;
		}
		if (n==0)
		{
			return 1.0;
		}
		if (abn==1)
		{
			return positive ? x : 1./x;
		}
		
		if (x==0.0)
		{
			return 0.0;
		}


		if (abs(x)<1)
		{
			positive = positive ? false : true;
			x = 1./x;
		}
		if (abs(x)==1.)
		{
			return x==1. ? 1. : (abn%2==0 ? 1. : -1.);
		}
		//判断x是否为10的倍数
		
		double result = x;
		double tmp, sumres=1.0 ;
		long long cnt =1;
		map<int,double> mapnum;
		mapnum[1] = x;
		while(cnt<abn)
		{
			tmp = result;
			result = result*result;
			cnt  = cnt<<1;
			mapnum[cnt] = result;
		}
		cnt = cnt>>1;
		sumres = mapnum[cnt];
		abn = abn-cnt;

		while (abn!=1)
		{
			cnt =1;
			while (cnt<abn)
			{
				cnt=cnt<<1;
			}
			cnt = cnt>>1;
			abn=abn-cnt;
			sumres = sumres* mapnum[cnt];
		}
		sumres = sumres*x;
		return positive ? sumres: 1./sumres;

	}

	//判断是否是回文构造
	//即 单词里面的字母相同，只是顺序不同，而且题目中提到所有字母都是小写字符
	//可以先对字符串排序，利用set<> 来判断
	vector<string> anagrams(vector<string> &strs) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function

		map<string,int> mapstr;
		vector<string> result;
		bool flag = false;
		for (size_t i=0; i!=strs.size(); i++)
		{
			string str = strs[i];
			sort(str.begin(),str.end());
			if (mapstr.find(str)==mapstr.end())
			{
				mapstr.insert(make_pair(str,i));
			}
			else
			{
				if (mapstr[str]>=0)
				{
					result.push_back(strs[mapstr[str]]);
					mapstr[str] = -1;
				}
				result.push_back(strs[i]);
			}
		}
		return result;
	}
	void rotate(vector<vector<int> > &matrix) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		int n = matrix.size();
		if (n==0 || n==1)
		{
			return;
		}
		int m = matrix[0].size();
		if (m!=n)
		{
			return;
		}

		for (int i=0; i<n/2 ; i++)
		{
			for(int j=i; j<n-i-1; j++)
			{
				int tmp = matrix[i][j];
				matrix[i][j] =  matrix[n-1-j][i];
				matrix[n-1-j][i] = matrix[n-1-i][n-1-j];
				matrix[n-1-i][n-1-j] = matrix[j][n-1-i];
				matrix[j][n-1-i] = tmp;
			}
		}
	}
	//排列组合  可以利用dfs来做
	vector<vector<int> > permuteUnique(vector<int> &num) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		vector< vector<int> >result;
		vector<int> input;
		if (num.empty())
		{
			return result;
		}
		multiset<int> numset(num.begin(),num.end());
		permuteUnique(numset,input,result);
		return result;
	}
	// dfs
	void permuteUnique(multiset<int>& numset, vector<int>& input, vector< vector<int> >& res)
	{
		if (numset.empty())
		{
			res.push_back(input);
			return;
		}
		multiset<int>::iterator iter = numset.begin();
		multiset<int> tmpset(numset);
		multiset<int> uniqueset;
		while(iter!=numset.end())
		{
			int num = *iter;
			if (uniqueset.find(num)==uniqueset.end())
			{
				uniqueset.insert(num);
			}
			else
				return;
			input.push_back(num);
			multiset<int>::iterator tmpiter = tmpset.find(num);
			tmpset.erase(tmpiter);
			permuteUnique(tmpset,input,res);
			input.pop_back();
			tmpset.insert(num);
			iter++;
		}
	}
	//排列组合  可以利用dfs来做
	vector<vector<int> > permute(vector<int> &num) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		vector< vector<int> >result;
		vector<int> input;
		if (num.empty())
		{
			return result;
		}
		multiset<int> numset(num.begin(),num.end());
		permute(numset,input,result);
		return result;
	}
	// dfs
	void permute(multiset<int>& numset, vector<int>& input, vector< vector<int> >& res)
	{
		if (numset.empty())
		{
			res.push_back(input);
			return;
		}
		multiset<int>::iterator iter = numset.begin();
		multiset<int> tmpset(numset);
		while(iter!=numset.end())
		{
			int num = *iter;
			input.push_back(num);
			multiset<int>::iterator tmpiter = tmpset.find(num);
			tmpset.erase(num);
			permute(tmpset,input,res);
			input.pop_back();
			tmpset.insert(num);
			iter++;
		}
	}
	// Given an array of non-negative integers, you are initially positioned at the first index of the array.
	//Each element in the array represents your maximum jump length at that position.
	//	Your goal is to reach the last index in the minimum number of jumps.
	//	For example:
	//Given array A = [2,3,1,1,4]
	//The minimum number of jumps to reach the last index is 2. (Jump 1 step from index 0 to 1, then 3 steps to the last index.)
	int jump(int A[], int n) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function

		if (A==NULL || n==0 || n==1)
		{
			return 0;
		}
		
		int begidx = 0;
		int idx = 0;
		int curmaxjump = 0+A[0];
		int nextmaxjump;
		int jmp = 1;
		while (curmaxjump<n-1)
		{
			nextmaxjump = curmaxjump;
			for (idx = begidx+1; idx<=curmaxjump;idx++)
			{
				if (idx+A[idx]>=nextmaxjump)
				{
					nextmaxjump = idx+A[idx];
				}
			}

			begidx = idx-1;
			curmaxjump = nextmaxjump!=curmaxjump ? nextmaxjump : curmaxjump+A[curmaxjump];
			jmp++;
		}

		return jmp;


		//利用动态规划的思想  消耗内存太大
		int** step = new int*[n];
		for (int i=0; i<n; i++)
		{
			step[i] = new int [n];
			memset(step[i],0,n*sizeof(int));
		}

		for (int i = 1; i<n; i++)
		{

			for (int j=0; i+j<n; j++)
			{
				if (A[j]>=i)	//如果可以一步
				{
					step[j][j+i] = 1;
				}
				else
				{
					int val = INT_MAX;
					int num = A[j];
					for (int m=1; m<i && m<=num; m++)
					{
						if (step[j+m][j+i]<val)
						{
							val = step[j+m][j+i];
						}
					}
					if (val==INT_MAX)
					{
						step[j][j+i] = INT_MAX;
					}
					else
						step[j][j+i] = val+1;
				}
			}
		}
		
		return step[0][n-1];



		//无法通过大集合
		return jump(A,0,n-1);
	}

	int jump(int a[], int beg, int end)
	{
		if (beg==end)
		{
			return 0;
		}
		if (a[beg]==0)
		{
			return INT_MAX;
		}
		if (beg+a[beg]>=end)
		{
			return 1;
		}
		
		int minval = INT_MAX;
		for (int i = 1; i<=a[beg]; i++)
		{
			int cnt = jump(a,beg+i,end);
			if (cnt<minval)
			{
				minval = cnt;
			}
		}
		if(minval==INT_MAX)	return INT_MAX;
		return minval+1;
	}

	//通配符匹配
	// *--任意字符串  ？--单个字符

	vector<string> getpattens(const char* p)
	{
		vector<string >	patten;
		string s;
		while (true)
		{
			if (*p=='*' || *p=='\0')
			{
				if (!s.empty())
				{
					patten.push_back(s);
					s = "";
				}
				if (*p=='\0')
				{
					break;
				}
			}
			else
			{
				s.push_back(*p);
			}
			p++;
		}
		return patten;
	}

	int matchstr(const char*s,const string& pat, int beg, int limit)
	{
		for (; beg<=limit; beg++)
		{
			for (int j=0; j<pat.size(); j++)
			{
				if (pat[j]!='?' && pat[j]!=s[beg+j])
				{
					break;
				}
				//全部匹配成功
				if (j == pat.size()-1)
				{
					return beg;
				}
			}
		}
		return -1;
	
	}
	bool isMatch(const char *s, const char *p) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
		
		//利用贪心算法
		if (s==NULL || p==NULL)
		{
			return false;
		}
		vector<string> patterns = getpattens(p);
		if (patterns.empty())
		{
			if (*p=='*')
			{
				return true;
			}
			else
				return *s=='\0';
		}

		// match each patten one by one on s
		int slen = strlen(s);
		int plen = strlen(p);

		int sb = 0;
		bool restrictfront = *p!='*';
		bool restricttail = *(p+plen-1)!='*';
		for (int pi = 0; pi<patterns.size(); pi++)
		{
			string str = patterns[pi];
			int sblimit = slen - str.size();
			if (sblimit < sb)
			{
				return false;
			}

			if (pi==0 && restrictfront)
			{
				sblimit = 0;
			}
			else if (pi == patterns.size()-1 && restricttail)
			{
				sb = slen-str.size();
				sblimit = sb;
			}

			int matchbase = matchstr(s,str,sb,sblimit);
			if (-1 == matchbase)
			{
				return false;
			}
			else
			{
				sb = matchbase+str.size();
			}
		}

		if (patterns.size()==1)
		{
			if (restrictfront && restricttail)
			{
				return s[sb]=='\0';
			}
		}
		return true;

		//无法过大数据
		//if (*s=='\0' && *p=='\0')
		//{
		//	return true;
		//}

		////如果不是通配符
		//if (*p!='*')
		//{
		//	if (*p=='?')
		//	{
		//		return *s=='\0' ? false : isMatch(s+1,p+1);
		//	}
		//	else
		//	{
		//		if (*p=='\0' && *s !='\0')
		//		{
		//			return false;
		//		}
		//		return *p==*s ? isMatch(s+1,p+1) : false;
		//	}
		//}

		//// 通配符
		//int num = 0;
		//while (1)
		//{
		//	//找到下一个不为‘*’的位置
		//	p = p+1;
		//	while (*(p)=='*')
		//	{
		//		p = p+1;
		//	}
		//	if (isMatch(s+num, p))
		//	{
		//		return true;
		//	}
		//	if (*(s+num)=='\0')
		//	{
		//		break;
		//	}
		//	num++;
		//}
		//return  false;


    }

	


	//两个很大的数相乘
	string multiply(string num1, string num2) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		int sz1 = num1.size();
		int sz2 = num2.size();
		int sz = min(sz1,sz2);
		string small, large;
		small = sz==sz1?num1:num2;
		large = sz==sz1?num2:num1;
		string res;
		for (int i=0; i<sz; i++)
		{
			int digit = small[i]-'0';
			string str = multiply(large,digit);
			res.push_back('0');
			res = plus(res,str);
		}
		return res;
	}

	string multiply(string num1, int digit)
	{
		if (digit==0)
		{
			return "";
		}
		if (digit == 1)
		{
			return num1;
		}
		size_t sz = num1.size();
		string str(sz,'0');
		int add = 0;
		for (int i=num1.size()-1; i>=0; i--)
		{
			int mul = num1[i]-'0';
			int res = mul*digit+add;
			add = res/10;
			str[i] = res%10+'0';
		}
		if (add>0)
		{
			char c[10];
			memset(c,0,10*sizeof(char));
			sprintf(c,"%d",add);
			str = c+str;
		}
		return str;
	}

	string plus(string num1,string num2)
	{
		int sz1 = num1.size();
		int sz2 = num2.size();
		string small, large,small2,left;
		if (sz1<sz2)
		{
			small = num1;
			large = num2;
			small2 = large.substr(sz2-sz1);
			left = large.substr(0,sz2-sz1);
		}
		else
		{
			small = num2;
			large = num1;
			small2 = large.substr(sz1-sz2);
			left = large.substr(0,sz1-sz2);
		}
		string str1(small),str2(left);
		int sz = small.size();
		int n1,n2,sum,add=0;
		for (int i=sz-1; i>=0; i--)
		{
			n1 = small[i]-'0';
			n2 = small2[i]-'0';
			sum = n1+n2+add;
			str1[i] = sum%10 + '0';
			add = sum/10;
		}
		if (add==0)
		{
			return str2+str1;
		}
		
		int size = left.size();
		for (int i= size-1; i>=0; i--)
		{
			n1 = left[i]-'0';
			sum = n1+add;
			str2[i] = sum%10+'0';
			add =sum/10;
			if (add==0)
			{
				break;
			}
		}
		if (add==0)
		{
			return str2+str1;
		}

		char c[10];
		sprintf(c,"%d",add);
		string str = c+str2+str1;
		return str;
		
	}

	//计算坐标系中的空间，放水的空间大小
	int trap(int A[], int n) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		
		int left,right;
		left = 0;
		while (A[left]==0)
		{
			left++;
		}

		int area = 0;

		while(left<n-1)
		{
			int i = left+1;
			right = i;
			//往右查找 大于或等于left的值
			while (i<n && A[i]<A[left])
			{
				i++;
			}
			if (i==n)
			{
			//往右查找 查找第二大的值
				int j = left+1;
				
				int high = 0;
				while(j<n )
				{
					if (A[j]>=high)
					{
						right = j;
						high = A[j];
					}
					j++;
				}				
			}
			else
			{
				right = i;
			}
			int sum = accumulate(A+left+1,A+right,0);
			area += min(A[left],A[right])*(right-left-1) - sum;
			left = right;

		}

		return area;


	}
	//复杂度o（n） 空间o(1)
	int firstMissingPositive(int A[], int n) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		for (int i=0; i!=n; i++)
		{
			if (A[i]<=0)
			{
				A[i] = n+2;
			}
		}

		for (int i=0; i!=n; i++)
		{
			int num = abs(A[i]);
			if (num>0 && num<=n)
			{
				if (A[num-1]>0)
					A[num-1] = -A[num-1];
			}	
		}
		int cnt = -1;
		for (int i=0; i!=n; i++)
		{
			if (A[i]>0)
			{
				cnt = i+1;
				break;
			}
			
		}
		if (cnt==-1)
		{
			cnt = n+1;
		}
		return cnt;
	}
	//只能有一个数出现
	vector<vector<int> > combinationSum2(vector<int> &num, int target) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		sort(num.begin(),num.end());
		vector<vector<int> >result;
		vector<int> input;
		if (num.empty())
		{
			return result;
		}
		if (num[0]>target)
		{
			return result;
		}
		combinationSum2(input,num,target,result);
		return result;
	}

	void combinationSum2(vector<int>& input, vector<int>& candidates, int target, vector<vector<int> >&res)
	{
		for (int i=0; i< candidates.size(); i++)
		{
			if (i>0 && candidates[i]==candidates[i-1])
			{
				continue;
			}
			
			int num = candidates[i];
			if (target==num)
			{
				input.push_back(num);
				res.push_back(input);
				input.pop_back();
				return;
			}
			else if (target > num)
			{
				input.push_back(num);
				vector<int> tmp(candidates.begin()+i+1,candidates.end());
				combinationSum2(input,tmp,target-num,res);
				input.pop_back();
			}
			else
				return;
		}
		
		
	}
	//用数组中的数进行复制组合成target
	vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		
		vector<vector<int>  > result;
		if (candidates.empty())
		{
			return result;
		}
		sort(candidates.begin(),candidates.end());
		vector<int> input;
		combinationSum(input,candidates,target,result);
		return result;

	}

	void combinationSum(vector<int>& input, vector<int>& candidates, int target,vector<vector<int>  >&res)
	{

		for (int i=0; i<candidates.size(); i++)
		{
			input.push_back(candidates[i]);
			int sum = 0;
			sum =accumulate(input.begin(), input.end(),0);
			if (sum==target)
			{
				res.push_back(input);
				input.pop_back();
				continue;
			}
			else if(sum>target)
			{
				input.pop_back();
				return;
			}
			else
			{
				vector<int>	origin(candidates.begin()+i,candidates.end());
				combinationSum(input,origin,target,res);
				input.pop_back();
			}
			
			
		}
		

	}


	//数数
	//1, 11, 21, 1211, 111221, ...
	string countAndSay(int n) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		if (n==1)
		{
			return "1";
		}
		string str = countAndSay(n-1);
		string res="";
		size_t i=0;
		char num[100];
		while (i<str.size())
		{
			
			int j=i+1;
			while (j<str.size() && str[i]==str[j])
			{
				j++;
			}
			int cnt = j-i;
			memset(num,0,100*sizeof(char));
			res = res+itoa(cnt,num,10);
			res.push_back(str[i]);
			i = j;
		}
		return res;
	}

	
	
	//解决数独问题
	void solveSudoku(vector<vector<char> > &board) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		//buid usable array
		set<int> defset;
		for (int i=1; i!=10; i++)
		{
			defset.insert(i);
		}
		const int n= 9;
		int sz = board.size();
		if (sz!=n)
		{
			return;
		}

		vector<set<int> >rowusable(n,defset),colusable(n,defset),ceilusable(n,defset);	//每一列，每一行，每一个小格可以使用的数字
		vector<int>	numrow(n,n),numcol(n,n),numceil(n,n);	//每一行，每一列，每个小格有多少不确定数
		int certain[n][n];	//不确定数的选择
		set<int>	unvisit;	//没有确定的位置
		memset(certain,0,sizeof(char)*n*n);	
		for (int i=0; i!=board.size(); i++)
		{
			int row = i/3;
			vector<char> str = board[i];
			for (int j=0; j!=str.size(); j++)
			{
				int col = j/3;
				if (str[j]=='.')
				{
					certain[i][j]=10;
					int ind = i*10+j;
					unvisit.insert(ind);
					continue;
				}
				int ind = str[j]-'0';
				certain[i][j]=ind;
				rowusable[i].erase(ind);	
				colusable[j].erase(ind);
				int ceilind = row*3+col;
				ceilusable[ceilind].erase(ind);
				numrow[i]--;
				numcol[j]--;
				numceil[ceilind]--;
			}
		}

		suduVisit(board,unvisit,rowusable,colusable,ceilusable);
		


	}

	bool suduVisit(vector<vector<char> > &board, set<int>& unvisit, vector<set<int> >& rowuse, vector<set<int> >& coluse, vector<set<int> >&ceiluse)
	{
		if (unvisit.empty())
		{
			return true;
		}
		
		int ind = *unvisit.begin();
		unvisit.erase(ind);

		int m,n,c;
		m = ind/10;
		n = ind%10;
		c = m/3*3+n/3;
		set<int> tmp,use;
		set_intersection(rowuse[m].begin(),rowuse[m].end(),coluse[n].begin(),coluse[n].end(),inserter(tmp,tmp.begin()));
		set_intersection(tmp.begin(),tmp.end(),ceiluse[c].begin(),ceiluse[c].end(),inserter(use,use.begin()));
	
		if (use.empty())
		{
			unvisit.insert(ind);
			return false;
		}
		
		set<int>::iterator iter = use.begin();
		
		
		while (iter!=use.end())
		{
			int num = *iter;
			bool flagrow,flagcol,flagceil;
			flagrow = flagcol = flagceil = false;
			if (rowuse[m].count(num))
			{
				flagrow = true;
			}
			if (coluse[n].count(num))
			{
				flagcol = true;
			}
			if (ceiluse[c].count(num))
			{
				flagceil = true;
			}
						
			
			rowuse[m].erase(num);
			coluse[n].erase(num);
			ceiluse[c].erase(num);
			board[m][n]=num+'0';

				//如果下一个所有尝试都失败
				if(!suduVisit(board,unvisit,rowuse,coluse,ceiluse))
				{
					board[m][n] = '.';
					if (flagrow)
					{
						rowuse[m].insert(num);
					}
					if (flagcol)
					{
						coluse[n].insert(num);
					}
					if (flagceil)
					{
						ceiluse[c].insert(num);
					}		
					iter++;
				}
				else
					return true;	
		}
		//如果所有都没有正确的话
		unvisit.insert(ind);
		return false;

	}

	



	//数独是否有效
	//空位为‘.’
	bool isValidSudoku(vector<vector<char> > &board) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
		const int n = 10;
        //row identify
		for(size_t i=0; i!= board.size(); i++)
		{
			vector<char>	str = board[i];
			if (!isValidSudoku(str))
			{
				return false;
			}
		}
		//cols identify
		for (size_t i=0; i!=board[0].size(); i++)
		{
			vector<char> str;
			for (size_t j=0; j!=board.size();j++)
			{
				str.push_back(board[j][i]);
			}
			if (!isValidSudoku(str))
			{
				return false;
			}
		}

		//little cube
		for(size_t i=0; i<n/3; i++)
		{
			vector<char> str0,str1,str2;
			str0 = board[3*i+0];
			str1 = board[3*i+1];
			str2 = board[3*i+2];
			for (size_t j=0; j<n/3; j++)
			{
				vector<char> str;
				str.push_back(str0[3*j+0]);
				str.push_back(str0[3*j+1]);
				str.push_back(str0[3*j+2]);
				str.push_back(str1[3*j+0]);
				str.push_back(str1[3*j+1]);
				str.push_back(str1[3*j+2]);
				str.push_back(str2[3*j+0]);
				str.push_back(str2[3*j+1]);
				str.push_back(str2[3*j+2]);
				if (!isValidSudoku(str))
				{
					return false;
				}			
			}		
		}

		return true;
		
		

    }

	bool isValidSudoku(vector<char> &board)
	{
		size_t sz = board.size();
		const int n = 10;
		if (sz!=n-1)
		{
			return false;
		}
		char	flag[n]={0};
		for (size_t i=0; i!=sz; i++)
		{
			char c = board[i];
			if (c=='.')
			{
				continue;
			}
			int ind = c-'0';
			if (flag[ind])
			{
				return false;
			}
			else
			{
				flag[ind]=1;
			}
			
		}
		return true;
	}

	//查找target可以插入的位置
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


	//在排序数组中找到和target一样的值得位置
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
		else	//target 找到
		{
			res.push_back(m);
			searchRange(a,l,m-1,target,res);
			searchRange(a,m+1,r,target,res);
		}

	
	}
	//数组是一个递增数组，但是右移了几位，求搜索target的位置
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

	//求字典中的下一个数 
	void nextPermutation(vector<int> &num) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        //从末尾开始找到第一个 前一个值< 后一个值
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
		//若是递减序列，则下一个为最小数组
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


	//查找级联容器中的字符串在S中的位置
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
			//对字符串分串
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
		//	//判断是否全部找到
		//	if(tmp.empty())
		//	{
		//		int index = ind-sumsz;
		//		res.push_back(index);
		//	}
		//}
		//return res;
		
    }
	//除法 
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
	//KMP算法
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

	int removeElement2(int A[], int n, int elem) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		int ind=0;
		for (int i=0; i<n; i++)
		{
			if(A[i]==elem)
				continue;
			else
			{
				A[ind] = A[i];
				ind++;
			}
		}
		return ind;
	}
	//删除数组中与elem值相同的值，同时返回最后长度
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
	
	//删除重复的数据
	int removeDuplicates3(int A[], int n) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		int ind=0;
		for (int i=0; i<n; i++)
		{
			if(i>0&& A[i]==A[i-1])
				continue;
			else
			{
				A[ind] = A[i];
				ind++;
			}
		}
		return ind;
	}
	//原地删除重复数据  数组已排序
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
	//两两交换位置，不能改变数据
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
	
	//每K个节点反转，最后不足K节点的不做反转
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
			//前面N组
			if(cnt==k)
			{
				pre->next = p;
				pre = tail;
				pre->next = q;
			}
			//最后一组
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
	
	struct cmp
	{
		bool operator() (ListNode* p, ListNode* q)
		{
			return p->val>q->val;
		}
	};
	//利用优先级队列来找到最小值
	ListNode *mergeKLists2(vector<ListNode *> &lists) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		priority_queue<ListNode*,deque<ListNode*>,cmp> que;
		if (lists.empty())
		{
			return NULL;
		}
		ListNode *p,*q;
		for (int i=0; i<lists.size(); i++)
		{
			p = lists[i];
			if (p)
			{
				que.push(p);
			}
		}
		ListNode *phead = new ListNode(0);
		q = phead;
		while (!que.empty())
		{
			p = que.top();
			q->next = p;
			q = p;
			que.pop();
			if (p->next)
			{
				que.push(p->next);
			}
		}
		return phead->next;

	}
	
	//生成 n对括号的有效排列组合
	vector<string> generateParenthesis(int n) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		vector<string>	res;
		generateParenthesishelper(0,0,n,"",res);
		return res;
	}
	void generateParenthesishelper(int left, int right, int n, string str, vector<string>& res)
	{
		if (left==n && right == n)
		{
			res.push_back(str);
			return;
		}
		if (left<n)
		{
			generateParenthesishelper(left+1,right,n,str+'(',res);
		}
		if (right<left && right<n)
		{
			generateParenthesishelper(left,right+1,n,str+')',res);
		}
	}

	//括号对是否有效
	bool isValid(string s) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		stack<char>	stk;
		for (int i=0; i<s.size(); i++)
		{
			char ch = s[i];
			if (ch==')')
			{
				if (!stk.empty() && stk.top()=='(')
				{
					stk.pop();
				}
				else
					return false;
			}
			else if (ch==']')
			{
				if (!stk.empty() && stk.top()=='[')
				{
					stk.pop();
				}
				else
					return false;
			}
			else if (ch=='}')
			{
				if (!stk.empty() && stk.top()=='{')
				{
					stk.pop();
				}
				else
					return false;
			}
			else
				stk.push(ch);
		}
		return stk.empty();
	}
	//删除倒数第N个节点
	ListNode *removeNthFromEnd(ListNode *head, int n) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		ListNode* phead = new ListNode(0);
		phead->next = head;
		int ind = 0;
		ListNode *pre,*last;
		pre = last = phead;
		while (ind!=n+1 && last)
		{
			last = last->next;
			ind++;
		}
		if (ind!=n+1)
		{
			return phead->next;
		}
		while (last)
		{
			last = last->next;
			pre = pre->next;
		}
		pre->next = pre->next->next;
		return phead->next;
	}
	//手机上按键的字母组合
	vector<string> letterCombinations(string digits) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		//DP法
		vector<string>	result;
		if (digits.empty())
		{
			result.push_back("");
			return result;
		}
		letterCombinationsHelper(digits,0,result,"");
		return result;
		/*vector<string> result;
		if (digits.empty())
		{
			return result;
		}
		return letterCombinations(digits,0);*/
	}
	void letterCombinationsHelper(string digits, int ind, vector<string>& res, string str)
	{
		static char chvec[11][5] = {"","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
		static vector<string> digvec(chvec,chvec+11); 
		if (ind>=digits.size())
		{
			res.push_back(str);
			return;
		}
		int dig = digits[ind]-'0';
		string digstr = digvec[dig];
		string digstr2;
		for (int i = 0; i<digstr.size(); i++)
		{
			digstr2 = str+digstr[i];
			letterCombinationsHelper(digits,ind+1,res,digstr2);
		}
		
	}
	vector<string>	letterCombinations(string digits, int ind)
	{
		static char chvec[11][5] = {"","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
		static vector<string> digvec(chvec,chvec+11); 
		vector<string> result, strvec,strvec2 ;
		if (ind>=digits.size())
		{
			return result;
		}
		strvec = letterCombinations(digits,ind+1);
		int dig = digits[ind]-'0';
		string str = digvec[dig];
		if (dig<=1)
		{
			return strvec;
		}
		for (int i=0; i<str.size(); i++)
		{
			strvec2.push_back(string(1,str[i]));
		}
		if (strvec.empty())
		{
			return strvec2;
		}
		for (int i=0; i<strvec2.size(); i++)
		{
			string res = strvec2[i],res2;
			for (int j=0; j<strvec.size(); j++)
			{
				res2 = res+strvec[j];
				result.push_back(res2);
			}
		}
		return result;
		
	}
	//4个数之和等于target
	vector<vector<int> > fourSum(vector<int> &num, int target) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		vector<vector<int> >result;
		int len = num.size();
		if (len<4)
		{
			return result;
		}
		sort(num.begin(),num.end());
		for (int i=0; i<len-3; i++)
		{	
			if (i!=0 && num[i]==num[i-1])
			{
				continue;
			}
			for (int j=i+1; j<len-2; j++)
			{
				if (j!=i+1 && num[j]==num[j-1])
				{
					continue;
				}
				int low= j+1;
				int high = len-1;
				while (low<high)
				{
					if (low!=j+1 && num[low]==num[low-1])
					{
						low++;
						continue;
					}
					if (high!=len-1 && num[high]==num[high+1])
					{
						high--;
						continue;
					}
					int sum = num[i]+num[j]+num[low]+num[high];
					if (sum==target)
					{
						vector<int> input;
						input.push_back(num[i]);
						input.push_back(num[j]);
						input.push_back(num[low]);
						input.push_back(num[high]);
						result.push_back(input);
						low++;
						high--;
					}
					else if (sum<target)
					{
						low++;
					}
					else
						high--;
				}//end while
			}	// end for j
		}	// end for i
		return result;
	}
	//最接近目标的3个值
	int threeSumClosest(vector<int> &num, int target) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		int minDis = INT_MAX;
		if (num.size()<3)
		{
			return -1;
		}
		sort(num.begin(),num.end());
		int len = num.size();
		for (int i=0; i<len-2; i++)
		{
			if (i!=0 && num[i]==num[i-1])
			{
				continue;
			}
			int low,high;
			low = i+1;
			high = len-1;
			while (low<high)
			{
				if (low!=i+1 && num[low]==num[low-1])
				{
					low++;
					continue;
				}
				if (high!=len-1 && num[high]==num[high+1])
				{
					high--;
					continue;
				}

				int sum = num[low]+num[high]+num[i];
				
				if (abs(sum-target)<abs(minDis))
				{
					minDis = sum-target;
				}
				if (sum-target==0)
				{
					return 0;
				}
				else if (sum-target>0)
				{
					high--;
				}
				else
					low++;
			}//end while
		}// end for
		return minDis+target;
	}
	//3个数之和为0
	vector<vector<int> > threeSum(vector<int> &num) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		sort(num.begin(),num.end());
		vector<vector<int> >result;
		if(num.empty()) return result;
		for (int i=0; i+2<num.size(); i++)
		{
			if (i>0 && num[i]==num[i-1])
			{
				continue;
			}
			int low,high;
			low = i+1;
			high = num.size()-1;
			while (low<high)
			{
				if (low!=i+1 && num[low]==num[low-1])
				{
					low++;
					continue;
				}
				if (high != num.size()-1 && num[high]==num[high+1])
				{
					high--;
					continue;
				}
				int sum = num[i]+num[low]+num[high];
				if (sum==0)
				{
					vector<int>	input;
					input.push_back(num[i]);
					input.push_back(num[low]);
					input.push_back(num[high]);
					result.push_back(input);
					low++;
					high--;
				}
				else if (sum>0)
				{
					high--;
				}
				else
					low++;
			}//end while 
		}// end for
		return result;
	}
	//求最长公共前缀
	string longestCommonPrefix(vector<string> &strs) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		string result;
		if (strs.empty())
		{
			return result;
		}
		int len = strs.size();
		int sz = strs[0].size();
		bool flag = true;
		for (int i=0; i<sz ; i++)
		{
			char ch = strs[0][i];
			for (int j=1; j<len; j++)
			{
				if (strs[j].size()==i)
				{
					return result;
				}
				if (strs[j][i]==ch)
				{
					continue;
				}
				else
					return result;
			}
			result += ch;
		}
		return result;
	}
	//罗马数转整数
	int romanToInt(string s) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		char oneArray[] = {'I','X','C','M'};
		char fiveArray[] = {'V','L','D'};
		int result = 0;
		int dev = 1;
		for (int i=0; i<4; i++)
		{
			int ind = -1;
			while ((ind=s.find(oneArray[i],ind+1))!=-1)
			{
				if (i<3 && ind<s.size()-1 && (s[ind+1]==oneArray[i+1] || s[ind+1]==fiveArray[i]))
				{
					result -= 2*dev; 
				}
				result = result+dev;
			}
			if (i<3 && s.find(fiveArray[i])!=-1)
			{
				result = result+5*dev;
			}
			dev = 10*dev;
		}
		return result;
		
	}
	//十进制数转为罗马数
	string intToRoman(int num) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function    
		char oneArray[] = {'I','X','C','M'};
		char fiveArray[] = {'V','L','D'};
		if (num<1 || num>3999)
		{
			return "";
		}
		string str ;
		int digit;
		int i=0;
		while (num)
		{
			string s;
			digit = num%10;
			if (digit<4)
			{
				s.assign(digit,oneArray[i]);
				str = s+str;
			}
			else if (digit==4)
			{
				s.assign(1,oneArray[i]);
				s = s+ fiveArray[i];
				str = s+str;
			}
			else if (digit<=8)
			{
				s.assign(1,fiveArray[i]);
				s = s+ string(digit-5,oneArray[i]);
				str = s + str;
			}
			else
			{
				str = string(1,oneArray[i])+string(1,oneArray[i+1])+str;
			}
			i++;
			num = num/10;
		}
		return str;
	}
	//height表示坐标线，求能够装下的最大面积的水
	int maxArea(vector<int> &height) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		int low = 0;
		int high = height.size()-1;
		int res = 0;
		while (low<high)
		{
			int tmp = min(height[low],height[high])*(high-low);
			res = max(res,tmp);		
			if (height[low]<=height[high])
			{
				low++;
			}
			else
				high--;
		}
		return res;
	}
	//		'.' match any signle character
	//		'*'	matches zero or more of the precding element
	bool isMatch2(const char *s, const char *p) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function    
		if (*p=='\0')
			return *s=='\0';
		//假设 后一个字符不是*
		if (*(p+1)!='*')
		{
			if ((*p=='.' && *s!='\0') || *p==*s)
			{
				return isMatch(s+1,p+1);
			}
			else
				return false;
		}
		int ind = 0;
		while ((*p==*s)|| (*p=='.' && *s !='\0'))
		{
			if (isMatch(s,p+2))
			{
				return true;
			}
			s++;
		}
		return isMatch(s,p+2);


	}
	//判断是否为回文数
	bool isPalindrome(int x) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		if (x<0)
			return false;
		else if(x==0)
			return true;
		int dev = 1;
		while (x/dev>=10)
		{
			dev *= 10;
		}
		while (x!=0)
		{
			int l = x/dev;
			int r = x%10;
			if (l!=r)
			{
				return false;
			}
			x = (x%dev)/10;
			dev /= 100;
		}
		return true;
	}
	//atoi
	//无效字符串返回0
	//越过前面空格字符
	//如果超过最大值，返回INT_MAX, INT_MIN
	int atoi(const char *str) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		if (*str=='\0')
		{
			return 0;
		}
		const char* p = str;
		bool flag = true;
		while(*p==' ')	p++;
		if (*p=='-')
		{
			flag = false;
			p++;
		}
		else if (*p=='+')
		{
			flag =true;
			p++;
		}
		long long num=0;
		while (isdigit(*p))
		{
			num = num*10 + *p-'0';
			if (num>(long long)INT_MAX+1)
			{
				break;
			}
			p++;
		}
		if (flag && num>INT_MAX)
		{
			return INT_MAX;
		}
		else if (!flag && num>(long long)INT_MAX+1)
		{
			return INT_MIN;
		}

		num = flag ? num : -1*num;
		return num;

	}
	int reverse(int x) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		int abx = abs(x);
		bool flag = x<0;
		long ret=0;
		int digit;
		while (abx)
		{
			digit = abx%10;
			ret = ret*10+digit;
			abx = abx/10;
		}
		if (flag)
			ret = -1*ret;
		return ret;
	}
	//蛇形访问字符串，同时按行访问字符串
	string convert(string s, int nRows) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function    
		if (nRows<=1)
		{
			return s;
		}
		int len = 2*nRows-2;
		vector<vector<char> >chvec(nRows);
		for (int i=0; i<s.size();i++)
		{
			char ch = s[i];
			int ind = i%len;
			if (ind<nRows)
			{
				chvec[ind].push_back(ch);
			}
			else
			{
				int num = 2*(nRows-1)-ind;
				chvec[num].push_back(ch);
			}
		}
		string ret;
		string str;
		for (int i=0; i<nRows; i++)
		{
			str.assign(chvec[i].begin(),chvec[i].end());
			ret+=str;
		}
		return ret;
	}
	//最长的回文子串
	//首先对字符串插入#，使所有回文字符串的长度变为奇数
	string longestPalindrome(string s) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		if (s.empty())
		{
			return "";
		}
		string T = longestPalindromeHelper(s);
		int n = T.size();
		vector<int> p(n,0);
		int rmax = 0;
		int center = 0;
		int maxlen = 0;
		int maxind=0;
		for (int i=1; i<n-1; i++)
		{
			int i_mirror = 2*center-i;
			p[i] = (rmax>i) ? min(rmax-i,p[i_mirror]) : 0;
			while (T[i+1+p[i]]==T[i-1-p[i]])
			{
				p[i]++;
			}
			if (i+p[i]>rmax)
			{
				rmax = i+p[i];
				center = i;
			}
			if (p[i]>maxlen)
			{
				maxlen = p[i];
				maxind = i;
			}
		}
		string ret = s.substr((maxind-maxlen-1)/2,maxlen);
		return ret;
	}
	string longestPalindromeHelper(string s)
	{
		int n = s.size();
		if (n==0)
			return "$&";
		string ret = "$";
		for (int i=0; i<n; i++)
		{
			ret += "#";
			ret += s[i];
		}
		ret += "#&";
		return ret;
	}
	//每个链表代表一个数，链表从头到尾代表数的低位到高位
	ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		ListNode* phead = new ListNode(0);
		ListNode *p1,*p2,*p;
		p1 = l1;
		p2 = l2;
		p = phead;
		int addval = 0;
		int sum = 0;
		while (p1 && p2)
		{
			sum = p1->val+p2->val+addval;
			addval = sum/10;
			p1->val = sum%10;
			p->next = p1;
			p = p1;
			p1 = p1->next;
			p2 = p2->next;
		}
		p1 = p1?p1:p2;
		p->next = p1;
		while (addval && p1)
		{
			sum = p1->val+addval;
			p1->val = sum%10;
			p->next = p1;
			p = p1;
			p1 = p1->next;
			addval = sum/10;
		}
		if (addval!=0)
		{
			p2 = new ListNode(addval);
			p->next = p2;
		}
		return phead->next;
	}
	//查找最长的无重复的子字符串
	//利用一个256的表格来查找 即O(1)的空间消耗
	int lengthOfLongestSubstring(string s) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		int start =0;
		int maxlen = 0;
		vector<bool>	flag(256,false);
		char ch;
		int len;
		for (int i=0; i<s.size();i++)
		{
			ch = s[i];
			if (!flag[ch])
			{
				flag[ch]=true;
			}
			else
			{
				len = i-start;
				maxlen = max(maxlen,len);
				while (s[start]!=ch)
				{
					flag[s[start]]=false;
					start++;
				}
				start++;
			}
		}
		len = s.size()-start;
		maxlen = max(maxlen,len);
		return maxlen;
	}		

	//找到两个排序数组的中间值
	//可以利用Kth值来查找
	double findMedianSortedArrays(int A[], int m, int B[], int n) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		int total = m+n;
		if (0==total%2)
		{
			return (findKthSortedArrays(A,m,B,n,total/2)+findKthSortedArrays(A,m,B,n,total/2+1))/2;
		}
		else
			return findKthSortedArrays(A,m,B,n,total/2+1);
	}
	double findKthSortedArrays(int a[],int m, int b[],int n, int k)
	{
		if (m>n)
			return findKthSortedArrays(b,n,a,m,k);
		if (m==0)
			return b[k-1];
		if(n==0)
			return a[k-1];
		if (k==1)
			return min(a[0],b[0]);

		int amid = min(k/2,m);
		int bmid = k-amid;
		if (a[amid-1]<=b[bmid-1])
		{
			return findKthSortedArrays(a+amid,m-amid,b,bmid,k-amid);
		}
		else
			return findKthSortedArrays(a,amid,b+bmid,n-bmid,k-bmid);
	}	

	//两个数之和为target，每个数组中有一对数之和为target
	vector<int> twoSum(vector<int> &numbers, int target) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		//利用map的方式来解决这个问题，但是需要重新开辟O(N)的空间
		//如果不开辟空间，需要使用O(N^2)的时间复杂度
		multimap<int,int>	num_map;
		vector<int>	result;
		for (int i=0; i<numbers.size();i++)
		{
			num_map.insert(make_pair(numbers[i],i));
		}
		multimap<int,int>::iterator iter,iter2;
		int num,ind,num2,ind2;
		for (iter = num_map.begin(); iter!=num_map.end();iter++)
		{
			 num = iter->first;
			 ind = iter->second;
			 num2 = target-num;
			 iter2 = num_map.find(num2);
			 if (iter2!=num_map.end())
			 {
				 if (iter==iter2)
				 {
					 iter2++;
					 if (iter2->first == iter->first)
					 {
						 ind2 = iter2->second;
						 break;
					 }
					 else
						 continue;
				 }
				 else
				 {
					 ind2 = iter2->second;
					 break;
				 }

			 }
			
		}
		result.push_back(min(ind,ind2));
		result.push_back(max(ind,ind2));
		return result;
	}

};

int _tmain(int argc, _TCHAR* argv[])
{
	/*string str[9] = {"..9748...","7........",".2.1.9...","..7...24.",".64.1.59.",".98...3..","...8.3.2.","........6","...2759.."};
	vector<vector<char> > input;
	for (int i=0; i!=9; i++)
	{
		vector<char> vec(str[i].begin(),str[i].end());
		input.push_back(vec);
	}
	*/
	int aval = 1;
	double d = -.7e4;
	Solution s;
	TreeLinkNode* p = new TreeLinkNode(1), *q = new TreeLinkNode(2), *r = new TreeLinkNode(3);

	p->right = q;
	q->left = r;
	int  a[] = {0,1};
	vector<int> invec(a,a+1);
	s.generateParenthesis(3);
	s.letterCombinations("23");
	s.threeSum(invec);
	s.romanToInt("IX");
	s.intToRoman(94);
	s.maxArea(invec);
	//s.connect(p);
	//s.isPalindrome(1001);
	//s.atoi("2147483647");
	//s.reverse(-100);
	//s.convert("PAYPALISHIRING",3);
	////p->left = q;
	////s.numDistinct("ccc","c");
	////s.flatten(p);
	////s.hasPathSum(p,1);
	//s.longestPalindrome("ccd");
	//s.lengthOfLongestSubstring("abcddcbae");
	//s.minCut("efe");

	//int A[100]={4};
	//int b[]={1,2,3,5,6};
	//char* strg[] ={"ted","tex","red","tax","tad","den","rex","pee"};
	//unordered_set<string> dict;
	//for (int i=0; i<8;i++)
	//{
	//	dict.insert(strg[i]);
	//}
	////set<string> dict(strg,strg+8);

	//s.findLadders("red","tex",dict);
	//s.isValidBST(NULL);
	//s.isInterleave("bcbccabcccbcbbbcbbacaaccccacbaccabaccbabccbabcaabbbccbbbaa","ccbccaaccabacaabccaaccbabcbbaacacaccaacbacbbccccbac",\
	//	"bccbcccabbccaccaccacbacbacbabbcbccbaaccbbaacbcbaacbacbaccaaccabcaccacaacbacbacccbbabcccccbababcaabcbbcccbbbaa");
	//s.generateTrees(2);
	//s.restoreIpAddresses("0000");
	//int res =  s.numDecodings("27");
	//vector<int> height(A,A+2);
	//s.grayCode(2);
	//s.largestRectangleArea(height);
	//s.combine(4,2);
	//s.minWindow("bba","ab");
	//s.sortColors(A,3);
	//int minval =  s.minDistance("abcd","bcda");
	//s.simplifyPath("/a/./b/../../c/");
	//string str[] = {"This", "is", "an", "example", "of", "text", "justification."};
	//vector<string> strvec(1,"");
	//s.fullJustify(strvec,16);
	return 0;
}

