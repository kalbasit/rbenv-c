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

TBD
