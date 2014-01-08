Scope Guard Implementation
----- ----- --------------

class ScopeGuardImplBase {
	public:

		void Dismiss() const throw() {
			dismissed_ = true;
		}

	protected:

		ScopeGuardImplBase() :
			dismissed_(false) { }
		ScopeGuardImplBase(const ScopeGuardImplBase& other)
			: dismissed_(other.dismissed_) {
			other.Dismiss();
		}
		~ScopeGuardImplBase() { }			// nonvirtual (see below why)

		 mutable bool dismissed_;

	private:

		// Disable assignment
		ScopeGuardImplBase& operator=(const ScopeGuardImplBase&);
};


template <typename Fun, typename Parm>
	class ScopeGuardImpl1 : public ScopeGuardImplBase {

	public:

		ScopeGuardImpl1(const Fun& fun, const Parm& parm) :
			fun_(fun), parm_(parm)  { }
		~ScopeGuardImpl1() {
			if (!dismissed_)
				fun_(parm_);
		}

	private:

		Fun        fun_;
		const Parm parm_;
};


template <typename Fun, typename Parm>
	ScopeGuardImpl1<Fun, Parm>
	MakeGuard(const Fun& fun, const Parm& parm)
{
	return ScopeGuardImpl1<Fun, Parm>(fun, parm);
}

typedef const ScopeGuardImplBase& ScopeGuard;


