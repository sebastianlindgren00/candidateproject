/*
Copyright (C) Motion Workshop 2014. Public domain.

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/
#include "vrpn_Tracker_MotionNode.h"
#ifdef  VRPN_USE_MOTIONNODE

// Option to print out more information for run-time testing.
//#define TRACKER_MOTIONNODE_TEST 1

//
// Use the binary Motion C API library provided by Motion Workshop. The library
// is loaded dynamically at run-time and is not required to compile this
// tracker The C API is available in your software installation or directly
// from Motion Workshop at:
//
// http://www.motionnode.com/sdk.html#capi
//
// The API is not required to compile this tracker class. The binary
// library is required at run-time to connect to the MotionNode data
// streams.
//
//#include <MotionNodeCAPI.h>

// For convenience, the functions we will use are included directly in this
// file. No external compile time dependencies.
#if !defined(MNCAPI_PREVIEW_SIZE)

#if defined(_WIN32)
#  define MNCAPI_IMPORT_API __declspec(dllimport)
#  define MNCAPI_CALL_API __cdecl
#else
#  define MNCAPI_IMPORT_API
#  define MNCAPI_CALL_API
#endif // defined(_WIN32)

extern "C" {

#define MNCAPI_PREVIEW_SIZE (14)

enum mncapi_error_t {
  MNCAPI_FAILURE = 0,
  MNCAPI_SUCCESS = 1
};

enum mncapi_stream_t {
  MNCAPI_PREVIEW  = 1,
  MNCAPI_SENSOR   = 2,
  MNCAPI_RAW      = 3
};

}

#endif // !defined(MNCAPI_PREVIEW_SIZE)

#include <string>
#include <vector>

#if defined(_WIN32)
#  include <windows.h>
#  define MOTION_C_API_LIBRARY "MotionCAPI.dll"
#else
#  include <dlfcn.h>
#  include <stdlib.h>
#  if defined(__APPLE__)
#    define MOTION_C_API_LIBRARY "libMotionCAPI.dylib"
#  else
#    define MOTION_C_API_LIBRARY "libMotionCAPI.so"
#  endif // __APPLE__
#  define GetProcAddress dlsym
#endif // _WIN32

typedef int (MNCAPI_CALL_API *MNCAPI_OPEN_HOST_FN)(enum mncapi_stream_t, const char *, int);
typedef int (MNCAPI_CALL_API *MNCAPI_SAMPLE_FN)(int, float *, int);
typedef void (MNCAPI_CALL_API *MNCAPI_CLOSE_FN)(int);


/**
  Just a local class definition to model the SDK Sampler class. This class
  stores all of the dynamically loaded library and symbol information from
  the C API.

  The constructor loads the library, connects, and binds useful function symbols.

  The destructor unloads the library after closing any active connections.
*/
class Sampler {
public:
  typedef std::vector<float> data_type;

  Sampler(const std::string &address, unsigned port);
  ~Sampler();

  bool get_data_block(data_type &data, const unsigned &num_sensor);

private:
  int m_handle;
#if defined(_WIN32)
  HMODULE m_library_handle;
#else
  void *m_library_handle;
#endif // WIN32
  MNCAPI_SAMPLE_FN m_mncapi_sample;
}; // class Sampler

typedef Sampler sampler_type;


