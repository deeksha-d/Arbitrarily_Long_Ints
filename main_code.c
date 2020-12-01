#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "intal.h"

static int min(int x, int y);
static char* reverseString(const char* str);
static void merge(char **arr, int l, int m, int r);

static void strcopy(char *s1, const char *s2)
{
    int i;
    for (i = 0; s2[i] != '\0'; ++i) {
        s1[i] = s2[i];
    }
    s1[i] = '\0';
}

static char* reverseString(const char* str) 
{ 
    int len, i; 
    char *begin_ptr, *end_ptr, ch; 
  
    len = strlen(str); 

    char *rev = (char*) malloc((len+1) * sizeof(char));
    rev[len] = '\0';

    strcopy(rev, str);
    begin_ptr = rev; 
    end_ptr = rev; 
  
    for (i = 0; i < len - 1; i++) 
        end_ptr++; 

    for (i = 0; i < len / 2; i++)
    { 
        ch = *end_ptr; 
        *end_ptr = *begin_ptr; 
        *begin_ptr = ch; 

        begin_ptr++; 
        end_ptr--; 
    } 
    
    return rev;
} 
static int min(int x, int y) { return (x<y)? x :y; }

static void merge(char **arr, int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 

    char L[n1][1001];
    char R[n2][1001]; 
  
    for (i = 0; i < n1; i++) 
        strcpy(L[i], arr[l + i]); 
    for (j = 0; j < n2; j++) 
        strcpy(R[j], arr[m + 1+ j]); 

    i = 0; 
    j = 0; 
    k = l; 
    while (i < n1 && j < n2) 
    { 
        int cmp = intal_compare(L[i], R[j]);
        if (cmp == -1 || cmp == 0) 
        { 
            strcpy(arr[k], L[i]); 
            i++; 
        } 
        else
        { 
            strcpy(arr[k], R[j]); 
            j++; 
        } 
        k++; 
    } 
  
    while (i < n1) 
    { 
        strcpy(arr[k], L[i]);
        i++; 
        k++; 
    } 
  
    while (j < n2) 
    { 
        strcpy(arr[k], R[j]);
        j++; 
        k++; 
    } 
} 

static int multiply(int x, char *res, int res_size) 
{ 
    int carry = 0; 
  
    for (int i=0; i<res_size; i++) 
    { 
        int prod = (res[i]-'0') * x + carry; 
        res[i] = (prod % 10) + '0';   
        carry  = prod/10;     
    } 

    while (carry) 
    { 
        res[res_size] = (carry%10) + '0'; 
        carry = carry/10; 
        res_size++; 
    } 

    return res_size; 
} 

char* intal_add(const char* intal1, const char* intal2)
{
    int a = strlen(intal1);
    int b = strlen(intal2);
    int large = (a>b)?a:b;
    int small = (a+b)-large;

    char *inal1 = reverseString(intal1);
    char *inal2 = reverseString(intal2);

    char *bigger = (a>b)?inal1:inal2;

    // char *sum = (char *)malloc((large+2) * sizeof(char));
    char sum[large+2];
    sum[large + 1] = '\0';

    int carry = 0;

    for (int i=0;i<small;++i)
    {
        a = carry + (inal1[i]-'0') + (inal2[i]-'0');
        carry = a/10;
        a = a % 10;
        sum[i] = a + '0';
        
    }

    for(int i=small;i<large;++i)
    {
        a = carry + (bigger[i] - '0');
        carry = a/10;
        a = a % 10;
        sum[i] = a + '0';
    }

    if (carry)
    {
        sum[large] = carry + '0';
    }
    else
    {
        sum[large] = '\0';
    }
  
    char *res = reverseString(sum);

    free(inal1); inal1 = NULL;
    free(inal2); inal2 = NULL;

    return res;
}

int intal_compare(const char* intal1, const char* intal2)
{
    int a = strlen(intal1);
    int b = strlen(intal2);
    if (a > b)
    {
        return 1;
    }
    else if (b > a)
    {
        return -1;
    }
    else
    {
        int i = 0;
        while(intal1[i] == intal2[i] && i < a)
        {
            ++i;
        }
        if (i == a)
        {
            return 0;
        }
        else
        {
            if (intal1[i] > intal2[i])
            {
                return 1;
            }
            else
            {
                return -1;
            }    
        }
    }  
}

