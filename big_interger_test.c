#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<string.h>

int digi_value(const char* point,int pos);
int is_negative(const char* s);
int is_postive(const char* s);
char* sub_internal(const char* left,const char* right);
char* sub(const char* left,const char* right);;
char* add_internal(const char* left,const char* right);
char* add(const char* left,const char* right);
void test_add();
char* negate(char* s);
int is_less_than(const char* left,const char* right);
void test_sub();
char* mul_by_x(const char* s,int x);
char* mul_internal(const char* left,const char* right);
char* mul(const char* left,const char* right);
void test_mul();

//取各个位上的数值
int digi_value(const char* point,int pos)
{
    if (pos > strlen(point))
        return 0;
    return point[(strlen(point) - pos)] - '0';
}

//判断正负
int is_negative(const char* s)
{
    return *s == '-';
}
int is_postive(const char* s)
{
    return *s != '-';
}

//两个正数的相加
char* add_internal(const char* left,const char* right)
{
    int lv = 0;
    int rv = 0;
    int carry = 0;
    int sum = 0;
    int max_width = strlen(left) > strlen(right) ? strlen(left) : strlen(right);
        
    char* result = calloc(max_width + 1 + 1,sizeof(char));
        
    int pos = 1;
    while (pos <= max_width + 1)
    {
        lv = digi_value(left,pos);
        rv = digi_value(right,pos);
    
        if(1)
        {
            sum = lv + rv + carry;
            /*
            if (sum>=10)
            {
                carry = 1;
            }
            else
            {
                carry = 0;
            }
            */
            carry =  sum >= 10 ? 1 : 0;
            result[max_width + 1 - pos] = sum % 10 + '0';
        }
    
        if (0)
        {
            if ((lv + rv + carry) > 9)
            {
                result[max_width + 1 - pos] = lv + rv + carry - 10 + '0';
                carry = 1;
            }
            else
            {
                result[max_width + 1 - pos] = lv + rv + carry + '0';
                carry = 0;
            }
        }
    
    pos++;
    }
    
    if (result[0] == '0')
    {
        memmove(result,result + 1,max_width + 1);
    }
        
    return result;
}

//通用加法
char* add(const char* left,const char* right)
{
    //if (*left != '-' && *right == '-')
    if (is_postive(left) && is_negative(right))
    {
        return sub(left,right + 1);
    }
    if (is_negative(left) && is_postive(right))
    {
        //return add(right,left);
        return sub(right,left + 1);
    }
    if (is_negative(left) && is_negative(right))
    {
        return negate(add_internal(left+1,right+1));
    }
    else
    {
        return add_internal(left,right);
    }    
}

//加法测试
void test_add()
{
    char* result = NULL;
    
    result = add("1","2");
    assert(strcmp(result,"3") == 0);
    free(result);
    
    result = add("1","3");
    assert(strcmp(result,"4") == 0);
    free(result);
    
    result = add("1","34");
    assert(strcmp(result,"35") == 0);
    free(result);
    
    result = add("33","33");
    assert(strcmp(result,"66") == 0);
    free(result);
    
    result = add("1","338");
    assert(strcmp(result,"339") == 0);
    free(result);
    
    result = add("1","89");
    assert(strcmp(result,"90") == 0);
    free(result);
    
    result = add("1","99");
    assert(strcmp(result,"100") == 0);
    free(result);
    
    result = add("5","-3");
    assert(strcmp(result,"2") == 0);
    free(result);
    
    result = add("5","-6");
    assert(strcmp(result,"-1") == 0);
    free(result);
    
    result = add("-123","23");
    assert(strcmp(result,"-100") == 0);
    free(result);
    
    result = add("-111","-222");
    assert(strcmp(result,"-333") == 0);
    free(result);
    
    result = add("123456789876543212345678987654321","123456789876543212345678987654321");
    printf("123456789876543212345678987654321 + 123456789876543212345678987654321  = %s\n",result);
}

//取负数
char* negate(char* s)
{
    char* result = calloc(strlen(s) + 2,sizeof(char));
    result[0] = '-';
    memcpy(result + 1,s,strlen(s) + 1);
    free(s);
    return result;
}

//判断大小
int is_less_than(const char* left,const char* right)
{
    /*
    if((strlen(left) == strlen(right)) && (memcmp(left,right,strlen(left)) < 0)  || (strlen(left) < strlen(right)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
    */
    
    return (strlen(left) == strlen(right)) && (memcmp(left,right,strlen(left)) < 0) || (strlen(left) < strlen(right));
}

