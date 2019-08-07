#define         m       32887
#define         EMPTY   -32768

int table[m];
void hash_init();
void hash_insert();
int  hash_srch();


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    int i,j,idx0,idx;
    hash_init();
    for(i=0;i<numsSize;i++)
        hash_insert(nums[i]);
    
    for(i=0;i<numsSize;i++)
    {
        
        idx=hash_srch(target-nums[i]);  //在table中的idx
        
        if(nums[i]*2==target)           //該元素*2等於目標的情況
        {
            idx0=i;
            int flag=0;
            for(j=i ;j<numsSize && flag<2 ;j++)
                if(nums[j]==nums[i])    //該元素的值如果出現一次就+1
                    flag++;
            
            if(flag==2)
            {
                idx=j-1;
                break;
            }   
        }
            
        
        else if(idx!=-1)  //如果有找到目標
        {
            idx0=i;
            
            for(j=i;j<numsSize;j++)
                if(nums[j]==table[idx])
                {
                    idx=j;
                    break;
                }

            
            break;
        }
    }
    
    *returnSize=2;
    
    int *ans=(int*)malloc(*returnSize*sizeof(int));
    ans[0]=idx0;
    ans[1]=idx;
    return ans;
    
}


//雜湊函數  這裡是取m的餘數
int hash(int key)
{
    return(abs(key)*11 % m);
}

//將陣列初始化 都變成空格
void hash_init(void)
{
    int i;
    for(i=0;i < m;i++)
        table[i]= EMPTY;
}


void hash_insert(int key)
{
    int addr=hash(key);         /*呼叫雜湊函數得位置*/
    while(table[addr] != EMPTY)
        addr=(addr+1) % m;      /*取餘數才能再從table[0]開始*/
    table[addr]=key;
}

/*搜尋鍵值為key,成功傳回表格位置,失敗傳回-1*/
int hash_srch(int key)
{
    int addr;
    addr=hash(key); //得到key的address
    while(table[addr] != key)   //當addr的值不等於key 往右移一格
    {
        addr=(addr+1)%m;  //取除m餘數確保可循環
        if(table[addr]== EMPTY || addr==hash(key))/*若是空格或又回到原點*/
                return(-1);                    /*則傳回失敗*/
    }
    return(addr);
}
