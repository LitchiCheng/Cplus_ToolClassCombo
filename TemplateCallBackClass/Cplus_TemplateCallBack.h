class CCallBackBase
{
	public:
		virtual void callBack(void){}
};

template<typename T>
class CTemplateCallBack: public CCallBackBase
{
    public:
        CTemplateCallBack(T* ptr_T, void(T::*ptr_func)()):_ptr_T(ptr_T), _ptr_func(ptr_func){}
        virtual void callBack(void){
            if(_ptr_T && _ptr_func)
				(_ptr_T->*_ptr_func)();
        }
        int enable(){
			//push "this" into a CCallBackBase* array or vector
		}
        int disable(){
			//pop "this" into a CCallBackBase* array or vector
		}
    private:
        T* _ptr_T;
		void (T::*_ptr_func)();
};