vrpn_Tracker_MotionNode::vrpn_Tracker_MotionNode(const char *name,
                                                 vrpn_Connection *c,
                                                 unsigned num_sensor,
                                                 const char *address,
                                                 unsigned port)
  : vrpn_Tracker(name, c), m_num_sensor(num_sensor), m_handle(NULL)
{
#if defined(TRACKER_MOTIONNODE_TEST)
  printf("vrpn_Tracker_MotionNode {\n");
#endif // TRACKER_MOTIONNODE_TEST

  register_server_handlers();

  {
    std::string remote_address = "127.0.0.1";
    unsigned remote_port = 32079;
    if (NULL != address) {
      remote_address = address;
    }
    if (port > 0) {
      remote_port = port;
    }

    sampler_type *sampler = new sampler_type(address, port);

    // Attempt to read a single sample from
    // the stream.
    for (int i=0; i<4; i++) {
      sampler_type::data_type data;
      if (sampler->get_data_block(data, m_num_sensor) && !data.empty()) {
        m_handle = sampler;
        sampler = NULL;
        break;
      }
    }
  
    if (NULL == m_handle) {
      fprintf(stderr, "MotionNode driver failed to start sampling, device not currently reading\n");
    }
#if defined(TRACKER_MOTIONNODE_TEST)
    else {
      printf(
        "Connected to Motion data service at \"%s:%d\"\n",
        remote_address.c_str(), remote_port);
    }
#endif // TRACKER_MOTIONNODE_TEST

    // Clean up resources now if the sampler was never
    // copied into this object.
    if ((NULL == m_handle) && (NULL != sampler)) {
      delete sampler;
    }
  }

  if (NULL != m_handle) {
    vrpn_Tracker::status = vrpn_TRACKER_SYNCING;
  } else {
    vrpn_Tracker::status = vrpn_TRACKER_FAIL;
  }

#if defined(TRACKER_MOTIONNODE_TEST)
  printf("} vrpn_Tracker_MotionNode, status=%d\n", vrpn_Tracker::status);
#endif // TRACKER_MOTIONNODE_TEST
}
 
vrpn_Tracker_MotionNode::~vrpn_Tracker_MotionNode()
{
#if defined(TRACKER_MOTIONNODE_TEST)
  printf("~vrpn_Tracker_MotionNode() {\n");
#endif // TRACKER_MOTIONNODE_TEST

  if (NULL != m_handle) {
    sampler_type *sampler = reinterpret_cast<sampler_type *>(m_handle);
    delete sampler;

    m_handle = NULL;
  }

#if defined(TRACKER_MOTIONNODE_TEST)
  printf("} ~vrpn_Tracker_MotionNode()\n");
#endif // TRACKER_MOTIONNODE_TEST
}

void vrpn_Tracker_MotionNode::mainloop()
{
  // Call the generic server mainloop, since we are a server
  server_mainloop();

  get_report();
}

void vrpn_Tracker_MotionNode::get_report()
{
  if (NULL != m_handle) {
    sampler_type *sampler = reinterpret_cast<sampler_type *>(m_handle);

    sampler_type::data_type data;
    if (sampler->get_data_block(data, m_num_sensor) && !data.empty()) {

      for (std::size_t i=0; i<m_num_sensor; i++) {
        const std::size_t index = i * MNCAPI_PREVIEW_SIZE;
        if (index + 4 < data.size()) {

          vrpn_Tracker::d_sensor = i;
          vrpn_Tracker::d_quat[0] = data[index + 1];
          vrpn_Tracker::d_quat[1] = data[index + 2];
          vrpn_Tracker::d_quat[2] = data[index + 3];
          vrpn_Tracker::d_quat[3] = data[index + 0];

          send_report();
        }
      }

    }
  }

}

void vrpn_Tracker_MotionNode::send_report()
{
  // Send the message on the connection
  if (NULL != vrpn_Tracker::d_connection) {
    char buffer[1024];
    int	len = encode_to(buffer);
    if (vrpn_Tracker::d_connection->pack_message(len, timestamp, position_m_id, d_sender_id, buffer, vrpn_CONNECTION_LOW_LATENCY)) {
      fprintf(stderr, "MotionNode: cannot write message: tossing\n");
    }
  }
}


