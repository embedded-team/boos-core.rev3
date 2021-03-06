/**
 * Runtime kernel execution.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef KERNEL_RUNTIME_HPP_
#define KERNEL_RUNTIME_HPP_

#include "kernel.Object.hpp"
#include "api.Runtime.hpp"
#include "module.Interrupt.hpp"

namespace kernel
{
    class Runtime : public ::kernel::Object, public ::api::Runtime
    {
        typedef ::kernel::Object Parent;
      
    public:
    
        /** 
         * Constructor.
         */     
        Runtime() : Parent(),
            isConstructed_ (getConstruct()){
            setConstruct( construct() );
        }
      
        /** 
         * Destructor.
         */
        virtual ~Runtime()
        {
        }    
        
        /**
         * Tests if this object has been constructed.
         *
         * @return true if object has been constructed successfully.
         */    
        virtual bool isConstructed() const
        {
            return isConstructed_;
        }
        
        /**
         * Loads a program for executing.
         *
         * @param path a system path to a program.
         * @return true if program has been loaded successfully.
         */    
        virtual bool load(const char* path)
        {
            if( not isConstructed_ ) return false;
            return path != NULL ? false : false;
        }           
  
        /**
         * Terminates a kernel execution.
         *
         * @param status a termination status.
         */    
        virtual void terminate(int32 status)
        {
            ::module::Interrupt::disableAll();
            while(true);
        }
        
    private:
        
        /** 
         * Constructor.
         *
         * @return true if object has been constructed successfully.
         */
        bool construct()
        {
            if( not isConstructed_ ) return false;
            return true;
        }        
        
        /**
         * Copy constructor.
         *
         * @param obj reference to source object.
         */
        Runtime(const Runtime& obj);
      
        /**
         * Assignment operator.
         *
         * @param obj reference to source object.
         * @return reference to this object.     
         */
        Runtime& operator =(const Runtime& obj);
        
        /** 
         * The root object constructed flag.
         */  
        const bool& isConstructed_;        

    };
}
#endif // KERNEL_RUNTIME_HPP_
