/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	C++ Support Library Test Harness Module File										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Test harness module for template class NestedStat<>.

	Revision History	:	1998-05-19 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1998 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Required include files . . .															*/
/*	***********************************************************************	*/

#ifdef _Windows
# pragma warning(disable:4710 4786)
# if _MSC_VER >= 1300
#  pragma warning(disable:4217 4251 4555)
# endif /* # if _MSC_VER >= 1300 */
# pragma warning(disable:4018 4100 4146 4244 4245 4511 4512 4663)
# include <algorithm>
# include <iomanip>
# include <iostream>
# include <limits>
# include <numeric>
# include <sstream>
# include <vector>
# ifndef min
#  define min _cpp_min
# endif /* # ifndef min */
# ifndef max
#  define max _cpp_min
# endif /* # ifndef min */
# if _MSC_VER >= 1300
#  pragma warning(default:4217 4251 4555)
# endif /* # if _MSC_VER >= 1300 */
# pragma warning(default:4018 4100 4146 4244 4245 4511 4512 4663)
#else
# include <algorithm>
# include <iomanip>
# include <iostream>
# include <limits>
# include <numeric>
# include <sstream>
# include <vector>
#endif /* #ifdef _Windows */

#include "InlineContainer.h"

#include "NestedStat.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
typedef enum {
	SOCKICPT_SIDE_NEAR = 1,
	SOCKICPT_SIDE_FAR  = 2,
	SOCKICPT_SIDE_BOTH = (SOCKICPT_SIDE_NEAR | SOCKICPT_SIDE_FAR)
} SOCKICPT_SIDE;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
typedef enum {
	SOCKICPT_OPER_RECV = 1,
	SOCKICPT_OPER_SEND = 2,
	SOCKICPT_OPER_BOTH = (SOCKICPT_OPER_RECV | SOCKICPT_OPER_SEND)
} SOCKICPT_OPER;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifdef _Windows
#include <climits>
typedef __int64 SOCKICPT_Counter;
// *** Windows has a broken output for this type . . .
std::ostream& operator << (std::ostream &o_str, SOCKICPT_Counter datum) {
	char buffer[(sizeof(datum) * CHAR_BIT) + 1]; // More than enough . . .
	sprintf(buffer, "%I64u", datum);
	o_str << buffer;
	return(o_str);
}
#elif SOCKICPT_HAS_NO_LONG_LONG
typedef double SOCKICPT_Counter;
#else
typedef unsigned long long SOCKICPT_Counter;
#endif /* #ifdef _Windows */
/*	***********************************************************************	*/

/*	***********************************************************************	*/
class SOCKICPT_StatSelect {

	public:

		SOCKICPT_StatSelect(SOCKICPT_SIDE side, SOCKICPT_OPER oper) :
			side_(side), oper_(oper) { }
		SOCKICPT_StatSelect(const SOCKICPT_StatSelect &other) :
			side_(other.side_), oper_(other.oper_) { }
		const SOCKICPT_StatSelect operator = (const SOCKICPT_StatSelect &other){
			side_ = other.side_;
			oper_ = other.oper_;
			return(*this);
		}

		bool IsSelected(const SOCKICPT_StatSelect &other) const {
			return((side_ & other.side_) && (oper_ & other.oper_));
		}

		bool operator < (const SOCKICPT_StatSelect &other) const {
			return(((this->side_ < other.side_) || ((this->side_ == other.side_) &&
				(this->oper_ < other.oper_))) ? true : false);
		}

		friend std::ostream& operator << (std::ostream &o_str,
			SOCKICPT_SIDE datum) {
			o_str <<	((datum == SOCKICPT_SIDE_NEAR) ? "NEAR" :
				((datum == SOCKICPT_SIDE_FAR)  ? "FAR " :
				((datum == SOCKICPT_SIDE_BOTH) ? "BOTH" : "????")));
			return(o_str);
		}
		friend std::ostream& operator << (std::ostream &o_str,
			SOCKICPT_OPER datum) {
			o_str <<	((datum == SOCKICPT_OPER_RECV) ? "RECV" :
				((datum == SOCKICPT_OPER_SEND) ? "SEND" :
				((datum == SOCKICPT_OPER_BOTH) ? "BOTH" : "????")));
			return(o_str);
		}
		friend std::ostream& operator << (std::ostream &o_str,
			const SOCKICPT_StatSelect &datum) {
			o_str << "{ " << datum.side_ << ", " << datum.oper_ << " }";
			return(o_str);
		}

