/** 
 * System class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2017 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.system.System.hpp"
#include "boos.system.SystemTimerInterrupt.hpp"
#include "boos.driver.Interrupt.hpp"
#include "boos.api.Toggle.hpp"

namespace system
{
  /**
   * Current value of the running system in milliseconds.
   *
   * @return time in milliseconds.
   */  
  int64 System::currentTimeMillis()
  {
    return nanoTime() / 1000000;
  }

  /**
   * Current value of the running system.
   *
   * @return time in nanoseconds.
   */  
  int64 System::nanoTime()
  {
    return interrupt_ != NULL ? interrupt_->nanoTime() : 0;
  }
  
  /**
   * Terminates the operating system execution.
   */
  void System::terminate()
  {
    ::driver::Interrupt::globalDisable();
    while(true);  
  }
  
  /**
   * Initialization.
   *
   * @return true if no errors.
   */
  bool System::init()
  {
    // Create the operating system system tick timer
    interrupt_ = new SystemTimerInterrupt();
    if(interrupt_ == NULL || !interrupt_->isConstructed()) return false;
    // Set heap interrupt controller
    global_ = NULL;
    ::api::Heap* heap = ::Allocator::getHeap();
    if(heap == NULL || !heap->isConstructed()) return false;
    global_ = &interrupt_->global();
    heap->toggle(global_);
    return true;
  }
  
  /**
   * Deinitialization.
   */
  void System::deinit()
  {
    global_ = NULL;
    if(interrupt_ != NULL)
    {
      delete interrupt_;
      interrupt_ = NULL;
    }
  }
  
  /**
   * Hardware timer interrupt resource (no boot).
   */
  SystemTimerInterrupt* System::interrupt_;  

  /**
   * Global interrupt resource (no boot).
   */
  ::api::Toggle* System::global_;  
}
