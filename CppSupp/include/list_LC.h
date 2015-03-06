/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	STL Support Library Include File														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for list_LC<>.

	Revision History	:	1998-04-08 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1998 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef HH__MLB__CPPSupp__STLSupp__list_LC_h__HH

#define HH__MLB__CPPSupp__STLSupp__list_LC_h__HH	1

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
# include <list>
# if _MSC_VER >= 1300
#  pragma warning(default:4217 4251 4555)
# endif /* # if _MSC_VER >= 1300 */
# pragma warning(default:4018 4100 4146 4244 4245 4511 4512 4663)
#else
# include <list>
#endif /* #ifdef _Windows */

#include "ScopedLock.h"

#include "NullLock.h"

/*	***********************************************************************	*/

namespace MLB {

namespace CPPSupp {

namespace STLSupp {

/*	***********************************************************************	*/
template <class DataType, class LockType = MLB::CPPSupp::NullLock,
	class AllocType = std::allocator<DataType> >
	class list_LC {

	private:

		//	////////////////////////////////////////////////////////////////
		//	////////////////////////////////////////////////////////////////
		// Some useful internal typedefs from which to work . . .
		//	////////////////////////////////////////////////////////////////
		typedef std::list<DataType, AllocType>                 BaseCollType;
		typedef list_LC<DataType, LockType, AllocType>         ThisCollType;
		//	////////////////////////////////////////////////////////////////

	public:

		//	////////////////////////////////////////////////////////////////
		//	////////////////////////////////////////////////////////////////
		//	Externally available for use in scoped locking:
		//
		//	Where there exists a collection:
		//		list_LC<SomeType> some_instance;
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
		typedef typename BaseCollType::allocator_type           allocator_type;
		typedef typename BaseCollType::value_type               value_type;
//	std::list::pointer not supported in Dinkumware for MSc++ version 6
#if defined(_MSC_VER) && (_MSC_VER < 1300) && defined(_LIST_)
		typedef typename BaseCollType::_Tptr                    pointer;
		typedef typename BaseCollType::_Ctptr                   const_pointer;
#else
		typedef typename BaseCollType::pointer                  pointer;
		typedef typename BaseCollType::const_pointer            const_pointer;
#endif // #if defined(_MSC_VER) && (_MSC_VER < 1300) && defined(_LIST_)
		typedef typename BaseCollType::reference                reference;
		typedef typename BaseCollType::const_reference          const_reference;
		typedef typename BaseCollType::size_type                size_type;
		typedef typename BaseCollType::difference_type          difference_type;
		typedef typename BaseCollType::iterator                 iterator;
		typedef typename BaseCollType::const_iterator           const_iterator;
		typedef typename BaseCollType::reverse_iterator         reverse_iterator;
		typedef typename BaseCollType::const_reverse_iterator   const_reverse_iterator;
		//	////////////////////////////////////////////////////////////////

	private:

		//	////////////////////////////////////////////////////////////////
		//	////////////////////////////////////////////////////////////////
		// Some internal short names...
		//	////////////////////////////////////////////////////////////////
		typedef typename allocator_type                          AllocatorType;
		typedef typename value_type                              ValueType;
		typedef typename pointer                                 Pointer;
		typedef typename const_pointer                           ConstPointer;
		typedef typename BaseCollType::reference                 Ref;
		typedef typename BaseCollType::const_reference           ConstRef;
		typedef typename BaseCollType::size_type                 SizeType;
		typedef typename BaseCollType::difference_type           DiffType;
		typedef typename BaseCollType::iterator                  Iter;
		typedef typename BaseCollType::const_iterator            ConstIter;
		typedef typename BaseCollType::reverse_iterator          RIter;
		typedef typename BaseCollType::const_reverse_iterator    ConstRIter;
		//	////////////////////////////////////////////////////////////////

	public:

