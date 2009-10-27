#ifndef H_SHAPE_H
#define H_SHAPE_H

#include <blitz/array.h>

/**
 * @brief This class defines the demand shape as polynomial.
 * It is mainly an abstract class and, here, demand
 * is an scalar, but an heritage class can define 
 * demand an an linear function.
 * @author Guillaume Lanquepin <guillaume@himolde.no>
 * @version 0.1
 */
class shapeLSS
{
    protected:
        blitz::Array<double,2>* intercept;/**< The current demand are scalar for each product and time period*/
        const blitz::Array<double,2>* price;/**< price vector (basically the tabular defined in glsp.cpp)*/
    public:
        shapeLSS(blitz::Array<double,2>* coefficient, blitz::Array<double,2>* price);/**< Default constructor */
        shapeLSS(const shapeLSS& origin);/** Copy constructor */
        virtual double getDemand(int j, int t);/**< Methods to get demand value*/
        virtual double getDemand(blitz::Array<double,2>* currentPrice,int j, int t);/**< Methods to get demand value*/
        virtual blitz::Array<double,2>* getProfit();/**< Methods to get profit array*/
        virtual blitz::Array<double,2>* getDemand();/**< Methods to get demand array*/
};
#endif
