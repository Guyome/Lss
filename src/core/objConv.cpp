#include <boost/python.hpp>
#include <vector>
#include "objConv.hpp"


typedef boost::python::list list;
using namespace blitz;
using namespace std;


template<> list ArrayToObj(const Array<double,2>& array)
{
    int period = array.columns();
    int product = array.rows();
    list row;
    list col;
    for (int j = 0; j < product; j ++)
    {
        col = list();
        for (int t = 0; t < period; t ++)
        {
            col.append( array(j,t) );
        }
        row.append( col );
    }
    
    return row;
}

template<> vector<vector<double> > ArrayToObj(const Array<double,2>& array)
{
    int period = array.columns();
    int product = array.rows();
    vector<vector<double> > tab (product,vector<double>(period));
    for (int j = 0; j < product; j ++)
    {
        for (int t = 0; t < period; t ++)
        {
            tab[j][t] = array(j,t) ;
        }
    }
    return tab;
}

Array<double,1>* ObjToVector (const list& list)
{
    int len = boost::python::extract<int>(list.attr("__len__")());/**< Get the list length */
    Array<double,1>* vector = new Array<double,1>(len);
    for (int i = 0; i < len; i++)
    {
        (*vector)(i) = (boost::python::extract<int>(list[i]));
    }
    return vector;
}

Array<double,1>* ObjToVector (const vector<double>& list)
{
    int len = list.size();/**< Get the list length */
    Array<double,1>* vector = new Array<double,1>(len);
    for (int i = 0; i < len; i++)
    {
        (*vector)(i) = list[i];
    }
    return vector;
}

Array<double,2>* ObjToArray(const list& list)
{
    int row = boost::python::extract<int>(list.attr("__len__")());/**< Get the row length */
    int col = boost::python::extract<int>(list[1].attr("__len__")());/**< Get the column length, all columns have the same size * */
    Array<double,2>* tab = new Array<double,2>(row,col);
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j ++)
        {
            (*tab)(i,j) = (boost::python::extract<int>(list[i][j]));
        }
    }
    return tab;
}

Array<double,2>* ObjToArray(const vector<vector<double> >& list)
{
    int row = list.size();/**< Get the row length */
    int col = list[1].size();/**< Get the column length, all columns have the same size */
    Array<double,2>* tab = new Array<double,2>(row,col);
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j ++)
        {
            (*tab)(i,j) = list[i][j];
        }
    }
    return tab;
}
