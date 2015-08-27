#ifndef STR_VEC_
#define STR_VEC_

#include <memory>
#include <string>

class strVec{
public:
	strVec():elements(nullptr), first_free(nulptr), cap(nullptr){}
	strVec(const strVec&);
	strVec &operator=(const strVec&);
	~strVec();
	void push_back(const std::string&);
	size_t size() const {return first_free - elements;}
	std::string *begin() const {return elements;}
	std::string *end() const {return first_free;}
private:
	std::allocator<std::string> alloc;
	void chk_n_alloc(){if(size() == capacity())  reallocate();}
    std::pair<std::string*, std::string*> alloc_n_copy(const std::string*, const std::string*);
    void free();
    void reallocate();
    std::string *elements;
    std::string *first_free;
    std::string *cap;
};

#endif