char* intal_diff(const char* intal1, const char* intal2)
{
    int cmp = intal_compare(intal1, intal2);
    char *big, *small;

    char *ans = (char*)malloc(2* sizeof(char));
    switch(cmp)
    {
        case 0: strcpy(ans, "0");
                return ans;
                break;
        case 1: big = reverseString(intal1);
                small = reverseString(intal2);
                break;
        case -1:big = reverseString(intal2);
                small = reverseString(intal1);
                break;
    }

    int max = strlen(big);
    int min = strlen(small);

    char res[max];

    int carry = 0, c = 0;
    int idx = 0;
    for (int i=0; i<min; ++i)
    {
        int sub = (big[i]-'0') - (small[i]-'0') - carry;

        if (sub < 0)
        {
            sub += 10;
            carry = 1;
        }
        else
        {
            carry = 0;
        }
        if (sub)
        {
            idx = c;
        }
        res[c++] = sub + '0';
    }

    for (int i=min; i<max; ++i)
    {
        int sub = (big[i]-'0') - carry;
        if (sub < 0)
        {
            sub += 10;
            carry = 1;
        }
        else
        {
            carry = 0;
        }
        if (sub)
        {
            idx = c;
        }
        res[c++] = sub + '0';
    }

    char d[idx + 2];
    d[idx + 1] = '\0';
    
    for (int i=0;i<=idx; ++i)
    {
        d[i] = res[i];
    }

    char *diff = reverseString(d);
    free(big); big = NULL;
    free(small); small = NULL;
    free(ans); ans = NULL;

    return diff;
}

char* intal_multiply(const char* intal1, const char* intal2)
{
    int a = strlen(intal1);
    int b = strlen(intal2);

    char res[a+b+1];
    res[a+b] = '\0';
    
    for (int i=0; i<a+b; ++i)
    {
        res[i] = '0';
    }

    int s_num1 = 0;
    int s_num2 = 0;
    int num1, num2;
    int sum = 0, carry = 0;

    for (int i=a-1; i>=0; --i)
    {
        carry = 0;
        num1 = intal1[i] - '0';
        s_num2 = 0;

        for (int j=b-1; j>=0; --j)
        {
            num2 = intal2[j] - '0';
            sum = num1*num2 + (res[s_num1 + s_num2]-'0') + carry;

            carry = sum/10;
            res[s_num1 + s_num2] = sum % 10 + '0';

            ++s_num2;
        }

        if (carry > 0)
        {
            res[s_num1 + s_num2] += carry;
        }

        ++s_num1; 
    } 
 
    int i = strlen(res) - 1; 
    while (i>=0 && res[i] == '0') 
    i--; 
  
    if (i == -1) 
    {
        char *res = (char*)malloc(2* sizeof(char));
        strcpy(res, "0");
        return res;
    } 
  
    // generate the result string 
    char *s = (char*)malloc((i+2) * sizeof(char));
    s[i+1] = '\0';

    int c = 0;
    while (i >= 0) 
        s[c++] = res[i--]; 

    return s; 

}

char* intal_mod(const char* intal1, const char* intal2)
{
    char *res = (char*)malloc((1001) * sizeof(char));
    res[1000] = '\0';
    
    if (intal_compare(intal1, intal2) == -1)
    {   
        strcopy(res, intal1);
        return res;
    }
    else
    {
        char limit[] = "4294967295";
        if (intal_compare(intal2, limit) == 1)
        {
            strcopy(res, intal1);

            while (intal_compare(res, intal2) == 1 || intal_compare(res, intal2) == 0)
            {
                res = intal_diff(res, intal2);
            }
            return res;
        }
        else
        {
            char *end;
            unsigned long int n2 = strtoul(intal2, &end, 0);
            
            unsigned long int mod = 0; 
            for (int i=0; i<strlen(intal1); i++) 
            {
                mod = (mod*10 + (intal1[i] - '0')) % n2; 
            }
            sprintf(res, "%lu", mod);
            return res;
        }
    }
}

char* intal_pow(const char* intal1, unsigned int n) 
{ 
    if (intal1[0] == '0')
    {
        char *res = (char*)malloc(2* sizeof(char));
        strcpy(res, "0");
        return res;
    }

    int a = strlen(intal1);
    char *n1 = (char*)malloc((a+1) * sizeof(char));
    n1[a] = '\0';

    strcopy(n1, intal1);

    char *res = (char*)malloc(1001 * sizeof(char));
    res[1000] = '\0';
    strcpy(res, "1");

    while (n > 0) 
    { 
        if (n & 1) 
        { 
            char *temp = intal_multiply(n1, res); 
			strcopy(res, temp);
			free(temp); temp = NULL;
        }
        n = n >> 1; 
        char *temp = intal_multiply(n1, n1); 
        strcopy(n1, temp);
        free(temp); temp = NULL;
        // n1 = intal_multiply(n1, n1); 
    } 

    free(n1); n1=NULL;
    return res; 
} 

