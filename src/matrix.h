#ifndef _MATRIX_H
#define _MATRIX_H

#include <cstddef>
#include <stdexcept>

template<class T>
class matrix {
	T *mem;
	size_t xsize, ysize;
public:
	matrix (size_t xsz, size_t ysz) : xsize (xsz), ysize (ysz) {
		mem = new T[xsz*ysz];
	}

	~matrix () { delete[] mem; }

	T& at (size_t x, size_t y) {
		if (x >= xsize || y >= ysize)
			throw std::range_error ("matrix: at() out of index");
		return mem[y*xsize + x];
	}

	T &operator() (size_t x, size_t y) {
		return at (x, y);
	}
};

#endif
