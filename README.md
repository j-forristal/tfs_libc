# tfs_libc

This is a portable, partial libc implementation useful for situations when you want to reduce your dependency (namely, eliminate imports) on external libc functions. It lets you carry-in select libc functionality that can be statically embedded into your application, even if your application is dynamically linked.

The main use case is app fortification, where you want to eliminate external shared library imports that are easy to hook or trampoline.

This implementation supports Android, iOS, MacOS (Darwin), Linux, and ESP8266 microcontroller.  There is also a generic pass-through layer that will simply use regular libc.

Note: this library is *not* transparent in operation.  Function names are explicitly different, meaning you will need to write/change your code specifically to use this library.


# License

Written in 2019 by Jeff Forristal, jeff@forristal.com

To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.

Please see LICENSE file for a copy of the CC0 Public Domain Dedication.