//两个正数相减
char* sub_internal(const char* left,const char* right)
{   
    int lv = 0;
    int rv = 0;
    int diff = 0;
    int jie = 0;
    int max_width = strlen(left) > strlen(right) ? strlen(left) : strlen(right);
        
    char* result = calloc(max_width + 1,sizeof(char));
        
    int pos = 1;
    while (pos <= max_width)
    {
        lv = digi_value(left,pos);
        rv = digi_value(right,pos);
        if(1)
        {
            diff = lv - rv - jie;
            if (diff < 0)
            {
              result[max_width - pos] = diff + 10 + '0';  
              jie = 1;
            }
            else
            {
                result[max_width - pos] = diff + '0';
                jie = 0; 
            }
        }  
    pos++;
    }
 
    int i = 0;
    while (i < max_width)
    {
        if (result[i] != '0')
            break;
        i++;
    }
    memmove(result,result + i,max_width - i + 1);
    
    return result;
}

//通用减法
char* sub(const char* left,const char* right)
{
    if (is_postive(left) && is_postive(right))
    {
        if(is_less_than(left,right))
        {
            return negate(sub_internal(right,left));
        }
        else
        {
            return sub_internal(left,right);
        }
    }
    if (is_postive(left) && is_negative(right))
    {
        return add(left,right + 1);
    }
    if (is_negative(left) && is_postive(right))
    {
        return negate(add(right,left + 1));
    }
    if (is_negative(left) && is_negative(right))
    {
        return sub(right + 1,left + 1);
    }
}

//减法测试
void test_sub()
{
    char* result = NULL;
    
    result = sub("4","3");
    assert(strcmp(result,"1") == 0);
    free(result);
    
    result = sub("14","3");
    assert(strcmp(result,"11") == 0);
    free(result);
    
    result = sub("14","5");
    assert(strcmp(result,"9") == 0);
    free(result);
    
    result = sub("100","99");
    assert(strcmp(result,"1") == 0);
    free(result);
    
    result = sub("5","9");
    assert(strcmp(result,"-4") == 0);
    free(result);
    
    result = sub("5","19");
    assert(strcmp(result,"-14") == 0);
    free(result);
    
    result = sub("5","13");
    assert(strcmp(result,"-8") == 0);
    free(result);
    
    result = sub("45","-123");
    assert(strcmp(result,"168") == 0);
    free(result);
        
    result = sub("-45","123");
    assert(strcmp(result,"-168") == 0);
    free(result);
    
    result = sub("-45","-123");
    assert(strcmp(result,"78") == 0);
    free(result);
    
    result = sub("123456789876543212345678987654321","-123456789876543212345678987654321");
    printf("123456789876543212345678987654321 - (-123456789876543212345678987654321)  = %s\n",result);
}

//与一位正整数(<10)相乘
char* mul_by_x(const char* s,int x)
{
    char c = 0;
    char* acc = add("0","0");
    char* p =NULL;
    
    for (c = 0; c < x; c++)
    {
        p = add(acc,s);
        free(acc);
        acc = p;
    }
    return acc;
}

//两个正整数相乘
char* mul_internal(const char* left,const char* right)
{
    int pos = 0;
    char* acc = add("0","0");
    char* p = NULL;
    char* p1 = NULL;
    char* p2 = NULL;
    while (pos < strlen(right))
    {
        p2 = mul_by_x(acc,10);
        p1 = mul_by_x(left,right[pos] - '0');
        p = add(p2,p1);
        free(p1);
        free(p2);
        acc = p;
        pos++;
    }
    return acc;
}

//通用乘法
char* mul(const char* left,const char* right)
{
    if (is_negative(left) && is_postive(right))
    {
        return negate(mul_internal(left + 1,right));
    }
    if (is_postive(left) && is_negative(right))
    {
        return negate(mul_internal(left,right + 1));
    }
    if (is_negative(left) && is_negative(right))
    {
        return mul_internal(left + 1,right + 1);
    }
    return mul_internal(left,right);
}

//乘法测试
void test_mul()
{
    char* result = NULL;
    
    result = mul("4","3");
    assert(strcmp(result,"12") == 0);
    free(result);
    
    result = mul("11","22");
    assert(strcmp(result,"242") == 0);
    free(result);
    
    result = mul("-11","22");
    assert(strcmp(result,"-242") == 0);
    free(result);
    
    result = mul("11","-22");
    assert(strcmp(result,"-242") == 0);
    free(result);

    result = mul("-11","-22");
    assert(strcmp(result,"242") == 0);
    free(result);
    
    result = mul("12345678987654321","-12345678987654321");
    printf("12345678987654321 * (-12345678987654321)  = %s\n",result);
}

int main()
{  
    test_add();
    test_sub();
    test_mul();
    printf("--------Congratulations!--------\n");
    return 0;
}