		/*	***********************************************************
			***********************************************************
			Used within 'std::accumulate()' so that the returned stats
			contain a selector with the OR'ed flags. May not make sense
			for all implementations . . .
			***********************************************************	*/
		SOCKICPT_StatSelect operator + (const SOCKICPT_StatSelect &other) const {
			return((this->IsSelected(other)) ?
				(SOCKICPT_StatSelect(((SOCKICPT_SIDE) (side_ | other.side_)),
				((SOCKICPT_OPER) (oper_ | other.oper_)))) : *this);
		}
		/*	***********************************************************	*/

	private:

		SOCKICPT_SIDE side_;
		SOCKICPT_OPER oper_;
};
/*	***********************************************************************	*/

/*	***********************************************************************	*/
class SOCKICPT_StatData {

	public:

		explicit SOCKICPT_StatData(SOCKICPT_Counter action_count = 0,
			SOCKICPT_Counter action_bytes = 0, unsigned int min_bytes = UINT_MAX,
			unsigned int max_bytes = 0) :
			action_count_(action_count), action_bytes_(action_bytes),
			min_bytes_(min_bytes), max_bytes_(max_bytes) { }

		SOCKICPT_Counter GetCount() const {
			return(action_count_);
		}
		SOCKICPT_Counter GetBytes() const {
			return(action_bytes_);
		}
		double           GetAverage() const {
			return((action_count_) ?
				(((double) action_bytes_) / ((double) action_count_)) : 0.0);
		}
		unsigned int     GetMinimum() const {
			return((min_bytes_ != UINT_MAX) ? min_bytes_ : 0);
		}
		unsigned int     GetMaximum() const {
			return(max_bytes_);
		}

		friend SOCKICPT_StatData operator + (const SOCKICPT_StatData &lhs,
			const SOCKICPT_StatData &rhs) {
			return(SOCKICPT_StatData(lhs.action_count_ + rhs.action_count_,
				lhs.action_bytes_ + rhs.action_bytes_,
				std::min(lhs.min_bytes_, rhs.min_bytes_),
				std::max(lhs.max_bytes_, rhs.max_bytes_)));
		}

		SOCKICPT_StatData &operator += (const SOCKICPT_StatData &other) {
			*this = *this + other;
			return(*this);
		}

		SOCKICPT_StatData operator + (unsigned int action_bytes) const {
			return(*this + SOCKICPT_StatData(1, action_bytes));
		}

		SOCKICPT_StatData operator += (unsigned int action_bytes) {
			*this += SOCKICPT_StatData(1, action_bytes);
			return(*this);
		}

		friend std::ostream& operator << (std::ostream &o_str,
			const SOCKICPT_StatData &datum) {
			o_str <<
				std::setw(10) << datum.GetCount() << " " <<
				std::setw(10) << datum.GetBytes() << " " <<
				std::setw(10) << datum.GetMinimum() << " " <<
				std::setw(10) << datum.GetMaximum() << " " <<
				std::setw(20) << std::fixed << std::setprecision(6) <<
					std::showpoint << datum.GetAverage();
			return(o_str);
		}

	private:

		SOCKICPT_Counter action_count_;
		SOCKICPT_Counter action_bytes_;
		unsigned int     min_bytes_;
		unsigned int     max_bytes_;
};
/*	***********************************************************************	*/

using namespace MLB::CPPSupp;
using namespace MLB::CPPSupp::STLSupp;

/*	***********************************************************************	*/
typedef NestedStat<SOCKICPT_StatSelect, SOCKICPT_StatData> NS;
typedef std::map<SOCKICPT_StatSelect, SOCKICPT_StatData>   NSMap;
/*	***********************************************************************	*/

