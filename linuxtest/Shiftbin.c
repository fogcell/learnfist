int mult(int x,int y)
{
    int op1= x;int op2=y;
    int result=0;
    while (op2!=0) {
        if (1 == (0x01&op2)) {
            result += op1;
            printf("d%d\n",result);
        }
        op1 <<= 1;
        op2 >>= 1;
    }
    return result;
}//移位 与加法实现乘法，基础版
