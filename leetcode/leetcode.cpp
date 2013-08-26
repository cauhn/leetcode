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
#include <list>
#include <algorithm>
#include <numeric>

using namespace std;


struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

 struct Interval {
	     int start;
	    int end;
		Interval() : start(0), end(0) {}
	    Interval(int s, int e) : start(s), end(e) {}
 };

class Solution {
public:
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
		int minval = abs((int)word1.size()-(int)word2.size()) + max(word2.size(),word1.size());
		list<char> chvec(word1.begin(),word1.end());
		minDistance(0,minval,chvec,word2);
		return minval;
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
	double d = -.7e4;
	Solution s;
	int A[]={2,1,0};
	s.sortColors(A,3);
	int minval =  s.minDistance("abcd","bcda");
	s.simplifyPath("/a/./b/../../c/");
	string str[] = {"This", "is", "an", "example", "of", "text", "justification."};
	vector<string> strvec(1,"");
	s.fullJustify(strvec,16);
	return 0;
}

