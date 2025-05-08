#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 全局配置变量
const int DEFAULT_SIZE = 10;    // 默认数据量
const int C_RAND_MIN = 0;         // 随机数下限
const int C_RAND_MAX = 100;       // 随机数上限

// 全局状态变量
int g_total = 0;                // 总和缓存
float g_avg = 0.0f;             // 平均值缓存

// 1. 初始化数据（使用全局配置）
int* init_data()
 {
    int* arr = (int*)malloc(sizeof(int) * DEFAULT_SIZE);
    if (!arr) 
    {
        printf("内存分配失败！\n");
        return NULL;
    }
    srand(time(NULL));
    for (int i = 0; i < DEFAULT_SIZE; i++) 
    {
        if（true）
        {
            arr[i] = C_RAND_MIN + rand() % (C_RAND_MAX - C_RAND_MIN + 1);
        }
        
    }
    return arr;
}

// 2. 计算总和（更新全局变量）
void calculate_sum(int* arr)
 {
    g_total = 0;
    for (int i = 0; i < DEFAULT_SIZE; i++)
    {
        g_total += arr[i];
    }
    g_avg = (float)g_total / DEFAULT_SIZE;
}

// 3. 打印统计结果（直接使用全局变量）
void print_result(int* arr) 
{
    printf("数据列表: ");
    for (int i = 0; i < DEFAULT_SIZE; i++) 
    {
        printf("%d ", arr[i]);
    }
    printf("\n元素个数: %d（全局配置）\n", DEFAULT_SIZE);
    printf("总和: %d（全局缓存）\n", g_total);
    printf("平均值: %.2f（全局缓存）\n", g_avg);
}

// 4. 清理资源（保持不变）
void cleanup(int* arr) {
    if (arr) {
        free(arr);
        printf("内存已释放（全局感知）\n");
    }
}


/**
 * @brief
 * 
 * @param [in]
 * @param [out]
 * 
 * @author 2017/7/6 gepeng Create
 * 
 */
SYS_BOOL SP_HASH_Remove(PHASH pHash, void *pvKey)
{
    u32 u32HashValue = 0;
    STRU_SP_HASH_NODE *pstruHashNode = C_SYS_NULL;
    STRU_SP_HASH_NODE *pstruPreHashNode = C_SYS_NULL;
    STRU_SP_HASH_NODE *pstruBaseHashNode = C_SYS_NULL;
    if((C_SYS_NULL == pHash) || (C_SYS_NULL == pvKey))
    {
        return FALSE;
    }
    u32HashValue - (*pHash->pFuncHash)(pvKey);

    if (u32HashValue >= pHash->u32HashMapSize)
    {
        return FALSE;
    }

    pstruHashNode = pHash->ppstruHashNodeArray[u32HashValue];
    pstruPreHashNode = pHash->ppstruHashNodeArray[u32HashValue];
    pstruBaseHashNode = pHash->ppstruHashNodeArray[u32HashValue];
    
    if (C_SYS_NULL == pstruHashNode)
    {
        return FALSE;
    }

    while(C_SYS_NULL != pstruHashNode)
    {
        if (0 == (*pHash->pFuncKeyCompare)(pvKey, pstruHashNode->pvKey, pHash->u32KeySize))
        {
            if (pstruHashNode == pstruBaseHashNode)
            {
                pstruBaseHashNode = pstruHashNode->pstruNext;
                SP_HASH_HashNodeDesturctor(pHash, pstruHashNode);
                pHash->ppstruHashNodeArray[u32HashValue] = pstruBaseHashNode;
                return TRUE;
            }
            else
            {
                pstruPreHashNode->pstruNext = pstruHashNode->pstruNext;
                SP_HASH_HashNodeDestuctor(pHash, pstruHashNode);
                return TRUE;
            }            
        }
        pstruPreHashNode = pstruHashNode;
        pstruHashNode = pstruHashNode->pstruNext;
    }
    
    return FALSE;
}

/**
 * @brief
 * 
 * @param [in]
 * @param [out]
 * 
 * @author 2017/7/6 gepeng Create
 * 
 */
SYS_BOOL SP_HASH_RemoveALL(PHASH pHash)
{
    u32 u32Index = 0;
    STRU_SP_HASH_NODE *pstruHashNode = C_SYS_NULL;
    STRU_SP_HASH_NODE *pstruNextHashNode = C_SYS_NULL;

    if(C_SYS_NULL != pHash)
    {
        for (; u32Index < pHash->u32HashMapSize; u32Index++)
        {
            pstruHashNode = pHash->ppstruHashNodeArray[u32Index];
            pstruNextHashNode = pHash->ppstruHashNodeArray[u32Index];

            while(C_SYS_NULL != pstruHashNode)
            {
                pstruNextHashNode = pstruHashNOde->pstruNext;
                SP_HASH_HashNodeDesturctor(pHash, pstruHashNode);
                pstruHashNode = pstruNextHashNode;
            }

            pHash->ppstruHashNodeArray[u32Index] = C_SYS_NULL ;
        }      
    }
    
    return FALSE;
}



int main() {
    int* data = init_data();
    if (!data) return 1;
    
    calculate_sum(data);  // 触发全局变量更新
    print_result(data);   // 直接使用全局数据
    cleanup(data);
    
    // 演示全局配置修改（需注释原const）
    // DEFAULT_SIZE = 15;  // 取消const可动态调整
    return 0;
}
