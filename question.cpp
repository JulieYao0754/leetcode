#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_set>
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

    // 217. Contains Duplicate
    // https://leetcode.com/problems/contains-duplicate/
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> hs;
        for (int num: nums) {
            if (hs.count(num) > 0) return true;
            else hs.insert(num);
        }
        return false;
    }

    // 136. Single Number
    // https://leetcode.com/problems/single-number/
    int singleNumber(vector<int>& nums) {
        int result = 0;
        for (int num: nums) result ^= num;
        return result;
    }

    // 349. Intersection of Two Arrays
    // https://leetcode.com/problems/intersection-of-two-arrays/
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        // unordered_set<int> ns(nums1.begin(), nums1.end());
        unordered_set<int> ns;
        vector<int> result;
        for(int num1: nums1) ns.insert(num1);
        for(int num2: nums2) {
            if (ns.count(num2) > 0) {
                result.emplace_back(num2);
                ns.erase(num2);
            }
        }
        return result;
    }
};

// 705. Design HashSet
// https://leetcode.com/problems/design-hashset/
class MyHashSet {
private:
    int hasharray[1000001];

public:
    /** Initialize your data structure here. */
    MyHashSet() {
        
    }
    
    void add(int key) {;
        hasharray[key] = 1;
    }
    
    void remove(int key) {
        hasharray[key] = 0;
    }
    
    /** Returns true if this set contains the specified element */
    bool contains(int key) {
        if (hasharray[key] == 1) return true;
        return false;
    }
};

// 706. Design HashMap
// https://leetcode.com/problems/design-hashmap/
class MyHashMap {
private:
    int hasharray[1000001];
public:
    /** Initialize your data structure here. */
    MyHashMap() {
        for (int i = 0; i < 1000001; i++) hasharray[i] = -1;
    }
    
    /** value will always be non-negative. */
    void put(int key, int value) {
        hasharray[key] = value;
    }
    
    /** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
    int get(int key) {
        return hasharray[key];
    }
    
    /** Removes the mapping of the specified value key if this map contains a mapping for the key */
    void remove(int key) {
        hasharray[key] = -1;
    }
};

class RandomClick {
public:
    // 1093. Statistics from a Large Sample
    // https://leetcode.com/problems/statistics-from-a-large-sample/
    vector<double> sampleStats(vector<int>& count) {
        vector<double> result(5);
        bool minflag = false, maxflag = false;
        int counts = 0;
        for (int i = 0; i < 256; i++) {
            if (!minflag && count[i] > 0) {
                result[0] = i;  // minimum
                minflag = true;
            }
            counts += count[i];
            result[2] += i * count[i];  // mean
            if (count[i] > count[result[4]]) result[4] = i; // mode
        }
        result[2] /= counts;
        int j = 0, k = 255, lc = count[j], rc = count[k];
        while (j < k) {
            if (!maxflag && count[k] > 0) {
                result[1] = k;  // maximum
                maxflag = true;
            }
            if (lc + rc == counts) break;
            if (lc > rc) {
                k--;
                rc += count[k];
            }
            else {
                j++;
                lc += count[j];
            }
        }
        if (lc == rc) result[3] = (j + k) / 2.0;
        else if (lc > rc) result[3] = j;
        else result[3] = k;
        return result;
    }
};

int main() {
    /*
    Solution Sol;
    int a[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27};
    vector<int> t1(begin(a), end(a));

    Sol.rotate(t1, 38);
    */
//    int a[] = {0,1,3,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//               0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//               0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//               0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//               0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//               0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int a[] = {652958,2522230,2465704,3832942,2754307,3451782,2776741,3398778,1323557,3785775,3184920,1100919,235592,662549,2563642,3036360,1996527,3705715,825817,3059729,2643006,3164888,148125,2505531,829199,189123,2239544,1735001,47730,1022995,3169331,3810442,2460389,1075633,3641414,2173315,1314752,1722600,1916232,1065769,1060527,1955368,3355152,649890,2590549,53360,1220867,1300573,3180064,3871511,342488,1776396,2843299,2671214,1207635,2921445,53106,190689,467786,2881315,2344937,212389,2386727,3875730,2190046,3409898,1408725,3048496,2867953,3135570,2432864,1933070,1603594,2019826,180529,3045537,2249666,2951898,2482439,3024064,3524566,2141017,3742383,799524,1469154,293250,1067599,1905804,2396055,2172195,2858562,1534287,1575952,601213,3455176,1203347,544860,3892538,520295,1702638,349639,3024786,1952106,1517275,2050957,4535,1657261,2355059,3168685,2981434,3566412,592191,2146008,1543766,1750688,3213722,3569504,2609287,3763041,628127,1508571,489179,311908,3613193,669184,2304018,1996451,1004078,3834156,3329104,1520096,1663361,1597628,1600011,3750542,2089582,1593571,1173342,733072,3478705,3580849,2939384,237497,3060221,2925767,3195082,3899321,82885,3233869,3120434,2329561,3305348,99358,1133566,2271989,2833394,2315617,2945369,1790281,2835887,3863051,822151,143200,938699,341686,1975441,1231516,1574235,2206397,1409254,738302,2487741,1859422,927941,3558351,3812682,3730642,2572155,2682116,829589,2512211,3675235,1374535,1070909,3551663,2630024,1824728,3887991,2578648,1339330,1852223,500054,2738506,2582517,3483094,1263097,71922,2117392,1915528,1876631,1176735,2024988,1039754,166730,596051,2351692,3320051,333675,848482,849207,2053241,526718,1455618,1479452,1560714,3388737,626298,205338,551162,3331124,1065550,632389,2815802,1202391,1700988,875769,2726105,3040859,3004780,1753639,995061,1387695,1883108,3008913,805735,2577588,2823145,2451544,1877117,1511402,3681237,1949282,2799341,3334487,3356387,876811,679101,667366,84074,1188002,1939276,1671058,1324519,3546841,1521673,1966319};
    vector<int> t1(begin(a), end(a));
    RandomClick Sol;
    Sol.sampleStats(t1);
}