#include "network.h"
#include "random.h"
#include <string>
#include <iostream>
using namespace std;

RandomNumbers Rand;

void Network::resize(const size_t & size)
{
	values.clear();
	values.resize(size);
		
	Rand.normal(values,0,1);
	
}
    

bool Network::  add_link(const size_t& a , const size_t& b)
{
	if (a == b or a >= values.size() or b>= values.size())  {
		return false;}
	for ( auto link :  neighbors(a))if( b== link){
		return false;
	}
		
	

		links.insert( pair<size_t,size_t> ( a, b));
		links.insert( pair<size_t,size_t> ( b, a));
		return true;

}

size_t Network:: random_connect(const double& nombre)
{
	links.clear();
	for ( size_t i(0); i<values.size(); i++){
		int newlinks(Rand.poisson(nombre));
		vector <int> blc (values.size());
		Rand.uniform_int(blc,0,values.size()-1); 
		
		for ( int j(0); j< newlinks; j++){
			add_link( i, blc[j]);
			}
	}
	return links.size() / 2;
}


size_t Network:: set_values(const vector<double>& newvalues)
{
	
	
	if ( newvalues.size() <= size() ){
		for (size_t j(0); j < newvalues.size();++j){
		values.erase(values.begin()+ j);
		values.insert(values.begin()+j ,newvalues.begin()+j , newvalues.begin()+j+1);
 	}
		return newvalues.size();

}	else {
		for (size_t j(0); j < size();++j){
			values.erase(values.begin()+ j);
			values.insert(values.begin()+j ,newvalues.begin()+j,newvalues.begin() +j+1);
			}
		}
		return values.size();
}

size_t Network:: size() const
{
	return values.size();
}

size_t Network:: degree(const size_t &_n) const
{

	return links.count(_n);

}

double Network:: value(const size_t &_n) const
{
	return values[_n];
}

vector<double> Network:: sorted_values() const
{
	 vector<double> listecopy= values;
	 sort(listecopy.begin(),listecopy.end());
	 reverse(listecopy.begin(),listecopy.end());
	 return listecopy;
	 
}

vector<size_t> Network:: neighbors(const size_t&_n) const
{	vector<size_t> neighbor;
	for (auto link : links) {
	if(link.first == _n){ 
		neighbor.push_back(link.second);
		}}
	return neighbor;
		
}



