#include <unistd.h>
#include <iostream>
#include <map>
// to find the boost library pass this flag to compiler:
// -I/local/src/boost_1_43_0/boost
//#include <functional/hash.hpp>
// apparently don't need boost for this.
using std::cout;
using std::endl;

typedef std::map<int, std::string> sys_map;
void add(sys_map*, int, std::string);
void print(sys_map*);

int main (void)
{
  sys_map aMap;
  sys_map* p = &aMap;

  add(p, _SC_NPROCESSORS_ONLN, "Nr of CPUs online: ");
  add(p, _SC_NPROCESSORS_CONF, "Nr of CPUs configured: ");

  aMap[_SC_ARG_MAX] = "The maximum bytes of argument to execve(2): ";
  aMap[_SC_CHILD_MAX] = "The maximum number of simultaneous processes per user id.";
  aMap[_SC_CLK_TCK] = "The frequency of the statistics clock in ticks per second.";
  aMap[_SC_IOV_MAX] = "The maximum number of elements in the I/O vector used by readv(2), writev(2), recvmsg(2), and sendmsg(2).";
  aMap[_SC_NGROUPS_MAX] = "The maximum number of supplemental groups.";
  aMap[_SC_NPROCESSORS_CONF] = "The number of processors configured.";
  aMap[_SC_NPROCESSORS_ONLN] = "The number of processors currently online.";
  aMap[_SC_OPEN_MAX] = "The maximum number of open files per user id.";
  aMap[_SC_STREAM_MAX] = "The minimum maximum number of streams that a process may have open at any one time.";
  aMap[_SC_TZNAME_MAX] = "The minimum maximum number of types supported for the name of a timezone.";
  aMap[_SC_JOB_CONTROL] = "Return 1 if job control is available on this system, otherwise -1.";
  aMap[_SC_SAVED_IDS] = "Returns 1 if saved set-group and saved set-user ID is available, otherwise -1.";
  aMap[_SC_VERSION] = "The version of IEEE Std 1003.1 (``POSIX.1'') with which the system attempts to comply.";
  aMap[_SC_BC_BASE_MAX] = "The maximum ibase/obase values in the bc(1) utility.";
  aMap[_SC_BC_DIM_MAX] = "The maximum array size in the bc(1) utility.";
  aMap[_SC_BC_SCALE_MAX] = "The maximum scale value in the bc(1) utility.";
  aMap[_SC_BC_STRING_MAX] = "The maximum string length in the bc(1) utility.";
  aMap[_SC_COLL_WEIGHTS_MAX] = "The maximum number of weights that can be assigned to any entry of the LC_COLLATE order keyword in the locale definition file.";
  aMap[_SC_EXPR_NEST_MAX] = "The maximum number of expressions that can be nested within parenthesis by the expr(1) utility.";
  aMap[_SC_LINE_MAX] = "The maximum length in bytes of a text-processing utility's input line.";
  aMap[_SC_RE_DUP_MAX] = "The maximum number of repeated occurrences of a regular expression permitted when using interval notation.";
  aMap[_SC_2_VERSION] = "The version of IEEE Std 1003.2 (``POSIX.2'') with which the system attempts to comply.";
  aMap[_SC_2_C_BIND] = "Return 1 if the system's C-language development facilities support the C-Language Bindings Option, otherwise -1.";
  aMap[_SC_2_C_DEV] = "Return 1 if the system supports the C-Language Development Utilities Option, otherwise -1.";
  aMap[_SC_2_CHAR_TERM] = "Return 1 if the system supports at least one terminal type capable of all operations described in IEEE Std 1003.2 (``POSIX.2''), otherwise -1.";
  aMap[_SC_2_FORT_DEV] = "Return 1 if the system supports the FORTRAN Development Utilities Option, otherwise -1.";
  aMap[_SC_2_FORT_RUN] = "Return 1 if the system supports the FORTRAN Runtime Utilities Option, otherwise -1.";
  aMap[_SC_2_LOCALEDEF] = "Return 1 if the system supports the creation of locales, otherwise -1.";
  aMap[_SC_2_SW_DEV] = "Return 1 if the system supports the Software Development Utilities Option, otherwise -1.";
  aMap[_SC_2_UPE] = "Return 1 if the system supports the User Portability Utilities Option, otherwise -1.";


  print(p);

  return 0;
}

void print(sys_map* p)
{
  for (sys_map::iterator i = p->begin(); i != p->end(); ++i)
  {
    cout << sysconf(i->first) << ": \t" << i->second << " " <<  endl;
  }
}

void add(sys_map* p, int value, std::string text)
{
  (*p)[value] = text;
}
