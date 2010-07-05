// to find the boost library pass this flag to compiler:
// -I/local/src/boost_1_43_0/boost
#include <boost/thread.hpp>

//#include <boost/bind.hpp>
//#include <boost/thread/thread.hpp>
//#include <boost/thread/mutex.hpp>
//#include <boost/shared_ptr.hpp>
#include <vector>

class threaded_class
{
public:
  threaded_class()
    : m_stoprequested(false)
    {
    }

  ~threaded_class()
    {
    }

  // Create the thread and start work
  void go()
    {
      assert(!m_thread);
      m_thread = boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&threaded_class::do_work, this)));
    }

  void stop() // Note 1
    {
      assert(m_thread);
      m_stoprequested = true;
      m_thread->join();
    }

  int get_fibonacci_value(int which)
    {
      boost::mutex::scoped_lock l(m_mutex); // Note 2
      return m_fibonacci_values.get(which);
    }

private:
  volatile bool m_stoprequested;
  boost::shared_ptr<boost::thread> m_thread;
  boost::mutex m_mutex;

  std::vector<int> m_fibonacci_values;

  int fibonacci_number(int num)
    {
      switch(num)
      {
        case 0:
        case 1:
          return 1;
        default:
          return fibonacci_number(num-2) + fibonacci_number(num-1); // Correct 4/6/2010 based on comments
      };
    }

  // Compute and save fibonacci numbers as fast as possible
  void do_work()
    {
      int iteration = 0;
      while (!m_stoprequested)
      {
        int value = fibonacci_number(iteration);
        boost::mutex::scoped_lock l(m_mutex);
        m_fibonacci_values.push_back(value);
        ++iteration;
      }
    }
};

int main(void)
{
  return 0;
}
