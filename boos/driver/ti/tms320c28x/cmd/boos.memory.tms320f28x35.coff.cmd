/**
 * System memory configuration for TI TMS320F28335/F28333/F28235 DSCs.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
-heap  0x100
-stack 0x100

MEMORY
{
  /** Program Memory */
PAGE 0:    

  RAM         : origin = 0x008000, length = 0x004000   
  FLASHH      : origin = 0x300000, length = 0x008000
  FLASHG      : origin = 0x308000, length = 0x008000
  FLASHF      : origin = 0x310000, length = 0x008000
  FLASHE      : origin = 0x318000, length = 0x008000
  FLASHD      : origin = 0x320000, length = 0x008000
  FLASHC      : origin = 0x328000, length = 0x008000
  FLASHB      : origin = 0x330000, length = 0x008000
  FLASHA      : origin = 0x338000, length = 0x007F80
  BROM        : origin = 0x3fffc0, length = 0x000040

  /** Data Memory */
PAGE 1:

  M0          : origin = 0x000000, length = 0x000400
  M1          : origin = 0x000400, length = 0x000400
  PIE         : origin = 0x000d00, length = 0x000100     
  RAM         : origin = 0x00c000, length = 0x003000
  HEAP        : origin = 0x00f000, length = 0x001000
}

SECTIONS
{
  /** Hardware interrupts */    
  .hwi       : > PIE,     PAGE = 1

  /** Allocate program areas */
  .cinit     : > FLASHA,  PAGE = 0
  .pinit     : > FLASHA,  PAGE = 0
  .text      : > RAM,  PAGE = 0
  .special   : 
               {
                 ./Debug/boos.Board.obj            (.text)               
                 ./Debug/boos.Configuration.obj    (.text)
                 ./Debug/boos.driver.Boot.obj      (.text)
                 ./Debug/boos.driver.Pll.obj       (.text)
                 ./Debug/boos.driver.Processor.obj (.text)
                 ./Debug/boos.driver.Watchdog.obj  (.text)
                 ./Debug/boos.system.Mutex.obj     (.text)
                 ./Debug/boos.system.Semaphore.obj (.text)
               } > FLASHA,  PAGE = 0   

  /** Initalized data sections */
  .econst    : > FLASHB,  PAGE = 0

  /** Uninitalized data sections */
  .data      : > RAM,     PAGE = 1
  .stack     : > RAM,     PAGE = 1, fill = 0xffff
  .bss       : > RAM,     PAGE = 1, fill = 0xffff      
  .sysmem    : > RAM,     PAGE = 1, fill = 0xffff      
  .ebss      : > RAM,     PAGE = 1, fill = 0xffff
  .esysmem   : > RAM,     PAGE = 1, fill = 0xffff
}
