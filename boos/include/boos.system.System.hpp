/** 
 * System class of the operating system.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2017 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_SYSTEM_SYSTEM_HPP_
#define BOOS_SYSTEM_SYSTEM_HPP_

#include "boos.Types.hpp"

namespace api { class Toggle; }

namespace system
{
  class Main;
  class SystemTimerInterrupt;
  
  class System
  {
    friend class Main;
    
  public:
    
    /** 
     * Returns a current value of the running system in milliseconds.
     *
     * @return time in milliseconds.
     */
    static int64 currentTimeMillis();

    /** 
     * Returns a current value of the running system.
     *
     * @return time in nanoseconds.
     */      
    static int64 nanoTime();
    
    /**
     * Terminates the operating system execution.
     */
    static void terminate();

  private:

    /**
     * Initialization.
     *
     * @return true if no errors.
     */
    static bool init();

    /**
     * Deinitialization.
     */
    static void deinit();

    /**
     * Hardware timer interrupt resource (no boot).
     */
    static SystemTimerInterrupt* interrupt_;
    
    /**
     * Global interrupt resource (no boot).
     */
    static ::api::Toggle* global_;    

  };
}
#endif // BOOS_SYSTEM_SYSTEM_HPP_