/*
 * mathPuzzles.cpp
 *
 *  Created on: Sep 15, 2017
 *      Author: Pradeep Gopanapalli
 */

using namespace std;
class mathPuzzles {
    private:
    public:
    /* Multiply numbers a and b without using * */
    int multipynums(int a ,int b) {
            int result = 0  ;

            if (!b%2) result += a; /*if b is odd then shift and add a */
            while (b>>=1) a <<= 1;
            result += a;

            return result;
        }
};
/* get sum of a & b without using +/- */
int getSum(int a, int b) {
        while (b) {
            int temp = a;
            a = a ^ b; /* exclusive or of a & b */
            b = (temp & b) << 1; /*carry forward */
        }
        return a;
}



