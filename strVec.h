#ifndef STR_VEC_
#define STR_VEC_

#include <memory>
#include <string>
#include <iostream>

class strVec{
public:
	strVec():elements(nullptr), first_free(nullptr), cap(nullptr){}
	strVec(const strVec&);
	strVec& operator=(const strVec&);
	~strVec();
	void push_back(const std::string&);
	size_t size() const {return first_free - elements;}
	size_t capacity() const {return cap - elements;}
	std::string *begin() const {return elements;}
	std::string *end() const {return first_free;}

	void reserve(size_t new_cap);
	void resize(size_t count);
	void resize(size_t count, const std::string&);
private:
	void chk_n_alloc(){if(size() == capacity())  reallocate();}
    std::pair<std::string*, std::string*> alloc_n_copy(const std::string*, const std::string*);
    void alloc_n_move(size_t new_cap);
    void free();
    void reallocate();
private:
	std::allocator<std::string> alloc;
    std::string *elements;
    std::string *first_free;
    std::string *cap;
};

#endif
