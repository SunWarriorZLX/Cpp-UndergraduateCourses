/* 快速排序 */
#include "LinkedListQueue.h"
template <typename T>
class sort /* 定义一个排序的工具类 */
{
private:
    void QuickSort(Queue<T> &nums, int low, int high)
    {
        /* 判断递归是否结束，low >= high 说明已经剩下单个元素，且该元素的位置已经确定，因此递归结束 */
        if (low >= high)
            return;

        /* 将已分组序列的第一个元素设置为标志元素，本次调用将计算出其在数组中的正确位置（指排序后） */
        T temp = nums[low];
        int i = low, j = high + 1; /* 此处 high+1 防止数组访问越界 */
        for (; true;)
        {
            for (i++; nums[i] < temp && i != high; i++)
                ; /* 从左到右检索大于 temp 的元素 */
            for (j--; nums[j] > temp && j != low; j--)
                ;       /* 从右到左检索小于 temp 的元素 */
            if (i >= j) /* 左右两边已全部检索，此时 j 等于 temp 在排序后的位置 */
                break;

            /* 交换检索到的元素，把小于 temp 的元素放到 temp 前面；大于 temp 的元素放到后面 */
            swap(nums[i], nums[j]);
        }

        /* 此时 j 为 temp 排序后的位置，由于上面的循环是 i 先停止的，因此 nums[j] 必然小于 temp，最后将
         nums[low]（即 temp 所代表的元素）放到 nums[j] 上 */
        swap(nums[low], nums[j]);

        /* 下标 j 将序列分成两个序列，递归，继续排序两个序列中除去 temp 以外的元素 */
        QuickSort(nums, low, j - 1);
        QuickSort(nums, j + 1, high);
    }
    void swap(T &a, T &b)
    {
        T temp = a;
        a = b;
        b = temp;
    }

public:
    void Sort(Queue<T> &nums, int size) //统一外部接口
    {
        QuickSort(nums, 0, size);
    };
};
