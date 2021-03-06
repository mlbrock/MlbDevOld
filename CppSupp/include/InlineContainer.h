/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	C++ Support Library Include File														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include and implementation file for inline containers.

								From an article published in _C/C++ Users Journal_,
								Vol 16, No 9, September 1998 by Andrei Alexandrescu,
								pp. 73-74.

	Revision History	:	1998-10-07 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1998 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef HH__MLB__CPPSupp__STLSupp___InlineContainer_h__HH

#define HH__MLB__CPPSupp__STLSupp___InlineContainer_h__HH	1

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
# include <list>
# include <vector>
# if _MSC_VER >= 1300
#  pragma warning(default:4217 4251 4555)
# endif /* # if _MSC_VER >= 1300 */
# pragma warning(default:4018 4100 4146 4244 4245 4511 4512 4663)
#else
# include <deque>
# include <list>
# include <vector>
#endif /* #ifdef _Windows */

/*	***********************************************************************	*/

namespace MLB {

namespace CPPSupp {

namespace STLSupp {

/*
	ADF NOTE:	Derives from STL containers. Polymorphic use not recommended.
*/
/*	***********************************************************************	*/
template <class DataType, class ContainerType = std::vector<DataType> >
	class InlineContainer : public ContainerType {

	public:

		/*	***********************************************************
			***********************************************************
			Constructors and destructor . . .
			***********************************************************	*/
		InlineContainer() { }
		explicit InlineContainer(const DataType &the_data) :
			ContainerType(1, the_data) { }
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			The copy constructors . . .

			Note we cast away the constness of the copy source and then
			'swap()' (thus changing it). This is OK because the inline
			container should be used only as specified . . .
			***********************************************************	*/
		InlineContainer(const InlineContainer &src) {
			this->swap(const_cast<InlineContainer &>(src));
		}
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Function-call operator . . .
			***********************************************************	*/
		InlineContainer & operator () (const DataType &the_data) {
			push_back(the_data);
			return(*this);
		}
		/*	***********************************************************	*/
};
/*	***********************************************************************	*/
			
/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Make the various supported container types . . .								*/
/*	***********************************************************************	*/
template <class DataType>
	inline InlineContainer<DataType, std::deque<DataType> >
	MakeInlineDeque()
{
	return(InlineContainer<DataType, std::deque<DataType> >());
}
template <class DataType>
	inline InlineContainer<DataType, std::list<DataType> >
	MakeInlineList()
{
	return(InlineContainer<DataType, std::list<DataType> >());
}
// std::vector explicitly specified in case the class template default changes.
template <class DataType>
	inline InlineContainer<DataType, std::vector<DataType> >
	MakeInlineVector()
{
	return(InlineContainer<DataType, std::vector<DataType> >());
}


template <class DataType>
	inline InlineContainer<DataType, std::deque<DataType> >
	MakeInlineDeque(const DataType &the_data)
{
	return(InlineContainer<DataType, std::deque<DataType> >(the_data));
}
template <class DataType>
	inline InlineContainer<DataType, std::list<DataType> >
	MakeInlineList(const DataType &the_data)
{
	return(InlineContainer<DataType, std::list<DataType> >(the_data));
}
// std::vector explicitly specified in case the class template default changes.
template <class DataType>
	inline InlineContainer<DataType, std::vector<DataType> >
	MakeInlineVector(const DataType &the_data)
{
	return(InlineContainer<DataType, std::vector<DataType> >(the_data));
}
/*	***********************************************************************	*/

} // namespace STLSupp

} // namespace CPPSupp

} // namespace MLB

#endif // #ifndef HH__MLB__CPPSupp__STLSupp___InlineContainer_h__HH

