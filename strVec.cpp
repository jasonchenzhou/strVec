#include "strVec.h"

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
    auto data = alloc_n_copy(rfs);
    elements = data.first;
    first_free = cap = data.second;
}

strVec &operator=(const strVec &rhs){
	auto tem = alloc_n_copy(rhs);
	free();
	elements = tem.first;
	first_free = cap = tem.second;
	return *this;
}

~strVec(){free();}

void reallocate(){
	auto newCapacity = size() ? 2*size() : 1;
	auto newData = alloc.allocate(newCapacity);
	auto dest = newData;
	auto elem = elements;
	for(size_t i=0; i!=size(); i++){
		alloc.construct(dest++, std::move(elem++));
	}
	free();
	elements = newData;
	first_free = dest;
	cap = elements + newCapacity;
}