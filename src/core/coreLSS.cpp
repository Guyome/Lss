#include "objConv.hpp"
#include "coreLSS.hpp"

using namespace blitz;

template <class data>
coreLSS<data>::coreLSS(data demand, data _prod, data _stor, data _consumption,
                    data _setup, data _constraint, int _period,
                    int _product)
{
    /** Initiate size of problem */
    period = _period;
    product = _product;
    /** Instanciate variable and data tabulars */
    prod = new Array<double,2>(product,period);
    stor = new Array<double,2>(product,period);
    cons = new Array<double,2>(product,period);
    setupcost = new Array<double,2>(product,period);
    setup = new Array<double,2>(product,period);
    price = new Array<double,2>(product,period);
    production = new Array<double,2>(product,period);
    storage = new Array<double,2>(product,period);
    ind = new Array<int,2>(product,period);
    constraint = new Array<double,1>(period);
    /** Import data from python object */
    profit = new shapeLSS(ObjToArray(demand),NULL);
    (*prod) = ObjToArray(_prod) -> copy();
    (*stor) = ObjToArray(_stor) -> copy();
    (*setup) = ObjToArray(_setup) -> copy();
    (*cons) = ObjToArray(_consumption) -> copy();
    (*constraint) = ObjToVector(_constraint) -> copy();
}

template <class data>
coreLSS<data>::coreLSS(const coreLSS& origin)
{
    /** Copy data */
    period = origin.period;
    product = origin.product;
    profit = new shapeLSS((*origin.profit));
    prod = new Array<double,2>((*origin.prod));
    stor = new Array<double,2>((*origin.stor));
    cons = new Array<double,2>((*origin.cons));
    setupcost = new Array<double,2>((*origin.setupcost));
    constraint = new Array<double,1>((*origin.constraint));
    /** Instanciate variables */
    setup = new Array<double,2>(product,period);
    price = new Array<double,2>(product,period);
    production = new Array<double,2>(product,period);
    storage = new Array<double,2>(product,period);
    ind = new Array<int,2>(product,period);
}

template <class data>
void coreLSS<data>::solve(void)
{
    Array<double,1> c(period);/**< cost function*/
    Array<double,1> f(period+1);/**< productective function*/
    Array<double,2> tprice(period,period);/**< local price */
    int t;/**< current time period */
    /** set variables */
    (*storage) = 0;
    (*production) = 0;
    price = initPrice();
    for(int j = 0; j < product;  j++)
    {
        t = 0;
        /** initiate price and cost */
        tprice(t,t) = computePrice(t,t,j);
        c(t) = computeCost(tprice,t,t,j);
        /** initiate criterium */
        f(t) = 0;
        f(t+1) = -c(t);
        /** result for the first period */
        (*ind)(j,t) = 0;
        (*price)(j,t) = tprice(t,(int)(*ind)(j,t));
        (*production)(j,t) = profit -> getDemand(j,t);
        for (t = 1; t < period;  t++)
        {
            for (int t0 = 0; t0 <= t; t0++)
            {
                /** compute price */
                tprice(t,t0) = computePrice(t,t0,j);
                /** compute cost */
                c(t0) = computeCost(tprice,t,t0,j);
            }
            /** find minimal criterium */
            f(t+1) = min(c(Range(0,t)) + f(Range(0,t)));
            /** update all variable for period t */
            (*ind)(j,t) = min(minIndex(c(Range(0,t))+ f(Range(0,t))));
            (*price)(j,t) = tprice(t,(int)(*ind)(j,t));
            (*production)(j,t) = 0.; /**< initiate production */
            (*production)(j,(*ind)(j,t)) += profit -> getDemand(j,t);
            if ( t > (*ind)(j,t) )
            {
                (*storage)(j,(*ind)(j,t)) += profit -> getDemand(j,t);
            }
        }
        (*setup) = where((*production) > 0,1,0);
    }
}

template <class data>
double coreLSS<data>::objective()
{
    Array<double,1> objective(product);
    for (int j = 0; j < product; j ++)
    {
        objective(j) = sum(
            (*profit -> getProfit())(j,Range::all())
            - (*prod)(j,Range::all())*(*production)(j,Range::all())
            - (*stor)(j,Range::all())*(*storage)(j,Range::all())
            - (*setup)(j,Range::all())*(*setupcost)(j,Range::all())
            );
    }
    return sum(objective);
}


template <class data>
void coreLSS<data>::initVariables()
{
    (*storage) = 0;
    (*production) = 0;
    (*price) = profit -> getNullDemandPrice() -> copy();
}

template <class data>
Array<double,2>* coreLSS<data>::initPrice()
{
    return profit -> getNullDemandPrice();
}

template <class data>
double coreLSS<data>::computeCost(Array<double,2> tprice, int t, int t0, int j)
{
    double cost = 0;
    for (int i = t0; i <= t; i++)
    {
        cost += ((*prod)(j,t0)
            + sum((*stor)(j,Range(t0,i-1)))
            - tprice(i,t0))
            * profit -> getDemand(j,t);
    }
    cost += (*setup)(j,t0);
    return cost;
}

template <class data>
double coreLSS<data>::computePrice(int t, int t0, int j)
{
    return (*price)(j,t);
}

template <class data> int coreLSS<data>::getProduct(){return product;}
template <class data> int coreLSS<data>::getPeriod(){return period;}
template <class data> data coreLSS<data>::getDemand(){return ArrayToObj<data>((*profit -> getDemand()));}
template <class data> data coreLSS<data>::getPrice(){return ArrayToObj<data>((*price));}
template <class data> data coreLSS<data>::getProd(){return ArrayToObj<data>((*production));}
template <class data> data coreLSS<data>::getHold(){return ArrayToObj<data>((*storage));}
template <class data> data coreLSS<data>::getSetup(){return ArrayToObj<data>((*setup));}
