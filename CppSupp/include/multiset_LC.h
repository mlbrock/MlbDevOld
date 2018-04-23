/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	STL Support Library Include File														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for multiset_LC<>.

	Revision History	:	1998-04-08 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1998 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef HH__MLB__CPPSupp__STLSupp__multiset_LC_h__HH

#define HH__MLB__CPPSupp__STLSupp__multiset_LC_h__HH	1

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
# include <set>
# if _MSC_VER >= 1300
#  pragma warning(default:4217 4251 4555)
# endif /* # if _MSC_VER >= 1300 */
# pragma warning(default:4018 4100 4146 4244 4245 4511 4512 4663)
#else
# include <set>
#endif /* #ifdef _Windows */

#include "ScopedLock.h"

#include "NullLock.h"

/*	***********************************************************************	*/

namespace MLB {

namespace CPPSupp {

namespace STLSupp {

/*	***********************************************************************	*/
template <class DataType, class LockType = MLB::CPPSupp::NullLock,
	class PredType = std::less<DataType>,
	class AllocType = std::allocator<DataType> >
	class multiset_LC {

	private:

		//	////////////////////////////////////////////////////////////////
		//	////////////////////////////////////////////////////////////////
		// Some useful internal typedefs from which to work . . .
		//	////////////////////////////////////////////////////////////////
		typedef std::multiset<DataType, PredType, AllocType>         BaseCollType;
		typedef multiset_LC<DataType, LockType, PredType, AllocType> ThisCollType;
		//	////////////////////////////////////////////////////////////////

	public:

		//	////////////////////////////////////////////////////////////////
		//	////////////////////////////////////////////////////////////////
		//	Externally available for use in scoped locking:
		//
		//	Where there exists a collection:
		//		multiset_LC<SomeType> some_instance;
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
		typedef typename BaseCollType::value_type               value_type;
		typedef typename BaseCollType::key_type                 key_type;
		typedef typename BaseCollType::key_compare              key_compare;
		typedef typename BaseCollType::value_compare            value_compare;
//	std::vector::pointer not supported in Dinkumware for MSc++ version 6
#if defined(_MSC_VER) && (_MSC_VER < 1300) && defined(_SET_)
		typedef typename AllocType::pointer                     pointer;
#else
		typedef typename BaseCollType::pointer                  pointer;
#endif // #if defined(_MSC_VER) && (_MSC_VER < 1300) && defined(_SET_)
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
		typedef typename value_type                             ValueType;
		typedef typename key_type                               KeyType;
		typedef typename key_compare                            KeyCompare;
		typedef typename value_compare                          ValueCompare;
		typedef typename pointer                                Pointer;
		typedef typename reference                              Ref;
		typedef typename const_reference                        ConstRef;
		typedef typename size_type                              SizeType;
		typedef typename difference_type                        DiffType;
		typedef typename iterator                               Iter;
		typedef typename const_iterator                         ConstIter;
		typedef typename reverse_iterator                       RIter;
		typedef typename const_reverse_iterator                 ConstRIter;
		//	////////////////////////////////////////////////////////////////

	public:
		/*	***********************************************************
			***********************************************************
			Core constructors and the destructor . . .
			***********************************************************	*/
		explicit multiset_LC(const ValueCompare &pred = PredType(),
			const AllocType &alloc = AllocType()) :
			coll_lock(), coll_data(pred, alloc) { }
		//	////////////////////////////////////////////////////////////////
		//	////////////////////////////////////////////////////////////////
		//	MSC version 6.0 doesn't support this constructor correctly
		//	because of a lack of full support for template member functions.
		//	////////////////////////////////////////////////////////////////
#if defined(_MSC_VER) && (_MSC_VER < 1300) && defined(_SET_)
		multiset_LC(ConstIter first_iter, ConstIter last_iter,
			const ValueCompare &pred = PredType(),
			const AllocType &alloc = AllocType()) :
			coll_lock(), coll_data(pred, alloc) {
			while (first_iter != last_iter) {
				coll_data.insert(*first_iter);
				++first_iter;
			}
		}
/*
		multiset_LC(const ValueType *first_iter, const ValueType *last_iter,
			const ValueCompare &pred = PredType(),
			const AllocType &alloc = AllocType()) :
			coll_lock(), coll_data(first_iter, last_iter, pred, alloc) { }
*/
#else
		template <class InputIterator> multiset_LC(InputIterator first_iter,
			InputIterator last_iter,
			const ValueCompare &pred = PredType(),
			const AllocType &alloc = AllocType()) :
			coll_lock(), coll_data(first_iter, last_iter, pred, alloc) { }
#endif // #if defined(_MSC_VER) && (_MSC_VER < 1300) && defined(_SET_)
		//	////////////////////////////////////////////////////////////////
		//	////////////////////////////////////////////////////////////////
		// Specialized constructor with the base collection as input...
		//	////////////////////////////////////////////////////////////////
		multiset_LC(const BaseCollType &in_coll) :
			coll_lock(), coll_data(in_coll) { }
		//	////////////////////////////////////////////////////////////////
		virtual ~multiset_LC() {
			MyLockReader my_lock(*this);
			clear();
		}
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			The copy constructor . . .
			***********************************************************	*/
		multiset_LC(const ThisCollType &in_coll) :
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

