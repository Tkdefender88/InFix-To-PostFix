/**
 * F18 CSCI232 Data Structures and Algorithms
 * 
 * Precondition Custom Exception Class
 * 
 * Phillip J. Curtiss, Assistant Professor
 * pcurtiss@mtech.edu, 406-496-4807
 * Department of Computer Science, Montana Tech
 */

#ifndef PRECOND_VIOLATED_EXCEP_IMP

#define PRECOND_VIOLATED_EXCEP_IMP

#include "PrecondViolatedExcep.h"  

PrecondViolatedExcep::PrecondViolatedExcep(const std::string& message)
         : std::logic_error("Precondition Violated Exception: " + message)
{
}  // end constructor

#endif