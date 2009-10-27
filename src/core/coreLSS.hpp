#ifndef H_CORE_H
#define H_CORE_H

#include "shapeLSS.hpp"

/**
 * @brief This class is an virtual class who define
 * lot-sizing problem in general. computeCost(int t, int t0, int j),
 * computePrice(int t, int t0, int j) and in initVariables()
 * must be specified in further classes in order to solve LSP
 * by dynamic programming methods.
 * @author Guillaume Lanquepin <guillaume@himolde.no>
 * @version 0.1
 */
template <class data> class coreLSS
{
    protected:
        /**@name Data */
        //@{
        int period;/**< the number of time period */
        int product;/**< the number of product */
        shapeLSS* profit;/**< Demand and profit managed by an specialized class*/
        blitz::Array<double,2>* prod;/**< Production cost */
        blitz::Array<double,2>* stor;/**< Holding cost */
        blitz::Array<double,2>* cons;/**< Consumption of resource per product */
        blitz::Array<double,2>* setupcost;/**< Setup cost */
        blitz::Array<double,1>* constraint;/**< Production constraint per time period */
        //@}

        /**@name Variable */
        //@{
        blitz::Array<double,2>* setup;/**< Setup structure */
        blitz::Array<double,2>* price;/**< Price */
        blitz::Array<double,2>* production;/**< Production */
        blitz::Array<double,2>* storage;/**< Holding */
        blitz::Array<int,2>* ind;/**< Index structure from Thomas's algorithm */
        //@}
       
        void initVariables();/**< Initiate all variables */
        blitz::Array<double,2>* initPrice();/**< Initiate price in solve() (pure abstract) */
        /** Compute cost in solve() (pure abstract) */
        double computeCost(blitz::Array<double,2> tprice,int t, int t0, int j);
        double computePrice(int t, int t0, int j);/**< Compute Price in solve() (pure abstract)*/
    public:
        /** Default constructor 
        * @param demand the slope of demand function
        * @param prod the production cost
        * @param stor the holding cost
        * @param consumption the resource consumption per product
        * @param setup the setup cost
        * @param constraint the production constraint per time period
        * @param period the number of time period
        * @param product the number of goods */
        coreLSS(data demand, data prod,
                    data stor, data consumption,
                    data setup, data constraint,
                    int period, int product);
        /** Copy constructor 
        * @param origin ther original HeurClsp object*/
        coreLSS(const coreLSS& origin);
        //virtual ~coreLSS();/**< Default destructor */
        double objective();/**< Returns the objective value */
        void solve();/**< Methods to solve unconstrained problem */
        
        /** @name Informative methods
        * Methods to obtain variables and various quality information; */
        //@{
        int getProduct();/**< Returns the number of product */
        int getPeriod();/**< Returns the number of time period */
        data getDemand();/**< Returns the current demand values*/
        data getPrice();/**< Returns the current price values*/
        data getProd();/**< Returns the current production values*/
        data getHold();/**< Returns the current holding values*/
        data getSetup();/**< Returns the current setup values*/
        //@}
};
#endif