Sampler::Sampler(const std::string &address, unsigned port)
  : m_handle(0), m_library_handle(NULL), m_mncapi_sample(NULL)
{
  // Load the dynamic library. This will use the search paths
  // and fail if the library can not be found.
#if defined(_WIN32)

  HMODULE library_handle = LoadLibrary(MOTION_C_API_LIBRARY);
  if (NULL == library_handle) {
    library_handle = LoadLibrary("C:/Program Files/Motion/tools/plugin/capi/" MOTION_C_API_LIBRARY);
  }

#else

  // Manually search for the shared library in likely locations.
  const char *SearchPaths[3] = {
    MOTION_C_API_LIBRARY,
    "./" MOTION_C_API_LIBRARY,
#if defined(__APPLE__)
    "/Applications/Motion.app/Contents/Resources/tools/plugin/capi" MOTION_C_API_LIBRARY
#else
    "/opt/Motion/tools/plugin/capi" MOTION_C_API_LIBRARY
#endif // defined(__APPLE__)
  };

  void *library_handle = NULL;
  for (int i=0; i<3; i++) {
    library_handle = dlopen(SearchPaths[i], RTLD_LAZY);
    if (NULL != library_handle) {
#if defined(TRACKER_MOTIONNODE_TEST)
      printf("Loaded Motion C API library, \"%s\"\n", SearchPaths[i]);
#endif // TRACKER_MOTIONNODE_TEST
      break;
    }
  }

#endif // defined(_WIN32)

  if (NULL != library_handle) {
    m_library_handle = library_handle;

    // Bind the open function and connect to the data service.
    MNCAPI_OPEN_HOST_FN mncapi_open_host =
      reinterpret_cast<MNCAPI_OPEN_HOST_FN>(GetProcAddress(m_library_handle, "mncapi_open_host"));
    if (NULL != mncapi_open_host) {
      // Connect and get the integer handle back.
      int handle = mncapi_open_host(MNCAPI_PREVIEW, address.c_str(), static_cast<int>(port));
      if (handle > 0) {
        m_handle = handle;

        // Bind the sampling function that we will reuse many times in the get_data_block method.
        MNCAPI_SAMPLE_FN mncapi_sample =
          reinterpret_cast<MNCAPI_SAMPLE_FN>(GetProcAddress(m_library_handle, "mncapi_sample"));
        if (NULL != mncapi_sample) {
          m_mncapi_sample = mncapi_sample;
        } else {
          fprintf(
            stderr,
            "failed to bind function \"mncapi_sample\" from Motion C API library\n");
        }

      } else {
        fprintf(
          stderr,
          "failed to connect to Motion data service at \"%s:%d\"\n",
          address.c_str(), port);
      }

    } else {
      fprintf(
        stderr,
        "failed to bind function \"mncapi_open_host\" from Motion C API library\n");
    }
  } else {
    fprintf(
      stderr,
      "failed to find Motion C API library, \"" MOTION_C_API_LIBRARY "\"\n");
  }
}

Sampler::~Sampler()
{
  // Clean up resource. Unload the dynamic library after closing the active connection.
  if (NULL != m_library_handle) {
    if (m_handle > 0) {
      MNCAPI_CLOSE_FN mncapi_close =
        reinterpret_cast<MNCAPI_CLOSE_FN>(GetProcAddress(m_library_handle, "mncapi_close"));
      if (NULL != mncapi_close) {
        mncapi_close(m_handle);
        m_handle = 0;
      } else {
        fprintf(
          stderr,
          "failed to bind function \"mncapi_close\" from Motion C API library\n");
      }
    }

    m_mncapi_sample = NULL;

#if defined(_WIN32)
    if (FreeLibrary(m_library_handle)) {
#else
    if (0 == dlclose(m_library_handle)) {
#endif // defined(_WIN32)
    } else {
      fprintf(stderr, "failed to unload Motion C API library\n");
    }

    m_library_handle = NULL;
  }
}

bool Sampler::get_data_block(data_type &data, const unsigned &num_sensor)
{
  bool result = false;

  if ((m_handle > 0) && (NULL != m_mncapi_sample) && (num_sensor > 0)) {
    // Accept up to num_sensor results. We may not receive that many.
    data.resize(MNCAPI_PREVIEW_SIZE * num_sensor);

    int sample_result = m_mncapi_sample(m_handle, &data[0], data.size());
    if (sample_result > MNCAPI_FAILURE) {
      result = true;
    }
  }

  return result;
}

#endif // VRPN_USE_MOTIONNODE
