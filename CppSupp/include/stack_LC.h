/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	STL Support Library Include File														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for stack_LC<>.

	Revision History	:	1998-04-08 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1998 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef HH__MLB__CPPSupp__STLSupp__stack_LC_h__HH

#define HH__MLB__CPPSupp__STLSupp__stack_LC_h__HH	1

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
# include <deque>
# include <vector>
# include <limits>
# if _MSC_VER >= 1300
#  pragma warning(default:4217 4251 4555)
# endif /* # if _MSC_VER >= 1300 */
# pragma warning(default:4018 4100 4146 4244 4245 4511 4512 4663)
#else
# include <deque>
# include <vector>
# include <limits>
#endif /* #ifdef _Windows */

#include "ScopedLock.h"

#include "NullLock.h"

/*	***********************************************************************	*/

namespace MLB {

namespace CPPSupp {

namespace STLSupp {

/*	***********************************************************************	*/
template <class DataType, class LockType = MLB::CPPSupp::NullLock,
	class ContainerType = std::deque<DataType> >
	class stack_LC {

	private:

		//	////////////////////////////////////////////////////////////////
		//	////////////////////////////////////////////////////////////////
		// Some useful internal typedefs from which to work . . .
		//	////////////////////////////////////////////////////////////////
		typedef ContainerType                                       FundCollType;
		typedef stack_LC<DataType, LockType, ContainerType>         ThisCollType;
		//	////////////////////////////////////////////////////////////////

	public:

		//	////////////////////////////////////////////////////////////////
		//	////////////////////////////////////////////////////////////////
		//	Externally available for use in scoped locking:
		//
		//	Where there exists a collection:
		//		stack_LC<SomeType> some_instance;
		//
		//	Lock the collection with:
		//		MyLockReader my_r_lock(some_instance);	//	Locked for reading.
		//		MyLockWriter my_w_lock(some_instance);	//	Locked for writing.
		//	////////////////////////////////////////////////////////////////
		typedef ScopedLockReader<ThisCollType>                  MyLockReader;
		typedef ScopedLockWriter<ThisCollType>                  MyLockWriter;
		//	////////////////////////////////////////////////////////////////

		//	////////////////////////////////////////////////////////////////
		//	////////////////////////////////////////////////////////////////
		// Available for use by the outside world...
		//	////////////////////////////////////////////////////////////////
		typedef typename FundCollType                           container_type;
		typedef typename FundCollType::allocator_type           allocator_type;
		typedef typename FundCollType::value_type               value_type;
		typedef typename FundCollType::size_type                size_type;
		typedef typename FundCollType::difference_type          difference_type;
		//	////////////////////////////////////////////////////////////////

	private:

		//	////////////////////////////////////////////////////////////////
		//	////////////////////////////////////////////////////////////////
		// Some internal short names...
		//	////////////////////////////////////////////////////////////////
		typedef typename container_type                          ContType;
		typedef typename allocator_type                          AllocatorType;
		typedef typename value_type                              ValueType;
		typedef typename size_type                               SizeType;
		typedef typename difference_type                         DiffType;
		//	////////////////////////////////////////////////////////////////

	public:

