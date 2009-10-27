#include "shapeLSS.hpp"

using namespace blitz;

/**< Default constructor */

shapeLSS::shapeLSS(Array<double,2>* coefficient, Array<double,2>* _price = NULL)
{
    price = _price;
    intercept = new Array<double,2>((*coefficient));
}
/** Copy constructor */

shapeLSS::shapeLSS(const shapeLSS& origin)
{
    price = new Array<double,2>((*origin.price));
    intercept = new Array<double,2>((*origin.intercept));
}
/** Methods to get demand value*/
inline double shapeLSS::getDemand(int j, int t){return (*intercept)(j,t);}
/** Methods to get demand array*/
Array<double,2>* shapeLSS::getDemand()
{
    int product = intercept -> rows();
    int period = intercept -> columns();
    Array<double,2>* tab = new  Array<double,2>(product,period);
    for (int j = 0; j < product; j ++)
    {
        for (int t = 0; t < period; t ++)
        {
            (*tab)(j,t) = getDemand(j,t);
        }
    }
    return tab;
}
/** Methods to get demand array*/
double getDemand(blitz::Array<double,2>* currentPrice,int j, int t){return (*intercept)(j,t);}
/** Methots to get profit array */
Array<double,2>* shapeLSS::getProfit()
{
    if (price == NULL)
    {
        return getDemand();
    }
    int product = intercept -> rows();
    int period = intercept -> columns();
    Array<double,2>* profit = new  Array<double,2>(product,period);
    for (int j = 0; j < product; j ++)
    {
        for (int t = 0; t < period; t ++)
        {
            (*profit)(j,t) = getDemand(j,t)*(*price)(j,t);
        }
    }
    return profit;
}
