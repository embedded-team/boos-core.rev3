/** 
 * The kernel time resource.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef KERNEL_TIME_HPP_
#define KERNEL_TIME_HPP_

#include "kernel.TimerInterrupt.hpp"
#include "api.Task.hpp"
#include "api.Value.hpp"
#include "module.Interrupt.hpp"
 
namespace kernel
{
    class Time : public ::kernel::TimerInterrupt, public ::api::Task, public ::api::Value<int64>
    {
        typedef ::kernel::TimerInterrupt Parent;
  
    public:
  
        /** 
         * Constructor.
         */     
        Time() : Parent(),
            isConstructed_ (getConstruct()),
            cnt_   (0),
            acc_   (0),
            time_  (0){
            setConstruct( construct() );
        }
      
        /** 
         * Destructor.
         */
        virtual ~Time()
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
         * The method with self context.
         */  
        virtual void main()
        {
            updateTime(getPeriod());
        }
        
        /**
         * Returns size of stack.
         *
         * @return stack size in bytes.
         */
        virtual int32 getStackSize() const
        {
            return 0x200;
        }
        
        
        /**
         * Sets a value.
         *
         * @param value a value for setting.
         */    
        virtual void setValue(int64 value)
        {
        }
          
        /**
         * Returns set value.
         *
         * @return the set value.
         */      
        virtual int64 getValue() const
        {
            return isConstructed_ ? updateTime( getCount() ) : 0;        
        }
        
        /**
         * Returns illegal element which will be returned as error value.
         *
         * @return illegal element.
         */
        virtual int64 getIllegal() const
        {
            return ILLEGAL_VALUE;
        }
        
        /**
         * Sets illegal element which will be returned as error value.
         *
         * @param value illegal value.
         */
        virtual void setIllegal(int64 value)
        {
        }
        
        /**
         * Tests if given value is an illegal.
         *
         * @param value testing value.
         * @param true if value is an illegal.
         */
        virtual bool isIllegal(const int64& value) const
        {
            return value == ILLEGAL_VALUE ? true : false;
        }
  
    private:
  
        /**
         * Update kernel time.
         *
         * @param cnt the timer counter value.
         * @return updated current time in nanoseconds.
         */    
        int64 updateTime(uint64 cnt) const
        {
            int64 time, dc, dt;
            int64 timerFrequency = getInternalClock();
            if(timerFrequency == 0) return time_;
            bool is = ::module::Interrupt::disableAll();
            // Set delta count it the value in timer clocks
            // which equals a time from previous updating.
            // This time in nanoseconds is a multiplying of
            // the value in timer clocks and system timer period.
            dc = cnt - cnt_;
            // Use a multiplying on 1E+9 for getting a time in nsec
            // from timer frequency in hz
            acc_ = dc * 1000000000 + acc_;
            // The nanoseconds left time after previous updating
            dt = acc_ / timerFrequency;
            // Increment operating system kernel working time in nsec
            time = time_ += dt;
            // Store the remainder for next updating
            acc_ = acc_ - dt * timerFrequency;
            // Store the timer counter value
            cnt_ = cnt;
            ::module::Interrupt::enableAll(is);               
            return time;
        } 
      
        /** 
         * Constructor.
         *
         * @return true if object has been constructed successfully.
         */
        bool construct()
        {
            if( not isConstructed_ ) return false;
            int32 source = getInterrupSource();
            if( setHandler(*this, source) == false ) return false;
            setPeriod();
            setCount(0);
            start();
            enable(true);
            return true;
        }
        
        /**
         * Copy constructor.
         *
         * @param obj reference to source object.
         */
        Time(const Time& obj);
      
        /**
         * Assignment operator.
         *
         * @param obj reference to source object.
         * @return reference to this object.     
         */
        Time& operator =(const Time& obj); 
        
        /** 
         * Illegal value of counting time.
         */
        static const int64 ILLEGAL_VALUE = -1;
        
        /** 
         * The root object constructed flag.
         */  
        const bool& isConstructed_;
        
        /**
         * Previous counter value.
         */    
        mutable uint64 cnt_;
      
        /**
         * Accumulator.
         */    
        mutable uint64 acc_;
        
        /**
         * The operating system kernel working time in nsec.
         */        
        mutable uint64 time_;
  
    };
}
#endif // KERNEL_TIME_HPP_

