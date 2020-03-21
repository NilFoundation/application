# =nil; Application Framework [![Build Status](https://travis-ci.com/nemothenoone/application.svg?token=DHGZQ8ocJtbnXsTs61qE&branch=master)](https://travis-ci.com/nemothenoone/application)

### Introduction

=nil; Application provides an application environment, or start point to any people that want a basic
 infrastructure to build an system application on Windows or Unix Variants (e.g. Linux, MacOS).
 
 This library intends to be put int [Boost](https://boost.org) sometime.

### Hello World (server)

```cpp

#define BOOST_ALL_DYN_LINK
#define BOOST_LIB_DIAGNOSTIC

#define BOOST_APPLICATION_FEATURE_NS_SELECT_BOOST

#include <iostream>
#include <fstream>

#include <boost/application.hpp>

using namespace boost;

// my application code

class myapp
{   
public:

   myapp(application::context& context)
      : context_(context)
   {
   }

   void worker()
   {
      // my application behaviour

      // dump args

      std::vector<std::string> arg_vector = 
         context_.find<application::args>()->arg_vector();

      my_log_file_ << "-----------------------------" << std::endl;
      my_log_file_ << "---------- Arg List ---------" << std::endl;
      my_log_file_ << "-----------------------------" << std::endl;

      // only print args on screen
      for(std::vector<std::string>::iterator it = arg_vector.begin(); 
         it != arg_vector.end(); ++it) {
         my_log_file_ << *it << std::endl;
      }

      my_log_file_ << "-----------------------------" << std::endl;

      // run logic

      boost::shared_ptr<application::status> st =          
         context_.find<application::status>();

      int count = 0;
      while(st->state() != application::status::stopped)
      {
         boost::this_thread::sleep(boost::posix_time::seconds(1));

         if(st->state() == application::status::paused)
            my_log_file_ << count++ << ", paused..." << std::endl;
         else
            my_log_file_ << count++ << ", running..." << std::endl;
      }
   }

   // param
   int operator()()
   {
      std::string logfile 
         = context_.find<application::path>()->executable_path().string() + "/log.txt";
      
      my_log_file_.open(logfile.c_str());
      my_log_file_ << "Start Log..." << std::endl;

      // launch a work thread
      boost::thread thread(&myapp::worker, this);
      
      context_.find<application::wait_for_termination_request>()->wait();

      // to run direct
      // worker(&context);

      return 0;
   }

   // windows/posix

   bool stop()
   {
      my_log_file_ << "Stoping my application..." << std::endl;
      my_log_file_.close();

      return true; // return true to stop, false to ignore
   }

   // windows specific (ignored on posix)

   bool pause()
   {
      my_log_file_ << "Pause my application..." << std::endl;
      return true; // return true to pause, false to ignore
   }

   bool resume()
   {
      my_log_file_ << "Resume my application..." << std::endl;
      return true; // return true to resume, false to ignore
   }

private:

   std::ofstream my_log_file_;
   application::context& context_;

};

int main(int argc, char *argv[])
{ 
  application::context app_context;
   
   // auto_handler will automatically add termination, pause and resume (windows) handlers
   application::auto_handler<myapp> app(app_context);

   // my server aspects

   // to handle args
   app_context.insert<application::args>(
      boost::make_shared<application::args>(argc, argv));  

   // my server instantiation

   boost::system::error_code ec;
   int result = application::launch<application::server>(app, app_context, ec);

   if(ec)
   {
      std::cout << "[E] " << ec.message() 
         << " <" << ec.value() << "> " << std::endl;
   }
   
   return result;
}

```

### Note about Plug-In system

This library is not intended to be the only building block for the plugin system. It is supposed to be
 built along with [Boost.DLL](https://github.com/apolukhin/Boost.DLL) usage. 

### On-line Documentation (Work in Progress), and other information

* [Online Docs](https://database.nil.foundation/projects/application/index.html) 

### Articles

Library use:
[Build a Server Application using Application Library] (http://www.codeproject.com/Articles/756866/Build-a-Server-Application-using-Application-Libra)

Library customization:
[Creating a New Application Mode] (http://www.codeproject.com/Articles/695937/Creating-a-New-Application-Mode)

### Installation Notes

If you are using boost lower than 1.56.0 you need install TypeIndex library manually:

* [TypeIndex] (https://github.com/boostorg/type_index)

### Tested compilers

* Linux (x86/64)
   * GCC 4.7/4.8/4.9

* Windows (x86/x86-64)
   * MinGW 4.7/4.8
   * Visual Studio 2013

### Other 'Application' Frameworks:

* [Boost.Application](https://github.com/retf/Boost.Application)
* [Pocoproject (WinService)](http://pocoproject.org/docs-1.5.3/Poco.Util.WinService.html)
* [Libdaemon (Daemon)] (http://www.tyrfingr.is/projects/libdaemon/)
* [Qt (qtservice)](http://doc.qt.digia.com/solutions/4/qtservice/qtservice.html)
 
### Contributing

Want to contribute with =nil; Application project? Open a pull request!
   
### Acknowledgements

A special thanks to Vicente J. Botet Escriba that helped a lot on all areas of this lib.

Thanks to Renato Tegon Forti for the initial library implementation.
Thanks to Benjamin Dieckmann for global_context implementation.
Thanks to Rodrigo Madera (RM of Boost.Application).<br>
Thanks to Antony Polukhin for improvements on plug-in system module (shared_library), that now is a new library, see notes above. 

### Contact

[Mikhail Komarov](mailto:nemo@nil.foundation)

### License

Distributed under the [Boost Software License, Version 1.0](http://www.boost.org/LICENSE_1_0.txt).
