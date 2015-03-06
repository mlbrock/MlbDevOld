/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	C++ Support Library Include File														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include and implementation file for scoped lock
								templates.

	Revision History	:	1998-04-08 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1998 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef HH__MLB__CPPSupp__ScopedLock_h__HH

#define HH__MLB__CPPSupp__ScopedLock_h__HH	1

namespace MLB {

namespace CPPSupp {

/*
	Required interface for the class 'LockType':

		'int   LockReader() const' returns 0 on success, non-zero on failure.

		'int   LockWriter() const' returns 0 on success, non-zero on failure.

		'int   Unlock() const'
*/
/*	***********************************************************************	*/
template <class LockType>
	class ScopedLock {

	public:

		/*	***********************************************************
			***********************************************************
			Constructors and destructor . . .

			A 'const' reference is used as the lock type parameter in
			order to receive the most-generous of implicit type conversions.

			Note that the default value for the 'lock_writer' parameter
			is 'true' --- that is writer locking. This is because writer
			locking permits the most general of behaviors (read/write
			access).
			***********************************************************	*/
		ScopedLock(const LockType &lock_type, bool lock_writer = true) :
			lock_ref(lock_type), lock_result(-1) {
			if (lock_writer)
				lock_result = lock_ref.LockWriter();
			else
				lock_result = lock_ref.LockReader();
		}
		ScopedLock(const ScopedLock &src) :
			lock_ref(src.lock_ref), lock_result(src.lock_result) {
			src.lock_result = -1;
		}
		~ScopedLock() {
			Unlock();
		}
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			This explicit 'Unlock' method permits the scoped lock to be
			unlocked before the end of scope. Likely to be useful when
			the scope is exited prematurely; say by exiting a thread . . .
			***********************************************************	*/
		void Unlock() {
			if (!lock_result) {
				lock_result = -1;
				lock_ref.Unlock();
			}
		}
		/*	***********************************************************	*/

	private:

		/*	***********************************************************
			***********************************************************
			Declared private but not defined to prevent instantiation
			because we don't want constructed (that is; locked) objects
			assigned . . .
			***********************************************************	*/
		ScopedLock& operator=(const ScopedLock &src);
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Private data:

				o The reference to the lock to be scope-managed

				o Result code from the lock attempt.
			***********************************************************	*/
		const LockType &lock_ref;
		int             lock_result;
		/*	***********************************************************	*/
};
/*	***********************************************************************	*/

/*	***********************************************************************	*/
template <class LockType>
	class ScopedLockReader : public ScopedLock<LockType> {

	public:

		/*	***********************************************************
			***********************************************************
			Constructor and destructor . . .
			***********************************************************	*/
		ScopedLockReader(const LockType &lock_type) :
			ScopedLock<LockType>(lock_type, false) { }
		~ScopedLockReader() { }
		/*	***********************************************************	*/

	private:

		/*	***********************************************************
			***********************************************************
			Impossible for the compiler to generate these as the base
			declares them private. This derived class declares them (but
			does not define them) to prevent compiler complaints . . .
			***********************************************************	*/
		ScopedLockReader& operator=(const ScopedLockReader &src);
		/*	***********************************************************	*/
};
/*	***********************************************************************	*/

/*	***********************************************************************	*/
template <class LockType>
	class ScopedLockWriter : public ScopedLock<LockType> {

	public:

		/*	***********************************************************
			***********************************************************
			Constructor and destructor . . .
			***********************************************************	*/
		ScopedLockWriter(const LockType &lock_type) :
			ScopedLock<LockType>(lock_type, true) { }
		~ScopedLockWriter() { }
		/*	***********************************************************	*/

	private:

		/*	***********************************************************
			***********************************************************
			Impossible for the compiler to generate these as the base
			declares them private. This derived class declares them (but
			does not define them) to prevent compiler complaints . . .
			***********************************************************	*/
		ScopedLockWriter& operator=(const ScopedLockWriter &src);
		/*	***********************************************************	*/
};
/*	***********************************************************************	*/

} // namespace CPPSupp

} // namespace MLB

#endif // #ifndef HH__MLB__CPPSupp__ScopedLock_h__HH

