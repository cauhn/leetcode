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
#include <algorithm>
#include <numeric>

using namespace std;


struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
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
	//两两交换指针，不能改变数据
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
	/*string str[9] = {"..9748...","7........",".2.1.9...","..7...24.",".64.1.59.",".98...3..","...8.3.2.","........6","...2759.."};
	vector<vector<char> > input;
	for (int i=0; i!=9; i++)
	{
		vector<char> vec(str[i].begin(),str[i].end());
		input.push_back(vec);
	}
	*/
	Solution s;
	int arr[]={-2, 1, -3, 4, -1, 2, 1, -5, 4};
	int res = s.maxSubArray(arr,9);
	s.solveNQueens(8);

	return 0;
}