		/*	***********************************************************
			***********************************************************
			Core constructors and the destructor . . .
			***********************************************************	*/
		stack_LC() :
			coll_lock(), coll_data() { }
		stack_LC(const container_type &source_container) :
			coll_lock(), coll_data(source_container) { }
		virtual ~stack_LC() {
			try {
				ClearData();
			}
			catch (...) { }
		}
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			The copy constructor . . .
			***********************************************************	*/
		stack_LC(const ThisCollType &in_coll) :
			coll_lock(), coll_data() {
			MyLockReader in_lock(in_coll);
			ContainerType tmp_coll(in_coll.coll_data);
			std::swap(coll_data, tmp_coll);
		}
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			The assignment constructor . . .
			***********************************************************	*/
		ThisCollType& operator=(const ThisCollType &in_coll) {
			if (this != &in_coll) {
				BaseCollType tmp_coll(in_coll.coll_data);
				std::swap(coll_data, tmp_coll);
			}
			return(*this);
		}
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Specialized container methods . . .
			***********************************************************	*/
		bool PopWithGet(DataType &out_data) {
			MyLockWriter my_lock(*this);
			SizeType coll_count;
			if (coll_data.empty())
				return(false);
			out_data = coll_data.back();
			pop();
			return(true);
		}
		bool Peek(DataType &out_data) {
			MyLockReader my_lock(*this);
			if (coll_data.empty())
				return(false);
			out_data = coll_data.back();
			return(true);
		}
		unsigned int ClearData(unsigned int max_clear =
			std::numeric_limits<unsigned int>::max()) {
			SizeType     cleared_count = 0;
			MyLockWriter my_lock(*this);
			while ((!coll_data.empty()) && max_clear--) {
				pop();
				++cleared_count;
			}
			return(cleared_count);
		}
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Locking container core methods . . .
			***********************************************************	*/
		bool       Empty() const {
			MyLockReader my_lock(*this);
			return(empty());
		}
		void       Pop() {
			MyLockWriter my_lock(*this);
			pop();
		}
		void       Push(const DataType &in_data) {
			MyLockWriter my_lock(*this);
			push(in_data);
		}
		SizeType   Size() const {
			MyLockReader my_lock(*this);
			return(size());
		}
		ValueType &Top() {
			MyLockReader my_lock(*this);
			return(top());
		}
		const ValueType &Top() const {
			MyLockReader my_lock(*this);
			return(top());
		}
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Non-locking container core methods . . .
			***********************************************************	*/
		bool       empty() const {
			return(coll_data.empty());
		}
		void       pop() {
			coll_data.pop_back();
		}
		void       push(const DataType &in_data) {
			coll_data.push_back(in_data);
		}
		SizeType   size() const {
			return(coll_data.size());
		}
		ValueType &top() {
			return(coll_data.back());
		}
		const ValueType &top() const {
			return(coll_data.top());
		}
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Container data accessors . . .
			***********************************************************	*/
		ContainerType GetData() const {
			MyLockReader my_lock(*this);
			return(coll_data);
		}
		void         GetData(ContainerType &out_coll) const {
			MyLockReader my_lock(*this);
			out_coll = coll_data;
		}
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Raw container data accessors. Locking must be managed by
			the caller for thread-safety. Use at your own risk . . .
			***********************************************************	*/
		ContainerType       &GetDataRef()       { return(coll_data);  }
		const ContainerType &GetDataRef() const { return(coll_data);  }
		ContainerType       *GetDataPtr()       { return(&coll_data); }
		const ContainerType *GetDataPtr() const { return(&coll_data); }
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Raw container lock accessors. It's generally better to use
			the scoped locking idiom . . .
			***********************************************************	*/
		LockType       &GetLockRef()       { return(coll_lock);  }
		const LockType &GetLockRef() const { return(coll_lock);  }
		LockType       *GetLockPtr()       { return(&coll_lock); }
		const LockType *GetLockPtr() const { return(&coll_lock); }
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			The external comparison operators . . .
			***********************************************************	*/
		friend bool operator==(const ThisCollType &lhs, const ThisCollType &rhs) {
			MyLockReader lhs_lock(lhs);
			MyLockReader rhs_lock(rhs);
			return(lhs.coll_data == rhs.coll_data);
		}
		friend bool operator!=(const ThisCollType &lhs, const ThisCollType &rhs) {
			MyLockReader lhs_lock(lhs);
			MyLockReader rhs_lock(rhs);
			return(lhs.coll_data != rhs.coll_data);
		}
		friend bool operator<(const ThisCollType &lhs, const ThisCollType &rhs) {
			MyLockReader lhs_lock(lhs);
			MyLockReader rhs_lock(rhs);
			return(lhs.coll_data < rhs.coll_data);
		}
		friend bool operator>(const ThisCollType &lhs, const ThisCollType &rhs) {
			MyLockReader lhs_lock(lhs);
			MyLockReader rhs_lock(rhs);
			return(lhs.coll_data > rhs.coll_data);
		}
		friend bool operator<=(const ThisCollType &lhs, const ThisCollType &rhs) {
			MyLockReader lhs_lock(lhs);
			MyLockReader rhs_lock(rhs);
			return(lhs.coll_data <= rhs.coll_data);
		}
		friend bool operator>=(const ThisCollType &lhs, const ThisCollType &rhs) {
			MyLockReader lhs_lock(lhs);
			MyLockReader rhs_lock(rhs);
			return(lhs.coll_data >= rhs.coll_data);
		}
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Locking primitives are made available here for use in
			derived classes. But implementors should prefer the scoped
			locking idiom . . .
			***********************************************************	*/
		int LockReader() const { return(coll_lock.LockReader()); }
		int LockWriter() const { return(coll_lock.LockWriter()); }
		int Unlock() const { return(coll_lock.Unlock()); }
		/*	***********************************************************	*/

	private:

		/*	***********************************************************
			***********************************************************
			Data members . . .
			***********************************************************	*/
		mutable LockType coll_lock;
		ContainerType    coll_data;
		/*	***********************************************************	*/
};
/*	***********************************************************************	*/

//	////////////////////////////////////////////////////////////////////////////
//	////////////////////////////////////////////////////////////////////////////
//	The external 'swap()' method . . .
//	////////////////////////////////////////////////////////////////////////////
template <class DataType, class LockType, class AllocType>
	inline void swap(stack_LC<DataType, LockType, AllocType> &lhs,
	stack_LC<DataType, LockType, AllocType>  &rhs) {
	lhs.Swap(rhs);
}
//	////////////////////////////////////////////////////////////////////////////

} // namespace STLSupp

} // namespace CPPSupp

} // namespace MLB

#endif // #ifndef HH__MLB__CPPSupp__STLSupp__stack_LC_h__HH

