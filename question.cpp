#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    //  724. Find Pivot Index
    //  https://leetcode.com/problems/find-pivot-index/
    int pivotIndex(vector<int>& nums) {
        int ls = 0, rs = 0;
        for (int u: nums) rs += u;

        for (int i; i < nums.size(); i++) {
            rs -= nums[i];
            if (ls == rs) return i;
            ls += nums[i];
        } 
        return -1;  
    }

    // 747. Largest Number At Least Twice of Others
    // https://leetcode.com/problems/largest-number-at-least-twice-of-others/
    int dominantIndex(vector<int>& nums) {
        int *fl, *sl; // Init largest number and second largest number
        int size = nums.size(); 
        if (size == 0) return -1;
        if (size == 1) return 0;
        if (nums[0] > nums[1]) {
            fl = &nums[0];
            sl = &nums[1];
        }
        else {
            fl = &nums[1];
            sl = &nums[0];
        }
        for (int i = 2; i < size; i++) {
            if (nums[i] > *sl) sl = &nums[i];
            if (*sl > *fl) {
                int *tmp = fl;
                fl = sl; 
                sl = tmp;
            }
        }
        if (*fl >= 2 * *sl) {
            return fl - &nums[0];
        }
        return -1;
    }

    // 66. Plus One
    // https://leetcode.com/problems/plus-one/
    vector<int> plusOne(vector<int>& digits) {
        int tmp = digits.back();
        digits.pop_back();
        vector<int> out;
        out.push_back((tmp + 1) % 10);
        int carry = (tmp + 1) / 10;
        while (!digits.empty())
        {
            tmp = digits.back();
            out.insert(out.begin(), (tmp + carry) % 10);
            carry = (tmp + carry) / 10;
            digits.pop_back();
        }
        if (carry > 0) {
            out.insert(out.begin(), carry);
        }
        return out;
    }

    // 498. Diagonal Traverse
    // https://leetcode.com/problems/diagonal-traverse/
    vector<int> findDiagonalOrder(vector<vector<int>>& matrix) {
        vector<int> out;

        int M = matrix.size();
        if (M == 0) return out;
        int N = matrix[0].size();
        if (N == 0) return out;

        out.resize(M * N);
        int total = M + N - 1;
        int min = std::min(M, N);
        int max = std::max(M, N);
        int start = 0;
        int cur;

        for (int i = 0; i < total; i++) {
            if (i < min) cur = i + 1;
            else if (i < max) cur = min;
            else cur = min - i + max - 1;

            if (i % 2 == 0) {
                int x = i >= M ? (M - 1) : i;
                int y = i >= M ? (i - M + 1) : 0;
                for (int j = 0; j < cur; j++) {
                    out[start+j] = matrix[x--][y++];
                }
            }
            else {
                int x = i >= N ? (i - N + 1) : 0;
                int y = i >= N ? (N - 1) : i;
                for (int j = 0; j < cur; j++) {
                    out[start+j] = matrix[x++][y--];
                }
            }
            start += cur;
        }
        return out;
    }

    // 54. Spiral Matrix
    // https://leetcode.com/problems/spiral-matrix/
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> out;
        
        int M = matrix.size();
        if (M == 0) return out;
        int N = matrix[0].size();
        if (N == 0) return out;

        int count = M * N;
        int inside = 0;
        if (M > 2 && N > 2) inside = (M - 2) * (N - 2);
        
        vector<int> visited(count, 0);     
        int x = 0;
        int y = 0;

        while (count > 0)
        {
            out.push_back(matrix[x][y]);
            visited[x * N + y] = 1;
            count--;
            if (count == inside) break;
            if (x == 0 && y < N - 1) y++;
            else if (y == N - 1 && x < M - 1) x++;
            else if (x == M - 1 && y > 0) y--;
            else if (y == 0 && x > 1) x--;
        }
        
        while (count > 0)
        {
            if (visited[x * N + y + 1] == 0 && visited[(x - 1) * N + y + 1] == 1) y++;
            else if (visited[(x + 1) * N + y] == 0 && visited[(x + 1) * N + y + 1] == 1) x++;
            else if (x < M - 1 && visited[x * N + y - 1] == 0 && visited[(x + 1) * N + y - 1] == 1) y--;
            else if (visited[(x - 1) * N + y] == 0 && visited[(x - 1) * N + y - 1] == 1) x--;
            out.push_back(matrix[x][y]);
            visited[x * N + y] = 1;
            count--;
        }
        return out;
    }

    // 118. Pascal's Triangle
    // https://leetcode.com/problems/pascals-triangle/
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> out;
        int curn = 1;
        while(numRows > 0) {
            vector<int> cur(curn, 1);
            for(int i = 1; i < curn - 1; i++) {
                cur[i] = out[curn - 2][i-1] + out[curn - 2][i];
            }
            out.push_back(cur);
            curn++;
            numRows--;
        }
        return out;
    }

    // 67. Add Binary
    // https://leetcode.com/problems/add-binary/
    string addBinary(string a, string b) {
        string out;
        int cur = 0, la = a.length() - 1, lb = b.length() - 1;
        while (la >= 0 || lb >= 0 || cur > 0) {
            if (la >= 0) {
                cur += a[la--] - '0';
            }
            if (lb >= 0) {
                cur += b[lb--] - '0';
            }
            out += (cur % 2) + '0';
            cur /= 2;
        }
        reverse(out.begin(), out.end());
        return out; 
    }

    // 28. Implement strStr()
    // https://leetcode.com/problems/implement-strstr/
    int strStr(string haystack, string needle) {
        int lh = haystack.size(), ln = needle.size(), out = -1;
        if (ln == 0) return 0;
        if (lh == 0) return -1;
        if (ln > lh) return -1;
        for (int i = 0; i <= lh - ln; i++) {
            if (haystack[i] == needle[0]) {
                for (int j = 0; j < ln; j++) {
                    if (haystack[i+j] != needle[j]) break;
                    if (j == ln - 1) out = i;
                }
            }
            if (out >= 0) break;
        }
        return out;
    }

    // 14. Longest Common Prefix
    // https://leetcode.com/problems/longest-common-prefix/
    string longestCommonPrefix(vector<string>& strs) {
         string result = "";
         int count = strs.size();
         if (count == 0) return "";
         int minlen = strs[0].size();
         for (int i = 1; i < count; i++) {
             if (strs[i].size() < minlen) minlen = strs[i].size();
         }
         char cur;
         bool diff = false;
         for (int j = 0; j < minlen; j++) {
             cur = strs[0][j];
             for (int i = 1; i < count; i++) {
                 if (cur != strs[i][j]) {
                     diff = true;
                     break;
                 }
             }
             if (diff == false) {
                 result += cur;
             }
             else break;
         }
         return result;
    }

    // 344. Reverse String
    // https://leetcode.com/problems/reverse-string/
    void reverseString(vector<char>& s) {
        char tmp;
        int max = s.size() - 1;
        for (int i = 0; i < (s.size() / 2); i++) {
            tmp = s[i];
            s[i] = s[max - i];
            s[max - i] = tmp;
        }
    }

    // 561. Array Partition I
    // https://leetcode.com/problems/array-partition-i/
    int arrayPairSum(vector<int>& nums) {
        int count = nums.size(), result = 0;
        vector<int> record(20001, 0);
        for (int i =0; i < count; i++) {
            ++record[nums[i]+10000];
        }
        bool flag = true;
        int cur = 0;
        while (count > 0) {
            if (record[cur] == 0) ++cur;
            else {
                if (flag) {
                    result += (cur - 10000);
                    flag = false;
                }
                else flag = true;
                --record[cur];
                --count;
            }
        }
        return result;
    }

    // 167. Two Sum II - Input array is sorted
    // https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/
    vector<int> twoSum(vector<int>& numbers, int target) {
        vector<int> result;
        int i = 0, j = numbers.size() - 1;
        while (numbers[i] + numbers[j] != target) {
            if (numbers[j] > target) j--;
            else if (numbers[i] + numbers[j] > target) j--;
            else i++;
        }
        result.push_back(i+1);
        result.push_back(j+1);
        return result;
    }

    // 27. Remove Element
    // https://leetcode.com/problems/remove-element/
    int removeElement(vector<int>& nums, int val) {
        int k = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != val) {
                nums[k++] = nums[i];
            }
        }
        return k;
    }

    // 485. Max Consecutive Ones
    // https://leetcode.com/problems/max-consecutive-ones/
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int output = 0;
        int k = -1;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == 0) {
                output = output > (i - k - 1)? output: (i - k - 1);
                k = i;
            }
        }
        if (k != nums.size() - 1) output = output > (nums.size() - k - 1)? output: nums.size() - k - 1;
        return output;
    }

    // 209. Minimum Size Subarray Sum
    // https://leetcode.com/problems/minimum-size-subarray-sum/
    int minSubArrayLen(int s, vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        int result = 0, cur_sum = 0, k = -1;
        for (int i = 0; i < n; i++) {
            cur_sum += nums[i];
            while (cur_sum >= s) {
                result = result > i - k || result == 0 ? i - k : result;
                cur_sum -= nums[++k];
            }
        }
        return result;
        /* Slower Solving.
        if (nums.size() == 0) return 0;
        for (int i = 0; i < nums.size(); i++) {
            cur_sum += nums[i];
            if (cur_sum >= s) {
                while (cur_sum >= s) {
                    result = result > i - k || result == 0 ? i - k : result;
                    cur_sum -= nums[++k];
                }
            }
            else if (result > 0 && result <= i - k) cur_sum -= nums[++k];
        } */
    }

    // 189. Rotate Array
    // https://leetcode.com/problems/rotate-array/
    void rotate(vector<int>& nums, int k) {
        int N = nums.size(), n = nums.size(), start = 0, mingap = k;
        k %= n;
        if (k == 0) return;
        while (true) {
            mingap = min(start + k, N);
            for (int i = start; i < mingap; i++) {
                swap(nums[i], nums[n - k + i]);
            }
            n -= k;
            start += k;
            k %= n;
            if (k == 0) break; 
        }
    }

    // 119. Pascal's Triangle II
    // https://leetcode.com/problems/pascals-triangle-ii/
    vector<int> getRow(int rowIndex) {
        vector<int> result(rowIndex+1, 0);
        result[0] = 1;
        for (int i = 1; i <= rowIndex; i++) {
            for (int j = i; j > 0; j--) {
                result[j] += result[j-1];
            }
        }
        return result;
    }

    // 151. Reverse Words in a String
    // https://leetcode.com/problems/reverse-words-in-a-string/
    string reverseWords(string s) {
        string result = "";
        int k = s.size();
        bool flag = false;
        for (int i = k - 1; i >= 0; i--) {
             if (!(s[i] - ' ')) {
                 if (flag) {
                     result.append(s.begin() + i + 1, s.begin() + k);
                     result.push_back(' ');
                     flag = false;
                 }
                 k = i;
             }
            else flag = true;
        }
        if (k > 0) result.append(s.begin(), s.begin() + k);
        else if (result.size() > 0) result.pop_back();
        return result;
    }

    // 557. Reverse Words in a String III
    // https://leetcode.com/problems/reverse-words-in-a-string-iii/
    string reverseWordsIII(string s) {
        string result = "", tmp;
        int k = -1, n = s.size();
        bool flag = false;
        for (int i = 0; i < n; i++) {
            if (!(s[i] - ' ')) {
                if (flag) {
                    tmp.assign(s.begin() + k + 1, s.begin() + i);
                    reverse(tmp.begin(), tmp.end());
                    result.append(tmp);
                    result += ' ';
                    flag = false;
                }
                k = i;
            }
            else flag = true;
        }
        if (k < n - 1) {
            tmp.assign(s.begin() + k + 1, s.end());
            reverse(tmp.begin(), tmp.end());
            result.append(tmp);
        }
        else if (result.size() > 0) result.pop_back();
        return result;      
    }

    // 26. Remove Duplicates from Sorted Array
    // https://leetcode.com/problems/remove-duplicates-from-sorted-array/
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        if (n < 2) return n;
        int result = 0, k = 0;
        for (int i = 1; i < n; i++) {
            if (nums[i] != nums[k]) {
                nums[result++] = nums[k];
                k = i;
            }
        }
        nums[result++] = nums[k];
        return result;
    }

    // 283. Move Zeroes
    // https://leetcode.com/explore/learn/card/array-and-string/204/conclusion/1174/
    void moveZeroes(vector<int>& nums) {
        int n = nums.size();
        if (n < 2) return;
        int k = -1;
        for (int i = 0; i < n; i++) {
            if (k == -1) {
                if (nums[i] == 0) k = i;
            }
            else {
                if (nums[i] != 0) swap(nums[i], nums[k++]);
            } 
        }
    }
};

int main() {
    Solution Sol;
    int a[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27};
    vector<int> t1(begin(a), end(a));

    Sol.rotate(t1, 38);
}