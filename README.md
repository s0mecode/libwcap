# libwcap

`libwcap` is a small C++ library that lets you capture the screen, a window or any
GStreamer‑compatible source on Linux.  It relies on the *freedesktop.org* ScreenCast
portal and GStreamer to pull raw frames from the compositor.

The project is intentionally lightweight and has no runtime dependencies other than
the system libraries it links against.

---
## Features

* Capture the whole screen, a single window or any source the user selects.
* Retrieve frames as a `std::vector<uint8_t>` in **BGR** format.
* Very small public API – just a handful of classes and enums.
* Example program `examples/simple_grab.cpp` demonstrates the usage.

---
## Requirements

* C++17 compiler (clang, gcc, MSVC)
* CMake 3.10 or newer
* GStreamer 1.0 development packages
* libgio‑2.0 / libglib‑2.0 development packages
* pkg‑config

---
## Building

```bash
mkdir build && cd build
cmake ..
make
```

The build produces:

* `libwcap.so` – the shared library
* `example_simple` – a tiny demo program in `examples/`

---
## Usage

The public header is `include/wcap.hpp`.  A minimal example is provided
in `examples/simple_grab.cpp`.

Compile the example (already built by the CMake target `example_simple`):

```bash
./build/example_simple
```

Run it and answer the prompt to choose the capture type.  The program will
capture 100 frames and save the last frame as `snapshot.png`.

---
## API Overview

```cpp
namespace wcap {
    enum class CaptureType { Screen, Window, Any };
    struct Frame {
        int width = 0;
        int height = 0;
        std::vector<uint8_t> data; // BGR, 3 bytes per pixel
    };

    class ScreenCapture {
    public:
        ScreenCapture();
        ~ScreenCapture();
        bool select_source(CaptureType type); // initialise capture
        Frame get_frame();                    // pull next frame
        void stop();                          // stop the pipeline
    };
}
```

---
## License

Apache-2.0 – see the `LICENSE` file.

---
## Contributing

Feel free to open issues or submit pull requests.