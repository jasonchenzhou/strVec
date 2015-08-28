#include "strVec.h"

void strVec::push_back(const std::string &s)
{
    chk_n_alloc();
    alloc.construct(first_free++, s);
}

std::pair<std::string*, std::string*> strVec::alloc_n_copy(const std::string* b, const std::string* e){
	auto data = alloc.allocate(e -b);
	return {data, uninitialized_copy(b, e, data)};   //return a pair, which is begin and end of the new string
}


void strVec::free(){
	if(elements){
		for(auto p=first_free; p!=elements; ){
			alloc.destroy(--p);
		}
		alloc.deallocate(elements, cap-elements);
	}
}

strVec::strVec(const strVec &rfs){
    auto data = alloc_n_copy(rfs.begin(), rfs.end());
    elements = data.first;
    first_free = cap = data.second;
}

strVec& strVec::operator=(const strVec &rhs){
	auto tem = alloc_n_copy(rhs.begin(), rhs.end());
	free();
	elements = tem.first;
	first_free = cap = tem.second;
	return *this;
}

strVec::~strVec(){free();}


void strVec::alloc_n_move(size_t new_cap)
{
    auto newdata = alloc.allocate(new_cap);
    auto dest = newdata;
    auto elem = elements;
    for (size_t i = 0; i != size(); ++i)
        alloc.construct(dest++, std::move(*elem++));
    free();
    elements = newdata;
    first_free = dest;
    cap = elements + new_cap;
}

void strVec::reallocate(){
	auto newCapacity = size() ? 2*size() : 1;
	auto newData = alloc.allocate(newCapacity);
	auto dest = newData;
	auto elem = elements;
	for(size_t i=0; i!=size(); i++){
		alloc.construct(dest++, std::move(*elem++));
	}
	free();
	elements = newData;
	first_free = dest;
	cap = elements + newCapacity;
}


void strVec::reserve(size_t new_cap)
{
    if (new_cap <= capacity()) return;
    alloc_n_move(new_cap);
}

void strVec::resize(size_t count)
{
    resize(count, std::string());
}

void strVec::resize(size_t count, const std::string &s)
{
    if (count > size()) {
        if (count > capacity()) reserve(count * 2);
        for (size_t i = size(); i != count; ++i)
            alloc.construct(first_free++, s);
    }
    else if (count < size()) {
        while (first_free != elements + count)
            alloc.destroy(--first_free);
    }
}

int main()
{
	strVec v;
	v.push_back("jason");
	v.push_back("billy");
	std::cout<<*v.begin()<<std::endl;
	for(auto elem : v)  std::cout<<elem<<std::endl;
    return 0;
}