		//	////////////////////////////////////////////////////////////////
		//	////////////////////////////////////////////////////////////////
		//	Specialized container methods . . .
		//	////////////////////////////////////////////////////////////////
		//	If the datum key is not located in the container, this method will
		//	insert it and return true.
		//	
		//	Otherwise, it takes no action and returns false.
		bool InsertOnly(const DataType &in_data) {
			MyLockWriter my_lock(*this);
			if (find(in_data) != end())
				return(false);
			insert(in_data);
			return(true);
		}
		//	////////////////////////////////////////////////////////////////
		//	If the datum key is located in the containe, this method will erase
		//	the key entry matching the provided datum, insert the provided datum
		//	in its place, and return true.
		//
		//	Otherwise, it takes no action and returns false.
		//	
		//	Note that it impossible to predict precisely which of a number of
		//	key entries matching that of the provided datum will be erased by
		//	this method.
		bool UpdateOnly(const DataType &out_data) {
			MyLockWriter my_lock(*this);
			if (find(in_data) == end())
				return(false);
			erase(in_data);
			insert(in_data);
			return(true);
		}
		//	////////////////////////////////////////////////////////////////
		//	Returns true if the datum was inserted (that is, it was not already
		//	in the container), false if the data was updated (that is, the key
		//	was found, erased, and the new datum was inserted).
		//	
		//	Note that it impossible to predict precisely which of a number of
		//	key entries matching that of the provided datum will be erased by
		//	this method.
		bool InsertOrUpdate(const DataType &out_data) {
			bool         return_code = false;
			MyLockWriter my_lock(*this);
			if (find(in_data) != end())
				erase(in_data);
			else
				return_code = true;
			insert(in_data);
			return(return_code);
		}
		//	////////////////////////////////////////////////////////////////