char* intal_gcd(const char* intal1, const char* intal2)
{
    if (intal_compare(intal1, "0") == 0 || intal_compare(intal2, "0") == 0)
    {
        char *res = (char*)malloc(2* sizeof(char));
        strcpy(res, "0");
        return res;
    }
    char *big = (char*)malloc(1001 * sizeof(char));
    big[1000] = '\0';
    strcopy(big, (intal_compare(intal1, intal2)==1)?intal1:intal2);
    
    char small[1001];
    small[1000] = '\0';
    strcopy(small, (intal_compare(intal1, intal2)==-1)?intal1:intal2);

    char r[1001];
    char *temp;
    while (intal_compare(small, "0") != 0)
    {
        temp = intal_mod(big, small);
        strcopy(r, temp);
        free(temp);temp = NULL;
        strcpy(big, small);
        strcpy(small, r);
    }
    return big;
}

char* intal_fibonacci(unsigned int n)
{
    char a[1001]; a[1000] = '\0';
    char b[1001]; b[1000] = '\0';
    strcpy(a, "0"); strcpy(b, "1");

    char *c = (char*) malloc(1001 * sizeof(char));
    strcpy(c, "0"); c[1000] = '\0';

    if (n == 0)
    {
        char *res = (char*)malloc(2* sizeof(char));
        strcpy(res, "0");
        return res;
    }
    else if (n == 1)
    {
        char *res = (char*)malloc(2* sizeof(char));
        strcpy(res, "1");
        return res;
    }
    else
    {
        for(int i=2; i<=n; ++i)
        {
            // c = intal_add(a, b);
            char *temp = intal_add(a,b);
            strcopy(c, temp);
            free(temp); temp = NULL;
            strcpy(a, b);
            strcpy(b, c);
        }
    }
    
  return c; 
}

char* intal_factorial(unsigned int n)
{
    char *ser = (char*) malloc(1001 * sizeof(char));
    char res[1001];
    strcopy(res, "1"); res[1000] = '\0';
 
    int res_size = 1; 
  
    for (int i=2; i<=n; ++i) 
        res_size = multiply(i, res, res_size); 

    res[res_size] = '\0';
    ser = reverseString(res);
    return ser;
}

char* intal_bincoeff(unsigned int n, unsigned int k)
{   
    char *temp;
    if (k > (int)n/2)
    {
        k = n - k;
    }

    char res[k+1][1001];
    strcpy(res[0], "1");

    for (int i=1;i<k+1;++i)
    {
        strcpy(res[i], "0");
    }
    
    for (int i=1; i<=n; ++i) 
    {
        for (int j=(i<k)?i:k; j>0; --j)
        {
            temp = intal_add(res[j], res[j-1]);
            strcopy(res[j], temp);
            free(temp); temp = NULL;
        } 
    } 
    char *bin = (char*)malloc(1001 * sizeof(char));
    bin[1000] = '\0';
    strcpy(bin, res[k]);
    return bin; 
}

int intal_max(char **arr, int n)
{
        char max[1001];
        max[1000] = '\0';
        strcpy(max, arr[0]);
        int pos = 0;
        for (int i=1; i<n; ++i)
        {
            if (intal_compare(arr[i], max) == 1)
            {
                pos = i;
                strcpy(max, arr[i]);
            }
        }
        return pos;
}

int intal_min(char **arr, int n)
{
        char min[1001];
        min[1000] = '\0';
        strcpy(min, arr[0]);
        int pos = 0;
        
        for (int i=1; i<n; ++i)
        {
            if (intal_compare(arr[i], min) == -1)
            {
                pos = i;
                strcpy(min, arr[i]);
            }
        }
        return pos;
}

int intal_search(char **arr, int n, const char* key)
{
    int pos = 0;
    int i = 0;
    int found = 0;

    while (i<n && !found)    
    {
        if (intal_compare(arr[i], key) == 0)
        {
            pos = i;
            found = 1;
        }
        ++i;
    }

    return (found)?pos:-1;
}

int intal_binsearch(char **arr, int n, const char* key)
{
    int low = 0;
    int high = n-1;
    int mid;

    while (low <= high)
    {
        mid = low + ((high - low)/2);

        if (intal_compare(arr[mid], key) == 0)
        {
            return mid;
        }
        if (intal_compare(arr[mid], key) == -1)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return -1;
}

void intal_sort(char **arr, int n)
{ 
   int curr_size;  
   int left_start; 
  
   for (curr_size=1; curr_size<=n-1; curr_size = 2*curr_size) 
   { 
       for (left_start=0; left_start<n-1; left_start += 2*curr_size) 
       { 
           int mid = min(left_start + curr_size - 1, n-1); 
  
           int right_end = min(left_start + 2*curr_size - 1, n-1); 
  
           merge(arr, left_start, mid, right_end); 
       } 
   } 
} 