#if 1
namespace std {
ostream& operator << (ostream &o_str,
	const NSMap::value_type &datum) {
	o_str << datum.first << "=" << datum.second;
	return(o_str);
}
}; // namespace std
#endif /* #if 0 */

/*	***********************************************************************	*/
static void TEST_ApplyStats(NSMap &stat_map);
static void TEST_AccumulateStats(NSMap &stat_map);
static int  TEST_Set();
static int  TEST_Map();
static void TEST_GetNestedMap(NSMap &stat_map);

template <class ContainerType>
	static void TEST_PopulateContainer(ContainerType &the_cont);
template <class ContainerType>
	static void TEST_AccumulateStatsForContainer(ContainerType &the_cont);
template <class ContainerType>
	static void TEST_OutputContainer(const ContainerType &the_cont);
static void TEST_GetPermutation(std::vector<SOCKICPT_SIDE> side_vec,
	std::vector<SOCKICPT_OPER> oper_vec,
	std::vector<NestedStat<SOCKICPT_StatSelect, SOCKICPT_StatData> > &out_perm);
/*	***********************************************************************	*/

#include <utility>

/*	***********************************************************************	*/
int main()
{
	int   return_code = EXIT_SUCCESS;
	NSMap stat_map;

//	return_code = TEST_Set();
	return_code = TEST_Map();

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static void TEST_ApplyStats(NSMap &stat_map)
{
	stat_map[SOCKICPT_StatSelect(SOCKICPT_SIDE_NEAR, SOCKICPT_OPER_RECV)] +=
		1;
	stat_map[SOCKICPT_StatSelect(SOCKICPT_SIDE_NEAR, SOCKICPT_OPER_SEND)] +=
		101;
	stat_map[SOCKICPT_StatSelect(SOCKICPT_SIDE_FAR,  SOCKICPT_OPER_RECV)] +=
		1001;
	stat_map[SOCKICPT_StatSelect(SOCKICPT_SIDE_FAR,  SOCKICPT_OPER_SEND)] +=
		10001;

	TEST_OutputContainer(stat_map);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static void TEST_AccumulateStats(NSMap &stat_map)
{
	std::cout << std::accumulate(stat_map.begin(), stat_map.end(),
		NS(SOCKICPT_StatSelect(SOCKICPT_SIDE_BOTH, SOCKICPT_OPER_BOTH))) <<
		std::endl;
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static int TEST_Set()
{
	int   return_code = EXIT_SUCCESS;
	std::set<NestedStat<SOCKICPT_StatSelect, SOCKICPT_StatData> > the_cont;
	std::set<NestedStat<SOCKICPT_StatSelect, SOCKICPT_StatData> >::iterator iter;

	TEST_PopulateContainer(the_cont);

	if ((iter = the_cont.find(SOCKICPT_StatSelect(SOCKICPT_SIDE_NEAR,
		SOCKICPT_OPER_RECV))) != the_cont.end())
		iter->GetData() += 1;
	if ((iter = the_cont.find(SOCKICPT_StatSelect(SOCKICPT_SIDE_NEAR,
		SOCKICPT_OPER_SEND))) != the_cont.end())
		iter->GetData() += 101;
	if ((iter = the_cont.find(SOCKICPT_StatSelect(SOCKICPT_SIDE_FAR, 
		SOCKICPT_OPER_RECV))) != the_cont.end())
		iter->GetData() += 1001;
	if ((iter = the_cont.find(SOCKICPT_StatSelect(SOCKICPT_SIDE_FAR, 
		SOCKICPT_OPER_SEND))) != the_cont.end())
		iter->GetData() += 10001;

	TEST_OutputContainer(the_cont);
	TEST_AccumulateStatsForContainer(the_cont);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static int TEST_Map()
{
	int   return_code = EXIT_SUCCESS;
	NSMap stat_map;

	TEST_GetNestedMap(stat_map);
	TEST_ApplyStats(stat_map);
	TEST_AccumulateStatsForContainer(stat_map);
//	TEST_AccumulateStats(stat_map);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static void TEST_GetNestedMap(NSMap &stat_map)
{
	SOCKICPT_SIDE side_list[] = { SOCKICPT_SIDE_NEAR, SOCKICPT_SIDE_FAR };
	SOCKICPT_OPER oper_list[] = { SOCKICPT_OPER_RECV, SOCKICPT_OPER_SEND };

	do {
		do {
			stat_map[SOCKICPT_StatSelect(*side_list, *oper_list)] =
				SOCKICPT_StatData();
std::cout << "MAKE MAP:[" << *side_list << ", " << *oper_list << "]" << std::endl;
		} while (std::next_permutation(oper_list,
			oper_list + (sizeof(oper_list) / sizeof(oper_list[0]))));
	} while (std::next_permutation(side_list,
		side_list + (sizeof(side_list) / sizeof(side_list[0]))));

	TEST_OutputContainer(stat_map);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
template <class ContainerType>
	static void TEST_PopulateContainer(ContainerType &the_cont)
{
	std::vector<NestedStat<SOCKICPT_StatSelect, SOCKICPT_StatData> > permutation;

	TEST_GetPermutation(MakeInlineVector(SOCKICPT_SIDE_NEAR)(SOCKICPT_SIDE_FAR),
		MakeInlineVector(SOCKICPT_OPER_RECV)(SOCKICPT_OPER_SEND), permutation);

	std::copy(permutation.begin(), permutation.end(),
		std::inserter(the_cont, the_cont.begin()));
//	the_cont.insert(permutation.begin(), permutation.end());
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
template <class ContainerType>
	static void TEST_AccumulateStatsForContainer(ContainerType &the_cont)
{
	std::vector<NestedStat<SOCKICPT_StatSelect, SOCKICPT_StatData> > permutation;

	TEST_GetPermutation(MakeInlineVector(SOCKICPT_SIDE_NEAR)(SOCKICPT_SIDE_FAR)
		(SOCKICPT_SIDE_BOTH), MakeInlineVector(SOCKICPT_OPER_RECV)
		(SOCKICPT_OPER_SEND)(SOCKICPT_OPER_BOTH), permutation);

	for (std::vector<NestedStat<SOCKICPT_StatSelect, SOCKICPT_StatData> >::iterator iter = permutation.begin();
		iter < permutation.end(); iter++)
		std::cout << std::accumulate(the_cont.begin(), the_cont.end(),
			ContainerType::value_type(*iter)) << std::endl;
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
template <class ContainerType>
	static void TEST_OutputContainer(const ContainerType &the_cont)
{
	std::cout << std::string(14, '-') << '-' <<
		std::string(10, '-') << ' ' <<
		std::string(10, '-') << ' ' <<
		std::string(10, '-') << ' ' <<
		std::string(10, '-') << ' ' <<
		std::string(20, '-') << std::endl;
	std::copy(the_cont.begin(), the_cont.end(),
		std::ostream_iterator<ContainerType::value_type>(std::cout, "\n"));
	std::cout << std::string(14, '-') << '-' <<
		std::string(10, '-') << ' ' <<
		std::string(10, '-') << ' ' <<
		std::string(10, '-') << ' ' <<
		std::string(10, '-') << ' ' <<
		std::string(20, '-') << std::endl;
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static void TEST_GetPermutation(std::vector<SOCKICPT_SIDE> side_vec,
	std::vector<SOCKICPT_OPER> oper_vec,
	std::vector<NestedStat<SOCKICPT_StatSelect, SOCKICPT_StatData> > &out_perm)
{
	// NOT the place for 'std::next_permutation()' . . .
	for (std::vector<SOCKICPT_SIDE>::iterator side_iter = side_vec.begin();
		side_iter < side_vec.end(); side_iter++) {
		for (std::vector<SOCKICPT_OPER>::iterator oper_iter = oper_vec.begin();
			oper_iter < oper_vec.end(); oper_iter++)
			out_perm.push_back(SOCKICPT_StatSelect(*side_iter, *oper_iter));
	}

	TEST_OutputContainer(out_perm);
}
/*	***********************************************************************	*/