		/*	***********************************************************
			***********************************************************
			Locking container core methods . . .
			***********************************************************	*/
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
		SizeType   Count(const KeyType &in_key) const {
			MyLockReader my_lock(*this);
			return(count(in_key));
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
		std::pair<Iter, Iter> Equal_Range(const KeyType &in_key) {
			MyLockReader my_lock(*this);
			return(equal_range(in_key));
		}
		std::pair<ConstIter, ConstIter> Equal_Range(const KeyType &in_key) const {
			return(equal_range(in_key));
		}
		void       Erase(Iter position) {
			MyLockWriter my_lock(*this);
			erase(position);
		}
		void       Erase(Iter first, Iter last) {
			MyLockWriter my_lock(*this);
			erase(first, last);
		}
		SizeType   Erase(const KeyType &in_key) {
			MyLockWriter my_lock(*this);
			return(erase(in_key));
		}
		Iter       Find(const KeyType &in_key) {
			MyLockReader my_lock(*this);
			return(find(in_key));
		}
		ConstIter  Find(const KeyType &in_key) const {
			MyLockReader my_lock(*this);
			return(find(in_key));
		}
		AllocType  Get_Allocator() const {
			MyLockReader my_lock(*this);
			return(get_allocator());
		}
		Iter       Insert(const ValueType &in_value) {
			MyLockWriter my_lock(*this);
			return(insert(in_value));
		}
		Iter       Insert(Iter position, const ValueType &in_value) {
			MyLockWriter my_lock(*this);
			return(insert(position, in_value));
		}
		template<class InputIterator>
			void Insert(InputIterator first_iter, InputIterator last_iter) {
			MyLockWriter my_lock(*this);
			insert(first_iter, last_iter);
		}
		KeyCompare Key_Comp() const {
			MyLockReader my_lock(*this);
			return(key_comp());
		}
		Iter       Lower_Bound(const KeyType &in_key) {
			MyLockReader my_lock(*this);
			return(lower_bound(in_key));
		}
		ConstIter  Lower_Bound(const KeyType &in_key) const {
			MyLockReader my_lock(*this);
			return(lower_bound(in_key));
		}
		SizeType   Max_Size() const {
			MyLockReader my_lock(*this);
			return(max_size());
		}
		RIter      Rbegin() {
			MyLockReader my_lock(*this);
			return(rbegin());
		}
		ConstRIter Rbegin() const {
			MyLockReader my_lock(*this);
			return(rbegin());
		}
		RIter      Rend() {
			MyLockReader my_lock(*this);
			return(rend());
		}
		ConstRIter Rend() const {
			MyLockReader my_lock(*this);
			return(rend());
		}
		SizeType   Size() const {
			MyLockReader my_lock(*this);
			return(size());
		}
		void       Swap(BaseCollType &in_coll) {
			MyLockWriter my_lock(*this);
			swap(in_coll);
		}
		void       Swap(ThisCollType &in_coll) {
			MyLockWriter in_lock(in_coll);
			Swap(in_coll.coll_data);
		}
		Iter       Upper_Bound(const KeyType &in_key) {
			MyLockReader my_lock(*this);
			return(upper_bound(in_key));
		}
		ConstIter  Upper_Bound(const KeyType &in_key) const {
			MyLockReader my_lock(*this);
			return(upper_bound(in_key));
		}
		ValueCompare Value_Comp() const {
			MyLockReader my_lock(*this);
			return(value_comp());
		}
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Non-locking container core methods . . .
			***********************************************************	*/
		Iter       begin() {
			return(coll_data.begin());
		}
		ConstIter  begin() const {
			return(coll_data.begin());
		}
		void       clear() {
			coll_data.clear();
		}
		SizeType   count(const KeyType &in_key) const {
			return(coll_data.count(in_key));
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
		std::pair<Iter, Iter>
			equal_range(const DataType &in_data) {
			return(coll_data.equal_range(in_data));
		}
		std::pair<ConstIter, ConstIter>
			equal_range(const DataType &in_data) const {
			return(coll_data.equal_range(in_data));
		}
		void       erase(Iter position) {
			coll_data.erase(position);
		}
		void       erase(Iter first, Iter last) {
			coll_data.erase(first, last);
		}
		SizeType   erase(const KeyType &in_key) {
			return(coll_data.erase(in_key));
		}
		Iter       find(const KeyType &in_key) {
			return(coll_data.find(in_key));
		}
		ConstIter  find(const KeyType &in_key) const {
			return(coll_data.find(in_key));
		}
		AllocType  get_allocator() const {
			return(coll_data.get_allocator());
		}
		Iter       insert(const ValueType &in_value) {
			return(coll_data.insert(in_value));
		}
		Iter       insert(Iter position, const ValueType &in_value) {
			return(coll_data.insert(position, in_value));
		}
		//	////////////////////////////////////////////////////////////////
		//	////////////////////////////////////////////////////////////////
		//	MSC version 6.0 doesn't support this insert() method correctly
		//	because of a lack of full support for template member functions.
		//	////////////////////////////////////////////////////////////////
#if defined(_MSC_VER) && (_MSC_VER < 1300) && defined(_SET_)
		template<class InputIterator>
			void insert(InputIterator first_iter, InputIterator last_iter) {
			std::copy(first_iter, last_iter,
				std::inserter(coll_data, coll_data.begin()));
		}
#else
		template<class InputIterator>
			void insert(InputIterator first_iter, InputIterator last_iter) {
			coll_data.insert(first_iter, last_iter);
		}
#endif // #if defined(_MSC_VER) && (_MSC_VER < 1300) && defined(_SET_)
		//	////////////////////////////////////////////////////////////////
		KeyCompare key_comp() const {
			return(coll_data.key_comp());
		}
		Iter       lower_bound(const KeyType &in_key) {
			return(coll_data.lower_bound(in_key));
		}
		ConstIter  lower_bound(const KeyType &in_key) const {
			return(coll_data.lower_bound(in_key));
		}
		SizeType   max_size() const {
			return(coll_data.max_size());
		}
		RIter      rbegin() {
			return(coll_data.rbegin());
		}
		ConstRIter rbegin() const {
			return(coll_data.rbegin());
		}
		RIter      rend() {
			return(coll_data.rend());
		}
		ConstRIter rend() const {
			return(coll_data.rend());
		}
		SizeType   size() const {
			return(coll_data.size());
		}
		void       swap(BaseCollType &in_coll) {
			coll_data.swap(in_coll);
		}
		void       swap(ThisCollType &in_coll) {
			swap(in_coll.coll_data);
		}
		Iter       upper_bound(const KeyType &in_key) {
			return(coll_data.upper_bound(in_key));
		}
		ConstIter  upper_bound(const KeyType &in_key) const {
			return(coll_data.upper_bound(in_key));
		}
		ValueCompare value_comp() const {
			return(coll_data.value_comp());
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
		mutable LockType coll_lock;
		BaseCollType     coll_data;
		/*	***********************************************************	*/
};
/*	***********************************************************************	*/

//	////////////////////////////////////////////////////////////////////////////
//	////////////////////////////////////////////////////////////////////////////
//			The external 'swap()' method . . .
//	////////////////////////////////////////////////////////////////////////////
template <class DataType, class LockType, class PredType, class AllocType>
	inline void swap(multiset_LC<DataType, LockType, PredType, AllocType> &lhs,
	multiset_LC<DataType, LockType, PredType, AllocType> &rhs)
{
	lhs.Swap(rhs);
}
//	////////////////////////////////////////////////////////////////////////////

} // namespace STLSupp

} // namespace CPPSupp

} // namespace MLB

#endif // #ifndef HH__MLB__CPPSupp__STLSupp__multiset_LC_h__HH

