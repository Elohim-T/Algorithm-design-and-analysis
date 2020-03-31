import java.util.Arrays;

public class Main {
    public static void main(String[] args) {
        int A[] = {0, 1, 2, 3, 3, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
        System.out.println(select(A, 0, A.length - 1, 1));
    }

    static int r = 5;

    private static int select(int[] A, int low, int high, int k) {
        int num = high - low + 1;
        int group = (int) Math.ceil(1.0 * num / r);
        //每个分组排序，存于M[]
        int[] M = new int[group];

        for (int i = 0; i < group; i++) {
            Arrays.sort(A, low + r * i, low + r * i + (num > r * i + r ? r : num - i * r));
            M[i] = A[low + r * i + (num > r * i + r ? r : num - i * r) / 2];
        }
        //选M[]的中位数m
        int mid = M.length <= 2 ? M[0] : select(M, 0, M.length - 1, M.length / 2);
        int[] S1 = new int[num];//小于mid的数
        int[] S2 = new int[num];//大于mid的数
        int numS1, numS2, numS3;
        numS1 = numS2 = numS3 = 0;
        //对数进行分组
        for (int i = low; i <= high; i++) {
            if (A[i] < mid) {
                S1[numS1++] = A[i];
            } else if (A[i] == mid) {
                numS3++;
            } else {
                S2[numS2++] = A[i];
            }
        }
        if (numS1 >= k) {
            //小于mid的数的数量对大于等于k
            return select(S1, 0, numS1 - 1, k);
        } else if (numS1 + numS3 >= k) {
            return mid;
        } else {
            //小于等于mid的数的数量小于k
            return select(S2, 0, numS2 - 1, k - numS1 - numS3);
        }

    }

}
