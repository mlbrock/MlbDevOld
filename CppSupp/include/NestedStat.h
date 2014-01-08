/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	C++ Support Library Include File														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include and implementation file for nested statistics
								of arbitrarily-nested depth.

	Revision History	:	1998-05-19 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1998 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef HH__MLB__CPPSupp__NestedStat_h__HH

#define HH__MLB__CPPSupp__NestedStat_h__HH	1

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
# include <map>
# include <set>
# if _MSC_VER >= 1300
#  pragma warning(default:4217 4251 4555)
# endif /* # if _MSC_VER >= 1300 */
# pragma warning(default:4018 4100 4146 4244 4245 4511 4512 4663)
#else
# include <map>
# include <set>
#endif /* #ifdef _Windows */

/*	***********************************************************************	*/

namespace MLB {

namespace CPPSupp {

/*
	Required interface for the class 'DataType':

		DataType();
		DataType(const DataType &src);
		DataType operator =  (const DataType &other);
		DataType operator +  (const DataType &lhs, const DataType &rhs); --- static
		DataType operator += (const DataType &other);
		DataType operator == (const DataType &other) const;

	Required interface for the class 'SelectorType':

		SelectorType(); // For std::accumulate()
		SelectorType(const SelectorType &src);
		SelectorType operator =  (const SelectorType &other);
		bool IsSelected(const SelectorType &other) const;
*/
/*	***********************************************************************	*/
template <class SelectorType, class DataType>
	class NestedStat {

	public:

		/*	***********************************************************
			***********************************************************
			Constructors and destructor . . .
			***********************************************************	*/
		NestedStat() :
			stat_data_(), selector_() { }
		NestedStat(const SelectorType &selector) :
			selector_(selector), stat_data_() { }
		NestedStat(const DataType &stat_data) :
			selector_(), stat_data_(stat_data) { }
		NestedStat(const SelectorType &selector, const DataType &stat_data) :
			selector_(selector), stat_data_(stat_data) { }
		~NestedStat() { }
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			The copy constructor . . .
			***********************************************************	*/
		NestedStat(const NestedStat &src) :
			stat_data_(src.stat_data_), selector_(src.selector_) { }
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			The assigment operator . . .
			***********************************************************	*/
		NestedStat& operator = (const NestedStat &src) {
			stat_data_ = src.stat_data_;
			selector_  = src.selector_;
			return(*this);
		}
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			The less than operator . . . forwards to the selector . . .
			***********************************************************	*/
		bool operator < (const NestedStat &other) const {
			return(selector_ < other.selector_);
		}
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			The addition assigment operators . . .
			***********************************************************	*/
		NestedStat &operator += (const NestedStat &other) {
			if (selector_.IsSelected(other.selector_))
				*this = *this + other;
			return(*this);
		}
		NestedStat &operator += (const DataType &stat_data) {
			stat_data_ += stat_data;
			return(*this);
		}
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			The addition operator is available to all . . .
			***********************************************************	*/
		friend NestedStat operator + (const NestedStat &lhs,
			const NestedStat &rhs) {
			return((lhs.selector_.IsSelected(rhs.selector_)) ?
				NestedStat(lhs.selector_, lhs.stat_data_ + rhs.stat_data_) :
				lhs);
		}
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			***********************************************************	*/
		DataType SelectData(const SelectorType &selector) const {
			DataType tmp_data;
			if (selector.IsSelected(selector_))
				tmp_data += stat_data_;
			return(tmp_data);
		}
		/*	***********************************************************	*/

		friend std::ostream& operator << (std::ostream &o_str,
			const NestedStat &datum) {
			o_str << datum.selector_ << "=" << datum.stat_data_;
			return(o_str);
		}

		friend std::ostream& operator << (std::ostream &o_str,
			const std::pair<const SelectorType, DataType> &datum) {
			o_str << datum.first << "=" << datum.second;
			return(o_str);
		}

		std::pair<const SelectorType, DataType> operator +
			(const std::pair<const SelectorType, DataType> &other) const {
			return(std::make_pair(SelectorType(selector_ + other.first),
				DataType(stat_data_ + other.second)));
		}
		std::pair<const SelectorType, DataType> operator =
			(const std::pair<const SelectorType, DataType> &src) {
			selector_  = src.first;
			stat_data_ = src.second;
			return(std::make_pair<const SelectorType, DataType>(selector_,
				stat_data_));
		}

		/*	***********************************************************
			***********************************************************
			***********************************************************	*/
		             SelectorType &GetSelector() { return(selector_); }
		static const SelectorType &GetSelector(const NestedStat<class SelectorType, class DataType> &src) {
			return(src.GetSelector());
		}
		             DataType     &GetData() { return(stat_data_); }
		static const DataType     &GetData(const NestedStat<class SelectorType, class DataType> &src) {
			return(src.GetData());
		}
/*
		       const SelectorType &GetSelector() const { return(selector_); }
		static const SelectorType &GetSelector(const NestedStat<class SelectorType, class DataType> &src) {
			return(src.GetSelector());
		}
		       const DataType     &GetData() const { return(stat_data_); }
		static const DataType     &GetData(const NestedStat<class SelectorType, class DataType> &src) {
			return(src.GetData());
		}
*/
		/*	***********************************************************	*/

	protected:

		/*	***********************************************************
			***********************************************************
			Data is protected to let derived classes get at it . . . see
			'NestedStatDefault' for an example . . .
			***********************************************************	*/
		SelectorType selector_;
		DataType     stat_data_;
		/*	***********************************************************	*/
};
/*	***********************************************************************	*/

/*	***********************************************************************	*/
template <class SelectorType, class DataType>
	class NestedStatMap {

	public:

		NestedStatMap() : coll_data_() { }
		template <class AnyIter> NestedStatMap(AnyIter first, AnyIter last) :
			coll_data_() {
			Populate(iter_first, iter_last);
		}

		NestedStatMap(const NestedStatMap &other) :
			coll_data_(other.coll_data_) { }

		template <class AnyIter> void Populate(AnyIter first, AnyIter last) {
			AnyIter iter = iter_first;
			while (iter != iter_last) {
				coll_data.insert(*iter, DataType());
				iter++;
			}
		}

		std::map<SelectorType, DataType> coll_data;
};
/*	***********************************************************************	*/

/*	***********************************************************************	*/
template <class SelectorType, class DataType,
	class ContainerType = std::set<NestedStat<SelectorType, DataType> > >
	class NestedStatContainer : public ContainerType {

	public:

		NestedStatContainer() { }
		NestedStatContainer(const NestedStatContainer &other) {
			this->swap(other);
		}
		explicit NestedStatContainer(
			const NestedStat<SelectorType, DataType> &src) :
			ContainerType(1, &src) { }
};
/*	***********************************************************************	*/

} // namespace CPPSupp

} // namespace MLB

#endif // #ifndef HH__MLB__CPPSupp__NestedStat_h__HH