		/*	***********************************************************
			***********************************************************
			Core constructors and the destructor . . .
			***********************************************************	*/
		explicit list_LC(const AllocType& alloc = AllocType()) :
			coll_lock(), coll_data(alloc) { }
		explicit list_LC(SizeType in_count, const DataType &data = DataType(),
			const AllocType &alloc = AllocType()) :
			coll_lock(), coll_data(in_count, data, alloc) { }
		//	////////////////////////////////////////////////////////////////
		//	////////////////////////////////////////////////////////////////
		//	MSC version 6.0 doesn't support this constructor correctly
		//	because of a lack of full support for template member functions.
		//	////////////////////////////////////////////////////////////////
#if defined(_MSC_VER) && (_MSC_VER < 1300) && defined(_LIST_)
		list_LC(ConstIter first_iter, ConstIter last_iter,
			const AllocType &alloc = AllocType()) :
			coll_lock(), coll_data(first_iter, last_iter, alloc) { }
#else
		template <class InputIterator> list_LC(InputIterator first_iter,
			InputIterator last_iter, const AllocType &alloc = AllocType()) :
			coll_lock(), coll_data(first_iter, last_iter, alloc) { }
#endif // #if defined(_MSC_VER) && (_MSC_VER < 1300) && defined(_LIST_)
		//	////////////////////////////////////////////////////////////////
		//	////////////////////////////////////////////////////////////////
		// Specialized constructor with the base collection as input...
		//	////////////////////////////////////////////////////////////////
		list_LC(const BaseCollType &in_coll) :
			coll_lock(), coll_data(in_coll) { }
		//	////////////////////////////////////////////////////////////////
		virtual ~list_LC() {
			MyLockReader my_lock(*this);
			clear();
		}
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			The copy constructor . . .
			***********************************************************	*/
		list_LC(const ThisCollType &in_coll) :
			coll_lock(), coll_data() {
			MyLockReader in_lock(in_coll);
			BaseCollType tmp_coll(in_coll.coll_data);
			swap(tmp_coll);
		}
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			The assignment constructor . . .
			***********************************************************	*/
		ThisCollType& operator=(const ThisCollType &in_coll) {
			if (this != &in_coll) {
				ThisCollType tmp_coll(in_coll);
				Swap(tmp_coll);
			}
			return(*this);
		}
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Specialized container methods . . .
			***********************************************************	*/
		bool PopBackWithGet(DataType &out_data) {
			MyLockWriter my_lock(*this);
			SizeType coll_count;
			if ((coll_count = coll_data.size()) == 0)
				return(false);
			out_data = back();
			pop_back();
			return(true);
		}
		bool PopFrontWithGet(DataType &out_data) {
			MyLockWriter my_lock(*this);
			if (coll_data.size() == 0)
				return(false);
			out_data = front();
			pop_front();
			return(true);
		}
		bool PeekBack(DataType &out_data) {
			MyLockReader my_lock(*this);
			SizeType coll_count;
			if ((coll_count = coll_data.size()) == 0)
				return(false);
			out_data = back();
			return(true);
		}
		bool PeekFront(DataType &out_data) {
			MyLockReader my_lock(*this);
			if (coll_data.empty())
				return(false);
			out_data = front();
			return(true);
		}
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Container core operator methods . . .
			***********************************************************	*/
		Ref      operator[](SizeType in_position) {
			MyLockReader my_lock(*this);
			return(coll_data[in_position]);
		}
		ConstRef operator[](SizeType in_position) const {
			MyLockReader my_lock(*this);
			return(coll_data[in_position]);
		}
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Locking container core methods . . .
			***********************************************************	*/
		//	////////////////////////////////////////////////////////////////
		//	////////////////////////////////////////////////////////////////
		//	MSC version 6.0 doesn't support this assign() method correctly
		//	because of a lack of full support for template member functions.
		//	////////////////////////////////////////////////////////////////
#if defined(_MSC_VER) && (_MSC_VER < 1300) && defined(_LIST_)
		void Assign(ConstIter first, ConstIter last) {
			MyLockWriter my_lock(*this);
			assign(first, last);
		}
#else
		template <class InputIterator>
			void Assign(InputIterator first, InputIterator last) {
			MyLockWriter my_lock(*this);
			assign(first, last);
		}
#endif // #if defined(_MSC_VER) && (_MSC_VER < 1300) && defined(_LIST_)
		//	////////////////////////////////////////////////////////////////
		void       Assign(SizeType in_count,
			const DataType &in_data = DataType()) {
			MyLockWriter my_lock(*this);
			assign(in_count, in_data);
		}
		Ref        Back() {
			MyLockReader my_lock(*this);
			return(back());
		}
		ConstRef   Back() const {
			MyLockReader my_lock(*this);
			return(back());
		}
		Iter       Begin() {
			MyLockReader my_lock(*this);
			return(begin());
		}
		ConstIter  Begin() const {
			MyLockReader my_lock(*this);
			return(begin());
		}
		void       Clear() {
			MyLockWriter my_lock(*this);
			clear();
		}
		bool       Empty() const {
			MyLockReader my_lock(*this);
			return(empty());
		}
		Iter       End() {
			MyLockReader my_lock(*this);
			return(end());
		}
		ConstIter  End() const {
			MyLockReader my_lock(*this);
			return(end());
		}
		Iter       Erase(Iter position) {
			MyLockWriter my_lock(*this);
			return(erase(position));
		}
		Iter       Erase(Iter first, Iter last) {
			MyLockWriter my_lock(*this);
			return(erase(first, last));
		}
		Ref        Front() {
			MyLockReader my_lock(*this);
			return(front());
		}
		ConstRef   Front() const {
			MyLockReader my_lock(*this);
			return(front());
		}
		AllocType  Get_Allocator() const {
			MyLockReader my_lock(*this);
			return(get_allocator());
		}
		Iter       Insert(Iter position,
			const DataType &in_data = DataType()) {
			MyLockWriter my_lock(*this);
			return(insert(position, in_data));
		}
		void       Insert(Iter position, SizeType in_count,
			const DataType &in_data = DataType()) {
			MyLockWriter my_lock(*this);
			insert(position, in_count, in_data);
		}
		//	////////////////////////////////////////////////////////////////
		//	////////////////////////////////////////////////////////////////
		//	MSC version 6.0 doesn't support this insert() method correctly
		//	because of a lack of full support for template member functions.
		//	////////////////////////////////////////////////////////////////
#if defined(_MSC_VER) && (_MSC_VER < 1300) && defined(_LIST_)
			void Insert(Iter position, ConstIter first, ConstIter last) {
			MyLockWriter my_lock(*this);
			insert(position, first, last);
		}
#else
		template <class InputIterator>
			void Insert(Iter position, InputIterator first, InputIterator last) {
			MyLockWriter my_lock(*this);
			insert(position, first, last);
		}
#endif // #if defined(_MSC_VER) && (_MSC_VER < 1300) && defined(_LIST_)
		//	////////////////////////////////////////////////////////////////
		SizeType   Max_Size() const {
			MyLockReader my_lock(*this);
			return(max_size());
		}
		void       Merge(BaseCollType &in_coll) {
			MyLockWriter my_lock(*this);
			merge(in_coll);
		}
		void       Merge(ThisCollType &in_coll) {
			MyLockWriter in_lock(in_coll);
			Merge(in_coll.coll_data);
		}
		template <class Traits>
			void Merge(BaseCollType &in_coll, Traits compare) {
			MyLockWriter my_lock(*this);
			merge(in_coll, compare);
		}
		template <class Traits>
			void Merge(ThisCollType &in_coll, Traits compare) {
			MyLockWriter in_lock(in_coll);
			Merge(in_coll.coll_data, compare);
		}
		void       Pop_Back() {
			MyLockWriter my_lock(*this);
			pop_back();
		}
		void       Pop_Front() {
			MyLockWriter my_lock(*this);
			pop_front();
		}
		void       Push_Back(const DataType &in_data) {
			MyLockWriter my_lock(*this);
			push_back(in_data);
		}
		void       Push_Front(const DataType &in_data) {
			MyLockWriter my_lock(*this);
			push_front(in_data);
		}
		RIter      Rbegin() {
			MyLockReader my_lock(*this);
			return(rbegin());
		}
		ConstRIter Rbegin() const {
			MyLockReader my_lock(*this);
			return(rbegin());
		}
		void       Remove(const DataType &in_data) {
			MyLockWriter my_lock(*this);
			remove(in_data);
		}
		template <class Predicate> void Remove_If(Predicate pred) {
			MyLockWriter my_lock(*this);
			remove_if(pred);
		}
		RIter      Rend() {
			MyLockReader my_lock(*this);
			return(rend());
		}
		ConstRIter Rend() const {
			MyLockReader my_lock(*this);
			return(rend());
		}
		void       Resize(SizeType in_count,
			const DataType &in_data = DataType()) {
			MyLockWriter my_lock(*this);
			resize(in_count, in_data);
		}
		void       Reverse() {
			MyLockWriter my_lock(*this);
			reverse();
		}
		SizeType   Size() const {
			MyLockReader my_lock(*this);
			return(size());
		}
		void       Sort() {
			MyLockWriter my_lock(*this);
			sort();
		}
		template <class Traits> void Sort(Traits compare) {
			MyLockWriter my_lock(*this);
			sort(compare);
		}
		void       Splice(Iter position, BaseCollType &in_coll,
			Iter first = in_coll.begin(), Iter last = in_coll.end()) {
			MyLockWriter my_lock(*this);
			splice(position, in_coll, first, last);
		}
		void       Splice(Iter position, ThisCollType &in_coll) {
			MyLockWriter my_lock(in_coll);
			Splice(position, in_coll.coll_data);
		}
		void       Splice(Iter position, ThisCollType &in_coll, Iter first) {
			MyLockWriter my_lock(in_coll);
			Splice(position, in_coll.coll_data, first);
		}
		void       Splice(Iter position, ThisCollType &in_coll, Iter first,
			Iter last) {
			MyLockWriter my_lock(in_coll);
			Splice(position, in_coll.coll_data, first, last);
		}
		void       Swap(BaseCollType &in_coll) {
			MyLockWriter my_lock(*this);
			swap(in_coll);
		}
		void       Swap(ThisCollType &in_coll) {
			MyLockWriter in_lock(in_coll);
			Swap(in_coll.coll_data);
		}
		void       Unique() {
			MyLockWriter my_lock(*this);
			unique();
		}
		template <class BinaryPredicate> void Unique(BinaryPredicate pred) {
			MyLockWriter my_lock(*this);
			unique(pred);
		}
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Non-locking container core methods . . .
			***********************************************************	*/
		//	////////////////////////////////////////////////////////////////
		//	////////////////////////////////////////////////////////////////
		//	MSC version 6.0 doesn't support this assign() method correctly
		//	because of a lack of full support for template member functions.
		//	////////////////////////////////////////////////////////////////
#if defined(_MSC_VER) && (_MSC_VER < 1300) && defined(_LIST_)
		void assign(ConstIter first, ConstIter last) {
			coll_data.assign(first, last);
		}
#else
		template <class InputIterator>
			void assign(InputIterator first, InputIterator last) {
			coll_data.assign(first, last);
		}
#endif // #if defined(_MSC_VER) && (_MSC_VER < 1300) && defined(_LIST_)
		//	////////////////////////////////////////////////////////////////
		void       assign(SizeType in_count,
			const DataType &in_data = DataType()) {
			coll_data.assign(in_count, in_data);
		}
		Ref        back() {
			return(coll_data.back());
		}
		ConstRef   back() const {
			return(coll_data.back());
		}
		Iter       begin() {
			return(coll_data.begin());
		}
		ConstIter  begin() const {
			return(coll_data.begin());
		}
		void       clear() {
			coll_data.clear();
		}
		bool       empty() const {
			return(coll_data.empty());
		}
		Iter       end() {
			return(coll_data.end());
		}
		ConstIter  end() const {
			return(coll_data.end());
		}
		Iter       erase(Iter position) {
			return(coll_data.erase(position));
		}
		Iter       erase(Iter first, Iter last) {
			return(coll_data.erase(first, last));
		}
		Ref        front() {
			return(coll_data.front());
		}
		ConstRef   front() const {
			return(coll_data.front());
		}
		AllocType  get_allocator() const {
			return(coll_data.get_allocator());
		}
		Iter       insert(Iter position,
			const DataType &in_data = DataType()) {
			return(coll_data.insert(position, in_data));
		}
		void       insert(Iter position, SizeType in_count,
			const DataType &in_data = DataType()) {
			coll_data.insert(position, in_count, in_data);
		}
		//	////////////////////////////////////////////////////////////////
		//	////////////////////////////////////////////////////////////////
		//	MSC version 6.0 doesn't support this insert() method correctly
		//	because of a lack of full support for template member functions.
		//	////////////////////////////////////////////////////////////////
#if defined(_MSC_VER) && (_MSC_VER < 1300) && defined(_LIST_)
		void insert(Iter position, ConstIter first, ConstIter last) {
			coll_data.insert(position, first, last);
		}
#else
		template <class InputIterator>
			void insert(Iter position, InputIterator first, InputIterator last) {
			coll_data.insert(position, first, last);
		}
#endif // #if defined(_MSC_VER) && (_MSC_VER < 1300) && defined(_LIST_)
		//	////////////////////////////////////////////////////////////////
		SizeType   max_size() const {
			return(coll_data.max_size());
		}
		void       merge(BaseCollType &in_coll) {
			coll_data.merge(in_coll);
		}
		void       merge(ThisCollType &in_coll) {
			merge(in_coll.coll_data);
		}
		template <class Traits>
			void merge(BaseCollType &in_coll, Traits compare) {
			coll_data.merge(in_coll, compare);
		}
		template <class Traits>
			void merge(ThisCollType &in_coll, Traits compare) {
			merge(in_coll.coll_data, compare);
		}
		void       pop_back() {
			coll_data.pop_back();
		}
		void       pop_front() {
			coll_data.pop_front();
		}
		void       push_back(const DataType &in_data) {
			coll_data.push_back(in_data);
		}
		void       push_front(const DataType &in_data) {
			coll_data.push_front(in_data);
		}
		RIter      rbegin() {
			return(coll_data.rbegin());
		}
		ConstRIter rbegin() const {
			return(coll_data.rbegin());
		}
		void       remove(const DataType &in_data) {
			coll_data.remove(in_data);
		}
		template <class Predicate> void remove_tf(Predicate pred) {
			coll_data.remove_if(pred);
		}
		RIter      rend() {
			return(coll_data.rend());
		}
		ConstRIter rend() const {
			return(coll_data.rend());
		}
		void       resize(SizeType in_count,
			const DataType &in_data = DataType()) {
			coll_data.resize(in_count, in_data);
		}
		void       reverse() {
			coll_data.reverse();
		}
		SizeType   size() const {
			return(coll_data.size());
		}
		void       sort() {
			coll_data.sort();
		}
		template <class Traits> void sort(Traits compare) {
			coll_data.sort(compare);
		}
		void       splice(Iter position, BaseCollType &in_coll,
			Iter first = in_coll.begin(), Iter last = in_coll.end()) {
			coll_data.splice(position, in_coll, first, last);
		}
		void       splice(Iter position, ThisCollType &in_coll) {
			plice(position, in_coll.coll_data);
		}
		void       splice(Iter position, ThisCollType &in_coll, Iter first) {
			splice(position, in_coll.coll_data, first);
		}
		void       splice(Iter position, ThisCollType &in_coll, Iter first,
			Iter last) {
			splice(position, in_coll.coll_data, first, last);
		}
		void       swap(BaseCollType &in_coll) {
			coll_data.swap(in_coll);
		}
		void       swap(ThisCollType &in_coll) {
			swap(in_coll.coll_data);
		}
		void       unique() {
			coll_data.unique();
		}
		template <class BinaryPredicate> void unique(BinaryPredicate pred) {
			coll_data.unique(pred);
		}
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Container data accessors . . .
			***********************************************************	*/
		BaseCollType GetData() const {
			MyLockReader my_lock(*this);
			return(coll_data);
		}
		void         GetData(BaseCollType &out_coll) const {
			MyLockReader my_lock(*this);
			out_coll = coll_data;
		}
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Raw container data accessors. Locking must be managed by
			the caller for thread-safety. Use at your own risk . . .
			***********************************************************	*/
		BaseCollType       &GetDataRef()       { return(coll_data);  }
		const BaseCollType &GetDataRef() const { return(coll_data);  }
		BaseCollType       *GetDataPtr()       { return(&coll_data); }
		const BaseCollType *GetDataPtr() const { return(&coll_data); }
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
		mutable LockType                coll_lock;
		std::list<DataType, AllocType> coll_data;
		/*	***********************************************************	*/
};
/*	***********************************************************************	*/

//	////////////////////////////////////////////////////////////////////////////
//	////////////////////////////////////////////////////////////////////////////
//	The external 'swap()' method . . .
//	////////////////////////////////////////////////////////////////////////////
template <class DataType, class LockType, class AllocType>
	inline void swap(list_LC<DataType, LockType, AllocType> &lhs,
	list_LC<DataType, LockType, AllocType>  &rhs) {
	lhs.Swap(rhs);
}
//	////////////////////////////////////////////////////////////////////////////

} // namespace STLSupp

} // namespace CPPSupp

} // namespace MLB

#endif // #ifndef HH__MLB__CPPSupp__STLSupp__list_LC_h__HH

















