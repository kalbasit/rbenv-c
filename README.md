This is an experimental reimplementation of the "slow parts" of rbenv in C.

Don't use it yet!

## Table of Contents

* [How It Works](#how-it-works)
* [Installing](#installing)
* [Building](#building)
* [Testing](#testing)
* [Development](#development)
  * [Version History](#version-history)
  * [License](#license)

## How It Works

`rbenv-c` replaces the slow parts of `rbenv` execution (path traversal) with
C code that does it quickly.

## How It Doesn't Work

1. Command-line competion for subcommands in C don't work.
2. Documentation for subcommands in C don't work.
3. `make install` only works if rbenv is installed in `~/.rbenv`. 
   In particular, it does not work with homebrew rbenv.
4. Right now it only "works" in Mac OS X. Implementations of 
   [`exepath`](https://github.com/sstephenson/rbenv-c/blob/master/exepath.c) 
   for other operating systems are welcome.
5. The only tested compiler so far is `clang`.

## Installing

Don't run `make install` from the command line; this is experimental and not
ready for you to enjoy.

## Building

Run `make` from the command line.

## Testing

Run `make test` from the command line.

## Development

The rbenv-c source code is 
[hosted on GitHub](https://github.com/sstephenson/rbenv-c). 
It's easy to understand if you're familiar with the C programming language.

Right now this project is experimental. If it doesn't work, [pull requests are
accepted](https://github.com/sstephenson/rbenv-c/pulls).

### Version History

**0.0.0** (Not Yet)

* rbenv-c exists

### License

(The MIT license)

Copyright (c) 2013 Sam Stephenson

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
